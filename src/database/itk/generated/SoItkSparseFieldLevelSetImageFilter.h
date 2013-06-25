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

#ifndef SO_ITK_SPARSEFIELDLEVELSETIMAGEFILTER_H_
# define SO_ITK_SPARSEFIELDLEVELSETIMAGEFILTER_H_

# include <Inventor/fields/SoSFBool.h>
# include <Inventor/fields/SoSFFloat.h>
# include "SoItkFiniteDifferenceImageFilter.h"

class XIPIVITK_API SoItkSparseFieldLevelSetImageFilter : public SoItkFiniteDifferenceImageFilter
{
	SO_ENGINE_ABSTRACT_HEADER( SparseFieldLevelSetImageFilter );

public:
	SoItkSparseFieldLevelSetImageFilter();

	SoSFFloat NumberOfLayers;
	SoSFFloat IsoSurfaceValue;
	SoSFBool InterpolateSurfaceLocation;
	
	static void initClass();

protected:
	~SoItkSparseFieldLevelSetImageFilter();

	virtual bool checkInput() = 0;
	virtual void evaluate() = 0;

};

#endif // SO_ITK_SPARSEFIELDLEVELSETIMAGEFILTER_H_
