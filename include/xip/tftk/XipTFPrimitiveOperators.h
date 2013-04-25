// -*- Mode: c++; c-indentation-style: stroustrup; -*-

/*
 *  COPYRIGHT NOTICE.  Copyright (C) 2005 Siemens Corporate Research, 
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
 *  
 */




#ifndef XIP_TF_PRIMITIVE_OPERATORS_H
#define XIP_TF_PRIMITIVE_OPERATORS_H

#include <xip/tftk/XipTFDefinition.h>
#include <xip/tftk/BasicOps.h>



/**
  Operator that draws the primitive as quads, this is 1D4V points.

  Primitive Operator (PO), Draw Quads, Clock-Wise (CW), 1D coords

  We might consider an additional processAllPoints that repeats the first
  and last points, indicated in a flag, so special handling can be done
  at the ends - in fact entirely encapsulating glBegin and glEnd as well.
**/

class PODrawQuadsCW1D {
public:
    PODrawQuadsCW1D(float depth, float base)
    {
	    mDepth = depth;
	    mBase = base;
    };

    inline void operator () (int idx, float * coord, float * value,
			     XipTFPrimitive::ProcessFirst)
    {
	    glBegin(GL_QUAD_STRIP);
	    operator () (idx, coord, value);
    };

    inline void operator () (int idx, float * coord, float * value)
    {
        //SoDebugError::postInfo( "PODrawQuadsCW1D", " coord=%f, val=%f", coord[0], value[3] );
	    glColor4fv(value);
        glVertex3f(coord[0], mBase, mDepth);
        glVertex3f(coord[0], value[3], mDepth);
    };

    inline void operator () (int idx, float * coord, float * value,
			     XipTFPrimitive::ProcessLast)
    {
	    operator () (idx, coord, value);
	    glEnd();
    };

    ///. These 2 should never occur!!!!
    inline void operator () (int idx, float * coord, float * value,
			     XipTFPrimitive::ProcessFirstInIsoLevel)
    {
        SoDebugError::postInfo( "PODrawQuadsCW1D", " This should never happen!!! but is needed for compile " );
    }

    // actually processes the first point again as well
    inline void operator () (int idx, float * coord, float * value,
			     XipTFPrimitive::ProcessLastInIsoLevel)
    {
        SoDebugError::postInfo( "PODrawQuadsCW1D", " This should never happen!!! but is needed for compile " );
    }

#if 0
    /* This is an alternative if type-based overloading don't work entirely */
    inline void operator () (int idx, float * coord, float * value, int flags)
    {
	if (flags & XipTFPrimitive::PROCESS_POINT_FIRST)
	{
	    glBegin(GL_QUADS);
	    operator () (idx, coord, value);
	}
	else if (flags & XipTFPrimitive::PROCESS_POINT_LAST)
	{
	    operator () (idx, coord, value);
	    glEnd();
	}
    }
#endif
    inline void adjustDepth(float depthInc) {mDepth += depthInc; };
    inline void resetDepth(float depth) {mDepth = depth; };

    static const int mDim = 1;

protected:
    float mDepth;

    float mBase;
    
};



/**
  Operator that draws the primitive edge as lines, this is 1D4V points.

  Primitive Operator (PO), Draw Lines, 1D coords
**/
class PODrawLines1D {
public:
    PODrawLines1D(float depth, float base)
    {
	    mDepth = depth;
	    mBase = base; //  is this needed TO DO
    }

    inline void operator () (int idx, float * coord, float * value,
			     XipTFPrimitive::ProcessFirst)
    {
	    glBegin(GL_LINE_STRIP);
        glColor4f(value[0], value[1], value[2], 1.0); // glColor4fv(value);
	    glVertex3f(coord[0], mBase, mDepth);
	    operator () (idx, coord, value);
    }

    inline void operator () (int idx, float * coord, float * value)
    {
	    glColor4f(value[0], value[1], value[2], 1.0); // glColor4fv(value);
	    glVertex3f(coord[0], value[3], mDepth);
    }

    inline void operator () (int idx, float * coord, float * value,
			     XipTFPrimitive::ProcessLast)
    {
	    operator () (idx, coord, value);
        glColor4f(value[0], value[1], value[2], 1.0); // glColor4fv(value);
	    glVertex3f(coord[0], mBase, mDepth);
	    glEnd();
    }

    /** 
    *   To process only one point
    **/
    inline void operator () (int idx, float * coord, float * value,
        XipTFPrimitive::ProcessFirstAndLast)
    {
        glBegin(GL_LINE_STRIP);
        glColor4f(value[0], value[1], value[2], 1.0); // glColor4fv(value);
        glVertex3f(coord[0], value[3], mDepth);
        glVertex3f(coord[0], value[3], mDepth);
        glEnd();
    }

    ///. These 2 should never occur!!!!
    inline void operator () (int idx, float * coord, float * value,
			     XipTFPrimitive::ProcessFirstInIsoLevel)
    {
        SoDebugError::postInfo( "PODrawLines1D", " This should never happen!!! but is needed for compile " );
    }

    // actually processes the first point again as well
    inline void operator () (int idx, float * coord, float * value,
			     XipTFPrimitive::ProcessLastInIsoLevel)
    {
        SoDebugError::postInfo( "PODrawLines1D", " This should never happen!!! but is needed for compile " );
    }

#if 0
    inline void operator () (int idx, float * coord, float * value, int flags)
    {
	if (flags & XipTFPrimitive::PROCESS_POINT_FIRST)
	{
	    glBegin(GL_LINE_STRIP);
	    glVertex3f(coord[0], mBase, mDepth);
	    operator () (idx, coord, value);
	}
	else if (flags & XipTFPrimitive::PROCESS_POINT_LAST)
	{
	    operator () (idx, coord, value);
	    glVertex3f(coord[0], mBase, mDepth);
	    glEnd();
	}
    }
#endif
    inline void adjustDepth(float depthInc) {mDepth += depthInc; };
    inline void resetDepth(float depth) {mDepth = depth; };

    static const int mDim = 1;

protected:
    float mDepth; 

    float mBase;
    
};



/**
  Operator that draws the primitives points, this is 1D4V points.

  Primitive Operator (PO), Draw points, 1D coords
**/
class PODrawPoints1D {
public:
    PODrawPoints1D(float depth, float base)
    {
	    mDepth = depth;
	    mBase = base;
    }

    inline void operator () (int idx, float * coord, float * value,
			     XipTFPrimitive::ProcessFirst)
    {
	    glBegin(GL_POINTS);
        glColor4f(value[0], value[1], value[2], 1.0); // glColor4fv(value);
	    glVertex3f(coord[0], mBase, mDepth);
	    operator () (idx, coord, value);
    }

    inline void operator () (int idx, float * coord, float * value)
    {
	    glColor4f(value[0], value[1], value[2], 1.0); // glColor4fv(value);
	    glVertex3f(coord[0], value[3], mDepth);
    }

    inline void operator () (int idx, float * coord, float * value,
			     XipTFPrimitive::ProcessLast)
    {
	    operator () (idx, coord, value);
        glColor4f(value[0], value[1], value[2], 1.0); // glColor4fv(value);
	    glVertex3f(coord[0], mBase, mDepth);
	    glEnd();
    }
    /** 
    *   To process only one point
    **/
    inline void operator () (int idx, float * coord, float * value,
        XipTFPrimitive::ProcessFirstAndLast)
    {
        glBegin(GL_POINTS);
        glColor4f(value[0], value[1], value[2], 1.0); // glColor4fv(value);
        glVertex3f(coord[0], value[3], mDepth);
        glEnd();
    }

    ///. These 2 should never occur!!!!
    inline void operator () (int idx, float * coord, float * value,
			     XipTFPrimitive::ProcessFirstInIsoLevel)
    {
        SoDebugError::postInfo( "PODrawPoints1D", " This should never happen!!! but is needed for compile " );
    }

    // actually processes the first point again as well
    inline void operator () (int idx, float * coord, float * value,
			     XipTFPrimitive::ProcessLastInIsoLevel)
    {
        SoDebugError::postInfo( "PODrawPoints1D", " This should never happen!!! but is needed for compile " );
    }
    
    inline void adjustDepth(float depthInc) {mDepth += depthInc; };
    inline void resetDepth(float depth) {mDepth = depth; };

    static const int mDim = 1;  // applicable dimeonsion

protected:
    float mDepth; 

    float mBase;
    
};




// ------- Operators for drawing white when selected -------

/**
  Operator that draws the selected primitive quads with a different color, this is 1D4V points.

  Primitive Operator (PO), Draw Quads, 1D coords
**/
class PODrawSelectedQuadsCW1D {
public:
    PODrawSelectedQuadsCW1D(float depth, float base, float * color)
    {
        mDepth = depth;
        mBase = base;
        
        if (!color)
            SoDebugError::post("PODrawSelectedQuadsCW1D", "float pointer = NULL" ); // TO DO 
        for (int i=0; i<4; i++)
            mColor[i] = color[i];
    };

    inline void operator () (int idx, float * coord, float * value,
			     XipTFPrimitive::ProcessFirst)
    {
	    glBegin(GL_QUAD_STRIP);
	    operator () (idx, coord, value);
    };

    inline void operator () (int idx, float * coord, float * value)
    {
        glColor4fv(mColor);
        glVertex3f(coord[0], value[3], mDepth); // glVertex3f(coord[0], mBase, mDepth);
        glVertex3f(coord[0], value[3], mDepth);
    };

    inline void operator () (int idx, float * coord, float * value,
			     XipTFPrimitive::ProcessLast)
    {
	    operator () (idx, coord, value);
	    glEnd();
    };

    ///. These 2 should never occur!!!!
    inline void operator () (int idx, float * coord, float * value,
			     XipTFPrimitive::ProcessFirstInIsoLevel)
    {
        SoDebugError::postInfo( "PODrawSelectedQuadsCW1D", " This should never happen!!! but is needed for compile " );
    }

    // actually processes the first point again as well
    inline void operator () (int idx, float * coord, float * value,
			     XipTFPrimitive::ProcessLastInIsoLevel)
    {
        SoDebugError::postInfo( "PODrawSelectedQuadsCW1D", " This should never happen!!! but is needed for compile " );
    }

#if 0
    /* This is an alternative if type-based overloading don't work entirely */
    inline void operator () (int idx, float * coord, float * value, int flags)
    {
	if (flags & XipTFPrimitive::PROCESS_POINT_FIRST)
	{
	    glBegin(GL_QUADS);
	    operator () (idx, coord, value);
	}
	else if (flags & XipTFPrimitive::PROCESS_POINT_LAST)
	{
	    operator () (idx, coord, value);
	    glEnd();
	}
    }
#endif
    
    inline void adjustDepth(float depthInc) {mDepth += depthInc; };
    inline void resetDepth(float depth) {mDepth = depth; };

    static const int mDim = 1;

protected:
    float mDepth; 

    float mBase;
    float mColor[4];
};



/**
  Operator that draws the selected primitive edge as with a different color, this is 1D4V points.

  Primitive Operator (PO), Draw Lines, 1D coords
**/
class PODrawSelectedLines1D {
public:
    PODrawSelectedLines1D(float depth, float base, float * color)
    {
	    mDepth = depth;
        mBase = base; //  is this needed TO DO

        if (!color)
            SoDebugError::post("PODrawSelectedLines1D", "float pointer = NULL" ); // TO DO 
        for (int i=0; i<4; i++)
            mColor[i] = color[i];
    }

    inline void operator () (int idx, float * coord, float * value,
			     XipTFPrimitive::ProcessFirst)
    {
	    glBegin(GL_LINE_STRIP);
        glColor4fv(mColor);
	    glVertex3f(coord[0], value[3], mDepth); //glVertex3f(coord[0], mBase, mDepth);
	    operator () (idx, coord, value);
    }

    inline void operator () (int idx, float * coord, float * value)
    {
        glColor4fv(mColor);
	    glVertex3f(coord[0], value[3], mDepth);
    }

    inline void operator () (int idx, float * coord, float * value,
			     XipTFPrimitive::ProcessLast)
    {
	    operator () (idx, coord, value);
        glColor4fv(mColor);
	    glVertex3f(coord[0], value[3], mDepth); //glVertex3f(coord[0], mBase, mDepth);
	    glEnd();
    }

    /** 
    *   To process only one point
    **/
    inline void operator () (int idx, float * coord, float * value,
        XipTFPrimitive::ProcessFirstAndLast)
    {
        glBegin(GL_LINE_STRIP);
        glColor4fv(mColor);
        glVertex3f(coord[0], value[3], mDepth);
        glVertex3f(coord[0], value[3], mDepth);
        glEnd();
    }

    ///. These 2 should never occur!!!!
    inline void operator () (int idx, float * coord, float * value,
			     XipTFPrimitive::ProcessFirstInIsoLevel)
    {
        SoDebugError::postInfo( "PODrawSelectedLines1D", " This should never happen!!! but is needed for compile " );
    }

    // actually processes the first point again as well
    inline void operator () (int idx, float * coord, float * value,
			     XipTFPrimitive::ProcessLastInIsoLevel)
    {
        SoDebugError::postInfo( "PODrawSelectedLines1D", " This should never happen!!! but is needed for compile " );
    }

#if 0
    inline void operator () (int idx, float * coord, float * value, int flags)
    {
	if (flags & XipTFPrimitive::PROCESS_POINT_FIRST)
	{
	    glBegin(GL_LINE_STRIP);
	    glVertex3f(coord[0], mBase, mDepth);
	    operator () (idx, coord, value);
	}
	else if (flags & XipTFPrimitive::PROCESS_POINT_LAST)
	{
	    operator () (idx, coord, value);
	    glVertex3f(coord[0], mBase, mDepth);
	    glEnd();
	}
    }
#endif

    inline void adjustDepth(float depthInc) {mDepth += depthInc; };
    inline void resetDepth(float depth) {mDepth = depth; };

    static const int mDim = 1;

protected:
    float mDepth; 

    float mBase;
    float mColor[4];
};


/**
  Operator that draws the selected primitive points with a different color, this is 1D4V points.

  Primitive Operator (PO), Draw Points, 1D coords
**/
class PODrawSelectedPoints1D {
public:
    PODrawSelectedPoints1D(float depth, float base, float* color)
    {
	    mDepth = depth;
	    mBase = base;
        if (!color)
            SoDebugError::post("PODrawSelectedPoints1D", "float pointer = NULL" ); // TO DO 
        for (int i=0; i<4; i++)
            mColor[i] = color[i];
    }

    inline void operator () (int idx, float * coord, float * value,
			     XipTFPrimitive::ProcessFirst)
    {
	    glBegin(GL_POINTS);
        glColor4fv(mColor);
	    glVertex3f(coord[0], value[3], mDepth); // glVertex3f(coord[0], mBase, mDepth);
	    operator () (idx, coord, value);
    }

    inline void operator () (int idx, float * coord, float * value)
    {
        glColor4fv(mColor);
	    glVertex3f(coord[0], value[3], mDepth);
    }

    inline void operator () (int idx, float * coord, float * value,
			     XipTFPrimitive::ProcessLast)
    {
	    operator () (idx, coord, value);
        glColor4fv(mColor);
	    glVertex3f(coord[0], value[3], mDepth); // glVertex3f(coord[0], mBase, mDepth);
	    glEnd();
    }
    /** 
    *   To process only one point
    **/
    inline void operator () (int idx, float * coord, float * value,
        XipTFPrimitive::ProcessFirstAndLast)
    {
        glBegin(GL_POINTS);
        glColor4fv(mColor);
        glVertex3f(coord[0], value[3], mDepth);
        glEnd();
    }
        
    ///. These 2 should never occur!!!!
    inline void operator () (int idx, float * coord, float * value,
			     XipTFPrimitive::ProcessFirstInIsoLevel)
    {
        SoDebugError::postInfo( "PODrawSelectedPoints1D", " This should never happen!!! but is needed for compile " );
    }

    // actually processes the first point again as well
    inline void operator () (int idx, float * coord, float * value,
			     XipTFPrimitive::ProcessLastInIsoLevel)
    {
        SoDebugError::postInfo( "PODrawSelectedPoints1D", " This should never happen!!! but is needed for compile " );
    }

    inline void adjustDepth(float depthInc) {mDepth += depthInc; };
    inline void resetDepth(float depth) {mDepth = depth; };

    static const int mDim = 1;  // applicable dimeonsion

protected:
    float mDepth; 

    float mBase;
    float mColor[4];    
};
















template <class PointOperator>
class PrimitiveRenderingOperator
{
public:    
    inline PrimitiveRenderingOperator(float depth, 
        float base, float depthInc) : mPointOp(depth, base) 
    { 
        mDepthInc = depthInc; 
    }
    inline PrimitiveRenderingOperator(float depth, 
        float depthInc) : mPointOp(depth) 
    { 
        mDepthInc = depthInc; 
    }

    inline void operator () (int idx, XipTFPrimitive * prim) 
    { 
        prim->processAllPoints(mPointOp);        
        mPointOp.adjustDepth(mDepthInc);    
    }

    inline int getDim() { return mPointOp.mDim; }
    inline void reset() {mPointOp.resetDepth(0.0); }

private:    
    PointOperator mPointOp;    
    float mDepthInc;
};
 




// ------ LUT GENERATION OPERATORS -----

class POAdd2LUT1D {
public:
    POAdd2LUT1D(float* image, int imageSize)
    {
	    mImage = image;
	    mImageSize = imageSize;
        mStepSize = 1.f/imageSize;
    }

    inline void operator () (int idx, float * coord, float * value,
			     XipTFPrimitive::ProcessFirst)
    {        
        mPrevPointCoord = coord;
        mPrevPointValue = value;
        mCurrentCell = floor(mPrevPointCoord[0]*mImageSize);
    }

    inline void operator () (int idx, float * coord, float * value)
    {
        
        if (mPrevPointCoord[0] < coord[0])
        {
            float iCoord = (((float)mCurrentCell)/mImageSize) + (mStepSize/2.f);  // interpolation Coordinate
            int numCalcs = 0;

            float oldValue[4];
            float newValue[4];

            while(iCoord < coord[0] && numCalcs < 10000 )
            {

                for (int i=0; i<4; i++)
                {
                    oldValue[i] = mImage[4*mCurrentCell + i];
                    // Linear interpolation
                    newValue[i] = ((coord[0] - iCoord) * mPrevPointValue[i] 
                    + (iCoord - mPrevPointCoord[0]) * value[i]) / (coord[0] - mPrevPointCoord[0]);
                }

                for (int i=0; i<3; i++)
                {
                    // blending of the colors
                    mImage[4*mCurrentCell + i] = newValue[3]*newValue[i] + 
                        (1.f-newValue[3])*oldValue[i]; // *oldValue[3];
                } 

                // calculate new alpha
                mImage[4*mCurrentCell + 3] = clamp(newValue[3] + (1.f-newValue[3])*oldValue[3], 0.f, 1.f);

                iCoord += mStepSize;

                mCurrentCell++;
                numCalcs++;
            }
        }
        mPrevPointCoord = coord;
        mPrevPointValue = value;
    }

    inline void operator () (int idx, float * coord, float * value,
			     XipTFPrimitive::ProcessLast)
    {
	    operator () (idx, coord, value);       
    }

    ///. These 2 should never occur!!!!
    inline void operator () (int idx, float * coord, float * value,
			     XipTFPrimitive::ProcessFirstInIsoLevel)
    {
        SoDebugError::postInfo( "POAdd2LUT1D", " This should never happen!!! but is needed for compile " );
    }

    // actually processes the first point again as well
    inline void operator () (int idx, float * coord, float * value,
			     XipTFPrimitive::ProcessLastInIsoLevel)
    {
        SoDebugError::postInfo( "POAdd2LUT1D", " This should never happen!!! but is needed for compile " );
    }


    static const int mDim = 1;  // applicable dimeonsion

protected:

    float* mImage;
    int mImageSize;
    float mStepSize;
    int mCurrentCell;
    float* mPrevPointCoord;
    float* mPrevPointValue;
};


template <class PointOperator>
class TextureGenerationOperator
{
public:    
    inline TextureGenerationOperator(float* image, int imageSize) 
        : mPointOp(image, imageSize) 
    { 
        // 
    }

    inline void operator () (int idx, XipTFPrimitive * prim) 
    { 
  //      SoDebugError::postInfo( "TextureGenerationOperator", "processallpoints" ); 
        prim->processAllPoints(mPointOp);        
    }

    inline void reset() {  }
    inline int getDim() { return mPointOp.mDim; }

private:    
    PointOperator mPointOp;    
};







// ---------------------------------------------
// ---------------- 2D OPERATORS ---------------
// ---------------------------------------------

/**
  Operator that draws the primitive as quads, this is 2D4V points.

  Primitive Operator (PO), Draw Quads, Clock-Wise (CW), 2D coords

**/

class PODrawQuadsCW2D {
public:
    PODrawQuadsCW2D(float depth)
    {
        mDepth = depth;
        mFirstPointInIsoCoord = NULL;
        mFirstPointInIsoValue = NULL;
    };

    inline void operator () (int idx, float * coord, float * value,
			     XipTFPrimitive::ProcessFirst)
    {
	    glBegin(GL_QUADS);
	    operator () (idx, coord, value);
    };

    inline void operator () (int idx, float * coord, float * value)
    {
        //SoDebugError::postInfo( "PODrawQuadsCW1D", " coord=%f, val=%f", coord[0], value[3] );
	    //glColor4fv(value);
        glColor4fv(value);
        glVertex3f(coord[0], coord[1], mDepth);
//        glVertex3f(coord[0], coord[1], mDepth);
    };

    inline void operator () (int idx, float * coord, float * value,
			     XipTFPrimitive::ProcessLast)
    {
	    operator () (idx, coord, value);

	    glEnd();
    };

    inline void operator () (int idx, float * coord, float * value,
        XipTFPrimitive::ProcessFirstInIsoLevel)
    {
        mFirstPointInIsoCoord = coord;
        mFirstPointInIsoValue = value;

        glBegin(GL_QUADS);
        operator () (idx, coord, value);
    }

    // actually processes the first point again as well
    inline void operator () (int idx, float * coord, float * value,
        XipTFPrimitive::ProcessLastInIsoLevel)
    {
        operator () (idx, coord, value);
        operator () (idx, mFirstPointInIsoCoord, mFirstPointInIsoValue);
        glEnd();
    }
    
    inline void adjustDepth(float depthInc) {mDepth += depthInc; };
    inline void resetDepth(float depth) {mDepth = depth; };

    static const int mDim = 2;

protected:
    float mDepth; 
    float * mFirstPointInIsoCoord;
    float * mFirstPointInIsoValue;
   
};



/**
  Operator that draws the primitive edge as lines, this is 2D4V points.

  Primitive Operator (PO), Draw Isolevel Lines, 2D coords
**/
class PODrawIsoLevelLines2D {
public:
    PODrawIsoLevelLines2D(float depth)
    {
	    mDepth = depth;
        mFirstPointInIsoCoord = NULL;
        mFirstPointInIsoValue = NULL;
    }

    inline void operator () (int idx, float * coord, float * value,
			     XipTFPrimitive::ProcessFirst)
    {
	    glBegin(GL_LINE_STRIP);
        glColor4f(value[0], value[1], value[2], 1.0); // glColor4fv(value);
	    glVertex3f(coord[0], coord[1], mDepth);
	    operator () (idx, coord, value);
    }

    inline void operator () (int idx, float * coord, float * value)
    {
	    glColor4f(value[0], value[1], value[2], 1.0); // glColor4fv(value);
	    glVertex3f(coord[0], coord[1], mDepth);
    }

    inline void operator () (int idx, float * coord, float * value,
			     XipTFPrimitive::ProcessLast)
    {
	    operator () (idx, coord, value);
        glColor4f(value[0], value[1], value[2], 1.0); // glColor4fv(value);
	    glVertex3f(coord[0], coord[1], mDepth);
	    glEnd();
    }

    inline void operator () (int idx, float * coord, float * value,
			     XipTFPrimitive::ProcessFirstInIsoLevel)
    {
        mFirstPointInIsoCoord = coord;
        mFirstPointInIsoValue = value;

	    glBegin(GL_LINE_STRIP);
	    operator () (idx, coord, value);
    }

    // actually processes the first point again as well
    inline void operator () (int idx, float * coord, float * value,
			     XipTFPrimitive::ProcessLastInIsoLevel)
    {
        operator () (idx, coord, value);
	    operator () (idx, mFirstPointInIsoCoord, mFirstPointInIsoValue);
	    glEnd();
    }


    /** 
    *   To process only one point
    **/
    inline void operator () (int idx, float * coord, float * value,
        XipTFPrimitive::ProcessFirstAndLast)
    {
        glBegin(GL_LINE_STRIP);
        glColor4f(value[0], value[1], value[2], 1.0); // glColor4fv(value);
        glVertex3f(coord[0], coord[1], mDepth);
        glVertex3f(coord[0], coord[1], mDepth);
        glEnd();
    }

    inline void adjustDepth(float depthInc) {mDepth += depthInc; };
    inline void resetDepth(float depth) {mDepth = depth; };
    static const int mDim = 2;

protected:
    float mDepth; 
    float * mFirstPointInIsoCoord;
    float * mFirstPointInIsoValue;

};



/**
  Operator that draws the primitives points, this is 2D4V points.

  Primitive Operator (PO), Draw points, 2D coords
**/
class PODrawPoints2D {
public:
    PODrawPoints2D(float depth)
    {
	    mDepth = depth;
    }

    inline void operator () (int idx, float * coord, float * value,
			     XipTFPrimitive::ProcessFirst)
    {
	    glBegin(GL_POINTS);
        glColor4fv(value);
	    glVertex3f(coord[0], coord[1], mDepth);
	    operator () (idx, coord, value);
    }

    inline void operator () (int idx, float * coord, float * value)
    {
	    glColor4f(value[0], value[1], value[2], 1.0); // glColor4fv(value);
	    glVertex3f(coord[0], coord[1], mDepth);
    }

    inline void operator () (int idx, float * coord, float * value,
			     XipTFPrimitive::ProcessLast)
    {
	    operator () (idx, coord, value);
        glColor4fv(value);
	    glVertex3f(coord[0], coord[1], mDepth);
	    glEnd();
    }
    /** 
    *   To process only one point
    **/
    inline void operator () (int idx, float * coord, float * value,
        XipTFPrimitive::ProcessFirstAndLast)
    {
        glBegin(GL_POINTS);
        glColor4fv(value);
        glVertex3f(coord[0], coord[1], mDepth);
        glEnd();
    }

    inline void adjustDepth(float depthInc) {mDepth += depthInc; };
    inline void resetDepth(float depth) {mDepth = depth; };
    static const int mDim = 2;  // applicable dimeonsion

protected:
    float mDepth; 

    
};




#endif // XIP_TF_PRIMITIVE_OPERATORS_H
