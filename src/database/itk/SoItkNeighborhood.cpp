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
#include <itkNeighborhood.h>
#include <xip/inventor/itk/SoItkSFDataNeighborhood.h>
#include <xip/inventor/itk/SoItkUtils.h>
#include "SoItkNeighborhood.h"


SO_ENGINE_SOURCE( SoItkNeighborhood )

SoItkNeighborhood::SoItkNeighborhood()
{
	SO_ENGINE_CONSTRUCTOR( SoItkNeighborhood );

	SO_ENGINE_DEFINE_ENUM_VALUE( PixelTypeEnum, UNSIGNED_SHORT );
	SO_ENGINE_DEFINE_ENUM_VALUE( PixelTypeEnum, FLOAT );
	SO_ENGINE_SET_SF_ENUM_TYPE( PixelType, PixelTypeEnum );
	SO_ENGINE_ADD_INPUT( PixelType, (FLOAT) );

	SO_ENGINE_ADD_INPUT( Dimension, (2) );
    SO_ENGINE_ADD_INPUT( Radius, (0) );
    Radius.setNum(0);

  	SO_ENGINE_ADD_OUTPUT( Output, SoItkSFDataNeighborhood );
    mOutput = 0;
}

SoItkNeighborhood::~SoItkNeighborhood()
{    
    if( mOutput )
    {
        mOutput->unref();
        mOutput = 0;
    }
}

void
SoItkNeighborhood::initClass()
{
	SO_ENGINE_INIT_CLASS( SoItkNeighborhood, SoEngine, "Engine" );	
}

void
SoItkNeighborhood::evaluate()
{
    if( mOutput )
    {
        mOutput->unref();
        mOutput = 0;
        SO_ENGINE_OUTPUT( Output, SoItkSFDataNeighborhood, setValue( 0 ) );
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
                        typedef itk::Neighborhood< float, 2 > NeighborhoodType;
                        NeighborhoodType* neighborhood = new NeighborhoodType;
                        
                        SO_ITK_SET_FIELD_SIZE( neighborhood, Radius, 2 );
                        
                        mOutput = new SoItkDataNeighborhood( SoItkDataNeighborhood::FLOAT, 2 );
                        mOutput->ref();
                        mOutput->setPointer( neighborhood );
                    }
					break ;

					case 3:
					{
                        typedef itk::Neighborhood< float, 3 > NeighborhoodType;
                        NeighborhoodType* neighborhood = new NeighborhoodType;
                        
                        SO_ITK_SET_FIELD_SIZE( neighborhood, Radius, 3 );
                        
                        mOutput = new SoItkDataNeighborhood( SoItkDataNeighborhood::FLOAT, 3 );
                        mOutput->ref();
                        mOutput->setPointer( neighborhood );
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
                        typedef itk::Neighborhood< unsigned short, 2 > NeighborhoodType;
                        NeighborhoodType* neighborhood = new NeighborhoodType;
                        
                        SO_ITK_SET_FIELD_SIZE( neighborhood, Radius, 2 );
                        
                        mOutput = new SoItkDataNeighborhood( SoItkDataNeighborhood::UNSIGNED_SHORT, 2 );
                        mOutput->ref();
                        mOutput->setPointer( neighborhood );
                    }
					break ;

					case 3:
					{
                        typedef itk::Neighborhood< unsigned short, 3 > NeighborhoodType;
                        NeighborhoodType* neighborhood = new NeighborhoodType;
                        
                        SO_ITK_SET_FIELD_SIZE( neighborhood, Radius, 3 );
                        
                        mOutput = new SoItkDataNeighborhood( SoItkDataNeighborhood::UNSIGNED_SHORT, 3 );
                        mOutput->ref();
                        mOutput->setPointer( neighborhood );
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
    
	SO_ENGINE_OUTPUT( Output, SoItkSFDataNeighborhood, setValue( mOutput ) );
}
