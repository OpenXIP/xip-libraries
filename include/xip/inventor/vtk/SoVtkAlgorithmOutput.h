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
 * \file SoVtkAlgorithmOutput.h
 *
 * \brief SoVtkAlgorithmOutput class description.
 *
 * \see SoVtkObject
 */

#ifndef SO_VTK_ALGORITHMOUTPUT_H_
# define SO_VTK_ALGORITHMOUTPUT_H_

# include <xip/inventor/core/SoXipData.h>
# include <xip/inventor/core/SoXipSubData.h>

# include "xipivvtk.h"

# include "vtkAlgorithmOutput.h"

/*!
 * \brief
 * SoVtkAlgorithmOutput class description.
 *
 * This class enables the transfer of AlgorithmOutput information
 * between Xipbuilder elements. Used for InputConnection and OutputPort.
 *
 * \see SoVtkObject
 *
 */
class XIPIVVTK_API SoVtkAlgorithmOutput : public SoXipData
{
	XIP_DATA_HEADER( SoVtkAlgorithmOutput );

public:
	/// Constructor.
	SoVtkAlgorithmOutput();
	
	/// Class initialization.
	static void initClass();

  /// Set the data to the given pointer.
	void setPointer( vtkAlgorithmOutput* );

  /// Get the current data.
	vtkAlgorithmOutput* getPointer() const;

protected:
	/// Destructor.
	~SoVtkAlgorithmOutput();

    /// Pointer to the AlgorithmOutput contained in the class instance.
	vtkAlgorithmOutput *mVtkAlgorithmOutput;


};

#endif // SO_VTK_ALGORITHMOUTPUT_H_
