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
#include <xip/inventor/core/XipGeomUtils.h>
#include <xip/common/XipDebug.h>
#include <xip/inventor/core/SbRectangle3f.h>
#include <limits>
#include <cmath>

using namespace std;

static int edge[12][2] =
{
	{0, 1}, {1, 2}, {2, 3}, {3, 0},
	{4, 5}, {5, 6}, {6, 7}, {7, 4},
	{0, 4}, {1, 5}, {2, 6}, {3, 7}
};

bool 
XipGeomUtils::isOnPlane(const SbVec3f& pt, const SbPlane &plane)
{
	float dist = pt.dot(plane.getNormal()) - plane.getDistanceFromOrigin();
	if ( fabs(dist)<XIP_EPSILON ) return true;

	return false;
}

bool 
XipGeomUtils::isOnPlane(const SbVec3f& pt, const SbMatrix& planeMatrix)
{
	SbVec3f s, t;
	SbRotation r, so;
	planeMatrix.getTransform ( t, r, s, so ) ;

	SbVec3f axisX, axisY;
	axisX[0] = planeMatrix[0][0];
	axisX[1] = planeMatrix[0][1];
	axisX[2] = planeMatrix[0][2];

	axisY[0] = planeMatrix[1][0];
	axisY[1] = planeMatrix[1][1];
	axisY[2] = planeMatrix[1][2];

	SbPlane plane(t, t+axisX, t+axisY);

	return isOnPlane(pt, plane);
}


bool
XipGeomUtils::isIntersect(const SbVec3f &u, const SbVec3f &v, const SbPlane &plane)
{
	float d0 = u.dot(plane.getNormal()) - plane.getDistanceFromOrigin();
	float d1 = v.dot(plane.getNormal()) - plane.getDistanceFromOrigin();

	if ( d0*d1>XIP_EPSILON ) return false;

	return true;
}

bool
XipGeomUtils::intersect(const SbLine &line, const SbPlane &plane, SbVec3f &pt)
{
	float t, denom;

	// solve for t:
	//  n . (l.p + t * l.d) - d == 0

	denom = plane.getNormal().dot(line.getDirection());
	if ( fabs(denom) < XIP_EPSILON )
		return FALSE;

	//  t = - (n . l.p - d) / (n . l.d)
	t = - (plane.getNormal().dot(line.getPosition()) - plane.getDistanceFromOrigin()) /  denom;

	pt = line.getPosition() + t * line.getDirection();
	return TRUE;
}

bool
XipGeomUtils::intersect(const SbVec3f &u, const SbVec3f &v, const SbPlane &plane, SbVec3f &pt)
{
	float d0 = u.dot(plane.getNormal()) - plane.getDistanceFromOrigin();
	float d1 = v.dot(plane.getNormal()) - plane.getDistanceFromOrigin();

	if ( d0*d1> -XIP_EPSILON ) return false;

	return XipGeomUtils::intersect(SbLine(u, v), plane, pt);
}

bool
XipGeomUtils::isIntersect(const SbMatrix &mpr, const SbMatrix &model)
{
	SbVec3f s, origin;
	SbRotation r, so;
	model.getTransform(origin, r, s, so);

	SbVec3f axisX, axisY, axisZ;
	axisX.setValue(model[0][0], model[0][1], model[0][2]);
	axisY.setValue(model[1][0], model[1][1], model[1][2]);
	axisZ.setValue(model[2][0], model[2][1], model[2][2]);

	SbVec3f pt0[12], pt1[12];
	pt0[0] = origin;							pt1[0] = origin + axisX;
	pt0[1] = origin + axisX;					pt1[1] = origin + axisX + axisY;
	pt0[2] = origin + axisX + axisY;			pt1[2] = origin + axisY;
	pt0[3] = origin + axisY;					pt1[3] = origin;

	pt0[4] = origin + axisZ;					pt1[4] = origin + axisX + axisZ;
	pt0[5] = origin + axisX + axisZ;			pt1[5] = origin + axisX + axisY + axisZ;
	pt0[6] = origin + axisX + axisY + axisZ;	pt1[6] = origin + axisY + axisZ;
	pt0[7] = origin + axisY + axisZ;			pt1[7] = origin + axisZ;

	pt0[8] = origin;							pt1[8] = pt0[8] + axisZ;
	pt0[9] = origin + axisX;					pt1[9] = pt0[9] + axisZ;
	pt0[10] = origin + axisX + axisY;			pt1[10] = pt0[10] + axisZ;
	pt0[11] = origin + axisY;					pt1[11] = pt0[11] + axisZ;

	axisX.setValue(mpr[0][0], mpr[0][1], mpr[0][2]);
	axisY.setValue(mpr[1][0], mpr[1][1], mpr[1][2]);
	origin.setValue(mpr[3][0], mpr[3][1], mpr[3][2]);
	SbPlane plane(origin, origin+axisX, origin+axisY);

	for (int i=0; i<12; ++i)
	{
		if ( isIntersect(pt0[i], pt1[i], plane) ) return true;
	}

	return false;
}

bool
XipGeomUtils::intersect(const SbMatrix &mpr, const SbMatrix &model, vector<SbVec3f> &pts, int width, int height, int depth, bool shifted)
{
	SbVec3f t, s ;
	SbRotation r, so ;
	model.getTransform ( t, r, s, so ) ;

	SbVec3f vsize, origin;
	SbVec3f axisX, axisY, axisZ;
	if ( shifted )
	{
		vsize[0] = s[0] / static_cast<float>(width);
		vsize[1] = s[1] / static_cast<float>(height);
		vsize[2] = s[2] / static_cast<float>(depth);

		origin[0] = t[0] - 0.5f*vsize[0];
		origin[1] = t[1] - 0.5f*vsize[1];
		origin[2] = t[2] - 0.5f*vsize[2];
	}
	else
	{
		origin[0] = t[0];
		origin[1] = t[1];
		origin[2] = t[2];
	}

	axisX[0] = model[0][0];
	axisX[1] = model[0][1];
	axisX[2] = model[0][2];

	axisY[0] = model[1][0];
	axisY[1] = model[1][1];
	axisY[2] = model[1][2];

	axisZ[0] = model[2][0];
	axisZ[1] = model[2][1];
	axisZ[2] = model[2][2];

	SbVec3f vert[8];
	vert[0] = origin;
	vert[1] = origin + axisX;
	vert[2] = origin + axisX + axisY;
	vert[3] = origin + axisY;

	vert[4] = vert[0] + axisZ;
	vert[5] = vert[1] + axisZ;
	vert[6] = vert[2] + axisZ;
	vert[7] = vert[3] + axisZ;

	mpr.getTransform ( t, r, s, so ) ;
	axisX[0] = mpr[0][0];
	axisX[1] = mpr[0][1];
	axisX[2] = mpr[0][2];

	axisY[0] = mpr[1][0];
	axisY[1] = mpr[1][1];
	axisY[2] = mpr[1][2];

	SbPlane plane(t, t+axisX, t+axisY);

	pts.clear();
	SbVec3f pt;
	for (int i=0; i<12; ++i)
	{
		if ( intersect(vert[edge[i][0]], vert[edge[i][1]], plane, pt) )
		{
			pts.push_back(pt);
		}
	}

	for (int i=0; i<8; ++i)
	{
		if ( isOnPlane(vert[i], plane) )
		{
			pts.push_back(vert[i]);
		}
	}

	if ( pts.size()>3 ) return true;

	return false;
}

bool
XipGeomUtils::intersect(const SbMatrix &mpr, const SbMatrix &model, SbMatrix &newMpr, int width, int height, int depth, bool shifted)
{
	SbVec3f t, s ;
	SbRotation r, so ;
	model.getTransform ( t, r, s, so ) ;

	SbVec3f vsize, origin;
	SbVec3f axisX, axisY, axisZ;
	axisX[0] = model[0][0];
	axisX[1] = model[0][1];
	axisX[2] = model[0][2];
	axisX.normalize();

	axisY[0] = model[1][0];
	axisY[1] = model[1][1];
	axisY[2] = model[1][2];
	axisY.normalize();

	axisZ[0] = model[2][0];
	axisZ[1] = model[2][1];
	axisZ[2] = model[2][2];
	axisZ.normalize();

	if ( shifted )
	{
		vsize[0] = s[0] / static_cast<float>(width);
		vsize[1] = s[1] / static_cast<float>(height);
		vsize[2] = s[2] / static_cast<float>(depth);

		origin = t - 0.5f*vsize[0]*axisX - 0.5f*vsize[1]*axisY - 0.5f*vsize[2]*axisZ;
	}
	else
	{
		origin[0] = t[0];
		origin[1] = t[1];
		origin[2] = t[2];
	}

	axisX[0] = model[0][0];
	axisX[1] = model[0][1];
	axisX[2] = model[0][2];

	axisY[0] = model[1][0];
	axisY[1] = model[1][1];
	axisY[2] = model[1][2];

	axisZ[0] = model[2][0];
	axisZ[1] = model[2][1];
	axisZ[2] = model[2][2];

	SbVec3f vert[8];
	vert[0] = origin;
	vert[1] = origin + axisX;
	vert[2] = origin + axisX + axisY;
	vert[3] = origin + axisY;

	vert[4] = vert[0] + axisZ;
	vert[5] = vert[1] + axisZ;
	vert[6] = vert[2] + axisZ;
	vert[7] = vert[3] + axisZ;

	mpr.getTransform ( t, r, s, so ) ;
	axisX[0] = mpr[0][0];
	axisX[1] = mpr[0][1];
	axisX[2] = mpr[0][2];
	axisX.normalize();

	axisY[0] = mpr[1][0];
	axisY[1] = mpr[1][1];
	axisY[2] = mpr[1][2];
	axisY.normalize();

	SbPlane plane(t, t+axisX, t+axisY);

	vector<SbVec3f> pts;
	pts.clear();
	SbVec3f pt;
	for (int i=0; i<12; ++i)
	{
		if ( intersect(vert[edge[i][0]], vert[edge[i][1]], plane, pt) )
		{
			pts.push_back(pt);
		}
	}

	for (int i=0; i<8; ++i)
	{
		if ( isOnPlane(vert[i], plane) )
		{
			pts.push_back(vert[i]);
		}
	}

	if ( pts.size()<3 ) return false;
	
	SbVec3f u;
	SbVec2f minv(numeric_limits<float>::max(), numeric_limits<float>::max());
	SbVec2f maxv(-numeric_limits<float>::max(), -numeric_limits<float>::max());
	float tmp;
	for (size_t i=0; i<pts.size(); ++i)
	{
		u = pts[i] - t;
		tmp = u.dot(axisX);
		if ( minv[0]>tmp ) minv[0] = tmp;
		if ( maxv[0]<tmp ) maxv[0] = tmp;

		tmp = u.dot(axisY);
		if ( minv[1]>tmp ) minv[1] = tmp;
		if ( maxv[1]<tmp ) maxv[1] = tmp;
	}

	SbVec2f center = 0.5f*(minv+maxv);

	origin = t + center[0]*axisX + center[1]*axisY;

	if ( !XipGeomUtils::isOnPlane(origin, mpr) )
	{
		XipDebug::output("Error: new center is not on the plane");
	}

	SbVec3f pt0 = t + minv[0]*axisX + minv[1]*axisY;
	SbVec3f pt1 = t + maxv[0]*axisX + minv[1]*axisY;
	SbVec3f pt2 = t + maxv[0]*axisX + maxv[1]*axisY;

	float scale = (pt1 - pt0).length();
	u = pt2 - pt1;
	if ( scale<u.length() ) scale = u.length();
	scale *= 1.01f;

	newMpr.setTransform(origin, r, SbVec3f(scale, scale, scale), so);
	//XipDebug::output("%f --> %f", s[0], scale);

	return true;
}

SbBool XipGeomUtils::planeIntersect(const SbPlane & p1, const SbPlane & p2, SbLine & line)
{
	// Based on code from Graphics Gems III, Plane-to-Plane Intersection
	// by Priamos Georgiades
	// http://www.cs.ualberta.ca/~graphics/books/GraphicsGems/gemsiii/pl2plane.c

	float invdet;  // inverse of 2x2 matrix determinant
	SbVec3f dir2;  // holds the squares of the coordinates of xdir

	SbVec3f xpt;
	SbVec3f xdir;
	xdir = p1.getNormal().cross(p2.getNormal());

	dir2[0] = xdir[0] * xdir[0];
	dir2[1] = xdir[1] * xdir[1];
	dir2[2] = xdir[2] * xdir[2];

	const SbVec3f & pl1n = p1.getNormal();
	const SbVec3f & pl2n = p2.getNormal();
	const float pl1w = - p1.getDistanceFromOrigin();
	const float pl2w = - p2.getDistanceFromOrigin();

	if ( (dir2[2] > dir2[1]) && (dir2[2] > dir2[0]) && (dir2[2] > XIP_FLT_EPSILON) ) 
	{
		// then get a point on the XY plane
		invdet = 1.0f / xdir[2];
		xpt = SbVec3f(
			pl1n[1] * pl2w - pl2n[1] * pl1w,
			pl2n[0] * pl1w - pl1n[0] * pl2w,
			0.0f);
	}
	else if ( (dir2[1] > dir2[0]) && (dir2[1] > XIP_FLT_EPSILON) ) 
	{
		// then get a point on the XZ plane
		invdet = -1.0f / xdir[1];
		xpt = SbVec3f(
			pl1n[2] * pl2w - pl2n[2] * pl1w,
			0.0f,
			pl2n[0] * pl1w - pl1n[0] * pl2w);
	}
	else if (dir2[0] > XIP_FLT_EPSILON) 
	{
		// then get a point on the YZ plane
		invdet = 1.0f / xdir[0];
		xpt = SbVec3f(
			0.0f,
			pl1n[2] * pl2w - pl2n[2] * pl1w,
			pl2n[1] * pl1w - pl1n[1] * pl2w);
	}
	else
	{
		// xdir is zero, then no point of intersection exists
		return FALSE;
	}

	xpt *= invdet;
	invdet = 1.0f / (float) sqrt(dir2[0] + dir2[1] + dir2[2]);

	xdir *= invdet;
	line = SbLine(xpt, xpt+xdir);

	return TRUE;
}


// returns intersection point of three planes
SbBool XipGeomUtils::planeIntersect(const SbPlane &p1, const SbPlane &p2, const SbPlane &p3, SbVec3f &point)
{
	SbLine line1, line2;
	SbVec3f point1, point2;

	if (!planeIntersect(p1, p2, line1)) return FALSE;
	if (!planeIntersect(p1, p3, line2)) return FALSE;
	if (!line1.getClosestPoints(line2, point1, point2)) return FALSE;
	if (!point1.equals(point2, XIP_FLT_EPSILON)) return FALSE;

	point = point1;
	return TRUE;
}


SbPlane XipGeomUtils::planeFromMatrix(const SbMatrix &m)
{
	SbVec3f translation, scaleFactor, normal;
	SbRotation rotation, scaleOrientation;
	m.getTransform(translation, rotation, scaleFactor, scaleOrientation);

	normal = SbVec3f(m[2][0], m[2][1], m[2][2]);
	normal.normalize();

	return SbPlane(normal, translation);
}


float XipGeomUtils::angleBetweenVectors(SbVec3f vectorA, SbVec3f vectorB)
{
	vectorA.normalize();
	vectorB.normalize();

	float dotProduct = vectorA.dot(vectorB);
	if (dotProduct > 1.f) dotProduct = 1.f;
	if (dotProduct < -1.f) dotProduct = -1.f;

	float angle = acos(dotProduct);

	return angle;
}


SbBool XipGeomUtils::mprIntersect(const SbMatrix & m1, const SbMatrix & m2, SbVec3f line[2], float viewportAspectRatio)
{
	SbLine objLine, worldLine;
	SbVec3f pt1, pt2;
	int pc = 0;
	SbPlane p1 = planeFromMatrix(m1);
	SbPlane p2 = planeFromMatrix(m2);

	float width = viewportAspectRatio < 1.f ? 1.f : viewportAspectRatio;
	float height = viewportAspectRatio > 1.f ? 1.f : 1.f / viewportAspectRatio;

	const SbLine frameLines[4] =
	{
		SbLine(SbVec3f(-width, -height, 0), SbVec3f(-width,  height, 0)),
		SbLine(SbVec3f(-width, -height, 0), SbVec3f( width, -height, 0)),
		SbLine(SbVec3f( width,  height, 0), SbVec3f(-width,  height, 0)),
		SbLine(SbVec3f( width,  height, 0), SbVec3f( width, -height, 0)) 
	};

	// First, get intersecting line of the two planes.
	if (!planeIntersect(p1, p2, worldLine)) return FALSE;


	// Convert intersection line from world into object space before
	// testing against frame lines, which are also in object space.
	m1.inverse().multLineMatrix(worldLine, objLine);

	SbVec3f normal = objLine.getDirection();
	normal.normalize();

	objLine = SbLine(objLine.getPosition(), objLine.getPosition() + normal);

	// Intersect with the 4 lines of frame.
	for (int i = 0; i < 4; i++)
	{
		//if (objLine.getClosestPoints(frameLines[i], pt1, pt2))
		//{
		//	// Valid intersection point. Convert back to world space.
		//	m1.multVecMatrix(pt1, pt2);
		//	line[pc++] = pt2;
		//	if (pc > 1) break;
		//}

		if ((1.0f - abs(objLine.getDirection().dot(frameLines[i].getDirection()))) > 0.1f)
		{
			if (objLine.getClosestPoints(frameLines[i], pt1, pt2))
			{
				// Valid intersection point. Convert back to world space.
				m1.multVecMatrix(pt1, pt2);
				line[pc++] = pt2;
				if (pc > 1) break;
			}
		}

	}

	return (pc == 2);
}


// computes translation of a plane along it's normal given any 3-D
// translation of the intersection position
SbMatrix XipGeomUtils::translatePlaneNormal(SbMatrix plane, SbVec3f translation)
{
	SbMatrix transMatrix, newPlane;
	SbVec3f centerWorld, shiftImage;

	// re-positioning of intersection marker
	transMatrix.setTranslate(translation);
	newPlane = plane * transMatrix;

	// determine shift in 2D image output
	plane.multVecMatrix(SbVec3f(0, 0, 0), centerWorld);
	newPlane.inverse().multVecMatrix(centerWorld, shiftImage);

	// correct for x-shift
	transMatrix.setTranslate(shiftImage[0] * SbVec3f(newPlane[0][0], newPlane[0][1], newPlane[0][2]));
	newPlane *= transMatrix;

	// correct for y-shift
	transMatrix.setTranslate(shiftImage[1] * SbVec3f(newPlane[1][0], newPlane[1][1], newPlane[1][2]));
	newPlane *= transMatrix;

	// return new plane
	return newPlane;
}


// checks if vector is located within (-1,-1 to 1,1) space.
SbBool XipGeomUtils::isVecInObjectSpace(const SbVec3f &vec, float halfLen)
{
	for (int i = 0; i < 3; i++) if (fabs(vec[i]) > halfLen) return FALSE;

	return TRUE;
}


int XipGeomUtils::orthoOrientations(const SbMatrix &orientation, SbMatrix &orthoF, SbMatrix &orthoL, SbMatrix &orthoA)
{
	int i;
	SbMatrix defOrient = orientation;

	SbVec3f defNormal = SbVec3f(defOrient[2][0], defOrient[2][1], defOrient[2][2]);
	defNormal.normalize();

	SbVec3f defUp = SbVec3f(defOrient[1][0], defOrient[1][1], defOrient[1][2]);
	defUp.normalize();

	// find best match of the default orientation to one of the standard orientations (F, L, A)
	float angle[6] = 
	{
		XipGeomUtils::angleBetweenVectors(defNormal, SbVec3f(0, 0, -1)),	// F
		XipGeomUtils::angleBetweenVectors(defNormal, SbVec3f(1, 0, 0)),		// L
		XipGeomUtils::angleBetweenVectors(defNormal, SbVec3f(0, -1, 0)),	// A
		XipGeomUtils::angleBetweenVectors(defNormal, SbVec3f(0, 0, 1)),		// H
		XipGeomUtils::angleBetweenVectors(defNormal, SbVec3f(-1, 0, 0)),	// R
		XipGeomUtils::angleBetweenVectors(defNormal, SbVec3f(0, 1, 0))		// P
	};

	int which = 0;
	for (i = 0; i < 6; i++)
	{
		if (angle[i] < angle[which])
			which = i;
	}

	SbMatrix rot1, rot2;

	if (which > 2) 
	{
		// H, R or P: flip orientation around to show F, L or A
		which -= 3;
		defNormal *= -1;
		rot1.setRotate(SbRotation(defUp, static_cast<float>(M_PI)));
		defOrient = rot1 * defOrient;
	}

	switch (which)
	{
	case 0:	// F
		{
			float a = XipGeomUtils::angleBetweenVectors(SbVec3f(defUp[0], defUp[1], 0), SbVec3f(0, -1, 0));
			int numRots = static_cast<int>((a / (0.5f * M_PI)) + 0.5f);
			a = numRots * (0.5f * static_cast<float>(M_PI));
			rot1.setRotate(SbRotation(defNormal, -a));
			defOrient = rot1 * defOrient;

			orthoF = defOrient;
			rot1.setRotate(SbRotation(SbVec3f(1, 0, 0), static_cast<float>(-M_PI) / 2.f));
			orthoA = rot1 * defOrient;
			rot2.setRotate(SbRotation(SbVec3f(0, 1, 0), static_cast<float>(M_PI) / 2.f));
			orthoL = rot2 * rot1 * defOrient;
		} break;
	case 1:	// L
		{
			float a = XipGeomUtils::angleBetweenVectors(SbVec3f(0, defUp[1], defUp[2]), SbVec3f(0, 0, 1));
			int numRots = static_cast<int>((a / (0.5f * M_PI)) + 0.5f);
			a = numRots * (0.5f * static_cast<float>(M_PI));
			rot1.setRotate(SbRotation(defNormal, -a));
			defOrient = rot1 * defOrient;

			orthoL = defOrient;
			rot2.setRotate(SbRotation(SbVec3f(0, 1, 0), static_cast<float>(-M_PI) / 2.f));
			orthoA = rot2 * defOrient;
			rot1.setRotate(SbRotation(SbVec3f(0, 1, 0), static_cast<float>(-M_PI) / 2.f));
			rot2.setRotate(SbRotation(SbVec3f(1, 0, 0), static_cast<float>(M_PI) / 2.f));
			orthoF = rot2 * rot1 * defOrient;
		} break;
	case 2:	// A
		{
			float a = XipGeomUtils::angleBetweenVectors(SbVec3f(defUp[0], 0, defUp[2]), SbVec3f(0, 0, 1));
			int numRots = static_cast<int>((a / (0.5f * M_PI)) + 0.5f);
			a = numRots * (0.5f * static_cast<float>(M_PI));
			rot1.setRotate(SbRotation(defNormal, -a));
			defOrient = rot1 * defOrient;

			orthoA = defOrient;
			rot1.setRotate(SbRotation(SbVec3f(1, 0, 0), static_cast<float>(M_PI) / 2.f));
			orthoF = rot1 * defOrient;
			rot1.setRotate(SbRotation(SbVec3f(0, 1, 0), static_cast<float>(M_PI) / 2.f));
			orthoL = rot1 * defOrient;
		} break;
	}

	return which;
}

bool 
XipGeomUtils::isIntersect(const SbVec3f &origin, const SbVec3f &axisX, const SbVec3f& axisY, const SbVec3f &axisZ, const SbMatrix &mpr)
{
	SbVec3f pt0[12], pt1[12];
	pt0[0] = origin;							pt1[0] = origin + axisX;
	pt0[1] = origin + axisX;					pt1[1] = origin + axisX + axisY;
	pt0[2] = origin + axisX + axisY;			pt1[2] = origin + axisY;
	pt0[3] = origin + axisY;					pt1[3] = origin;

	pt0[4] = origin + axisZ;					pt1[4] = origin + axisX + axisZ;
	pt0[5] = origin + axisX + axisZ;			pt1[5] = origin + axisX + axisY + axisZ;
	pt0[6] = origin + axisX + axisY + axisZ;	pt1[6] = origin + axisY + axisZ;
	pt0[7] = origin + axisY + axisZ;			pt1[7] = origin + axisZ;

	pt0[8] = origin;							pt1[8] = pt0[8] + axisZ;
	pt0[9] = origin + axisX;					pt1[9] = pt0[9] + axisZ;
	pt0[10] = origin + axisX + axisY;			pt1[10] = pt0[10] + axisZ;
	pt0[11] = origin + axisY;					pt1[11] = pt0[11] + axisZ;

	SbRectangle3f rect(mpr);
	for (int i=0; i<12; ++i)
	{
		if ( rect.isIntersect(pt0[i], pt1[i]) ) return true;
	}

	SbRectangle3f facet0(pt0[0], pt0[1], pt0[2], pt0[3]);
	if ( facet0.isIntersect(rect[0], rect[1]) ) return true;
	if ( facet0.isIntersect(rect[1], rect[2]) ) return true;
	if ( facet0.isIntersect(rect[2], rect[3]) ) return true;
	if ( facet0.isIntersect(rect[3], rect[0]) ) return true;

	SbRectangle3f facet1(pt0[4], pt0[5], pt0[6], pt0[7]);
	if ( facet1.isIntersect(rect[0], rect[1]) ) return true;
	if ( facet1.isIntersect(rect[1], rect[2]) ) return true;
	if ( facet1.isIntersect(rect[2], rect[3]) ) return true;
	if ( facet1.isIntersect(rect[3], rect[0]) ) return true;

	SbRectangle3f facet2(pt0[0], pt0[1], pt0[5], pt0[4]);
	if ( facet2.isIntersect(rect[0], rect[1]) ) return true;
	if ( facet2.isIntersect(rect[1], rect[2]) ) return true;
	if ( facet2.isIntersect(rect[2], rect[3]) ) return true;
	if ( facet2.isIntersect(rect[3], rect[0]) ) return true;

	SbRectangle3f facet3(pt0[1], pt0[2], pt0[6], pt0[5]);
	if ( facet3.isIntersect(rect[0], rect[1]) ) return true;
	if ( facet3.isIntersect(rect[1], rect[2]) ) return true;
	if ( facet3.isIntersect(rect[2], rect[3]) ) return true;
	if ( facet3.isIntersect(rect[3], rect[0]) ) return true;

	SbRectangle3f facet4(pt0[3], pt0[2], pt0[6], pt0[7]);
	if ( facet4.isIntersect(rect[0], rect[1]) ) return true;
	if ( facet4.isIntersect(rect[1], rect[2]) ) return true;
	if ( facet4.isIntersect(rect[2], rect[3]) ) return true;
	if ( facet4.isIntersect(rect[3], rect[0]) ) return true;

	SbRectangle3f facet5(pt0[0], pt0[3], pt0[7], pt0[4]);
	if ( facet5.isIntersect(rect[0], rect[1]) ) return true;
	if ( facet5.isIntersect(rect[1], rect[2]) ) return true;
	if ( facet5.isIntersect(rect[2], rect[3]) ) return true;
	if ( facet5.isIntersect(rect[3], rect[0]) ) return true;

	return false;
}

bool 
XipGeomUtils::isIntersect(const SbVec3f &u, const SbVec3f &v, const SbMatrix &model)
{
	SbVec3f axisX(model[0][0], model[0][1], model[0][2]);
	SbVec3f axisY(model[1][0], model[1][1], model[1][2]);
	SbVec3f axisZ(model[2][0], model[2][1], model[2][2]);
	SbVec3f origin(model[3][0], model[3][1], model[3][2]);

	SbVec3f pt[12];
	pt[0] = origin;							
	pt[1] = origin + axisX;					
	pt[2] = origin + axisX + axisY;			
	pt[3] = origin + axisY;					

	pt[4] = origin + axisZ;					
	pt[5] = origin + axisX + axisZ;			
	pt[6] = origin + axisX + axisY + axisZ;	
	pt[7] = origin + axisY + axisZ;			

	SbRectangle3f facet0(pt[0], pt[1], pt[2], pt[3]);
	if ( facet0.isIntersect(u, v) ) return true;

	SbRectangle3f facet1(pt[4], pt[5], pt[6], pt[7]);
	if ( facet1.isIntersect(u, v) ) return true;

	SbRectangle3f facet2(pt[0], pt[1], pt[5], pt[4]);
	if ( facet2.isIntersect(u, v) ) return true;

	SbRectangle3f facet3(pt[1], pt[2], pt[6], pt[5]);
	if ( facet3.isIntersect(u, v) ) return true;

	SbRectangle3f facet4(pt[3], pt[2], pt[6], pt[7]);
	if ( facet4.isIntersect(u, v) ) return true;

	SbRectangle3f facet5(pt[0], pt[3], pt[7], pt[4]);
	if ( facet5.isIntersect(u, v) ) return true;

	return false;
}

bool
XipGeomUtils::isInside(const SbVec3f &u, const SbMatrix &model)
{
	SbMatrix inv = model.inverse();

	SbVec3f v;

	inv.multVecMatrix(u, v);

	if ( v[0]<0.0f || v[1]<0.0f || v[2]<0.0f ) return false;

	if ( v[0]>1.0f || v[1]>1.0f || v[2]>1.0f ) return false;

	return true;
}
