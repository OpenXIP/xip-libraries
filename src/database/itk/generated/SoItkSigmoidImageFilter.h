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

#ifndef SO_ITK_SIGMOIDIMAGEFILTER_H_
# define SO_ITK_SIGMOIDIMAGEFILTER_H_

# include <Inventor/fields/SoSFFloat.h>
# include "SoItkUnaryFunctorImageFilter.h"

class XIPIVITK_API SoItkSigmoidImageFilter : public SoItkUnaryFunctorImageFilter
{
	SO_ENGINE_HEADER( SigmoidImageFilter );

public:
	SoItkSigmoidImageFilter();

	SoSFFloat Beta;
	SoSFFloat OutputMaximum;
	SoSFFloat OutputMinimum;
	SoSFFloat Alpha;
	
	static void initClass();

protected:
	~SoItkSigmoidImageFilter();

	virtual bool checkInput();
	virtual void evaluate();

};

#endif // SO_ITK_SIGMOIDIMAGEFILTER_H_
