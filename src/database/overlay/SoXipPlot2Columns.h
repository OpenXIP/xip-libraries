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
*	@file	SoXipPlot2Columns.h
*	@brief	Declaration of the SoXipPlot2Columns class
*	@author	Julien Gein
**/

#ifndef SOXIPPLOT2COLUMNS_H
#define SOXIPPLOT2COLUMNS_H

#include <Inventor/nodekits/SoSubKit.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/fields/SoSFColor.h>
#include <Inventor/fields/SoSFShort.h>
#include <Inventor/fields/SoSFString.h>

class SoXipPlot2Columns : public SoBaseKit
{
	SO_KIT_HEADER( SoXipColumnChart );

	SO_KIT_CATALOG_ENTRY_HEADER( mMainSeparator );

	SO_KIT_CATALOG_ENTRY_HEADER( mVertices );

	SO_KIT_CATALOG_ENTRY_HEADER( mBorderSeparator );
	SO_KIT_CATALOG_ENTRY_HEADER( mBorderColor );
	SO_KIT_CATALOG_ENTRY_HEADER( mBorderStyle );
	SO_KIT_CATALOG_ENTRY_HEADER( mBorderLines );

	SO_KIT_CATALOG_ENTRY_HEADER( mFaceSeparator );
	SO_KIT_CATALOG_ENTRY_HEADER( mFaceMaterial );
	SO_KIT_CATALOG_ENTRY_HEADER( mFaces );

public:
	/// Constructor
	SoXipPlot2Columns();

	SoSFString	label;
	SoMFFloat	data;
	SoSFColor	faceColor;
	SoSFFloat	faceTransparency;
	SoSFColor	borderColor;
	SoSFShort	borderWidth;

	/// Class initialization
	static void initClass();

protected:
	/// Destructor
	virtual ~SoXipPlot2Columns();

	virtual void setVertices();

	virtual void GLRender( SoGLRenderAction* action );

	virtual SbBool setUpConnections( SbBool onOff, SbBool doItAlways = FALSE );	

private:
	static void dataSensorCB( void* userData, SoSensor* );

	class SoFieldSensor*	mDataSensor;

};

#endif // SOXIPPLOT2COLUMNS_H
