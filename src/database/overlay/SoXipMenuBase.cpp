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

#include <Inventor/actions/SoHandleEventAction.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/actions/SoGetBoundingBoxAction.h>
#include <Inventor/events/SoMouseButtonEvent.h>
#include <Inventor/events/SoLocation2Event.h>
#include <Inventor/elements/SoModelMatrixElement.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoSwitch.h>
#include <Inventor/nodes/SoTranslation.h>
#include <Inventor/projectors/SbPlaneProjector.h>
#include <Inventor/sensors/SoFieldSensor.h>
#include <xip/system/GL/gl.h>

#include "SoXipMenuBase.h"

SO_NODE_ABSTRACT_SOURCE( SoXipMenuBase );

SoXipMenuBase::SoXipMenuBase()
{
	SO_NODE_CONSTRUCTOR( SoXipMenuBase );

	SO_XIP_KIT_ADD_TYPE_ENTRY(    mMenuSwitch,      SoSwitch, this );
	SO_XIP_KIT_ADD_TYPE_ENTRY( mMenuSeparator,   SoSeparator, mMenuSwitch );
	SO_XIP_KIT_ADD_TYPE_ENTRY(    mMenuOffset, SoTranslation, mMenuSeparator );
    
	SO_NODE_ADD_FIELD(           on, (FALSE) );
	SO_NODE_ADD_FIELD(     position, (0, 0) );
	SO_NODE_ADD_FIELD(  itemFocused, (-1) );
	SO_NODE_ADD_FIELD(  itemClicked, (-1) );

	mActionNode			= 0;
	mIsSubMenu			= FALSE;

	mFieldSensors[0]	= new SoFieldSensor( fieldSensorCB, this );
	mFieldSensors[0]->attach( &on );
	mFieldSensors[1]	= new SoFieldSensor( fieldSensorCB, this );
	mFieldSensors[1]->attach( &position );

	mPlaneProj			= new SbPlaneProjector;
	mPlaneProj->setPlane( SbPlane( SbVec3f(0, 0, 1), 0 ) );
}

SoXipMenuBase::~SoXipMenuBase()
{
    for( int i = 0; i < 2; ++ i )
        delete mFieldSensors[i];

	if( mPlaneProj )
		delete mPlaneProj;
	mPlaneProj = 0;
}

void
SoXipMenuBase::initClass()
{
	SO_NODE_INIT_ABSTRACT_CLASS( SoXipMenuBase, SoXipKit, "SoXipKit" );
}

void
SoXipMenuBase::fieldSensorCB( void* userData, SoSensor* sensor )
{
    SoXipMenuBase* menu = (SoXipMenuBase *) userData;    
    SoFieldSensor* fieldSensor = (SoFieldSensor *) sensor;
    
    menu->fieldChanged( fieldSensor->getAttachedField() );    
}

void
SoXipMenuBase::fieldChanged( SoField* whichField )
{
    if( whichField == &on )
    {
		mMenuSwitch->whichChild.setValue( on.getValue() ? 0 : -1 );        
    }
    else if( whichField == &position )
    {
		//mMenuOffset->translation.setValue( position.getValue() );
    }
}

SbBool
SoXipMenuBase::getPickedItem( SoHandleEventAction* action, int& pickedItem ) const
{
	SoRayPickAction pa( action->getViewportRegion() );
	pa.setPoint( action->getEvent()->getPosition() );
	pa.setRadius( 3 );
	pa.setPickAll( TRUE );
	pa.enableCulling( FALSE );
	pa.apply( mActionNode );

	for( int i = 0; i < size(); ++ i )
	{
		if( getItem(i)->isFocused() )
		{
			pickedItem = i;
			return TRUE;
		}
	}
	return FALSE;
}

void
SoXipMenuBase::GLRender( SoGLRenderAction* action )
{
	if( on.getValue() == FALSE )
		return ;

	// Compute the 3D position of the menu, given the mouse 2D position
	saveViewInformation( action );

	mMenuOffset->translation.setValue( mPlaneProj->project( position.getValue() ) );

	SoGetBoundingBoxAction bba( action->getViewportRegion() );
	bba.apply( mMenuSeparator );

	SbBox3f bbox = bba.getBoundingBox();
	bbox.transform( mModelMatrix );

	float viewportAR = mViewport.getViewportAspectRatio();
	SbVec3f screenOffset(0, 0, 0);
	if( viewportAR < 1. )
	{
		screenOffset[0] = bbox.getMax()[0] - 1.;
		screenOffset[1] = bbox.getMax()[1] - 1. / viewportAR;
	}
	else
	{
		screenOffset[0] = bbox.getMax()[0] - viewportAR;
		screenOffset[1] = bbox.getMax()[1] - 1;
	}

	if( screenOffset[0] < 0 )
		screenOffset[0] = 0;
	if( screenOffset[1] < 0 )
		screenOffset[1] = 0;

	SbVec3f worldOffset;
	mModelMatrix.inverse().multVecMatrix( screenOffset, worldOffset );

	mMenuOffset->translation.setValue( mMenuOffset->translation.getValue() - worldOffset );

	glPushAttrib( GL_ENABLE_BIT );
	glDisable( GL_DEPTH_TEST );

	SoXipKit::GLRender( action );

	glPopAttrib();
}

void
SoXipMenuBase::saveViewInformation( SoAction* action )
{
	SoState* state = action->getState();

	// Save the view volume element
	mViewVolume = SoViewVolumeElement::get( state );

	// Save the model matrix element
	mModelMatrix = SoModelMatrixElement::get( state );

	// Save the plane projector
	float distance = mViewVolume.getDepth() / 2.f;
	mPlaneProj->setViewVolume( mViewVolume );
	mPlaneProj->setWorkingSpace( mModelMatrix );
	mPlaneProj->setPlane( mViewVolume.getPlane( mViewVolume.getNearDist() + distance ) );

	// Save the viewport
	mViewport = SoViewportRegionElement::get( state );
}

void
SoXipMenuBase::handleEvent( SoHandleEventAction* action )
{
	if( on.getValue() == FALSE )
		return ;

	if( action->isHandled() || action->getGrabber() != this )
		return ;

   	const SoEvent* event = action->getEvent();
	if( !event )
		return ;

	int pickedItem;

	if( SO_MOUSE_PRESS_EVENT( action->getEvent(), BUTTON1 ) && action->getGrabber() == this )
	{
		action->setHandled();
	}
	else if( SO_MOUSE_RELEASE_EVENT( action->getEvent(), BUTTON1 ) && action->getGrabber() == this )
	{
		if( getPickedItem( action, pickedItem ) && getItem( pickedItem )->isEnabled() )
		{
			itemClicked.setValue( pickedItem );
		}		

		on.setValue( FALSE );

		action->setHandled();
		action->releaseGrabber();
	}
	else if( event->isOfType( SoLocation2Event::getClassTypeId() ) )
	{
		mActionNode = action->getNodeAppliedTo();

		if( getPickedItem( action, pickedItem ) )
		{
			itemFocused.setValue( pickedItem );
			action->setHandled();
		}
	}	
}

int
SoXipMenuBase::size() const
{
    return mItems.getNum();    
}

void 
SoXipMenuBase::addItem( SoXipMenuItemBase* item )
{
    insertItem( size(), item );
	onMenuChange();
}

void 
SoXipMenuBase::insertItem( int position, SoXipMenuItemBase* item )
{
#ifdef _DEBUG
    if( position < 0 || position > size() )
    {
        SoDebugError::post( __FILE__, "Index out of bounds" );
        return ;
    }    
#endif
    
    mItems.set1Value( position, item );    
}

void 
SoXipMenuBase::removeItem( int position )
{
#ifdef _DEBUG
    if( position < 0 || position >= size() )
    {
        SoDebugError::post( __FILE__, "Index out of bounds" );
        return ;
    }    
#endif
    
    mItems.enableNotify( FALSE );
    mItems.setValues( position, size() - position - 1, mItems.getValues( position + 1 ) );
    mItems.enableNotify( TRUE );
    mItems.setNum( size() - 1 );    
}

void 
SoXipMenuBase::removeItem( SoXipMenuItemBase* item )
{
    removeItem( findItem( item ) );
}

int  
SoXipMenuBase::findItem( SoXipMenuItemBase* item )
{    
    for( int i = 0; i < size(); ++ i )
    {
        if( getItem(i) == item )
            return i;
    }
    return -1;
}

int  
SoXipMenuBase::findItem( const SbString& itemCaption )
{    
    for( int i = 0; i < size(); ++ i )
    {
        if( getItem(i)->caption.getValue() == itemCaption )
            return i;
    }
    return -1;
}

SoXipMenuItemBase* 
SoXipMenuBase::getItem( int position )
{
#ifdef _DEBUG
    if( position < 0 || position >= size() )
    {
        SoDebugError::post( __FILE__, "Index out of bounds" );
        return 0;
    }    
#endif
    
    return (SoXipMenuItemBase *) mItems[ position ];
}

const SoXipMenuItemBase* 
SoXipMenuBase::getItem( int position ) const
{
#ifdef _DEBUG
    if( position < 0 || position >= size() )
    {
        SoDebugError::post( __FILE__, "Index out of bounds" );
        return 0;
    }    
#endif
    
    return (SoXipMenuItemBase *) mItems[ position ];
}

void
SoXipMenuBase::enableItem( int position, SbBool state )
{
	getItem( position )->enable( state );
}

void
SoXipMenuBase::enableItem( const SbString& itemCaption, SbBool state )
{
	int position;
	if( ( position = findItem( itemCaption ) ) != -1 )
		enableItem( position, state );
}
