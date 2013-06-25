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
/*!
 * \file xip/inventor/vtk/SoSFVtkAlgorithmOutput.h
 * \brief SoSFVtkAlgorithmOutput class description.
 *
 * \see SoSFVtkObject
 */

#ifndef SO_SF_VTK_ALGORITHMOUTPUT_H_
# define SO_SF_VTK_ALGORITHMOUTPUT_H_

# include <xip/inventor/core/SoXipSFData.h>

# include "SoVtkAlgorithmOutput.h"


/*!
 * \brief
 * SoSFVtkAlgorithmOutput class description.
 *
 * This class implements the fields that allow the vtkAlgorithmOutput
 * object to send data to other xip modules.
 *
 * \see SoVtkAlgorithmOutput
 *
 */
class XIPIVVTK_API SoSFVtkAlgorithmOutput : public SoXipSFData
{
	XIP_SFDATA_HEADER( SoSFVtkAlgorithmOutput, SoVtkAlgorithmOutput );
};

#endif // SO_SF_VTK_ALGORITHMOUTPUT_H_
