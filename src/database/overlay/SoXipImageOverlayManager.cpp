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
#include "SoXipImageOverlayManager.h"
#include <xip/inventor/overlay/SoXipShape.h>
#include "SoXipShapeList.h"
#include <xip/inventor/overlay/XipOverlayUtils.h>

SO_NODE_SOURCE( SoXipImageOverlayManager );

SoXipImageOverlayManager::SoXipImageOverlayManager()
{
	SO_NODE_CONSTRUCTOR( SoXipImageOverlayManager );

	SO_NODE_ADD_FIELD( store, () );
	SO_NODE_ADD_FIELD( update, () );

	mShapeSwitch->whichChild.setValue(-1);
	mShapeSwitch->removeAllChildren();

	mImageData			= 0;
	mCurrentSlice		= -1;

	mStoreSensor = new SoFieldSensor( storeSensorCB, this );
	mStoreSensor->attach( &store );

	mUpdateSensor = new SoFieldSensor( updateSensorCB, this );
	mUpdateSensor->attach( &update );

	mOverlaysSensor = new SoNodeSensor( overlaysSensorCB, this );
	mOverlaysSensor->attach( mShapeSwitch );

	mOverlaysTimerSensor = new SoTimerSensor( overlaysTimerSensorCB, this );
	mOverlaysTimerSensor->unschedule();
}

SoXipImageOverlayManager::~SoXipImageOverlayManager()
{
	if( mImageData )
	{
		mImageData->unref();
		mImageData = 0;
	}

	delete mStoreSensor;
	delete mUpdateSensor;
	delete mOverlaysSensor;
	delete mOverlaysTimerSensor;
}

void
SoXipImageOverlayManager::initClass()
{
	SO_NODE_INIT_CLASS( SoXipImageOverlayManager, SoXipOverlayManager, "SoXipOverlayManager" );
}

void
SoXipImageOverlayManager::storeSensorCB( void* userData, SoSensor* )
{
	((SoXipImageOverlayManager *) userData)->saveOverlays();
}

void
SoXipImageOverlayManager::updateSensorCB( void* userData, SoSensor* )
{
	SoDebugError::post( __FILE__, "Update requested" );

	((SoXipImageOverlayManager *) userData)->loadOverlays();
}

void
SoXipImageOverlayManager::overlaysSensorCB( void* userData, SoSensor* )
{
	// Activate/reset the timer for an update in half a second
	SoXipImageOverlayManager* manager = (SoXipImageOverlayManager *) userData;
	manager->mOverlaysTimerSensor->unschedule();
	manager->mOverlaysTimerSensor->setInterval(0.5f);
	manager->mOverlaysTimerSensor->schedule();
}

void
SoXipImageOverlayManager::overlaysTimerSensorCB( void* userData, SoSensor* )
{
	SoXipImageOverlayManager* manager = (SoXipImageOverlayManager *) userData;	
	manager->mOverlaysTimerSensor->unschedule();
	manager->saveOverlays();
}

SbBool
SoXipImageOverlayManager::imageChanged( SoAction* action )
{   
	// Get reference image
	SoXipDataImage* refData = 0;
	SoXipDataImage* eltData = SoXipDataImageElement::get( action->getState() );

	if( eltData )
	{
		while( (refData = (SoXipDataImage *) eltData->getRefByType( SoXipDataImage::getClassTypeId() )) )
			eltData = refData;
	}

	if( mImageData )
	{
		return !eltData || mImageData->get() != eltData->get();
	}
	else
	{
		return eltData && eltData->get();
	}
}

void
SoXipImageOverlayManager::updateOverlays( SoAction* action )
{
	if( imageChanged( action ) )
	{
		this->saveOverlays();

		if( mImageData )
		{
			mImageData->unref();		
			mImageData = 0;
		}

		SoXipDataImage* eltData = SoXipDataImageElement::get( action->getState() );

		// Reset the current slice to force the update
		mCurrentSlice = -1;

		if( eltData )
		{
			// Get reference image
			SoXipDataImage* refData = 0;
			SoXipDataImage* eltData = SoXipDataImageElement::get( action->getState() );
	
			while( (refData = (SoXipDataImage *) eltData->getRefByType( SoXipDataImage::getClassTypeId() )) )
				eltData = refData;

			mImageData = eltData;
			mImageData->ref();

			// retrieve ROI overlay from Dicom
			this->loadOverlays();
		}
	}

	int sliceIndex = SoXipDataImageElement::getSliceIndex( action->getState() );
	if( sliceIndex != mCurrentSlice )
	{
		// When switching to a different slice, unselect all the shapes that were
		// previously selected.
		SoNodeList selection = XipOverlayUtils::getTopLevelShapes( mShapeSwitch, TRUE );	

		for( int i = 0; i < selection.getLength(); ++ i )
			((SoXipShape *) selection[i])->select( FALSE );

		mSelection.truncate(0);

		SoXipShapeList* sliceShapeList = mSliceMap[ sliceIndex ];
		if( sliceShapeList )
		{
			mShapeSwitch->whichChild.setValue( mShapeSwitch->findChild( sliceShapeList ) );
		}
		else
		{
			sliceShapeList = new SoXipShapeList;
			sliceShapeList->label.setValue( SbString( sliceIndex ) );
			
			mShapeSwitch->addChild( sliceShapeList );
			mShapeSwitch->whichChild.setValue( mShapeSwitch->getNumChildren() - 1 );

			mSliceMap[ sliceIndex ] = sliceShapeList;
		}

		mCurrentSlice = sliceIndex;
	}
}

void
SoXipImageOverlayManager::GLRender( SoGLRenderAction* action )
{
    // First, update the overlays in case the dicom image we're looking at has changed.
    updateOverlays( action );
    
    SoXipOverlayManager::GLRender( action );
}

void
SoXipImageOverlayManager::handleEvent( SoHandleEventAction* action )
{
	if( action->isHandled() )
		return ;

    // First, update the overlays in case the dicom image we're looking at has changed.
    // Can only be done if the scene has been traversed entirely (not if the grabber
	// has been set)
    if( !action->getGrabber() )
        updateOverlays( action );

	SoXipOverlayManager::handleEvent( action );
}

void 
SoXipImageOverlayManager::pick( SoPickAction* action)
{
    // First, update the overlays in case the dicom image we're looking at has changed.
    updateOverlays( action );

	SoXipOverlayManager::pick( action );
}

void 
SoXipImageOverlayManager::callback( SoCallbackAction* action)
{
    // First, update the overlays in case the dicom image we're looking at has changed.
    updateOverlays( action );

	SoXipOverlayManager::callback( action );
}

void 
SoXipImageOverlayManager::saveOverlays()
{
	if( mImageData )
	{
		SoNodeList overlays;
		for( int i = 0; i < mShapeSwitch->getNumChildren(); ++ i )
		{
			SoXipShapeList* shapeList = (SoXipShapeList *) mShapeSwitch->getChild(i);
			if( !shapeList )
			{
				SoDebugError::post( __FILE__, "Warning. Should not have NULL pointer in list of overlays" );
				continue ;
			}

			if( shapeList->getNumChildren() )
				overlays.append( shapeList );
		}

		SbString overlayStr = XipOverlayUtils::saveOverlaysToString( overlays );
		mImageData->setProperty( "overlays", overlayStr );
	}
}

void
SoXipImageOverlayManager::loadOverlays()
{
	// When the patient changes
	clearClipboard();

	// Remove all the geometries from the switch
	mShapeSwitch->removeAllChildren();
	mShapeSwitch->whichChild.setValue(-1);

	mCurrentSlice = -1;

	if( mImageData )
	{
		SbString overlayStr = mImageData->getProperty( "overlays" );
		SoNodeList nodes = XipOverlayUtils::loadOverlaysFromString( overlayStr.getString(), overlayStr.getLength(), TRUE );

		for( int i = 0; i < nodes.getLength(); ++ i )
		{
			if( !nodes[i]->isOfType( SoXipShapeList::getClassTypeId() ) )
			{
				SoDebugError::post( __FILE__, "Invalid overlay node found in Dicom. Ignored." );				
				continue ;
			}
			mShapeSwitch->addChild( nodes[i] );
		}
	}

	updateSliceMap();
}

void
SoXipImageOverlayManager::clearClipboard()
{
#ifdef WIN32

	if( !OpenClipboard(0) )
		return ;

	try
	{
		HGLOBAL hMem = GetClipboardData( CF_TEXT );
		if( hMem )
		{
			LPCTSTR ptxt = (LPCTSTR) GlobalLock(hMem);
			if( ptxt )
			{
				// Copy the first characters to read the header information
				// According to SoDB::isValidHeader documentation, take only the
				// 80 first characters.
				int size = std::min( lstrlen(ptxt), 80 );					
				if( size )
				{
					char header[81];
					memcpy( header, ptxt, sizeof(char) * size );

					// If the clipboard contains Open Inventor data, then we can safely
					// remove it (do not erase it if it's from another application)
					if( SoDB::isValidHeader( header ) )
					{
						EmptyClipboard();
					}
				}
			}
			
			GlobalUnlock( hMem );
		}
	}
	catch( ... )
	{
		SoError::post( "Unknown exception in clearClipboard()" );
	}
    
	CloseClipboard();

#endif
}



SoXipShapeList*
SoXipImageOverlayManager::getCurrentList()
{
	int childId = mShapeSwitch->whichChild.getValue();
	if( childId < 0 || childId >= mShapeSwitch->getNumChildren() )
		return 0;

	return (SoXipShapeList *) mShapeSwitch->getChild( childId );
}

void
SoXipImageOverlayManager::updateSliceMap()
{
	// Removes all the previous entries
	mSliceMap.clear();

	SoSearchAction sa;
	sa.setInterest( SoSearchAction::ALL );
	sa.setType( SoXipShapeList::getClassTypeId() );
	sa.setSearchingAll( TRUE );
	sa.apply( mShapeSwitch );

	SoPathList paths = sa.getPaths();
	for( int i = 0; i < paths.getLength(); ++ i )
	{
		SbString label = ((SoXipShapeList *) paths[i]->getTail())->label.getValue().getString();

		int sliceIndex;
		if( sscanf( label.getString(), "%d", &sliceIndex ) != 1 )
		{
			SoDebugError::post( __FILE__, "Invalid label found '%s'", label.getString() );
			continue  ;
		}
		
		mSliceMap[ sliceIndex ] = (SoXipShapeList *) paths[i]->getTail();
	}
}

void
SoXipImageOverlayManager::addOverlays()
{
	const SoNode** nodes = overlays.getValues(0);

	for( int i = 0; i < overlays.getNum(); ++ i )
	{
		const SoXipShapeList* shapeList = (const SoXipShapeList *) nodes[i];

		if( !shapeList->isOfType( SoXipShapeList::getClassTypeId() ) )
		{
			SoDebugError::post( __FILE__, "Child not supported" );
			return ;
		}

		int sliceIndex;
		if( sscanf( shapeList->label.getValue().getString(), "%d", &sliceIndex ) != 1 )
		{
			SoDebugError::post( __FILE__, "Invalid label found '%s'", shapeList->label.getValue().getString() );
			return ;
		}

		SoXipShapeList* sliceShapeList = mSliceMap[ sliceIndex ];
		if( !sliceShapeList )
		{
			sliceShapeList = new SoXipShapeList;
			sliceShapeList->label.setValue( SbString( sliceIndex ) );

			mShapeSwitch->addChild( sliceShapeList );

			mSliceMap[ sliceIndex ] = sliceShapeList;
		}

		int numShapes = shapeList->getNumChildren();
		for( int i = 0; i < numShapes; ++ i )
		{
			// Copy to string to force removing of the connections
			SoNode* copyNode = shapeList->getChild (i)->copy();
			copyNode->ref();
			SbString str = XipOverlayUtils::saveNodeToString( copyNode );
			copyNode->unref();

			// Reload copy node from this string
			SoNode* readNode = XipOverlayUtils::loadNodeFromString( str.getString(), str.getLength() );
			((SoXipShape *) readNode)->updateGeometries();
			sliceShapeList->addChild( readNode );
		}
	}
}

void
SoXipImageOverlayManager::removeOverlays()
{
	const SoNode** nodes = overlays.getValues(0);

	for( int i = 0; i < overlays.getNum(); ++ i )
	{
		const SoXipShapeList* shapeList = (const SoXipShapeList *) nodes[i];

		if( !shapeList->isOfType( SoXipShapeList::getClassTypeId() ) )
		{
			SoDebugError::post( __FILE__, "Child not supported" );
			return ;
		}

		int sliceIndex;
		if( sscanf( shapeList->label.getValue().getString(), "%d", &sliceIndex ) != 1 )
		{
			SoDebugError::post( __FILE__, "Invalid label found '%s'", shapeList->label.getValue().getString() );
			return ;
		}

		SoXipShapeList* sliceShapeList = mSliceMap[ sliceIndex ];
		if( sliceShapeList )
		{
			int numShapes = shapeList->getNumChildren();
			for( int i = 0; i < numShapes; ++ i )
				sliceShapeList->removeChild( shapeList->getChild (i) );
		}
	}
}

void
SoXipImageOverlayManager::clearOverlays()
{
	SoXipShapeList* saveCurrentList = getCurrentList();
	if( saveCurrentList )
	{
		// Remove all shapes from the current slice
		saveCurrentList->removeAllChildren();

		// Reference the shape list before removing all the slices
		saveCurrentList->ref();
		
		mShapeSwitch->removeAllChildren();

		// Add the saved shape list, and remove the extra-reference
		mShapeSwitch->addChild( saveCurrentList );
		mShapeSwitch->whichChild.setValue(0);
		saveCurrentList->unref();
	}

	updateSliceMap();
}
