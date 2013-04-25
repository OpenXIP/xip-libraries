#include <xip/inventor/core/SoXipMFDataImage.h>
#include "SoXipComposeMFImage.h"

SO_ENGINE_SOURCE( SoXipComposeMFImage );

SoXipComposeMFImage::SoXipComposeMFImage()
{
	SO_ENGINE_CONSTRUCTOR( SoXipComposeMFImage );

	SO_ENGINE_ADD_INPUT( input0, (0) );
	SO_ENGINE_ADD_INPUT( input1, (0) );
	SO_ENGINE_ADD_INPUT( input2, (0) );
	SO_ENGINE_ADD_INPUT( input3, (0) );
	SO_ENGINE_ADD_INPUT( input4, (0) );
	SO_ENGINE_ADD_INPUT( input5, (0) );
	SO_ENGINE_ADD_INPUT( input6, (0) );
	SO_ENGINE_ADD_INPUT( input7, (0) );

	SO_ENGINE_ADD_OUTPUT( output, SoXipMFDataImage );
}

SoXipComposeMFImage::~SoXipComposeMFImage()
{

}

void
SoXipComposeMFImage::initClass()
{
	SO_ENGINE_INIT_CLASS( SoXipComposeMFImage, SoEngine, "Engine" );
}

void
SoXipComposeMFImage::evaluate()
{
    SoXipMFDataImage tmp;
    
    for( int i = 0; i < 8; ++ i )
    {
        char fieldName[256];
        sprintf( fieldName, "input%d", i );
        
        SoXipSFDataImage* field = (SoXipSFDataImage *) getField( fieldName );
        if( field && field->getValue() )
            tmp.set1Value( tmp.getNum(), field->getValue() );
    }
    
    SO_ENGINE_OUTPUT( output, SoXipMFDataImage, copyFrom(tmp) );
}