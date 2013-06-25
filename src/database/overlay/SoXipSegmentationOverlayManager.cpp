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
// Disable the warning raised because of the std::map<>
#pragma warning ( disable : 4786 )

#include <xip/inventor/core/SoXipDataImage.h>
#include <xip/inventor/core/SoXipDataImageElement.h>
#include <Inventor/actions/SoCallbackAction.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/actions/SoHandleEventAction.h>
#include <Inventor/actions/SoRayPickAction.h>
#include <Inventor/actions/SoWriteAction.h>
#include <Inventor/actions/SoSearchAction.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoSwitch.h>
#include <Inventor/nodes/SoBaseColor.h>
#include <Inventor/nodes/SoLabel.h>
#include <Inventor/sensors/SoFieldSensor.h>
#include <Inventor/sensors/SoNodeSensor.h>
#include <Inventor/sensors/SoTimerSensor.h>
#include "SoXipSegmentationOverlayManager.h"
#include <xip/inventor/overlay/SoXipShape.h>
#include "SoXipContour.h"
#include "SoXipLine.h"
#include "SoXipShapeList.h"
#include <xip/inventor/overlay/XipOverlayUtils.h>
// Inventor events
#include <Inventor/events/SoMouseButtonEvent.h>
#include <Inventor/events/SoLocation2Event.h>
#include <Inventor/events/SoKeyboardEvent.h>

#include <xip/system/standard.h>

SO_NODE_SOURCE( SoXipSegmentationOverlayManager );

SoXipSegmentationOverlayManager::SoXipSegmentationOverlayManager()
{
	SO_NODE_CONSTRUCTOR( SoXipSegmentationOverlayManager );

	SO_NODE_ADD_FIELD( OverlayOption, ("") );
	//SO_NODE_ADD_FIELD( OverlayAction, (0) );
	//SO_NODE_ADD_FIELD( OverlayEnable, (true) );

	//!
	mMouseDownTime			= SbTime::zero();
	mMouseUpTime			= SbTime::zero();
	mMouseDownPos			= SbVec2s(-1, -1);

}

SoXipSegmentationOverlayManager::~SoXipSegmentationOverlayManager()
{
}

void SoXipSegmentationOverlayManager::initClass()
{
	SO_NODE_INIT_CLASS( SoXipSegmentationOverlayManager, SoXipOverlayManager, "SoXipOverlayManager" );
}

void SoXipSegmentationOverlayManager::GLRender( SoGLRenderAction* action )
{
	int numShapes = 0 ;

    SoXipOverlayManager::GLRender( action );
}

void SoXipSegmentationOverlayManager::handleEvent( SoHandleEventAction* action )
{
	int numShapes = 0 ;
	SoXipShapeList* list = getCurrentList ( ) ;
	if (list != NULL) numShapes = list->getNumChildren ( ) ;

	//if (numShapes > 0)
	//{
	//	SoXipShape *pshape = (SoXipShape*)list->getChild(numShapes-1) ;
	//	if (pshape != NULL) SetupOverlayAction ( action, pshape ) ;
	//}

	if( action->isHandled() ) return ;
	
	SoXipOverlayManager::handleEvent( action );

	if (list != NULL)
	{
		int nnumShapes = list->getNumChildren ( ) ;
		//! A shape created 
		if (nnumShapes > numShapes)
		{
		    // Returns pointer to nth child node
			SoXipShape *pshape = (SoXipShape*)list->getChild(numShapes) ;
			if (pshape != NULL) SetupOverlayOption ( pshape, OverlayOption ) ;
		}
	}
}

void SoXipSegmentationOverlayManager::pick( SoPickAction* action)
{
	SoXipOverlayManager::pick( action );
}

void SoXipSegmentationOverlayManager::callback( SoCallbackAction* action)
{
	SoXipOverlayManager::callback( action );
}

int SoXipSegmentationOverlayManager::SetupOverlayOption ( SoXipShape *pshape, SoMFString& OO )
{
	if (pshape == NULL) return ( 0 ) ;

	const SbString& classname = shapeClassName.getValue();

	int sh, len ;
	SbString *pstr ;
	char *sz, szTemp[256] ;
	char *szPrefix =  "SoXip" ;
	char *szSuffix =  "/SoXip" ;

	{
		char *szName = (char*)classname.getString () ;
		//
		if (szName == NULL) return ( 0 ) ;
		pstr = (SbString*)OO.getValues ( 0 ) ;
		if (pstr == NULL) return ( 0 ) ;
	
		//! Default operations 
		strncpy ( szTemp, szName, 5 ) ; szTemp[5] = 0 ;
#ifdef WIN32
		if (stricmp ( szTemp, szPrefix ) == 0)
#else
		if (strcasecmp ( szTemp, szPrefix ) == 0)
#endif /* WIN32 */
		{
			pshape->setRank ( -1 ) ;
		}

#ifdef WIN32
		if (stricmp ( szName, "SoXipContour" ) == 0)
#else
		if (strcasecmp ( szName, "SoXipContour" ) == 0)
#endif /* WIN32 */
		{
			SoXipContour *p = (SoXipContour*)pshape ;
			//! Default settings
			//p->closeOnDblClick = false ;
			//p->closed = false ;

			for (sh=0; sh<OO.getNum(); sh++)
			{
				sz = (char*)pstr[sh].getString ( ) ; if (sz == NULL) continue ;
				len = pstr[sh].getLength ( ) ; if (len < 1) continue ;

				//if (stricmp ( sz, "NonClosed" ) == 0)	{ p->closed = false ;	p->closeOnDblClick = false ;	continue ; }
				//if (stricmp ( sz, "Closed" ) == 0)		{ p->closed = true ;	p->closeOnDblClick = true ;		continue ; }
				// SoDebugError::postInfo ( szName, sz ) ;
			}
		}
	}

	return ( 1 ) ;
}

int SoXipSegmentationOverlayManager::SetupOverlayAction ( SoHandleEventAction* action, SoXipShape *pshape )
{
	// Maximal distance between two consecutive mouse down positions
	// allowed to generate a double-click.
	int DoubleClickMaxJump = 2;
	// Maximal time between two mouse clicks to be considered as a
	// double-click.
	SbTime DoubleClickTime = SbTime(0.5);
	// Time corresponding to a click
	SbTime ClickTime = SbTime(0.1);

	if (pshape == NULL) return ( 0 ) ;
	const SbString& classname = shapeClassName.getValue();
	char *szName = (char*)classname.getString () ;
	if (szName == NULL) return ( 0 ) ;

	SoDebugError::postInfo ( szName, "test" ) ;

	SbVec3f pos;
	const SbVec2s& mousePosition = action->getEvent()->getPosition() ;
	
	//if( SO_MOUSE_RELEASE_EVENT( action->getEvent(), BUTTON1 ) && action->getGrabber() == this ) 
	if( SO_MOUSE_RELEASE_EVENT( action->getEvent(), BUTTON1 )) 
	{
		SoDebugError::postInfo ( szName, "test" ) ;
		mMouseUpTime = action->getEvent()->getTime();
		{
		}
	}
	else if( SO_MOUSE_PRESS_EVENT( action->getEvent(), BUTTON1 ) )
	{
		SbTime tim = action->getEvent()->getTime();

		// Compute the distance between the last mouse press event and this one
		SbVec2s v = (mMouseDownPos - mousePosition);
		float mouseJump = sqrtf( v.dot(v) );

		// Do not perform a double-click if the time between two mouse press
		// events is higher than the default time set for double-clicks, or if
		// the mouse jumped further than the tolerance set (without tolerance
		// it is more difficult to get a double-click.
		if ( (tim - mMouseDownTime) < DoubleClickTime && mouseJump < DoubleClickMaxJump )
		{
			mMouseDownTime = SbTime::zero();
			mMouseDownPos = SbVec2s(-1, -1);
		}
		else
		{
			mMouseDownTime = action->getEvent()->getTime() ;
		}
	}

	return ( 1 ) ;
}


