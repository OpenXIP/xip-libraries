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
*	@file    SoXipHandlerShape.h
*	@brief   Base class for shapes being manipulated with handlers
*	@author  Julien Gein
**/

#ifndef SOXIPHANDLERSHAPE_H
#define SOXIPHANDLERSHAPE_H

#include <xip/inventor/overlay/SoXipSubShape.h>


/**
*	@class SoXipHandlerShape
*
* Base class for all shapes that'd better be manipulated point by point
* (SoXipOverlayHandlerManip), rather than with a transform box
* (SoXipOverlayTransformBoxManip).
*
*	@see SoXipOverlayHandlerManip
*
**/
class XIPIVOVERLAY_API SoXipHandlerShape : public SoXipManipulableShape
{
	SO_NODE_ABSTRACT_HEADER( SoXipHandlerShape );

public:
    /// Constructor
	SoXipHandlerShape();

    /// Class initialization
	static void initClass();

    /**
    *	@brief Get a list of handler points, i.e. points that can be manipulated
    *  by a SoXipOverlayHandlerManip.
    *
    *	@param point    list of handler points
    **/
	virtual void getHandlerPoints( SoMFVec3f& point );

    /**
    *	@brief Callback triggered when one handler point is being moved by a
    * a SoXipOverlayHandlerManip.
    *
    *	@param id        index of the handler point being moved
    *	@param newPos    new position of the handler point
    **/
	virtual void moveHandlerPoint( int id, const SbVec3f& newPos ) = 0;

protected:
    /// Destructor
	~SoXipHandlerShape();

};

#endif // SOXIPHANDLERSHAPE_H
