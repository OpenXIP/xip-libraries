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

#ifndef SO_ITK_RESAMPLEIMAGEFILTER_H_
# define SO_ITK_RESAMPLEIMAGEFILTER_H_

# include <Inventor/fields/SoMFFloat.h>
# include <Inventor/fields/SoMFInt32.h>
# include <Inventor/fields/SoSFBool.h>
# include <Inventor/fields/SoSFFloat.h>
# include <Inventor/fields/SoSFMatrix.h>
# include <xip/inventor/itk/SoItkSFDataTransform.h>
# include "SoItkImageToImageFilter.h"

class XIPIVITK_API SoItkResampleImageFilter : public SoItkImageToImageFilter
{
	SO_ENGINE_HEADER( ResampleImageFilter );

public:
	SoItkResampleImageFilter();

	SoItkSFDataTransform Transform;
	SoSFBool UseReferenceImage;
	SoSFMatrix OutputDirection;
	SoMFInt32 OutputStartIndex;
	SoSFFloat OutputSpacing;
	SoMFFloat OutputOrigin;
	SoMFInt32 Size;
	SoSFFloat DefaultPixelValue;
	
	static void initClass();

protected:
	~SoItkResampleImageFilter();

	virtual bool checkInput();
	virtual void evaluate();

};

#endif // SO_ITK_RESAMPLEIMAGEFILTER_H_
