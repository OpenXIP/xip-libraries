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
/*
 * \brief
 * \author Sylvain Jaume, Francois Huguet
 */
 
 
 
# ifndef SO_VTK_GESIGNAREADER_H_
# define SO_VTK_GESIGNAREADER_H_

# include <Inventor/engines/SoSubEngine.h>

# include "xip/inventor/vtk/SoSFVtkAlgorithmOutput.h"
# include "xip/inventor/vtk/SoSFVtkObject.h"

# include "vtkGESignaReader.h"

# include "Inventor/fields/SoSFVec3f.h"
# include "Inventor/fields/SoMFString.h"
# include "Inventor/fields/SoSFInt32.h"
# include "Inventor/fields/SoMFInt32.h"
# include "Inventor/fields/SoSFULong.h"

class SoVtkGESignaReader : public SoEngine
{
	SO_ENGINE_HEADER( SoVtkGESignaReader );

public:

	/// Constructor
	SoVtkGESignaReader();

	/// Class Initialization
	static void initClass();
	
	// Inputs
	/// DataSpacing
	SoSFVec3f DataSpacing;
	/// ImageNumber
	SoMFString ImageNumber;
	/// FilePattern
	SoMFString FilePattern;
	/// Series
	SoMFString Series;
	/// PatientID
	SoMFString PatientID;
	/// FilePrefix
	SoMFString FilePrefix;
	/// FileDimensionality
	SoSFInt32 FileDimensionality;
	/// Modality
	SoMFString Modality;
	/// DataOrigin
	SoSFVec3f DataOrigin;
	/// DataScalarType
	SoSFInt32 DataScalarType;
	/// Input connection 
	SoSFVtkAlgorithmOutput InputConnection;
	/// DataExtent
	SoMFInt32 DataExtent;
	/// HeaderSize
	SoSFULong HeaderSize;
	/// PatientName
	SoMFString PatientName;
	/// FileNameSliceOffset
	SoSFInt32 FileNameSliceOffset;
	/// NumberOfScalarComponents
	SoSFInt32 NumberOfScalarComponents;
	/// Date
	SoMFString Date;
	/// FileLowerLeft
	SoSFInt32 FileLowerLeft;
	/// DataByteOrder
	SoSFInt32 DataByteOrder;
	/// FileName
	SoMFString FileName;
	/// SwapBytes
	SoSFInt32 SwapBytes;
	/// Study
	SoMFString Study;
	/// FileNameSliceSpacing
	SoSFInt32 FileNameSliceSpacing;

	
	// Outputs
	/// SoSFVtkObject of type vtkImageData
	SoEngineOutput Output;
	/// SoSFVtkAlgorithmOutput
	SoEngineOutput OutputPort;

protected:

	/// Destructor
	~SoVtkGESignaReader();

	/// Evaluate Function
	virtual void evaluate();

	/// inputChanged Function
	virtual void inputChanged(SoField *);

	/// reset Function
	virtual void reset();

	/// vtkImageData
	SoVtkObject *mOutput;

	/// vtkAlgorithm
	SoVtkAlgorithmOutput *mOutputPort;


private:

	vtkGESignaReader* mObject;
	/// addCalled checks if the Add*() method has been called 
	bool addCalled;
};

#endif // SO_VTK_GESIGNAREADER_H_

