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
 
 
# include "SoVtkFixedPointRayCastImage.h"
# include "SoVtkUtils.h"



SO_ENGINE_SOURCE( SoVtkFixedPointRayCastImage )

SoVtkFixedPointRayCastImage::SoVtkFixedPointRayCastImage()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkFixedPointRayCastImage);

	mObject = vtkFixedPointRayCastImage::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkFixedPointRayCastImage *aFixedPointRayCastImage = vtkFixedPointRayCastImage::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(ImageInUseSize, (0,0));

	y = (int *) aFixedPointRayCastImage->GetImageInUseSize();
	ImageInUseSize.setValue((float) y[0],(float) y[1]);

	SO_ENGINE_ADD_INPUT(ImageViewportSize, (0,0));

	y = (int *) aFixedPointRayCastImage->GetImageViewportSize();
	ImageViewportSize.setValue((float) y[0],(float) y[1]);

	SO_ENGINE_ADD_INPUT(ImageSampleDistance, (0));
	ImageSampleDistance.setValue(aFixedPointRayCastImage->GetImageSampleDistance());

	SO_ENGINE_ADD_INPUT(ZBufferSize, (0,0));

	y = (int *) aFixedPointRayCastImage->GetZBufferSize();
	ZBufferSize.setValue((float) y[0],(float) y[1]);

	SO_ENGINE_ADD_INPUT(UseZBuffer, (0));
	UseZBuffer.setValue(aFixedPointRayCastImage->GetUseZBuffer());

	SO_ENGINE_ADD_INPUT(ImageOrigin, (0,0));

	y = (int *) aFixedPointRayCastImage->GetImageOrigin();
	ImageOrigin.setValue((float) y[0],(float) y[1]);

	SO_ENGINE_ADD_INPUT(ZBufferOrigin, (0,0));

	y = (int *) aFixedPointRayCastImage->GetZBufferOrigin();
	ZBufferOrigin.setValue((float) y[0],(float) y[1]);

	SO_ENGINE_ADD_INPUT(ImageMemorySize, (0,0));

	y = (int *) aFixedPointRayCastImage->GetImageMemorySize();
	ImageMemorySize.setValue((float) y[0],(float) y[1]);

	aFixedPointRayCastImage->Delete();


	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;


	addCalled = 0;
}

SoVtkFixedPointRayCastImage::~SoVtkFixedPointRayCastImage()
{
	// Deletion of the objects if they exist
	if ( mObject )
	{
		mObject->UnRegister(0);
		mObject->Delete();
		mObject = 0;
	}
	

}

void SoVtkFixedPointRayCastImage::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkFixedPointRayCastImage, SoEngine, "Engine" );
}

void SoVtkFixedPointRayCastImage::evaluate()
{
	try
	{
		// Get the input type(s)
		// Deletion of the objects if they exist
		if ( addCalled )
		{
			reset();
			addCalled = 0;
		}

		mOutput = new SoVtkObject();
		mOutput->ref();
		mOutput->setPointer( mObject );

	}
	catch(...)
	{
		SoDebugError::post( __FILE__, "Unknown Exception" );
		return;
	}
	SO_ENGINE_OUTPUT( Output, SoSFVtkObject, setValue( mOutput ) );
}


void SoVtkFixedPointRayCastImage::inputChanged(SoField * f)
{
	// Get the ImageInUseSize value
	if ( f == &ImageInUseSize )
		SO_VTK_SET_FIELD_VEC2F( mObject, ImageInUseSize);

	// Get the ImageViewportSize value
	if ( f == &ImageViewportSize )
		SO_VTK_SET_FIELD_VEC2F( mObject, ImageViewportSize);

	// Get the ImageSampleDistance value
	if ( f == &ImageSampleDistance )
		SO_VTK_SET_FIELD_VALUE( mObject, ImageSampleDistance);

	// Get the ZBufferSize value
	if ( f == &ZBufferSize )
		SO_VTK_SET_FIELD_VEC2F( mObject, ZBufferSize);

	// Get the UseZBuffer value
	if ( f == &UseZBuffer )
		SO_VTK_SET_FIELD_VALUE( mObject, UseZBuffer);

	// Get the ImageOrigin value
	if ( f == &ImageOrigin )
		SO_VTK_SET_FIELD_VEC2F( mObject, ImageOrigin);

	// Get the ZBufferOrigin value
	if ( f == &ZBufferOrigin )
		SO_VTK_SET_FIELD_VEC2F( mObject, ZBufferOrigin);

	// Get the ImageMemorySize value
	if ( f == &ImageMemorySize )
		SO_VTK_SET_FIELD_VEC2F( mObject, ImageMemorySize);

}

void SoVtkFixedPointRayCastImage::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkFixedPointRayCastImage::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	// Get the ImageInUseSize value
	
		SO_VTK_SET_FIELD_VEC2F( mObject, ImageInUseSize);

	// Get the ImageViewportSize value
	
		SO_VTK_SET_FIELD_VEC2F( mObject, ImageViewportSize);

	// Get the ImageSampleDistance value
	
		SO_VTK_SET_FIELD_VALUE( mObject, ImageSampleDistance);

	// Get the ZBufferSize value
	
		SO_VTK_SET_FIELD_VEC2F( mObject, ZBufferSize);

	// Get the UseZBuffer value
	
		SO_VTK_SET_FIELD_VALUE( mObject, UseZBuffer);

	// Get the ImageOrigin value
	
		SO_VTK_SET_FIELD_VEC2F( mObject, ImageOrigin);

	// Get the ZBufferOrigin value
	
		SO_VTK_SET_FIELD_VEC2F( mObject, ZBufferOrigin);

	// Get the ImageMemorySize value
	
		SO_VTK_SET_FIELD_VEC2F( mObject, ImageMemorySize);

}
