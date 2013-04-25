#include <xip/inventor/core/SoXipSFDataImage.h>
#include "SoXipDecomposeMFImage.h"

SO_ENGINE_SOURCE( SoXipDecomposeMFImage );

SoXipDecomposeMFImage::SoXipDecomposeMFImage()
{
	SO_ENGINE_CONSTRUCTOR( SoXipDecomposeMFImage );

	SO_ENGINE_ADD_INPUT( input, (0) );
	input.setNum(0);
	SO_ENGINE_ADD_INPUT( index, (-1) );

	SO_ENGINE_ADD_OUTPUT( output, SoXipSFDataImage );
}

SoXipDecomposeMFImage::~SoXipDecomposeMFImage()
{

}

void
SoXipDecomposeMFImage::initClass()
{
	SO_ENGINE_INIT_CLASS( SoXipDecomposeMFImage, SoEngine, "Engine" );
}

void
SoXipDecomposeMFImage::evaluate()
{
	int id = index.getValue();
	if( id < 0 || id >= input.getNum() )
	{
		SO_ENGINE_OUTPUT( output, SoXipSFDataImage, setValue(0) );
		return ;
	}

	SO_ENGINE_OUTPUT( output, SoXipSFDataImage, setValue( input[id] ) );
}