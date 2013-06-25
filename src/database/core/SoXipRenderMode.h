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
#ifndef SOXIPRENDERMODE_H
#define SOXIPRENDERMODE_H

#include <vector>
#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/actions/SoActions.h>
#include <xip/inventor/core/SoXipRenderModeElement.h>
#include <xip/inventor/core/XipInventorUtils.h>


class SoFieldSensor;

class XIPIVCORE_API SoXipRenderMode : public SoNode
{
	SO_NODE_HEADER(SoXipRenderMode);

public:
	enum render_mode_t {
        MPR			= SoXipRenderModeElement::MPR,
        MAXIP		= SoXipRenderModeElement::MAXIP,
        MINIP		= SoXipRenderModeElement::MINIP,
        SSD			= SoXipRenderModeElement::SSD,
		COLORSSD	= SoXipRenderModeElement::SSD_COLOR,
        VRT			= SoXipRenderModeElement::VRT_COLOR,
		DRR			= SoXipRenderModeElement::DRR
	};

	SoSFEnum mode;

	static void initClass();
	SoXipRenderMode();

protected:
	XIP_DOACTION_HEADER();
};

#endif // SOXIPRENDERMODE_H
