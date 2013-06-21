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
#ifndef SOXIPPICKACTION_H
#define SOXIPPICKACTION_H

#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/fields/SoMFVec3f.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFBitMask.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/events/SoMouseButtonEvent.h>
#include <Inventor/actions/SoActions.h>

class SoFieldSensor;


/*! \class SoXipPickAction
*  \brief A node for handling the mouse click evens and set picked point(s) to a field
*
* This node is typically used to group all nodes and property relevant 
* to a particular volume under one group such that a processing node 
* can apply the corresponding properties to the corresponding volume, 
* e.g. in a fusion scenario
*/
class SoXipPickAction : public SoNode
{
	SO_NODE_HEADER(SoXipPickAction);

public:

    /// Constructor, initilaize fields and defaults
    SoXipPickAction();

    /// Initializes the SoXipVolDataElement class
	static void initClass();

    /*! \enum keyButtonType
    * Types of special keyboard keys should be pressed in order for consideration for picking    
    */
	enum keyButtonType {
		SHIFT = 1, /*! shift key */
		CONTROL = 2 /*! control key */
	};

    /*! \enum mouseButtonType
    * Types mouse buttons to be used for consideration for picking    
    */
	enum mouseButtonType {
		BUTTON1 = SoMouseButtonEvent::BUTTON1, /*! button 1 (i.e. left for right handed mouse)*/
		BUTTON2 = SoMouseButtonEvent::BUTTON2, /*! button 2 (middle mouse) */
		BUTTON3 = SoMouseButtonEvent::BUTTON3  /*! button 3 (i.e. right for right handed mouse)*/
	};

    /// sets whether a special key should be pressed for mouse clicks to be considered for picking
	SoSFBitMask	key;
    /// sets which mouse button event should be used
	SoSFEnum	mouse;
    /// if true, sets whether picked points should be accumulated as multiple points, default = false
	SoSFBool	multiplePoints;

    /// the output picked point(s)
	SoMFVec3f	point;

protected:
    /// Destructor, dereference data
	virtual ~SoXipPickAction();

    /// overrides handle event method to compute and set mouse points to picked points
	virtual void handleEvent(SoHandleEventAction *action);
};

#endif // SOXIPPICKACTION_H
