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
#include "SoXipImageAttributes.h"
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFShort.h>
#include <xip/inventor/core/SoXipDataImage.h>
#include <xip/inventor/core/SbXipImage.h>
#include <xip/inventor/core/XipGeomUtils.h>


SO_ENGINE_SOURCE(SoXipImageAttributes);


void SoXipImageAttributes::initClass()
{
	SO_ENGINE_INIT_CLASS(SoXipImageAttributes, SoEngine, "Engine");
}


SoXipImageAttributes::SoXipImageAttributes()
{
	SO_ENGINE_CONSTRUCTOR(SoXipImageAttributes);

	SO_ENGINE_ADD_INPUT(image, (0));
	SO_ENGINE_ADD_OUTPUT(modelMatrix, SoSFMatrix);
	SO_ENGINE_ADD_OUTPUT(width, SoSFShort);
	SO_ENGINE_ADD_OUTPUT(height, SoSFShort);
	SO_ENGINE_ADD_OUTPUT(depth, SoSFShort);
	SO_ENGINE_ADD_OUTPUT(bitsStored, SoSFShort);

	SO_ENGINE_ADD_OUTPUT(defaultOrientation, SoSFMatrix);
	SO_ENGINE_ADD_OUTPUT(orthoScanOrientation, SoSFShort);
	SO_ENGINE_ADD_OUTPUT(orthoOrientation1, SoSFMatrix);
	SO_ENGINE_ADD_OUTPUT(orthoOrientation2, SoSFMatrix);
	SO_ENGINE_ADD_OUTPUT(orthoOrientation3, SoSFMatrix);
	SO_ENGINE_ADD_OUTPUT(defaultCenter, SoSFVec3f);
}


SoXipImageAttributes::~SoXipImageAttributes()
{
}


void SoXipImageAttributes::evaluate()
{
	SoXipDataImage *imgData = image.getValue();

	if (imgData)
	{
		SbXipImage *img = imgData->get();
		if (img)
		{
			SO_ENGINE_OUTPUT(modelMatrix, SoSFMatrix, setValue(img->getModelMatrix()));
			SO_ENGINE_OUTPUT(bitsStored, SoSFShort, setValue(img->getBitsStored()));

			SO_ENGINE_OUTPUT(width,  SoSFShort, setValue(img->getDimStored()[0]));
			SO_ENGINE_OUTPUT(height, SoSFShort, setValue(img->getDimStored()[1]));
			SO_ENGINE_OUTPUT(depth,  SoSFShort, setValue(img->getDimStored()[2]));

			SbMatrix modelMat = img->getModelMatrix();

			SbVec3f t, s;
			SbRotation r, so;
			modelMat.getTransform(t, r, s, so);
			modelMat.multVecMatrix(SbVec3f(0.5, 0.5, 0.5), t);

			// scale MPR model matrix always to max. individual dimension by default
			float maxScale = s[0] > s[1] ? s[0] : s[1] > s[2] ? s[1] : s[2];
//			modelMat.setTransform(t, r, SbVec3f(maxScale, maxScale, maxScale), so);

			// when using get/setTransform, the rotation is derived from normal vector
			// but for gantry tilt, we need to compute normal from row and column vector
			SbVec3f rot[3];
			rot[0] = SbVec3f(modelMat[0][0], modelMat[0][1], modelMat[0][2]);
			rot[1] = SbVec3f(modelMat[1][0], modelMat[1][1], modelMat[1][2]);
			rot[2] = rot[0].cross(rot[1]);

			rot[0].normalize();
			rot[1].normalize();
			rot[2].normalize();
			rot[0] *= maxScale;
			rot[1] *= maxScale;
			rot[2] *= maxScale;

			modelMat = SbMatrix(
				rot[0][0], rot[0][1], rot[0][2], 0,
				rot[1][0], rot[1][1], rot[1][2], 0,
				rot[2][0], rot[2][1], rot[2][2], 0,
				t[0], t[1], t[2], 1);

			// update engine outputs
			SbMatrix tmp = SbMatrix::identity();

			// flip default viewing direction
			tmp.setRotate(SbRotation(SbVec3f(1, 0, 0), M_PI));

			SbMatrix defOrient = tmp * modelMat;

			// adjust so plane falls onto original plane
			defOrient.getTransform(t, r, s, so);
			SbVec3f object;
			modelMat = img->getModelMatrix();
			modelMat.inverse().multVecMatrix(t, object);

			object[0] = int(object[0] * img->getDimStored()[0] + 0.5);
			object[1] = int(object[1] * img->getDimStored()[1] + 0.5);
			object[2] = int(object[2] * img->getDimStored()[2] + 0.5);

			object[0] /= img->getDimStored()[0];
			object[1] /= img->getDimStored()[1];
			object[2] /= img->getDimStored()[2];

			modelMat.multVecMatrix(object, t);
			defOrient.setTransform(t, r, s, so);

			SO_ENGINE_OUTPUT(defaultOrientation, SoSFMatrix, setValue(defOrient));

			SbMatrix ortho1, ortho2, ortho3;
			int which = XipGeomUtils::orthoOrientations(defOrient, ortho1, ortho2, ortho3);
			SO_ENGINE_OUTPUT(orthoScanOrientation, SoSFShort, setValue(which));

			SO_ENGINE_OUTPUT(orthoOrientation1, SoSFMatrix, setValue(ortho1));
			SO_ENGINE_OUTPUT(orthoOrientation2, SoSFMatrix, setValue(ortho2));
			SO_ENGINE_OUTPUT(orthoOrientation3, SoSFMatrix, setValue(ortho3));

			defOrient.getTransform(t, r, s, so);
			SO_ENGINE_OUTPUT(defaultCenter, SoSFVec3f, setValue(t));

			return;
		}
	}

	SO_ENGINE_OUTPUT(modelMatrix, SoSFMatrix, setValue(SbMatrix::identity()));
	SO_ENGINE_OUTPUT(bitsStored, SoSFShort, setValue(0));

	SO_ENGINE_OUTPUT(width,  SoSFShort, setValue(0));
	SO_ENGINE_OUTPUT(height, SoSFShort, setValue(0));
	SO_ENGINE_OUTPUT(depth,  SoSFShort, setValue(0));

	SbMatrix rot1, rot2;
	SO_ENGINE_OUTPUT(defaultOrientation, SoSFMatrix, setValue(SbMatrix::identity()));
	SO_ENGINE_OUTPUT(orthoScanOrientation, SoSFShort, setValue(0));
	SO_ENGINE_OUTPUT(orthoOrientation1, SoSFMatrix, setValue(SbMatrix::identity()));
	rot1.setRotate(SbRotation(SbVec3f(1, 0, 0), -M_PI / 2.f));
	SO_ENGINE_OUTPUT(orthoOrientation2, SoSFMatrix, setValue(rot1));
	rot2.setRotate(SbRotation(SbVec3f(0, 1, 0), M_PI / 2.f));
	SO_ENGINE_OUTPUT(orthoOrientation3, SoSFMatrix, setValue(rot2 * rot1));

	SO_ENGINE_OUTPUT(defaultCenter, SoSFVec3f, setValue(SbVec3f(0.5, 0.5, 0.5)));
}
