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
*/#pragma once

#include <xip/common/XipCommon.h>
#include <Inventor/SbLinear.h>
#include <vector>
#include "xipivcore.h"

#define XIP_FLT_EPSILON	0.0001f

const float XIP_EPSILON = 0.0001f;

/*! \class XipGeomUtils
* \brief Utility class providing methods to compute simple geometric information
*/
class XIPIVCORE_API XipGeomUtils
{
public:
	// computes the intersection line of two planes
	static SbBool planeIntersect(const SbPlane & p1, const SbPlane & p2, SbLine & line);

	// computes the intersection point of three planes
	static SbBool planeIntersect(const SbPlane &p1, const SbPlane &p2, const SbPlane &p3, SbVec3f &point);

	// returns a SbPlane object for a given model matrix
	static SbPlane planeFromMatrix(const SbMatrix &m);

	// returns the angle between the two vectors
	static float angleBetweenVectors(SbVec3f vectorA, SbVec3f vectorB);

	// computes the two end points of the intersection line of two MPR planes
	static SbBool mprIntersect(const SbMatrix & m1, const SbMatrix & m2, SbVec3f line[2], float viewportAspectRatio);

	// computes translation of a plane along it's normal given any 3-D
	// translation of the intersection position
	static SbMatrix translatePlaneNormal(SbMatrix plane, SbVec3f translation);

	// checks if vector is located within (-1,-1 to 1,1) space.
	static SbBool isVecInObjectSpace(const SbVec3f &vec, float halfLen = 1.0);

	// computes the default orthogonal orientations
	static int orthoOrientations(const SbMatrix &orientation, SbMatrix &orthoF, SbMatrix &orthoL, SbMatrix &orthoA);

	static bool isOnPlane(const SbVec3f& pt, const SbPlane &plane);

	static bool isOnPlane(const SbVec3f& pt, const SbMatrix &planeMatrix);

	static bool isIntersect(const SbVec3f &u, const SbVec3f &v, const SbPlane &plane);

	static bool isIntersect(const SbVec3f &origin, const SbVec3f &axisX, const SbVec3f& axisY, const SbVec3f &axisZ, const SbMatrix &mpr);

	static bool intersect(const SbLine &line, const SbPlane &plane, SbVec3f &pt);

	static bool intersect(const SbVec3f &u, const SbVec3f &v, const SbPlane &plane, SbVec3f &pt);

	static bool isIntersect(const SbMatrix &mpr, const SbMatrix &model);

	static bool intersect(const SbMatrix &mpr, const SbMatrix &model, std::vector<SbVec3f> &pts, int width=-1, int height=-1, int depth=-1, bool shifted=false);

	static bool intersect(const SbMatrix &mpr, const SbMatrix &model, SbMatrix &newMpr, int width=-1, int height=-1, int depth=-1, bool shifted=false);

	static bool isIntersect(const SbVec3f &u, const SbVec3f &v, const SbMatrix &model);

	static bool isInside(const SbVec3f &u, const SbMatrix &model);
};
