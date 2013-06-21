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
/**
*	@file    SoXipShapeGroup.h
*	@brief   Base class for all compound shapes
*	@author  Julien Gein
**/

#ifndef SOXIPSHAPEGROUP_H
#define SOXIPSHAPEGROUP_H

#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoMFNode.h>
#include <Inventor/sensors/SoFieldSensor.h>
#include <xip/inventor/overlay/SoXipShape.h>

/**
*	@class SoXipShapeGroup
*
* This class can be used as base class for all the shapes
* that are a composition of one or more SoXipShape. The shape group
* is handled by the framework as one overlay (same id, etc.) although
* its children can be manipulated individually.
*
**/
class SoXipShapeGroup : public SoXipShape
{
	SO_NODE_ABSTRACT_HEADER( SoXipShapeGroup );

public:
	/// Constructor
	SoXipShapeGroup();

	/// If children are linked, then selecting/unselecting one child of this group is
	/// like selecting/unselecting all the children
	SoSFBool			childrenLinked;
	/// List of children
	SoMFNode			children;

	/// Open Inventor class initialization
	static void initClass();

	/// Is the shape group being edited ?
	virtual SbBool isEditing() const;
	/// Is the shape group being created ?
	virtual SbBool isCreating() const;
	/// Is the shape group selected ?
	virtual SbBool isSelected() const;

	/// Return the number of children shapes
	int getNumChildren() const;
	/// Return the child shape at given position
	SoNode* getChild( int index ) const;
	/// Add a child shape to the group
    void addChild( SoNode* child );
	/// Insert a child shape to the group at the given position
    void insertChild( SoNode* child, int newChildIndex );
	/// Remove child from the group at the given position
    void removeChild( int index );
	/// Remove all child shapes from the group
    void removeAllChildren();
	/// Replace the child at given position by given node
    void replaceChild( int index, SoNode* newChild );

	/// Set the index of the child that will terminate the group creation
	void setCreationChild( int index );
	/// Set the child that will terminate the group creation
	void setCreationChild( SoNode* child );

	/// Set the order of the group (back to front)
	virtual void setOrder( int order ) {}
	/// Set the label (name) of the group
	virtual void setLabel( const SoMFString& label );
	/// Set the rank (enumeration) of the group
	virtual void setRank( int rank ) {}
	/// Set the caption (annotation) of the group
	virtual void setCaption( const SbString& caption ) {}

	virtual void invalidateGeometries();
	virtual void updateGeometries();

	/**
    *   @brief  Callback function called before the shape creation
    *
    **/
	virtual void beforeCreation();

	/**
    *   @brief  Callback function called after the shape creation
    *
    **/
	virtual void afterCreation();

protected:
	/// Destructor
	virtual ~SoXipShapeGroup();

	virtual SbBool readInstance( SoInput* in, unsigned short flags );
	virtual SbBool setUpConnections( SbBool onOff, SbBool doItAlways = FALSE );

    virtual void search( SoSearchAction* action );

private:
	static void creationStatusSensorCB( void* userData, SoSensor* sensor );
	static void shapeSensorCB( void* userData, SoSensor* sensor );

	SoFieldSensor*		mCreationStatusSensor;
	SoFieldSensor*		mShapeSensors[2];
	int					mCreationChildIndex;

};

#endif // SOXIPSHAPEGROUP_H
