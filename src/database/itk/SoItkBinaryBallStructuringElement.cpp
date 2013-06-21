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
#include <itkBinaryBallStructuringElement.h>
#include <xip/inventor/itk/SoItkSFDataNeighborhood.h>
#include <xip/inventor/itk/SoItkUtils.h>
#include "SoItkBinaryBallStructuringElement.h"


SO_ENGINE_SOURCE( SoItkBinaryBallStructuringElement )

SoItkBinaryBallStructuringElement::SoItkBinaryBallStructuringElement()
{
	SO_ENGINE_CONSTRUCTOR( SoItkBinaryBallStructuringElement );
}

SoItkBinaryBallStructuringElement::~SoItkBinaryBallStructuringElement()
{    

}

void
SoItkBinaryBallStructuringElement::initClass()
{
	SO_ENGINE_INIT_CLASS( SoItkBinaryBallStructuringElement, SoItkNeighborhood, "SoItkNeighborhood" );	
}

void
SoItkBinaryBallStructuringElement::evaluate()
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
                        typedef itk::BinaryBallStructuringElement< float, 2 > NeighborhoodType;
                        NeighborhoodType* neighborhood = new NeighborhoodType;
                        
                        SO_ITK_SET_FIELD_SIZE( neighborhood, Radius, 2 );
                        
                        mOutput = new SoItkDataNeighborhood( SoItkDataNeighborhood::FLOAT, 2 );
                        mOutput->ref();
                        mOutput->setPointer( neighborhood );
                    }
					break ;

					case 3:
					{
                        typedef itk::BinaryBallStructuringElement< float, 3 > NeighborhoodType;
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
                        typedef itk::BinaryBallStructuringElement< unsigned short, 2 > NeighborhoodType;
                        NeighborhoodType* neighborhood = new NeighborhoodType;
                        
                        SO_ITK_SET_FIELD_SIZE( neighborhood, Radius, 2 );
                        
                        mOutput = new SoItkDataNeighborhood( SoItkDataNeighborhood::UNSIGNED_SHORT, 2 );
                        mOutput->ref();
                        mOutput->setPointer( neighborhood );
                    }
					break ;

					case 3:
					{
                        typedef itk::BinaryBallStructuringElement< unsigned short, 3 > NeighborhoodType;
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
