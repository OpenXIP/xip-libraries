#include <xip/inventor/dicom/SoXipMFDataDicom.h>
#include "SoXipComposeMFDicom.h"

SO_ENGINE_SOURCE( SoXipComposeMFDicom );

SoXipComposeMFDicom::SoXipComposeMFDicom()
{
	SO_ENGINE_CONSTRUCTOR( SoXipComposeMFDicom );

	SO_ENGINE_ADD_INPUT( input0, (0) );
	SO_ENGINE_ADD_INPUT( input1, (0) );
	SO_ENGINE_ADD_INPUT( input2, (0) );
	SO_ENGINE_ADD_INPUT( input3, (0) );
	SO_ENGINE_ADD_INPUT( input4, (0) );
	SO_ENGINE_ADD_INPUT( input5, (0) );
	SO_ENGINE_ADD_INPUT( input6, (0) );
	SO_ENGINE_ADD_INPUT( input7, (0) );

	SO_ENGINE_ADD_OUTPUT( output, SoXipMFDataDicom );
}

SoXipComposeMFDicom::~SoXipComposeMFDicom()
{

}

void
SoXipComposeMFDicom::initClass()
{
	SO_ENGINE_INIT_CLASS( SoXipComposeMFDicom, SoEngine, "Engine" );
}

void
SoXipComposeMFDicom::evaluate()
{
    SoXipMFDataDicom tmp;
    
    for( int i = 0; i < 8; ++ i )
    {
        char fieldName[256];
        sprintf( fieldName, "input%d", i );
        
        SoXipSFDataDicom* field = (SoXipSFDataDicom *) getField( fieldName );
        if( field && field->getValue() )
            tmp.set1Value( tmp.getNum(), field->getValue() );
    }
    
    SO_ENGINE_OUTPUT( output, SoXipMFDataDicom, copyFrom(tmp) );
}