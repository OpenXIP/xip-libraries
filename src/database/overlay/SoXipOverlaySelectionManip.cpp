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
#include <xip/inventor/core/SoXipCursor.h>
#include <Inventor/SoPickedPoint.h>
#include <Inventor/actions/SoHandleEventAction.h>
#include <Inventor/events/SoMouseButtonEvent.h>
#include <Inventor/events/SoLocation2Event.h>
#include  <xip/inventor/overlay/SoXipManipulableShape.h>
#include "SoXipOverlaySelectionManip.h"
#include <xip/inventor/overlay/XipOverlayUtils.h>

SO_NODE_SOURCE( SoXipOverlaySelectionManip );

SoXipOverlaySelectionManip::SoXipOverlaySelectionManip()
{
	SO_NODE_CONSTRUCTOR( SoXipOverlaySelectionManip );	
}

SoXipOverlaySelectionManip::~SoXipOverlaySelectionManip()
{

}

void
SoXipOverlaySelectionManip::initClass()
{
	SO_NODE_INIT_CLASS( SoXipOverlaySelectionManip, 
		SoXipOverlayManipBase, "SoXipOverlayManipBase" );
}

void
SoXipOverlaySelectionManip::handleEvent( SoHandleEventAction* action )
{
	if( !on.getValue() )
		return ;
	
	
	SoXipOverlayManipBase::handleEvent( action );
	if( action->isHandled() )
		return ;

	if( SO_MOUSE_RELEASE_EVENT( action->getEvent(), BUTTON1 ) )
	{
		if( !mPickedShape )
			updateShapesStatus( action );

		mPickedShape = 0;
	}
	else if( SO_MOUSE_PRESS_EVENT( action->getEvent(), BUTTON1 ) )
	{
		if( action->getEvent()->wasShiftDown() )
		{
			updateShapesStatus( action );
		}
		else if( action->getEvent()->wasCtrlDown() )
		{
			if( mPickedShape )
			{
				// Add or remove this shape from the selection
				//
				mPickedShape->select( !mPickedShape->isSelected() );

				updateShapesStatus( action, FALSE );
			}

			// The selection manip should not handle the event in case
			// there is a translation manip behind it that needs both
			// the event to be not handled and the shape to be selected.
			// In case the user press CTRL, forget about this rule, just
			// add/ remove the shape from the selection.
			action->setHandled();
		}
		else if( mPickedShape && mPickedShape->isEditing() )
		{
			// Do nothing
		}
		else if( mPickedShape && !mPickedShape->isSelected() )
		{
			// If the picked shape is already selected, do not change
			// the state of the current selection. Otherwise, discard
			// the current selection and add the picked shape to it.
			//
			updateShapesStatus( action );

			mPickedShape->select();
		}
		else if( mPickedShape && mPickedShape->isTextPicked() )
		{
			// If the text is picked, it means the user does not want
			// to translate the other selected shapes. What he wants is
			// only translating the text. Then we need to clear the
			// selection and add the shape the text belongs to.
			updateShapesStatus( action );

			mPickedShape->select();
		}
		else if( !mPickedShape )
		{
			updateShapesStatus( action );
		}
	}
}

void
SoXipOverlaySelectionManip::updateShapesStatus( SoHandleEventAction* action,
											    SbBool unselect,
												SbBool finishEditing )
{
	if( mActionNode )
	{
		SoNodeList shapes = XipOverlayUtils::getManipulableShapes( mActionNode, FALSE );
		for( int i = 0; i < shapes.getLength(); ++ i )
		{
			SoXipManipulableShape* shape = (SoXipManipulableShape *) shapes[i];

			if( unselect && shape->isSelected() )
				shape->select( FALSE );
			
			if( finishEditing && shape->isEditing() )
				shape->status.setValue( SoXipShape::NONE );
		}
	}
}
