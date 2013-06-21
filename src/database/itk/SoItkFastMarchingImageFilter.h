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

#ifndef SO_ITK_FASTMARCHINGIMAGEFILTER_H_
# define SO_ITK_FASTMARCHINGIMAGEFILTER_H_

# include <Inventor/fields/SoMFFloat.h>
# include <Inventor/fields/SoMFInt32.h>
# include <Inventor/fields/SoSFBool.h>
# include <Inventor/fields/SoSFFloat.h>
# include <Inventor/fields/SoSFEnum.h>
# include <Inventor/fields/SoSFShort.h>
# include <Inventor/fields/SoSFMatrix.h>
# include <xip/inventor/itk/SoItkSFNodeContainer.h>
# include "generated/SoItkImageToImageFilter.h"

class SoItkFastMarchingImageFilter : public SoItkImageToImageFilter
{
	SO_ENGINE_HEADER( FastMarchingImageFilter );

public:
	enum OutputPixelTypeEnum
	{
		FLOAT,
		UNSIGNED_SHORT
	};

	SoItkFastMarchingImageFilter();

	SoSFEnum OutputPixelType;
	SoSFShort Dimension;
	SoSFMatrix ModelMatrix;

	SoSFFloat NormalizationFactor;
	SoMFInt32 OutputRegion;
	SoSFFloat OutputSpacing;
	SoMFFloat OutputOrigin;
	SoSFBool CollectPoints;
	SoItkSFNodeContainer TrialPoints;
	SoItkSFNodeContainer AlivePoints;
	SoSFBool OverrideOutputInformation;
	SoMFInt32 OutputSize;
	SoSFFloat StoppingValue;
	SoSFFloat SpeedConstant;
	
	static void initClass();

protected:
	~SoItkFastMarchingImageFilter();

	virtual bool checkInput();
	virtual void evaluate();

};

#endif // SO_ITK_FASTMARCHINGIMAGEFILTER_H_
