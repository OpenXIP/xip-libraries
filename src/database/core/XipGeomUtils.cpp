#include <xip/inventor/core/XipGeomUtils.h>

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
		if (objLine.getClosestPoints(frameLines[i], pt1, pt2))
		{
			// Valid intersection point. Convert back to world space.
			m1.multVecMatrix(pt1, pt2);
			line[pc++] = pt2;
			if (pc > 1) break;
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