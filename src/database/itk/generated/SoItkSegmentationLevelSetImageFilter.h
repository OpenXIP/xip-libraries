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

#ifndef SO_ITK_SEGMENTATIONLEVELSETIMAGEFILTER_H_
# define SO_ITK_SEGMENTATIONLEVELSETIMAGEFILTER_H_

# include <Inventor/fields/SoSFBool.h>
# include <Inventor/fields/SoSFFloat.h>
# include <xip/inventor/itk/SoItkSFDataImage.h>
# include "SoItkSparseFieldLevelSetImageFilter.h"

class XIPIVITK_API SoItkSegmentationLevelSetImageFilter : public SoItkSparseFieldLevelSetImageFilter
{
	SO_ENGINE_ABSTRACT_HEADER( SegmentationLevelSetImageFilter );

public:
	SoItkSegmentationLevelSetImageFilter();

	SoSFFloat FeatureScaling;
	SoSFFloat AdvectionScaling;
	SoSFFloat CurvatureScaling;
	SoItkSFDataImage FeatureImage;
	SoSFFloat MaximumPropagationTimeStep;
	SoSFBool UseMinimalCurvature;
	SoSFBool ReverseExpansionDirection;
	SoSFFloat PropagationScaling;
	SoSFFloat MaximumCurvatureTimeStep;
	
	static void initClass();

protected:
	~SoItkSegmentationLevelSetImageFilter();

	virtual bool checkInput() = 0;
	virtual void evaluate() = 0;

};

#endif // SO_ITK_SEGMENTATIONLEVELSETIMAGEFILTER_H_
