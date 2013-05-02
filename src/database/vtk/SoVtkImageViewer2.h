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
 * \file SoVtkImageViewer2.h
 * \brief XIP wrapping of SoVtkImageViewer2
 * \author Sylvain Jaume (Siemens Corporate Research), Francois Huguet
 */
#ifndef SO_VTK_IMAGEVIEWER2_H
#define SO_VTK_IMAGEVIEWER2_H

#include <Inventor/nodes/SoGroup.h>
#include <Inventor/nodes/SoNode.h>

#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/actions/SoGetBoundingBoxAction.h>

#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFTrigger.h>

#include <Inventor/sensors/SoFieldSensor.h>
#include <Inventor/misc/SoState.h>

#include "xip/inventor/vtk/SoSFVtkAlgorithmOutput.h"
#include "xip/inventor/vtk/SoSFVtkObject.h"

#include <xip/system/GL/gl.h>
#include <xip/system/GL/glu.h>

#include "vtkImageViewer2.h"

#ifdef WIN32
#include "vtkWin32OpenGLRenderWindow.h"
class myRenderWindow : public vtkWin32OpenGLRenderWindow
#elif linux
#include "vtkXOpenGLRenderWindow.h"
class myRenderWindow : public vtkXOpenGLRenderWindow
#elif DARWIN
#include "vtkCocoaRenderWindow.h" //"vtkCarbonRenderWindow.h"
class myRenderWindow : public vtkCocoaRenderWindow //vtkCarbonRenderWindow
#endif
{
public:
  void Render()
  {
  // notify Inventor instead of rendering...
  //SoDebugError::postInfo("myRenderWindow::Render", "called");
  }

  void GLRender()
  {
  // vtk multiplies to the current modelview matrix, therefore set it to identity
  glLoadIdentity();
  // really does render (called by GLRender method of Inventor node)
  vtkRenderWindow::Render();
  }
};

/*!
 * \brief
 * SoVtkImageViewer2 wraps vtkImageViewer2. Displays a 2D image.
 * 
 * From VTK:
 * vtkImageViewer2 is a convenience class for displaying a 2D image. It
 * packages up the functionality found in vtkRenderWindow, vtkRenderer,
 * vtkImageActor and vtkImageMapToWindowLevelColors into a single easy to use
 * class. The image is placed in the 3D scene at a depth based on the
 * z-coordinate of the particular image slice. Each call to
 * Next/PreviousSlice() changes the image data (slice) displayed AND changes
 * the depth of the displayed slice in the 3D scene.
 * 
 * \see
 * SoVtkWin32OpenGLRenderWindow | SoVtkRenderer | SoVtkImageActor 
 */
class SoVtkImageViewer2 : public SoNode
{
	SO_NODE_HEADER(SoVtkImageViewer2);

  /// Orientation Enum.
  enum SliceOrientationEnum
    {
      XY,
      XZ,
      YZ
    };

public :

	/// Constructor
	SoVtkImageViewer2();

	/// Class Initialization
	static void		initClass();

	/// Input connection
	SoSFVtkAlgorithmOutput InputConnection;
	/// Input data
	SoSFVtkObject Input;
	/// Bits used per pixel
	SoSFInt32  BitsUsed;
	/// Window color
	SoSFFloat Window;
	/// Window level
	SoSFFloat Level;
	/// Slice Orientation enumeration.
	SoSFEnum   SliceOrientation;
	/// Slice index
	SoSFInt32	SliceIndex;
	/// Next Slice
	SoSFTrigger	NextSlice;
	/// Previous Slice
	SoSFTrigger	PreviousSlice;

protected :

	/// Destructor
	virtual ~SoVtkImageViewer2();

	/// GLRender
	virtual void	GLRender(SoGLRenderAction *action);

	/// Handle the next slice
	static void	onNextCallback( void* user, SoSensor* sensor );

	/// Go to the next slice
	virtual void	nextSlice();

	/// Handle the previous slice
	static void	onPreviousCallback( void* user, SoSensor* sensor );

	/// Go to the previous slice
	virtual void	previousSlice();

	/// Get RAD camera information and update the VTK camera.
	void		updateCamera(SoState *state);

	void getBoundingBox(SoGetBoundingBoxAction *action);

private:

	/// Slice min
	int mMin;

	/// Slice max
	int mMax;
#ifdef WIN32
	/// Current context
	HGLRC		mRC;
#endif
	/// OpenGL render Window
	myRenderWindow *mRenWin;

	/// Image Viewer
	vtkImageViewer2	*mViewer;

	SoFieldSensor*	mNextSensor;
	SoFieldSensor*	mPreviousSensor;

};

#endif // SO_VTK_IMAGEVIEWER2_H



