#include <xip/inventor/dicom/SoXipSFDataDicom.h>
#include "SoXipDecomposeMFDicom.h"

SO_ENGINE_SOURCE( SoXipDecomposeMFDicom );

SoXipDecomposeMFDicom::SoXipDecomposeMFDicom()
{
	SO_ENGINE_CONSTRUCTOR( SoXipDecomposeMFDicom );

	SO_ENGINE_ADD_INPUT( input, (0) );
	input.setNum(0);
	SO_ENGINE_ADD_INPUT( index, (-1) );

	SO_ENGINE_ADD_OUTPUT( output, SoXipSFDataDicom );
}

SoXipDecomposeMFDicom::~SoXipDecomposeMFDicom()
{

}

void
SoXipDecomposeMFDicom::initClass()
{
	SO_ENGINE_INIT_CLASS( SoXipDecomposeMFDicom, SoEngine, "Engine" );
}

void
SoXipDecomposeMFDicom::evaluate()
{
	int id = index.getValue();
	if( id < 0 || id >= input.getNum() )
	{
		SO_ENGINE_OUTPUT( output, SoXipSFDataDicom, setValue(0) );
		return ;
	}

	SO_ENGINE_OUTPUT( output, SoXipSFDataDicom, setValue( input[id] ) );
}