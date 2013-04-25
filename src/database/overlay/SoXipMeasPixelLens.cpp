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

#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoTranslation.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoBaseColor.h>
#include <Inventor/nodes/SoPickStyle.h>
#include <Inventor/actions/SoActions.h>
#include <Inventor/elements/SoGLCoordinateElement.h>
#include <Inventor/elements/SoViewVolumeElement.h>
#include <Inventor/elements/SoViewportRegionElement.h>
#include <Inventor/projectors/SbPlaneProjector.h>
#include <Inventor/events/SoLocation2Event.h>
#include <Inventor/events/SoMouseButtonEvent.h>
#include <Inventor/SoPickedPoint.h>
#include <Inventor/elements/SoBBoxModelMatrixElement.h>
#include <xip/inventor/core/SbXipCoordinateTransform.h>
#include <xip/system/GL/gl.h>
#include "SoXipMeasPixelLens.h"
#include <xip/inventor/overlay/SoXipText2.h>
#include "SoXipDropShadowElement.h"
#include "geomutils.h"

SO_KIT_SOURCE(SoXipMeasPixelLens);


void SoXipMeasPixelLens::initClass()
{
	SO_KIT_INIT_CLASS(SoXipMeasPixelLens, SoBaseKit, "BaseKit");
	SO_ENABLE(SoGLRenderAction, SoXipDropShadowElement);
}


SoXipMeasPixelLens::SoXipMeasPixelLens()
{
	mHasPickedPoint = FALSE;
	mHasPickedPointChanged = TRUE;

	SO_KIT_CONSTRUCTOR(SoXipMeasPixelLens);

	SO_KIT_ADD_CATALOG_ENTRY(separator, SoSeparator, FALSE, this, \0 , FALSE);
	SO_KIT_ADD_CATALOG_ENTRY(pickStyle, SoPickStyle, FALSE, separator, \0, FALSE);
	SO_KIT_ADD_CATALOG_ENTRY(coordinate, SoCoordinate3, FALSE, separator, \0 , FALSE);
	SO_KIT_ADD_CATALOG_ENTRY(pointset, SoPointSet, FALSE, separator, \0 , FALSE);
	SO_KIT_ADD_CATALOG_ENTRY(translation, SoTranslation, FALSE, separator, \0 , FALSE);
	SO_KIT_ADD_CATALOG_ENTRY(text, SoXipText2, FALSE, separator, \0 , FALSE);

	SO_KIT_INIT_INSTANCE();

	SO_NODE_ADD_FIELD(on, (TRUE));
	SO_NODE_ADD_FIELD(image, (0));
	SO_NODE_ADD_FIELD(offset, (0));

	// output
	SO_NODE_ADD_FIELD(position, (SbVec3f(0, 0, 0)) );

	mShadowColor = new SoBaseColor;
	mShadowColor->ref();
	mShadowTranslation = new SoTranslation;
	mShadowTranslation->ref();

	pickStyle.getValue()->set( "style UNPICKABLE" );
}


SoXipMeasPixelLens::~SoXipMeasPixelLens()
{
	mShadowColor->unref();
	mShadowTranslation->unref();
}


void SoXipMeasPixelLens::GLRender(SoGLRenderAction *action)
{
	SoCoordinate3 *coord = (SoCoordinate3*) getAnyPart("coordinate", TRUE);
	if (!coord) return;

	SoXipText2 *text2 = (SoXipText2*) getAnyPart("text", TRUE);
	if (!text2) return;

	if (on.getValue() && image.getValue() && mHasPickedPoint)
	{
		if (mHasPickedPointChanged)
		{
			// need to get voxel value in the GLRender() method since
			// the model matrix element is not set in handleEvent()
			SbMatrix transformMatrix = SoBBoxModelMatrixElement::get(action->getState());
			SbVec3f noTransPt, pickPt = mPickedPoint;
			transformMatrix.inverse().multVecMatrix(pickPt, noTransPt);
			
			float value = 0;
			if (getVoxelValue(noTransPt, value))
			{
				SoTranslation *trans = (SoTranslation*) getAnyPart("translation", TRUE);
				trans->translation.setValue(noTransPt);
				coord->point.setValue(noTransPt);

				char tmp[30];
				SbBool isFloat = FALSE;

				SbXipImage *img = image.getValue()->get();
				if (img)
				{
					if (img->getType() == SbXipImage::FLOAT)
					{
						isFloat = TRUE;
					}
				}

				sprintf(tmp, isFloat ? "  %.3f" : "  %.0f", value + (float) offset.getValue());

				text2->string.setValue(tmp);
				text2->vAlignment.setValue(SoXipText2::BOTTOM);

				mHasPickedPointChanged = FALSE;
			}
			else
			{
				// mouse is outside of volume
				text2->string.setValue("");
			}
		}

		GLboolean isDepthOn = glIsEnabled(GL_DEPTH_TEST);
		glDisable(GL_DEPTH_TEST);

		// push state because we will turn drop shadow for the text off since it is handled here
		action->getState()->push();

		// render shadow first
		if (SoXipDropShadowElement::isOn(action->getState()))
		{
			SbVec2s offset = SoXipDropShadowElement::getPixelOffset(action->getState());
			SbVec3f xPixelVec, yPixelVec;
			getScreenPixelVectors(action, mPickedPoint, xPixelVec, yPixelVec);
			xPixelVec *= offset[0];
			yPixelVec *= offset[1];

			mShadowColor->rgb.setValue(SoXipDropShadowElement::getColor(action->getState()));
			mShadowTranslation->translation.setValue(xPixelVec + yPixelVec);

			// push state to restore default diffuse color after rendering the shadows
			action->getState()->push();
			SoXipDropShadowElement::set(action->getState(), this, FALSE, SbColor(0, 0, 0), 0, SbVec2s(0, 0));

			action->traverse(mShadowColor);
			action->traverse(mShadowTranslation);
			SoBaseKit::GLRender(action);

			action->getState()->pop();
		}

		SoBaseKit::GLRender(action);

		action->getState()->pop();

		if (isDepthOn)
			glEnable(GL_DEPTH_TEST);
	}
	else
	{
		coord->point.setNum(0);
		text2->string.setValue("");

		mHasPickedPoint = FALSE;
	}
}


void SoXipMeasPixelLens::handleEvent(SoHandleEventAction *action)
{
	if (on.getValue() && !action->getGrabber() && image.getValue())
	{
		SoState *state = action->getState();
		const SoEvent *event = action->getEvent();

		if (event->isOfType(SoLocation2Event::getClassTypeId()))		
		{
			// CULLING is on when getting picked point from SoHandleEventAction but IVT has some problem with it
			//const SoPickedPoint *pickedPoint = action->getPickedPoint();

			mHasPickedPoint = FALSE;

			SoRayPickAction pa(action->getViewportRegion());
			pa.setPoint(action->getEvent()->getPosition());
			pa.setRadius(3);
			pa.enableCulling(FALSE);
			pa.apply(action->getNodeAppliedTo());
			const SoPickedPoint *pickedPoint = pa.getPickedPoint();

			if (pickedPoint)
			{
				mPickedPoint = pickedPoint->getPoint();
				mHasPickedPoint = TRUE;
				mHasPickedPointChanged = TRUE;

				position.setValue(mPickedPoint);
			}
			else
			{
				position.setValue(SbVec3f(0, 0, 0));
			}

			startNotify();
		}
	}

	SoBaseKit::handleEvent(action);
}


SbBool SoXipMeasPixelLens::getVoxelValue(const SbVec3f &position, float &value)
{
	SbXipImage *img = image.getValue()->get();
	if (img)
	{
		if (img->getComponents() == 1)
		{
			XipWorldToImageConvert cvt( img->getModelMatrix(), img->getDimStored() );
			
			SbVec3s index;
			if( cvt.getIndexTest( position, index ) )
			{
				int x = index[0];
				int y = index[1];
				int z = index[2];

				const void *ptr = img->refBufferPtr();

				int lineSize = img->getDimAllocated()[0];
				int sliceSize = lineSize * img->getDimAllocated()[1];

				switch (img->getType())
				{
				case SbXipImage::UNSIGNED_BYTE:
					{
						unsigned char *p = (unsigned char *) ptr;
						value = p[sliceSize * z + lineSize * y + x];
					} break;
				case SbXipImage::UNSIGNED_SHORT:
					{
						unsigned short *p = (unsigned short *) ptr;
						value = p[sliceSize * z + lineSize * y + x];
					} break;
				case SbXipImage::FLOAT:
					{
						float *p = (float *) ptr;
						value = p[sliceSize * z + lineSize * y + x];
					} break;
				default:
					img->unrefBufferPtr();
					return FALSE;
				}

				img->unrefBufferPtr();

				return TRUE;
			}
		}
	}

	return FALSE;
}

void SoXipMeasPixelLens::getBoundingBox(SoGetBoundingBoxAction *action)
{
	if (on.getValue())
	{
		SoBaseKit::getBoundingBox(action);
	}
}
