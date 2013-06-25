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

#ifndef SOXIPIMAGEEXAMINER_H
#define SOXIPIMAGEEXAMINER_H

#include <xip/inventor/core/SoXipMFDataImage.h>
#include "SoXipImageExaminerBase.h"

class SoXipImageExaminer : public SoXipImageExaminerBase
{
	SO_NODE_HEADER( SoXipImageExaminer );

public:
	SoXipImageExaminer();

	SoXipMFDataImage		images;

	static void initClass();

protected:
	~SoXipImageExaminer();

	virtual unsigned int getNumImages() const;
	virtual unsigned int getNumSlices( unsigned int imageIndex ) const;
	
	void imagesChanged();

	class SoXipDecomposeMFImage*	mDecomposer;
	class SoXipExtractSlice*		mSliceExtractor;

private:
	static void imagesSensorCB( void* userData, SoSensor* );

	SoFieldSensor*			mImagesSensor;

};

#endif	// SOXIPIMAGEEXAMINER_H
