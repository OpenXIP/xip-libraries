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

#include <Inventor/actions/SoSearchAction.h>
#include "SoXipShapeGroup.h"

SO_NODE_ABSTRACT_SOURCE( SoXipShapeGroup );

SoXipShapeGroup::SoXipShapeGroup()
{
	SO_NODE_CONSTRUCTOR( SoXipShapeGroup );

	SO_NODE_ADD_FIELD( childrenLinked, (FALSE) );
	SO_NODE_ADD_FIELD(       children,     (0) );
	children.setNum(0);

	mCreationChildIndex = 0;

	SoField* fields[2] = { &rank, &caption };
	for( int i = 0; i < 2; ++ i )
	{
		mShapeSensors[i] = new SoFieldSensor( shapeSensorCB, this );
		mShapeSensors[i]->setPriority(0);
		mShapeSensors[i]->attach( fields[i] );
	}

	mCreationStatusSensor = new SoFieldSensor( creationStatusSensorCB, this );
	mCreationStatusSensor->setPriority(0);

	setUpConnections( TRUE, TRUE );
}

SoXipShapeGroup::~SoXipShapeGroup()
{
	for( int i = 0; i < 2; ++ i )
	{
		if( mShapeSensors[i] )
			delete mShapeSensors[i];
		mShapeSensors[i] = 0;
	}	

	if( mCreationStatusSensor )
		delete mCreationStatusSensor;
	mCreationStatusSensor = 0;
}

void
SoXipShapeGroup::initClass()
{
	SO_NODE_INIT_ABSTRACT_CLASS( SoXipShapeGroup, SoXipShape, "SoXipShape" );
}

void
SoXipShapeGroup::search( SoSearchAction* action )
{
	setSearchingChildren( action->isSearchingAll() );

	SoXipKit::search( action );
}

SbBool
SoXipShapeGroup::isEditing() const
{
	int numChildren = getNumChildren();
	for( int i = 0; i < numChildren; ++ i )
	{
		if( ((SoXipShape *) getChild(i))->isEditing() )
			return TRUE;
	}
	return FALSE;
}

SbBool
SoXipShapeGroup::isCreating() const
{
	int numChildren = getNumChildren();
	for( int i = 0; i < numChildren; ++ i )
	{
		if( ((SoXipShape *) getChild(i))->isCreating() )
			return TRUE;
	}
	return FALSE;
}

SbBool
SoXipShapeGroup::isSelected() const
{
	int numChildren = getNumChildren();
	for( int i = 0; i < numChildren; ++ i )
	{
		if( ((SoXipShape *) getChild(i))->isSelected() )
			return TRUE;
	}
	return FALSE;
}

void 
SoXipShapeGroup::setLabel( const SoMFString& label )
{
	int numChildren = getNumChildren();
	for( int i = 0; i < numChildren; ++ i )
	{
		((SoXipShape* ) getChild(i))->setLabel( label );
	}
}

int
SoXipShapeGroup::getNumChildren() const
{
	return children.getNum();
}

SoNode*
SoXipShapeGroup::getChild( int index ) const
{
#ifdef _DEBUG
	if( index < 0 || index >= getNumChildren() )
		return 0;
#endif

	return children[index];
}

void 
SoXipShapeGroup::addChild( SoNode* child )
{
	SoXipKit::addChild( child );
	
	children.set1Value( children.getNum(), child );
}

void 
SoXipShapeGroup::insertChild( SoNode* child, int newChildIndex )
{
	SoXipKit::addChild( child );
	
#ifdef _DEBUG
	if( newChildIndex < 0 || newChildIndex >= getNumChildren() )
		return ;
#endif

	children.insertSpace( newChildIndex, 1 );
	children.set1Value( newChildIndex, child );	
}

void 
SoXipShapeGroup::removeChild( int index )
{
	SoXipKit::removeChild( index );

#ifdef _DEBUG
	if( index < 0 || index >= getNumChildren() )
		return ;
#endif

	children.setValues( index, getNumChildren() - index - 1, children.getValues( index + 1 ) );
}

void 
SoXipShapeGroup::removeAllChildren()
{
	SoXipKit::removeAllChildren();

	children.setNum(0);
}

void 
SoXipShapeGroup::replaceChild( int index, SoNode* newChild )
{
	SoXipKit::replaceChild( index, newChild );
	
#ifdef _DEBUG
	if( index < 0 || index >= getNumChildren() )
		return ;
#endif

	children.set1Value( index, newChild );
}

void
SoXipShapeGroup::setCreationChild( int index )
{
#ifdef _DEBUG
	if( index < 0 || index >= getNumChildren() )
	{
		SoDebugError::post( __FILE__, "" );
		return ;
	}
#endif

	mCreationChildIndex = index;
}

void
SoXipShapeGroup::setCreationChild( SoNode* child )
{
	setCreationChild( findChild( child ) );
}

SbBool 
SoXipShapeGroup::readInstance( SoInput* in, unsigned short flags )
{
    SbBool readOK = TRUE;

	SbBool saveNotify = enableNotify( FALSE );
	SbBool wasSetUp = setUpConnections( FALSE );
    
    readOK = SoNode::readInstance( in, flags );

	invalidateGeometries();

	// Call the SoXipKit method to remove only the children attached to the kit
	// and not the one contained in the field children
	SoXipKit::removeAllChildren();

	for( int i = 0; i < children.getNum(); ++ i )
	{
		SoXipKit::addChild( children[i] );
	}

   	setUpConnections( wasSetUp );
	enableNotify( saveNotify );

	return readOK;
}

SbBool 
SoXipShapeGroup::setUpConnections( SbBool onOff, SbBool doItAlways )
{
    if( !doItAlways && connectionsSetUp == onOff )
		return onOff;

	if( getNumChildren() )
	{

#ifdef _DEBUG
		if( mCreationChildIndex < 0 || mCreationChildIndex >= getNumChildren() )
		{
			SoDebugError::post( __FILE__, "" );
			return TRUE;
		}
#endif
		try
		{
			SoXipShape* shape = (SoXipShape *) getChild( mCreationChildIndex );

			if ( onOff )
			{
				// We connect AFTER base class.
				SoXipShape::setUpConnections( onOff, FALSE );

				if( mCreationStatusSensor->getAttachedField() != &shape->status )
					mCreationStatusSensor->attach( &shape->status );
			}
			else
			{
				// We disconnect BEFORE base class.
				if( mCreationStatusSensor->getAttachedField() )
					mCreationStatusSensor->detach();

				SoXipShape::setUpConnections( onOff, FALSE );
			}
		}
		catch(...)
		{
			SoDebugError::post( __FILE__, "Cannot setup connections" );
			return TRUE;
		}
	}

    return !( connectionsSetUp = onOff );
}

void 
SoXipShapeGroup::creationStatusSensorCB( void* userData, SoSensor* sensor )
{
	SoXipShapeGroup* group = (SoXipShapeGroup *) userData;
	SoXipShape* creationChild = (SoXipShape *) group->getChild( group->mCreationChildIndex );

	if( creationChild->status.getValue() == NONE )
		group->status.setValue( NONE );	
}

void 
SoXipShapeGroup::shapeSensorCB( void* userData, SoSensor* sensor )
{
	SoXipShapeGroup* group = (SoXipShapeGroup *) userData;
	SoField* field = ((SoFieldSensor *) sensor)->getAttachedField();

	if( field == &group->rank )
		group->setRank( group->rank.getValue() );

	else if( field == &group->caption )
		group->setCaption( group->caption.getValue() );
}

void
SoXipShapeGroup::beforeCreation()
{
	SoXipShape* shape = (SoXipShape *) getChild( mCreationChildIndex );

	if( mCreationStatusSensor->getAttachedField() != &shape->status )
		mCreationStatusSensor->attach( &shape->status );

	int numChildren = getNumChildren();
	for( int i = 0; i < numChildren; ++ i )
		((SoXipShape *) getChild(i))->status.setValue( CREATE );
}

void
SoXipShapeGroup::afterCreation()
{
	if( mCreationStatusSensor->getAttachedField() )
		mCreationStatusSensor->detach();

	int numChildren = getNumChildren();
	for( int i = 0; i < numChildren; ++ i )
		((SoXipShape *) getChild(i))->status.setValue( NONE );
}

void
SoXipShapeGroup::invalidateGeometries()
{
	int numChildren = getNumChildren();
	for( int i = 0; i < numChildren; ++ i )
		((SoXipShape *) getChild(i))->invalidateGeometries();
}

void
SoXipShapeGroup::updateGeometries()
{
	int numChildren = getNumChildren();
	for( int i = 0; i < numChildren; ++ i )
		((SoXipShape *) getChild(i))->updateGeometries();
}