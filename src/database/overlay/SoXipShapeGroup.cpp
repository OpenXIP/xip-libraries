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
