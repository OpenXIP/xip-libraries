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
 * \file SoVtkImageViewer2.cpp
 * \brief Implementation of the SoVtkImageViewer2 node
 * \author Francois Huguet
 */
#include "SoVtkImageViewer2.h"

#include <Inventor/elements/SoViewVolumeElement.h>
#include <Inventor/elements/SoFocalDistanceElement.h>
#include <Inventor/elements/SoViewportRegionElement.h>
#include <Inventor/elements/SoViewingMatrixElement.h>
#include <Inventor/elements/SoComplexityElement.h>

#include "xip/inventor/vtk/SoVtkAlgorithmOutput.h"
#include "xip/inventor/vtk/SoVtkObject.h"

#include "vtkImageData.h"
#include "vtkImageActor.h"
#include "vtkCamera.h"
#include "vtkRenderer.h"

#define pi 3.14159265358979323846

SO_NODE_SOURCE(SoVtkImageViewer2);

SoVtkImageViewer2::SoVtkImageViewer2()
{
	SO_NODE_CONSTRUCTOR(SoVtkImageViewer2);

	// Initializations
	mViewer = vtkImageViewer2::New();
	mViewer->Register(0);

	mRenWin = new myRenderWindow;
	mRenWin->Register(0);
	// We need to give the viewer the render window from Rad to draw in the same context as Rad
	mViewer->SetRenderWindow(mRenWin);


	SO_NODE_ADD_FIELD( InputConnection  , (0) );
	SO_NODE_ADD_FIELD( Input  , (0) );
	SO_NODE_ADD_FIELD( BitsUsed , (8));
	SO_NODE_ADD_FIELD( Window , (0) );
	SO_NODE_ADD_FIELD( Level , (0) );

    SO_NODE_DEFINE_ENUM_VALUE( SliceOrientationEnum, XY );
    SO_NODE_DEFINE_ENUM_VALUE( SliceOrientationEnum, XZ );
    SO_NODE_DEFINE_ENUM_VALUE( SliceOrientationEnum, YZ );

    SO_NODE_SET_SF_ENUM_TYPE( SliceOrientation, SliceOrientationEnum );
    SO_NODE_ADD_FIELD( SliceOrientation, (XY) );
	
	SO_NODE_ADD_FIELD( SliceIndex , (0) );
	SO_NODE_ADD_FIELD( NextSlice , () );
	SO_NODE_ADD_FIELD( PreviousSlice, () );
	

	mNextSensor = new SoFieldSensor( &onNextCallback, this );
	mNextSensor->attach( &NextSlice );
	mNextSensor->setPriority(0);

	mPreviousSensor = new SoFieldSensor( &onPreviousCallback, this );
	mPreviousSensor->attach( &PreviousSlice );
	mPreviousSensor->setPriority(0);

	mMin = 0;
	mMax = 0;
	mRC = 0;
}

             ////////////// CALLBACKS METHODS /////////////

void
SoVtkImageViewer2::onNextCallback( void* user, SoSensor* sensor )
{
	SoVtkImageViewer2 *viewer = (SoVtkImageViewer2*) user;
	if( viewer )
		viewer->nextSlice();
}

void
SoVtkImageViewer2::nextSlice()
{
	if (SliceIndex.getValue() < mMax)
	{
		SliceIndex.setValue(SliceIndex.getValue()+1);
		mViewer->SetSlice(SliceIndex.getValue());
	}
}

void
SoVtkImageViewer2::onPreviousCallback( void* user, SoSensor* sensor )
{
	SoVtkImageViewer2 *viewer = (SoVtkImageViewer2*) user;
	if( viewer )
		viewer->previousSlice();
}

void
SoVtkImageViewer2::previousSlice()
{
	if (SliceIndex.getValue() > mMin)
	{
		SliceIndex.setValue(SliceIndex.getValue()-1);
		mViewer->SetSlice(SliceIndex.getValue());
	}
}

SoVtkImageViewer2::~SoVtkImageViewer2()
{
	if (mViewer)
	{
		mViewer->UnRegister(0);
		mViewer->Delete();
		mViewer = 0;
	}
}

void SoVtkImageViewer2::initClass()
{
  SO_NODE_INIT_CLASS(SoVtkImageViewer2, SoNode, "Node" );
}

void SoVtkImageViewer2::getBoundingBox(SoGetBoundingBoxAction *action)
{
	SbBox3f	bbox;
	SbVec3f	center;

	if (mViewer->GetImageActor())
	{
		const double *bounds = mViewer->GetImageActor()->GetBounds();
		SbBox3f bbox(bounds[0], bounds[2], bounds[4], bounds[1], bounds[3], bounds[5]);
		action->extendBy(bbox);
		action->setCenter(bbox.getCenter(), FALSE);
	}
}

             ///////////////// GLRENDER /////////////////

void SoVtkImageViewer2::GLRender(SoGLRenderAction *action)
{
	try
	{

		// Get the 2 inputs
		SoVtkObject *inputPtr = Input.getValue();
		
		if (inputPtr && inputPtr->getPointer()->IsA("vtkImageData"))
			mViewer->SetInput(vtkImageData::SafeDownCast(inputPtr->getPointer()));

		SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
		if (inputPortPtr)
			mViewer->SetInputConnection(inputPortPtr->getPointer());


		// Update graphics/rendering context
		HGLRC currentContext = ::wglGetCurrentContext();
		if (mRC != currentContext)
		{
			mRC = currentContext;
			if (mViewer->GetRenderWindow())
			{
				mRenWin->SetDeviceContext(::wglGetCurrentDC());
				mRenWin->SetContextId(currentContext);
				mRenWin->SetSwapBuffers(0);
			}
			mRenWin->OpenGLInit();
		}


		// Get the slice range
		mMin = mViewer->GetSliceMin();
		mMax = mViewer->GetSliceMax();

		// Update the slice orientation
		switch( SliceOrientation.getValue() )
		{
			case XY:
			{
				mViewer->SetSliceOrientationToXY();
			}
			break ;

			case XZ:
			{
				mViewer->SetSliceOrientationToXZ();
			}
			break ;

			case YZ:
			{
				mViewer->SetSliceOrientationToYZ();
			}
			break ;
		}

		// Set the slice index
		mViewer->SetSlice(SliceIndex.getValue());

		// Update the vtk camera according to the inventor state
		updateCamera(action->getState());

		// Render
		mRenWin->GLRender();

	}
	catch(...)
	{
		SoDebugError::post( __FILE__, "Unknown Exception" );
		return ;
	}
}

             ////////////// UPDATE METHODS ////////////

void SoVtkImageViewer2::updateCamera(SoState *state)
{

	// Get the viewport information about the scene.
	SbViewportRegion viewportRegion = SoViewportRegionElement::get(state);

	float X = viewportRegion.getWindowSize()[0];
	float Y = viewportRegion.getWindowSize()[1];

	float X_beg = viewportRegion.getViewportOrigin()[0];
	float Y_beg = viewportRegion.getViewportOrigin()[1];

	float view_X = viewportRegion.getViewportSize()[0];
	float view_Y = viewportRegion.getViewportSize()[1];

	float ratio = viewportRegion.getViewportAspectRatio();

	// Reset Renderer camera
	mViewer->GetRenderer()->ResetCamera();

	// Adjust camera depending if we do a stretch horizontally or vertically
	if (ratio < 1.0)
		mViewer->GetRenderer()->GetActiveCamera()->SetUseHorizontalViewAngle(1);
	else
		mViewer->GetRenderer()->GetActiveCamera()->SetUseHorizontalViewAngle(0);

	// Update the render window level and color
	int value = Window.getValue();
	if (value < 1)
	{
		double Bits = pow(2,(double) BitsUsed.getValue());
		mViewer->SetColorLevel(Level.getValue() * Bits );
		mViewer->SetColorWindow(Window.getValue() * Bits );
	}
	else
	{
		mViewer->SetColorLevel(Level.getValue());
		mViewer->SetColorWindow(Window.getValue());
	}
	
	// Set the viewport of the renderer
	mViewer->GetRenderer()->SetViewport(X_beg,Y_beg,X_beg+view_X,Y_beg+view_Y);

	// Set the size of the vtkRenderWindow.
	int x = floor(X + 0.5f);
	int y = floor(Y + 0.5f);
	mViewer->GetRenderWindow()->SetSize( x, y);
  
}
