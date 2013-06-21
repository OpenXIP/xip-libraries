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
 * \author Sylvain Jaume, Francois Huguet
 */
#ifndef SO_VTK_POLYDATA_H_
#define SO_VTK_POLYDATA_H_

#include <Inventor/engines/SoSubEngine.h>
#include <Inventor/fields/SoSFInt32.h>

#include <xip/inventor/vtk/SoSFVtkAlgorithmOutput.h>
#include <xip/inventor/vtk/SoSFVtkObject.h>
#include <xip/inventor/core/SoSFVariant.h>

#include "vtkPolyData.h"

class SoVtkPolyData : public SoEngine
{
  SO_ENGINE_HEADER( SoVtkPolyData );

public:
  /// Constructor
  SoVtkPolyData();

  /// Class Initialization
  static void initClass();

  // Inputs
  /// Input object of type PolyData
  SoSFVtkObject Input;
  /// ExtentTranslator of type vtkExtentTranslator
  SoSFVtkObject ExtentTranslator;
  /// MaximumNumberOfPieces
  SoSFInt32 MaximumNumberOfPieces;
  /// RequestExactExtent
  SoSFInt32 RequestExactExtent;
  /// UpdatePiece
  SoSFInt32 UpdatePiece;
  /// WholeBoundingBox
  SoSFVariant WholeBoundingBox;
  /// UpdateGhostLevel
  SoSFInt32 UpdateGhostLevel;
  /// UpdateNumberOfPieces
  SoSFInt32 UpdateNumberOfPieces;
  /// Lines of type vtkCellArray
  SoSFVtkObject Lines;
  /// Strips of type vtkCellArray
  SoSFVtkObject Strips;
  /// Source of type vtkSource
  SoSFVtkObject Source;
  /// PipelineInformation of type vtkInformation
  SoSFVtkObject PipelineInformation;
  /// FieldData of type vtkFieldData
  SoSFVtkObject FieldData;
  /// Polys of type vtkCellArray
  SoSFVtkObject Polys;
  /// UpdateExtent
  SoSFVariant UpdateExtent;
  /// WholeExtent
  SoSFVariant WholeExtent;
  /// Points of type vtkPoints
  SoSFVtkObject Points;
  /// Verts of type vtkCellArray
  SoSFVtkObject Verts;
  	
  // Outputs
  /// SoSFVtkObject of type vtkPolyData
  SoEngineOutput Output;

protected:
  /// Destructor
  ~SoVtkPolyData();

  /// Evaluate Function
  virtual void evaluate();

  virtual void inputChanged(SoField *);
	
  /// vtkPolyData
  SoVtkObject *mOutput;

private:

  vtkPolyData* mObject;
};

#endif // SO_VTK_POLYDATA_H_



