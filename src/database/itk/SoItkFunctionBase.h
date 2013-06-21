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

#ifndef SO_ITK_FUNCTION_BASE_H_
# define SO_ITK_FUNCTION_BASE_H_

# include <xip/inventor/itk/xipivitk.h>
# include <Inventor/engines/SoSubEngine.h>

class SoItkDataInterpolator;

class SoItkFunctionBase : public SoEngine
{
	SO_ENGINE_ABSTRACT_HEADER( SoItkFunctionBase );

public:
	SoItkFunctionBase();

	static void initClass();
	
	SoEngineOutput Output;		// SoItkSFDataInterpolator

protected:
	~SoItkFunctionBase();

	virtual void evaluate() = 0;

	SoItkDataInterpolator* mOutput;

};

#endif // SO_ITK_FUNCTION_BASE_H_