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

#ifndef SO_ITK_IMPORT_IMAGE_FILTER_H_
# define SO_ITK_IMPORT_IMAGE_FILTER_H_

# include <xip/inventor/itk/SoItkSFDataImage.h>
# include <Inventor/engines/SoSubEngine.h>
# include <Inventor/fields/SoSFEnum.h>
# include <Inventor/fields/SoSFString.h>
# include <Inventor/fields/SoSFShort.h>

class SoItkDataImage;

class SoItkImportImageFilter : public SoEngine
{	
	SO_ENGINE_HEADER( SoItkImportImageFilter );

public:
	enum OutputPixelTypeEnum
	{
		FLOAT,
		UNSIGNED_SHORT
	};

	SoItkImportImageFilter();

	SoSFString		File;
	SoSFEnum		Type;
	SoSFShort		Width;
	SoSFShort		Height;	

	SoEngineOutput	Output;

	static void initClass();

protected:
	~SoItkImportImageFilter();

	void* loadBuffer();

	virtual void evaluate();

	unsigned short* mPixelBuffer;

	SoItkDataImage* mOutput;		
};

#endif // SO_ITK_IMPORT_IMAGE_FILTER_H_