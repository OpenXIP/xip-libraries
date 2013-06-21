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
#ifndef SO_ITK_DATA_TRANSFORM_H_
# define SO_ITK_DATA_TRANSFORM_H_

# include <xip/inventor/core/SoXipData.h>
# include <xip/inventor/core/SoXipSubData.h>
# include <xip/inventor/itk/xipivitk.h>

class XIPIVITK_API SoItkDataTransform : public SoXipData
{
	XIP_DATA_HEADER( SoItkDataTransform );

public:
	enum pixel_type_t
	{
		UNDEFINED,
		BYTE,
		UNSIGNED_BYTE,
		SHORT,
		UNSIGNED_SHORT,
		INT,
		UNSIGNED_INT,
		FLOAT,
		DOUBLE
	};

public:
	SoItkDataTransform();

	SoItkDataTransform( pixel_type_t mPixelType,
		unsigned int numDimension );

	SoItkDataTransform( const SoItkDataTransform& other );

	void setPointer( void* transform );

	static void initClass();

public:
	pixel_type_t getType() const;

	unsigned int getNumDimension() const;

	void* getPointer() const;

protected:
	~SoItkDataTransform();

protected:
	void* mItkTransform;
		// A pointer to the itkTransform

	pixel_type_t mPixelType;
		// The type of the internal pixel buffer

	unsigned int mNumDimension;
		// The number of dimensions
};

#endif // SO_ITK_DATA_TRANSFORM_H_
