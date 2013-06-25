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
 *  \file	SoXipSubShape.h
 *  \brief	Contains some utility macros for safe creation of nodes derived from SoXipShape.
 *  \author	Julien Gein
 *
 */
 
#ifndef SOXIPSUBSHAPE_H
#define SOXIPSUBSHAPE_H

#include <xip/inventor/overlay/SoXipManipulableShape.h>
    /**
     * \brief Declare a shape field and its associated sensor.
     *
     * Automatically declares a sensor to be used for the specific
     * shape.
     *
     */
#define SO_XIP_SHAPE_FIELD( FieldName, FieldType ) \
	public: \
		FieldType FieldName; \
	private: \
		SoFieldSensor m##FieldName##Sensor;

    /**
     * \brief Add a field to a xip shape.
     *
     * This automatically creates sensors to the given field
     * Only call this macro, if the shape geometries need 
     * to be updated when the field value is changed.
     *
     */
#define SO_XIP_SHAPE_ADD_FIELD( FieldName, FieldValue ) \
	SO_NODE_ADD_FIELD( FieldName, FieldValue ); \
	m##FieldName##Sensor.setFunction( SoXipManipulableShape::invalidateGeometriesCB ); \
	m##FieldName##Sensor.setData( this ); \
	m##FieldName##Sensor.setPriority(0); \
	m##FieldName##Sensor.attach( &FieldName );

#endif // SOXIPSUBSHAPE_H
