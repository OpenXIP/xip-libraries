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

#ifndef SO_ITK_TRANSFORM_H_
# define SO_ITK_TRANSFORM_H_

# include <xip/inventor/itk/xipivitk.h>
# include <Inventor/engines/SoSubEngine.h>

class SoItkDataTransform;

class SoItkTransform : public SoEngine
{
	SO_ENGINE_ABSTRACT_HEADER( SoItkTransform );

public:
	SoItkTransform();

	static void initClass();

	SoMFFloat Parameters;
	
	SoEngineOutput NumberOfParameters;	// SoSFFloat
	SoEngineOutput OutputParameters;	// SoMFFloat
	SoEngineOutput Output;				// SoItkSFDataTransform

protected:
	~SoItkTransform();

	virtual void evaluate() = 0;

	SoItkDataTransform* mOutput;

};

#endif // SO_ITK_TRANSFORM_H_
