/*
Copyright (c) 2011, Siemens Corporate Research a Division of Siemens Corporation 
All rights reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/
/*!
 * \file SoVtkRenderer.cpp
 *
 * \brief SoVtkRenderer class implementation.
 * \author Sylvain Jaume, Francois Huguet
 */

#include "SoVtkRenderer.h"

#include <Inventor/elements/SoViewVolumeElement.h>
#include <Inventor/elements/SoFocalDistanceElement.h>
#include <Inventor/elements/SoViewportRegionElement.h>
#include <Inventor/elements/SoViewingMatrixElement.h>
#include <Inventor/elements/SoComplexityElement.h>

#include "SoVtkAssembly.h"
#include "SoVtkActor.h"
#include "SoVtkActor2D.h"
#include "SoVtkImageActor.h"
#include "SoVtkLODActor.h"
#include "SoVtkVolume.h"
#include "SoVtkUtils.h"

#include "vtkCamera.h"
#ifdef WIN32
#include "vtkWin32OpenGLRenderWindow.h"
#endif // WIN32

#define pi 3.14159265358979323846

SO_NODE_SOURCE( SoVtkRenderer );

SoVtkRenderer::SoVtkRenderer()
{
  SO_NODE_CONSTRUCTOR( SoVtkRenderer );

  mRen = vtkOpenGLRenderer::New();
  mRen->Register(0);
  mRen->SetAllocatedRenderTime(10);

  mRenWin = vtkRenderWindow::New();
  mRenWin->Register(0);
  mRenWin->AddRenderer(mRen);

  /* FIXME : The stereo render modifies the camera. */

  //SO_NODE_ADD_FIELD( StereoRender, (FALSE) );

  //SO_NODE_DEFINE_ENUM_VALUE(StereoModeEnum, Anaglyph);
  //SO_NODE_DEFINE_ENUM_VALUE(StereoModeEnum, CrystalEyes);
  //SO_NODE_DEFINE_ENUM_VALUE(StereoModeEnum, Dresden);
  //SO_NODE_DEFINE_ENUM_VALUE(StereoModeEnum, Interlaced);
  //SO_NODE_DEFINE_ENUM_VALUE(StereoModeEnum, Left);
  //SO_NODE_DEFINE_ENUM_VALUE(StereoModeEnum, RedBlue);
  //SO_NODE_DEFINE_ENUM_VALUE(StereoModeEnum, Right);
  //SO_NODE_SET_SF_ENUM_TYPE(StereoMode, StereoModeEnum);

  //SO_NODE_ADD_FIELD( StereoMode, (Interlaced) );
	
  SO_NODE_ADD_FIELD(Background,(0,0,0));
#ifdef WIN32
  mRC = 0;
#endif // WIN32
  mNodeId = 0;
}

SoVtkRenderer::~SoVtkRenderer()
{
  // Rmq: we don't delete the renderer since it is done by the renderWindow.
	
  if (mRenWin)
  {
  mRenWin->UnRegister(0);
  mRenWin->Delete();
  mRenWin = 0;
  }
}

void
SoVtkRenderer::initClass()
{
	SO_NODE_INIT_CLASS( SoVtkRenderer, SoGroup, "Group" );

	SO_ENABLE(SoGLRenderAction,SoComplexityElement);
}


                //////////////// RENDERING ////////////////////


void
SoVtkRenderer::GLRender( SoGLRenderAction* action )
{
	SoGroup::GLRender(action);

	if ( mNodeId != getNodeId() )
	{
		mNodeId = getNodeId();
		updateChildren();
	}
#ifdef WIN32
	// Update graphics/rendering context
	HGLRC currentContext = ::wglGetCurrentContext();
	if (mRC != currentContext)
	{
	  mRC = currentContext;
	  vtkWin32OpenGLRenderWindow *win32RenderWindow = vtkWin32OpenGLRenderWindow::SafeDownCast(mRenWin);
	  if(win32RenderWindow)
	    {
	    win32RenderWindow->SetDeviceContext(::wglGetCurrentDC());
	    win32RenderWindow->SetContextId(currentContext);
		mRenWin->SetSwapBuffers(0);
		win32RenderWindow->OpenGLInit();
		}
	}
#endif // WIN32
	// Update the size of both vtk viewport and window
	this->updateRenderWindowSize(action->getState());


	// Change the stereo mode of the camera
	this->updateStereoMode();

	// Update the vtk camera according to the inventor state
	updateCamera(action->getState());

	float Complexity = SoComplexityElement::get(action->getState());
	if (Complexity > 0 && Complexity <= 0.25 )
		mRenWin->SetDesiredUpdateRate(5);
	else
	{
		mRenWin->SetDesiredUpdateRate(0);
	}

	SO_VTK_SET_FIELD_VEC3F(mRen,Background);

	// vtk multiplies to the current modelview matrix, therefore set it to identity
	glLoadIdentity();

	mRenWin->Render();
}


             
void 
SoVtkRenderer::updateChildren()
{
	mRen->RemoveAllViewProps();

	// An assembly is a hierarchy of actors or volumes, since the renderer
	// does not see the objects under the assembly, we have to update the children of 
	// the assembly when one of its parts has changed so that the renderer knows
	// that one part of its assembly has changed.
	for (int i = 0; i < SoGroup::getNumChildren(); i++)
	{
		SoNode *child = SoGroup::getChild(i);
	
		if (child->isOfType(SoVtkAssembly::getClassTypeId()))
		{
			// assembly
			SoVtkAssembly *assembly = (SoVtkAssembly *) child;
			assembly->updateChildren();
		}
	}

	for (int i = 0; i < SoGroup::getNumChildren(); i++)
	{
		SoNode *child = SoGroup::getChild(i);

		if (child->isOfType(SoVtkActor::getClassTypeId()))
		{
			// actor
			SoVtkActor *actor = (SoVtkActor *) child;
			mRen->AddActor(actor->getActor());
		}

		if (child->isOfType(SoVtkLODActor::getClassTypeId()))
		{
			// LOD actor
			SoVtkLODActor *actor = (SoVtkLODActor *) child;
			mRen->AddActor(actor->getLODActor());
		}

		if (child->isOfType(SoVtkActor2D::getClassTypeId()))
		{
			// actor 2D
			SoVtkActor2D *actor = (SoVtkActor2D *) child;
			mRen->AddActor2D(actor->getActor2D());
		}

		if (child->isOfType(SoVtkImageActor::getClassTypeId()))
		{
			// image actor
			SoVtkImageActor *actor = (SoVtkImageActor *) child;
			mRen->AddActor(actor->getImageActor());
		}

		if (child->isOfType(SoVtkVolume::getClassTypeId()))
		{
			// volume
			SoVtkVolume *vol = (SoVtkVolume *) child;
			mRen->AddVolume(vol->getVolume());
		}
		
		if (child->isOfType(SoVtkAssembly::getClassTypeId()))
		{
			// assembly
			SoVtkAssembly *assembly = (SoVtkAssembly *) child;
			mRen->AddViewProp(vtkAssembly::SafeDownCast(assembly->getAssembly()));
		}
	}
}


           ///////////////////// UPDATE CAMERA ///////////////////////


void SoVtkRenderer::normalize(SbVec3f& v)
{
   GLdouble d = sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
   if (d)
   { 
     v[0] /= d; v[1] /= d; v[2] /= d;
   }
}

void
SoVtkRenderer::updateCamera(SoState *state)
{
	SbVec3f pos, foc, viewUp;

	// Get the Xip camera settings
	SbViewVolume volume = SoViewVolumeElement::get( state );
	float focalDistance = SoFocalDistanceElement::get( state );

	SbMatrix affine, proj;
	volume.getMatrices(affine, proj);
		
	// Set the camera focal point
	foc[0] = volume.getSightPoint(focalDistance)[0];
	foc[1] = volume.getSightPoint(focalDistance)[1];
	foc[2] = volume.getSightPoint(focalDistance)[2];
	mRen->GetActiveCamera()->SetFocalPoint(foc[0], foc[1], foc[2]);

	// Set the camera position
	pos[0] = volume.getProjectionPoint()[0];
	pos[1] = volume.getProjectionPoint()[1];
	pos[2] = volume.getProjectionPoint()[2];
	mRen->GetActiveCamera()->SetPosition(pos[0], pos[1], pos[2]);

	// Set the camera view up
	viewUp = volume.ulf - volume.llf;
	normalize(viewUp);
	mRen->GetActiveCamera()->SetViewUp(viewUp[0], viewUp[1], viewUp[2]);

	// Set the camera clipping planes
	mRen->GetActiveCamera()->SetClippingRange(volume.getNearDist(), volume.getNearDist() + volume.getDepth());

	// Set the camera projection type
	if (volume.getProjectionType() == SbViewVolume::ORTHOGRAPHIC)
	{
		mRen->GetActiveCamera()->ParallelProjectionOn();
		mRen->GetActiveCamera()->SetParallelScale(volume.getHeight()/2.);
	}
	else
	{
		float f = proj[1][1];
		float view_angle_xip = 2 * atan(1 / f);
		float view_angle_deg =  view_angle_xip * 180 / pi;

		mRen->GetActiveCamera()->ParallelProjectionOff();
		mRen->GetActiveCamera()->SetViewAngle(view_angle_deg);
	}
	
}


////////////// UPDATE METHODS /////////////


void SoVtkRenderer::updateRenderWindowSize(SoState *state)
{
	// Get the viewport information about the xip scene.
	SbViewportRegion viewportRegion = SoViewportRegionElement::get(state);

	float X = viewportRegion.getWindowSize()[0];
	float Y = viewportRegion.getWindowSize()[1];

	float X_beg = viewportRegion.getViewportOrigin()[0];
	float Y_beg = viewportRegion.getViewportOrigin()[1];

	float view_X = viewportRegion.getViewportSize()[0];
	float view_Y = viewportRegion.getViewportSize()[1];

	// Set the viewport of the renderer
	mRen->SetViewport(X_beg,Y_beg,view_X,view_Y);

	// Set the size of the vtkRenderWindow.
	int x = floor(X + 0.5f);
	int y = floor(Y + 0.5f);
	mRenWin->SetSize( x, y);
}


// The stereo mode is not yet handled, to handle it, the VTK camera needs to be reset.
void SoVtkRenderer::updateStereoMode()
{
	if (StereoRender.getValue() == 1)
	{
		mRenWin->StereoCapableWindowOn();

		switch (StereoMode.getValue())
		{
		case SoVtkRenderer::Anaglyph :
		{
			mRenWin->SetStereoTypeToAnaglyph();
		}
		break;
		case SoVtkRenderer::CrystalEyes :
		{
			mRenWin->SetStereoTypeToCrystalEyes();
		}
		break;
		case SoVtkRenderer::Dresden :
		{
			mRenWin->SetStereoTypeToDresden();
		}
		break;
		case SoVtkRenderer::Interlaced :
		{
			mRenWin->SetStereoTypeToInterlaced();
		}
		break;
		case SoVtkRenderer::Left :
		{
			mRenWin->SetStereoTypeToLeft();
		}
		break;
		case SoVtkRenderer::RedBlue :
		{
			mRenWin->SetStereoTypeToRedBlue();
		}
		break;
		case SoVtkRenderer::Right :
		{
			mRenWin->SetStereoTypeToRight();
		}
		break;
		}

		mRenWin->StereoRenderOn();
		this->lastStereo = 1;
	}
	else
	{
		if (this->lastStereo == 1)
		{
			mRenWin->StereoCapableWindowOff();
			mRenWin->StereoRenderOff();
			this->lastStereo = 0;
		}
	}
}

vtkOpenGLRenderer *SoVtkRenderer::getRenderer() const
{
	return mRen;
}

vtkRenderWindow *SoVtkRenderer::getRenderWindow() const
{
	return mRenWin;
}



