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
*	@file	SoXipPlot2Samples.h
*	@brief	Declaration of the SoXipPlot2Samples class
*	@author	Julien Gein
**/

#ifndef SOXIPPLOT2SAMPLES_H
#define SOXIPPLOT2SAMPLES_H

#include <Inventor/nodekits/SoSubKit.h>
#include <Inventor/fields/SoMFVec2f.h>
#include <Inventor/fields/SoMFVec3f.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFColor.h>
#include <Inventor/fields/SoSFString.h>
#include "SoXipMarkerSet.h"

class SoXipPlot2Samples : public SoBaseKit
{
	SO_KIT_HEADER( SoXipPlot2Samples );

	SO_KIT_CATALOG_ENTRY_HEADER( mMainSeparator );

	SO_KIT_CATALOG_ENTRY_HEADER( mMarkerSeparator );
	SO_KIT_CATALOG_ENTRY_HEADER( mMarkerMaterial );
	SO_KIT_CATALOG_ENTRY_HEADER( mMarkerCoord );
	SO_KIT_CATALOG_ENTRY_HEADER( mMarkerSet );

public:
	/// Constructor
	SoXipPlot2Samples();

	/// Data points
	SoSFString		label;
	SoMFVec2f		data;
	SoSFEnum		markerType;
	SoSFColor		markerColor;
	SoSFFloat		markerTransparency;

	/// Class initialization
	static void initClass();

protected:
	/// Destructor
	virtual ~SoXipPlot2Samples();

	virtual void extractMarkerCoords();

	virtual void GLRender( SoGLRenderAction* action );

	virtual void getBoundingBox( SoGetBoundingBoxAction* action );

	virtual SbBool setUpConnections( SbBool onOff, SbBool doItAlways = FALSE );		

private:
	static void dataSensorCB( void* userData, SoSensor* );	

	class SoFieldSensor*	mDataSensors[1];
};

#endif // SOXIPPLOT2SAMPLES_H
