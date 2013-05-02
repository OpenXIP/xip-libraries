/*
 *  COPYRIGHT NOTICE.  Copyright (C) 2007 Siemens Corporate Research, 
 *  Inc. ("caBIG(tm) Participant"). The eXtensible Imaging Platform
 *  (XIP) was created with NCI funding and is part of the caBIG(tm) 
 *  initiative. The software subject to this notice and license 
 *  includes both human readable source code form and machine 
 *  readable, binary, object code form (the "caBIG(tm) Software").
 *  
 *  This caBIG(tm) Software License (the "License") is between 
 *  caBIG(tm) Participant and You.  "You (or "Your") shall mean a 
 *  person or an entity, and all other entities that control, are 
 *  controlled by, or are under common control with the entity.  
 *  "Control" for purposes of this definition means (i) the direct or 
 *  indirect power to cause the direction or management of such 
 *  entity, whether by contract or otherwise, or (ii) ownership of 
 *  fifty percent (50%) or more of the outstanding shares, or (iii) 
 *  beneficial ownership of such entity.
 *  
 *  LICENSE.  Provided that You agree to the conditions described 
 *  below, caBIG(tm) Participant grants You a non-exclusive, 
 *  worldwide, perpetual, fully-paid-up, no-charge, irrevocable, 
 *  transferable and royalty-free right and license in its rights in 
 *  the caBIG(tm) Software, including any copyright or patent rights 
 *  therein that may be infringed by the making, using, selling, 
 *  offering for sale, or importing of caBIG(tm) Software, to (i) 
 *  use, install, access, operate, execute, reproduce, copy, modify, 
 *  translate, market, publicly display, publicly perform, and 
 *  prepare derivative works of the caBIG(tm) Software; (ii) make, 
 *  have made, use, practice, sell, and offer for sale, and/or 
 *  otherwise dispose of caBIG(tm) Software (or portions thereof); 
 *  (iii) distribute and have distributed to and by third parties the 
 *  caBIG(tm) Software and any modifications and derivative works 
 *  thereof; and (iv) sublicense the foregoing rights set out in (i), 
 *  (ii) and (iii) to third parties, including the right to license 
 *  such rights to further third parties.  For sake of clarity, and 
 *  not by way of limitation, caBIG(tm) Participant shall have no 
 *  right of accounting or right of payment from You or Your 
 *  sublicensees for the rights granted under this License.  This 
 *  License is granted at no charge to You.  Your downloading, 
 *  copying, modifying, displaying, distributing or use of caBIG(tm) 
 *  Software constitutes acceptance of all of the terms and 
 *  conditions of this Agreement.  If you do not agree to such terms 
 *  and conditions, you have no right to download, copy, modify, 
 *  display, distribute or use the caBIG(tm) Software.
 *  
 *  1.	Your redistributions of the source code for the caBIG(tm) 
 *      Software must retain the above copyright notice, this list 
 *      of conditions and the disclaimer and limitation of 
 *      liability of Article 6 below.  Your redistributions in 
 *      object code form must reproduce the above copyright notice, 
 *      this list of conditions and the disclaimer of Article 6 in 
 *      the documentation and/or other materials provided with the 
 *      distribution, if any.
 *  2.	Your end-user documentation included with the 
 *      redistribution, if any, must include the following 
 *      acknowledgment: "This product includes software developed 
 *      by Siemens Corporate Research Inc."  If You do not include 
 *      such end-user documentation, You shall include this 
 *      acknowledgment in the caBIG(tm) Software itself, wherever 
 *      such third-party acknowledgments normally appear.
 *  3.	You may not use the names "Siemens Corporate Research, 
 *      Inc.", "The National Cancer Institute", "NCI", "Cancer 
 *      Bioinformatics Grid" or "caBIG(tm)" to endorse or promote 
 *      products derived from this caBIG(tm) Software.  This 
 *      License does not authorize You to use any trademarks, 
 *  	service marks, trade names, logos or product names of 
 *      either caBIG(tm) Participant, NCI or caBIG(tm), except as 
 *      required to comply with the terms of this License.
 *  4.	For sake of clarity, and not by way of limitation, You may 
 *      incorporate this caBIG(tm) Software into Your proprietary 
 *      programs and into any third party proprietary programs.  
 *      However, if You incorporate the caBIG(tm) Software into 
 *      third party proprietary programs, You agree that You are 
 *      solely responsible for obtaining any permission from such 
 *      third parties required to incorporate the caBIG(tm) 
 *      Software into such third party proprietary programs and for 
 *      informing Your sublicensees, including without limitation 
 *      Your end-users, of their obligation to secure any required 
 *      permissions from such third parties before incorporating 
 *      the caBIG(tm) Software into such third party proprietary 
 *      software programs.  In the event that You fail to obtain 
 *      such permissions, You agree to indemnify caBIG(tm) 
 *      Participant for any claims against caBIG(tm) Participant by 
 *      such third parties, except to the extent prohibited by law, 
 *      resulting from Your failure to obtain such permissions.
 *  5.	For sake of clarity, and not by way of limitation, You may 
 *      add Your own copyright statement to Your modifications and 
 *      to the derivative works, and You may provide additional or 
 *      different license terms and conditions in Your sublicenses 
 *      of modifications of the caBIG(tm) Software, or any 
 *      derivative works of the caBIG(tm) Software as a whole, 
 *      provided Your use, reproduction, and distribution of the 
 *      Work otherwise complies with the conditions stated in this 
 *      License.
 *  6.	THIS caBIG(tm) SOFTWARE IS PROVIDED "AS IS" AND ANY 
 *      EXPRESSED OR IMPLIED WARRANTIES (INCLUDING, BUT NOT LIMITED 
 *      TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, NON-
 *      INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE) ARE 
 *      DISCLAIMED.  IN NO EVENT SHALL SIEMENS CORPORATE RESEARCH 
 *      INC. OR ITS AFFILIATES BE LIABLE FOR ANY DIRECT, INDIRECT, 
 *      INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
 *      (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE 
 *      GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR 
 *      BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
 *      LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 *      (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT 
 *      OF THE USE OF THIS caBIG(tm) SOFTWARE, EVEN IF ADVISED OF 
 *      THE POSSIBILITY OF SUCH DAMAGE.
 *  
 */

#include <xip/inventor/core/SoXipExaminer.h>
#include <Inventor/sensors/SoFieldSensor.h>
#include <Inventor/sensors/SoTimerSensor.h>
#include <Inventor/nodes/SoPerspectiveCamera.h>
#include <Inventor/nodes/SoOrthographicCamera.h>
#include <Inventor/nodes/SoSwitch.h>
#include <Inventor/elements/SoViewportRegionElement.h>
#include <Inventor/elements/SoCoordinateElement.h>
#include <Inventor/events/SoMouseButtonEvent.h>
#include <Inventor/events/SoLocation2Event.h>

#ifdef WIN32
# include <Inventor/events/SoMouseWheelEvent.h>
#else
# include "../../extern/inventor/lib/xip/include/Inventor/events/SoMouseWheelEvent.h"
#endif

#include <Inventor/projectors/SbPlaneProjector.h>
#include <Inventor/projectors/SbSphereSheetProjector.h>
#include <Inventor/projectors/SbLineProjector.h>
#include <Inventor/elements/SoViewportRegionElement.h>
#include <Inventor/elements/SoViewVolumeElement.h>
#include <Inventor/elements/SoModelMatrixElement.h>
#include <xip/inventor/core/SoXipActiveViewportElement.h> // SoXipRenderNodeElement
#include <Inventor/SoPickedPoint.h>
#include <xip/inventor/core/SoXipCursor.h>
#include <xip/inventor/core/XipGeomUtils.h>
#include <xip/inventor/core/SoXipMprPlaneElement.h>
#include <Inventor/nodes/SoAnnotation.h>
#include "SoXipViewportBorder.h"


const int ROT_BUFF_SIZE = 3;
//quality value texture mapping.Valid range is from 0.0 to 1.0
const float TEXTURE_QUALITY = 0.249;


SO_KIT_SOURCE(SoXipExaminer);


SoXipExaminer::SoXipExaminer()
{
	SO_KIT_CONSTRUCTOR(SoXipExaminer);

	isBuiltIn = TRUE;
	mViewAll = FALSE;
	mResetPlane = FALSE;
	mViewVolume.ortho(-1, 1, -1, 1, 1, 10);
	mVpRegion = SbViewportRegion(1, 1);
	mViewTransform = SbMatrix::identity();
	mLastMousePos = mMouseDownPos = SbVec2f(0, 0);
	mShowPlaneRotationPoint = FALSE;

	mPlaneProj = new SbPlaneProjector(FALSE);
	mPlaneProj->setPlane(SbPlane(SbVec3f(0, 0, 1), 0));

    mSphereSheetProj = new SbSphereSheetProjector;
    mSphereSheetProj->setViewVolume(mViewVolume);
    mSphereSheetProj->setSphere(SbSphere(SbVec3f(0, 0, 0), .7f));

	mIsFirstMouseDown = FALSE;
	mLastHandleEventTime.setToTimeOfDay();

	mParentId = 0;
	mSceneCamera = 0;
	mSceneCameraId = 0;

	// Initialize children catalog and add entries to it:
	//
	//     cameraSwitch      borderSwitch     complexity
	//          |                 |
	//      +--------+        annotation
	//      |        |            |
	//    ortho perspective   borderNode
	//
	SO_KIT_ADD_CATALOG_ENTRY(cameraSwitch, SoSwitch, FALSE, this, \0 , FALSE);
	SO_KIT_ADD_CATALOG_ENTRY(borderSwitch, SoSwitch, FALSE, this, \0 , FALSE);
	SO_KIT_ADD_CATALOG_ENTRY(complexity, SoComplexity, FALSE, this, \0 , FALSE);
	SO_KIT_ADD_CATALOG_ENTRY(orthoCamera, SoOrthographicCamera, FALSE, cameraSwitch, \0 , FALSE);
	SO_KIT_ADD_CATALOG_ENTRY(perspectiveCamera, SoPerspectiveCamera, FALSE, cameraSwitch, \0 , FALSE);
	SO_KIT_ADD_CATALOG_ENTRY(annotation, SoAnnotation, FALSE, borderSwitch, \0 , FALSE);
	SO_KIT_ADD_CATALOG_ENTRY(borderNode, SoXipViewportBorder, FALSE, annotation, \0 , FALSE);

	SO_KIT_INIT_INSTANCE();

	SO_NODE_ADD_FIELD(perspective, (TRUE));

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

	SO_NODE_ADD_FIELD(viewAll, ());
	SO_NODE_ADD_FIELD(resetPlane, ());

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
	SO_NODE_DEFINE_ENUM_VALUE(modeType, PANZOOM);
	SO_NODE_DEFINE_ENUM_VALUE(modeType, ROTATE_PLANE);
	SO_NODE_DEFINE_ENUM_VALUE(modeType, TRANSLATE_PLANE);
	SO_NODE_DEFINE_ENUM_VALUE(modeType, PAN);

	SO_NODE_SET_SF_ENUM_TYPE(mode, modeType);
	SO_NODE_ADD_FIELD(mode, (NONE));
	SO_NODE_ADD_FIELD(pointTo, (FALSE));
	SO_NODE_ADD_FIELD(border, (FALSE));
	SO_NODE_ADD_FIELD(borderColor, (SbColor(0.7f, 0.7f, 0.7f)));
	SO_NODE_ADD_FIELD(autoSpin, (FALSE));
	SO_NODE_ADD_FIELD(rotatePinpoint, (FALSE));

	SO_NODE_ADD_FIELD(rotateCamera, (SbRotation(SbVec3f(0, 0, 1), 0)));
	SO_NODE_ADD_FIELD(scaleHeight, (1.0f));

	SO_NODE_ADD_FIELD(viewBoundingBox, (SbMatrix::identity()));
	SO_NODE_ADD_FIELD(plane, (SbPlane(SbVec3f(0, 0, 1), 0)));
	

	SoField *fields[] = { &viewAll, &perspective, &resetPlane, &viewOrientation, &rotateCamera, &scaleHeight };
	for (int i = 0; i < (sizeof(fields) / sizeof(SoField*)); i++)
	{
		SoFieldSensor *fieldSensor = new SoFieldSensor(&fieldSensorCBFunc, this);
		fieldSensor->attach(fields[i]);
		mInputSensors.push_back(fieldSensor);
	}

	mTimerSensor = new SoTimerSensor(timerSensorCBFunc, this);
	mTimerSensor->setInterval(0.05);	// 20 fps

	mRotBuffer = new SbRotation[ROT_BUFF_SIZE];

	SoSwitch *cameraSwitch = (SoSwitch*) getAnyPart("cameraSwitch", TRUE);
	cameraSwitch->whichChild.setValue(perspective.getValue());

	mAutoSpinRotation.setValue(SbVec3f(0, 0, 1), 0);
	mAnimRotationStart.setValue(SbVec3f(0, 0, 1), 0);
	mAnimRotationStop.setValue(SbVec3f(0, 0, 1), 0);
	mAnimSlerp = 0.f;
}


SoXipExaminer::~SoXipExaminer()
{
	delete mPlaneProj;
	delete mSphereSheetProj;
	delete [] mRotBuffer;

	std::vector<SoFieldSensor *>::iterator i;
	for (i = mInputSensors.begin(); i != mInputSensors.end(); i++)
	{
		delete (*i);
	}

	if (mTimerSensor)
	{
		delete mTimerSensor;
	}
}


void SoXipExaminer::initClass()
{
	SO_KIT_INIT_CLASS(SoXipExaminer, SoBaseKit, "BaseKit");

	SO_ENABLE(SoHandleEventAction, SoXipMprPlaneElement);
	SO_ENABLE(SoHandleEventAction, SoViewportRegionElement);
	SO_ENABLE(SoHandleEventAction, SoViewVolumeElement);
	SO_ENABLE(SoHandleEventAction, SoModelMatrixElement);
}


void SoXipExaminer::extractViewingParams(SoHandleEventAction *action)
{
	if (!action) 
	{
		// If the action is NULL, use default values for view info.
		mViewVolume.ortho(-1, 1, -1, 1, 1, 10);
		mVpRegion = SbViewportRegion(1, 1);
	}
	else 
	{
		// Get the view info from the action.
		SoState *state = action->getState();
		mViewVolume = SoViewVolumeElement::get(state);
		mVpRegion = SoViewportRegionElement::get(state);
		mViewTransform = SoModelMatrixElement::get(state);
	}
}


SbVec2f SoXipExaminer::getMousePosNormalized(SoHandleEventAction *action)
{
	const SoEvent *e = action->getEvent();

	if (action->getGrabber() != this)
	{
		extractViewingParams(action);
	}

	return e->getNormalizedPosition(mVpRegion);
}


SoCamera *SoXipExaminer::getCamera()
{
	if (mSceneCamera) return mSceneCamera;

	return (SoCamera*) (perspective.getValue() ? getAnyPart("perspectiveCamera", TRUE) : getAnyPart("orthoCamera", TRUE));
}


void SoXipExaminer::inputChanged(SoField *which)
{
	if (which == &viewAll)
	{
		mViewAll = TRUE;
		touch();
	}
	else if (which == &resetPlane)
	{
		mResetPlane = TRUE;
		touch();
	}
	else if (which == &perspective)
	{
		SoSwitch *cameraSwitch = (SoSwitch*) getAnyPart("cameraSwitch", TRUE);

		if (cameraSwitch->whichChild.getValue() != perspective.getValue())
		{
			SoCamera *from, *to;
			if (perspective.getValue())
			{
				from = (SoCamera*) getAnyPart("orthoCamera", TRUE);
				to = (SoCamera*) getAnyPart("perspectiveCamera", TRUE);
			}
			else
			{
				to = (SoCamera*) getAnyPart("orthoCamera", TRUE);
				from = (SoCamera*) getAnyPart("perspectiveCamera", TRUE);
			}

			to->viewportMapping = from->viewportMapping;
			to->position        = from->position;
			to->orientation     = from->orientation;
			to->aspectRatio     = from->aspectRatio;
			to->nearDistance    = from->nearDistance;
			to->farDistance     = from->farDistance;
			to->focalDistance   = from->focalDistance;

			cameraSwitch->whichChild.setValue(perspective.getValue());
		}
	}
	else if (which == &viewOrientation)
	{
		SbRotation rot, oldRot;
		rot = oldRot = getCamera()->orientation.getValue();

		const float fM_PI = static_cast<float>(M_PI);

		switch (orientation.getValue())
		{
		case FEET:		rot = SbRotation(SbVec3f(1, 0, 0), fM_PI); break;
		case HEAD:		rot = SbRotation(SbVec3f(0, 0, 1), fM_PI); break;
		case LEFT:		rot = SbRotation(SbVec3f(0, 0, 1),  fM_PI / 2.f) * SbRotation(SbVec3f(0, 1, 0),  fM_PI / 2.f); break;
		case RIGHT:		rot = SbRotation(SbVec3f(0, 0, 1), -fM_PI / 2.f) * SbRotation(SbVec3f(0, 1, 0), -fM_PI / 2.f); break;
		case ANTERIOR:	rot = SbRotation(SbVec3f(1, 0, 0), fM_PI / 2.f); break;
		case POSTERIOR:	rot = SbRotation(SbVec3f(0, 1, 0), fM_PI) * SbRotation(SbVec3f(1, 0, 0), fM_PI / 2.f); break;
		case RANGE_START: rot = SbRotation(SbVec3f(0, 1, 0), -fM_PI / 2.f); break;
		case RANGE_END:   rot = SbRotation(SbVec3f(0, 1, 0), fM_PI / 2.f); break;
		case AZIMUTH_START: rot = SbRotation(SbVec3f(0, 0, 1),  fM_PI / 2.f); break;
		case AZIMUTH_END: rot = SbRotation(SbVec3f(0, 1, 0),  fM_PI) * SbRotation(SbVec3f(0, 0, 1),  fM_PI / 2.f); break;
		case ELEVATION_START: rot = SbRotation(SbVec3f(0, 1, 0),  fM_PI / 2.f) * SbRotation(SbVec3f(0, 0, 1),  fM_PI / 2.f); break;
		case ELEVATION_END: rot = SbRotation(SbVec3f(0, 1, 0),  -fM_PI / 2.f) * SbRotation(SbVec3f(0, 0, 1),  fM_PI / 2.f); break;
		}

		rotateCam(rot * oldRot.inverse(), TRUE);
	}
	else if (which == &rotateCamera)
	{
		rotateCam(rotateCamera.getValue(), TRUE);
	}
	else if (which == &scaleHeight)
	{
		scaleCam(scaleHeight.getValue());
	}
}

void SoXipExaminer::timer(SoSensor *sensor)
{
	if (getCamera()->getNodeId() != mSceneCameraId || !autoSpin.getValue())
	{
		// somebody else is working with our camera, stop all animations
		setInteractive(FALSE);
		mTimerSensor->unschedule();
		mAutoSpinRotation.setValue(SbVec3f(0, 0, 1), 0);
		mAnimRotationStart.setValue(SbVec3f(0, 0, 1), 0);
		mAnimRotationStop.setValue(SbVec3f(0, 0, 1), 0);

		return;
	}


	if (!mAnimRotationStart.equals(mAnimRotationStop, 0.001f))
	{
		// animation
		
		mAnimSlerp += (1.1f - mAnimSlerp) * 0.2f;

		if (mAnimSlerp >= 1.f)
			mAnimSlerp = 1.f;

		SbRotation rot = SbRotation::slerp(mAnimRotationStart, mAnimRotationStop, mAnimSlerp);

		// get center of rotation
		SbRotation camRot = getCamera()->orientation.getValue();
		float radius = getCamera()->focalDistance.getValue();
		SbMatrix m;
		m = camRot;
		SbVec3f dir(-m[2][0], -m[2][1], -m[2][2]);
		SbVec3f center = getCamera()->position.getValue() + dir * radius;

		// apply new rotation to the camera
		camRot = rot;// * camRot;
		getCamera()->orientation = camRot;

		// reposition camera to look at pt of interest
		m = camRot;
		dir.setValue(-m[2][0], -m[2][1], -m[2][2]);
		getCamera()->position = center - dir * radius;

		if (mAnimSlerp >= 1.f)
		{
			mAutoSpinRotation.setValue(SbVec3f(0, 0, 1), 0);
			mAnimRotationStart.setValue(SbVec3f(0, 0, 1), 0);
			mAnimRotationStop.setValue(SbVec3f(0, 0, 1), 0);

			// stop timer if user switched mode
			if (mTimerSensor->isScheduled())
			{
				setInteractive(FALSE);
				mTimerSensor->unschedule();
			}
		}
	}
	else if ((mode.getValue() == ROTATE) && (fabs(mAutoSpinRotation.getValue()[3]) > 0.001f))
	{
		// auto rotate
		rotateCam(mAutoSpinRotation);
	}
	else
	{
		mAutoSpinRotation.setValue(SbVec3f(0, 0, 1), 0);
		mAnimRotationStart.setValue(SbVec3f(0, 0, 1), 0);
		mAnimRotationStop.setValue(SbVec3f(0, 0, 1), 0);

		// stop timer if user switched mode
		if (mTimerSensor->isScheduled())
		{
			setInteractive(FALSE);
			mTimerSensor->unschedule();
		}
	}

	mSceneCameraId = getCamera()->getNodeId();
}


void SoXipExaminer::fieldSensorCBFunc(void *usr, SoSensor *sensor)
{
	((SoXipExaminer*)usr)->inputChanged(((SoFieldSensor*) sensor)->getAttachedField());
}


void SoXipExaminer::timerSensorCBFunc(void *usr, SoSensor *sensor)
{
	((SoXipExaminer*)usr)->timer(sensor);
}


SoCamera *SoXipExaminer::findCameraInScene(SoAction *action)
{
	SoCamera *oldCamera = mSceneCamera;
	mSceneCamera = 0;

	if (action) 
	{
		const SoPath *path = action->getCurPath();
		if (path->getLength() > 1)
		{
			SoNode *parentNode = path->getNodeFromTail(1);

			if ((parentNode->getNodeId() != mParentId) && parentNode->isOfType(SoGroup::getClassTypeId()))
			{
				mParentId = parentNode->getNodeId();
				SoGroup *parent = (SoGroup *) parentNode;

				SoSearchAction sa;
				sa.setFind(SoSearchAction::TYPE);
				sa.setInterest(SoSearchAction::ALL);
				sa.setType(SoCamera::getClassTypeId(), TRUE);

				// find first camera before this
				SbBool foundThis = FALSE;
				for (int i = parent->getNumChildren() - 1; i >= 0; i--)
				{
					if (!foundThis)
					{
						if (parent->getChild(i) == this)
							foundThis = TRUE;
						continue;
					}
					else
					{
						sa.apply(parent->getChild(i));
						SoPathList results = sa.getPaths();
						if (results.getLength() > 0)
						{
							SoNode *n = results[results.getLength() - 1]->getTail();
							if (n->isOfType(SoCamera::getClassTypeId()))
							{
								mSceneCamera = (SoCamera*) n;
								break;
							}
						}
					}
				}
			}
			else
			{
				mSceneCamera = oldCamera;
			}
		}
	}

	return mSceneCamera;
}


void SoXipExaminer::GLRender(SoGLRenderAction * action)
{
	if (!action->isRenderingDelayedPaths())
	{
		SoCamera *cam = findCameraInScene(action);
		int whichChild = cam ? -1 : perspective.getValue();
		SoSwitch *cameraSwitch = (SoSwitch*) getAnyPart("cameraSwitch", TRUE);
		if (cameraSwitch->whichChild.getValue() != whichChild)
			cameraSwitch->whichChild.setValue(whichChild);
	}


	if (!SoXipActiveViewportElement::get(action->getState()))
	{
		// whenever this is not the active segment the next mouse click is for activation only
		mIsFirstMouseDown = TRUE;
	}

	SoSwitch *onOff = (SoSwitch*) getAnyPart("borderSwitch", TRUE);
	if (onOff)
	{
		if (onOff->whichChild.getValue() != (border.getValue() ? 0 : -1))
			onOff->whichChild.setValue(border.getValue() ? 0 : -1);
	}

	SoXipViewportBorder *b = (SoXipViewportBorder*) getAnyPart("borderNode", TRUE);
	if ((b->activeColor.getValue() != borderColor.getValue()) || (b->inactiveColor.getValue() != borderColor.getValue()))
	{
		b->activeColor.setValue(borderColor.getValue());
		b->inactiveColor.setValue(borderColor.getValue());
	}			

	if (mViewAll)
	{
		SbViewportRegion viewportRegion = SoViewportRegionElement::get(action->getState());

		const SoPath *path = action->getCurPath();
		if (path)
		{
			// get the node one before this
			SoNode *node = path->getNodeFromTail(1);
			if (node)
			{
				if (getCamera()->isOfType(SoPerspectiveCamera::getClassTypeId()))
				{
					((SoPerspectiveCamera*) getCamera())->heightAngle.setValue((45.f / 180.) * static_cast<float>(M_PI));
				}

				getCamera()->viewAll(node, viewportRegion);
				getCamera()->scaleHeight(scaleHeight.getValue());

				// compute bounding box
				SoGetBoundingBoxAction bba(viewportRegion);

				// Find the bounding box of the scene
				bba.apply(node);

				SbBox3f box = bba.getBoundingBox();

				if (!box.isEmpty())
				{
					SbVec3f origin, size;

					box.getOrigin(origin[0], origin[1], origin[2]);
					box.getSize(size[0], size[1], size[2]);

					SbMatrix m;
					m.setTransform(origin, SbRotation(SbMatrix::identity()), size);
					viewBoundingBox.setValue(m);
				}
				else
				{
					viewBoundingBox.setValue(SbMatrix::identity());
				}

				// make sure the updated camera is set if it is an external one
				// the build in cameras will be traversed later in this method
				if (mSceneCamera)
					action->traverse(mSceneCamera);
			}
		}

		mViewAll = FALSE;
	}

	if (mResetPlane)
	{
		SbRotation camRot = getCamera()->orientation.getValue();
		float radius = getCamera()->focalDistance.getValue();
		SbMatrix m;
		m = camRot;
		SbVec3f dir(-m[2][0], -m[2][1], -m[2][2]);
		SbVec3f center = getCamera()->position.getValue() + dir * radius;

		plane.setValue(SbPlane(dir, center));

		mResetPlane = FALSE;
	}

	SoBaseKit::GLRender(action); 

	SoCoordinateElement::set3(action->getState(), this, mShowPlaneRotationPoint ? 1 : 0, &mDragStartMouseOnPlane);
}


void SoXipExaminer::getBoundingBox(SoGetBoundingBoxAction *action)
{
	SoBaseKit::getBoundingBox(action); 

	SoCoordinateElement::set3(action->getState(), this, 0, &mDragStartMouseOnPlane);
}


void SoXipExaminer::updateCursor()
{
	switch (mode.getValue())
	{
	case PAN:		SoXipCursor::setCursor("SEL_PAN");
					break;
	case PANZOOM:	if (mDragStartMouseBorder)
						SoXipCursor::setCursor("SEL_ZOOM");
					else
						SoXipCursor::setCursor("SEL_PAN");
					break;
	case ROTATE:	if (mDragStartMouseBorder)
						SoXipCursor::setCursor("ROTATE_NORMAL_VR");//SoXipCursor::ROTATE_INPLANE
					else
						SoXipCursor::setCursor("SEL_ROTATE_VR");//SoXipCursor::SEL_ROTATE
					break;
	case ROTATE_PLANE:
					SoXipCursor::setCursor("ROTATE_CLIP");
					break;
	case TRANSLATE_PLANE:
					SoXipCursor::setCursor("TRANS_CLIP");
					break;
	default:
		SoXipCursor::setCursor();
	}
}

void SoXipExaminer::handleEvent(SoHandleEventAction *action)
{
	if (action->getGrabber() == 0)
	{
		extractViewingParams(action);
	}

    SbBool keyOk = TRUE;
    if (key.getValue() & SHIFT_KEY) keyOk &= action->getEvent()->wasShiftDown();
    if (key.getValue() & CTRL_KEY) keyOk &= action->getEvent()->wasCtrlDown();
    if (!(key.getValue() & SHIFT_KEY)) keyOk &= !action->getEvent()->wasShiftDown();
    if (!(key.getValue() & CTRL_KEY)) keyOk &= !action->getEvent()->wasCtrlDown();

	// scroll wheel translates clip plane
	if (action->getEvent()->isOfType(SoMouseWheelEvent::getClassTypeId()) && !action->getEvent()->wasShiftDown() && !action->getEvent()->wasCtrlDown()
		&& SoXipActiveViewportElement::get(action->getState()))
	{
		action->setHandled();

		int delta = ((SoMouseWheelEvent*) action->getEvent())->getDelta();	
		SbVec3f step;
		SbMatrix trans;
		SbPlane p = plane.getValue();
		step = static_cast<float>(delta) * p.getNormal();
		trans.setTranslate(step);
		p.transform(trans);
		plane.setValue(p);
	}


	if (mIsFirstMouseDown && border.getValue())
	{
		if (SO_MOUSE_PRESS_EVENT(action->getEvent(), ANY))
		{
			action->setHandled();
			action->setGrabber(this);
			return;
		}
		else if (SO_MOUSE_RELEASE_EVENT(action->getEvent(), ANY) && (action->getGrabber() == this)) 
		{
			action->releaseGrabber();
			mIsFirstMouseDown = FALSE;
			action->setHandled();
			return;
		}
		else if (action->getEvent()->isOfType(SoLocation2Event::getClassTypeId()))
		{
			SbVec2f pos = getMousePosNormalized(action);
			if ((pos[0] >= 0.f) && (pos[0] <= 1.f) &&
				(pos[1] >= 0.f) && (pos[1] <= 1.f))
			{
				SoXipCursor::setCursor();
			}
			return;
		}
	}

	mHandleEventAction = action;

	SbBool handled = FALSE;
	const SoEvent *e = action->getEvent();

	// call base class first
	SoBaseKit::handleEvent(action);

	if (!pointTo.getValue() && (mode.getValue() == NONE))
	{
		// do nothing
		return;
	}

	if (SoMouseButtonEvent::isButtonPressEvent(e, (SoMouseButtonEvent::Button) mouse.getValue()))
	{
		if ((action->getGrabber() != this) && keyOk)
		{
			// get MPR planes
			mMprPlaneList.clear();
			SoXipMprPlaneElement *element = SoXipMprPlaneElement::getInstance(action->getState());
			if (element)
			{
				int numPlanes = element->getNum();

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
			mRotFirstIndex = 0;
			mRotLastIndex = -1;

			mAutoSpinRotation.setValue(SbVec3f(0, 0, 1), 0);
			mAnimRotationStart.setValue(SbVec3f(0, 0, 1), 0);
			mAnimRotationStop.setValue(SbVec3f(0, 0, 1), 0);
			mAnimSlerp = 0.f;


			// set focal plane as projection plane
			SbMatrix m;
			m = getCamera()->orientation.getValue();
			SbVec3f dir(-m[2][0], -m[2][1], -m[2][2]);
			SbVec3f focalPoint = getCamera()->position.getValue() + dir * getCamera()->focalDistance.getValue();
			mPlaneProj->setPlane(SbPlane(dir, focalPoint));
			mPlaneProj->setViewVolume(mViewVolume);

			// set sphere sheet starting point
			mSphereSheetProj->project(getMousePosNormalized(action));

			mLastMousePos = getMousePosNormalized(action);
			mMouseDownPos = mLastMousePos;
			mDragStartMouse = mPlaneProj->project(mLastMousePos);
			mDragStartCameraPos = getCamera()->position.getValue();
			mRotLastNormPos = mLastMousePos - SbVec2f(0.5, 0.5);

			if (plane.getValue().getNormal().dot(mViewVolume.getProjectionDirection()))
			{
				SbPlaneProjector cutPlaneProj = *mPlaneProj;
				cutPlaneProj.setPlane(plane.getValue());
				mDragStartMouseOnPlane = cutPlaneProj.project(mLastMousePos);
			}

			if (rotatePinpoint.getValue() && (mode.getValue() == ROTATE_PLANE))
			{
				mShowPlaneRotationPoint = TRUE;
			}

			// if point on clip plane is outside volume, use center of view volume instead
			SbVec3f tmp;
			viewBoundingBox.getValue().inverse().multVecMatrix(mDragStartMouseOnPlane, tmp);
			if (!((tmp[0] > 0) && (tmp[0] < 1) && (tmp[1] > 0) && (tmp[1] < 1) && (tmp[2] > 0) && (tmp[2] < 1)))
			{
				viewBoundingBox.getValue().multVecMatrix(SbVec3f(0.5f, 0.5f, 0.5f), mDragStartMouseOnPlane);
				mShowPlaneRotationPoint = FALSE;
			}

			switch (mode.getValue())
			{
				case PANZOOM:	mDragStartMouseBorder = (mLastMousePos[0] > 0.6f) || (mLastMousePos[1] > 0.6f) || (mLastMousePos[0] < 0.4f) || (mLastMousePos[1] < 0.4f); break;
				case ROTATE:	mDragStartMouseBorder = (mLastMousePos[0] > 0.9f) || (mLastMousePos[1] > 0.9f) || (mLastMousePos[0] < 0.1f) || (mLastMousePos[1] < 0.1f); break;
				default:
					mDragStartMouseBorder = FALSE;
			}

			action->setGrabber(this);

			updateCursor();

			handled = TRUE;
		}
	}
	else if (e->isOfType(SoLocation2Event::getClassTypeId()))
	{
		if (action->getGrabber() == this)
		{
			handled = TRUE;

			setInteractive(TRUE);
	
			
			if ((e->getTime() - mLastHandleEventTime).getValue() > 0.25)
			{
				mRotFirstIndex = 0;
				mRotLastIndex = -1;
			}

			switch (mode.getValue())
			{
			case PAN:		mDragStartMouseBorder = false;
			case PANZOOM:	if (mDragStartMouseBorder)
								scaleCam(1.f + (mLastMousePos[1] - getMousePosNormalized(action)[1]));
							else
								panCam(getMousePosNormalized(action));
							break;
			case ROTATE:	if (mDragStartMouseBorder)
								spinNormCam(getMousePosNormalized(action));
							else
								spinCam(getMousePosNormalized(action));
							break;
			case ROTATE_PLANE:
							mouseRotatePlane(getMousePosNormalized(action));
							break;
			case TRANSLATE_PLANE:
							mouseTranslatePlane(getMousePosNormalized(action));
							break;
			default:
				handled = FALSE;
			}

			mLastMousePos = getMousePosNormalized(action);

			updateCursor();
		}
		else if (!action->isHandled() && keyOk && (mouse.getValue() == BUTTON1))
		{
			mLastMousePos = getMousePosNormalized(action);
			if ((mLastMousePos[0] >= 0.f) && (mLastMousePos[0] <= 1.f) &&
				(mLastMousePos[1] >= 0.f) && (mLastMousePos[1] <= 1.f))
			{
				switch (mode.getValue())
				{
				case PANZOOM:	mDragStartMouseBorder = !XipGeomUtils::isVecInObjectSpace(SbVec3f((mLastMousePos[0] * 2) - 1, (mLastMousePos[1] * 2) - 1, 0), 0.6f); break;
				case ROTATE:	mDragStartMouseBorder = (mLastMousePos[0] > 0.9f) || (mLastMousePos[1] > 0.9f) || (mLastMousePos[0] < 0.1f) || (mLastMousePos[1] < 0.1f); break;
				default:
					mDragStartMouseBorder = FALSE;
				}

				if (mode.getValue() != NONE)
				{
					updateCursor();
					action->setHandled();
				}
			}
		}
	}
	//else if (SoMouseButtonEvent::isButtonReleaseEvent(e, mDragMouseButton) && (action->getGrabber() == this)) 
	else if (SO_MOUSE_RELEASE_EVENT(e, ANY) && (action->getGrabber() == this)) 
	{
		mShowPlaneRotationPoint = FALSE;
		action->releaseGrabber();
		handled = TRUE;

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
			scrollToCursor(action);
			setInteractive(FALSE);
			SoComplexity *complexityPtr = (SoComplexity*) getAnyPart("complexity", TRUE);
			complexityPtr->value.setValue(0.5);
			complexityPtr->textureQuality.setValue(0.5);
		}
		else
		{
			if ((e->getTime() - mLastHandleEventTime).getValue() > 0.25)
			{
				mRotFirstIndex = 0;
				mRotLastIndex = -1;
			}
			
			float averageAngle, angle;
			SbVec3f averageAxis, axis;

			// get number of samples
			int num = (((mRotLastIndex - mRotFirstIndex) + 1 + ROT_BUFF_SIZE) % ROT_BUFF_SIZE);

			// check for not enough samples
			if (num >= 2 && autoSpin.getValue()) 
			{
				// get average axis of rotation
				// ??? right now only take one sample
				mRotBuffer[mRotFirstIndex].getValue(averageAxis, angle);

				// get average angle of rotation
				averageAngle = 0;
				for (int i=0; i<num; i++) 
				{
					int n = (mRotFirstIndex + i) % ROT_BUFF_SIZE;
					mRotBuffer[n].getValue(axis, angle);
					averageAngle += angle;
				}
				averageAngle /= float(num);
				//averageAngle /= 2.0f;

				mAutoSpinRotation.setValue(averageAxis, averageAngle);
				mSceneCameraId = getCamera()->getNodeId();
				mTimerSensor->schedule();
			}
			else
			{
				setInteractive(FALSE);
				SoComplexity *complexityPtr = (SoComplexity*) getAnyPart("complexity", TRUE);
				complexityPtr->value.setValue(0.5);
				complexityPtr->textureQuality.setValue(0.5);
			}
		}
	}

	if (handled)
	{
		action->setHandled();
		mLastHandleEventTime = e->getTime();
	}
}


void SoXipExaminer::panCam(const SbVec2f pos)
{
	getCamera()->position = mDragStartCameraPos + (mDragStartMouse - mPlaneProj->project(pos));
}


void SoXipExaminer::scaleCam(float scale)
{
	getCamera()->scaleHeight(scale);

	if (getCamera()->isOfType(SoPerspectiveCamera::getClassTypeId()))
	{
		float ha = ((SoPerspectiveCamera*) getCamera())->heightAngle.getValue();
		if (ha > 3.0)
		{
			((SoPerspectiveCamera*) getCamera())->heightAngle.setValue(3.0f);
		}
		if (ha < 0.1)
		{
			((SoPerspectiveCamera*) getCamera())->heightAngle.setValue(0.1f);
		}
	}
	else if (getCamera()->isOfType(SoOrthographicCamera::getClassTypeId()))
	{
		float h = ((SoOrthographicCamera*) getCamera())->height.getValue();

		SbMatrix m = viewBoundingBox.getValue();
		float maxHeight = 0.f;
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				if (m[i][j] > maxHeight)
					maxHeight = m[i][j];

		if (h > (10.f * maxHeight))
		{
			((SoOrthographicCamera*) getCamera())->height.setValue(10.f * maxHeight);
		}

		if (h < (0.1f * maxHeight))
		{
			((SoOrthographicCamera*) getCamera())->height.setValue(0.1f * maxHeight);
		}
	}
}


void SoXipExaminer::rotateCam(const SbRotation &rot, SbBool enableAnimation)
{
	if (autoSpin.getValue() && enableAnimation)
	{
		mAutoSpinRotation.setValue(SbVec3f(0, 0, 1), 0);
		mAnimRotationStart = getCamera()->orientation.getValue();
		mAnimRotationStop  = rot * mAnimRotationStart;

		SbVec3f axis;
		float radians;
		rot.getValue(axis, radians);

		if (radians < 0.001f)
		{
			mAutoSpinRotation.setValue(SbVec3f(0, 0, 1), 0);
			mAnimRotationStart.setValue(SbVec3f(0, 0, 1), 0);
			mAnimRotationStop.setValue(SbVec3f(0, 0, 1), 0);
		}
		else
		{
			mAnimSlerp = 0.f;
			setInteractive(TRUE);
			mSceneCameraId = getCamera()->getNodeId();

			if (!mTimerSensor->isScheduled())
				mTimerSensor->schedule();
		}
	}
	else
	{
		// get center of rotation
		SbRotation camRot = getCamera()->orientation.getValue();
		float radius = getCamera()->focalDistance.getValue();
		SbMatrix m;
		m = camRot;
		SbVec3f dir(-m[2][0], -m[2][1], -m[2][2]);
		SbVec3f center = getCamera()->position.getValue() + dir * radius;

		// apply new rotation to the camera
		camRot = rot * camRot;
		getCamera()->orientation = camRot;

		// reposition camera to look at pt of interest
		m = camRot;
		dir.setValue(-m[2][0], -m[2][1], -m[2][2]);
		getCamera()->position = center - dir * radius;
	}
}


void SoXipExaminer::spinCam(const SbVec2f pos)
{
	// find rotation and rotate camera
	SbRotation rot;
	mSphereSheetProj->projectAndGetRotation(pos, rot);
	rot.invert();

	rotateCam(rot);

	// save rotation for animation
	mRotLastIndex = ((mRotLastIndex+1) % ROT_BUFF_SIZE);
	mRotBuffer[mRotLastIndex] = rot;

	// check if queue is full
	if (((mRotLastIndex+1) % ROT_BUFF_SIZE) == mRotFirstIndex)
	mRotFirstIndex = ((mRotFirstIndex+1) % ROT_BUFF_SIZE);
}

void SoXipExaminer::spinNormCam(const SbVec2f pos)
{
	SbVec2f norm = pos - SbVec2f(0.5, 0.5);
	
	SbVec3f from, to;
	from = SbVec3f(mRotLastNormPos[0], mRotLastNormPos[1], 0.f);
	to = SbVec3f(norm[0], norm[1], 0);

	SbRotation rot(from, to);
	rot.invert();
	rotateCam(rot);

	mRotLastNormPos = norm;
}

// --------------------------------------------------------------------------
//! used to rotate the plane
// --------------------------------------------------------------------------
void SoXipExaminer::rotatePlane(const SbRotation &rot, const SbVec3f &center)
//void SoXipExaminer::rotatePlane(const SbRotation &rot)
{
	// change the plane equation by transforming it with a rotation matrix
	//SbVec3f center;
	//viewBoundingBox.getValue().multVecMatrix(SbVec3f(0.5f, 0.5f, 0.5f), center);
	SbPlane tmpPlane(plane.getValue());

	SbMatrix tmpMat;
	tmpMat.makeIdentity();

	tmpMat.setTransform(SbVec3f(0, 0, 0), rot, SbVec3f(1, 1, 1), SbRotation(1, 1, 1, 1), center);

	tmpPlane.transform(tmpMat);
	plane.setValue(tmpPlane);
}


// --------------------------------------------------------------------------
//! used to translate the plane
// --------------------------------------------------------------------------
void SoXipExaminer::translatePlane(const SbVec3f &tvec)
{
	// change the plane equation by transforming it with a translation matrix

	// change the plane equation by transforming it with a rotation matrix
	SbVec3f center, minVec, maxVec;
	viewBoundingBox.getValue().multVecMatrix(SbVec3f(0.5f, 0.5f, 0.5f), center);	
	viewBoundingBox.getValue().multVecMatrix(SbVec3f(0.f, 0.f, 0.f), minVec);	
	viewBoundingBox.getValue().multVecMatrix(SbVec3f(1.0f, 1.0f, 1.0f), maxVec);	
	
	SbPlane tmpPlane(plane.getValue());

	SbVec3f planeCenter;
	tmpPlane.intersect(SbLine(center, center + tmpPlane.getNormal()), planeCenter);

	float xc, yc, zc, xmin, ymin, zmin, xmax, ymax, zmax, xcur, ycur, zcur;

	planeCenter.getValue(xc, yc, zc);
	tvec.getValue(xcur, ycur, zcur);

	minVec.getValue(xmin, ymin, zmin);
	maxVec.getValue(xmax, ymax, zmax);

	// test if the plane is still containing in the bounding box 
	if( (xc + xcur < xmin) ||
		(yc + ycur < ymin) ||
		(zc + zcur < zmin) ||
		(xc + xcur > xmax) ||
		(yc + ycur > ymax) ||
		(zc + zcur > zmax))
			return;


	SbMatrix tmpMat;
	tmpMat.makeIdentity();

	tmpMat.setTranslate(tvec);

	tmpPlane.transform(tmpMat);
	plane.setValue(tmpPlane);
}

//--------------------------------------------------------------------------
//! called whenever the scene is rendered
//--------------------------------------------------------------------------
void SoXipExaminer::mouseRotatePlane(const SbVec2f &mousePos)
{
	SbVec3f center, minVec, maxVec;
	viewBoundingBox.getValue().multVecMatrix(SbVec3f(0.5f, 0.5f, 0.5f), center);	
	viewBoundingBox.getValue().multVecMatrix(SbVec3f(0.f, 0.f, 0.f), minVec);	
	viewBoundingBox.getValue().multVecMatrix(SbVec3f(1.0f, 1.0f, 1.0f), maxVec);	

	// use a projector to translate the mouse position and rotate the plane using the mouse motion 
	if (mShowPlaneRotationPoint)
	{
		center = mDragStartMouseOnPlane;
	}
	
	SbSphere boxSphere(center, 0.8f * (maxVec - minVec).length());

//	boxSphere.setRadius(boxSphere.getRadius()/1.5);
//	boxSphere.circumscribe(SbBox3f(minVec, maxVec));

	SbSphereSheetProjector sProjector(boxSphere);
	sProjector.setViewVolume(mViewVolume);
	sProjector.setWorkingSpace(mViewTransform);

	SbRotation Prot;

	sProjector.projectAndGetRotation(mLastMousePos, Prot);
	sProjector.projectAndGetRotation(mousePos, Prot);

	rotatePlane(Prot, center);
}

//--------------------------------------------------------------------------
//! translate the plane with the mouse
//--------------------------------------------------------------------------
void SoXipExaminer::mouseTranslatePlane(const SbVec2f &mousePos)
{
	// use a projector to translate the mouse position and translate the plane using the mouse motion 
	SbVec3f center, norm;
	viewBoundingBox.getValue().multVecMatrix(SbVec3f(0.5f, 0.5f, 0.5f), center);	

	SbLineProjector pProjector;
	pProjector.setViewVolume(mViewVolume);
	pProjector.setWorkingSpace(mViewTransform);

	norm = plane.getValue().getNormal();

	SbVec3f z = mViewVolume.zVector();
	float dot = z.dot(norm);

	if (fabs(dot) > 0.95)
	{
		// plane is almost orthogonal to viewer, navigate with up/down movement
		float delta = (mLastMousePos[1] - mousePos[1]) / 2.0f;

		SbVec3f h = mViewVolume.ulf.getValue();
		h -= mViewVolume.llf.getValue();

		z.normalize();
		z *= h.length();;
		z *= delta;
		translatePlane(z);
	}
	else
	{
		// navigate plane to new mouse position in 3-D
		pProjector.setLine(SbLine(center, center + norm));

		SbVec3f mouseVec = pProjector.getVector(mLastMousePos, mousePos);
		translatePlane(mouseVec);
	}
}


void SoXipExaminer::scrollToCursor(SoHandleEventAction *action)
{
	SoRayPickAction pa(mVpRegion);
	pa.setPoint(action->getEvent()->getPosition());

	pa.setRadius(3);
	pa.enableCulling(FALSE);
	pa.apply(action->getNodeAppliedTo());
	const SoPickedPoint *pickedPoint = pa.getPickedPoint();

	if (pickedPoint)
	{
		SbVec3f pt = pickedPoint->getPoint();

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
}


void SoXipExaminer::setInteractive(SbBool on)
{
	SoComplexity *complexityPtr = (SoComplexity*) getAnyPart("complexity", TRUE);
	if (!complexityPtr) 
		return;

	float c = on ? 0.249f : 0.5f;
	if (complexityPtr->value.getValue() != c)
	{
		complexityPtr->value.setValue(c);
	}			
}


