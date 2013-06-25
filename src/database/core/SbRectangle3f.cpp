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

#include <xip/inventor/core/SbRectangle3f.h>
#include <xip/inventor/core/XipGeomUtils.h>

SbRectangle3f::SbRectangle3f()
{

}

SbRectangle3f::SbRectangle3f(const SbVec3f& v0, const SbVec3f& v1, const SbVec3f& v2, const SbVec3f &v3)
: mPlane(v0, v1, v2)
{
	mPts[0] = v0;
	mPts[1] = v1;
	mPts[2] = v2;
	mPts[3] = v3;

	mAxisX = v1 - v0;
	mAxisY = v3 - v0;

	mWidth = mAxisX.normalize();
	mHeight = mAxisY.normalize();
}

SbRectangle3f::SbRectangle3f(const SbMatrix &mpr)
{
	mAxisX.setValue(mpr[0][0], mpr[0][1], mpr[0][2]);
	mAxisY.setValue(mpr[1][0], mpr[1][1], mpr[1][2]);
	SbVec3f axisZ(mpr[2][0], mpr[2][1], mpr[2][2]);
	SbVec3f center(mpr[3][0], mpr[3][1], mpr[3][2]);

	mPts[0] = center - 0.5f*mAxisX - 0.5f*mAxisY;
	mPts[1] = center + 0.5f*mAxisX - 0.5f*mAxisY;
	mPts[2] = center + 0.5f*mAxisX + 0.5f*mAxisY;
	mPts[3] = center - 0.5f*mAxisX + 0.5f*mAxisY;

	mWidth = mAxisX.normalize();
	mHeight = mAxisY.normalize();

	axisZ.normalize();
	mPlane = SbPlane(axisZ, center);
}

bool
SbRectangle3f::isInside(const SbVec3f& pt)
{
	SbVec3f v = pt - mPts[0];
	
	float x = v.dot(mAxisX);
	if ( x<0.0 || x>mWidth ) return false;

	float y = v.dot(mAxisY);
	if ( y<0.0 || y>mHeight ) return false;

	return true;
}

bool
SbRectangle3f::isIntersect(const SbVec3f &v0, const SbVec3f &v1)
{
	SbVec3f pt;
	if ( !XipGeomUtils::intersect(v0, v1, mPlane, pt) ) return false;
	
	if ( !isInside(pt) ) return false;

	return true;
}

bool
SbRectangle3f::isIntersect(const SbBox3f &box)
{
	for (int i=0; i<4; ++i)
	{
		if ( box.intersect(mPts[i]) ) return true;
	}

	return false;
}

void
SbRectangle3f::transform(const SbVec3f &origin, const SbVec3f &axisX, const SbVec3f& axisY, const SbVec3f &axisZ)
{
	SbVec3f tmp;
	for (int i=0; i<4; ++i)
	{
		mPts[i] -= origin;
		tmp[0] = mPts[i].dot(axisX)/axisX.length();
		tmp[1] = mPts[i].dot(axisY)/axisY.length();
		tmp[2] = mPts[i].dot(axisZ)/axisZ.length();
		mPts[i] = tmp;
	}

	mPlane = SbPlane(mPts[0], mPts[1], mPts[2]);

	mAxisX = mPts[1] - mPts[0];
	mAxisY = mPts[3] - mPts[0];

	mWidth = mAxisX.normalize();
	mHeight = mAxisY.normalize();

}
