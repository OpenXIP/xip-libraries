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
#include <itkPointSet.h>
#include <xip/inventor/itk/SoItkSFDataPointSet.h>
#include <xip/inventor/itk/SoItkUtils.h>
#include "SoItkPointSet.h"


SO_ENGINE_SOURCE( SoItkPointSet )

SoItkPointSet::SoItkPointSet()
{
	SO_ENGINE_CONSTRUCTOR( SoItkPointSet );
    
    // Enumerations
	SO_ENGINE_DEFINE_ENUM_VALUE( OutputPixelTypeEnum, FLOAT );
	SO_ENGINE_DEFINE_ENUM_VALUE( OutputPixelTypeEnum, UNSIGNED_SHORT );
	SO_ENGINE_SET_SF_ENUM_TYPE( PixelType, OutputPixelTypeEnum );
    
	// Define input fields and their default values
	SO_ENGINE_ADD_INPUT( PixelType, (FLOAT) );
    SO_ENGINE_ADD_INPUT( Dimension, (2) );    
    SO_ENGINE_ADD_INPUT( Points, (0, 0, 0) );
    Points.setNum(0);
    
    SO_ENGINE_ADD_OUTPUT( PointSet, SoItkSFDataPointSet );
    mOutput = 0;
}

SoItkPointSet::~SoItkPointSet()
{    
    if( mOutput )
    {
        mOutput->unref();
        mOutput = 0;
        SO_ENGINE_OUTPUT( PointSet, SoItkSFDataPointSet, setValue( 0 ) );
    }
}

void
SoItkPointSet::initClass()
{
	SO_ENGINE_INIT_CLASS( SoItkPointSet, SoEngine, "SoEngine" );	
}

void
SoItkPointSet::evaluate()
{
    if( mOutput )
    {
        mOutput->unref();
        mOutput = 0;
        SO_ENGINE_OUTPUT( PointSet, SoItkSFDataPointSet, setValue( 0 ) );
    }
    
    try
    {
        switch( PixelType.getValue() )
		{
			case FLOAT:
			{
				switch( Dimension.getValue() )
				{
					case 2:
					{
                        typedef itk::PointSet< float, 2 > PointSetType;
                        typedef PointSetType::PointType PointType;
                        
						PointSetType* pointSet = PointSetType::New();
                        pointSet->Register();
                        
                        unsigned int numPoints = Points.getNum();
                        for( unsigned int i = 0; i < numPoints; ++ i )
                        {
                            PointType p;
                            p[0] = Points[i][0];
                            p[1] = Points[i][1];
                            
                            pointSet->SetPoint( i, p );
                        }
                        
                        mOutput = new SoItkDataPointSet( SoItkDataPointSet::FLOAT, 2 );
                        mOutput->ref();
                        mOutput->setPointer( pointSet );
                    }
					break ;

					case 3:
					{

                    }
					break ;
                }
            }
			break ;

			case UNSIGNED_SHORT:
			{
				switch( Dimension.getValue() )
				{
					case 2:
					{
                    }
					break ;

					case 3:
					{
                    }
					break ;
                }
            }
			break ;
        }
    }
    catch(...)
    {
        SoDebugError::post( __FILE__, "Unknown Exception" );
        return ;
    }
    
	SO_ENGINE_OUTPUT( PointSet, SoItkSFDataPointSet, setValue( mOutput ) );
}
