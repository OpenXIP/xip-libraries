/*
 *  COPYRIGHT NOTICE.  Copyright (C) 2007 Siemens Corporate Research, 
 *  Inc. ("caBIG(tm) Participant"). eXtensible Imaging Platform (XIP)
 *  was created with NCI funding and is part of the caBIG(tm) 
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
 */
#define NOMINMAX
#include <xip/inventor/renderer/xipivrenderer.h>
#include <xip/inventor/coregl/SoXipGlowElement.h>
#include <Inventor/elements/SoViewingMatrixElement.h>
#include <Inventor/elements/SoModelMatrixElement.h>
#include <Inventor/elements/SoBBoxModelMatrixElement.h>
#include <Inventor/SbBox.h>
#include <Inventor/elements/SoViewportRegionElement.h>
#include <Inventor/elements/SoGLTextureEnabledElement.h>
#include <Inventor/elements/SoComplexityElement.h>
#include <Inventor/elements/SoViewVolumeElement.h>
#include <Inventor/elements/SoModelMatrixElement.h>
#include <Inventor/actions/SoGetBoundingBoxAction.h>

#include <xip/inventor/core/SbXipImage.h>
#include <xip/inventor/core/SoXipClipPlaneElement.h>
#include <xip/inventor/coregl/SoXipGLSLShaderProgramElement.h>
#include "SoXipPluginSlicer.h"

#include <xip/system/standard.h>
#include <algorithm>

SO_NODE_SOURCE( SoXipPluginSlicer );

#define TEXTURE_UNIT_0 0

/**
 *	Constructor
 */
SoXipPluginSlicer::SoXipPluginSlicer()
{
	SO_NODE_CONSTRUCTOR( SoXipPluginSlicer );

    SO_NODE_ADD_FIELD( numSlicesX, (256) );
    SO_NODE_ADD_FIELD( numSlicesY, (256) );
    SO_NODE_ADD_FIELD( numSlicesZ, (256) );
    SO_NODE_ADD_FIELD( numSlices, (256) );
    SO_NODE_ADD_FIELD( useComplexity, (TRUE) );
    SO_NODE_ADD_FIELD(slicing, (VIEW_ALIGNED));
    SO_NODE_ADD_FIELD(mode, (VRT));    
    SO_NODE_ADD_FIELD(compositing, (BACK_TO_FRONT));    

    SO_NODE_DEFINE_ENUM_VALUE(Mode, MPR);
    SO_NODE_DEFINE_ENUM_VALUE(Mode, MAXIP);
    SO_NODE_DEFINE_ENUM_VALUE(Mode, MINIP);
    SO_NODE_DEFINE_ENUM_VALUE(Mode, VRT);
    SO_NODE_SET_SF_ENUM_TYPE(mode, Mode);

    // Set up static info for enumerated type field
    SO_NODE_DEFINE_ENUM_VALUE(Slicing, VIEW_ALIGNED);
    SO_NODE_DEFINE_ENUM_VALUE(Slicing, OBJECT_ALIGNED);
    SO_NODE_SET_SF_ENUM_TYPE(slicing, Slicing);

    SO_NODE_DEFINE_ENUM_VALUE(Compositing, BACK_TO_FRONT);
    SO_NODE_DEFINE_ENUM_VALUE(Compositing, FRONT_TO_BACK);
    SO_NODE_SET_SF_ENUM_TYPE(compositing, Compositing);
}

/**	
 *	Destructor
 */
SoXipPluginSlicer::~SoXipPluginSlicer()
{

}

/**	
 *	Initializes the class
 */
void SoXipPluginSlicer::initClass()
{
	SO_NODE_INIT_CLASS( SoXipPluginSlicer, SoShape, "Shape" );

	SO_ENABLE(SoGLRenderAction, SoXipGLOWElement );
	SO_ENABLE(SoGLRenderAction, SoXipGLSLShaderProgramElement );
    SO_ENABLE(SoGLRenderAction, SoViewVolumeElement);
    SO_ENABLE(SoGLRenderAction, SoModelMatrixElement);
    SO_ENABLE(SoGLRenderAction, SoXipClipPlaneElement);
    SO_ENABLE(SoGLRenderAction, SoXipRenderModeElement);
}



void SoXipPluginSlicer::computeBBox(SoAction *action, SbBox3f &box,
				    SbVec3f &center)
{
	center.setValue(0.5, 0.5, 0.5);
	box.setBounds(0, 0, 0, 1, 1, 1);
}

void SoXipPluginSlicer::generatePrimitives(SoAction *action)
{
}

/**	
 *	Gets the slicing direction, regarding the camera position & orientation
 */
int SoXipPluginSlicer::getSlicingDirection(SoState *pState, SbVec3f *pViewDir) 
{
	const SbVec3f	zAxis(0.0, 0.0, 1.0);
	SbVec3f         dummyVec;    
	SbRotation	    dummyRot;
	SbVec3f	        vecToCam;	   
	SbRotation	    camRotation;    // the rotation of the camera	
	SbVec3f			finalSliceDir;
	SbVec3f			volTranslation; // the local rotation of the volume
	SbVec3f			volScale;       // the local scaling of the volume 
	SbRotation		volRotation;    // the local rotation of the volume
	
	// get viewing matrix from the OpenInventor state
    SbMatrix	 viewMat  = SoViewingMatrixElement::get(pState);
	//  extract the camera rotation from the viewing matrix
	viewMat.getTransform(dummyVec, camRotation, dummyVec, dummyRot);
	
	// get modeling matrix from the OpenInventor state
    SbMatrix	 modelMat = SoModelMatrixElement::get(pState);
	// extract the local translation, rotation and scaling of the volume from the modeling matrix
	modelMat.getTransform(volTranslation, volRotation, volScale, dummyRot);
	
	// compute the viewing vector pointing to the camera
	camRotation.inverse().multVec(zAxis, vecToCam);
	// compute the normal vector of a viewport aligned slice
	// taking into account the local rotation of the volume
	volRotation.inverse().multVec(vecToCam, finalSliceDir);
	
	// now find the maximum vector component of the slice normal vector
	double x = finalSliceDir[0];
	double y = finalSliceDir[1];
	double z = finalSliceDir[2];
	double X = (x > 0)? x: -x;
	double Y = (y > 0)? y: -y;
	double Z = (z > 0)? z: -z;
	
	int nfinalSliceDir;
	
	if ((Z > Y) && (Z > X)) { 
		// Z is the vector component with the largest absolute value 
		if (z > 0) {   
			nfinalSliceDir = SD_Z_FRONT_TO_BACK;     // negative z-component
		} else {       
			nfinalSliceDir = SD_Z_BACK_TO_FRONT;     // positive z-component
		} // endif (z < 0)
	} else {
		if (Y > X) {
			// Y is the vector component with the largest absolute value 
			if (y < 0) { 
				nfinalSliceDir = SD_Y_BACK_TO_FRONT; // negative y-component
			} else { 
				nfinalSliceDir = SD_Y_FRONT_TO_BACK; // positive y-component
			} // endif (y < 0)

		} else {
			if (x < 0) {
				// X  is the vector component with the largest absolute value 
				nfinalSliceDir = SD_X_BACK_TO_FRONT; // negative x-component
			} else {
				nfinalSliceDir = SD_X_FRONT_TO_BACK; // positive x-component
			} // endif (x < 0)
		} // endif (Y > X)
	} // endif ((Z > Y) && (Z > X))
	
	if (pViewDir != NULL) {
		// return the slicing direction in the return parameter pViewDir
		*pViewDir = finalSliceDir; 
	}

	// return the slice direction
	return nfinalSliceDir;
} /* end of SoVolume::getSlicingDirection(SoState *pState, SbVec3f *pViewDir) */

void SoXipPluginSlicer::volumeRendering(SoState *state)
{
    glEnable( GL_BLEND );
  
    //	Set the appropriate blending function (VRT is order-dependant)
   if (compositing.getValue() == FRONT_TO_BACK)
    {
        glDepthMask(GL_FALSE);
        glBlendFunc(GL_ONE_MINUS_DST_ALPHA,GL_ONE);
    }
    else
        glBlendFunc( GL_ONE, GL_ONE_MINUS_SRC_ALPHA );
    //	Which render mode ?
    switch (mode.getValue())
    {
    case VRT:
        glBlendEquationEXT(GL_FUNC_ADD_EXT);
        break;
    case MAXIP:
        glBlendEquationEXT(GL_MAX_EXT);
        break;
    case MINIP:
        glBlendEquationEXT(GL_MIN_EXT);
        break;
    default:;
    }

    // Check if clip planes are to be used and prepare them
    mNumClipPlanes = 0;
    const SoXipClipPlaneElement *clipPlaneElt = SoXipClipPlaneElement::getInstance(state);
    if (clipPlaneElt && clipPlaneElt->getNum() != 0)
    {
        mNumClipPlanes = std::min(clipPlaneElt->getNum(), MAX_VR_CLIP_PLANES);		
        SbMatrix modelMat = SoModelMatrixElement::get(state);
        modelMat = modelMat.inverse();
        SbMatrix space;
        space.setTransform(SbVec3f(-1.0f, -1.0f, -1.0f), SbRotation::identity(), SbVec3f(2.0f, 2.0f, 2.0f));
        modelMat = modelMat * space;
        // Transform the planes from world space back into [-1,-1,-1:1,1,1] space used by the slicer
        for (int i = 0; i < mNumClipPlanes; ++i)
        {
            mClipPlanes[i] = clipPlaneElt->get(i, 0);
            mClipPlanes[i].transform(modelMat);
        }
    }

    //	Which slicing method ?
    if (slicing.getValue() == VIEW_ALIGNED)
        sliceViewAligned( state );
    else
        sliceObjectAligned(	state );

    //	Reset the blending equation
    if (mode.getValue() != VRT)
        glBlendEquationEXT(GL_FUNC_ADD_EXT);
}


void SoXipPluginSlicer::mprRendering(SoState *state)
{
    // Get corners
    SbVec3f	corners[4];
    SbViewVolume viewVolume = SoViewVolumeElement::get(state);
    float dist = viewVolume.getNearDist() + viewVolume.getDepth() * 0.5f;
    corners[0] = viewVolume.getPlanePoint(dist, SbVec2f(0, 0));
    corners[1] = viewVolume.getPlanePoint(dist, SbVec2f(1, 0));
    corners[2] = viewVolume.getPlanePoint(dist, SbVec2f(1, 1));
    corners[3] = viewVolume.getPlanePoint(dist, SbVec2f(0, 1));

    // Get bounding box span and start from model matrix
    SbMatrix modelMat = SoModelMatrixElement::get(state);
    SbVec3f wSpan, wStart;
    SbRotation dummy;
    modelMat.getTransform(wStart, dummy, wSpan, dummy);

    // Convert the corner points from worldspace to model space
    for (int i = 0; i < 4; ++i)
    {
        corners[i] -= wStart;
        corners[i][0] = (corners[i][0] / wSpan[0]);
        corners[i][1] = (corners[i][1] / wSpan[1]);
        corners[i][2] = (corners[i][2] / wSpan[2]);
    }

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glMatrixMode(GL_TEXTURE);
    glPushMatrix();
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    // Render mpr
    glBegin(GL_QUADS);
    glTexCoord3fv(corners[0].getValue());
    glVertex2f(-1, -1);
    glTexCoord3fv(corners[1].getValue());
    glVertex2f(1, -1);
    glTexCoord3fv(corners[2].getValue());
    glVertex2f(1, 1);
    glTexCoord3fv(corners[3].getValue());
    glVertex2f(-1, 1);
    glEnd();

    glPopMatrix();
    glMatrixMode(GL_TEXTURE);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

/**	
 *	GLRender
 */
void SoXipPluginSlicer::GLRender( SoGLRenderAction* action )
{

	SoState  *state = action->getState();

	if( !state ) return;

    SbBool doTextures = SoGLTextureEnabledElement::get(state);

	glPushAttrib( GL_ENABLE_BIT|GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT );
	if (doTextures) 
	{
		// We use the current texture unit set
	    //glActiveTextureARB(GL_TEXTURE0_ARB);
		glEnable( GL_TEXTURE_3D );
	}

    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE );

    switch(mode.getValue())
    {
    case MPR:
        mprRendering(state);
        break;
    case MAXIP:
    case MINIP:
    case VRT:
        volumeRendering(state);
        break;
    }
	
	//	Back to original state
	glPopAttrib();
}




/**	
 *	Create geometry for view-aligned slicing (ie. 3D texture-based)
 */
void SoXipPluginSlicer::sliceViewAligned(SoState  *state)
{
	int i=0,j=0;
	
	
	// Initialize vertices
	SbVec3f vertices[8];
	vertices[0] = SbVec3f( -1.f,  -1.f,  -1.f); 
	vertices[1] = SbVec3f(  1.f,  -1.f,  -1.f); 
	vertices[2] = SbVec3f(  1.f,   1.f,  -1.f); 
	vertices[3] = SbVec3f( -1.f,   1.f,  -1.f); 
	vertices[4] = SbVec3f(  1.f,   1.f,   1.f); 
	vertices[5] = SbVec3f( -1.f,   1.f,   1.f); 
	vertices[6] = SbVec3f( -1.f,  -1.f,   1.f); 
	vertices[7] = SbVec3f(  1.f,  -1.f,   1.f);
	SbVec3f diag(2.f, 2.f, 2.f);


	SbLine edges[12];
	// initialize the 12 edges
	//                          e0     e1     e2     e3     e4     e5     e6     e7     e8     e9     e10    e11
	const int eindex[12][2] = {{0,1}, {2,3}, {6,7}, {4,5}, {1,2}, {0,3}, {5,6}, {4,7}, {1,7}, {2,4}, {3,5}, {0,6}};
	for (i = 0; i < 12; ++i)
		edges[i]   = SbLine(vertices[eindex[i][0]], vertices[eindex[i][1]]);
	
	
	float fRadius = 0.5 * diag.length();

	SbVec3f vecViewDir;
	(void) getSlicingDirection(state, &vecViewDir);

	SbPlane planeSlice;
	//	set the starting position for the plane
	if (compositing.getValue() == FRONT_TO_BACK)
		planeSlice = SbPlane(vecViewDir, fRadius);
	else
		planeSlice = SbPlane(vecViewDir, -fRadius);

	SbVec3f vecIntersections[12];
	SbVec3f vecIntersection;
	SbVec3f vecIntersectionsSorted[12+MAX_VR_CLIP_PLANES];
	SbVec3f smoothedPoly[12+MAX_VR_CLIP_PLANES];
	bool    bIntersectionUsed[12];
	int     nEdgeCodes[12];


	#define FACE_FRONT  (1)
	#define FACE_BACK   (2)
	#define FACE_RIGHT  (4)
	#define FACE_LEFT   (8)
	#define FACE_BOTTOM (16)
	#define FACE_TOP    (32) 
	//                       edge 0                    edge 1                  edge 2                   edge 3
	const int ecodes[12] = {(FACE_FRONT+FACE_BOTTOM), (FACE_FRONT+FACE_TOP),  (FACE_BACK+FACE_BOTTOM), (FACE_BACK+FACE_TOP), 
	//                       edge 4                    edge 5                  edge 6                   edge 7 
	(FACE_FRONT+FACE_RIGHT ), (FACE_FRONT+FACE_LEFT), (FACE_BACK+FACE_LEFT),   (FACE_BACK+FACE_RIGHT),
	//                       edge 8                    edge 9                  edge 10                  edge 11
	(FACE_RIGHT+FACE_BOTTOM), (FACE_RIGHT+FACE_TOP),  (FACE_TOP+ FACE_LEFT),   (FACE_BOTTOM+FACE_LEFT)};
	

	int nbSlices = numSlices.getValue();

	if (useComplexity.getValue())
	{
		float complexity = SoComplexityElement::get(state);
		// Inventor complexity usually ranges from 0.1 -> 0.5, remap to 0.2 -> 1.0
		nbSlices = 2.f * complexity * nbSlices;
	}

	float fSampleRate = 1.f;
	// calculate the slice distance from the voxel diagonal and the current sampling rate
	float fSliceDistance = diag.length() / nbSlices / fSampleRate;
	// this is the tolerance value for merging two vertices
	if (compositing.getValue() == FRONT_TO_BACK)
		fSliceDistance = - fSliceDistance;
	
	float fTolerance = fSliceDistance / 100.0;

	SbVec3f v;
    SbVec3f offset(1.f, 1.f, 1.f);

    int nSlice,numUsedIntersections,nEdgeCode;
	// for all slices
	for (nSlice = 0; nSlice < nbSlices; ++nSlice)
	{
		int numIntersections = 0;
		for (i = 0; i < 12; ++i) 
		{
			if (planeSlice.intersect(edges[i], vecIntersection))
			{
				if (vecIntersection.length() <= fRadius)
				{
					vecIntersections[numIntersections]  = vecIntersection;
					nEdgeCodes[numIntersections]        = ecodes[i];
					bIntersectionUsed[numIntersections] = false;
					numIntersections++;
				}
			}
		}

		// slice-volume intersection step 2
		// eliminate double vertices
		// -------------------------------------------------
		if (numIntersections > 2) 
		{
			for (i = 0; i < numIntersections - 1; ++i)
			{
				for (j = i + 1; j < numIntersections; ++j)
				{
					if ((vecIntersections[i] - vecIntersections[j]).length() < fTolerance)
					{
						// merge the two intersections
						nEdgeCodes[i] |= nEdgeCodes[j];
						// remove j
						if (j < numIntersections - 1)
						{
							vecIntersections[j] = vecIntersections[numIntersections-1];
							nEdgeCodes[j] = nEdgeCodes[numIntersections-1];
							j--; // vertex j has changed, so examine the vertex j again
						}
						numIntersections--;
					}
				}
			}
		}

		
		if (numIntersections > 2) 
		{
			// slice-volume intersection step 3
			// -------------------------------------------------
			// find the correct sequence
			bIntersectionUsed[0]      = true;
			vecIntersectionsSorted[0] = vecIntersections[0];
			numUsedIntersections      = 1;
			nEdgeCode = nEdgeCodes[0];
			while (numUsedIntersections != numIntersections)
			{
				for (i = 1; i < numIntersections; ++i)
				{
					// the sequence is valid if the edge codes of both points have one bit in common 
					if ((bIntersectionUsed[i] == false) && (nEdgeCodes[i] & nEdgeCode))
					{
						vecIntersectionsSorted[numUsedIntersections] = vecIntersections[i];
						nEdgeCode = nEdgeCodes[i];
						bIntersectionUsed[i] = true;
						numUsedIntersections++;
					}
				}
			}

			// Clip polygon against VRClipPlanes
			if (mNumClipPlanes)
				numIntersections = clipPolygon(vecIntersectionsSorted, numIntersections);
			  
			if (numIntersections > 2)
			{
				// Rescale vertices to 0-1 space
				for (i = 0; i < numIntersections; ++i)
					vecIntersectionsSorted[i] = (vecIntersectionsSorted[i] + offset) * 0.5f;

				
				// Draw the polygon
				glBegin(GL_TRIANGLE_FAN);				  
				for (i = 0; i < numIntersections; ++i)
				{
					
					glTexCoord3fv(vecIntersectionsSorted[i].getValue());
					glVertex3fv(vecIntersectionsSorted[i].getValue());
				}
				glEnd();

				
			}
		}

		// next plane
		planeSlice.offset(fSliceDistance);
	}
}

int	clipPolyPlane(const SbPlane &plane, SbVec3f *inPoints, SbVec3f *outPoints, int numInPoints)
{
	int numOutPoints = 0;
	for (int i = 0; i < numInPoints; ++i)
	{
        int j = i + 1;
        if (j == numInPoints)
            j = 0;
		SbVec3f p1 = inPoints[i];
		SbVec3f p2 = inPoints[j];
		
		int p1In = plane.isInHalfSpace(p1);
		int p2In = plane.isInHalfSpace(p2);

		// Trivial accept, both points in half space
		if (p1In && p2In)
		{
			outPoints[numOutPoints++] = p1;
		}
		// Line between p1 and p2 intersects plane
		else if ((p1In && !p2In) || (!p1In && p2In))
		{	
			SbLine	line(p1, p2);
			SbVec3f inter;
			plane.intersect(line, inter);
			if (p1In)
				outPoints[numOutPoints++] = p1;
			outPoints[numOutPoints++] = inter;
		}
    }
	return numOutPoints;
}
/**	
 *	Clips the passed polygon with SoXipClipPlaneElements present in state
 */
int SoXipPluginSlicer::clipPolygon(SbVec3f *poly, int numPoints)
{
	SbVec3f *p1, *p2, *ptemp;
	p1 = mTmpPoly1;
	p2 = mTmpPoly2;

	int num = clipPolyPlane(mClipPlanes[0], poly, p1, numPoints);
	if (num > 2)
		for (int i = 1; i < mNumClipPlanes; ++i)
		{
			num = clipPolyPlane(mClipPlanes[i], p1, p2, num);
	
			ptemp = p1;
			p1 = p2;
			p2 = ptemp;
			if (num < 3)
				break;
		}
	
	memcpy(poly, p1, num * sizeof(SbVec3f));
	return num;
}

/**	
 *	Create geometry for object-aligned slicing (ie. 2D texture-based)
 */
 void SoXipPluginSlicer::sliceObjectAligned(SoState  *state)
{
	int nSliceDir = getSlicingDirection(state); 

	int i;
    float complexity = SoComplexityElement::get(state);

	if ((nSliceDir == SD_Z_FRONT_TO_BACK) ||
			(nSliceDir == SD_Z_BACK_TO_FRONT))
	{
		float d = 0.f;
		float dInc = 0.f;
        int numSlices_z = numSlicesZ.getValue();
		if (useComplexity.getValue())
			// Inventor complexity usually ranges from 0.1 -> 0.5,
			// remap to 0.2 -> 1.0
			numSlices_z = 2.f * complexity * numSlices_z;

		if (numSlices_z > 1)
			dInc = 1.f/(numSlices_z-1);

		if (nSliceDir == SD_Z_BACK_TO_FRONT)
		{
			d = 1.f;
			dInc = -dInc;
		}
		if (compositing.getValue() == FRONT_TO_BACK)
		{
			d=1.0f-d;
			dInc = -dInc;
		}

		//	Create slices
		glBegin(GL_QUADS);
		for (i=0;i<numSlices_z;i++)
		{
			glTexCoord3f(0.f, 0.f, d);
			glVertex3f  (0.f, 0.f, d);
			glTexCoord3f( 1.f, 0.f, d);
			glVertex3f  ( 1.f, 0.f, d);
			glTexCoord3f( 1.f,  1.f, d);
			glVertex3f  ( 1.f,  1.f, d);
			glTexCoord3f(0.f,  1.f, d);
			glVertex3f  (0.f,  1.f, d);

			//	offset the slice position for the next one
			d = d + dInc;
		}
		glEnd();
	}
	else
	if ((nSliceDir == SD_Y_FRONT_TO_BACK) ||
								 (nSliceDir == SD_Y_BACK_TO_FRONT))
	{
		float d = 0.f;
		float dInc = 0.f;
        int numSlices_y = numSlicesY.getValue();
		if (useComplexity.getValue())
			// Inventor complexity usually ranges from 0.1 -> 0.5, remap to 0.2 -> 1.0
			numSlices_y = 2.f * complexity * numSlices_y;

		if (numSlices_y > 1)
			dInc = 1.f/(numSlices_y-1);

		if (nSliceDir == SD_Y_BACK_TO_FRONT)
		{
			d = 1.f;
			dInc = -dInc;
		}
		if (compositing.getValue() == FRONT_TO_BACK)
		{
			d=1.0f-d;
			dInc = -dInc;
		}

		//	Create slices
		glBegin(GL_QUADS);
		for (i=0;i<numSlices_y;i++)
		{
			glTexCoord3f(0.f, d, 0.f);
			glVertex3f  (0.f, d, 0.f);
			glTexCoord3f( 1.f, d, 0.f);
			glVertex3f  ( 1.f, d, 0.f);
			glTexCoord3f( 1.f, d,  1.f);
			glVertex3f  ( 1.f, d,  1.f);
			glTexCoord3f(0.f, d,  1.f);
			glVertex3f  (0.f, d,  1.f);

			//	offset the slice position for the next one
			d = d + dInc;
		}
		glEnd();
	}
	else
	{
		float d = 0.f;
		float dInc = 0.f;
        int numSlices_x = numSlicesX.getValue();
		if (useComplexity.getValue())
			// Inventor complexity usually ranges from 0.1 -> 0.5, remap to 0.2 -> 1.0
			numSlices_x = 2.f * complexity * numSlices_x;

		if (numSlices_x > 1)
			dInc = 1.f/(numSlices_x-1);

		if (nSliceDir == SD_X_BACK_TO_FRONT)
		{
			d = 1.f;
			dInc = -dInc;
		}
		if (compositing.getValue() == FRONT_TO_BACK)
		{
			d=1.0f-d;
			dInc = -dInc;
		}
		
		//	Create slices
		glBegin(GL_QUADS);
		for (i=0;i<numSlices_x;i++)
		{
			glTexCoord3f(d, 0.f, 0.f);
			glVertex3f  (d, 0.f, 0.f);		
			glTexCoord3f(d,  1.f, 0.f);		
			glVertex3f  (d,  1.f, 0.f);		
			glTexCoord3f(d,  1.f,  1.f);		
			glVertex3f  (d,  1.f,  1.f);		
			glTexCoord3f(d, 0.f,  1.f);		
			glVertex3f  (d, 0.f,  1.f);		
			
			//	offset the slice position for the next one
			d = d + dInc;
		}
		glEnd();
	}
}
