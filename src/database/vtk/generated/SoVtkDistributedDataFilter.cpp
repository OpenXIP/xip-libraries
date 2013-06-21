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
 * \file SoSFVtkAlgorithmOutput.cpp
 *
 * \brief XIP wrapping of vtkAlgorithmOutput.cpp
 *
 * \author Sylvain Jaume <sylvain.jaume@siemens.com>
 * \author Francois Huguet
 *
 * \see SoSFVtkObject
 */
 
#include "SoVtkDistributedDataFilter.h"
#include "SoVtkUtils.h"

#include "vtkMultiProcessController.h"
#include "vtkAlgorithmOutput.h"
#include "vtkUnstructuredGrid.h"
#include "vtkPKdTree.h"

SO_ENGINE_SOURCE( SoVtkDistributedDataFilter )

SoVtkDistributedDataFilter::SoVtkDistributedDataFilter()
{
  SO_ENGINE_CONSTRUCTOR(SoVtkDistributedDataFilter);

  mObject = vtkDistributedDataFilter::New();
  mObject->Register(0);
  mObject->SetGlobalWarningDisplay(0);

  vtkDistributedDataFilter *aDistributedDataFilter =
          vtkDistributedDataFilter::New();
  double *x = 0;
  int *y = 0;
  float *z = 0;

  SO_ENGINE_ADD_INPUT(BoundaryMode, (0));
  BoundaryMode.setValue(aDistributedDataFilter->GetBoundaryMode());

  SO_ENGINE_ADD_INPUT(IncludeAllIntersectingCells, (0));
  IncludeAllIntersectingCells.setValue(aDistributedDataFilter->
    GetIncludeAllIntersectingCells());

  SO_ENGINE_ADD_INPUT(Timing, (0));
  Timing.setValue(aDistributedDataFilter->GetTiming());

  SO_ENGINE_ADD_INPUT(RetainKdtree, (0));
  RetainKdtree.setValue(aDistributedDataFilter->GetRetainKdtree());

  SO_ENGINE_ADD_INPUT(UseMinimalMemory, (0));
  UseMinimalMemory.setValue(aDistributedDataFilter->
    GetUseMinimalMemory());

  SO_ENGINE_ADD_INPUT(ClipCells, (0));
  ClipCells.setValue(aDistributedDataFilter->GetClipCells());

  //SO_ENGINE_ADD_INPUT(GlobalNodeIdArrayName, (""));

  SO_ENGINE_ADD_INPUT(GlobalElementIdArrayName, (""));

  SO_ENGINE_ADD_INPUT(Controller, (0));

  SO_ENGINE_ADD_INPUT(InputConnection, (0));

  aDistributedDataFilter->Delete();

  SO_ENGINE_DEFINE_ENUM_VALUE( BoundaryModes,
    ASSIGN_TO_ALL_INTERSECTING_REGIONS );
  SO_ENGINE_DEFINE_ENUM_VALUE( BoundaryModes, SPLIT_BOUNDARY_CELLS );
  SO_ENGINE_DEFINE_ENUM_VALUE( BoundaryModes, ASSIGN_TO_ONE_REGION );
  SO_ENGINE_SET_SF_ENUM_TYPE( BoundaryModesEnum, BoundaryModes );

  SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
  mOutput = 0;
  SO_ENGINE_ADD_OUTPUT( oKdtree, SoSFVtkObject );
  mKdtree = 0;
  SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
  mOutputPort = 0;

  addCalled = 0;
}

SoVtkDistributedDataFilter::~SoVtkDistributedDataFilter()
{
  // Deletion of the objects if they exist
  if ( mOutput )
    {
    mOutput->unref();
    mOutput = 0;
    }
        
  if ( mKdtree )
    {
    mKdtree->unref();
    mKdtree = 0;
    }
        
  if ( mOutputPort )
    {
    mOutputPort->unref();
    mOutputPort = 0;
    }
        
  if ( mObject )
    {
    mObject->UnRegister(0);
    mObject->Delete();
    mObject = 0;
    }
}

void SoVtkDistributedDataFilter::initClass()
{
        SO_ENGINE_INIT_CLASS( SoVtkDistributedDataFilter, SoEngine, "Engine" );
}

void SoVtkDistributedDataFilter::evaluate()
{
        try
        {
                // Get the input type(s)
                SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
                
                if (inputPortPtr)
                        mObject->SetInputConnection(inputPortPtr->getPointer());

                // Deletion of the objects if they exist
                if ( mOutput )
                {
                
                        mOutput->unref();
                        mOutput = 0;
                }
                
                if ( mKdtree )
                {
                
                        mKdtree->unref();
                        mKdtree = 0;
                }
                
                if ( mOutputPort )
                {
                
                        mOutputPort->unref();
                        mOutputPort = 0;
                }
                
                if ( addCalled )
                {
                        reset();
                        addCalled = 0;
                }

                mObject->GetOutput()->Register(0);
                mOutput = new SoVtkObject();
                mOutput->ref();
                mOutput->setPointer( mObject->GetOutput() );

                mObject->GetKdtree();
                mKdtree = new SoVtkObject();
                mKdtree->ref();
                mKdtree->setPointer( mObject->GetKdtree() );

                if ( mObject->GetNumberOfOutputPorts() > 0 )
                {
                        mObject->GetOutputPort()->Register(0);
                        mOutputPort = new SoVtkAlgorithmOutput();
                        mOutputPort->ref();
                        mOutputPort->setPointer( mObject->GetOutputPort() );
                }

        }
        catch(...)
        {
                SoDebugError::post( __FILE__, "Unknown Exception" );
                return;
        }
        SO_ENGINE_OUTPUT( Output, SoSFVtkObject, setValue( mOutput ) );
        SO_ENGINE_OUTPUT( oKdtree, SoSFVtkObject, setValue( mKdtree ) );
        SO_ENGINE_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput, setValue( mOutputPort ) );
}


void SoVtkDistributedDataFilter::inputChanged(SoField * f)
{
  // Get the BoundaryMode value
  if ( f == &BoundaryMode )
       SO_VTK_SET_FIELD_VALUE( mObject, BoundaryMode);

        // Get the IncludeAllIntersectingCells value
        if ( f == &IncludeAllIntersectingCells )
                SO_VTK_SET_FIELD_VALUE( mObject, IncludeAllIntersectingCells);

        // Get the Timing value
        if ( f == &Timing )
                SO_VTK_SET_FIELD_VALUE( mObject, Timing);

        // Get the RetainKdtree value
        if ( f == &RetainKdtree )
                SO_VTK_SET_FIELD_VALUE( mObject, RetainKdtree);

        // Get the UseMinimalMemory value
        if ( f == &UseMinimalMemory )
                SO_VTK_SET_FIELD_VALUE( mObject, UseMinimalMemory);

        // Get the ClipCells value
        if ( f == &ClipCells )
                SO_VTK_SET_FIELD_VALUE( mObject, ClipCells);

        // Get the GlobalNodeIdArrayName value
        //if ( f == &GlobalNodeIdArrayName )
        //SO_VTK_SET_FIELD_MFSTRING( mObject, GlobalNodeIdArrayName);

        // Get the GlobalElementIdArrayName value
        //if ( f == &GlobalElementIdArrayName )
        //SO_VTK_SET_FIELD_MFSTRING( mObject, GlobalElementIdArrayName);

        // Get the Controller value
        if ( f == &Controller )
                SO_VTK_SET_FIELD_DATA( mObject, Controller, vtkMultiProcessController);

        mObject->Update();
}

void SoVtkDistributedDataFilter::reset()
{
        mObject->UnRegister(0);
        mObject->Delete();
        mObject = 0;
        mObject = vtkDistributedDataFilter::New();
        mObject->Register(0);
        mObject->SetGlobalWarningDisplay(0);
        // Get the input type(s)
        SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
        
        if (inputPortPtr)
                mObject->SetInputConnection(inputPortPtr->getPointer());

        // Get the BoundaryMode value
        SO_VTK_SET_FIELD_VALUE( mObject, BoundaryMode);

        // Get the IncludeAllIntersectingCells value
        SO_VTK_SET_FIELD_VALUE( mObject, IncludeAllIntersectingCells);

        // Get the Timing value
        SO_VTK_SET_FIELD_VALUE( mObject, Timing);

        // Get the RetainKdtree value
        SO_VTK_SET_FIELD_VALUE( mObject, RetainKdtree);

        // Get the UseMinimalMemory value
        SO_VTK_SET_FIELD_VALUE( mObject, UseMinimalMemory);

        // Get the ClipCells value
        SO_VTK_SET_FIELD_VALUE( mObject, ClipCells);

        // Get the GlobalNodeIdArrayName value
        //SO_VTK_SET_FIELD_MFSTRING( mObject, GlobalNodeIdArrayName);

        // Get the GlobalElementIdArrayName value
        //SO_VTK_SET_FIELD_MFSTRING( mObject, GlobalElementIdArrayName);

        // Get the Controller value
        SO_VTK_SET_FIELD_DATA( mObject, Controller, vtkMultiProcessController);

        mObject->Update();
}

