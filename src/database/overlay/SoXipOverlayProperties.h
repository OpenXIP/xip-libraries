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
#ifndef SOXIPOVERLAYPROPERTIES_H
#define SOXIPOVERLAYPROPERTIES_H

#include <Inventor/engines/SoSubEngine.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoSFTrigger.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoMFNode.h>

class SoXipOverlayProperties : public SoEngine
{
	SO_ENGINE_HEADER( SoXipOverlayProperties );

public:
	SoXipOverlayProperties();

	SoMFNode		overlays;
	SoSFString		label;
	SoSFTrigger		addLabel;
	SoSFTrigger		clearLabel;
	SoSFString		caption;
	SoSFTrigger		setCaption;
	SoSFInt32		rank;
	SoSFTrigger		setRank;

	SoEngineOutput	status;

	static void initClass();

protected:
	~SoXipOverlayProperties();

	virtual void inputChanged( SoField* whichField );
	virtual void evaluate();

	SoField*		m_Trigger;

};

#endif // SOXIPOVERLAYPROPERTIES_H
