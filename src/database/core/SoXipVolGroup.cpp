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
#include "SoXipVolGroup.h"
#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/actions/SoCallbackAction.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/actions/SoPickAction.h>
#include <Inventor/actions/SoGetBoundingBoxAction.h> 
#include <xip/inventor/core/SoXipVolGroupElement.h>


SO_NODE_SOURCE(SoXipVolGroup);


/** \fn SoXipVolGroup::SoXipVolGroup()
* All input and output fields are added and initialized here. 
* \return none
*/
SoXipVolGroup::SoXipVolGroup(void)
{
	SO_NODE_CONSTRUCTOR(SoXipVolGroup);

	SO_NODE_ADD_FIELD(on, (TRUE));
}



/*! \fn SoXipVolGroup::~SoXipVolGroup()
 * \brief Destructor, cleans up internal data
 * \return None
 */
SoXipVolGroup::~SoXipVolGroup()
{
}


/*! \fn SoXipVolGroup::initClass()
 * Initializes this class. Called on dll initialization.
 * \return void
 */
void SoXipVolGroup::initClass(void)
{
	SO_NODE_INIT_CLASS(SoXipVolGroup, SoGroup, "Group");

	SO_ENABLE(SoGLRenderAction, SoXipVolGroupElement);
	SO_ENABLE(SoPickAction,     SoXipVolGroupElement);
	SO_ENABLE(SoCallbackAction, SoXipVolGroupElement);
	SO_ENABLE(SoGetBoundingBoxAction, SoXipVolGroupElement);
}


/*! \fn SoXipVolGroup::doAction(SoAction * action)
 *  Adds a node to the SoXipVolGroupElement in the current state
 *  \param action - the current state action, no action taken if input action is NULL
 *  \return void
 */
void SoXipVolGroup::doAction(SoAction * action)
{
	// don't do anything if turned off
	if (!on.isIgnored() && !on.getValue()) return;

	// add MPR plane element
	SoXipVolGroupElement::add(action->getState(), this);
}


/*! \fn SoXipVolGroup::GLRender(SoGLRenderAction * action) 
*  Derived inventor GLRender method, overrides to doAction
*  \param action - the current state action
*  \return void
*/
void SoXipVolGroup::GLRender(SoGLRenderAction * action)
{
	doAction(action);
}


/*! \fn SoXipVolGroup::callback(SoCallbackAction * action) 
*  Derived inventor callback method, overrides to doAction
*  \param action - the current state action
*  \return void
*/
void SoXipVolGroup::callback(SoCallbackAction * action)
{
	doAction(action);
}


/*! \fn SoXipVolGroup::pick(SoPickAction * action) 
*  Derived inventor pick method, overrides to doAction
*  \param action - the current state action
*  \return void
*/
void SoXipVolGroup::pick(SoPickAction * action)
{
	doAction(action);
}

/*! \fn SoXipVolGroup::getBoundingBox(SoGetBoundingBoxAction * action) 
*  Derived inventor getBoundingBox method, overrides to doAction
*  \param action - the current state action
*  \return void
*/
void SoXipVolGroup::getBoundingBox(SoGetBoundingBoxAction *action)
{
	doAction(action);
}

/*! \fn SoXipVolGroup::getChildByType(const SoType &type) const
*  Returns a child node of the given type if any, otherwise return null.
*  \param action - the current state action
*  \return void
*/
SoNode *SoXipVolGroup::getChildByType(const SoType &type) const
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
