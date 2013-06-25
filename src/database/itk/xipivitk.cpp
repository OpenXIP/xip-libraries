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
#include <xip/inventor/core/xipivcore.h>

#include <xip/inventor/itk/SoItkSFNodeContainer.h>
#include <xip/inventor/itk/SoItkSFDataArray.h>
#include <xip/inventor/itk/SoItkSFDataMatrix.h>
#include <xip/inventor/itk/SoItkSFDataImage.h>
#include <xip/inventor/itk/SoItkSFDataImageMetric.h>
#include <xip/inventor/itk/SoItkSFDataNeighborhood.h>
#include <xip/inventor/itk/SoItkSFDataTransform.h>
#include <xip/inventor/itk/SoItkSFDataOptimizer.h>
#include <xip/inventor/itk/SoItkSFDataInterpolator.h>
#include <xip/inventor/itk/SoItkSFDataDecorator.h>
#include <xip/inventor/itk/SoItkSFDataPointSet.h>
#include <xip/inventor/itk/SoItkMFDataImage.h>
#include "generated/itkWrapInit.h"

#include "SoItkConvertItkImageToXipImage.h"
#include "SoItkConvertXipImageToItkImage.h"
#include "SoItkConvertItkPointSetToMFVec3f.h"

#include "SoItkImportImageFilter.h"
#include "SoItkImageFileReader.h"
#include "SoItkImageFileWriter.h"

// Fast Marching is done manually because we have a problem here:
// ITK filters can only be instantiated with a certain template
// configuration. The Fast Marching can be used without any input
// images and produce an output image. But what we have now is
// output type is deduced from the input type if not specified
// differently in the XML. So If no input are given by the user,
// what output do we instantiate ?
#include "SoItkFastMarchingImageFilter.h"

#include "SoItkSeedImage.h"
#include "SoItkArray.h"
#include "SoItkMatrix.h"
#include "SoItkPointSet.h"
#include "SoItkVectorImage.h"

#include "SoItkImageToImageMetric.h"
#include "SoItkMeanSquaresImageToImageMetric.h"

#include "SoItkNeighborhood.h"
#include "SoItkBinaryBallStructuringElement.h"
#include "SoItkBinaryCrossStructuringElement.h"

#include "SoItkOptimizer.h"
#include "SoItkNonLinearOptimizer.h"
#include "SoItkSingleValuedNonLinearOptimizer.h"
#include "SoItkRegularStepGradientDescentBaseOptimizer.h"
#include "SoItkRegularStepGradientDescentOptimizer.h"

#include "SoItkFunctionBase.h"
#include "SoItkImageFunction.h"
#include "SoItkInterpolateImageFunction.h"
#include "SoItkLinearInterpolateImageFunction.h"

#include "SoItkTransform.h"
#include "SoItkMatrixOffsetTransformBase.h"
#include "SoItkRigid2DTransform.h"
#include "SoItkCenteredRigid2DTransform.h"

#include "SoItkImageRegistrationMethod.h"

#include "SoItkNodeContainer.h"

#include "SoItkComposeMFDataImage.h"

int XIPIVITK_API xipivitk_init()
{
	static bool isInit = false;
	if(isInit)
		return 1;
	isInit = true;

	xipivcore_init();

	// Data Objects
	SoItkDataArray::initClass();
	SoItkDataMatrix::initClass();
	SoItkDataImage::initClass();
	SoItkDataImageMetric::initClass();
    SoItkDataNeighborhood::initClass();
	SoItkDataTransform::initClass();
	SoItkDataOptimizer::initClass();
	SoItkDataInterpolator::initClass();
	SoItkDataDecorator::initClass();
	SoItkDataPointSet::initClass();
	
	// Data Fields
	SoItkSFDataArray::initClass();
	SoItkSFDataMatrix::initClass();
	SoItkSFDataImage::initClass();
	SoItkSFDataImageMetric::initClass();
    SoItkSFDataNeighborhood::initClass();
	SoItkSFDataTransform::initClass();
	SoItkSFDataOptimizer::initClass();
	SoItkSFDataInterpolator::initClass();
	SoItkSFDataDecorator::initClass();
	SoItkSFDataPointSet::initClass();
	SoItkMFDataImage::initClass();

	// Fields
	SoItkSFNodeContainer::initClass();
	
	// Utilities	
	SoItkImportImageFilter::initClass();
	SoItkImageFileReader::initClass();
	SoItkImageFileWriter::initClass();

	SoItkSeedImage::initClass();
	SoItkArray::initClass();
	SoItkMatrix::initClass();
	SoItkPointSet::initClass();
	SoItkVectorImage::initClass();

	SoItkImageToImageMetric::initClass();
	SoItkMeanSquaresImageToImageMetric::initClass();

	SoItkOptimizer::initClass();
	SoItkNonLinearOptimizer::initClass();
	SoItkSingleValuedNonLinearOptimizer::initClass();
	SoItkRegularStepGradientDescentBaseOptimizer::initClass();
	SoItkRegularStepGradientDescentOptimizer::initClass();

	SoItkFunctionBase::initClass();
	SoItkImageFunction::initClass();
	SoItkInterpolateImageFunction::initClass();
	SoItkLinearInterpolateImageFunction::initClass();

	SoItkTransform::initClass();
	SoItkMatrixOffsetTransformBase::initClass();
	SoItkRigid2DTransform::initClass();
	SoItkCenteredRigid2DTransform::initClass();

	SoItkNeighborhood::initClass();
	SoItkBinaryBallStructuringElement::initClass();
	SoItkBinaryCrossStructuringElement::initClass();

	SoItkNodeContainer::initClass();

	SoItkComposeMFDataImage::initClass();

	// Converters
	SoItkConvertItkImageToXipImage::initClass();
	SoItkConvertXipImageToItkImage::initClass();
	SoItkConvertItkPointSetToMFVec3f::initClass();

	// Wrapped Filters 
	itkWrapInit();

	SoItkImageRegistrationMethod::initClass();
	SoItkFastMarchingImageFilter::initClass();
	
	return 1;
}

#ifdef WIN32
BOOL APIENTRY DllMain(HANDLE, DWORD reason, LPVOID)
{
	if ( reason == DLL_PROCESS_ATTACH )
		xipivitk_init();

	return TRUE;
}

#else //UNIX

static int initted = FALSE;    // a little protection--probably unnecessary
void __attribute__ ((constructor)) _init(void)// don't write this if DllMain is to be used
{

	int err;



	xipivitk_init();


	initted = TRUE;
	//return 0;
}

void __attribute__ ((destructor)) _fini(void)
{
   //printf ("fini print.\n");
}

//forcing initialization through static member (as workaround)
static const bool initMe = xipivitk_init();


#endif //WIN32
