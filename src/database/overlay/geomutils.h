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
 *  @file	geomutils.h
 *  @brief	Contains geometry utility functions.
 *
 *  @author	Daphne Yu
 *  @author	Julien Gein
 *  @author	Thomas Moeller
 */
 
#ifndef XIPGEOMUTILS_H
#define XIPGEOMUTILS_H

#include <Inventor/SbLinear.h>
#include <Inventor/fields/SoMFVec3f.h>
#include <Inventor/fields/SoMFInt32.h>
#include  <xip/inventor/overlay/xipivoverlay.h>
#define ZERO_TOLERANCE 0.005

#ifndef max
#  define max(a,b) (a > b ? a : b )
#endif

#ifndef min
#  define min(a,b) (a < b ? a : b )
#endif


bool isZero( double value );

double area2(
	const SbVec3f&			p1,
	const SbVec3f&			p2,
	const SbVec3f&			p3 );

bool isCollinear(
	const SbVec3f&			p1, 
	const SbVec3f&			p2, 
	const SbVec3f&			p3 );

bool isBetween(
	const SbVec3f&			p1, 
	const SbVec3f&			p2, 
	const SbVec3f&			p3 );

double XIPIVOVERLAY_API areaPolygon3D( const SoMFVec3f& point, const SbVec3f& normal );

double areaPolygon3D( 
	const SoMFVec3f&		point, 
	const SoMFInt32&		indices, 
	const SbVec3f&			normal );

bool intersect(
	const SbVec3f&			p0,
	const SbVec3f&			p1,
	const SbVec3f&			q0, 
	const SbVec3f&			q1,
	SbVec3f&				intersectPoint );

SbBool XIPIVOVERLAY_API selfIntersect( const SoMFVec3f& point, SbBool isClosed );

double XIPIVOVERLAY_API angleBetweenVectors( 
	const SbVec3f&			u, 
	const SbVec3f&			v, 
	const SbVec3f&			normal );

double XIPIVOVERLAY_API angleBetweenVectors( 
	const SbVec3f&			u, 
	const SbVec3f&			v );

int closestPoint(
	const SoMFVec3f&		point, 
	const SbVec3f&			ref );

void XIPIVOVERLAY_API removeClosePoints(
	const SoMFVec3f&		point_in,
	SoMFVec3f&				point_out,
	float					minDist );

void XIPIVOVERLAY_API removeClosePoints(
	SoMFVec3f&				point_inout,
	float					minDist );

bool XIPIVOVERLAY_API belongToSegment( 
	const SbVec3f&			pt,
	const SbVec3f&			s0, 
	const SbVec3f&			s1 );

bool isInsideContour(
	const SbVec3f&			pt, 
	const SoMFVec3f&		point, 
	const SoMFInt32&		coordIndex );

bool XIPIVOVERLAY_API isInsideClosedContour(
	const SbVec3f&			pt, 
	const SoMFVec3f&		point );

SbString XIPIVOVERLAY_API formatLength( float length );

SbMatrix extractRotationMatrix(	const SbMatrix& matrix );

void getScreenPixelVectors(
	class SoGLRenderAction*	action, 
	const SbVec3f			position, 
	SbVec3f&				xPixelVec, 
	SbVec3f&				yPixelVec ) ;

#endif // XIPGEOMUTILS_H


