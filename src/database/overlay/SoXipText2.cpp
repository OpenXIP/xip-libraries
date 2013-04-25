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

#include <Inventor/errors/SoErrors.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/actions/SoHandleEventAction.h>
#include <Inventor/actions/SoGetBoundingBoxAction.h>
#include <Inventor/elements/SoCacheElement.h>
#include <Inventor/elements/SoProjectionMatrixElement.h>
#include <Inventor/elements/SoViewingMatrixElement.h>
#include <Inventor/elements/SoFontNameElement.h>
#include <Inventor/elements/SoFontSizeElement.h>
#include <Inventor/elements/SoViewVolumeElement.h>
#include <Inventor/elements/SoModelMatrixElement.h>
#include <Inventor/elements/SoViewportRegionElement.h>
#include <Inventor/projectors/SbPlaneProjector.h>
#include <Inventor/sensors/SoFieldSensor.h>
#include <Inventor/SoPrimitiveVertex.h>
#include <FTLibrary.h>
#include <FTGLBitmapFont.h>
#include <FTGLPixmapFont.h>
#include <FTGLPolygonFont.h>
#include <FTGLTextureFont.h>
#include "SoXipDropShadowElement.h"
#include <xip/inventor/overlay/SoXipText2.h>
#include "fontutils.h"

#ifndef MAX_PATH
# define MAX_PATH 260
#endif

SO_NODE_SOURCE( SoXipText2 );

SoXipText2::SoXipText2()
{
	SO_NODE_CONSTRUCTOR( SoXipText2 );

	SO_NODE_DEFINE_ENUM_VALUE( justificationType, LEFT );
	SO_NODE_DEFINE_ENUM_VALUE( justificationType, RIGHT );
	SO_NODE_DEFINE_ENUM_VALUE( justificationType, CENTER );
	SO_NODE_SET_SF_ENUM_TYPE( justification, justificationType );

	SO_NODE_DEFINE_ENUM_VALUE( alignmentType, BOTTOM );
   	SO_NODE_DEFINE_ENUM_VALUE( alignmentType, TOP );
	SO_NODE_DEFINE_ENUM_VALUE( alignmentType, CENTER );
	SO_NODE_SET_SF_ENUM_TYPE( vAlignment, alignmentType );   

	SO_NODE_ADD_FIELD(        string, ("one test") );
	SO_NODE_ADD_FIELD( justification,       (LEFT) );
	SO_NODE_ADD_FIELD(    vAlignment,        (TOP) );
	
	mFont				= 0;
	mCurrentFontType	= -1;
	mCurrentString		= NULL;

	mStringSensor = new SoFieldSensor( stringSensorCB, this );
	mStringSensor->setPriority(0);
	mStringSensor->attach( &string );
}

SoXipText2::~SoXipText2()
{
	deleteFont();

	if( mStringSensor )
	{
		delete mStringSensor;
		mStringSensor = 0;
	}
}

void SoXipText2::initClass()
{
	SO_NODE_INIT_CLASS( SoXipText2, SoShape, "SoShape" );

	SO_ENABLE(SoGLRenderAction, SoXipDropShadowElement);
}

void 
SoXipText2::stringSensorCB( void* userData, SoSensor* )
{
	((SoXipText2 *) userData)->onStringChange();
}

void
SoXipText2::onStringChange()
{

}

SbBool SoXipText2::createFont(const SbName &fontName, SoXipFontTypeElement::FontType type, int fontSize)
{
	char fontFile[MAX_PATH];
	char fontDisp[MAX_PATH];

	if (GetFontFile(fontName.getString(), fontDisp, MAX_PATH, fontFile, MAX_PATH))
	{
		deleteFont();

		switch ( type )
		{
		case ( SoXipFontTypeElement::BITMAP ) :
			mFont = new FTGLBitmapFont(fontFile);
			break;
		case ( SoXipFontTypeElement::PIXMAP ) :
			mFont = new FTGLPixmapFont(fontFile);
			break;
		case ( SoXipFontTypeElement::TEXTURE ) :
			mFont = new FTGLTextureFont(fontFile);
			break;
		}

		if (!mFont)
			return FALSE;

		FT_Error error = mFont->Error();
		if ( error )
		{
			deleteFont();
			return FALSE;
		}

		mFont->UseDisplayList(false);
		mFont->CharMap(ft_encoding_unicode);
		mFont->FaceSize(fontSize);

		mCurrentFontName = fontName;
		mCurrentFontType = type;
	}
	else
	{
		return FALSE;
	}

	return TRUE;
}


void SoXipText2::deleteFont()
{
	if (mFont)
	{
		delete mFont;
		mFont = 0;
		mCurrentFontName = SbName("");
	}
}


void SoXipText2::computeJustification(SoGLRenderAction *action, SbVec3f &width, SbVec3f &height) 
{
	// To compute correct offset in world space we project width of text onto a plane parallel
	// to the near plane of the camera that goes through the current translation of the model matrix.
	SoState *state = action->getState();
	SbPlaneProjector planeProj(FALSE);
	SbViewVolume viewVolume = SoViewVolumeElement::get(state);
	SbViewportRegion viewport = SoViewportRegionElement::get(state);
	SbMatrix modelMatrix = SoModelMatrixElement::get(state);

	SbVec3f trans, scale;
	SbRotation rot, scaleOrient;
	modelMatrix.getTransform(trans, rot, scale, scaleOrient);

	planeProj.setViewVolume(viewVolume);
	planeProj.setPlane(SbPlane(viewVolume.getPlane(0.f).getNormal(), trans));

	float pixelWidth = 1.f / (float) viewport.getViewportSizePixels()[0];
	float pixelHeight = 1.f / (float) viewport.getViewportSizePixels()[1];

	SbVec3f p1 = planeProj.project(SbVec2f(0, 0));
	SbVec3f p2 = planeProj.project(SbVec2f(pixelWidth, 0));
	width = (p2 - p1);

	p2 = planeProj.project(SbVec2f(0, pixelHeight));
	height = (p2 - p1);
}

void
SoXipText2::computeBBox(SoAction *action, SbBox3f &box, SbVec3f &center)
{
	if (mFont)
	{
		box = mBBox;
		center.setValue(0.0, 0.0, 0.0);
	}
}

void
SoXipText2::generatePrimitives(SoAction *action)
{
	SoPrimitiveVertex pv;

	beginShape(action, TRIANGLE_STRIP);
	pv.setPoint(SbVec3f(mBBox.getMin()[0], mBBox.getMin()[1], mBBox.getMin()[2]));
	shapeVertex(&pv);
	pv.setPoint(SbVec3f(mBBox.getMin()[0], mBBox.getMax()[1], mBBox.getMin()[2]));
	shapeVertex(&pv);
	pv.setPoint(SbVec3f(mBBox.getMax()[0], mBBox.getMax()[1], mBBox.getMin()[2]));
	shapeVertex(&pv);
	pv.setPoint(SbVec3f(mBBox.getMin()[0], mBBox.getMin()[1], mBBox.getMin()[2]));
	shapeVertex(&pv);
	pv.setPoint(SbVec3f(mBBox.getMax()[0], mBBox.getMax()[1], mBBox.getMin()[2]));
	shapeVertex(&pv);
	pv.setPoint(SbVec3f(mBBox.getMax()[0], mBBox.getMin()[1], mBBox.getMin()[2]));
	shapeVertex(&pv);
	endShape();
}

////////////////////////////////////////////////////////////////////////
//
// /!\ Borrowed from SGI SoText2 => license issues
//
//		@author Germain
//
// Description:
//    Static helper routine; given 2D pixel coordinates, a
//    transformation matrix to object space, and a viewportRegion,
//    return the object-space point (assuming the 2D pixel is at z
//    coordinate 0).
//
// Use: internal, static

static SbVec3f
toObjectSpace(const SbVec3f &pixel, const SbMatrix &matrix,
	      const SbViewportRegion &vpr)
//
////////////////////////////////////////////////////////////////////////
{
    // Viewport transformation, to normalized device coordinates:
    SbVec2s vpSize = vpr.getViewportSizePixels();
    SbVec3f ndc;
    ndc[0] = pixel[0]*2.0/vpSize[0] - 1.0;
    ndc[1] = pixel[1]*2.0/vpSize[1] - 1.0;
    ndc[2] = pixel[2];

    SbVec3f result;
    matrix.multVecMatrix(ndc, result);

    return result;
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Static helper routine; given a vector in object space, a
//    transformation matrix to screen (normalized-device coordinate)
//    space, and a viewportRegion, returns the 2D pixel coordinates of
//    the vector (relative to the origin of the viewport).  This
//    actually returns a 3D vector; the z value is just the NDC z value.
//
// Use: internal, static
static SbVec3f
fromObjectSpace(const SbVec3f &vector, const SbMatrix &matrix,
		const SbViewportRegion &vpr)
//
////////////////////////////////////////////////////////////////////////
{
    // First, transform to NDC (-1 to 1 in viewport)
    SbVec3f ndc;
    matrix.multVecMatrix(vector, ndc);

    // And do the viewport transformation:
    SbVec2s vpSize = vpr.getViewportSizePixels();
    SbVec3f result;
    result[0] = (ndc[0]+1.0)*vpSize[0]/2.0;
    result[1] = (ndc[1]+1.0)*vpSize[1]/2.0;
    // Leave the z coordinate alone
    result[2] = ndc[2];

    return result;
}

void
SoXipText2::GLRender(SoGLRenderAction *action)
{
	SoState* state = action->getState();

	float fontSize = SoFontSizeElement::get(state);
	SbName fontName = SoFontNameElement::get(state);
	SoXipFontTypeElement::FontType fontType = SoXipFontTypeElement::get(state);

#ifdef WIN32
	if ((fontName == "Helvetica") || (fontName == "defaultFont"))
	{
		fontName = "Arial";
	}
	else if (fontName == "Utopia-Regular")
	{
		fontName = "Times New Roman";
	}
#else
	if (fontName == "defaultFont")
		fontName = "Helvetica";
#endif

	if ((fontName != mCurrentFontName) || (fontType != mCurrentFontType))
	{
		// need to recreate font
		deleteFont();
	}

	if (!mFont)
	{
		if (!createFont(fontName, fontType, fontSize))
		{
			SoError::post("Font '%s' could not be created.", fontName.getString());
			return;
		}
		SoGetBoundingBoxAction getbbaction(action->getViewportRegion());
		getbbaction.apply(this); 
	}

	if (mFont->FaceSize() != fontSize)
		mFont->FaceSize(fontSize);


	SbBool hasShadow = SoXipDropShadowElement::isOn(state);

	GLboolean depthMask = TRUE;
	glGetBooleanv(GL_DEPTH_WRITEMASK, &depthMask);

	for (int shadow = hasShadow; shadow >= 0; shadow--)
	{
		// set text color
		SbColor textColor = SoLazyElement::getDefaultDiffuse();
		SoLazyElement *lazyElem = SoLazyElement::getInstance( state );
		if (lazyElem->getNumDiffuse())
		{
			textColor = lazyElem->getDiffuse( state, 0 );
		}

		SbVec2s offset(0, 0);

		if (shadow)
		{
			textColor = SoXipDropShadowElement::getColor(state);
			offset = SoXipDropShadowElement::getPixelOffset(state);

			// turn off writing into depth buffer for shadows to avoid depth fighting
			glDepthMask( FALSE );
		}

		glColor3f(textColor[0], textColor[1], textColor[2]);


		// enable texture only if necessary
		glPushAttrib(GL_ENABLE_BIT | GL_DEPTH_BUFFER_BIT);
		glDisable(GL_LIGHTING);

		glPushMatrix();

		if (fontType == SoXipFontTypeElement::PIXMAP)
		{
			glDisable( GL_DEPTH_TEST );
		}

		char str[1024];

		if (!mCurrentString || ( 0 != strcmp(mCurrentString, string.getValue().getString())))
		{
			mCurrentString = string.getValue().getString();
			touch();
		}

		const char *current = mCurrentString;

		SbVec3f lineFeed = SbVec3f(0, 0, 0);
		SbVec3f w, h, trans(0, 0, 0);

		// compute justification
		computeJustification(action, w, h);
		mBBox.makeEmpty();

		// if vertical alignment is CENTER
		// compute the number of lines in the text
		if (vAlignment.getValue() == CENTER)
		{
			int n = 0;	// number of white space in a string
			const char* textStr = current;
			const char* pos = 0;

			int len = strlen(current);

			while ( ((textStr - current) < len) && ((pos = strchr(textStr, '\n')) != NULL) )
			{
				textStr = pos + 1;
				n++;
			}

			// compute the initial vertical offset
			lineFeed += fontSize * ((n + 1) / 2) * h;
		}

		if (fontType == SoXipFontTypeElement::TEXTURE) 
		{
			glEnable(GL_TEXTURE_2D);
			glEnable(GL_BLEND);

			// adjust camera for textured text
			SbViewportRegion viewport = SoViewportRegionElement::get(state);
			float halfWidth  = (float) viewport.getViewportSizePixels()[0] / 2.f;
			float halfHeight = (float) viewport.getViewportSizePixels()[1] / 2.f;
			float tmp1 = (float) viewport.getViewportSizePixels()[0] * w.length();
			float tmp2 = (float) viewport.getViewportSizePixels()[1] * h.length();
			w = SbVec3f(1,0,0);
			h = SbVec3f(0,1,0);

			gluOrtho2D(-halfWidth, halfWidth, -halfHeight, halfHeight);
			glScalef(tmp1 / 2.f, tmp2 / 2.f, 1);
		}

		SbMatrix modelMatrix = SoModelMatrixElement::get(state);
		SbVec3f translation, scaleFactor;
		SbRotation rotation, scaleOrientation;
		modelMatrix.getTransform(translation, rotation, scaleFactor, scaleOrientation);

		while (current)
		{
			const char *nl = strchr(current, '\n');

			int len = nl ? (nl - current) : strlen(current);
			if (len > 1023) len = 1023;

			strncpy(str, current, len);
			str[len] = '\0';
			current = nl ? current + len + 1 : 0;

			// justify
			glPushMatrix();
			trans = lineFeed;

			// query size of text in pixels
			float	x[2], y[2], z[2];
			mFont->BBox(str, x[0], y[0], z[0], x[1], y[1], z[1]);

			switch (justification.getValue())
			{
			case CENTER:	trans -= (x[1] * w) / 2.f; break;
			case RIGHT:		trans -= (x[1] * w); break;
			}

			switch (vAlignment.getValue())
			{
				case TOP : trans -= (y[1] * h);	break;
				case CENTER: trans -= (y[1] * h) / 2.f; break;
			}

			trans += offset[0] * w;
			trans += offset[1] * h;

			glScalef(1.f / scaleFactor[0], 1.f / scaleFactor[1], 1.f / scaleFactor[2]);
			glTranslatef(trans[0], trans[1], trans[2]);

			// render text
			glRasterPos3d(0, 0, 0);
			mFont->Render(str);

			SbMatrix objToScreen;
			objToScreen = SoProjectionMatrixElement::get(state);
			objToScreen =
			objToScreen.multLeft(SoViewingMatrixElement::get(state));
			objToScreen =
			objToScreen.multLeft(SoModelMatrixElement::get(state));

			SbMatrix screenToObj = objToScreen.inverse();
			SbViewportRegion vpr = SoViewportRegionElement::get(state);
			SbVec3f screenOrigin =
			fromObjectSpace(SbVec3f(0,0,0), objToScreen, vpr);
			SbVec3f objectPointMin, objectPointMax, temp;

			float min[3], max[3];
			mFont->BBox(str,
						min[0], min[1], min[2], max[0], max[1], max[2]);

			temp.setValue(min[0], min[1], screenOrigin[2]);
			objectPointMin = toObjectSpace(temp, screenToObj, vpr);
			mBBox.extendBy(objectPointMin - objectPointMin + trans);

			temp.setValue(max[0], max[1], screenOrigin[2]);
			objectPointMax = toObjectSpace(temp, screenToObj, vpr);
			mBBox.extendBy(objectPointMax - objectPointMin + trans);

			glPopMatrix();

			switch (vAlignment.getValue())
			{
				case TOP: 
				case CENTER:
					lineFeed -= fontSize * h; 
					break;
				case BOTTOM:
					lineFeed += fontSize * h;
					break;
			}
		}

		// restore matrices
		glPopMatrix();

		glPopAttrib();
		glDepthMask( depthMask );
	}
}