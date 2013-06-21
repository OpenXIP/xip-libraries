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
#ifndef SOXIPTRANSPARENTGEOMETRYGROUP_H
#define SOXIPTRANSPARENTGEOMETRYGROUP_H

#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/fields/SoSFBool.h>
#include <xip/inventor/core/xipivcore.h>


/*! \class SoXipTransparentGeometryGroup
*  \brief A volume group for collecting nodes relevant to a volume
*
* This node is typically used to group all nodes and property relevant 
* to a particular volume under one group such that a processing node 
* can apply the corresponding properties to the corresponding volume, 
* e.g. in a fusion scenario
*/
class XIPIVCORE_API SoXipTransparentGeometryGroup : public SoGroup 
{
	SO_NODE_HEADER(SoXipTransparentGeometryGroup);

public:
    /// Constructor, initilaize fields and defaults
    SoXipTransparentGeometryGroup();

    /// Initializes the SoXipTransparentGeometryDataElement class
	static void initClass();

    /// returns a child node within this group, if any
    virtual SoNode *getChildByType(const SoType &type) const;

    /// field enable/disables this group
    SoSFBool on;

    /// field renders immediately or delayed rendering
    SoSFBool directRendering;

protected:
    /// Destructor, dereference data
	virtual ~SoXipTransparentGeometryGroup();

    /// Performs the action, sets the crop box data
	virtual void doAction(SoAction * action);

    /// Performs GL render action
	virtual void GLRender(SoGLRenderAction * action);

    /// Performs the callback
	virtual void callback(SoCallbackAction * action);

    /// Performs the pick action
	virtual void pick(SoPickAction * action);

    /// Performs the bounding box computation action
	virtual void getBoundingBox (SoGetBoundingBoxAction *action);
};

#endif // SOXIPTRANSPARENTGEOMETRYGROUP_H
