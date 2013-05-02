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
* \author Sylvain Jaume (Siemens Corporate Research), Francois Huguet
*/

#include <xip/system/standard.h>
#include <stdlib.h>

#include <xip/inventor/core/xipivcore.h>

// Converter
#include "SoVtkConvertXipImageToVtkAlgorithmOutput.h"

// Useful class
#include "SoVtkImageViewer2.h"

// Data classes
#include "xip/inventor/vtk/SoVtkAlgorithmOutput.h"
#include "xip/inventor/vtk/SoSFVtkAlgorithmOutput.h"
#include "xip/inventor/vtk/SoVtkObject.h"
#include "xip/inventor/vtk/SoSFVtkObject.h"

// Rendering classes
#include "SoVtkRenderer.h"
#include "SoVtkActor.h"
#include "SoVtkLODActor.h"
#include "SoVtkAssembly.h"
#include "SoVtkActor2D.h"
#include "SoVtkImageActor.h"
#include "SoVtkVolume.h"

// Generated classes
//#include "SoVtk3DSImporter.h"
#include "SoVtkAppendPolyData.h"
#include "SoVtkAppendFilter.h"
#include "SoVtkArrowSource.h"
#include "SoVtkAxes.h"
//#include "SoVtkBox.h"
#include "SoVtkBMPReader.h"
#include "SoVtkButterflySubdivisionFilter.h"
#include "SoVtkBYUReader.h"
#include "SoVtkClipPolyData.h"
#include "SoVtkColorTransferFunction.h"
//#include "SoVtkCone.h"
#include "SoVtkConeSource.h"
#include "SoVtkConnectivityFilter.h"
#include "SoVtkContourFilter.h"
#include "SoVtkCutter.h"
#include "SoVtkDelaunay2D.h"
#include "SoVtkDiskSource.h"
#include "SoVtkDICOMImageReader.h"
#include "SoVtkExtractGrid.h"
#include "SoVtkGlyph3D.h"
#include "SoVtkImageReader2.h"
#include "SoVtkLookupTable.h"
#include "SoVtkMatrix4x4.h"
#include "SoVtkOutlineFilter.h"
#include "SoVtkPiecewiseFunction.h"
#include "SoVtkPlane.h"
#include "SoVtkPLOT3DReader.h"
#include "SoVtkPolyData.h"
#include "SoVtkPolyDataMapper.h"
#include "SoVtkPolyDataNormals.h"
#include "SoVtkProperty.h"
#include "SoVtkRungeKutta4.h"
#include "SoVtkSphereSource.h"
#include "SoVtkStreamLine.h"
#include "SoVtkStripper.h"
#include "SoVtkStructuredGridGeometryFilter.h"
#include "SoVtkStructuredGridOutlineFilter.h"
#include "SoVtkStructuredGridReader.h"
#include "SoVtkStructuredPointsReader.h"
#include "SoVtkTransform.h"
#include "SoVtkTriangleFilter.h"
#include "SoVtkTubeFilter.h"
#include "SoVtkVolume16Reader.h"
#include "SoVtkVolumeProperty.h"
#include "SoVtkVolumeRayCastCompositeFunction.h"
#include "SoVtkVolumeRayCastIsosurfaceFunction.h"
#include "SoVtkVolumeRayCastMapper.h"
#include "SoVtkVolumeRayCastMIPFunction.h"
#include "SoVtkVolumeTextureMapper2D.h"

#define SAFE_INIT_CLASS(className) \
className::initClass(); \
if( className::getClassTypeId().isBad() ) \
{ \
SoDebugError::post( __FILE__, "Could not init class '#className'" ); \
}

int xipivvtk_init()
{
	static bool isInit = false;
	if(isInit)
		return 1;
	isInit = true;

	xipivcore_init();

	// Converter
	SAFE_INIT_CLASS(SoVtkConvertXipImageToVtkAlgorithmOutput);

	// Useful class
	SAFE_INIT_CLASS(SoVtkImageViewer2);

	// Data classes
	SAFE_INIT_CLASS(SoVtkObject);
	SAFE_INIT_CLASS(SoSFVtkObject);
	SAFE_INIT_CLASS(SoVtkAlgorithmOutput);
	SAFE_INIT_CLASS(SoSFVtkAlgorithmOutput);

	// Rendering classes
	SAFE_INIT_CLASS(SoVtkRenderer);
	SAFE_INIT_CLASS(SoVtkActor);
	SAFE_INIT_CLASS(SoVtkLODActor);
	SAFE_INIT_CLASS(SoVtkActor2D);
	SAFE_INIT_CLASS(SoVtkImageActor);
	SAFE_INIT_CLASS(SoVtkVolume);
	SAFE_INIT_CLASS(SoVtkAssembly);

	// Generated classes
	//SAFE_INIT_CLASS(SoVtk3DSImporter);
	//SAFE_INIT_CLASS(SoVtkAppendPolyData);
	//SAFE_INIT_CLASS(SoVtkAppendFilter);
	SAFE_INIT_CLASS(SoVtkArrowSource);
	SAFE_INIT_CLASS(SoVtkAxes);
	//SAFE_INIT_CLASS(SoVtkBox);
	SAFE_INIT_CLASS(SoVtkBMPReader);
	SAFE_INIT_CLASS(SoVtkButterflySubdivisionFilter);
	SAFE_INIT_CLASS(SoVtkBYUReader);
	SAFE_INIT_CLASS(SoVtkClipPolyData);
	SAFE_INIT_CLASS(SoVtkColorTransferFunction);
	//SAFE_INIT_CLASS(SoVtkCone);
	SAFE_INIT_CLASS(SoVtkConeSource);
	SAFE_INIT_CLASS(SoVtkConnectivityFilter);
	SAFE_INIT_CLASS(SoVtkContourFilter);
	SAFE_INIT_CLASS(SoVtkCutter);
	SAFE_INIT_CLASS(SoVtkDelaunay2D);
	SAFE_INIT_CLASS(SoVtkDiskSource);
	SAFE_INIT_CLASS(SoVtkDICOMImageReader);
	SAFE_INIT_CLASS(SoVtkExtractGrid);
	SAFE_INIT_CLASS(SoVtkGlyph3D);
	SAFE_INIT_CLASS(SoVtkImageReader2);
	SAFE_INIT_CLASS(SoVtkLookupTable);
	SAFE_INIT_CLASS(SoVtkMatrix4x4);
	SAFE_INIT_CLASS(SoVtkOutlineFilter);
	SAFE_INIT_CLASS(SoVtkPiecewiseFunction);
	SAFE_INIT_CLASS(SoVtkPlane);
	SAFE_INIT_CLASS(SoVtkPLOT3DReader);
	SAFE_INIT_CLASS(SoVtkPolyData);
	SAFE_INIT_CLASS(SoVtkPolyDataMapper);
	SAFE_INIT_CLASS(SoVtkPolyDataNormals);
	SAFE_INIT_CLASS(SoVtkProperty);
	SAFE_INIT_CLASS(SoVtkRungeKutta4);
	SAFE_INIT_CLASS(SoVtkSphereSource);
	SAFE_INIT_CLASS(SoVtkStreamLine);
	SAFE_INIT_CLASS(SoVtkStripper);
	SAFE_INIT_CLASS(SoVtkStructuredGridGeometryFilter);
	SAFE_INIT_CLASS(SoVtkStructuredGridOutlineFilter);
	SAFE_INIT_CLASS(SoVtkStructuredGridReader);
	SAFE_INIT_CLASS(SoVtkStructuredPointsReader);
	SAFE_INIT_CLASS(SoVtkTransform);
	SAFE_INIT_CLASS(SoVtkTriangleFilter);
	SAFE_INIT_CLASS(SoVtkTubeFilter);
	SAFE_INIT_CLASS(SoVtkVolume16Reader);
	SAFE_INIT_CLASS(SoVtkVolumeProperty);
	SAFE_INIT_CLASS(SoVtkVolumeRayCastCompositeFunction);
	SAFE_INIT_CLASS(SoVtkVolumeRayCastIsosurfaceFunction);
	SAFE_INIT_CLASS(SoVtkVolumeRayCastMapper);
	SAFE_INIT_CLASS(SoVtkVolumeRayCastMIPFunction);
	SAFE_INIT_CLASS(SoVtkVolumeTextureMapper2D);

	return 1;
}

#ifdef WIN32

BOOL APIENTRY DllMain(HANDLE, DWORD reason, LPVOID)
{
	if ( reason == DLL_PROCESS_ATTACH )
		xipivvtk_init();

	return TRUE;
}

#else //UNIX

static int initted = FALSE;    // a little protection--probably unnecessary
void __attribute__ ((constructor)) _init(void)// don't write this if DllMain is to be used
{

	int err;



	xipivvtk_init();


	initted = TRUE;
	//return 0;
}

void __attribute__ ((destructor)) _fini(void)
{
   //printf ("fini print.\n");
}

//forcing initialization through static member (as workaround)
static const bool initMe = xipivvtk_init();


#endif //WIN32
