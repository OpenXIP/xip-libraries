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

#include <Inventor/SoType.h>
#include <xip/inventor/core/SoXipDataImage.h>
#include <xip/inventor/core/SbXipImage.h>


XIP_DATA_SOURCE(SoXipDataImage);


void SoXipDataImage::initClass()
{
	XIP_DATA_INIT_CLASS(SoXipDataImage, SoXipData, "SoXipData");
}

SoXipDataImage::SoXipDataImage()
{
	XIP_DATA_CONSTRUCTOR(SoXipDataImage);

	mImage = 0;
}

SoXipDataImage::~SoXipDataImage()
{
	if (mImage)
	{
		delete mImage;
		mImage = 0;
	}
}

SbXipImage *SoXipDataImage::get() const
{
	return mImage;
}

void SoXipDataImage::set(SbXipImage *image)
{
	if (mImage == image) return;

	if (mImage)
	{
		delete mImage;
		mImage = 0;
	}

	mImage = image;

	startNotify();
}

