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
#include <algorithm>
#include <vector>

#include <xip/system/standard.h>

#ifdef WIN32
# include <winuser.h>
#endif

#include <xip/inventor/core/SoXipCursor.h>

#include <Inventor/SoPickedPoint.h>
#include <Inventor/actions/SoHandleEventAction.h>
#include <Inventor/actions/SoRayPickAction.h>
#include <Inventor/actions/SoWriteAction.h>
#include <Inventor/actions/SoSearchAction.h>
#include <Inventor/events/SoMouseButtonEvent.h>
#include <Inventor/events/SoKeyboardEvent.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoSwitch.h>
#include <Inventor/sensors/SoFieldSensor.h>

#include "SoXipOverlayManager.h"
#include <xip/inventor/overlay/SoXipEditableShape.h>
#include "SoXipShapeList.h"
#include <xip/inventor/overlay/SoXipOverlayManipBase.h>
#include "SoXipMenu.h"
#include "SoXipMenuItem.h"
#include "SoXipMenuItemSeparator.h"
#include <xip/inventor/overlay/XipOverlayUtils.h>
#include <xip/system/defines.h>

SO_NODE_SOURCE( SoXipOverlayManager );

SoXipOverlayManager::SoXipOverlayManager()
{
	SO_NODE_CONSTRUCTOR( SoXipOverlayManager );

	// Main separators
	SO_XIP_KIT_ADD_ENTRY( mTopSeparator, SoSeparator, this );
	SO_XIP_KIT_ADD_ENTRY( mGeomSeparator, SoSeparator, mTopSeparator );
	// Shapes
	SO_XIP_KIT_ADD_TYPE_ENTRY( mShapeSwitch, SoSwitch, mGeomSeparator );
	SO_XIP_KIT_ADD_ENTRY( mShapeList, SoXipShapeList, mShapeSwitch );

	mShapeSwitch->whichChild.setValue(0);

	// Menu
	SO_XIP_KIT_ADD_ENTRY( mMenuSwitch, SoSwitch, mTopSeparator );
	SO_XIP_KIT_ADD_ENTRY( mMenuSeparator, SoSeparator, mMenuSwitch );
	SO_XIP_KIT_ADD_ENTRY( mMenuFont, SoFont, mMenuSeparator );
	SO_XIP_KIT_ADD_ENTRY( mMenuNoShadows, SoXipDropShadowStyle, mMenuSeparator );
	SO_XIP_KIT_ADD_ENTRY( mMenuStyle, SoXipMenuStyle, mMenuSeparator );
	SO_XIP_KIT_ADD_ENTRY( mMenuCamera, SoXipWidgetCamera, mMenuSeparator );
	SO_XIP_KIT_ADD_TYPE_ENTRY( mMenu, SoXipMenu, mMenuSeparator );

	((SoSFColor *) mMenuStyle->getField( "disabledTextColor" ))->setValue( 0.3, 0.3, 0.2 );
	((SoSFFloat *) mMenuFont->getField( "size" ))->setValue( 10 );

	SO_NODE_ADD_FIELD(    menuEnabled,          (FALSE) );
	SO_NODE_ADD_FIELD(         create,          (FALSE) );
	SO_NODE_ADD_FIELD( shapeClassName, ("SoXipEllipse") );
	SO_NODE_ADD_FIELD(     shapeLabel,             ("") );
	SO_NODE_ADD_FIELD(   shapeCaption,             ("") );
	SO_NODE_ADD_FIELD( multipleShapes,           (TRUE) );
	SO_NODE_ADD_FIELD(       overlays,              (0) );
	SO_NODE_ADD_FIELD(            add,               () );
	SO_NODE_ADD_FIELD(         remove,               () );
	SO_NODE_ADD_FIELD(          clear,               () );
	SO_NODE_ADD_FIELD(		     node,				(0)	);
	shapeLabel.setNum(0);

	mMenuEnabledSensor = new SoFieldSensor( menuEnabledSensorCB, this );
	mMenuEnabledSensor->attach( &menuEnabled );
	mMenuEnabledSensor->setPriority(0);

	mMenuClickSensor = new SoFieldSensor( menuClickSensorCB, this );
	mMenuClickSensor->setPriority(0);

	SoField* watchFields[] = { &add, &remove, &clear };

	for( int i = 0; i < 3; ++ i )
	{
		mFieldSensors[i] = new SoFieldSensor( fieldSensorCB, this );
		mFieldSensors[i]->attach( watchFields[i] );
		mFieldSensors[i]->setPriority(0);
	}

	initContextMenu();

	setUpConnections( TRUE, TRUE );

	mActionNode = 0;

	// Force the manager to propagate the search action through its children
	// This allows the manipulators to get the overlays by using a search action
	//
	setSearchingChildren( TRUE );
}

SoXipOverlayManager::~SoXipOverlayManager()
{
	if( mMenuClickSensor )
	{
		delete mMenuClickSensor;
		mMenuClickSensor = 0;
	}

	if( mMenuEnabledSensor )
	{
		delete mMenuEnabledSensor;
		mMenuEnabledSensor = 0;
	}

	for( int i = 0; i < 3; ++ i )
	{
		delete mFieldSensors[i];
		mFieldSensors[i] = 0;
	}
}

void
SoXipOverlayManager::initClass()
{
	SO_NODE_INIT_CLASS( SoXipOverlayManager, SoXipKit, "SoXipKit" );
}

SbBool
SoXipOverlayManager::setUpConnections( SbBool onOff, SbBool doItAlways )
{
    if( !doItAlways && connectionsSetUp == onOff )
		return onOff;

	try
	{
		if ( onOff )
		{
			// We connect AFTER base class.
			SoXipKit::setUpConnections( onOff, FALSE );

			if( mMenuClickSensor->getAttachedField() != &mMenu->itemClicked )
				mMenuClickSensor->attach( &mMenu->itemClicked );
		}
		else
		{
			// We disconnect BEFORE base class.

			if( mMenuClickSensor->getAttachedField() )
				mMenuClickSensor->detach();

			SoXipKit::setUpConnections( onOff, FALSE );
		}
	}
	catch(...)
	{
		SoDebugError::post( __FILE__, "Cannot setup connections" );
		return true;
	}

    return !( connectionsSetUp = onOff );
}

SoXipShape*
SoXipOverlayManager::isShapePicked( SoHandleEventAction* action )
{
	SoRayPickAction pa( action->getViewportRegion() );
	pa.setPoint( action->getEvent()->getPosition() );
	pa.setRadius( 3 );
	pa.setPickAll( TRUE );
	pa.enableCulling( FALSE );
	pa.apply( action->getNodeAppliedTo() );

	SoPickedPointList pickedPoints = pa.getPickedPointList();
	for( int i = 0; i < pickedPoints.getLength(); ++ i )
	{
		SoPath* path = pickedPoints[i]->getPath();
		if( !path->containsNode( this ) )
			continue ;
		
		SoFullPath* fullpath = (SoFullPath *) path;
		for( int i = 0; i < fullpath->getLength(); ++ i )
		{
			if( fullpath->getNode(i)->isOfType( SoXipShape::getClassTypeId() ) )
				return (SoXipShape *) fullpath->getNode(i);
		}
	}
	return 0;
}

void
SoXipOverlayManager::handleEvent( SoHandleEventAction* action )
{
	if( action->isHandled() )
		return ;

	const SoEvent* event = action->getEvent();
	if( !event )
		return ;

	if( !action->getGrabber() )
	{
		mActionNode = action->getNodeAppliedTo();
	}

	if( event->isOfType( SoKeyboardEvent::getClassTypeId() ) && SO_KEY_PRESS_EVENT( event, ANY ) )
	{
		const SoKeyboardEvent* keyEvent = (const SoKeyboardEvent *) event;

		if( event->wasCtrlDown() )
		{
			if( keyEvent->getKey() == SoKeyboardEvent::V )
			{
				onPaste();
			}
			else if( keyEvent->getKey() == SoKeyboardEvent::C )
			{
				mSelection = XipOverlayUtils::getTopLevelShapes( mShapeSwitch, TRUE );	
				onCopy();
			}
			else if( keyEvent->getKey() == SoKeyboardEvent::X )
			{
				mSelection = XipOverlayUtils::getTopLevelShapes( mShapeSwitch, TRUE );	
				onCopy();
				onDelete();
			}
		}
		else if( keyEvent->getKey() == SoKeyboardEvent::KEY_DELETE )
		{
			mSelection = XipOverlayUtils::getTopLevelShapes( mShapeSwitch, TRUE );	
			if (onDelete())
				action->setHandled();
		}
	}

	else if( SO_MOUSE_PRESS_EVENT( action->getEvent(), BUTTON3 ) && menuEnabled.getValue() )
	{
		SoXipCursor::setCursor();
		
		mMousePosition = action->getEvent()->getPosition();
		
		mMenu->position.setValue( action->getEvent()->getNormalizedPosition( action->getViewportRegion() ) );
		mMenu->on.setValue( TRUE );

		action->setGrabber( mMenu );
		action->setHandled();

		mMenu->enableItem(         "Copy", FALSE );
		mMenu->enableItem(          "Cut", FALSE );
		mMenu->enableItem(  "Edit Points", FALSE );
		mMenu->enableItem(   "Nudge Tool", FALSE );
		mMenu->enableItem(     "Cut Tool", FALSE );
		mMenu->enableItem(    "Add Point", FALSE );
		mMenu->enableItem( "Delete Point", FALSE );

		mSelection = XipOverlayUtils::getTopLevelShapes( mShapeSwitch, TRUE );	

		SoXipShape* pickedShape = isShapePicked( action );
		if( pickedShape )
		{
			if( !pickedShape->isSelected() )
			{
				for( int i = 0; i < mSelection.getLength(); ++ i )
				{
					((SoXipShape *) mSelection[i])->select( FALSE );
				}

				mSelection.truncate(0);
				mSelection.append( pickedShape );
			}

			mMenu->enableItem( "Copy", TRUE );
			mMenu->enableItem(  "Cut", TRUE );

			if( mSelection.getLength() == 1 )
			{
				if( pickedShape->isOfType( SoXipEditableShape::getClassTypeId() ) )
				{
					SoXipEditableShape* editShape = (SoXipEditableShape *) pickedShape;

					mMenu->enableItem( "Edit Points", TRUE );
					mMenu->enableItem(  "Nudge Tool", TRUE );
					mMenu->enableItem(    "Cut Tool", TRUE );

					if( pickedShape->isEditing() )
					{
						mMenu->enableItem( "Add Point", TRUE );

						mPickedControlPoint = editShape->pickControlPoint( action );
						if( mPickedControlPoint != -1 )
							mMenu->enableItem( "Delete Point", TRUE );
					}
				}
			}
		}
		else 
		{
			for( int i = 0; i < mSelection.getLength(); ++ i )
			{
				((SoXipShape *) mSelection[i])->select( FALSE );
			}
			mSelection.truncate(0);
		}

		return ;
	}
	else if( SO_MOUSE_PRESS_EVENT( action->getEvent(), BUTTON1 ) &&
		! action->getEvent()->wasShiftDown() &&
		! action->getEvent()->wasCtrlDown() )
	{
		SoXipKit::handleEvent( action );
		if( action->isHandled() )
			return ;

		if( create.getValue() )
		{
			if( multipleShapes.getValue() || getCurrentList()->getNumChildren() == 0 )
			{
				int nextRank = getNextRank();

				SoXipShape* shape = createNewShape();
				if( shape )
				{
					shape->setLabel( shapeLabel );
					shape->setRank( nextRank );
					shape->setCaption( shapeCaption.getValue() );

					node.setValue(shape);

					SoXipKit::handleEvent( action );
				}
				return ;
			}
		}
	}

	SoXipKit::handleEvent( action );
}

int
SoXipOverlayManager::getNextRank()
{
	SoNodeList shapes = XipOverlayUtils::getTopLevelShapes( getCurrentList() );

	int numShapes = shapes.getLength();
	if( numShapes == 0 )
		return 1;
	
	std::vector< int > ranks(numShapes, 1);
	for( int i = 0; i < numShapes; ++ i )
	{
		ranks[i] = ((SoXipShape *) shapes[i])->rank.getValue();
	}

	std::sort( ranks.begin(), ranks.end() );

	for( int j = 0 ; j < numShapes; ++ j )
	{
		if( ranks[j] > j + 1 )
			return j + 1;
	}

	return numShapes + 1;
}

SoXipShape*
SoXipOverlayManager::createNewShape()
{
	const SbString& classname = shapeClassName.getValue();

	SoXipShapeList* currentList = getCurrentList();

	if( currentList )
	{
		SoType type = SoType::fromName( classname );
		if( !type.canCreateInstance() )
		{
			SoDebugError::post( __FILE__, "Unknown shape type '%s'", classname  );
			return 0;
		}

		if( !type.isDerivedFrom( SoXipShape::getClassTypeId() ) )
		{
			SoDebugError::post( __FILE__, "Invalid shape class '%s'", classname );
			return 0;
		}

		SoXipShape* newShape = (SoXipShape *) type.createInstance();
		if( !newShape )
		{
			SoDebugError::post( __FILE__, "Shape creation failed" );
			return 0;
		}
		
		currentList->addChild( newShape );
		
		return newShape;
	}

	return 0;
}

void
SoXipOverlayManager::initContextMenu()
{
	SoXipMenuItemBase* item;

	item = new SoXipMenuItem;
	item->caption.setValue( "Edit Points" );
	mMenu->addItem( item );

	mMenu->addItem( new SoXipMenuItemSeparator );
	
	item = new SoXipMenuItem;
	item->caption.setValue( "Add Point" );
	mMenu->addItem( item );

	item = new SoXipMenuItem;
	item->caption.setValue( "Delete Point" );
	mMenu->addItem( item );

	mMenu->addItem( new SoXipMenuItemSeparator );

	item = new SoXipMenuItem;
	item->caption.setValue( "Paste" );
	item->icon.setValue( SoXipMenuItem::IC_PASTE );
	mMenu->addItem( item );

	item = new SoXipMenuItem;
	item->caption.setValue( "Copy" );
	item->icon.setValue( SoXipMenuItem::IC_COPY );
	mMenu->addItem( item );

	item = new SoXipMenuItem;
	item->caption.setValue( "Cut" );
	item->icon.setValue( SoXipMenuItem::IC_CUT );
	mMenu->addItem( item );
}

void 
SoXipOverlayManager::menuClickSensorCB( void* userData, SoSensor* )
{
	((SoXipOverlayManager *) userData)->onMenuItemClick();
}

void 
SoXipOverlayManager::menuEnabledSensorCB( void* userData, SoSensor* )
{
	((SoXipOverlayManager *) userData)->onMenuEnable();
}

void 
SoXipOverlayManager::fieldSensorCB( void* userData, SoSensor* sensor )
{
	SoXipOverlayManager* manager = (SoXipOverlayManager *) userData;
	SoField* whichField = ((SoFieldSensor *) sensor)->getAttachedField();

	if( whichField == &manager->add )
		manager->addOverlays();
	else if( whichField == &manager->remove )
		manager->removeOverlays();
	else if( whichField == &manager->clear )
		manager->clearOverlays();
}

void 
SoXipOverlayManager::onMenuItemClick()
{
	int id = mMenu->itemClicked.getValue();

	if( id == mMenu->findItem( "Edit Points" ) )
	{
		if( mSelection.getLength() != 1 )
		{
			SoDebugError::post( __FILE__, "Cannot Edit several shapes at a time" );
			return ;
		}

		((SoXipShape *) mSelection[0])->status.setValue( SoXipShape::EDIT );
	}
	else if( id == mMenu->findItem( "Copy" ) )
	{
		onCopy();
	}
	else if( id == mMenu->findItem( "Paste" ) )
	{
		onPaste();
	}
	else if( id == mMenu->findItem( "Cut" ) )
	{
		onCopy();
		onDelete();
	}
	else if( id == mMenu->findItem( "Add Point" ) && mActionNode )
	{
		((SoXipEditableShape *) mSelection[0])->addPoint( mActionNode, mMousePosition );
		((SoXipEditableShape *) mSelection[0])->invalidateGeometries();
	}
	else if( id == mMenu->findItem( "Delete Point" ) )
	{
		((SoXipEditableShape *) mSelection[0])->deletePoint( mPickedControlPoint );
		((SoXipEditableShape *) mSelection[0])->invalidateGeometries();
	}
}

void 
SoXipOverlayManager::onMenuEnable()
{
	((SoSwitch *) mMenuSwitch)->whichChild.setValue( menuEnabled.getValue() ? 0 : -1 );
}

#ifdef WIN32

void
SoXipOverlayManager::onCopy()
{
	
	SoOutput out;
	out.setBuffer(malloc(1024), 1024, realloc);

	SoSeparator* shapeSep = new SoSeparator;
	shapeSep->ref();

	for( int i = 0; i < mSelection.getLength(); ++ i )
	{
		shapeSep->addChild( mSelection[i] );
	}

	SoWriteAction wa( &out );
	wa.apply( shapeSep );

	shapeSep->unref();

	if ( !OpenClipboard(0) )
	{
		SoDebugError::post( __FILE__, "Cannot open the Clipboard" );
		return ;
	}
	
	// Remove the current Clipboard contents
	if( !EmptyClipboard() )
	{
		CloseClipboard();

		SoDebugError::post( __FILE__, "Cannot empty the Clipboard" );
		return ;
	}

	size_t sizeBuffer = 0;
	void* outBuffer = 0;
	if( !out.getBuffer( outBuffer, sizeBuffer ) )
	{
		CloseClipboard();

		SoDebugError::post( __FILE__, "Error while copying to clipboard" );
		return ;
	}

	if (outBuffer)
	{
		HGLOBAL hMem = GlobalAlloc( GMEM_SHARE | GMEM_MOVEABLE, ( sizeBuffer + 1 ) * sizeof( char ) );
		LPTSTR ptxt = (LPTSTR) GlobalLock( hMem );

		// copy content and make sure we terminate the buffer with a zero
		memcpy(ptxt, outBuffer, sizeBuffer * sizeof( char ));
		ptxt[sizeBuffer] = 0;

		GlobalUnlock( hMem );	
		
		if( ::SetClipboardData( CF_TEXT, hMem ) == NULL )
		{
			SoDebugError::post( __FILE__, "Unable to set Clipboard data" );
		}

		free(outBuffer);
	}
	
	CloseClipboard();
}

void
SoXipOverlayManager::onPaste()
{
	if( OpenClipboard(0) )
	{
		HGLOBAL hMem = GetClipboardData( CF_TEXT );
		if( hMem )
		{
			LPCTSTR ptxt = (LPCTSTR) GlobalLock(hMem);

			SoInput in;
			in.setBuffer((void*) ptxt, lstrlen( ptxt ) );

			SoNode* readNode = 0;
			SoDB::read( &in, readNode );

			if( readNode && readNode->isOfType( SoSeparator::getClassTypeId() ) )
			{
				SoSeparator* root = (SoSeparator *) readNode;

				int numChildren = root->getNumChildren();
				for( int i = 0; i < numChildren; ++ i )
				{
					SoXipShape* child = (SoXipShape *) root->getChild(i);
					if( child->isOfType( SoXipShape::getClassTypeId() ) )
					{
						child->setRank( getNextRank() );
						getCurrentList()->addChild( child );
					}
				}
			}
			
			GlobalUnlock( hMem );
		}
        
		CloseClipboard();
	}
}

#else /* WIN32 */

void
SoXipOverlayManager::onCopy()
{
// FIXME: [CRITICAL] Implement SoXipOverlayManager::onCopy()
/*	SoOutput out;
	out.setBuffer(malloc(1024), 1024, realloc);

	SoSeparator* shapeSep = new SoSeparator;
	shapeSep->ref();

	for( int i = 0; i < mSelection.getLength(); ++ i )
	{
		shapeSep->addChild( mSelection[i] );
	}

	SoWriteAction wa( &out );
	wa.apply( shapeSep );

	shapeSep->unref();

	if ( !OpenClipboard(0) )
	{
		SoDebugError::post( __FILE__, "Cannot open the Clipboard" );
		return ;
	}
	
	// Remove the current Clipboard contents
	if( !EmptyClipboard() )
	{
		CloseClipboard();

		SoDebugError::post( __FILE__, "Cannot empty the Clipboard" );
		return ;
	}

	size_t sizeBuffer = 0;
	void* outBuffer = 0;
	if( !out.getBuffer( outBuffer, sizeBuffer ) )
	{
		CloseClipboard();

		SoDebugError::post( __FILE__, "Error while copying to clipboard" );
		return ;
	}

	if (outBuffer)
	{
		HGLOBAL hMem = GlobalAlloc( GMEM_SHARE | GMEM_MOVEABLE, ( sizeBuffer + 1 ) * sizeof( char ) );
		LPTSTR ptxt = (LPTSTR) GlobalLock( hMem );

		// copy content and make sure we terminate the buffer with a zero
		memcpy(ptxt, outBuffer, sizeBuffer * sizeof( char ));
		ptxt[sizeBuffer] = 0;

		GlobalUnlock( hMem );	
		
		if( ::SetClipboardData( CF_TEXT, hMem ) == NULL )
		{
			SoDebugError::post( __FILE__, "Unable to set Clipboard data" );
		}

		free(outBuffer);
	}
	
	CloseClipboard();*/
}

void
SoXipOverlayManager::onPaste()
{
// FIXME: [CRITICAL] Implement SoXipOverlayManager::onPaste()
printf("paste hello\n");
/*	if( OpenClipboard(0) )
	{
		HGLOBAL hMem = GetClipboardData( CF_TEXT );
		if( hMem )
		{
			LPCTSTR ptxt = (LPCTSTR) GlobalLock(hMem);

			SoInput in;
			in.setBuffer((void*) ptxt, lstrlen( ptxt ) );

			SoNode* readNode = 0;
			SoDB::read( &in, readNode );

			if( readNode && readNode->isOfType( SoSeparator::getClassTypeId() ) )
			{
				SoSeparator* root = (SoSeparator *) readNode;

				int numChildren = root->getNumChildren();
				for( int i = 0; i < numChildren; ++ i )
				{
					SoXipShape* child = (SoXipShape *) root->getChild(i);
					if( child->isOfType( SoXipShape::getClassTypeId() ) )
					{
						child->setRank( getNextRank() );
						getCurrentList()->addChild( child );
					}
				}
			}
			
			GlobalUnlock( hMem );
		}
        
		CloseClipboard();
	}*/
}

#endif /* WIN32 */

SoXipShapeList*
SoXipOverlayManager::getCurrentList()
{
	return (SoXipShapeList *) mShapeList;
}

bool
SoXipOverlayManager::onDelete()
{
	SoXipShapeList* shapeList = getCurrentList();

	bool isHandled = false;
	
	for( int i = 0; i < shapeList->getNumChildren(); ++ i )
	{
		SoXipShape* shape = (SoXipShape *) shapeList->getChild(i);

		if( mSelection.find(shape) != -1 )
		{
			shapeList->removeChild(i --);
			isHandled = true;
		}
	}

	return isHandled;
}

void
SoXipOverlayManager::addOverlays()
{
	const SoNode** nodes = overlays.getValues(0);

	for( int i = 0; i < overlays.getNum(); ++ i )
	{
		const SoNode* node = nodes[i];

		if( !node->isOfType( SoXipShapeList::getClassTypeId() ) )
		{
			SoDebugError::post( __FILE__, "Child not supported" );
			return ;
		}

		SoXipShapeList* shapeList = (SoXipShapeList *) node;

		int numShapes = shapeList->getNumChildren();
		for( int i = 0; i < numShapes; ++ i )
		{
			// Copy to string to force removing of the connections
			SoNode* copyNode = shapeList->getChild(i)->copy();
			copyNode->ref();
			SbString str = XipOverlayUtils::saveNodeToString( copyNode );
			
			copyNode->unref();

			// Reload copy node from this string
			SoNode* readNode = XipOverlayUtils::loadNodeFromString( str.getString(), str.getLength() );

			((SoXipShapeList *) mShapeList)->addChild( readNode );
		}
	}
}

void
SoXipOverlayManager::removeOverlays()
{
	// FIXME
	SoError::post( "Remove not yet implemented." );
}

void
SoXipOverlayManager::clearOverlays()
{
	node.setValue(0);
	((SoXipShapeList *) mShapeList)->removeAllChildren();
}


