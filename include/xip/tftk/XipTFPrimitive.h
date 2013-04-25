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

#ifndef  XIP_TF_PRIMITIVE_H
#define  XIP_TF_PRIMITIVE_H

#include <windows.h>
#include <gl/GL.h>
//#include <GL/glext.h>
#include <xip/tftk/XipTFGlobals.h>
#include <xip/tftk/XipTFExceptions.h>


// TO DO remove when we do not need any more debug text in XIP
#include <Inventor/errors/SoDebugError.h>
#include <Inventor/actions/SoGLRenderAction.h>


/*
  XIP Transfer Function Toolkit (XIP TFTK)

  

*/


/*
  xip/tftk/XipTFPrimitive

  The data stored in a primitive is considered to be a 2D array of
  floats, allocated as basic 1D float array.  The stride between rows
  are defined by mStride and the offset to the point location
  (position, coordinates) is determined by mPointOffset.  The offset
  to the values for each point is determined by mValueOffset.

  The primitive contains mNumPoints Points (coordinates and values)

  A Point consists of a Coordinate and a Value, possibly of one or
  dimensions as in nDmV - n-dimensional m-variate points.  The
  Coordinate is always located at offset 0 and the Value is preferably
  located immediately after the coordinates. A packed representation
  of the data have mStride = mCoordDim + mValueDim, but padding/extra
  spacing is allowed.

  mData is a pointer to float data and mDataSize is the number of
  floats in the data, not the number of points.  The following must
  be true at all times: mNumPoints * mStride <= mDataSize.


*/



 

// The basic structure for all the primitives

class XipTFPrimitive {
    friend class XipTFDefinition;    
    
public:
    XipTFPrimitive( bool& created, XipTFPrimitiveShape shape, int numPoints, int coorDim, 
                    int valueDim, int stride, int valueOffset, int alphaValueOffset,
                    XipTFPrimitiveType type = XIP_TF_PRIMITIVE_TYPE_SCALAR_COLORALPHA,
                    int numIsoLevels = 0, int numPointsInIsoLevel = 0);
    ~XipTFPrimitive();

    enum ProcessFirst {
	    PROCESS_POINT_FIRST = 0x0001
    };

    enum ProcessLast {
	    PROCESS_POINT_LAST = 0x0002
    };

    enum ProcessFirstAndLast {
        PROCESS_POINT_FIRST_AND_LAST = 0x0004
    };

    enum ProcessFirstInIsoLevel {
        PROCESS_POINT_FIRST_IN_ISO_LEVEL = 0x0008
    };

    enum ProcessLastInIsoLevel {
        PROCESS_POINT_LAST_IN_ISO_LEVEL = 0x0010
    };

    inline const float * getCoordinateBase() {
	    return mData;
    }

    inline const float * getValueBase() {
	    return mData ? mData + mValueOffset : 0;
    }

    /**
    *   @brief get the points coordinate pointer.
    **/
    inline const float * getPointCoordinate(const int idx) {
	    return idx < mNumPoints ? mData + idx * mStride : 0;
    }

    /**
    *   @brief get the points value pointer.
    **/
    inline const float * getPointValue(const int idx) {
	    return idx < mNumPoints ? mValueData + idx * mStride : 0;
    } 

    /**
    *   @brief get the shape of the primitive.
    **/
    inline XipTFPrimitiveShape getShape() {return mPrimitiveShape; }

    /**
    *   @brief get the type of the primitive.
    **/
    inline XipTFPrimitiveType getType() {return mPrimitiveType; }

    /**
    *   @brief get the channel mask.
    **/
    inline unsigned int getChannelMask() { return mChannelMask; } 

    /**
    *   Get the coordinate dimension.
    **/
    inline int getCoordinateDim() { return mCoordDim; } 

    /**
    *   @brief get the value dimension.
    **/
    inline int getValueDim() { return mValueDim; }

    /**
    *   @brief get the number of points.
    **/
    inline int getNumPoints() { return mNumPoints; }

    /**
    *   @brief get the number of points in each isolevel.
    **/
    inline int getNumPointsInIsoLevel() { return mNumPointsInIsoLevel; }

    /**
    *   @brief get the number of isolevels.
    **/
    inline int getNumIsoLevels() { return mNumIsoLevels; }

    /**
    *   @brief get the index of the base point in a specified isoLevel. 
    * 
    *   plus one is for the centerpoint.
    **/
    inline int getIsoLevelBasePointIndex(int isoLevel) { return isoLevel*mNumPointsInIsoLevel + 1; }

    /**
    *   @brief get the alpha value for a point.
    **/
    inline float getAlphaValue(const int pointIdx) {return getPointValue(pointIdx)[mAlphaValueOffset]; }
    
    /**
    *   @brief get which index the alpha value has.
    **/
    inline int getAlphaChannelIndex() {return mAlphaValueOffset; }

    /**
    *   @brief This function loops over all points in the primitve and applies the operator
    *   op on each point. The rendering of the primitives may be done in this manner.
    **/
    template <class operator_t>
    inline void processAllPoints(operator_t & op);

    /**
    *   @brief This function loops over a selection of points in the primitve and applies the operator
    *   op on each point. The rendering of selections in the primitives may be done in this manner.
    **/
    template <class operator_t>
    inline void processPoints(operator_t & op, int firstIdx, int lastIdx);

protected:
 
    /**
    *   @brief set the shape of a primitive.
    **/
    inline void setShape(XipTFPrimitiveShape shape) {mPrimitiveShape = shape; }

    /**
    *   @brief set the type of a primitive.
    **/
    inline void setType(XipTFPrimitiveType type) {mPrimitiveType = type; }

    /**
    *   @brief set the trackingID.
    **/
    inline void setTrackingID(int ID) {mTID = ID; }

    /**
    *   @brief set primary color of a primitive - not always used.
    **/
    inline void setPrimaryColor(float r, float g, float b, float alpha) { 
        mPrimaryColor[0] = r; mPrimaryColor[1] = g; 
        mPrimaryColor[2] = b; mPrimaryColor[3] = alpha; }

    /**
    *   @brief set the channel mask.
    **/
    inline void setChannelMask(unsigned int mask) {mChannelMask = mask; }

    /**
    *   @brief set shading mode of a primitive.
    **/
    inline void setShadingMode(unsigned int mode) {mShadingMode = mode; }

    /**
    *   @brief set which groups the primitive belongs to.
    **/
    // TO DO check for error if array is not allocated of the size specified by numgroups
    inline void setGroups(int* groupIndices, int numGroups) { mGroups = groupIndices; mNumGroups = numGroups; } 
    
    /**
    *   @brief set the semantic label of the primitive - ex: is it bone/muscle tissue.
    **/
    inline void setSematicLabel(const int semanticLabel) {mSematicLabel = semanticLabel; }

    /**
    *   @brief set alpha value if a point.
    **/
    inline void setAlphaValue(const int idx, float data) {*(mValueData + idx*mStride + mAlphaValueOffset) = data; }

    /**
    *   @brief set a value to all teh points of a primitive. Ex: color for the whole primitive
    *   means that the 3 (datalength) first data values of each point is set to the specified value.
    **/
    inline void setPrimitiveValue(const float * data, int dataLength) 
    { 
        if (!data)
             SoDebugError::post( "setPrimitiveValue", "invalid data pointer!" ); // ERROR TO DO
        for (int i=0; i<mNumPoints; i++)
            setPointValue(i, data, dataLength); 
    } 
   
    /**
    *   @brief set value of a point.
    **/
    void setPointValue(const int idx, const float * data, const int dataLength);

    /**
    *   @brief set coordinate value of a point.
    **/
    void setPointCoordinate(const int idx, const float * data, const int dataLength);

    /**
    *   @brief swap the points in the actual data array -> copying values.
    **/
    void swapPoints(const int point1, const int point2);

protected:
    
    int			mTID;		// Tracking ID

    /* Some generic data goes here... */
    float		mPrimaryColor[4];
    unsigned int	mChannelMask;	// Channel mask (max 32 channels)
    int			mShadingMode;	// Shading modes semantics not defined in prim

    /* Primitive may be in zero, one or more groups */
    int *		mGroups;	// Indices to groups
    int			mNumGroups;

    /* Primitive may be in zero or one semantic label/group */
    int			mSematicLabel;	// Index into semantic labels

    XipTFPrimitiveShape mPrimitiveShape;
    XipTFPrimitiveType mPrimitiveType;

    /*
      I might add/create a more generic way to support adding more data fields
      and bind them to a description table - dynamically creating structs or so.
      For now just hardwire all additional primitive data you need.
    */

    int mNumIsoLevels;
    int mNumPointsInIsoLevel;


    /* Here's a set of basic parts... */
    int		mNumPoints;
    int		mCoordDim;
    int		mValueDim;

    int		mStride;
    int		mValueOffset;
    int     mAlphaValueOffset;

    float *	mData;
    int		mDataSize;		// assert: mNumPoints * mStride <= mDataSize
    float *	mValueData;		// = mData + mValueOffset;

};


template <class operator_t>
inline void XipTFPrimitive::processAllPoints(operator_t & op)
{
    float * coord = mData;
    float * value = mValueData;

    int i = 0;

    if (mNumPoints > 0) //  standard 
    {
        op(i, coord, value, PROCESS_POINT_FIRST);
        i++;
        coord += mStride;
        value += mStride;

        for (; i < mNumPoints-1; i++)
        {
            op(i, coord, value);
            coord += mStride;
            value += mStride;
        }

        op(i, coord, value, PROCESS_POINT_LAST);
    }
}

template <class operator_t>
inline void XipTFPrimitive::processPoints(operator_t & op, int firstIdx, int lastIdx)
{
    float * coord = mData + mStride*firstIdx;
    float * value = mValueData + mStride*firstIdx;

    int i = firstIdx;

    if (mNumPoints > lastIdx && lastIdx > firstIdx)
    {     
        op(i, coord, value, PROCESS_POINT_FIRST);
        
        i++;
        coord += mStride;
        value += mStride;

        for (; (i < mNumPoints-1) && (i < lastIdx); i++)
        {
            op(i, coord, value);
            coord += mStride;
            value += mStride;
        }

        op(i, coord, value, PROCESS_POINT_LAST);
    }
    else if (mNumPoints > lastIdx && lastIdx == firstIdx)
    {   
        op(i, coord, value, PROCESS_POINT_FIRST_AND_LAST);          
    }
}


/*
  Example code to draw quads and then lines on top of the quad,
  taking into care that the first and last points might not be
  at the bottom (base).
*/
#if 0
inline void DrawPrimitive(XipTFPrimitive * prim)
{
    PODrawQuadsCW1D quadsOp(0.0, 0.0);
    PODrawLines1D linesOp(0.0, 0.01);
    PODrawPoints1D pointsOp(0.0, 0.02);

    prim->processAllPoints(quadsOp);
    prim->processAllPoints(linesOp);
    prim->processAllPoints(pointsOp); 
};
#endif


#endif /* XIP_TF_PRIMITIVE_H */
