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
#ifndef SBRECTANGLE3F_H
#define SBRECTANGLE3F_H

#include <xip/common/XipCommon.h>
#include <Inventor/SbLinear.h>
#include <Inventor/SbBox.h>
#include "xipivcore.h"

class XIPIVCORE_API SbRectangle3f
{
public:
	SbRectangle3f();

	SbRectangle3f(const SbVec3f& v0, const SbVec3f& v1, const SbVec3f& v2, const SbVec3f &v3);

	SbRectangle3f(const SbMatrix &mpr);

	bool isInside(const SbVec3f& pt);

	bool isIntersect(const SbVec3f &v0, const SbVec3f &v1);

	bool isIntersect(const SbBox3f &box);

	const SbVec3f& operator [] (int idx) const
	{
		return mPts[idx];
	}

	void transform(const SbVec3f &origin, const SbVec3f &axisX, const SbVec3f& axisY, const SbVec3f &axisZ);

private:
	SbVec3f		mPts[4];
	SbVec3f		mAxisX;
	SbVec3f		mAxisY;
	SbPlane		mPlane;
	float		mWidth;
	float		mHeight;
};

#endif
