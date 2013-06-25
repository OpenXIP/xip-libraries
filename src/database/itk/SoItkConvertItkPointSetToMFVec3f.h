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
#ifndef SO_ITK_CONVERT_ITK_POINTSET_TO_MFVEC3F_H_
# define SO_ITK_CONVERT_ITK_POINTSET_TO_MFVEC3F_H_

# include <Inventor/engines/SoFieldConverter.h>
# include <xip/inventor/itk/SoItkSFDataPointSet.h>

class SoItkConvertItkPointSetToMFVec3f : public SoFieldConverter
{
	SO_ENGINE_HEADER( SoItkConvertItkPointSetToMFVec3f );

public:

	SoItkConvertItkPointSetToMFVec3f();
		// Constructor

	static void initClass();
		// Open Inventor class' initialization
	
	SoItkSFDataPointSet Input;
		// Input Image

	SoEngineOutput Output; // SoItkSFDataImage
		// Output Image

private:

	~SoItkConvertItkPointSetToMFVec3f();
		// Destructor

	virtual void evaluate();
		// Evaluation method

	virtual SoField* getInput( SoType type );
		// Returns the input defined by the given type

	virtual SoEngineOutput* getOutput( SoType type );
		// Returns the output defined by the given type

};

#endif /// SO_ITK_CONVERT_ITK_POINTSET_TO_MFVEC3F_H_
