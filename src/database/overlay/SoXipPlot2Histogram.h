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
/**
*	@file	SoXipPlot2Histogram.h
*	@brief	Declaration of the SoXipPlot2Histogram class
*	@author	Julien Gein
**/

#ifndef SOXIPPLOT2HISTOGRAM_H
#define SOXIPPLOT2HISTOGRAM_H

#include <Inventor/nodekits/SoBaseKit.h>
#include <Inventor/SbViewportRegion.h>
#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoSFVec2f.h>

class SoCoordinate3;
class SoFaceSet;
class SoFieldSensor;

class SoXipPlot2Histogram : public SoBaseKit
{
	SO_KIT_HEADER( SoXipPlot2Histogram );

	SO_KIT_CATALOG_ENTRY_HEADER( separator );
	SO_KIT_CATALOG_ENTRY_HEADER( shapeHints );
	SO_KIT_CATALOG_ENTRY_HEADER( coordinate );
	SO_KIT_CATALOG_ENTRY_HEADER( faceSet );

public:
	SoXipPlot2Histogram();

	SoMFFloat		values;
	SoSFVec2f		validRange;
	SoSFInt32		numBins;

	static void initClass();

protected:
	virtual ~SoXipPlot2Histogram();

	virtual void update();

	SoFieldSensor*	mValueSensor;
	SoFieldSensor*	mValidRangeSensor;
	SoFieldSensor*	mNumBinsSensor;

private:
	static void fieldSensorCBFunc( void* user, SoSensor* sensor );

};

#endif // SoXIPPLOT2HISTOGRAM_H
