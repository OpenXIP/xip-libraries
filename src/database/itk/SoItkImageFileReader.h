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

/* author Sylvain Jaume, Julien Gein */

#ifndef SO_ITK_IMAGE_FILE_READER_H_
# define SO_ITK_IMAGE_FILE_READER_H_

# include <xip/inventor/itk/xipivitk.h>
# include <Inventor/engines/SoSubEngine.h>
# include <Inventor/fields/SoSFEnum.h>
# include <Inventor/fields/SoSFString.h>

class SoItkDataImage;

class SoItkImageFileReader : public SoEngine
{	
	SO_ENGINE_HEADER( SoItkImageFileReader );

public:
	enum DataType
	{
		FLOAT,
		UNSIGNED_SHORT,
		SHORT,
		UNSIGNED_CHAR
	};

	enum DimensionEnum
	{
		TWO,
		THREE
	};

	enum ComponentLayoutType
	{
		LUMINANCE,
		RGB,
		RGBA
	};

	SoItkImageFileReader();

	SoSFString		File;
	SoSFEnum		Type;
	SoSFEnum		Dimension;
	SoSFEnum		ComponentLayout;

	SoEngineOutput	Output;			// SoItkSFDataImage
	SoEngineOutput	Dimensions;		// SoMFFloat

	static void initClass();

protected:
	~SoItkImageFileReader();
	
	virtual void evaluate();

	SoItkDataImage* mOutput;
	
};

#endif // SO_ITK_IMAGE_FILE_READER_H_