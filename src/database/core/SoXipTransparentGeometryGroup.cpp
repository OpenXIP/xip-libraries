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
#include "SoXipTransparentGeometryGroup.h"
#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/actions/SoCallbackAction.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/actions/SoPickAction.h>
#include <Inventor/actions/SoGetBoundingBoxAction.h> 
#include <xip/inventor/core/SoXipTransparentGeometryGroupElement.h>


SO_NODE_SOURCE(SoXipTransparentGeometryGroup);


/** \fn SoXipTransparentGeometryGroup::SoXipTransparentGeometryGroup()
* All input and output fields are added and initialized here. 
* \return none
*/
SoXipTransparentGeometryGroup::SoXipTransparentGeometryGroup(void)
{
	SO_NODE_CONSTRUCTOR(SoXipTransparentGeometryGroup);
	SO_NODE_ADD_FIELD(directRendering, (FALSE));
	SO_NODE_ADD_FIELD(on, (TRUE));
}



/*! \fn SoXipTransparentGeometryGroup::~SoXipTransparentGeometryGroup()
 * \brief Destructor, cleans up internal data
 * \return None
 */
SoXipTransparentGeometryGroup::~SoXipTransparentGeometryGroup()
{
}


/*! \fn SoXipTransparentGeometryGroup::initClass()
 * Initializes this class. Called on dll initialization.
 * \return void
 */
void SoXipTransparentGeometryGroup::initClass(void)
{
	SO_NODE_INIT_CLASS(SoXipTransparentGeometryGroup, SoGroup, "Group");

	SO_ENABLE(SoGLRenderAction, SoXipTransparentGeometryGroupElement);
	SO_ENABLE(SoPickAction,     SoXipTransparentGeometryGroupElement);
	SO_ENABLE(SoCallbackAction, SoXipTransparentGeometryGroupElement);
	SO_ENABLE(SoGetBoundingBoxAction, SoXipTransparentGeometryGroupElement);
}


/*! \fn SoXipTransparentGeometryGroup::doAction(SoAction * action)
 *  Adds a node to the SoXipTransparentGeometryGroupElement in the current state
 *  \param action - the current state action, no action taken if input action is NULL
 *  \return void
 */
void SoXipTransparentGeometryGroup::doAction(SoAction * action)
{
	// don't do anything if turned off
	if (!on.isIgnored() && !on.getValue()) return;

	// add MPR plane element
	SoXipTransparentGeometryGroupElement::add(action->getState(), this);
}


/*! \fn SoXipTransparentGeometryGroup::GLRender(SoGLRenderAction * action) 
*  Derived inventor GLRender method, overrides to doAction
*  \param action - the current state action
*  \return void
*/
void SoXipTransparentGeometryGroup::GLRender(SoGLRenderAction * action)
{
	doAction(action);
}


/*! \fn SoXipTransparentGeometryGroup::callback(SoCallbackAction * action) 
*  Derived inventor callback method, overrides to doAction
*  \param action - the current state action
*  \return void
*/
void SoXipTransparentGeometryGroup::callback(SoCallbackAction * action)
{
	doAction(action);
}


/*! \fn SoXipTransparentGeometryGroup::pick(SoPickAction * action) 
*  Derived inventor pick method, overrides to doAction
*  \param action - the current state action
*  \return void
*/
void SoXipTransparentGeometryGroup::pick(SoPickAction * action)
{
	doAction(action);
}

/*! \fn SoXipTransparentGeometryGroup::getBoundingBox(SoGetBoundingBoxAction * action) 
*  Derived inventor getBoundingBox method, overrides to doAction
*  \param action - the current state action
*  \return void
*/
void SoXipTransparentGeometryGroup::getBoundingBox(SoGetBoundingBoxAction *action)
{
	doAction(action);
}

/*! \fn SoXipTransparentGeometryGroup::getChildByType(const SoType &type) const
*  Returns a child node of the given type if any, otherwise return null.
*  \param action - the current state action
*  \return void
*/
SoNode *SoXipTransparentGeometryGroup::getChildByType(const SoType &type) const
{
	for (int i = 0; i < getNumChildren(); i++)
	{
		SoNode *child = getChild(i);
		
		if (child->isOfType(type))
		{
			return child;
		}
	}

	return 0;
}
