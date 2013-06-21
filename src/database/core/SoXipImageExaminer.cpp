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

#include <xip/inventor/core/SbXipImage.h>
#include <xip/inventor/core/SoXipSFDataImage.h>
#include <xip/inventor/core/SoXipDataImage.h>
#include "SoXipDecomposeMFImage.h"
#include "SoXipExtractSlice.h"
#include "SoXipImageExaminer.h"

SO_NODE_SOURCE( SoXipImageExaminer );

SoXipImageExaminer::SoXipImageExaminer()
{
	SO_NODE_CONSTRUCTOR( SoXipImageExaminer );

	SO_NODE_ADD_FIELD( images, (0) );

	mImagesSensor = new SoFieldSensor( &imagesSensorCB, this );
	mImagesSensor->attach( &images );

	mDecomposer = new SoXipDecomposeMFImage;
	mDecomposer->ref();

	mSliceExtractor = new SoXipExtractSlice;
	mSliceExtractor->ref();

	mDecomposer->input.connectFrom(&images);
	mDecomposer->index.connectFrom(&imageIndex);

	mSliceExtractor->image.connectFrom( &mDecomposer->output );
	mSliceExtractor->sliceIndex.connectFrom( &sliceIndex );

	((SoXipSFDataImage *) mImage->getField(SbName("image")))->connectFrom(
		&mSliceExtractor->output );
}

SoXipImageExaminer::~SoXipImageExaminer()
{
	if( mImagesSensor )
	{
		delete mImagesSensor;
		mImagesSensor = 0;
	}

	if( mDecomposer )
	{
		mDecomposer->unref();
		mDecomposer = 0;
	}

	if( mSliceExtractor )
	{
		mSliceExtractor->unref();
		mSliceExtractor = 0;
	}
}

void SoXipImageExaminer::initClass()
{
	SO_NODE_INIT_CLASS( SoXipImageExaminer, SoXipImageExaminerBase, "SoXipImageExaminerBase" );
}

void SoXipImageExaminer::imagesSensorCB( void* userData, SoSensor* sensor)
{
	((SoXipImageExaminer*) userData)->imagesChanged();
}

void SoXipImageExaminer::imagesChanged()
{
	int numImages = images.getNum();
	if( numImages <= 0 )
	{
		imageIndex.setValue(-1);
		sliceIndex.setValue(-1);
	}
	else
	{
		int prevImageId = imageIndex.getValue();
		int prevSliceId = sliceIndex.getValue();

		if( prevImageId < 0 || prevImageId >= numImages )
			imageIndex.setValue(0);

		int numOfSlices = getNumSlices( imageIndex.getValue() );

		if( prevSliceId < 0 || prevSliceId >= numOfSlices )
			sliceIndex.setValue(0);

		mViewAll = TRUE;
	}
}

unsigned int SoXipImageExaminer::getNumImages() const
{
	return images.getNum();
}

unsigned int SoXipImageExaminer::getNumSlices( unsigned int imageIndex ) const
{
	if( imageIndex < 0 || imageIndex >= getNumImages() )
		return -1;

	SoXipDataImage* imageData = images[ imageIndex ];
	if( !imageData )
		return -1;

	SbXipImage* image = imageData->get();
	if( !image )
		return -1;

	return image->getDimStored()[2];
}
