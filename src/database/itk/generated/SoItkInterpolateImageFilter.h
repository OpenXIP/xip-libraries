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

#ifndef SO_ITK_INTERPOLATEIMAGEFILTER_H_
# define SO_ITK_INTERPOLATEIMAGEFILTER_H_

# include <Inventor/fields/SoSFFloat.h>
# include <xip/inventor/itk/SoItkSFDataImage.h>
# include "SoItkImageToImageFilter.h"

class XIPIVITK_API SoItkInterpolateImageFilter : public SoItkImageToImageFilter
{
	SO_ENGINE_HEADER( InterpolateImageFilter );

public:
	SoItkInterpolateImageFilter();

	SoSFFloat Distance;
	SoItkSFDataImage Input1;
	
	static void initClass();

protected:
	~SoItkInterpolateImageFilter();

	virtual bool checkInput();
	virtual void evaluate();

};

#endif // SO_ITK_INTERPOLATEIMAGEFILTER_H_
