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

#include <itkPointSet.h>
#include <Inventor/SoDB.h>
#include <Inventor/fields/SoMFVec3f.h>
#include "SoItkConvertItkPointSetToMFVec3f.h"

SO_ENGINE_SOURCE( SoItkConvertItkPointSetToMFVec3f );

SoItkConvertItkPointSetToMFVec3f::SoItkConvertItkPointSetToMFVec3f()
{
	SO_ENGINE_CONSTRUCTOR( SoItkConvertItkPointSetToMFVec3f );

    // Inputs
	SO_ENGINE_ADD_INPUT( Input, (0) );

	// Outputs
	SO_ENGINE_ADD_OUTPUT( Output, SoMFVec3f );
}

void 
SoItkConvertItkPointSetToMFVec3f::initClass()
{
	SO_ENGINE_INIT_CLASS( SoItkConvertItkPointSetToMFVec3f, SoFieldConverter, "SoFieldConverter" );

	// Register this converter's type with the Inventor database
	//
	SoDB::addConverter( SoItkSFDataPointSet::getClassTypeId(),
		SoMFVec3f::getClassTypeId(),
		getClassTypeId() );
}

SoItkConvertItkPointSetToMFVec3f::~SoItkConvertItkPointSetToMFVec3f()
{

}

void
SoItkConvertItkPointSetToMFVec3f::evaluate()
{
	SoDebugError::post( __FILE__, "DOING CONVERSION" );

	SoItkDataPointSet* Input_ = Input.getValue();
	if( !Input_ )
		return ;

	try
	{
        switch( Input_->getDimension() )        
        {
            case 2:
            {
                typedef itk::PointSet< float, 2 > PointSetType;
				typedef PointSetType::PointsContainer::Iterator PointsIterator;
				typedef PointSetType::PointType PointType;
                
                PointSetType* pointSet = static_cast< PointSetType* >(
                    Input_->getPointer() );

				SoDebugError::post( __FILE__, "Num: %d", pointSet->GetNumberOfPoints() );
                
                unsigned int numberOfPoints = pointSet->GetNumberOfPoints();
                SO_ENGINE_OUTPUT( Output, SoMFVec3f, setNum( numberOfPoints ) );
				
				PointsIterator pointIterator = pointSet->GetPoints()->Begin();
				PointsIterator end = pointSet->GetPoints()->End();
				for( unsigned int count = 0; pointIterator != end; ++ pointIterator )
				{
					PointType p = pointIterator.Value();

                    SbVec3f point( p[0], p[1], 0 );                    
                    SO_ENGINE_OUTPUT( Output, SoMFVec3f, set1Value( count ++, point ) );
                }
            }
            break ;
            
            case 3:
            {
                
            }
            break;
        }
	}
	catch( itk::ExceptionObject& e )
	{
		SoDebugError::post( e.GetFile(), "line %d: %s", e.GetLine(), e.GetDescription() );
		return ;
	}
	catch(...)
	{
		SoDebugError::post( __FILE__, "Unknown exception" );
		return ;
	}
}

SoField* 
SoItkConvertItkPointSetToMFVec3f::getInput( SoType type )
{
	if( type == SoItkSFDataPointSet::getClassTypeId() )
	{
		return &Input;
	}

	SoDebugError::post( __FILE__, "SoItkConvertItkPointSetToMFVec3f::getOutput() : unresolved input" );
	return 0;
}

SoEngineOutput* 
SoItkConvertItkPointSetToMFVec3f::getOutput( SoType type )
{
	if( type == SoMFVec3f::getClassTypeId() )
	{
		return &Output;
	}

	SoDebugError::post( __FILE__, "SoItkConvertItkPointSetToMFVec3f::getOutput() : unresolved output" );
	return 0;
}

