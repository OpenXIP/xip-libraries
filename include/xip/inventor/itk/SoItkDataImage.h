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
#ifndef SO_ITK_DATA_IMAGE_H_
# define SO_ITK_DATA_IMAGE_H_

# include <xip/inventor/core/SoXipData.h>
# include <xip/inventor/core/SoXipSubData.h>
# include <xip/inventor/itk/xipivitk.h>

class XIPIVITK_API SoItkDataImage : public SoXipData
{
	XIP_DATA_HEADER( SoItkDataImage );

public:
	enum DataType
	{
		UNDEFINED,
		BOOL,
		UNSIGNED_SHORT,
		FLOAT,
		SHORT,
		UNSIGNED_CHAR
	};

	enum ComponentLayoutType
	{
		LUMINANCE,
  		RGB,
		RGBA,
		VECTOR,
		COV_VECTOR
	};

public:
	SoItkDataImage();

	SoItkDataImage( DataType type,
		unsigned int numDimension,
		const SbMatrix& modelMatrix = SbMatrix::identity() );

	SoItkDataImage( DataType type,
		ComponentLayoutType componentLayoutType,
		unsigned int numDimension,
		const SbMatrix& modelMatrix = SbMatrix::identity() );

	SoItkDataImage( const SoItkDataImage& other );

	void setPointer( const void* image );

	void* getPointer() const;

	DataType getType() const;

	ComponentLayoutType getComponentLayoutType() const;

	unsigned int getDimension( unsigned int i ) const;

	unsigned int getNumDimension() const;

	const SbMatrix& getModelMatrix() const;

	static void initClass();

protected:
	~SoItkDataImage();

	/// A pointer to the itkImage
	void*					mItkImage;		

	/// The type of the internal data buffer
	DataType				mDataType;		

	/// The component layout type of each image value
	ComponentLayoutType		mComponentLayoutType;		

	/// The number of dimensions
	unsigned int			mNumDimension;	

	/// Model matrix
	SbMatrix				mModelMatrix;
		

};

#endif // SO_ITK_DATA_IMAGE_H_
