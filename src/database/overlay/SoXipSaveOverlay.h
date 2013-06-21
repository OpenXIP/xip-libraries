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
*	@file    SoXipSaveOverlay.h
*	@brief   Declaration of the SoXipSaveOverlay engine
*	@author  Julien Gein
**/

#ifndef SOXIPSAVEOVERLAY_H
#define SOXIPSAVEOVERLAY_H

#include <Inventor/engines/SoSubEngine.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoMFNode.h>
#include <Inventor/fields/SoSFTrigger.h>

/**
*	@class	SoXipSaveOverlay
*	@brief	Engine used to save overlays to an external file
*
**/
class SoXipSaveOverlay : public SoEngine
{
	SO_ENGINE_HEADER( SoXipSaveOverlay );

public:
	/// Constructor
	SoXipSaveOverlay();

	/// filename
	SoSFString		filename;
	/// list of overlays to be saved
	SoMFNode		overlays;
	/// perform the save operation
	SoSFTrigger		save;

	/// Engine dummy output (to allow serialization to file)
	SoEngineOutput	status;

	/// Open Inventor class initialization
	static void initClass();

protected:
	/// Destructor
	~SoXipSaveOverlay();

	/// Engine inputChanged method
	virtual void inputChanged( SoField* whichField );

	/// Engine evaluate method
	virtual void evaluate();

	/// Read instance method
	virtual SbBool readInstance( SoInput* in, unsigned short flags );

	SbBool			m_ReadInstance;
	
};

#endif // SOXIPSAVEOVERLAY_H
