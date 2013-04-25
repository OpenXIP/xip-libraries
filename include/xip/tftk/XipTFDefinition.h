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

#ifndef  XIP_TF_DEFINITION_H
#define  XIP_TF_DEFINITION_H

#include <xip/tftk/XipTFPrimitive.h>


/*
  XIP Transfer Function Toolkit (XIP TFTK)

  

*/


/*
  xip/tftk/XipTFDefinition

  Not completely happy with this name...

*/

class XipTFDefinition {
    friend class XipTFEngine;
public:

    XipTFDefinition();
    ~XipTFDefinition();    

    /*
    Process primitives in the definition. selections holds an
    optional list of selection modifiers, like SET_CHANNEL_MASK,
    INCLUDE_TYPE, etc.
    This routine may be be used to generate lookup tables, draw the
    primitives, etc...
    */    

    /*! 
    *   Process primitives will loop over all the primitives and apply the operator 
    *   to each point. However the operator will only be applied to the primitive if
    *   the coordinate dimension of the primitive matches the return value of getDim() 
    *   from the operator class. If the operator should be applied to all primitives
    *   just make sure the getDim() returns -1.
    *
    *   processPrimitives resets the Depth value of the operator to zero. If this 
    *   is unwanted rewrite this code.
    **/
    template <class operator_t>
    inline void processPrimitives(operator_t & op,
        unsigned long * qualifiers = 0, int length = 0);

    template <class operator_t>
    inline void processPrimitives(operator_t & op,
        char* selectionMask, int length);

    enum PrimitiveSelection {
        SELECT_END_OF_LIST = 0,
        SELECT_SET_CHANNEL_MASK = 1,
        SELECT_COORDINATE_DIM = 3,
        SELECT_ACTIVE_PRIMITIVE = 4,        
        SELECT_INCLUDE_TYPE = 10,
        SELECT_INCLUDE_GROUP = 11,
        SELECT_INCLUDE_LAYER = 12,	// Short for Semantic Layer
    };


    /*
      It should support recording/tracking of changes so we can
      support undos to some extent. But it might become complicated if
      all indexes all that shifts around, so maybe we need to have
      another form of keeping track these objects so the links can be
      recreated.  Maybe a simple sequence numbering scheme would be
      enough so we can search for the objects.  Calling it Tracking ID
      and is maintained by the Engine -- no, moved it into
      TFDefinition.
    */
    unsigned int getNewTrackingID()
    {
	    mLastTID++;
    
	    if (mLastTID > 0x7ffffffe) 
        {
	        // Safe guard if the application isn't restarted in a long time...
	        // Might require communication to client/server to update tracking IDs.
	        // We should try to avoid that!!!
	        reassignTrackingIDs();
	    }

	    return mLastTID;
    }

    /**
    *   @brief mLastTID is updated every time a function changes the structure.
    **/
    unsigned int getTrackingID()
    {
	    return mLastTID;
    }  

    /**
    *   Create a selection of primitives. The list of qualifiers is tetsed against
    *   all primitives and a mask of the desired primitives is returned.
    *   This can be used for selection ex selection with mouse or whenever
    *   one needs only a certain type of primitive.
    *   
    *   Default is channelMask == ~0 (all channels)
    *   Coordinate Dimension == 1
    **/
    char * createSelectionMask(unsigned long * qualifiers, int length);

    /**
    *   delete the selection.
    **/
    void freeSelection(char * selection);

    /**
    *   Yet to be implemented
    **/
    void reassignTrackingIDs();

    /**
    *   @brief  Return pointer to primitive.
    *
    *   If index is out of bounds the active primitive is selected.
    *
    **/
    inline XipTFPrimitive * getPrimitive(int index = -1) 
    { 
        index = (index < 0) ? mActivePrimitive : (index >= mNumPrimitives) ? mActivePrimitive : index;
        return mPrimitives[index]; 
    }
    
    /**
    *   @brief  Get the number of primitives.
    **/
    inline int getPrimitiveCount() { return mNumPrimitives; }

    /**
    *   @brief  Return index to active primitive.
    **/
    inline int getActivePrimitiveIndex() { return mActivePrimitive; }

    /**
    *   @brief  Return the active primitive.
    **/
    inline XipTFPrimitive * getActivePrimitive() { return mPrimitives[mActivePrimitive]; }

    /**
    *   @brief get the shape of the primitive, if index is invalid the active primitive will be choosen.
    **/
    inline XipTFPrimitiveShape getShape(int primIdx = -1) 
    {
        primIdx = primIdx < 0 ? mActivePrimitive : primIdx >= mNumPrimitives ? mActivePrimitive : primIdx;
        return mPrimitives[primIdx]->getShape(); 
    }

    /**
    *   @brief get the type of the primitive, if index is invalid the active primitive will be choosen.
    **/
    inline XipTFPrimitiveType getType(int primIdx = -1) 
    {
        primIdx = primIdx < 0 ? mActivePrimitive : primIdx >= mNumPrimitives ? mActivePrimitive : primIdx;
        return mPrimitives[primIdx]->getType(); 
    }

    /**
    *   @brief get the channel mask, if index is invalid the active primitive will be choosen.
    **/
    inline unsigned int getChannelMask(int primIdx = -1)
    { 
        primIdx = primIdx < 0 ? mActivePrimitive : primIdx >= mNumPrimitives ? mActivePrimitive : primIdx;
        return mPrimitives[primIdx]->getChannelMask(); 
    } 

    /**
    *   @brief get the coordinate dimension, if index is invalid the active primitive will be choosen.
    **/
    inline int getCoordinateDim(int primIdx = -1) 
    { 
        primIdx = primIdx < 0 ? mActivePrimitive : primIdx >= mNumPrimitives ? mActivePrimitive : primIdx;
        return mPrimitives[primIdx]->getCoordinateDim(); 
    } 

    /**
    *   @brief get the value dimension, if index is invalid the active primitive will be choosen.
    **/
    inline int getValueDim(int primIdx = -1) 
    { 
        primIdx = primIdx < 0 ? mActivePrimitive : primIdx >= mNumPrimitives ? mActivePrimitive : primIdx;
        return mPrimitives[primIdx]->getValueDim(); 
    } 

    /**
    *   @brief get the number of points, if index is invalid the active primitive will be choosen.
    **/
    inline int getNumPoints(int primIdx = -1) 
    { 
        primIdx = primIdx < 0 ? mActivePrimitive : primIdx >= mNumPrimitives ? mActivePrimitive : primIdx;
        return mPrimitives[primIdx]->getNumPoints(); 
    } 

    /**
    *   @brief get the number of points in each isolevel, if index is invalid the 
    *   active primitive will be choosen.
    **/
    inline int getNumPointsInIsoLevel(int primIdx = -1) 
    { 
        primIdx = primIdx < 0 ? mActivePrimitive : primIdx >= mNumPrimitives ? mActivePrimitive : primIdx;
        return mPrimitives[primIdx]->getNumPointsInIsoLevel(); 
    } 
    /**
    *   @brief get the number of isolevels, if index is invalid the 
    *   active primitive will be choosen.
    **/
    inline int getNumIsoLevels(int primIdx = -1) 
    { 
        primIdx = primIdx < 0 ? mActivePrimitive : primIdx >= mNumPrimitives ? mActivePrimitive : primIdx;
        return mPrimitives[primIdx]->getNumIsoLevels(); 
    } 

    /**
    *   @brief get the index of the base point in a specified isoLevel.
    **/
    inline int getIsoLevelBasePointIndex(int isoLevel, int primIdx = -1) 
    { 
        primIdx = primIdx < 0 ? mActivePrimitive : primIdx >= mNumPrimitives ? mActivePrimitive : primIdx;
        return mPrimitives[primIdx]->getIsoLevelBasePointIndex(isoLevel);
    }

    /**
    *   @brief get the points coordinate pointer, if index is invalid the active primitive will be choosen.
    *   Do not change the value which this is pointed. If one wishes to change the value use the set functions.
    *   This is becaue the XipTFEngine is supposed to be able to track all changes to the data.
    **/
    inline const float * getPointCoordinate(const int pointIdx, int primIdx = -1)    
    { 
        primIdx = primIdx < 0 ? mActivePrimitive : primIdx >= mNumPrimitives ? mActivePrimitive : primIdx;
        return mPrimitives[primIdx]->getPointCoordinate(pointIdx); 
    } 

    /**
    *   @brief get the points value pointer, if index is invalid the active primitive will be choosen.
    *   Do not change the value which this is pointed. If one wishes to change the value use the set functions.
    *   This is becaue the XipTFEngine is supposed to be able to track all changes to the data.
    **/
    inline const float * getPointValue(const int pointIdx, int primIdx = -1)    
    { 
        primIdx = primIdx < 0 ? mActivePrimitive : primIdx >= mNumPrimitives ? mActivePrimitive : primIdx;
        return mPrimitives[primIdx]->getPointValue(pointIdx); 
    } 

    /**
    *   @brief get the alpha value for a point, if index is invalid the active primitive will be choosen.
    *   Do not change the value which this is pointed. If one wishes to change the value use the set functions.
    *   This is becaue the XipTFEngine is supposed to be able to track all changes to the data.
    **/
    inline float getAlphaValue(const int pointIdx, int primIdx = -1 )
    { 
        primIdx = primIdx < 0 ? mActivePrimitive : primIdx >= mNumPrimitives ? mActivePrimitive : primIdx;
        return mPrimitives[primIdx]->getAlphaValue(pointIdx); 
    } 

    /**
    *   @brief get which index the alpha value has.
    **/
    inline int getAlphaChannelIndex(int primIdx = -1 ) 
    {
        primIdx = primIdx < 0 ? mActivePrimitive : primIdx >= mNumPrimitives ? mActivePrimitive : primIdx;
        return mPrimitives[primIdx]->getAlphaChannelIndex();
    }


protected:

    /**
    *   @brief  Add a primitive.
    *   
    *   Add a primitive to the definition. If no index is specified 
    *   or the index is invalid the primitive will be added to the 
    *   end of the array.
    *
    **/
    int addPrimitive(XipTFPrimitive * prim, int idx = -1);
    
    /**
    *   @brief  Remove a primitive.
    *   
    *   Remove a primitive from the definition. This function does NOT 
    *   delete the primitive. This is up to the user.
    *   If primitive index is -1 the active primitive is selected
    *
    **/
    XipTFPrimitive * removePrimitive(int idx = -1);

    /*
      Primitive swapping supports reordering and moving around all
      primitives. But if the index change the group and primitive links
      must be updated as well. This should all be handled here so we have
      one (or a just a few places) all of that is managed.
      I really would like to be able to avoid pointers and rather stick with
      indexing.
    */
    int swapPrimitives(int prim1, int prim2);

    /**
    *   @brief  set the active primitive.
    **/
    inline void setActivePrimitive(int index) 
    {
        mLastTID++;
        index = (index < 0) ? 0 : (index >= mNumPrimitives) ? 0 : index;
        mActivePrimitive = index;
    }

    /**
    *   @brief move a certain point in a primitive.
    *   Invalid primitive index chooses the active primitive.
    **/
    inline void setPointCoordinate(int pointIndex, const float *newCoord, int dataLength, int primIdx = -1)
    {
        mLastTID++;
        primIdx = primIdx < 0 ? mActivePrimitive : primIdx >= mNumPrimitives ? mActivePrimitive : primIdx; 
        mPrimitives[primIdx]->setPointCoordinate(pointIndex, newCoord, dataLength);
    };

    /**
    *   @brief set value of a certain point in a primitive.
    *   Invalid primitive index chooses the active primitive.
    **/
    inline void setPointValue(int pointIndex, const float *value, int dataLength, int primIdx = -1)
    {
        mLastTID++;
        primIdx = primIdx < 0 ? mActivePrimitive : primIdx >= mNumPrimitives ? mActivePrimitive : primIdx; 
        mPrimitives[primIdx]->setPointValue(pointIndex, value, dataLength);
    };

    /**
    *   @brief set a certain points alpha value in a primitive.
    *   Invalid primitive index chooses the active primitive.
    **/
    inline void setAlphaValue(int pointIndex, float newAlphaValue, int primIdx = -1)
    {       
        mLastTID++;
        primIdx = primIdx < 0 ? mActivePrimitive : primIdx >= mNumPrimitives ? mActivePrimitive : primIdx; 
        mPrimitives[primIdx]->setAlphaValue(pointIndex, newAlphaValue);
    };

    /**
    *   @brief set value for all points in a primitive. Ex: the rgb channel of all points.
    *   Invalid primitive index chooses the active primitive.
    **/
    inline void setPrimitiveValue(const float *value, int dataLength, int primIdx = -1)
    {
        mLastTID++;
        primIdx = primIdx < 0 ? mActivePrimitive : primIdx >= mNumPrimitives ? mActivePrimitive : primIdx; 
        mPrimitives[primIdx]->setPrimitiveValue(value, dataLength);
    };

    /**
    *   @brief swap the points in the actual data array -> copying values. 
    *   Invalid primitive index chooses the active primitive.
    **/
    inline void swapPoints(int point1, int point2, int primIdx = -1)
    {
        mLastTID++;
        primIdx = primIdx < 0 ? mActivePrimitive : primIdx >= mNumPrimitives ? mActivePrimitive : primIdx; 
        mPrimitives[primIdx]->swapPoints(point1, point2);
    };


protected:
    int			mLastTID;

    int			mActivePrimitive;

    XipTFPrimitive **	mPrimitives;
    int			mNumPrimitives;    

//    XipTFResource **	mResources;
//    int			mNumResources;

    unsigned long * DGB_variableRemoveMeNowIfUSeeMe;
};


template <class operator_t>
inline void XipTFDefinition::processPrimitives(operator_t & op,
                unsigned long * qualifiers, int length)
{
    char * selPrims = createSelectionMask(qualifiers, length);

    if (!selPrims) return; 

    for(int i=0; i<mNumPrimitives; i++)
    {
        if (!selPrims[i]) 
        {            
            continue;
        }
        if ( op.getDim() == mPrimitives[i]->mCoordDim || op.getDim() == -1)
            op(i, mPrimitives[i]);
    }
    op.reset();

    freeSelection(selPrims);
};

template <class operator_t>
inline void XipTFDefinition::processPrimitives(operator_t & op,
                char* selectionMask, int length)
{
    if (!selectionMask || length != mNumPrimitives) return; 

    for(int i=0; i<mNumPrimitives; i++)
    {
        if (!selectionMask[i]) 
        {            
            continue;
        }
        else if ( op.getDim() == mPrimitives[i]->mCoordDim || op.getDim() == -1)
            op(i, mPrimitives[i]);
    }
    op.reset();

};









/*
  Use of the above...  this is just an example
*/
/*

make_selection(XipTFDefinition * tfdef)
{
    unsigned long defqual[] = {
	    XipTFDefinition::SELECT_SET_CHANNEL_MASK, 0x0003,
	    XipTFDefinition::SELECT_INCLUDE_TYPE, PRIMITIVE_TYPE_SCALAR_COLORALPHA,
	    XipTFDefinition::SELECT_END_OF_LIST, 0
    };

    PrimitiveRenderingOperator op(fun stuff);

    processPrimitives(op, defqual, sizeof(defqual) / sizeof(unsigned long));
}


*/

/*
inline void drawDefinition(XipTFDefinition * tfdef)
{
    PODrawQuadsCW1D quadsOp(0.0, 0.0);
    PODrawLines1D linesOp(0.0, 0.01);
    PODrawPoints1D pointsOp(0.0, 0.02);

    PrimitiveRenderingOperator renderOp(1,1);
    tfdef->processPrimitives(renderOp);
};
*/

#endif /* XIP_TF_DEFINITION_H */
