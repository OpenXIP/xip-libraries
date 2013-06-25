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
#include "SoXipOverlayTranslationManip.h"

SO_NODE_SOURCE( SoXipOverlayTranslationManip );

SoXipOverlayTranslationManip::SoXipOverlayTranslationManip()
{
	SO_NODE_CONSTRUCTOR( SoXipOverlayTranslationManip );	

	mCanTranslate = FALSE;
}

SoXipOverlayTranslationManip::~SoXipOverlayTranslationManip()
{

}

void
SoXipOverlayTranslationManip::initClass()
{
	SO_NODE_INIT_CLASS( SoXipOverlayTranslationManip, 
		SoXipOverlayManipBase, "SoXipOverlayManipBase" );
}

void
SoXipOverlayTranslationManip::handleEvent( SoHandleEventAction* action )
{
	if (!on.getValue())
		return;
	
	
	SoXipOverlayManipBase::handleEvent( action );
	if( action->isHandled() )
		return ;

	const SoEvent* event = action->getEvent();

	if( SO_MOUSE_RELEASE_EVENT( event, BUTTON1 ) ) 
	{
		if( action->getGrabber() == this )
		{
			applyTransform( mActionNode );

			action->setHandled();
			action->releaseGrabber();
		}

		mCanTranslate			= FALSE;
		mPickedShape			= 0;
		mTransformationMatrix	= SbMatrix::identity();
	}
	else if( action->getEvent()->isOfType( SoLocation2Event::getClassTypeId() ) )
	{
		if( mCanTranslate && mPickedShape )
		{
			SbVec3f pos;
			if( getPoint( action, pos ) )
			{
				if( pos != mTransformationOrigin )
				{
					if( !action->getGrabber() )
					{
						action->setGrabber( this );
					}
					
					mTransformationMatrix.setTranslate( pos - mTransformationOrigin );			
					applyTransform( mActionNode );
						
					action->setHandled();

					mTransformationOrigin = pos;
				}
			}
		}
		else
		{
			SoXipManipulableShape* pickedShape = isShapePicked( action );
			if( pickedShape )
			{
				if( !pickedShape->isEditing() )
				{
					SoXipCursor::setCursor( "SEL_PAN" );
					action->setHandled();
				}
			}
		}	
	}
	else if( SO_MOUSE_PRESS_EVENT( action->getEvent(), BUTTON1 ) )
	{
		// Do not do anything if one key modifier was pressed
		if( event->wasShiftDown() || event->wasCtrlDown() || event->wasAltDown() )
			return ;

		if( mPickedShape )
		{
			// If the picked shape is being edited, then it has to be ignored by the
			// translation manip.
			//
			if( mPickedShape->isEditing() )
			{
				mPickedShape = 0;
			}
			else if( getPoint( action, mTransformationOrigin ) )
			{				
				mCanTranslate = TRUE;
				action->setHandled();
			}
		}
	}
}
