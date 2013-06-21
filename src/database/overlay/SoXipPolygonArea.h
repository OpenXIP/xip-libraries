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
*	@file    SoXipPolygonArea.h
*	@brief   Declaration of the SoXipPolygonArea class
*	@author  Julien Gein
**/

#ifndef SOXIPPOLYGONAREA_H
#define SOXIPPOLYGONAREA_H

#include <Inventor/engines/SoSubEngine.h>
#include <Inventor/fields/SoMFVec3f.h>
#include <Inventor/fields/SoMFInt32.h>

/**
*	@class SoXipPolygonArea
*
* This engine computes the area of an arbitrary polygon
*
**/
class SoXipPolygonArea : public SoEngine
{
	SO_ENGINE_HEADER( SoXipPolygonArea );

public:
	/// Constructor
	SoXipPolygonArea();

	/// List of point
	SoMFVec3f		point;
	/// List of point indices defining the polygon
	SoMFInt32		coordIndex;

	/// Area corresponding to the given polygon
    SoEngineOutput	area;

	/// Open Inventor class initialization
	static void initClass();

protected:
	/// Destructor
	~SoXipPolygonArea();

	/// Engine evaluate method
	virtual void evaluate();

};

#endif // SOXIPPOLYGONAREA_H
