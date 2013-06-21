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

#ifndef SO_ITK_IMAGE_TO_IMAGE_METRIC_H_
# define SO_ITK_IMAGE_TO_IMAGE_METRIC_H_

# include <xip/inventor/itk/xipivitk.h>
# include <xip/inventor/itk/SoItkSFDataImage.h>
# include <xip/inventor/itk/SoItkSFDataInterpolator.h>
# include <xip/inventor/itk/SoItkSFDataTransform.h>
# include <Inventor/engines/SoSubEngine.h>
# include <Inventor/fields/SoSFEnum.h>
# include <Inventor/fields/SoSFShort.h>

class SoItkDataImageMetric;

class SoItkImageToImageMetric : public SoEngine
{
	SO_ENGINE_ABSTRACT_HEADER( SoItkImageToImageMetric );

public:
	SoItkImageToImageMetric();

	static void initClass();

	enum PixelTypeEnum
	{
        UNSIGNED_SHORT,
		FLOAT,
		DOUBLE		
	};

	SoSFEnum PixelType;
	SoSFShort Dimension;

//    SoItkSFDataImage FixedImage;
//    SoItkSFDataImage MovingImage;
//    SoItkSFDataTransform Transform;
//    SoItkSFDataInterpolator Interpolator;
//    SoSFVec3f FixedImageRegionOrigin;
//    SoSFVec3f FixedImageRegionSize;
//    SoMFFloat TransformParameters;
//    SoSFBool ComputeGradient;
	
//    SoEngineOutput NumberOfPixelsCounted; // SoSFFloat
//    SoEngineOutput NumberOfParameters; // SoSFFloat
//    SoEngineOutput GradientImage; // SoItkSFDataImage
	SoEngineOutput Output; // SoItkSFDataImageMetric

protected:
	~SoItkImageToImageMetric();

	virtual void evaluate() = 0;

	SoItkDataImageMetric* mOutput;
	SoItkDataImage* mGradientImage;

};

#endif // SO_ITK_IMAGE_TO_IMAGE_METRIC_H_