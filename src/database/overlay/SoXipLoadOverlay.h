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
*	@file	SoXipLoadOverlay.h
*	@brief	Declaration of the SoXipLoadOverlay class
*	@author	Julien Gein
**/

#ifndef SOXIPLOADOVERLAY_H
#define SOXIPLOADOVERLAY_H

#include <Inventor/engines/SoSubEngine.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoMFNode.h>
#include <Inventor/fields/SoSFTrigger.h>

/**
*	@class SoXipLoadOverlay
*
* Engine that can load overlays from an external file
*
**/
class SoXipLoadOverlay : public SoEngine
{
	SO_ENGINE_HEADER( SoXipLoadOverlay );

public:
	/// Constructor
	SoXipLoadOverlay();

	/// Path to the file
	SoSFString		filename;
	/// Load trigger
	SoSFTrigger		load;

	/// Overlays found in the given file (SoMFNode)
	SoEngineOutput	overlays;

	/// Open Inventor class initialization
	static void initClass();

protected:
	/// Destructor
	~SoXipLoadOverlay();

	/// Engines inputChanged method
	virtual void inputChanged( SoField* whichField );
	/// Engines evaluate method
	virtual void evaluate();

};

#endif // SOXIPLOADOVERLAY_H
