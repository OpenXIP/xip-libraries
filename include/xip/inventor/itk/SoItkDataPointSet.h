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
#ifndef SO_ITK_DATA_POINTSET_H_
# define SO_ITK_DATA_POINTSET_H_

# include <xip/inventor/core/SoXipData.h>
# include <xip/inventor/core/SoXipSubData.h>
# include <xip/inventor/itk/xipivitk.h>

class XIPIVITK_API SoItkDataPointSet : public SoXipData
{
	XIP_DATA_HEADER( SoItkDataPointSet );

public:
	enum PixelTypeEnum
	{
		UNSIGNED_SHORT,
		FLOAT
	};

	SoItkDataPointSet();
	SoItkDataPointSet( PixelTypeEnum pixelType, unsigned int dimension );
	SoItkDataPointSet( const SoItkDataPointSet& other );

	void setPointer( void* itkPointSet );

	static void initClass();

public:
	void* getPointer() const;
	PixelTypeEnum getPixelType() const;
	unsigned int getDimension() const;

protected:
	~SoItkDataPointSet();

protected:
	void* mItkPointSet;
		// 
	PixelTypeEnum mPixelType;
		//
	unsigned int mDimension;
		//
};

#endif // SO_ITK_DATA_POINTSET_H_
