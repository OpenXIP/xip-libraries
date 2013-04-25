/*
 *  COPYRIGHT NOTICE.  Copyright (C) 2007 Siemens Corporate Research, 
 *  Inc. ("caBIG(tm) Participant"). The eXtensible Imaging Platform
 *  (XIP) was created with NCI funding and is part of the caBIG(tm) 
 *  initiative. The software subject to this notice and license 
 *  includes both human readable source code form and machine 
 *  readable, binary, object code form (the "caBIG(tm) Software").
 *  
 *  This caBIG(tm) Software License (the "License") is between 
 *  caBIG(tm) Participant and You.  "You (or "Your") shall mean a 
 *  person or an entity, and all other entities that control, are 
 *  controlled by, or are under common control with the entity.  
 *  "Control" for purposes of this definition means (i) the direct or 
 *  indirect power to cause the direction or management of such 
 *  entity, whether by contract or otherwise, or (ii) ownership of 
 *  fifty percent (50%) or more of the outstanding shares, or (iii) 
 *  beneficial ownership of such entity.
 *  
 *  LICENSE.  Provided that You agree to the conditions described 
 *  below, caBIG(tm) Participant grants You a non-exclusive, 
 *  worldwide, perpetual, fully-paid-up, no-charge, irrevocable, 
 *  transferable and royalty-free right and license in its rights in 
 *  the caBIG(tm) Software, including any copyright or patent rights 
 *  therein that may be infringed by the making, using, selling, 
 *  offering for sale, or importing of caBIG(tm) Software, to (i) 
 *  use, install, access, operate, execute, reproduce, copy, modify, 
 *  translate, market, publicly display, publicly perform, and 
 *  prepare derivative works of the caBIG(tm) Software; (ii) make, 
 *  have made, use, practice, sell, and offer for sale, and/or 
 *  otherwise dispose of caBIG(tm) Software (or portions thereof); 
 *  (iii) distribute and have distributed to and by third parties the 
 *  caBIG(tm) Software and any modifications and derivative works 
 *  thereof; and (iv) sublicense the foregoing rights set out in (i), 
 *  (ii) and (iii) to third parties, including the right to license 
 *  such rights to further third parties.  For sake of clarity, and 
 *  not by way of limitation, caBIG(tm) Participant shall have no 
 *  right of accounting or right of payment from You or Your 
 *  sublicensees for the rights granted under this License.  This 
 *  License is granted at no charge to You.  Your downloading, 
 *  copying, modifying, displaying, distributing or use of caBIG(tm) 
 *  Software constitutes acceptance of all of the terms and 
 *  conditions of this Agreement.  If you do not agree to such terms 
 *  and conditions, you have no right to download, copy, modify, 
 *  display, distribute or use the caBIG(tm) Software.
 *  
 *  1.	Your redistributions of the source code for the caBIG(tm) 
 *      Software must retain the above copyright notice, this list 
 *      of conditions and the disclaimer and limitation of 
 *      liability of Article 6 below.  Your redistributions in 
 *      object code form must reproduce the above copyright notice, 
 *      this list of conditions and the disclaimer of Article 6 in 
 *      the documentation and/or other materials provided with the 
 *      distribution, if any.
 *  2.	Your end-user documentation included with the 
 *      redistribution, if any, must include the following 
 *      acknowledgment: "This product includes software developed 
 *      by Siemens Corporate Research Inc."  If You do not include 
 *      such end-user documentation, You shall include this 
 *      acknowledgment in the caBIG(tm) Software itself, wherever 
 *      such third-party acknowledgments normally appear.
 *  3.	You may not use the names "Siemens Corporate Research, 
 *      Inc.", "The National Cancer Institute", "NCI", "Cancer 
 *      Bioinformatics Grid" or "caBIG(tm)" to endorse or promote 
 *      products derived from this caBIG(tm) Software.  This 
 *      License does not authorize You to use any trademarks, 
 *  	service marks, trade names, logos or product names of 
 *      either caBIG(tm) Participant, NCI or caBIG(tm), except as 
 *      required to comply with the terms of this License.
 *  4.	For sake of clarity, and not by way of limitation, You may 
 *      incorporate this caBIG(tm) Software into Your proprietary 
 *      programs and into any third party proprietary programs.  
 *      However, if You incorporate the caBIG(tm) Software into 
 *      third party proprietary programs, You agree that You are 
 *      solely responsible for obtaining any permission from such 
 *      third parties required to incorporate the caBIG(tm) 
 *      Software into such third party proprietary programs and for 
 *      informing Your sublicensees, including without limitation 
 *      Your end-users, of their obligation to secure any required 
 *      permissions from such third parties before incorporating 
 *      the caBIG(tm) Software into such third party proprietary 
 *      software programs.  In the event that You fail to obtain 
 *      such permissions, You agree to indemnify caBIG(tm) 
 *      Participant for any claims against caBIG(tm) Participant by 
 *      such third parties, except to the extent prohibited by law, 
 *      resulting from Your failure to obtain such permissions.
 *  5.	For sake of clarity, and not by way of limitation, You may 
 *      add Your own copyright statement to Your modifications and 
 *      to the derivative works, and You may provide additional or 
 *      different license terms and conditions in Your sublicenses 
 *      of modifications of the caBIG(tm) Software, or any 
 *      derivative works of the caBIG(tm) Software as a whole, 
 *      provided Your use, reproduction, and distribution of the 
 *      Work otherwise complies with the conditions stated in this 
 *      License.
 *  6.	THIS caBIG(tm) SOFTWARE IS PROVIDED "AS IS" AND ANY 
 *      EXPRESSED OR IMPLIED WARRANTIES (INCLUDING, BUT NOT LIMITED 
 *      TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, NON-
 *      INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE) ARE 
 *      DISCLAIMED.  IN NO EVENT SHALL SIEMENS CORPORATE RESEARCH 
 *      INC. OR ITS AFFILIATES BE LIABLE FOR ANY DIRECT, INDIRECT, 
 *      INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
 *      (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE 
 *      GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR 
 *      BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
 *      LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 *      (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT 
 *      OF THE USE OF THIS caBIG(tm) SOFTWARE, EVEN IF ADVISED OF 
 *      THE POSSIBILITY OF SUCH DAMAGE.
 *  
 */

/*!
 * \file SoVtkRenderer.cpp
 *
 * \brief SoVtkRenderer class implementation.
 *
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

#define pi 3.14159265358979323846

SO_NODE_SOURCE( SoVtkRenderer );

SoVtkRenderer::SoVtkRenderer()
{
	SO_NODE_CONSTRUCTOR( SoVtkRenderer );

	mRen = vtkOpenGLRenderer::New();
	mRen->Register(0);
	mRen->SetAllocatedRenderTime(10);

	mRenWin = vtkWin32OpenGLRenderWindow::New();
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

	mRC = 0;
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

	// Update graphics/rendering context
	HGLRC currentContext = ::wglGetCurrentContext();
	if (mRC != currentContext)
	{
		mRC = currentContext;
		if (mRenWin)
		{
			mRenWin->SetDeviceContext(::wglGetCurrentDC());
			mRenWin->SetContextId(currentContext);
			mRenWin->SetSwapBuffers(0);
		}
		mRenWin->OpenGLInit();
	}

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

vtkOpenGLRenderer *
SoVtkRenderer::getRenderer() const
{
	return mRen;
}

vtkWin32OpenGLRenderWindow *
SoVtkRenderer::getRenderWindow() const
{
	return mRenWin;
}