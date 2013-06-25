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
#ifndef SO_ITK_CONVERT_MF_DICOM_TO_ITK_IMAGE_H_
# define SO_ITK_CONVERT_MF_DICOM_TO_ITK_IMAGE_H_

# include <Inventor/engines/SoFieldConverter.h>
# include <xip/inventor/core/SoRadMFDataDicom.h>
# include <xip/inventor/itk/SoItkSFDataImage.h>

class SoItkConvertMFDicomToItkImage : public SoFieldConverter
{
	SO_ENGINE_HEADER( SoItkConvertMFDicomToItkImage );

public:

	SoItkConvertMFDicomToItkImage();
		// Constructor

	static void initClass();
		// Open Inventor class' initialization
	
	SoRadMFDataDicom input;
		// Input Image

	SoEngineOutput output; // SoItkSFDataImage
		// Output Image

private:

	~SoItkConvertMFDicomToItkImage();
		// Destructor

	virtual void evaluate();
		// Evaluation method

	virtual SoField* getInput( SoType type );
		// Returns the input defined by the given type

	virtual SoEngineOutput* getOutput( SoType type );
		// Returns the output defined by the given type

protected:

	SoItkDataImage* mItkImage;
		// Data wrapper for the ITK image class

	void* mPixelBuffer;
		//
    unsigned int mBufferSize;
		//

};

#endif /// SO_ITK_CONVERT_MF_DICOM_TO_ITK_IMAGE_H_
