/*
 *  COPYRIGHT NOTICE.  Copyright (C) 2007 Siemens Corporate Research, 
 *  Inc. ("caBIG(tm) Participant"). The eXtensible Imaging Platform
 *  (XIP) was created with NCI funding and is part of the caBIG(tm) 
 *  initiative. The software subject to this notice and license 
 *  includes both human readable source code form and machine 
 *  readable, binary, object code form (the "caBIG(tm) Software").
 *  
 *  This caBIG(tm) Software License (the "License") is between 
 *  caBIG(tm) Participant and You.  "You (or "Your") shall mean a 
 *  person or an entity, and all other entities that control, are 
 *  controlled by, or are under common control with the entity.  
 *  "Control" for purposes of this definition means (i) the direct or 
 *  indirect power to cause the direction or management of such 
 *  entity, whether by contract or otherwise, or (ii) ownership of 
 *  fifty percent (50%) or more of the outstanding shares, or (iii) 
 *  beneficial ownership of such entity.
 *  
 *  LICENSE.  Provided that You agree to the conditions described 
 *  below, caBIG(tm) Participant grants You a non-exclusive, 
 *  worldwide, perpetual, fully-paid-up, no-charge, irrevocable, 
 *  transferable and royalty-free right and license in its rights in 
 *  the caBIG(tm) Software, including any copyright or patent rights 
 *  therein that may be infringed by the making, using, selling, 
 *  offering for sale, or importing of caBIG(tm) Software, to (i) 
 *  use, install, access, operate, execute, reproduce, copy, modify, 
 *  translate, market, publicly display, publicly perform, and 
 *  prepare derivative works of the caBIG(tm) Software; (ii) make, 
 *  have made, use, practice, sell, and offer for sale, and/or 
 *  otherwise dispose of caBIG(tm) Software (or portions thereof); 
 *  (iii) distribute and have distributed to and by third parties the 
 *  caBIG(tm) Software and any modifications and derivative works 
 *  thereof; and (iv) sublicense the foregoing rights set out in (i), 
 *  (ii) and (iii) to third parties, including the right to license 
 *  such rights to further third parties.  For sake of clarity, and 
 *  not by way of limitation, caBIG(tm) Participant shall have no 
 *  right of accounting or right of payment from You or Your 
 *  sublicensees for the rights granted under this License.  This 
 *  License is granted at no charge to You.  Your downloading, 
 *  copying, modifying, displaying, distributing or use of caBIG(tm) 
 *  Software constitutes acceptance of all of the terms and 
 *  conditions of this Agreement.  If you do not agree to such terms 
 *  and conditions, you have no right to download, copy, modify, 
 *  display, distribute or use the caBIG(tm) Software.
 *  
 *  1.	Your redistributions of the source code for the caBIG(tm) 
 *      Software must retain the above copyright notice, this list 
 *      of conditions and the disclaimer and limitation of 
 *      liability of Article 6 below.  Your redistributions in 
 *      object code form must reproduce the above copyright notice, 
 *      this list of conditions and the disclaimer of Article 6 in 
 *      the documentation and/or other materials provided with the 
 *      distribution, if any.
 *  2.	Your end-user documentation included with the 
 *      redistribution, if any, must include the following 
 *      acknowledgment: "This product includes software developed 
 *      by Siemens Corporate Research Inc."  If You do not include 
 *      such end-user documentation, You shall include this 
 *      acknowledgment in the caBIG(tm) Software itself, wherever 
 *      such third-party acknowledgments normally appear.
 *  3.	You may not use the names "Siemens Corporate Research, 
 *      Inc.", "The National Cancer Institute", "NCI", "Cancer 
 *      Bioinformatics Grid" or "caBIG(tm)" to endorse or promote 
 *      products derived from this caBIG(tm) Software.  This 
 *      License does not authorize You to use any trademarks, 
 *  	service marks, trade names, logos or product names of 
 *      either caBIG(tm) Participant, NCI or caBIG(tm), except as 
 *      required to comply with the terms of this License.
 *  4.	For sake of clarity, and not by way of limitation, You may 
 *      incorporate this caBIG(tm) Software into Your proprietary 
 *      programs and into any third party proprietary programs.  
 *      However, if You incorporate the caBIG(tm) Software into 
 *      third party proprietary programs, You agree that You are 
 *      solely responsible for obtaining any permission from such 
 *      third parties required to incorporate the caBIG(tm) 
 *      Software into such third party proprietary programs and for 
 *      informing Your sublicensees, including without limitation 
 *      Your end-users, of their obligation to secure any required 
 *      permissions from such third parties before incorporating 
 *      the caBIG(tm) Software into such third party proprietary 
 *      software programs.  In the event that You fail to obtain 
 *      such permissions, You agree to indemnify caBIG(tm) 
 *      Participant for any claims against caBIG(tm) Participant by 
 *      such third parties, except to the extent prohibited by law, 
 *      resulting from Your failure to obtain such permissions.
 *  5.	For sake of clarity, and not by way of limitation, You may 
 *      add Your own copyright statement to Your modifications and 
 *      to the derivative works, and You may provide additional or 
 *      different license terms and conditions in Your sublicenses 
 *      of modifications of the caBIG(tm) Software, or any 
 *      derivative works of the caBIG(tm) Software as a whole, 
 *      provided Your use, reproduction, and distribution of the 
 *      Work otherwise complies with the conditions stated in this 
 *      License.
 *  6.	THIS caBIG(tm) SOFTWARE IS PROVIDED "AS IS" AND ANY 
 *      EXPRESSED OR IMPLIED WARRANTIES (INCLUDING, BUT NOT LIMITED 
 *      TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, NON-
 *      INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE) ARE 
 *      DISCLAIMED.  IN NO EVENT SHALL SIEMENS CORPORATE RESEARCH 
 *      INC. OR ITS AFFILIATES BE LIABLE FOR ANY DIRECT, INDIRECT, 
 *      INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
 *      (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE 
 *      GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR 
 *      BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
 *      LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 *      (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT 
 *      OF THE USE OF THIS caBIG(tm) SOFTWARE, EVEN IF ADVISED OF 
 *      THE POSSIBILITY OF SUCH DAMAGE.
 *  
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
			onDelete();
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

void
SoXipOverlayManager::onDelete()
{
	SoXipShapeList* shapeList = getCurrentList();
	
	for( int i = 0; i < shapeList->getNumChildren(); ++ i )
	{
		SoXipShape* shape = (SoXipShape *) shapeList->getChild(i);

		if( mSelection.find(shape) != -1 )		
			shapeList->removeChild(i --);
	}
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
	((SoXipShapeList *) mShapeList)->removeAllChildren();
}
