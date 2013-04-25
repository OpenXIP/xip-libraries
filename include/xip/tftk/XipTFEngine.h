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

#ifndef  XIP_TF_ENGINE_H
#define  XIP_TF_ENGINE_H

#include "XipTFDefinition.h" 
#include "XipTFPrimitiveIntersectFunctions.h"
#include "XipTFPrimitiveRenderFunctions.h"


/*
  XIP Transfer Function Toolkit (XIP TFTK)

  

*/



/*
  xip/tftk/XipTFEngine

  The TF engine is the compenent that tracks changes in a TF Definition.
  Supports communication with client or server.  I think this guy is the one
  we register all new types and features with.  By installing parsers,
  type definitions and callbacks for various change tracking etc.
  Some of this was in my old tfeditor_t class.

  Change tracking is moved into TFDefinition so each TF their own undo list.

*/

class XipTFEngine {
public:

    /**
    *   @brief Instance manager. so far only one instace is supported.
    */
    static XipTFEngine * getInstance(const char * name = "DEFAULT");

    /**
    *   @brief Instance manager. so far only one instace is supported.
    */
    static int XipTFEngine::releaseInstance(const char * name = "DEFAULT");

    /**
    *   @brief  Load a TF from file.
    *
    *  Load a TF from file, put into a container slot, -1 means next available.
    *  Returns used slot, -1 on failure.
    *
    **/
    int loadFromFile(char * filename, int slot = -1);

    /**
    *   @brief  Save a TF to file.
    *
    **/
    int saveToFile(char * filename, int slot);

    /**
    *   @brief   Install a TF Container at a slot, -1 means any available.
    *
    *   Return value -1 failed.
    **/
    int installDefinition(XipTFDefinition * definition, int slot = -1);

    /**
    *   @brief  Release a definition.
    **/
    XipTFDefinition * releaseDefinition(int slot);

    /**
    *   @brief  swap 2 defitnions.
    **/
    int swapDefinitions(int def1, int def2);

    /**
    *   @brief  Set the active definition.
    *   
    *   if slot is out of the range of the available slots, slot 0 is set as active
    **/
    inline void setActiveDefinition(int slot) { 
        slot = (slot < 0) ? -1 : (slot >= mNumDefinitions) ? -1 : slot;
        mActiveDefinition = slot;}
    
    /**
    *   @brief  Get the active definition.
    **/
    inline XipTFDefinition * getActiveDefinition() 
    {        
        return (mActiveDefinition < 0) ? 0 : (mActiveDefinition >= mNumDefinitions) ? 0 : mDefinitions[mActiveDefinition]; 
    }

    /**
    *   @brief  Get the active definitions index.
    **/
    inline int getActiveDefinitionIndex() { return mActiveDefinition; }
    
    /**
    *   @brief  Return pointer to definition.
    *
    *   If index is out of bounds the first Definition is selected
    *
    **/
    inline XipTFDefinition * getDefinition(int index = -1) 
    { 
        index = (index < 0) ? mActiveDefinition : (index >= mNumDefinitions) ? mActiveDefinition : index;
        return mDefinitions[index]; 
    }

    /**
    *   @brief  Return the number of definitions installed.
    *
    **/
    inline int getNumDefinitions() { return mNumDefinitions; }
    
    /**
    *   @brief  Loops over all primitives in selection specified by qualifiers and apply the operator to each point.
    **/
    template <class operator_t>
    inline void processPrimitives(operator_t & op, unsigned long * qualifiers = 0,
				   int length = 0, int defSlot = -1)
    {
        defSlot = defSlot < 0 ? mActiveDefinition : defSlot >= mNumDefinitions ? mActiveDefinition : defSlot; 
        mDefinitions[defSlot]->processPrimitives(op, qualifiers, length);
    }

    /**
    *   @brief  Loops over the selected primitives and apply the operator to each point.
    **/
    template <class operator_t>
    inline void processPrimitives(operator_t & op, char* selectionMask, int length, int defSlot = -1) 
    {
        defSlot = defSlot < 0 ? mActiveDefinition : defSlot >= mNumDefinitions ? mActiveDefinition : defSlot; 
        mDefinitions[defSlot]->processPrimitives(op, selectionMask, length);
    }

    /**
    *   @brief  Render primitives with the predefined function that the mPrimRenderFuncTable points to
    *   for this shape. flags tell which kind of graphics priitives to render, e.g. line points areas. 
    *   qualifiers tell which (type, shape, kind) of the primitives are to be rendered.
    **/
    int renderPrimitives(int numRenderedPrims = 0, int flags = 0xffff, unsigned long * qualifiers = 0, 
        int length = 0, int defSlot = -1);

    /**
    *   @brief  Perform check to see if any primitives are hit at location (x,y).
    *   sensitivity is the limit on how far away the click can be. If the viewport
    *   is not square adjust this accordingly to sensitivity. Flags tells us which 
    *   graphics types (points, lines, ...), and qualifiers tells us which primitives 
    *   to intersect. The background is always checked for intersection.
    **/
    XipTFIntersectRecord * intersectPrimitives(float x, float y, int &numHits, float *sensitivityXY,
        int flags = 0xffff, unsigned long * qualifiers = 0, int length = 0, int defSlot = -1 );
    
    /**
    *   @brief  Perform check to see if any primitives are hit at location (x,y).
    **/
    inline XipTFIntersectRecord * intersectPrimitives(float x, float y) 
    {
        int dummy;
        float sensitivity[2] = {0.03, 0.03};
        return intersectPrimitives(x, y, dummy, sensitivity);
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
    inline char * createSelectionMask(unsigned long * qualifiers = 0, int length = 0, int defSlot = -1)
    {
        defSlot = defSlot < 0 ? mActiveDefinition : defSlot >= mNumDefinitions ? mActiveDefinition : defSlot; 
        return mDefinitions[defSlot]->createSelectionMask(qualifiers, length);
    }

    /**
    *   delete the selection.
    **/
    inline void freeSelection(char * selection, int defSlot = -1)
    {
        defSlot = defSlot < 0 ? mActiveDefinition : defSlot >= mNumDefinitions ? mActiveDefinition : defSlot; 
        mDefinitions[defSlot]->freeSelection(selection);
    }

    /**
    *   Yet to be implemented
    **/
    void reassignTrackingIDs(int defSlot = -1)
    {
        defSlot = defSlot < 0 ? mActiveDefinition : defSlot >= mNumDefinitions ? mActiveDefinition : defSlot; 
        mDefinitions[defSlot]->reassignTrackingIDs();
    }

    /**
    *   @brief move a certain point in a primitive.
    *   -1 or any number outside of allowed the span on the slot and primitive index
    *   will select the active primitive/definition.
    **/
    inline void setPointCoordinate(int pointIndex, const float *newCoord, int dataLength, int primIdx = -1, int defSlot = -1)
    {
        defSlot = defSlot < 0 ? mActiveDefinition : defSlot >= mNumDefinitions ? mActiveDefinition : defSlot; 
        mDefinitions[defSlot]->setPointCoordinate(pointIndex, newCoord, dataLength, primIdx);
    };
    
    /**
    *   @brief change the value of a specific point in a primitive.
    *   -1 or any number outside of allowed the span on the slot and primitive index
    *   will select the active primitive/definition.
    **/
    inline void setPointValue(int pointIndex, const float * value, int dataLength,  int primIdx = -1, int defSlot = -1 ) 
    {
        defSlot = defSlot < 0 ? mActiveDefinition : defSlot >= mNumDefinitions ? mActiveDefinition : defSlot; 
        mDefinitions[defSlot]->setPointValue(pointIndex, value, dataLength, primIdx);
    }

    /**
    *   @brief change the value of all points in a primitive. Ex: RGB channels for whole primitive
    *   -1 or any number outside of allowed the span on the slot and primitive index
    *   will select the active primitive/definition.
    **/
    inline void setPrimitiveValue(const float * value, int dataLength,  int primIdx = -1, int defSlot = -1 ) 
    {
        defSlot = defSlot < 0 ? mActiveDefinition : defSlot >= mNumDefinitions ? mActiveDefinition : defSlot; 
        mDefinitions[defSlot]->setPrimitiveValue(value, dataLength, primIdx);
    }

    /**
    *   @brief set a certain points alpha value in a defintion.
    *   -1 or any number outside of allowed the span on the slot and primitive index
    *   will select the active primitive/definition. 
    **/
    inline void setAlphaValue(int pointIndex, float newAlphaValue, int primIdx = -1, int defSlot = -1)
    {       
        defSlot = defSlot < 0 ? mActiveDefinition : defSlot >= mNumDefinitions ? mActiveDefinition : defSlot; 
        mDefinitions[defSlot]->setAlphaValue(pointIndex, newAlphaValue, primIdx);
    };

    /**
    *   @brief  swap 2 primitives around.
    *   An invalid defintion slot selects the active slot.
    **/
    inline int swapPrimitives(int prim1, int prim2, int defSlot = -1) 
    { 
        defSlot = defSlot < 0 ? mActiveDefinition : defSlot >= mNumDefinitions ? mActiveDefinition : defSlot; 
        if ( -1 == defSlot )
            return 0;

        return mDefinitions[defSlot]->swapPrimitives(prim1, prim2);
    }

    /**
    *   @brief  Add a primitive.
    *   
    *   Add a primitive to a definition. If no index is specified 
    *   or the index is invalid the primitive will be added to the 
    *   end of the array. If their is no definition, no primitive will be added. 
    **/
    inline int addPrimitive(XipTFPrimitive * prim, int primIdx = -1, int defSlot = -1)
    {
        defSlot = defSlot < 0 ? mActiveDefinition : defSlot >= mNumDefinitions ? mActiveDefinition : defSlot; 
        if ( -1 == defSlot )
            return 0;

        return mDefinitions[defSlot]->addPrimitive(prim, primIdx);
    };

    /**
    *   @brief  Remove a primitive.
    *   
    *   Remove a primitive from a definition. This function does NOT 
    *   delete the primitive. This is up to the user.
    *   If primitive index is -1 the active primitive is selected
    **/
    inline XipTFPrimitive * removePrimitive(int primIdx = -1, int defSlot = -1)
    {
        defSlot = defSlot < 0 ? mActiveDefinition : defSlot >= mNumDefinitions ? mActiveDefinition : defSlot; 
        if (-1 == defSlot)
            return 0;
        return mDefinitions[defSlot]->removePrimitive(primIdx);
    }

    /**
    *   @brief  set the active primitive.
    *   Invalid primitive index chooses the active primitive.
    *   Invalid defintion slot index chooses the active definition.
    **/
    inline void setActivePrimitive(int primIdx = -1, int defSlot = -1) 
    {
        defSlot = defSlot < 0 ? mActiveDefinition : defSlot >= mNumDefinitions ? mActiveDefinition : defSlot; 
        mDefinitions[defSlot]->setActivePrimitive(primIdx);
    }

    /**
    *   @brief  get a primitive.
    *   Invalid primitive index chooses the active primitive.
    *   Invalid defintion slot index chooses the active definition.
    **/
    inline XipTFPrimitive* getPrimitive(int primIdx = -1, int defSlot = -1) 
    {
        defSlot = defSlot < 0 ? mActiveDefinition : defSlot >= mNumDefinitions ? mActiveDefinition : defSlot; 
        return mDefinitions[defSlot]->getPrimitive(primIdx);
    }

    /**
    *   @brief get the shape of the primitive, if index is invalid the active definition will be choosen.
    *   Invalid primitive index chooses the active primitive.
    *   Invalid defintion slot index chooses the active definition.
    **/
    inline XipTFPrimitiveShape getShape(int primIdx = -1, int defSlot = -1) 
    {
        defSlot = defSlot < 0 ? mActiveDefinition : defSlot >= mNumDefinitions ? mActiveDefinition : defSlot; 
        return mDefinitions[defSlot]->getShape(primIdx); 
    }

    /**
    *   @brief get the type of the primitive, if index is invalid the active definition will be choosen.
    *   Invalid primitive index chooses the active primitive.
    *   Invalid defintion slot index chooses the active definition.
    **/
    inline XipTFPrimitiveType getType(int primIdx = -1, int defSlot = -1) 
    {
        defSlot = defSlot < 0 ? mActiveDefinition : defSlot >= mNumDefinitions ? mActiveDefinition : defSlot; 
        return mDefinitions[defSlot]->getType(primIdx); 
    }

    /**
    *   @brief get the channel mask, if index is invalid the active definition will be choosen.
    *   Invalid primitive index chooses the active primitive.
    *   Invalid defintion slot index chooses the active definition.
    **/
    inline unsigned int getChannelMask(int primIdx = -1, int defSlot = -1)
    { 
        defSlot = defSlot < 0 ? mActiveDefinition : defSlot >= mNumDefinitions ? mActiveDefinition : defSlot; 
        return mDefinitions[defSlot]->getChannelMask(primIdx); 
    } 

    /**
    *   @brief get the coordinate dimension, if index is invalid the active definition will be choosen.
    *   Invalid primitive index chooses the active primitive.
    *   Invalid defintion slot index chooses the active definition.
    **/
    inline int getCoordinateDim(int primIdx = -1, int defSlot = -1) 
    { 
        defSlot = defSlot < 0 ? mActiveDefinition : defSlot >= mNumDefinitions ? mActiveDefinition : defSlot; 
        return mDefinitions[defSlot]->getCoordinateDim(primIdx); 
    } 

    /**
    *   @brief get the value dimension, if index is invalid the active definition will be choosen.
    *   Invalid primitive index chooses the active primitive.
    *   Invalid defintion slot index chooses the active definition.
    **/
    inline int getValueDim(int primIdx = -1, int defSlot = -1) 
    { 
        defSlot = defSlot < 0 ? mActiveDefinition : defSlot >= mNumDefinitions ? mActiveDefinition : defSlot; 
        return mDefinitions[defSlot]->getValueDim(primIdx); 
    } 

    /**
    *   @brief get the number of points, if index is invalid the active definition will be choosen.
    *   Invalid primitive index chooses the active primitive.
    *   Invalid defintion slot index chooses the active definition.
    **/
    inline int getNumPoints(int primIdx = -1, int defSlot = -1) 
    { 
        defSlot = defSlot < 0 ? mActiveDefinition : defSlot >= mNumDefinitions ? mActiveDefinition : defSlot; 
        return mDefinitions[defSlot]->getNumPoints(primIdx); 
    } 

    /**
    *   @brief get the number of points in each isolevel, if index is invalid the 
    *   active primitive will be choosen. Invalid defintion slot index chooses the active definition.
    **/
    inline int getNumPointsInIsoLevel(int primIdx = -1, int defSlot = -1) 
    { 
        defSlot = defSlot < 0 ? mActiveDefinition : defSlot >= mNumDefinitions ? mActiveDefinition : defSlot; 
        return mDefinitions[defSlot]->getNumPointsInIsoLevel(primIdx); 
    } 
    /**
    *   @brief get the number of isolevels, if index is invalid the 
    *   active primitive will be choosen. Invalid defintion slot index chooses the active definition.
    **/
    inline int getNumIsoLevels(int primIdx = -1, int defSlot = -1) 
    { 
        defSlot = defSlot < 0 ? mActiveDefinition : defSlot >= mNumDefinitions ? mActiveDefinition : defSlot; 
        return mDefinitions[defSlot]->getNumIsoLevels(primIdx); 
    } 

    /**
    *   @brief get the index of the base point in a specified isoLevel, if index is invalid the 
    *   active primitive will be choosen. Invalid defintion slot index chooses the active definition.
    **/
    inline int getIsoLevelBasePointIndex(int isoLevel, int primIdx = -1, int defSlot = -1) 
    { 
        defSlot = defSlot < 0 ? mActiveDefinition : defSlot >= mNumDefinitions ? mActiveDefinition : defSlot; 
        return mDefinitions[defSlot]->getIsoLevelBasePointIndex(isoLevel, primIdx);
    }

    /**
    *   @brief  Return index to active primitive, if index is invalid the active definition will be choosen.
    *   Invalid defintion slot index chooses the active definition.
    **/
    inline int getActivePrimitiveIndex(int defSlot = -1) 
    { 
        defSlot = defSlot < 0 ? mActiveDefinition : defSlot >= mNumDefinitions ? mActiveDefinition : defSlot; 
        return mDefinitions[defSlot]->getActivePrimitiveIndex(); 
    } 

    /**
    *   @brief  Get the number of primitives, if index is invalid the active definition will be choosen.
    *   Invalid defintion slot index chooses the active definition.
    **/
    inline int getPrimitiveCount(int defSlot = -1) 
    { 
        defSlot = defSlot < 0 ? mActiveDefinition : defSlot >= mNumDefinitions ? mActiveDefinition : defSlot; 
        return mDefinitions[defSlot]->getPrimitiveCount(); 
    } 

    /**
    *   @brief swap the points in the actual data array -> copying values. 
    *   Invalid primitive index chooses the active primitive.
    *   Invalid defintion slot index chooses the active definition.
    **/
    inline void swapPoints(int point1, int point2, int primIdx = -1, int defSlot = -1)
    {
        defSlot = defSlot < 0 ? mActiveDefinition : defSlot >= mNumDefinitions ? mActiveDefinition : defSlot; 
        return mDefinitions[defSlot]->swapPoints(point1, point2, primIdx);
    };

    /**
    *   @brief get the points coordinate pointer, if index is invalid the active primitive will be choosen.
    *   Do not change the value which this is pointed. If one wishes to change the value use the set functions.
    *   This is becaue the XipTFEngine is supposed to be able to track all changes to the data.
    **/
    inline const float * getPointCoordinate(int pointIdx, int primIdx = -1, int defSlot = -1)    
    { 
        defSlot = defSlot < 0 ? mActiveDefinition : defSlot >= mNumDefinitions ? mActiveDefinition : defSlot; 
        return mDefinitions[defSlot]->getPointCoordinate(pointIdx, primIdx); 
    } 

    /**
    *   @brief get the points value pointer, if index is invalid the active primitive will be choosen.
    *   Do not change the value which this is pointed. If one wishes to change the value use the set functions.
    *   This is becaue the XipTFEngine is supposed to be able to track all changes to the data.
    **/
    inline const float * getPointValue(int pointIdx, int primIdx = -1, int defSlot = -1)    
    { 
        defSlot = defSlot < 0 ? mActiveDefinition : defSlot >= mNumDefinitions ? mActiveDefinition : defSlot; 
        return mDefinitions[defSlot]->getPointValue(pointIdx, primIdx); 
    } 
    
    /**
    *   @brief get the alpha value for a point, if index is invalid the active primitive will be choosen.
    *   Do not change the value which this is pointed. If one wishes to change the value use the set functions.
    *   This is becaue the XipTFEngine is supposed to be able to track all changes to the data.
    **/
    inline float getAlphaValue(int pointIdx, int primIdx = -1, int defSlot = -1)    
    { 
        defSlot = defSlot < 0 ? mActiveDefinition : defSlot >= mNumDefinitions ? mActiveDefinition : defSlot; 
        return mDefinitions[defSlot]->getAlphaValue(pointIdx, primIdx); 
    } 

    /**
    *   @brief get which index the alpha value has.
    **/
    inline int getAlphaChannelIndex(int primIdx = -1, int defSlot = -1)    
    { 
        defSlot = defSlot < 0 ? mActiveDefinition : defSlot >= mNumDefinitions ? mActiveDefinition : defSlot; 
        return mDefinitions[defSlot]->getAlphaChannelIndex();
    }

    /**
    *   @brief Generate a look-up table. Default gives no selection so send in qualifiers.
    **/
    float* generateLUT(int LUTWidth, int LUTHeight, unsigned long * qualifiers = 0, int length = 0, 
        int defSlot = -1);

    /**
    *   @brief mLastTID is updated every time a function changes the structure.
    **/
    unsigned int getTrackingID(int defSlot = -1)
    {
        defSlot = defSlot < 0 ? mActiveDefinition : defSlot >= mNumDefinitions ? mActiveDefinition : defSlot; 
        return mDefinitions[defSlot]->getTrackingID();
    } 
    
protected:
    int	mActiveDefinition;

    XipTFDefinition **	mDefinitions;		// Allocated array
    int mNumDefinitions;
    int mNumRegisteredPrimitiveTypes;
    int mNumRegisteredPrimitiveShapes;

    static XipTFIntersectFunction mPrimIntersectFuncTable[XIP_TF_NUM_PRIMITIVE_SHAPES];
    static XipTFRenderFunction mPrimRenderFuncTable[XIP_TF_NUM_PRIMITIVE_SHAPES];

    float* mLUT;
    int mLUTWidth;

private:
    XipTFEngine();
    ~XipTFEngine();
    XipTFEngine(const XipTFEngine& obj) {}; // should never happen - copying

    static XipTFEngine * mInstance;
    static int mNumInstances;

};







#endif /* XIP_TF_ENGINE_H */
