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
#include "SoVtkConvertXipImageToVtkAlgorithmOutput.h"

#include "vtkImageImport.h"
#include "vtkAlgorithmOutput.h"
#include "vtkImageViewer.h"

#include <Inventor/SoDB.h>
#include "SoVtkUtils.h"

SO_ENGINE_SOURCE( SoVtkConvertXipImageToVtkAlgorithmOutput );

SoVtkConvertXipImageToVtkAlgorithmOutput::SoVtkConvertXipImageToVtkAlgorithmOutput()
{
	SO_ENGINE_CONSTRUCTOR( SoVtkConvertXipImageToVtkAlgorithmOutput );

	// Inputs
	SO_ENGINE_ADD_INPUT( Input, (0) );

	// Outputs
	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mAlgorithmOutput = 0;
	mFlip = 0;
}

void
SoVtkConvertXipImageToVtkAlgorithmOutput::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkConvertXipImageToVtkAlgorithmOutput, SoFieldConverter, "SoFieldConverter" );

	SoDB::addConverter( SoXipSFDataImage::getClassTypeId(),
		      SoSFVtkAlgorithmOutput::getClassTypeId(),
		      getClassTypeId() );
}

SoVtkConvertXipImageToVtkAlgorithmOutput::~SoVtkConvertXipImageToVtkAlgorithmOutput()
{
	if( mAlgorithmOutput )
	{
		mAlgorithmOutput->unref();
		mAlgorithmOutput = 0;
	}
	if (mFlip)
	{
		mFlip->Delete();
		mFlip = 0;
	}
}

void
SoVtkConvertXipImageToVtkAlgorithmOutput::evaluate()
{
	if( mAlgorithmOutput )
	{
		mAlgorithmOutput->unref();
		mAlgorithmOutput = 0;
		SO_ENGINE_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput, setValue(0) );
	}

	SoXipDataImage* xipDataImage = Input.getValue();
	if( !xipDataImage )
		return ;

	SbXipImage *xipImage = xipDataImage->get();
	if( !xipImage )
		return ;

	try
	{

		vtkImageImport *importer = vtkImageImport::New();
		importer->Register(0);

		// Get the number of image components
		switch (xipImage->getComponentLayoutType())
		{
			case SbXipImage::LUMINANCE:
				importer->SetNumberOfScalarComponents(1);
			break;
			case SbXipImage::LUMINANCE_ALPHA:
				importer->SetNumberOfScalarComponents(2);
			break;
			case SbXipImage::RGB:
				importer->SetNumberOfScalarComponents(3);
			break;
			case SbXipImage::RGBA:
				importer->SetNumberOfScalarComponents(4);
			break;
			default: SoDebugError::post( __FILE__, "Image type not supported by converter." );
		}

		// Get the dimensions
		SbXipImageDimensions dimensions = xipImage->getDimStored();

		// Get the spacing
		SbMatrix matrix = xipImage->getModelMatrix();

		double x_spacing = matrix[0][0] / dimensions[0];
		double y_spacing = matrix[1][1] / dimensions[1];
		double z_spacing = matrix[2][2] / dimensions[2];

		importer->SetDataSpacing(x_spacing,y_spacing,z_spacing);

		// Set the extent according to the dimensions
		if( dimensions[2] > 1 )
			importer->SetWholeExtent(1,dimensions[0],1,dimensions[1],1,dimensions[2]);
		else
			importer->SetWholeExtent(1,dimensions[0],1,dimensions[1],0,0);

		// Set scalar type and data pointer
		switch (xipImage->getType())
		{
			case SbXipImage::UNSIGNED_BYTE :
			{
				importer->SetDataScalarTypeToUnsignedChar();
				unsigned char* pixelBuffer = (unsigned char *) xipImage->refBufferPtr();
				importer->SetImportVoidPointer(pixelBuffer);
			}
			break;
			case SbXipImage::BYTE :
			{
				SoDebugError::post( __FILE__, "Converter cannot convert signed byte/char" );
				importer->Delete();
				return ;
			}
			break;
			case SbXipImage::UNSIGNED_SHORT :
			{
				importer->SetDataScalarTypeToUnsignedShort();
				unsigned short* pixelBuffer = (unsigned short *) xipImage->refBufferPtr();
				importer->SetImportVoidPointer(pixelBuffer);
			}
			break;
			case SbXipImage::SHORT :
			{
				importer->SetDataScalarTypeToShort();
				short* pixelBuffer = (short *) xipImage->refBufferPtr();
				importer->SetImportVoidPointer(pixelBuffer);
			}
			break;
			case SbXipImage::UNSIGNED_INT :
			{
				SoDebugError::post( __FILE__, "Converter cannot convert unsigned int" );
				importer->Delete();
				return ;
			}
			break;
			case SbXipImage::INT :
			{
				importer->SetDataScalarTypeToInt();
				int* pixelBuffer = (int *) xipImage->refBufferPtr();
				importer->SetImportVoidPointer(pixelBuffer);
			}
			break;
			case SbXipImage::FLOAT :
			{
				importer->SetDataScalarTypeToFloat();
				float* pixelBuffer = (float *) xipImage->refBufferPtr();
				importer->SetImportVoidPointer(pixelBuffer);
			}
			break;
			case SbXipImage::DOUBLE :
			{
				importer->SetDataScalarTypeToDouble();
				double* pixelBuffer = (double *) xipImage->refBufferPtr();
				importer->SetImportVoidPointer(pixelBuffer);
			}	
			break;
    }

	xipImage->unrefBufferPtr();

    importer->SetDataExtentToWholeExtent();
    mAlgorithmOutput = new SoVtkAlgorithmOutput();
    mAlgorithmOutput->ref();


    // Flip the image, since rad image begins at the upper-left corner
    // of the image, and the vtk one begins at the lower-left one.
    if (!mFlip)
		mFlip = vtkImageFlip::New();
    mFlip->SetInputConnection(importer->GetOutputPort());
    mFlip->SetFilteredAxis(1);
    mFlip->GetOutputPort()->Register(0);

    mAlgorithmOutput->setPointer(mFlip->GetOutputPort());

    importer->Delete();
  }
  catch(...)
  {
    SoDebugError::post( __FILE__, "Unknown exception" );
    return ;
  }

  SO_ENGINE_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput, setValue( mAlgorithmOutput ) );
}

SoField*
SoVtkConvertXipImageToVtkAlgorithmOutput::getInput( SoType type )
{
  if( type == SoXipSFDataImage::getClassTypeId() )
  {
    return &Input;
  }

  SoDebugError::post( __FILE__, "SoVtkConvertXipImageToVtkAlgorithmOutput::getInput() : unresolved input" );
  return 0;
}

SoEngineOutput*
SoVtkConvertXipImageToVtkAlgorithmOutput::getOutput( SoType type )
{
  if( type == SoSFVtkAlgorithmOutput::getClassTypeId() )
  {
    return &OutputPort;
  }

  SoDebugError::post( __FILE__, "SoVtkConvertXipImageToVtkAlgorithmOutput::getOutput() : unresolved output" );
  return 0;
}


