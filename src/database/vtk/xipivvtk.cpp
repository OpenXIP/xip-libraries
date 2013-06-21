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
