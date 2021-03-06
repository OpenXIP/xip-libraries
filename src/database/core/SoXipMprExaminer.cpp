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

#include "SoXipMprExaminer.h"
#include <Inventor/sensors/SoFieldSensor.h>
#include <Inventor/sensors/SoTimerSensor.h>
#include <Inventor/nodes/SoPerspectiveCamera.h>
#include <Inventor/nodes/SoOrthographicCamera.h>
#include <Inventor/nodes/SoSwitch.h>
#include <Inventor/elements/SoViewportRegionElement.h>
#include <Inventor/events/SoMouseButtonEvent.h>
#include <Inventor/events/SoLocation2Event.h>
#ifdef WIN32
  #include <Inventor/events/SoMouseWheelEvent.h>
#else
  #include "../../extern/inventor/lib/xip/include/Inventor/events/SoMouseWheelEvent.h"
#endif
#include <Inventor/projectors/SbPlaneProjector.h>
#include <Inventor/projectors/SbSphereSheetProjector.h>
#include <Inventor/projectors/SbLineProjector.h>
#include <Inventor/elements/SoViewportRegionElement.h>
#include <Inventor/elements/SoViewVolumeElement.h>
#include <Inventor/elements/SoModelMatrixElement.h>
#include <xip/inventor/core/SoXipCursor.h>
#include <xip/inventor/core/XipGeomUtils.h>
#include <xip/inventor/core/SoXipMprPlaneElement.h>
#include <xip/inventor/core/SoXipActiveViewportElement.h>
#include <xip/inventor/core/SoXipMprLockElement.h>
#include <xip/inventor/core/SoXipMprActiveElement.h>
#include <Inventor/nodes/SoAnnotation.h>
#include "SoXipMprIntersectionManip.h"
#include "SoXipDogEar.h"
#include "SoXipViewportBorder.h"
#include "SoXipOrientationCube.h"

SO_KIT_SOURCE(SoXipMprExaminer);


SoXipMprExaminer::SoXipMprExaminer()
{
	SO_KIT_CONSTRUCTOR(SoXipMprExaminer);

	isBuiltIn = TRUE;
	mViewAll = FALSE;
    mViewFirst = FALSE;
    mViewLast = FALSE;
	mBoundingBox = SbBox3f(SbVec3f(0, 0, 0), SbVec3f(1, 1 ,1));
	mMprModelMatrix = SbMatrix::identity();
	mStepSize = 0;
	mThickness = 0;
	mMprMatrixField = 0;
	mMprCenterField = 0;
	mViewVolume.ortho(-1, 1, -1, 1, 1, 10);
	mVpRegion = SbViewportRegion(1, 1);
	mViewTransform = SbMatrix::identity();
	mBorderColor = SbColor(0.7f, 0.7f, 0.7f);

	mDogEarNextSensor = 0;
	mDogEarPreviousSensor = 0;
	mOrientationCubeSensor = 0;

    mSphereSheetProj = new SbSphereSheetProjector;
    mSphereSheetProj->setViewVolume(mViewVolume);
    mSphereSheetProj->setSphere(SbSphere(SbVec3f(0, 0, 0), .7f));

	mLastMousePos = mMouseDownPos = SbVec2f(0, 0);
	mMprLock = 0;
	mMprId = 0;

	mLastMprModelMatrix = SbMatrix::identity();


	// Initialize children catalog and add entries to it:
	//
	//       camera  annotation  complexity
	//                   |
	//           +---------------+
	//           |               |
	//    intersectionManip     ...
	//

	SO_KIT_ADD_CATALOG_ENTRY(camera, SoOrthographicCamera, FALSE, this, \0 , FALSE);
	SO_KIT_ADD_CATALOG_ENTRY(annotation, SoAnnotation, FALSE, this, \0 , FALSE);
	SO_KIT_ADD_CATALOG_ENTRY(complexity, SoComplexity, FALSE, this, \0 , FALSE);
	SO_KIT_ADD_CATALOG_ENTRY(interactionSwitch, SoSwitch, FALSE, annotation, \0, FALSE);
	SO_KIT_ADD_CATALOG_ENTRY(intersectionManip, SoXipMprIntersectionManip, FALSE, interactionSwitch, \0 , FALSE);

	SO_KIT_ADD_CATALOG_ENTRY(borderSwitch, SoSwitch, FALSE, annotation, \0 , FALSE);
	SO_KIT_ADD_CATALOG_ENTRY(borderNode, SoXipViewportBorder, FALSE, borderSwitch, \0 , FALSE);

	SO_KIT_ADD_CATALOG_ENTRY(dogEarSwitch, SoSwitch, FALSE, annotation, \0 , FALSE);
	SO_KIT_ADD_CATALOG_ENTRY(dogEarNode, SoXipDogEar, FALSE, dogEarSwitch, \0 , FALSE);
	
	SO_KIT_ADD_CATALOG_ENTRY(orientationSwitch, SoSwitch, FALSE, annotation, \0 , FALSE);
	SO_KIT_ADD_CATALOG_ENTRY(orientationNode, SoXipOrientationCube, FALSE, orientationSwitch, \0 , FALSE);


	SO_KIT_INIT_INSTANCE();
	

	SO_NODE_DEFINE_ENUM_VALUE(orientationType, FEET);
	SO_NODE_DEFINE_ENUM_VALUE(orientationType, HEAD);
	SO_NODE_DEFINE_ENUM_VALUE(orientationType, LEFT);
	SO_NODE_DEFINE_ENUM_VALUE(orientationType, RIGHT);
	SO_NODE_DEFINE_ENUM_VALUE(orientationType, ANTERIOR);
	SO_NODE_DEFINE_ENUM_VALUE(orientationType, POSTERIOR);
	SO_NODE_DEFINE_ENUM_VALUE(orientationType, RANGE_START);
	SO_NODE_DEFINE_ENUM_VALUE(orientationType, RANGE_END);
	SO_NODE_DEFINE_ENUM_VALUE(orientationType, AZIMUTH_START);
	SO_NODE_DEFINE_ENUM_VALUE(orientationType, AZIMUTH_END);
	SO_NODE_DEFINE_ENUM_VALUE(orientationType, ELEVATION_START);
	SO_NODE_DEFINE_ENUM_VALUE(orientationType, ELEVATION_END);
	SO_NODE_SET_SF_ENUM_TYPE(orientation, orientationType);
	SO_NODE_ADD_FIELD(orientation, (FEET));
	SO_NODE_ADD_FIELD(viewOrientation, ());
//	SO_NODE_ADD_FIELD(viewCenter, ());
	SO_NODE_ADD_FIELD(viewAll, ());
    SO_NODE_ADD_FIELD(viewFirst, ());
    SO_NODE_ADD_FIELD(viewLast, ());
	SO_NODE_ADD_FIELD(stepNext, ());
	SO_NODE_ADD_FIELD(stepPrevious, ());

//	SO_NODE_ADD_FIELD(recenter, ());

    SO_NODE_DEFINE_ENUM_VALUE(keyButtonType, SHIFT_KEY);
    SO_NODE_DEFINE_ENUM_VALUE(keyButtonType, CTRL_KEY);
    SO_NODE_SET_SF_ENUM_TYPE(key, keyButtonType);

    SO_NODE_DEFINE_ENUM_VALUE(mouseButtonType, BUTTON1);
    SO_NODE_DEFINE_ENUM_VALUE(mouseButtonType, BUTTON2);
    SO_NODE_DEFINE_ENUM_VALUE(mouseButtonType, BUTTON3);
    SO_NODE_SET_SF_ENUM_TYPE(mouse, mouseButtonType);

	SO_NODE_ADD_FIELD(key, (0));
    SO_NODE_ADD_FIELD(mouse, (BUTTON1));

	SO_NODE_DEFINE_ENUM_VALUE(modeType, NONE);
	SO_NODE_DEFINE_ENUM_VALUE(modeType, ROTATE);
	SO_NODE_DEFINE_ENUM_VALUE(modeType, ROTATE_XY);
	SO_NODE_DEFINE_ENUM_VALUE(modeType, PANZOOM);
	SO_NODE_DEFINE_ENUM_VALUE(modeType, SHIFT);
	SO_NODE_DEFINE_ENUM_VALUE(modeType, PAN);
	SO_NODE_DEFINE_ENUM_VALUE(modeType, ROTATE_NORMAL);
	SO_NODE_SET_SF_ENUM_TYPE(mode, modeType);
	SO_NODE_ADD_FIELD(mode, (NONE));

	SO_NODE_DEFINE_ENUM_VALUE(intersectType, OFF);
	SO_NODE_DEFINE_ENUM_VALUE(intersectType, INTERSECTION);
	SO_NODE_DEFINE_ENUM_VALUE(intersectType, TRANSLATION);
	SO_NODE_DEFINE_ENUM_VALUE(intersectType, FREE);
	SO_NODE_SET_SF_ENUM_TYPE(intersection, intersectType);
	SO_NODE_ADD_FIELD(intersection, (TRANSLATION));

	SO_NODE_ADD_FIELD(rotatePinpoint, (TRUE));
	SO_NODE_ADD_FIELD(manip, (FALSE));
	SO_NODE_ADD_FIELD(pointTo, (FALSE));
	SO_NODE_ADD_FIELD(border, (FALSE));
	SO_NODE_ADD_FIELD(dogEar, (FALSE));
	SO_NODE_ADD_FIELD(orientationCube, (FALSE));

	SO_NODE_ADD_FIELD(rotateCamera, (SbRotation(SbVec3f(0, 0, 1), 0)));
	SO_NODE_ADD_FIELD(scaleHeight, (1.0f));

	SO_NODE_ADD_FIELD(stubs, (FALSE));
	SO_NODE_ADD_FIELD(stubScale, (10.0f));
	SO_NODE_ADD_FIELD(plane, (SbMatrix::identity()));
	SO_NODE_ADD_FIELD(accelerationFactor, (1.0f));

	SoFieldSensor *fieldSensor;
	SoField *fields[] = { &viewAll, &viewFirst, &viewLast, &viewOrientation, &stepNext, &stepPrevious, &intersection, &rotateCamera, &scaleHeight, &stubs, &stubScale };
	for (int i = 0; i < (sizeof(fields) / sizeof(SoField*)); i++)
	{
		fieldSensor = new SoFieldSensor(&fieldSensorCBFunc, this);
		fieldSensor->attach(fields[i]);
		if (i <= 1) fieldSensor->setPriority(0);
		mInputSensors.push_back(fieldSensor);
	}

	mTimerSensor = new SoTimerSensor(timerSensorCBFunc, this);
	mTimerSensor->setInterval(0.05);	// 20 fps

	SoCamera *cam = (SoCamera *) getAnyPart("camera", TRUE);
	if (cam)
	{
		cam->nearDistance = -1;
		cam->farDistance = 1;
		cam->focalDistance = 0;
	}

	updateDogEarSensors(TRUE);
}


SoXipMprExaminer::~SoXipMprExaminer()
{
	delete mSphereSheetProj;

	std::vector<SoFieldSensor *>::iterator i;
	for (i = mInputSensors.begin(); i != mInputSensors.end(); i++)
	{
		delete (*i);
	}

	if (mTimerSensor)
	{
		delete mTimerSensor;
	}

	if (mDogEarNextSensor)
	{
		delete mDogEarNextSensor;
	}

	if (mDogEarPreviousSensor)
	{
		delete mDogEarPreviousSensor;
	}

	if (mOrientationCubeSensor)
	{
		delete mOrientationCubeSensor;
	}
}


void SoXipMprExaminer::initClass()
{
	SO_KIT_INIT_CLASS(SoXipMprExaminer, SoBaseKit, "BaseKit");

	SO_ENABLE(SoGLRenderAction, SoXipMprPlaneElement);
	SO_ENABLE(SoPickAction,     SoXipMprPlaneElement);
	SO_ENABLE(SoCallbackAction, SoXipMprPlaneElement);
	SO_ENABLE(SoGetBoundingBoxAction, SoXipMprPlaneElement);
	SO_ENABLE(SoHandleEventAction, SoXipMprPlaneElement);

	SO_ENABLE(SoHandleEventAction, SoViewportRegionElement);
	SO_ENABLE(SoHandleEventAction, SoViewVolumeElement);
	SO_ENABLE(SoHandleEventAction, SoModelMatrixElement);
	SO_ENABLE(SoHandleEventAction, SoXipActiveViewportElement);
	SO_ENABLE(SoHandleEventAction, SoXipMprLockElement);

	SO_ENABLE(SoGLRenderAction, SoViewportRegionElement);
	SO_ENABLE(SoGLRenderAction, SoViewVolumeElement);
	SO_ENABLE(SoGLRenderAction, SoModelMatrixElement);
	SO_ENABLE(SoGLRenderAction, SoXipActiveViewportElement);
}


void SoXipMprExaminer::updateMprElement(SoAction *action)
{
	SoXipMprPlaneElement *element = SoXipMprPlaneElement::getInstance(action->getState());
	if (element)
	{
		int numPlanes = element->getNum();

		if (!numPlanes)
			return;

		mMprId = element->getId(numPlanes - 1);

		if (numPlanes != static_cast<int>(mMprPlaneList.size()))
		{
			// get MPR planes
			mMprPlaneList.clear();

			for (int i = 0; i < numPlanes; i++)
			{
				mprPlanes_s entry;

				entry.matrixField = element->getMatrixField(i);
				entry.centerField = element->getCenterField(i);

				if (entry.matrixField)
				{
					mMprPlaneList.push_back(entry);
				}
			}
		}
		else
		{
			for (int i = 0; i < numPlanes; i++)
			{
				mMprPlaneList[i].matrixField = element->getMatrixField(i);
				mMprPlaneList[i].centerField = element->getCenterField(i);
			}
		}
	}
}

void SoXipMprExaminer::updateMprFirst(SoAction *action)
{
    SoXipMprIntersectionManip *manip = (SoXipMprIntersectionManip *) getAnyPart("intersectionManip", TRUE);
    if (manip)
    {
        manip->on = FALSE;
    }

    SbViewportRegion viewportRegion = SoViewportRegionElement::get(action->getState());

    const SoPath *path = action->getCurPath();
    if (path)
    {
        // get the node one before this
        SoNode *node = path->getNodeFromTail(1);
        if (node)
        {
            // compute bounding box
            SoGetBoundingBoxAction bbAction(viewportRegion);

            // Find the bounding box of the scene
            bbAction.apply(node);

            mBoundingBox = bbAction.getBoundingBox();

            if (!mBoundingBox.isEmpty())
            {
                SbVec3f origin, size;

                mBoundingBox.getOrigin(origin[0], origin[1], origin[2]);
                mBoundingBox.getSize(size[0], size[1], size[2]);

                //float maxSize = size[0] > size[1] ? size[0] : size[1];
                //maxSize = maxSize > size[2] ? maxSize : size[2];

                float maxSize = 0.0f;
                if ( orientation.getValue() == FEET || orientation.getValue() == HEAD )
                {
                    maxSize = size[0] > size[1] ? size[0] : size[1];
                }
                else if ( orientation.getValue() == LEFT || orientation.getValue() == RIGHT )
                {
                    maxSize = size[1] > size[2] ? size[1] : size[2];
                }
                else if ( orientation.getValue() == ANTERIOR || orientation.getValue() == POSTERIOR )
                {
                    maxSize = size[0] > size[2] ? size[0] : size[2];
                }
                else
                {
                    maxSize = size[0] > size[1] ? size[0] : size[1];
                    maxSize = maxSize > size[2] ? maxSize : size[2];
                }
                SbVec3f t, s;
                SbRotation r, so;
                mMprModelMatrix.getTransform(t, r, s, so);

                SbVec3f transVec, mprCenter;
                int orient = orientation.getValue();
                switch(orient)
                {
                case FEET:
                    transVec = origin + SbVec3f(size[0] * 0.5f, size[1] * 0.5f, size[2] - mStepSize);
                    mprCenter = transVec;
                    break;
                case HEAD:
                    transVec = origin + SbVec3f(size[0], size[1], 0.0f) * 0.5f;
                    mprCenter = transVec;
                    break;
                case LEFT:
                    transVec = origin + SbVec3f(0.0f, size[1], size[2]) * 0.5f;
                    mprCenter = transVec;
                    break;
                case RIGHT:
                    transVec = origin + SbVec3f(size[0], size[1] * 0.5f, size[2] * 0.5f);
                    mprCenter = transVec;
                    break;
                case ANTERIOR:
                    transVec = origin + SbVec3f(size[0], 0.0f, size[2]) * 0.5f;
                    mprCenter = transVec;
                    break;
                case POSTERIOR:
                    transVec = origin + SbVec3f(size[0] * 0.5f, size[1], size[2] * 0.5f);
                    mprCenter = transVec;
                    break;
                default:
                    break;
                }

                mMprModelMatrix.setTransform(transVec, r, 
                    SbVec3f(maxSize, maxSize, maxSize));

                // update MPR element
                SoXipMprPlaneElement *element = SoXipMprPlaneElement::getInstance(action->getState());
                if (element)
                {
                    int numPlanes = element->getNum();
                    if (numPlanes > 0)
                    {
                        element->setMatrix(numPlanes - 1, mMprModelMatrix);
                        element->setCenter(numPlanes - 1, mprCenter);
                    }
                }
            }
            else
            {
                mBoundingBox = SbBox3f(SbVec3f(0, 0, 0), SbVec3f(1, 1, 1));
            }
        }
    }

    if (manip && (intersection.getValue() != OFF))
    {
        manip->on = TRUE;
    }

    mViewFirst = FALSE;
}

void SoXipMprExaminer::updateMprLast(SoAction *action)
{
    SoXipMprIntersectionManip *manip = (SoXipMprIntersectionManip *) getAnyPart("intersectionManip", TRUE);
    if (manip)
    {
        manip->on = FALSE;
    }

    SbViewportRegion viewportRegion = SoViewportRegionElement::get(action->getState());

    const SoPath *path = action->getCurPath();
    if (path)
    {
        // get the node one before this
        SoNode *node = path->getNodeFromTail(1);
        if (node)
        {
            // compute bounding box
            SoGetBoundingBoxAction bbAction(viewportRegion);

            // Find the bounding box of the scene
            bbAction.apply(node);

            mBoundingBox = bbAction.getBoundingBox();

            if (!mBoundingBox.isEmpty())
            {
                SbVec3f origin, size;

                mBoundingBox.getOrigin(origin[0], origin[1], origin[2]);
                mBoundingBox.getSize(size[0], size[1], size[2]);

                //float maxSize = size[0] > size[1] ? size[0] : size[1];
                //maxSize = maxSize > size[2] ? maxSize : size[2];

                float maxSize = 0.0f;
                if ( orientation.getValue() == FEET || orientation.getValue() == HEAD )
                {
                    maxSize = size[0] > size[1] ? size[0] : size[1];
                }
                else if ( orientation.getValue() == LEFT || orientation.getValue() == RIGHT )
                {
                    maxSize = size[1] > size[2] ? size[1] : size[2];
                }
                else if ( orientation.getValue() == ANTERIOR || orientation.getValue() == POSTERIOR )
                {
                    maxSize = size[0] > size[2] ? size[0] : size[2];
                }
                else
                {
                    maxSize = size[0] > size[1] ? size[0] : size[1];
                    maxSize = maxSize > size[2] ? maxSize : size[2];
                }
                SbVec3f t, s;
                SbRotation r, so;
                mMprModelMatrix.getTransform(t, r, s, so);

                SbVec3f transVec, mprCenter;
                int orient = orientation.getValue();
                switch(orient)
                {
                case FEET:
                    transVec = origin + SbVec3f(size[0], size[1], 0.0f) * 0.5f;
                    mprCenter = transVec;
                    break;
                case HEAD:
                    transVec = origin + SbVec3f(size[0] * 0.5f, size[1] * 0.5f, size[2] - mStepSize);
                    mprCenter = transVec;
                    break;
                case LEFT:
                    transVec = origin + SbVec3f(size[0], size[1] * 0.5f, size[2] * 0.5f);
                    mprCenter = transVec;
                    break;
                case RIGHT:
                    transVec = origin + SbVec3f(0.0f, size[1], size[2]) * 0.5f;
                    mprCenter = transVec;
                    break;
                case ANTERIOR:
                    transVec = origin + SbVec3f(size[0] * 0.5f, size[1], size[2] * 0.5f);
                    mprCenter = transVec;
                    break;
                case POSTERIOR:
                    transVec = origin + SbVec3f(size[0], 0.0f, size[2]) * 0.5f;
                    mprCenter = transVec;
                    break;
                default:
                    break;
                }

                mMprModelMatrix.setTransform(transVec, r, 
                    SbVec3f(maxSize, maxSize, maxSize));

                // update MPR element
                SoXipMprPlaneElement *element = SoXipMprPlaneElement::getInstance(action->getState());
                if (element)
                {
                    int numPlanes = element->getNum();
                    if (numPlanes > 0)
                    {
                        element->setMatrix(numPlanes - 1, mMprModelMatrix);
                        element->setCenter(numPlanes - 1, mprCenter);
                    }
                }
            }
            else
            {
                mBoundingBox = SbBox3f(SbVec3f(0, 0, 0), SbVec3f(1, 1, 1));
            }
        }
    }

    if (manip && (intersection.getValue() != OFF))
    {
        manip->on = TRUE;
    }

    mViewLast = FALSE;
}

void SoXipMprExaminer::extractViewingParams(SoAction *action)
{
	if (!action) 
	{
		// If the action is NULL, use default values for view info.
		mViewVolume.ortho(-1, 1, -1, 1, 1, 10);
		mVpRegion = SbViewportRegion(1, 1);
		mMprLock = 0;
	}
	else 
	{
		// Get the view info from the action.
		SoState *state = action->getState();
		mViewVolume = SoViewVolumeElement::get(state);
		mVpRegion = SoViewportRegionElement::get(state);
		mViewTransform = SoModelMatrixElement::get(state);

		updateMprElement(action);
		mMprLock = SoXipMprLockElement::get(action->getState());
	}
}


SbVec2f SoXipMprExaminer::getMousePosNormalized(SoHandleEventAction *action)
{
	const SoEvent *e = action->getEvent();

	if (action->getGrabber() != this)
	{
		extractViewingParams(action);
	}

	return e->getNormalizedPosition(mVpRegion);
}


void SoXipMprExaminer::inputChanged(SoField *which, SoSensor *sensor)
{
	SbVec3f center(0, 0, 0);
	if (mMprCenterField)
	{
		center = mMprCenterField->getValue();
	}

	if (which == &intersection)
	{
		SoXipMprIntersectionManip *manip = (SoXipMprIntersectionManip *) getAnyPart("intersectionManip", TRUE);
		if (manip)
		{
			switch (intersection.getValue())
			{
			case OFF:			manip->on = FALSE; break;
			case INTERSECTION:	manip->on = TRUE; manip->mode.setValue(SoXipMprIntersectionManip::INTERSECTION); break;
			case TRANSLATION:	manip->on = TRUE; manip->mode.setValue(SoXipMprIntersectionManip::TRANSLATION); break;
			case FREE:			manip->on = TRUE; manip->mode.setValue(SoXipMprIntersectionManip::FREE); break;
			}
		}
	}
	else if (which == &rotateCamera)
	{
		SbVec3f viewCenter;
		mMprModelMatrix.multVecMatrix(SbVec3f(0, 0, 0), viewCenter);
		rotateCam(rotateCamera.getValue(), rotatePinpoint.getValue() ? center : viewCenter, TRUE);
	}
	else if (which == &scaleHeight)
	{
		zoomMprList(scaleHeight.getValue());
	}
/*	else if (which == &recenter)
	{
		SbVec3f origin, size, center, intersection;

		mBoundingBox.getOrigin(origin[0], origin[1], origin[2]);
		mBoundingBox.getSize(size[0], size[1], size[2]);
		
		center = SbVec3f(origin[0], origin[1], origin[2]) + SbVec3f(size[0], size[1], size[2]) / 2.f;

		SbPlane plane = planeFromMatrix(mMprModelMatrix);

		SbLine line(center, center + plane.getNormal());

		if (mMprCenterField && plane.intersect(line, intersection))
		{
			if (mMprCenterField->getValue() != intersection)
			{
				mMprCenterField->setValue(intersection);
			}
		}
	}
	else if (which == &viewCenter)
	{
		SbVec3f t, s;
		SbRotation r, so;
		mBoundingBoxVolume.getTransform(t, r, s, so);

		// scale MPR model matrix always to max. individual dimension by default
		float maxScale = s[0] > s[1] ? s[0] : s[1] > s[2] ? s[1] : s[2];
		SbMatrix modelMatrix;
		modelMatrix.setTransform(t, r, SbVec3f(maxScale, maxScale, maxScale), so);

		// translate from corner to center of image
		SbMatrix tmp, tmp2;
		tmp.setTranslate(SbVec3f(0.5 * (s[0] / maxScale), 0.5 * (s[1] / maxScale), 0.5 * (s[2] / maxScale)));
		modelMatrix = (tmp * modelMatrix);

		SbVec3f t2, s2;
		SbRotation r2, so2;
		mMprModelMatrix.getTransform(t2, r2, s2, so2);
		modelMatrix.getTransform(t, r, s, so);
		modelMatrix.setTransform(t, r2, s, so);

		mMprModelMatrix = modelMatrix;
	}	*/
	else if (which == &viewAll)
	{
		mViewAll = TRUE;
		touch();
	}
    else if (which == &viewFirst)
	{
		mViewFirst = TRUE;
		touch();
	}
    else if (which == &viewLast)
    {
        mViewLast = TRUE;
        touch();
    }
	else if (which == &viewOrientation)
	{
		SbVec3f t, s;
		SbRotation rot, so;
		mMprModelMatrix.getTransform(t, rot , s, so);

		rot = getDefaultOrientation(orientation.getValue());
		const float fM_PI = static_cast<float>(M_PI);

		switch (orientation.getValue())
		{
		case FEET:		rot = SbRotation(SbVec3f(1, 0, 0), fM_PI); break;
		case HEAD:		rot = SbRotation(SbVec3f(0, 0, 1), fM_PI); break;
		case LEFT:		rot = SbRotation(SbVec3f(0, 1, 0), fM_PI / 2.f) * SbRotation(SbVec3f(1, 0, 0), fM_PI / 2.f); break;
		case RIGHT:		rot = SbRotation(SbVec3f(0, 1, 0), -fM_PI / 2.f) * SbRotation(SbVec3f(1, 0, 0), fM_PI / 2.f); break;
		case ANTERIOR:	rot = SbRotation(SbVec3f(1, 0, 0), fM_PI / 2.f); break;
		case POSTERIOR:	rot = SbRotation(SbVec3f(0, 1, 0), fM_PI) * SbRotation(SbVec3f(1, 0, 0), fM_PI / 2.f); break;
		case RANGE_START: rot = SbRotation(SbVec3f(0, 0, 1), -fM_PI / 2.f) * SbRotation(SbVec3f(0, 1, 0), -fM_PI / 2.f); break;
		case RANGE_END:   rot = SbRotation(SbVec3f(0, 0, 1), fM_PI / 2.f) * SbRotation(SbVec3f(0, 1, 0), fM_PI / 2.f); break;
		case AZIMUTH_START: rot = SbRotation(SbVec3f(0, 0, 1),  fM_PI / 2.f); break;
		case AZIMUTH_END: rot = SbRotation(SbVec3f(0, 1, 0),  fM_PI) * SbRotation(SbVec3f(0, 0, 1),  fM_PI / 2.f); break;
		case ELEVATION_START: rot = SbRotation(SbVec3f(0, 1, 0),  fM_PI / 2.f) * SbRotation(SbVec3f(0, 0, 1),  fM_PI / 2.f); break;
		case ELEVATION_END: rot = SbRotation(SbVec3f(0, 1, 0),  -fM_PI / 2.f) * SbRotation(SbVec3f(0, 0, 1),  fM_PI / 2.f); break;
		default: return;
		}

		mMprModelMatrix.setTransform(t, rot, s, so);
	} 
	else if ((sensor == mDogEarNextSensor) || (which == &stepNext))
	{
		SbVec3f step, p1, p2;
		SbMatrix trans;

		if (mStepSize <= 0)
		{
			mMprModelMatrix.multVecMatrix(SbVec3f(0, 0, 0), p1);
			mMprModelMatrix.multVecMatrix(SbVec3f(0, 0, 0.01f), p2);
			step = p1 - p2;
		}
		else
		{
			step = mStepSize * XipGeomUtils::planeFromMatrix(mMprModelMatrix).getNormal();
		}

		trans.setTranslate(step);
		mMprModelMatrix *= trans;

		center += step;
	}
	else if ((sensor == mDogEarPreviousSensor) || (which == &stepPrevious))
	{
		SbVec3f step, p1, p2;
		SbMatrix trans;

		if (mStepSize <= 0)
		{
			mMprModelMatrix.multVecMatrix(SbVec3f(0, 0, 0), p1);
			mMprModelMatrix.multVecMatrix(SbVec3f(0, 0, -0.01f), p2);
			step = p1 - p2;
		}
		else
		{
			step = -mStepSize * XipGeomUtils::planeFromMatrix(mMprModelMatrix).getNormal();
		}

		trans.setTranslate(step);
		mMprModelMatrix *= trans;

		center += step;
	}
	else if (which == &stubs)
	{
		SoXipMprIntersectionManip *manip = (SoXipMprIntersectionManip *) getAnyPart("intersectionManip", TRUE);
		if (manip)
		{
			manip->stubs = stubs;
		}
	}
	else if (which == &stubScale)
	{
		SoXipMprIntersectionManip *manip = (SoXipMprIntersectionManip *) getAnyPart("intersectionManip", TRUE);
		if (manip)
		{
			manip->stubScale = stubScale;
		}
	}

	if (mMprMatrixField)
	{
		if (!mMprMatrixField->getValue().equals(mMprModelMatrix, XIP_FLT_EPSILON))
		{
			mMprMatrixField->setValue(mMprModelMatrix);
			updateCamera();
		}
	}

	if (mMprCenterField)
	{
		if (!mMprCenterField->getValue().equals(center, XIP_FLT_EPSILON))
		{
			mMprCenterField->setValue(center);
		}
	}
}

SbRotation SoXipMprExaminer::getDefaultOrientation(int orien)
{
	const float fM_PI = static_cast<float>(M_PI);
	SbRotation rot = SbRotation::identity();

	switch (orien)
	{
	case FEET:			rot = SbRotation(SbVec3f(1, 0, 0), fM_PI); break;
	case HEAD:			rot = SbRotation(SbVec3f(0, 0, 1), fM_PI); break;
	case LEFT:			rot = SbRotation(SbVec3f(0, 1, 0), fM_PI / 2.f) * SbRotation(SbVec3f(1, 0, 0), fM_PI / 2.f); break;
	case RIGHT:			rot = SbRotation(SbVec3f(0, 1, 0), -fM_PI / 2.f) * SbRotation(SbVec3f(1, 0, 0), fM_PI / 2.f); break;
	case ANTERIOR:		rot = SbRotation(SbVec3f(1, 0, 0), fM_PI / 2.f); break;
	case POSTERIOR:		rot = SbRotation(SbVec3f(0, 1, 0), fM_PI) * SbRotation(SbVec3f(1, 0, 0), fM_PI / 2.f); break;
	case RANGE_START:	rot = SbRotation(SbVec3f(0, 0, 1), -fM_PI / 2.f) * SbRotation(SbVec3f(0, 1, 0), -fM_PI / 2.f); break;
	case RANGE_END:		rot = SbRotation(SbVec3f(0, 0, 1), fM_PI / 2.f) * SbRotation(SbVec3f(0, 1, 0), fM_PI / 2.f); break;
	case AZIMUTH_START: rot = SbRotation(SbVec3f(0, 0, 1),  fM_PI / 2.f); break;
	case AZIMUTH_END:	rot = SbRotation(SbVec3f(0, 1, 0),  fM_PI) * SbRotation(SbVec3f(0, 0, 1),  fM_PI / 2.f); break;
	case ELEVATION_START: rot = SbRotation(SbVec3f(0, 1, 0),  fM_PI / 2.f) * SbRotation(SbVec3f(0, 0, 1),  fM_PI / 2.f); break;
	case ELEVATION_END: rot = SbRotation(SbVec3f(0, 1, 0),  -fM_PI / 2.f) * SbRotation(SbVec3f(0, 0, 1),  fM_PI / 2.f); break;
	}

	return rot;
}

void SoXipMprExaminer::timer(SoSensor *sensor)
{
	if (mode.getValue() == SHIFT)
	{
		SbVec3f step, p1, p2;
		SbMatrix trans;

		mMprModelMatrix.multVecMatrix(SbVec3f(0, 0, 0), p1);
		mMprModelMatrix.multVecMatrix(SbVec3f(0, 0, mShift), p2);

        if (mStepSize <=XIP_FLT_EPSILON)
        {
            step = p1 - p2;
        } else
        {
            SbVec3f diffVec = p1 - p2;
            float diff = diffVec.length();
            diffVec.normalize();

            // speed it up a little since typically the step size is larger than the default increments
            int numIncr = int(2.0 * diff / mStepSize + 0.5);
            step = mStepSize * numIncr * diffVec;
        }

		trans.setTranslate(step);
		mMprModelMatrix *= trans;

		if (mMprMatrixField)
		{
			if (!mMprMatrixField->getValue().equals(mMprModelMatrix, XIP_FLT_EPSILON))
			{
				mMprMatrixField->setValue(mMprModelMatrix);
			}
		}

		if (mMprCenterField)
		{
			SbVec3f center = mMprCenterField->getValue() + (p1 - p2);

			if (!mMprCenterField->getValue().equals(center, XIP_FLT_EPSILON))
			{
				mMprCenterField->setValue(center);
			}
		}
	}
	else
	{
		// stop timer if user switched mode
		if (mTimerSensor->isScheduled())
			mTimerSensor->unschedule();
	}
}


void SoXipMprExaminer::fieldSensorCBFunc(void *usr, SoSensor *sensor)
{
	((SoXipMprExaminer*)usr)->inputChanged(((SoFieldSensor*) sensor)->getAttachedField(), sensor);
}


void SoXipMprExaminer::timerSensorCBFunc(void *usr, SoSensor *sensor)
{
	((SoXipMprExaminer*)usr)->timer(sensor);
}


void SoXipMprExaminer::GLRender(SoGLRenderAction * action)
{
	updateElement(action);

	if (mViewAll)
	{
		SoXipMprIntersectionManip *manip = (SoXipMprIntersectionManip *) getAnyPart("intersectionManip", TRUE);
		if (manip)
		{
			manip->on = FALSE;
		}

		SbViewportRegion viewportRegion = SoViewportRegionElement::get(action->getState());

		const SoPath *path = action->getCurPath();
		if (path)
		{
			// get the node one before this
			SoNode *node = path->getNodeFromTail(1);
			if (node)
			{
				// compute bounding box
				SoGetBoundingBoxAction bbAction(viewportRegion);

				// Find the bounding box of the scene
				bbAction.apply(node);

				mBoundingBox = bbAction.getBoundingBox();

				if (!mBoundingBox.isEmpty())
				{
					SbVec3f origin, size;

					mBoundingBox.getOrigin(origin[0], origin[1], origin[2]);
					mBoundingBox.getSize(size[0], size[1], size[2]);

					//float maxSize = size[0] > size[1] ? size[0] : size[1];
					//maxSize = maxSize > size[2] ? maxSize : size[2];

					float maxSize = 0.0f;
					if ( orientation.getValue() == FEET || orientation.getValue() == HEAD )
					{
						maxSize = size[0] > size[1] ? size[0] : size[1];
					}
					else if ( orientation.getValue() == LEFT || orientation.getValue() == RIGHT )
					{
						maxSize = size[1] > size[2] ? size[1] : size[2];
					}
					else if ( orientation.getValue() == ANTERIOR || orientation.getValue() == POSTERIOR )
					{
						maxSize = size[0] > size[2] ? size[0] : size[2];
					}
					else
					{
						maxSize = size[0] > size[1] ? size[0] : size[1];
						maxSize = maxSize > size[2] ? maxSize : size[2];
					}
					SbVec3f t, s;
					SbRotation r, so;
					mMprModelMatrix.getTransform(t, r, s, so);

					mMprModelMatrix.setTransform(
						SbVec3f(origin[0], origin[1], origin[2]) + SbVec3f(size[0], size[1], size[2]) / 2.f,
						r,
						SbVec3f(maxSize * ((s[0] < 0) ? -1 : 1), maxSize * ((s[1] < 0) ? -1 : 1), maxSize * ((s[2] < 0) ? -1 : 1)), so);

					// update MPR element
					SoXipMprPlaneElement *element = SoXipMprPlaneElement::getInstance(action->getState());
					if (element)
					{
						int numPlanes = element->getNum();
						if (numPlanes > 0)
						{
							element->setMatrix(numPlanes - 1, mMprModelMatrix);
							element->setCenter(numPlanes - 1, SbVec3f(origin[0], origin[1], origin[2]) + SbVec3f(size[0], size[1], size[2]) / 2.f);
						}
					}
				}
				else
				{
					mBoundingBox = SbBox3f(SbVec3f(0, 0, 0), SbVec3f(1, 1, 1));
				}
			}
		}

		if (manip && (intersection.getValue() != OFF))
		{
			manip->on = TRUE;
		}
		mViewAll = FALSE;
	}
    else if (mViewFirst)
    {
		updateMprFirst(action);
	}
    else if (mViewLast)
    {
        updateMprLast(action);
    }

	// update field
	if (mMprModelMatrix != mLastMprModelMatrix)
	{
		mLastMprModelMatrix = mMprModelMatrix;
		plane.setValue(mMprModelMatrix);
	}

	updateCamera();

	SoXipViewportBorder *b = (SoXipViewportBorder*) getAnyPart("borderNode", TRUE);
	if ((b->activeColor.getValue() != mBorderColor) || (b->inactiveColor.getValue() != mBorderColor))
	{
		b->activeColor.setValue(mBorderColor);
		b->inactiveColor.setValue(mBorderColor);
	}			

	SoBaseKit::GLRender(action); 
}


void SoXipMprExaminer::updateCursor()
{
	switch (mode.getValue())
	{
	case PAN:		SoXipCursor::setCursor("SEL_PAN");
					break;
	case ROTATE_NORMAL:	SoXipCursor::setCursor("ROTATE_INPLANE");
						break;
	case PANZOOM:	if (mDragStartMouseBorder)
						SoXipCursor::setCursor("SEL_ZOOM");
					else
						SoXipCursor::setCursor("SEL_PAN");
					break;
	case ROTATE_XY:
	case ROTATE:	if (mDragStartMouseBorder)
						SoXipCursor::setCursor("ROTATE_INPLANE");
					else
						SoXipCursor::setCursor("SEL_ROTATE");
					break;
	case SHIFT:		SoXipCursor::setCursor("SHIFT");
					break;
	default:		SoXipCursor::setCursor("NONE");
	}
}


void SoXipMprExaminer::handleEvent(SoHandleEventAction *action)
{
	mHandleEventAction = action;

	SbBool handled = FALSE;
	const SoEvent *e = action->getEvent();

    SbBool keyOk = TRUE;
	
	switch (key.getValue())
	{
		case SHIFT_KEY:	// SHIFT key is specified
			keyOk = action->getEvent()->wasShiftDown();
			break;
		case CTRL_KEY:	// CTRL key is specified
			keyOk = action->getEvent()->wasCtrlDown();
			break;
		default:	// if no key is specified
			keyOk = !(action->getEvent()->wasShiftDown() || action->getEvent()->wasShiftDown());
	}

	/*
	keyOk &= action->getEvent()->wasShiftDown();
	keyOk &= !action->getEvent()->wasShiftDown();
	keyOk &= action->getEvent()->wasCtrlDown();
	keyOk &= !action->getEvent()->wasCtrlDown();
	*/

    
	// call base class first
	SoBaseKit::handleEvent(action);

	if (action->isHandled()) return;

	// wheel events
	if (e->isOfType(SoMouseWheelEvent::getClassTypeId()) && !e->wasShiftDown() && !e->wasCtrlDown() && !action->getGrabber()
		&& SoXipActiveViewportElement::get(action->getState()))
	{
		action->setHandled();

		int delta = ((SoMouseWheelEvent*) e)->getDelta();	

		SbVec3f step, p1, p2;
		SbMatrix trans;
        float stepIncr = 0.0f;
        if (mStepSize <=XIP_FLT_EPSILON)
        {
            stepIncr = 1.0f;
        } else
        {            
            stepIncr = mStepSize ;
        }
		step = delta * stepIncr * XipGeomUtils::planeFromMatrix(mMprModelMatrix).getNormal();
		trans.setTranslate(step);
		mMprModelMatrix *= trans;

		// update field of SoMprPlane node
		if (mMprMatrixField)
		{
			if (!mMprMatrixField->getValue().equals(mMprModelMatrix, XIP_FLT_EPSILON))
			{
				mMprMatrixField->setValue(mMprModelMatrix);
			}
			// update field of MPR plane
			plane.setValue(mMprModelMatrix);
		}
		if (mMprCenterField)
		{
			SbVec3f center = mMprCenterField->getValue() + step;
			if (!mMprCenterField->getValue().equals(center, XIP_FLT_EPSILON))
			{
				mMprCenterField->setValue(center);
			}
		}

		// update active MPR plane
		if (SoXipMprActiveElement::getMprIndex(action->getState()) != mMprId)
		{
			// need to update active MPR element
			SoSFInt32 *field = SoXipMprActiveElement::getMprFieldIndex(action->getState());
			if (field)
			{
				field->setValue(mMprId);
			}

			SoXipMprActiveElement::set(action->getState(), this, mMprId, field);
		}
	}

	if (!pointTo.getValue() && (mode.getValue() == NONE))
	{
		// if not in the correct mode AND not a mouse event, do nothing
		if (!e->isOfType(SoKeyboardEvent::getClassTypeId()))
			return;
	}


	// get current MPR center position
	SbVec3f center(0, 0, 0);
	if (mMprCenterField)
	{
		center = mMprCenterField->getValue();
	}


	// mouse button press event
	if (SoMouseButtonEvent::isButtonPressEvent(e, (SoMouseButtonEvent::Button) mouse.getValue()))
	{
		if ((action->getGrabber() == 0) && keyOk)
		{
			//if (mode.getValue() == NONE) return;

			// need to save viewing parameters because after grabbing we are called
			// directly (camera etc. will be skipped)
			extractViewingParams(action);

			SbVec2f pos = getMousePosNormalized(action);
			if (!((pos[0] >= 0.f) && (pos[0] <= 1.f) &&
				(pos[1] >= 0.f) && (pos[1] <= 1.f)))
			{
				// ignore click outside current viewport
				return;
			}

			// reset the animation queue
			if (mTimerSensor->isScheduled())
				mTimerSensor->unschedule();

			// initialize spherical projector for this view and center positon
			SbVec2s vpSize = mVpRegion.getViewportSizePixels();
			SbVec2f camSize(1,1);
			if (vpSize[0] > vpSize[1])
				camSize[0] *= ((float) vpSize[0] / (float) vpSize[1]);
			else
				camSize[1] *= ((float) vpSize[1] / (float) vpSize[0]);

			SbViewVolume vv;
			vv.ortho(-camSize[0], camSize[0], -camSize[1], camSize[1], -1, 1);
			mSphereSheetProj->setViewVolume(vv);

			SbVec3f centerOfRotation(0, 0, 0);
			if (rotatePinpoint.getValue())
			{
				mMprModelMatrix.inverse().multVecMatrix(center, centerOfRotation);
			}
			mSphereSheetProj->setSphere(SbSphere(2.0f * centerOfRotation, 0.7f));

			// set sphere sheet starting point
			mSphereSheetProj->project(getMousePosNormalized(action));

			mLastMousePos = getMousePosNormalized(action);
			mShift = 0.f;
			mShiftChange = 0;

			switch (mode.getValue())
			{
			case PANZOOM:	mDragStartMouseBorder = !XipGeomUtils::isVecInObjectSpace(SbVec3f((mLastMousePos[0] * 2) - 1, (mLastMousePos[1] * 2) - 1, 0), 0.6f); break;
			case ROTATE_XY:
			case ROTATE:	mDragStartMouseBorder = (mLastMousePos[0] > 0.9f) || (mLastMousePos[1] > 0.9f) || (mLastMousePos[0] < 0.1f) || (mLastMousePos[1] < 0.1f); break;
			default:
				mDragStartMouseBorder = FALSE;
			}

			mMouseDownPos = mLastMousePos;
			action->setGrabber(this);

			updateCursor();

			handled = TRUE;
		}
	}
	// keyboard events
	else if (e->isOfType(SoKeyboardEvent::getClassTypeId()))
	{
		SbVec2f diff;
		SbVec3f viewCenter, p;
		mMprModelMatrix.multVecMatrix(SbVec3f(0, 0, 0), viewCenter);

		// acceleration factor (obtained from the field only when ALT key is pressed)
		float acce = action->getEvent()->wasAltDown() ? accelerationFactor.getValue() : 1.0f;
			
		// keyboard events are triggered anytime regardless of modes
		////if (mode.getValue() == PANZOOM)
		{
			switch( ((SoKeyboardEvent* )(e))->getKey() )
			{
			case SoKeyboardEvent::PAGE_UP:
				mDragStartMouseBorder = true;
				zoomMprList(1 + (2 * -0.05f*acce));
				handled = TRUE;
				break ;
			case SoKeyboardEvent::PAGE_DOWN:
				mDragStartMouseBorder = true;
				zoomMprList(1 + (2 * +0.05f*acce));
				handled = TRUE;
				break ;
			case SoKeyboardEvent::UP_ARROW:
				mDragStartMouseBorder = false;

				diff[0] = 0; diff[1] = 0.01f*acce;
				mMprModelMatrix.multVecMatrix(SbVec3f(diff[0], diff[1], 0), p);
				panCam(viewCenter - p);
				handled = TRUE;
				break ;
			case SoKeyboardEvent::DOWN_ARROW:
				mDragStartMouseBorder = false;

				diff[0] = 0; diff[1] = -0.01f*acce;
				mMprModelMatrix.multVecMatrix(SbVec3f(diff[0], diff[1], 0), p);
				panCam(viewCenter - p);
				handled = TRUE;
				break ;
			case SoKeyboardEvent::LEFT_ARROW:
				mDragStartMouseBorder = false;

				diff[0] = -0.01f*acce; diff[1] = 0;
				mMprModelMatrix.multVecMatrix(SbVec3f(diff[0], diff[1], 0), p);
				panCam(viewCenter - p);
				handled = TRUE;
				break ;
			case SoKeyboardEvent::RIGHT_ARROW:
				mDragStartMouseBorder = false;

				diff[0] = 0.01f*acce; diff[1] = 0;
				mMprModelMatrix.multVecMatrix(SbVec3f(diff[0], diff[1], 0), p);
				panCam(viewCenter - p);
				handled = TRUE;
				break ;
			default:
				break;
			}

		}
		

		//handled = TRUE;

		updateCursor();

		//action->setHandled();
	}
	else if (e->isOfType(SoLocation2Event::getClassTypeId()))
	{
		if (action->getGrabber() == this)
		{
			handled = TRUE;

			SoComplexity *complexityPtr = (SoComplexity*) getAnyPart("complexity", TRUE);
			if (complexityPtr->value.getValue() != 0.249)
			{
				complexityPtr->value.setValue(0.249f);
			}			
			
			SbVec2f diff = getMousePosNormalized(action) - mLastMousePos;
			SbVec3f viewCenter;
			mMprModelMatrix.multVecMatrix(SbVec3f(0, 0, 0), viewCenter);

			switch (mode.getValue())
			{
			case PAN:	{	
							SbVec3f p;
							mMprModelMatrix.multVecMatrix(SbVec3f(diff[0], diff[1], 0), p);
							panCam(viewCenter - p);
							break;
						}
			case PANZOOM:	if ( (mDragStartMouseBorder) && (!e->wasShiftDown()) )
							{
								// zoom
								zoomMprList(1 + (2 * -diff[1]));
							}
							else
							{
								// pan
								SbVec3f p;
								mMprModelMatrix.multVecMatrix(SbVec3f(diff[0], diff[1], 0), p);
								panCam(viewCenter - p);
							}
							break;
			case ROTATE_NORMAL:	mDragStartMouseBorder = TRUE;
			case ROTATE_XY:
			case ROTATE:	{
								SbRotation rotate(SbVec3f(0, 0, 1), 0);
								if (mDragStartMouseBorder)
								{
									// spin normal
									SbVec2f prevPos = mLastMousePos - SbVec2f(0.5, 0.5);
									SbVec2f currPos = getMousePosNormalized(action) - SbVec2f(0.5, 0.5);
									
									SbVec3f from = SbVec3f(prevPos[0], prevPos[1], 0.f);
									SbVec3f to = SbVec3f(currPos[0], currPos[1], 0.f);
									rotate = SbRotation(from, to);
								}
								else
								{
									if (mode.getValue() == ROTATE)
									{
										// spin sphere
										mSphereSheetProj->projectAndGetRotation(getMousePosNormalized(action), rotate);
									}
									else
									{
										// x/y-axis rotation only
										SbVec2f diff = getMousePosNormalized(action) - mLastMousePos;
										rotate = SbRotation(SbVec3f(0, 1, 0), 4.f * diff[0]);
										rotate *= SbRotation(SbVec3f(1, 0, 0), 4.f * diff[1]);
									}
								}

								// rotate around center point of plane (center)
								// or middle of segment (viewCenter)?
								rotate.invert();
								rotateCam(rotate, rotatePinpoint.getValue() ? center : viewCenter, mDragStartMouseBorder);
							}
							break;
			case SHIFT:
				{
					// translate along normal direction
					if ((mShift < 0) && (diff[1] > 0))
					{
						// change in direction: stop
						mShift = 0;
						mShiftChange = 10;
						if (mTimerSensor->isScheduled())
							mTimerSensor->unschedule();
					}
					else if ((mShift > 0) && (diff[1] < 0))
					{
						// change in direction: stop
						mShift = 0;
						mShiftChange = 10;
						if (mTimerSensor->isScheduled())
							mTimerSensor->unschedule();
					}
					else if (mShift == 0)
					{
						if (mShiftChange <= 0)
						{
							// start new shift
							mShift = (diff[1] / 10.f);
							mTimerSensor->schedule();
						}
						else
						{
							mShiftChange--;
						}
					}
					else
					{
						// speed up a little
						mShift += (diff[1] / 10.f);
					}

				} break;
			default:
				handled = FALSE;
			}

			mLastMousePos = getMousePosNormalized(action);

			// update field of SoMprPlane node
			if (mMprMatrixField)
			{
				if (!mMprMatrixField->getValue().equals(mMprModelMatrix, XIP_FLT_EPSILON))
				{
					mMprMatrixField->setValue(mMprModelMatrix);
				}
			}
			if (mMprCenterField)
			{
				if (!mMprCenterField->getValue().equals(center, XIP_FLT_EPSILON))
				{
					mMprCenterField->setValue(center);
				}
			}

			updateCursor();
		}
		else if (!action->isHandled() && !handled && keyOk && (mouse.getValue() == BUTTON1))
		{
			mLastMousePos = getMousePosNormalized(action);
			if ((mLastMousePos[0] >= 0.f) && (mLastMousePos[0] <= 1.f) &&
				(mLastMousePos[1] >= 0.f) && (mLastMousePos[1] <= 1.f))
			{
				switch (mode.getValue())
				{
				case PANZOOM:	mDragStartMouseBorder = !XipGeomUtils::isVecInObjectSpace(SbVec3f((mLastMousePos[0] * 2) - 1, (mLastMousePos[1] * 2) - 1, 0), 0.6f); break;
				case ROTATE_XY:
				case ROTATE:	mDragStartMouseBorder = (mLastMousePos[0] > 0.9f) || (mLastMousePos[1] > 0.9f) || (mLastMousePos[0] < 0.1f) || (mLastMousePos[1] < 0.1f); break;
				case NONE:		return;
				default:
					mDragStartMouseBorder = FALSE;
				}
				updateCursor();
				action->setHandled();
			}
		}
	}
	else if (SO_MOUSE_RELEASE_EVENT(e, ANY) && (action->getGrabber() == this)) 
	{
		action->releaseGrabber();
		handled = TRUE;

		SoComplexity *complexityPtr = (SoComplexity*) getAnyPart("complexity", TRUE);
		complexityPtr->value.setValue(0.5);
		complexityPtr->textureQuality.setValue(0.5);

		if (mTimerSensor->isScheduled())
			mTimerSensor->unschedule();
		mShift = 0;
		mShiftChange = 0;

		if (mLastMousePos == mMouseDownPos)
		{
			// resend this event if user releases button without movement
			// (needed for orientation cube to react)
			SoHandleEventAction ha(action->getViewportRegion());
			ha.setEvent(action->getEvent());
			ha.apply(action->getNodeAppliedTo());
		}

		if (pointTo.getValue() && (mLastMousePos == mMouseDownPos))
		{
			// release button position equals push button position: scroll to cursor
			scrollToCursor();
		}
	}

	if (handled)
	{
		action->setHandled();
	}
}


void SoXipMprExaminer::scrollToCursor()
{
	SbVec3f pt = mViewVolume.getPlanePoint(0.f, mLastMousePos);
	mprPlanes_t::const_iterator i;

	for (i = mMprPlaneList.begin(); i != mMprPlaneList.end(); i++)
	{
		SoSFMatrix *mf = i->matrixField;
		SoSFVec3f  *cf = i->centerField;

		if (mf)
		{
			SbMatrix m = mf->getValue();

			SbVec3f t, s;
			SbRotation r, so;
			m.getTransform(t, r, s, so);

			SbPlane plane = XipGeomUtils::planeFromMatrix(m);
			SbLine line(t, t + plane.getNormal());
			m.setTransform(pt, r, s, so);
			plane = XipGeomUtils::planeFromMatrix(m);
			if (plane.intersect(line, t))
			{
				m.setTransform( t, r, s, so );

				SbVec3f ptObjectSpace;
				SbMatrix pInv = m.inverse();
				pInv.multVecMatrix( pt, ptObjectSpace );

                SbVec3f offset( 0, 0, 0 );
				if( ptObjectSpace[0] > 0.5f )
					offset[0] = ptObjectSpace[0] - 0.4f;
				else if( ptObjectSpace[0] < -0.5f )
					offset[0] = ptObjectSpace[0] + 0.4f;	
				if( ptObjectSpace[1] > 0.5f )
					offset[1] = ptObjectSpace[1] - 0.4f;	
				else if( ptObjectSpace[1] < -0.5f )
					offset[1] = ptObjectSpace[1] + 0.4f;	

				SbMatrix scaleMatrix;
				scaleMatrix.setTransform( SbVec3f(0, 0, 0), r, s, so );
				scaleMatrix.multVecMatrix( offset, offset );

				m.setTransform( t + offset, r, s, so );
				mf->setValue( m );
			}
		}

		if (cf)
		{
			cf->setValue(pt);
		}
	}
}


void SoXipMprExaminer::updateElement(SoAction * action)
{
	// check state
	SoState *state = action->getState();
	if (!state) return;

	SoXipMprPlaneElement *element = SoXipMprPlaneElement::getInstance(state);
	if (!element) return;

	int numPlanes = element->getNum();
	if (numPlanes <= 0) return;

	updateMprElement(action);

	mMprModelMatrix = element->getMatrix(numPlanes - 1);
	mStepSize = element->getStepSize(numPlanes - 1);
	mThickness = element->getThickness(numPlanes - 1);
	mMprMatrixField = element->getMatrixField(numPlanes - 1);
	mMprCenterField = element->getCenterField(numPlanes - 1);
	mBorderColor = element->getColor(numPlanes - 1);


	// disable notification for this internal scene graph updates
	SbBool saveNotify = enableNotify(FALSE);

	SoSwitch *onOff;
	onOff = (SoSwitch*) getAnyPart("interactionSwitch", TRUE);
	if (onOff)
	{
		onOff->whichChild = manip.getValue() ? 0 : -1;
	}

	onOff = (SoSwitch*) getAnyPart("dogEarSwitch", TRUE);
	if (onOff)
	{
		onOff->whichChild = dogEar.getValue() ? 0 : -1;
	}

	onOff = (SoSwitch*) getAnyPart("borderSwitch", TRUE);
	if (onOff)
	{
		onOff->whichChild = border.getValue() ? 0 : -1;
	}

	onOff = (SoSwitch*) getAnyPart("orientationSwitch", TRUE);
	if (onOff)
	{
		onOff->whichChild = orientationCube.getValue() ? 0 : -1;
	}
	
	enableNotify(saveNotify);
}


void SoXipMprExaminer::updateCamera()
{
	SoOrthographicCamera *cam = (SoOrthographicCamera *) getAnyPart("camera", TRUE);
	if (cam)
	{
		SbVec3f t, s;
		SbRotation r, so;

		// get transform of model matrix
		mMprModelMatrix.getTransform(t, r, s, so);

		// update scale
		if (cam->height.getValue() != s[0])
		{
			cam->height = s[0];
		}

		// update position and orientation of camera if necessary
		SbVec3f pos = t;
		if (cam->position.getValue() != pos)
		{
			cam->position = pos;
		}

		if (cam->orientation.getValue() != r)
		{
			cam->orientation = r;
		}

		if (mThickness>0)
		{
			cam->nearDistance.setValue(-mThickness/2.0f);
			cam->farDistance.setValue(mThickness/2.0f);
		}
	}
}

void SoXipMprExaminer::getBoundingBox(SoGetBoundingBoxAction *action)
{
	updateElement(action);
	SoBaseKit::getBoundingBox(action);
}


void SoXipMprExaminer::callback(SoCallbackAction *action)
{
	updateElement(action);
	SoBaseKit::callback(action);
}


void SoXipMprExaminer::pick(SoPickAction *action)
{
	updateElement(action);
	SoBaseKit::pick(action);
}


SbBool SoXipMprExaminer::setUpConnections(SbBool onoff, SbBool doitalways)
{
	updateDogEarSensors(onoff);

	return SoBaseKit::setUpConnections(onoff, doitalways);
}

void SoXipMprExaminer::updateDogEarSensors(SbBool onoff)
{
	if (mDogEarNextSensor)
	{
		delete mDogEarNextSensor;
		mDogEarNextSensor = 0;
	}

	if (mDogEarPreviousSensor)
	{
		delete mDogEarPreviousSensor;
		mDogEarPreviousSensor = 0;
	}

	if (mOrientationCubeSensor)
	{
		delete mOrientationCubeSensor;
		mOrientationCubeSensor = 0;
	}

	if (onoff)
	{
		SoXipDogEar *aDogEar = (SoXipDogEar*) getAnyPart("dogEarNode", TRUE);
		if (aDogEar)
		{
			mDogEarNextSensor = new SoFieldSensor(&fieldSensorCBFunc, this);
			mDogEarNextSensor->attach(&aDogEar->next);

			mDogEarPreviousSensor = new SoFieldSensor(&fieldSensorCBFunc, this);
			mDogEarPreviousSensor->attach(&aDogEar->previous);
		}

		SoXipOrientationCube *aOC = (SoXipOrientationCube*) getAnyPart("orientationNode", TRUE);
		if (aOC)
		{
			mOrientationCubeSensor = new SoFieldSensor(&fieldSensorCBFunc, this);
			mOrientationCubeSensor->attach(&aOC->orientation);
		}
	}
}

void SoXipMprExaminer::zoomMprList(float scaleFactor)
{
	// zoom
	for (mprPlanes_t::const_iterator i = mMprPlaneList.begin(); i != mMprPlaneList.end(); i++)
	{
		if (!(mMprLock & SoXipMprLockElement::SCALE) && (i < (mMprPlaneList.end() - 1)))
			continue;

		SoSFMatrix *mf = i->matrixField;
		SoSFVec3f  *cf = i->centerField;

		if (mf)
		{
			SbMatrix m = mf->getValue();

			// zoom
			SbVec3f p1, p2, pv(0, 0, 0);
			SbMatrix scale, trans;

			// get center of image before scaling
			m.multVecMatrix(SbVec3f(0, 0, 0), p1);
			if (cf)
			{
				p1 = cf->getValue();
			}

			// get 2D view position of zoom point
			m.inverse().multVecMatrix(p1, pv);

			// scale
			scale.setScale(scaleFactor);
			m *= scale;

			// get center of image after scaling
			m.multVecMatrix(SbVec3f(pv[0], pv[1], 0), p2);

			// translate so center before scaling is center after scaling
			trans.setTranslate(p1 - p2);
			m *= trans;

			if (m != mf->getValue())
			{
				mf->setValue(m);
			}

			if (i == (mMprPlaneList.end() - 1))
			{
				mMprModelMatrix = m;
			}
		}
	}
}

void SoXipMprExaminer::rotateCam(SbRotation rotation, SbVec3f center, SbBool ignoreLock)
{
	// The rotation specified (rotation) is relative to the current plane.
	// Let's apply it first and the compute the rotation in world space,
	// which can be applied to all MPR's.	
	SbRotation r, rBefore, rAfter, rWorld, so;
	SbVec3f t, s;
	mMprModelMatrix.getTransform(t, rBefore, s, so);
	rAfter = rotation * rBefore;
	rWorld = rBefore.inverse() * rAfter;

	SbMatrix rot, trans = SbMatrix::identity();
	rot.setRotate(rWorld);
	trans.setTranslate(center);

	for (mprPlanes_t::const_iterator i = mMprPlaneList.begin(); i != mMprPlaneList.end(); i++)
	{
		if ((ignoreLock || !(mMprLock & SoXipMprLockElement::ORIENTATION)) && (i < (mMprPlaneList.end() - 1)))
			continue;

		SoSFMatrix *mf = i->matrixField;
		SoSFVec3f  *cf = i->centerField;

		if (mf)
		{
			SbMatrix m = mf->getValue();

			m = m * trans.inverse() * rot * trans;

			if (m != mf->getValue())
			{
				mf->setValue(m);
			}

			if (i == (mMprPlaneList.end() - 1))
			{
				mMprModelMatrix = m;
			}
		}
	}
}

void SoXipMprExaminer::panCam(SbVec3f translation)
{
	SbMatrix trans;
	trans.setTranslate(translation);

	for (mprPlanes_t::const_iterator i = mMprPlaneList.begin(); i != mMprPlaneList.end(); i++)
	{
		if (!(mMprLock & SoXipMprLockElement::POSITION) && (i < (mMprPlaneList.end() - 1)))
			continue;

		SoSFMatrix *mf = i->matrixField;
		SoSFVec3f  *cf = i->centerField;

		if (mf)
		{
			SbMatrix m = mf->getValue();

			m *= trans;

			if (m != mf->getValue())
			{
				mf->setValue(m);
			}

			if (i == (mMprPlaneList.end() - 1))
			{
				mMprModelMatrix = m;
			}
		}
	}
}
