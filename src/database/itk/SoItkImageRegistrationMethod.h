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

#ifndef SO_ITK_IMAGEREGISTRATIONMETHOD_H_
# define SO_ITK_IMAGEREGISTRATIONMETHOD_H_

# include <Inventor/fields/SoMFFloat.h>
# include <Inventor/fields/SoSFTrigger.h>
# include <xip/inventor/itk/SoItkSFDataTransform.h>
# include <xip/inventor/itk/SoItkSFDataImage.h>
# include <xip/inventor/itk/SoItkSFDataImageMetric.h>
# include <xip/inventor/itk/SoItkSFDataInterpolator.h>
# include <xip/inventor/itk/SoItkSFDataOptimizer.h>
# include "generated/SoItkProcessObject.h"

class SoItkImageRegistrationMethod : public SoItkProcessObject
{
	SO_ENGINE_HEADER( ImageRegistrationMethod );

public:
	SoItkImageRegistrationMethod();

	SoMFFloat InitialTransformParameters;
	SoItkSFDataTransform Transform;
	SoItkSFDataImage FixedImage;
	SoItkSFDataImage MovingImage;
	SoItkSFDataInterpolator Interpolator;
	SoItkSFDataImageMetric Metric;
	SoMFFloat FixedImageRegion;
	SoItkSFDataOptimizer Optimizer;
	SoSFTrigger Start;

	SoEngineOutput OutputOptimizer; // SoItkSFDataOptimizer
	SoEngineOutput LastTransformParameters; // SoMFFloat
	
	static void initClass();

protected:
	~SoItkImageRegistrationMethod();

	virtual bool checkInput();
	virtual void evaluate();
	virtual void inputChanged( SoField* whichInput );

	bool mStartRegistration;

	SoItkDataOptimizer* mOptimizer;

};

#endif // SO_ITK_IMAGEREGISTRATIONMETHOD_H_
