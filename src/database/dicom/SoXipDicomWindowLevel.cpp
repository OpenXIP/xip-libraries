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
#include <xip/inventor/dicom/SoXipDataDicom.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFShort.h>
#include "SoXipDicomWindowLevel.h"

SO_ENGINE_SOURCE( SoXipDicomWindowLevel );

SoXipDicomWindowLevel::SoXipDicomWindowLevel()
{
	SO_ENGINE_CONSTRUCTOR( SoXipDicomWindowLevel );

	SO_ENGINE_ADD_INPUT( input, (0) );

	SO_ENGINE_ADD_OUTPUT( window, SoSFFloat );
	SO_ENGINE_ADD_OUTPUT( level, SoSFFloat );
	SO_ENGINE_ADD_OUTPUT( bitsStored, SoSFShort );
}

SoXipDicomWindowLevel::~SoXipDicomWindowLevel()
{

}

void
SoXipDicomWindowLevel::initClass()
{
	SO_ENGINE_INIT_CLASS( SoXipDicomWindowLevel, SoEngine, "Engine" );
}

	const unsigned int XIP_IMAGE_SAMPLES_PER_PIXEL_DICOMGROUP		= 0x0028;
	const unsigned int XIP_IMAGE_SAMPLES_PER_PIXEL_DICOMELEMENT		= 0x0002;
	const unsigned int XIP_IMAGE_BITSSTORED_DICOMGROUP				= 0x0028;
	const unsigned int XIP_IMAGE_BITSSTORED_DICOMELEMENT			= 0x0101;
	const unsigned int XIP_IMAGE_RESCALE_INTERCEPT_DICOMGROUP		= 0x0028;
	const unsigned int XIP_IMAGE_RESCALE_INTERCEPT_DICOMELEMENT		= 0x1052;
	const unsigned int XIP_IMAGE_RESCALE_SLOPE_DICOMGROUP			= 0x0028;
	const unsigned int XIP_IMAGE_RESCALE_SLOPE_DICOMELEMENT			= 0x1053;
	const unsigned int XIP_IMAGE_WINDOW_WIDTH_DICOMGROUP			= 0x0028;
	const unsigned int XIP_IMAGE_WINDOW_WIDTH_DICOMELEMENT			= 0x1051;
	const unsigned int XIP_IMAGE_WINDOW_CENTER_DICOMGROUP			= 0x0028;
	const unsigned int XIP_IMAGE_WINDOW_CENTER_DICOMELEMENT			= 0x1050;
	const unsigned int XIP_IMAGE_PIXELREPRESENTATION_DICOMGROUP		= 0x0028;
	const unsigned int XIP_IMAGE_PIXELREPRESENTATION_DICOMELEMENT	= 0x0103;


void
SoXipDicomWindowLevel::evaluate()
{
	unsigned short bitsUsed = 0;
	float width = 1.f;
	float center = 0.5f;
	float slope = 1.0;
	float intercept = 0.0;
	unsigned short pixelRepresentation = 0; // default unsigned

	SoXipDataDicom* dicomData = input.getValue();
	if( dicomData )
	{
		SbXipDicomItemHandle dataset = dicomData->getDataset();
		if( !dataset.isNull() )
		{
			SbString v;
			SbXipDicomItem item(dataset);

			// Read number of samples
			unsigned short samplesPerPixel = 0;

			if( item.findAndGet( SbXipDicomTagKey( XIP_IMAGE_SAMPLES_PER_PIXEL_DICOMGROUP,
				XIP_IMAGE_SAMPLES_PER_PIXEL_DICOMELEMENT ), v, FALSE ) )
			{
				sscanf( v.getString(), "%hu", &samplesPerPixel );
			}

			// Read number of bits used
			if( item.findAndGet( SbXipDicomTagKey( XIP_IMAGE_BITSSTORED_DICOMGROUP,
				XIP_IMAGE_BITSSTORED_DICOMELEMENT ), v, FALSE ) )
			{
				sscanf( v.getString(), "%hu", &bitsUsed );
			}

			if( samplesPerPixel == 1 )
			{
				// Read rescale intercept
				if( item.findAndGet( SbXipDicomTagKey( XIP_IMAGE_RESCALE_INTERCEPT_DICOMGROUP,
					XIP_IMAGE_RESCALE_INTERCEPT_DICOMELEMENT ), v, FALSE ) )
				{
					sscanf( v.getString(), "%f", &intercept );
				}

				// Read rescale slope
				if( item.findAndGet( SbXipDicomTagKey( XIP_IMAGE_RESCALE_SLOPE_DICOMGROUP,
					XIP_IMAGE_RESCALE_SLOPE_DICOMELEMENT ), v, FALSE ) )
				{
					sscanf( v.getString(), "%f", &slope );
				}

				// pixel representation
				if( item.findAndGet( SbXipDicomTagKey( XIP_IMAGE_PIXELREPRESENTATION_DICOMGROUP,
					XIP_IMAGE_PIXELREPRESENTATION_DICOMELEMENT ), v, FALSE ) )
				{
					sscanf( v.getString(), "%hu", &pixelRepresentation );
				}

				// Read window width
				if( item.findAndGet( SbXipDicomTagKey( XIP_IMAGE_WINDOW_WIDTH_DICOMGROUP,
					XIP_IMAGE_WINDOW_WIDTH_DICOMELEMENT ), v, FALSE ) )
				{
					if( sscanf( v.getString(), "%f", &width ) == 1 )
					{
						//width = (width - intercept) / slope;
						width /= pow( 2.0, (double) bitsUsed );
					}
				}

				// Read window center
				if( item.findAndGet( SbXipDicomTagKey( XIP_IMAGE_WINDOW_CENTER_DICOMGROUP,
					XIP_IMAGE_WINDOW_CENTER_DICOMELEMENT ), v, FALSE ) )
				{
					if( sscanf( v.getString(), "%f", &center ) == 1 )
					{
						center = (center - intercept) / slope; 

						if (pixelRepresentation == 1) // signed
						{
							center += (1 << bitsUsed) / 2;
						}
						center /= pow( 2.0, (double) bitsUsed );
					}
				}
			}
		}
	}

	SO_ENGINE_OUTPUT( window, SoSFFloat, setValue(width) );
	SO_ENGINE_OUTPUT( level, SoSFFloat, setValue(center) );
	SO_ENGINE_OUTPUT( bitsStored, SoSFShort, setValue(bitsUsed) );
}
