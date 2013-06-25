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

#ifndef SO_ITK_ISOLATEDWATERSHEDIMAGEFILTER_H_
# define SO_ITK_ISOLATEDWATERSHEDIMAGEFILTER_H_

# include <Inventor/fields/SoSFFloat.h>
# include <Inventor/fields/SoSFVec3f.h>
# include "SoItkImageToImageFilter.h"

class XIPIVITK_API SoItkIsolatedWatershedImageFilter : public SoItkImageToImageFilter
{
	SO_ENGINE_HEADER( IsolatedWatershedImageFilter );

public:
	SoItkIsolatedWatershedImageFilter();

	SoSFFloat UpperValueLimit;
	SoSFVec3f Seed1;
	SoSFFloat IsolatedValueTolerance;
	SoSFFloat ReplaceValue1;
	SoSFVec3f Seed2;
	SoSFFloat Threshold;
	SoSFFloat ReplaceValue2;
	
	static void initClass();

protected:
	~SoItkIsolatedWatershedImageFilter();

	virtual bool checkInput();
	virtual void evaluate();

};

#endif // SO_ITK_ISOLATEDWATERSHEDIMAGEFILTER_H_
