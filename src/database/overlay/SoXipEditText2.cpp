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
#include <Inventor/actions/SoHandleEventAction.h>
#include <Inventor/SoPickedPoint.h>
#include <Inventor/events/SoMouseButtonEvent.h>
#include <Inventor/events/SoLocation2Event.h>
#include <Inventor/events/SoKeyboardEvent.h>
#include <Inventor/sensors/SoFieldSensor.h>
#include <xip/inventor/overlay/SoXipEditText2.h>
#include <string.h>
#include <xip/system/defines.h>

SO_NODE_SOURCE( SoXipEditText2 );

SoXipEditText2::SoXipEditText2()
{
	SO_NODE_CONSTRUCTOR( SoXipEditText2 );

	SO_NODE_ADD_FIELD( displayBBox, (FALSE) );
	SO_NODE_ADD_FIELD( isEditing, (FALSE) );

	mEditString = std::string( string.getValue().getString() );	

	mEditingSensor = new SoFieldSensor( editingSensorCB, this );
	mEditingSensor->setPriority(0);
	mEditingSensor->attach( &isEditing );
}

void
SoXipEditText2::initClass()
{
	SO_NODE_INIT_CLASS( SoXipEditText2, SoXipText2, "SoXipText2" );
}

SoXipEditText2::~SoXipEditText2()
{
	if( mEditingSensor )
		delete mEditingSensor;
	mEditingSensor = 0;
}

void
SoXipEditText2::onStringChange()
{
	mEditString = std::string( string.getValue().getString() );
}

void
SoXipEditText2::editingSensorCB( void* userData, SoSensor* )
{
	((SoXipEditText2 *) userData)->toggleEditing();
}

void
SoXipEditText2::toggleEditing()
{
	if( isEditing.getValue() )
	{
		SoXipCursor::setCursor( "EDIT" );

		mCursorPos = string.getValue().getLength();

		mEditString.insert( mCursorPos, 1, '_' );
	}
	else
	{
		mEditString.erase( mCursorPos, 1 );		
	}

	// Update the string without triggering the field sensor
	mStringSensor->detach();
	string.setValue( mEditString.c_str() );
	mStringSensor->attach( &string );
}

SbBool
SoXipEditText2::isPicked( SoHandleEventAction* action ) const
{
	const SoPickedPoint* pickedPoint = action->getPickedPoint();
	if( pickedPoint )
	{
		SoFullPath* path = (SoFullPath *) pickedPoint->getPath();

		return path->containsNode( this );
	}
	return FALSE;
}

void
SoXipEditText2::handleEvent( SoHandleEventAction* action )
{
    if( action->isHandled() )
		return ;
    
    // Mouse Press Event
    //
	if( SO_MOUSE_PRESS_EVENT( action->getEvent(), BUTTON1 ) )
	{
        if( isEditing.getValue() == TRUE && isPicked( action ) == FALSE )
		{            
            isEditing.setValue( FALSE );

            action->releaseGrabber();
            action->setHandled();
		}
        
        if( action->getEvent()->wasShiftDown() )
		{
			if( isEditing.getValue() == FALSE && isPicked( action ) == TRUE )
			{
				// Set editing mode to true. Set the grabber to get the next
				// keyboard events.
				isEditing.setValue( TRUE );

				action->setHandled();
				action->setGrabber( this );
			}
		}
	}
    
    // Mouse Move Event
    //
    else if( action->getEvent()->isOfType( SoLocation2Event::getClassTypeId() ) )
	{
        if( isEditing.getValue() || isPicked( action ) )
        {
            action->setHandled();
			SoXipCursor::setCursor( "EDIT" );
        }
	}
	
    // Keyboard Event
    //
	else if( action->getEvent()->isOfType( SoKeyboardEvent::getClassTypeId() ) && SO_KEY_PRESS_EVENT( action->getEvent(), ANY ) )
	{
		if( isEditing.getValue() )
		{
			action->setHandled();

			const SoKeyboardEvent* kEvent = (const SoKeyboardEvent *) action->getEvent();
			
			switch( kEvent->getKey() )
			{
			case SoKeyboardEvent::ESCAPE:
				isEditing.setValue( FALSE );				
				action->releaseGrabber();
				break ;
			case SoKeyboardEvent::KEY_DELETE:
				// Add -1 for the underscore, showing the cursor position
				if( mCursorPos < string.getValue().getLength() - 1)
					mEditString.erase( mCursorPos, 1 );

				break ;

			case SoKeyboardEvent::BACKSPACE:
				if ( mCursorPos > 0 )
					mEditString.erase( mCursorPos-- - 1, 1 );
				break ;

			case SoKeyboardEvent::LEFT_ARROW:
				if( mCursorPos > 0 )
					-- mCursorPos;
				break ;
				
			case SoKeyboardEvent::RIGHT_ARROW:
				if( mCursorPos < string.getValue().getLength() )
					++ mCursorPos;
				break ;

			case SoKeyboardEvent::RETURN:
				mEditString.insert( mCursorPos, 1, '\n' );
				++ mCursorPos;
				break ;

			default:
				{
					char printableChar;
					if( ( printableChar = kEvent->getPrintableCharacter() ) )
					{
						mEditString.insert( mCursorPos, 1, printableChar );
						++ mCursorPos;
					}
					else return ;						
				}
			}

			// Update the string without triggering the field sensor
			mStringSensor->detach();
			string.setValue( mEditString.c_str() );
			mStringSensor->attach( &string );
		}
	}
}


void
SoXipEditText2::GLRender(SoGLRenderAction *action)
{
	SoXipText2::GLRender( action );

	if( displayBBox.getValue() )
	{
		glPushAttrib(GL_POLYGON_BIT);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		const float *minf = mBBox.getMin().getValue(), *maxf = mBBox.getMax().getValue();

		glBegin(GL_QUADS);
		glVertex3f(minf[0], minf[1], minf[2]);
		glVertex3f(maxf[0], minf[1], maxf[2]);
		glVertex3f(maxf[0], maxf[1], maxf[2]);
		glVertex3f(minf[0], maxf[1], minf[2]);
		glVertex3f(minf[0], minf[1], minf[2]);
		glEnd();
		glPopAttrib();
	}
}
