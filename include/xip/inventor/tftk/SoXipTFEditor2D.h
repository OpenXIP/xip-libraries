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


#ifndef SO_XIP_TF_EDITOR_2D_H
#define SO_XIP_TF_EDITOR_2D_H

#include <Inventor/nodes/SoShape.h>
#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/fields/SoMFInt32.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFColor.h>
#include <Inventor/fields/SoSFShort.h> 
#include <Inventor/fields/SoSFTrigger.h>
#include <Inventor/fields/SoSFVec2s.h>
#include <Inventor/fields/SoSFVec2f.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFVec4f.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/SbLinear.h>
#include <Inventor/SbTime.h>
#include <Inventor/SbViewportRegion.h>
#include <xip/inventor/core/SbXIPImage.h>
#include <xip/inventor/core/SoXIPDataImage.h>
#include <xip/inventor/core/SoXIPSFDataImage.h>

#include <xip/tftk/color.h>
#include <xip/tftk/BasicOps.h>
#include <xip/tftk/XipTFPrimitiveOperators.h> 
#include <xip/tftk/XipTFEngine.h>



class SoFieldSensor;
class TFPrimitive; 


class SoXipTFEditor2D : public SoShape
{
    SO_NODE_HEADER(SoXipTFEditor2D);

public:
    static void initClass();
    SoXipTFEditor2D();

    // FIELDS
    SoXipSFDataImage lutImage;

protected:
    virtual void generatePrimitives(SoAction *action);
    virtual void GLRender(SoGLRenderAction *action);
    virtual void computeBBox(SoAction *action, SbBox3f &box, SbVec3f &center);

    /**!   
    *   All mouse events go through here.
    **/
    virtual void handleEvent(SoHandleEventAction* action);

    /**!   
    *   Function callback to handle when the add primitive field is triggered. this is called by fieldChangeCB.
    **/
    static void addPrimitiveCB( void* userData, SoSensor* );

    /**!   
    *   Function callback to handle when the remove primitive field is triggered. this is called by fieldChangeCB.
    **/
    static void removePrimitiveCB( void* userData, SoSensor* );

    /**!   
    *   Function callback to handle when the fields change. This is where one
    *   would add new callback actions.
    **/
    static void fieldChangeCB( void* userData, SoSensor* );
    
    /**!   
    *   Function that contains all the drawing calls for the TFengine.
    **/
    void drawDefinition();

    /**!   
    *   Function that contains all the drawing calls for the histogram.
    **/
    void drawHistogram(SoState * state);

    /**!   
    *   Selects which hit in the hitRecord that is to be the selectedHit.
    **/
    int selectHit2BeActive(const int numHits);

    /**!   
    *   Function that controls the moving of points, lines and the whole primitve.
    *   Depending on what has been selected = what the selectedHit points to, different
    *   movement is applied.
    **/
    void primitiveMovement(float x, float y);

    /**!   
    *   Sets plausible default values to the primitive at the primitive index.
    **/
    void setDefaultValues2Primitive(/*XipTFPrimitiveShape primShape, int numPoints,
        int numIsoLevels, int numPointsInIsoLevel, XipTFPrimitiveType primType,*/ 
        int primIndex, float centerPointX = 0.5, float centerPointY = 0.5, int definitionSlot = -1);
    
    /**!   
    *   moves a point with += (x,y).
    **/
    bool movePoint(int pointIdx, float deltaX, float deltaY, bool adjustOverlap = true);
   
    /**!   
    *   update the LUT image.
    **/
    void updateLUT();

    /**!   
    *   set the values of fields if incorrect input.
    **/
    void checkFields();

    /**!   
    *   get an instance of a TF engine and insert some startup primitives.
    **/
    void createPrimitiveStructure(const char * name = "DEFAULT");

    /**!   
    *   function to generate the colors that are nearby and change the current color 
    *   at point pointIndex.
    **/
    void editColor(float xCoord, float yCoord, int pointIndex, int colorChannel2Edit);

    /**!   
    *   function to rotate a whole 2D primitve. The rotattion center will be point[0] in 
    *   the primitive. theta is specified in radians.
    **/
    void rotatePrim(float theta, int pointIndex = 0, int primIndex = -1);

    /**!   
    *   function to update the mask for drawing.
    **/
    void updateDrawingMask();

private:
    virtual ~SoXipTFEditor2D(); 
    void rotateXY(float &x, float &y, float theta);   
    void normalizeXY(float &x, float &y);
    bool areGraphicsPrimitivesStillConvex();
    bool checkConvexCW(const float ** data, int dataLength, int numPoints);
    void checkForGLError(const char* text);
    const float * interpolateValues(const float* val1, const float* val2, int numValues, float * result);
//    void getTexValues(); // TO DO REMOVE

    int mNodeId;
    int mTrackingID;
    int mDefinitionSlot;
    SbVec2s mViewportSize; 
    SbViewportRegion mViewport;

    int mNumSensors;    
    SoFieldSensor** mFieldSensors;             

    // mouse actions
    float mXCoordLastTime;
    float mYCoordLastTime;
    float mCoordButton1Pressed[2];
    float mCoordDiffFromHit[2];                 // keeps track of the position diff of click and real pos.
    float mCoordButton1PressedLastTime[2];
    float mCoordButton3Pressed[2];
    float mSensitivity[2];                      // So a skewed scaling won't effect the clickable area
    bool mMouseButton1Down;
    bool mMouseButton3Down;
    bool mInZoomedMode;
    bool mDrawZoomSquare;
    bool mDrawColorSquare;
    bool mUpdated;
    int mRenderCounter;
    SbTime mTimeOfLastClickButton1;             // double click effect
    SbTime mTime;

    float mCoordTranslation[3];
    float mCoordScaling[3];
    float mZoomCoordTranslation[3];
    float mZoomCoordScaling[3];

    // Selection
    float mSelectionColorLines[4];
    float mSelectionColorPoints[4];
    XipTFEngine* mTFEngine;
    XipTFIntersectRecord * mHitRecord;    
    XipTFPrimitive *mSelectedPrimitive; 
    XipTFIntersectRecord *mSelectedHit;
    int mSelectionFlags;

    int mNumHits;
    int * mSelectedGraphicsPrimID;
    int mSelectedHitIndex;
    bool mSelectionStarted;                     // to make sure all values are initialized correctly.
    
    // handles zoom mode
    float mZoomSquare[4];                       
    float mTranslationLastTime[2];              
    float mTranslationTotal[2];

    float mColorSquarePos[2];
    float mColorStep[2];    
    color_rgb_t<float> mNearSColorRGB;
    color_rgb_t<float> mNearEColorRGB;
    color_rgb_t<float> mNearNColorRGB;
    color_rgb_t<float> mNearWColorRGB;
    color_rgb_t<float> mFarSColorRGB; 
    color_rgb_t<float> mFarEColorRGB;
    color_rgb_t<float> mFarNColorRGB;
    color_rgb_t<float> mFarWColorRGB;
    color_rgb_t<float> mColorRGB;

    // Histogram 
    GLint mProgramHandle;
    bool mHistUpdated;
    GLuint mHistTexFormat;
    GLuint mHistInternalTexFormat;
    GLuint mHistWidth;
    GLuint mHistHeight;
    GLuint mHistDataType; 
    SbXipImage     * mHistImage;
    SoXipDataImage * mHistDataImage;
    unsigned int mHistTexID;

    // fields
    SoSFTrigger triggerUpdate;    
    SoSFTrigger addPrimitive;   
    SoSFEnum shape;
    SoSFEnum type;
    SoSFInt32 insertIndex; 
    SoSFInt32 coordinateDim;
    SoSFInt32 valueDim;
    SoSFInt32 numberOfPoints;
    SoSFInt32 numberOfIsoLevels;
    SoSFInt32 numberOfPointsInIsoLevel;

    SoSFTrigger removePrimitive;
    SoSFInt32 removeIndex;

    SoSFTrigger setPrimitiveColor;
    SoSFTrigger setPointColor;
    SoSFVec4f color2Set;
    SoSFVec4f selectedPtsColor;
    SoSFTrigger addPoint2Prim;
    SoSFTrigger removeSelPoint;
    SoSFTrigger moveSelPrimBack;
    SoSFTrigger moveSelPrimForw;
    SoSFTrigger rotatePrimitive;
    SoSFFloat radians2Rotate;

    SoSFInt32 definitionSlot2Use;
    SoSFTrigger addNewDefinition;
    
    SoSFVec2f windowDimensions;
    SoXipSFDataImage histImage;
    //SoXipSFDataImage histColor;

};


#endif //SO_XIP_TF_EDITOR_2D_H



