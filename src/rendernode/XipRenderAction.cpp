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


#include "XipRenderAction.h"

#include <xip/inventor/remote/XipRenderActionParams.h>
#include <xip/inventor/remote/XipRequestManager.h>
#include <xip/inventor/core/SoXipDataImage.h>
#include <xip/inventor/core/SbXipImage.h>
#include <Inventor/engines/SoEngine.h>
#include <Inventor/fields/SoSFNode.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoMFString.h>
#include <Inventor/fields/SoSFMatrix.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoSFShort.h>
#include <Inventor/fields/SoSFColor.h>
#include <xip/inventor/core/SoXipSFDataImage.h>
#include <xip/inventor/core/SoXipDataImage.h>
//#include <xip/inventor/core/SoXipTexture.h>
#include <xip/inventor/remote/losslessCompression/losslessCompression.h>

#include <iomanip>
#include <vector>

//static losslessCompression compressionObj;
static fastMemTransfer memTransfers;
/**
 *
 *	Default Constructor.
 *
 */
XipRenderAction::XipRenderAction()
: mRoot(NULL),
mOffScreenRenderer(NULL),
mImage(NULL),
mRenderNode(NULL),
mTrigger(NULL),
mVolumeData(NULL),
mDicomLoader(NULL),
mGraph(NULL),
mSwitch(NULL),
mVrtLut(NULL),
mMprLut(NULL),
mSlicer(NULL),
mCamera(NULL),
mCurrentRenderAction(ACTION_VRT_COLOR)
{
   	// initialize scene graph
	this->initialize();
}

/**
 *
 *	Default Destructor.
 *
 */
XipRenderAction::~XipRenderAction()
{
	// clean up
	this->terminate();
}

/**
 *
 *	Initialize data object.
 *
 */
void XipRenderAction::initialize()
{
    mRoot = readSceneGraph("offline_renderer.iv");
    if ( NULL==mRoot )
    {
        printf("The root node of the Scene graph is not initialized!\n");
        return;
    }
    mRoot->ref();

    mOffScreenRenderer = SoEngine::getByName("renderer");
    if ( NULL==mOffScreenRenderer )
    {
        return;
    }

    mImage = SoNode::getByName("image");
    if ( NULL==mImage )
    {
        return;
    }

    mGraph = readSceneGraph("..\\..\\graph\\renderer.iv");
    if ( NULL==mGraph )
    {
        return;
    }
	mGraph->ref();

    mDicomLoader = SoEngine::getByName("dicomLoader");
    if ( NULL==mDicomLoader )
    {
        return;
    }

    mVolumeData = SoEngine::getByName("volumeData");
    if ( NULL==mVolumeData )
    {
        return;
    }

	mVrtLut = SoNode::getByName(SbName("vrtLut"));
	if ( NULL==mVrtLut )
	{
		return;
	}

    mMprLut = SoNode::getByName(SbName("mprLut"));
    if ( NULL==mMprLut )
    {
        return;
    }

    mSwitch = SoNode::getByName(SbName("switch"));
    if ( NULL==mSwitch )
    {
        printf("Error: Switch node cannot be initialized!\n");
        return;
    }

    mSlicer = SoNode::getByName(SbName("slicer"));
    if ( NULL==mSlicer )
    {
        printf("Slicer node cannot be initialized!\n");
        return;
    }

    mCamera = (SoOrthographicCamera*)SoNode::getByName(SbName("camera"));
    if ( NULL==mCamera )
    {
        return;
    }

    mRenderNode = (SoSFNode*)mOffScreenRenderer->getField("node");
    if ( NULL==mRenderNode )
    {
        return;
    }
    mRenderNode->setValue(mGraph);

    mTrigger = (SoSFTrigger*)mOffScreenRenderer->getField("apply");
    if ( NULL==mTrigger )
    {
        return;
    }

    mTrigger->setValue();

    int temp;
    getOutput(temp);


    //SoSFNode* mprNode = (SoSFNode*)mMprOffRenderer->getField("node");
    //if ( NULL==mprNode )
    //{
    //    return;
    //}
    //mprNode->setValue(mMprGraph);


    //mMprTrigger = (SoSFTrigger*)mMprOffRenderer->getField("apply");
    //if ( NULL==mMprTrigger )
    //{
    //    return;
    //}
    //mMprTrigger->setValue();


    //SoXipSFDataImage* image = (SoXipSFDataImage*)mImage->getField("image");
    //if ( NULL==image )
    //{
    //    return;
    //}
    //SoXipDataImage* dataImage = image->getValue();
    //if ( NULL==dataImage )
    //{
    //    return;
    //}

    //SbXipImage * result = dataImage->get();
    //if ( NULL==result )
    //{
    //    return;
    //}

    //SbXipImageDimensions dim = result->getDimStored();
    //printf("%d %d %d\n", dim[0], dim[1], dim[2]);
    //printf("Datatype is %d\n", (int)result->getType());
    //printf("Layout is %d\n", (int)result->getComponentLayoutType());

    //UINT8* rgb = (UINT8*)result->refBufferPtr();

    //CImg<unsigned char> img(dim[0], dim[1], 1, 3, 0);
    //int idx=0;
    //cimg_forXY(img, x, y) 
    //{
    //    img(x, y, 0) = rgb[idx++];
    //    img(x, y, 1) = rgb[idx++];
    //    img(x, y, 2) = rgb[idx++];
    //}

    //img.save("C:\\Works\\test.bmp");
}

/**
 *
 *	Deletes the data object.
 *
 */
void XipRenderAction::terminate()
{
    //unload data
    loadDicom("");
    mTrigger->setValue();
    int bufsize;
    getOutput(bufsize);

    if ( mGraph ) 
    {
        mGraph->unref();
        mGraph = NULL;
    }

    if ( mRoot ) 
    {
        mRoot->unref();
        mRoot = NULL;
    }
}

/**
 *	
 *	Does volume rendering. After rendering it returns the image buffer.
 *
 *	\param	requestRecv	Class holding the render action request parameters.
 *	\param	buffer	Pointer to the output image data buffer.
 *
 *	\return	size of the output image buffer
 *
 */
int XipRenderAction::renderVolume(XipTreeRequestReceiver &reqReceiver, unsigned char* &buffer)
{
    //Reading rendering parameters

    int rcWidth, rcHeight;
    bool resRCW = reqReceiver.getUniqueIntElement(RENDERACTION_RCWIDTH, rcWidth);
    bool resRCH = reqReceiver.getUniqueIntElement(RENDERACTION_RCHEIGHT, rcHeight);

    if (resRCW ) 
    {
        reqReceiver.rNtohl(&rcWidth);
        setWindowWidth(mOffScreenRenderer, rcWidth);
    }

    if ( resRCH )
    {
        reqReceiver.rNtohl(&rcHeight);
        setWindowHeight(mOffScreenRenderer, rcHeight);
    }

    short renderMode;
    bool resRM = reqReceiver.getUniqueShortElement(RENDERACTION_RENDERMODE, renderMode);
    reqReceiver.rNtohs(&renderMode);

    setMode(renderMode);

    float temp[4];
#ifdef WIN64
    memcpy((unsigned char *)&temp[0], (unsigned char *)reqReceiver.getElementContent(RENDERACTION_CAMERA_POSITION, 3*sizeof(float)),3*sizeof(float));
#else // WIN64
    memTransfers.fastMemcopy((unsigned char *)&temp[0], (unsigned char *)reqReceiver.getElementContent(RENDERACTION_CAMERA_POSITION, 3*sizeof(float)),3*sizeof(float));
#endif // WIN64
    reqReceiver.rSwapf(temp, 3);
    SbVec3f pos(temp[0], temp[1], temp[2]);
    printf("received pos=%f %f %f\n", temp[0], temp[1], temp[2]);

#ifdef WIN64
    memcpy((unsigned char *)&temp[0], (unsigned char *)reqReceiver.getElementContent(RENDERACTION_CAMERA_ORIENTATION, 4*sizeof(float)),4*sizeof(float));
#else // WIN64
    memTransfers.fastMemcopy((unsigned char *)&temp[0], (unsigned char *)reqReceiver.getElementContent(RENDERACTION_CAMERA_ORIENTATION, 4*sizeof(float)),4*sizeof(float));
#endif // WIN64
    reqReceiver.rSwapf(temp, 4);
    SbRotation rot(temp);
    printf("received ori=%f %f %f %f\n", temp[0], temp[1], temp[2], temp[3]);

#ifdef WIN64
    memcpy((unsigned char *)&temp[0], (unsigned char *)reqReceiver.getElementContent(RENDERACTION_CAMERA_RATIO, sizeof(float)), sizeof(float));
#else // WIN64
    memTransfers.fastMemcopy((unsigned char *)&temp[0], (unsigned char *)reqReceiver.getElementContent(RENDERACTION_CAMERA_RATIO, sizeof(float)), sizeof(float));
#endif // WIN64
    reqReceiver.rSwapf(temp);
    float ratio = temp[0];
   
#ifdef WIN64
    memcpy((unsigned char *)&temp[0], (unsigned char *)reqReceiver.getElementContent(RENDERACTION_CAMERA_NEARDIST, sizeof(float)), sizeof(float));
#else // WIN64
    memTransfers.fastMemcopy((unsigned char *)&temp[0], (unsigned char *)reqReceiver.getElementContent(RENDERACTION_CAMERA_NEARDIST, sizeof(float)), sizeof(float));
#endif // WIN64
    reqReceiver.rSwapf(temp);
    float zNear = temp[0];

#ifdef WIN64
    memcpy((unsigned char *)&temp[0], (unsigned char *)reqReceiver.getElementContent(RENDERACTION_CAMERA_FARDIST, sizeof(float)), sizeof(float));
#else // WIN64
    memTransfers.fastMemcopy((unsigned char *)&temp[0], (unsigned char *)reqReceiver.getElementContent(RENDERACTION_CAMERA_FARDIST, sizeof(float)), sizeof(float));
#endif // WIN64
    reqReceiver.rSwapf(temp);
    float zFar = temp[0];

#ifdef WIN64
    memcpy((unsigned char *)&temp[0], (unsigned char *)reqReceiver.getElementContent(RENDERACTION_CAMERA_HEIGHT, sizeof(float)), sizeof(float));
#else // WIN64
    memTransfers.fastMemcopy((unsigned char *)&temp[0], (unsigned char *)reqReceiver.getElementContent(RENDERACTION_CAMERA_HEIGHT, sizeof(float)), sizeof(float));
#endif // WIN64
    reqReceiver.rSwapf(temp);
    float height = temp[0];

    mCamera->position.setValue(pos);
    mCamera->orientation.setValue(rot);

    printf("Position: %f %f %f\n", pos[0], pos[1], pos[2]);
    const float* ptr = rot.getValue();
    printf("Rotation: %f %f %f %f\n", ptr[0], ptr[1], ptr[2], ptr[3]);

    mCamera->nearDistance.setValue(zNear);
    mCamera->farDistance.setValue(zFar);

    mCamera->aspectRatio.setValue(ratio);
    mCamera->height.setValue(height);
    mCamera->touch();

    int bufferSize = 0;	
    mTrigger->setValue();
    buffer = getOutput(bufferSize);
	return bufferSize;
}

SoSeparator* XipRenderAction::readSceneGraph(const char* filename)
{
    SoInput sceneInput;
    if ( !sceneInput.openFile(filename) )
    {
        printf("Cannot open scene graph file %s\n", filename);
        return NULL;
    }

    SoSeparator* root = SoDB::readAll(&sceneInput);
    if ( NULL==root )
    {
        printf("Problem reading scene graph file %s\n", filename);
        sceneInput.closeFile();
        return NULL;
    }

    sceneInput.closeFile();

    return root;
}

unsigned char* XipRenderAction::getOutput(int &bufSize)
{
    bufSize = 0;

    if ( NULL==mImage ) return NULL;

    SoXipSFDataImage* imageField = (SoXipSFDataImage*)mImage->getField("image");
    if ( NULL==imageField )
    {
        printf("Error: image is null\n");
        return NULL;
    }
    SoXipDataImage* dataImage = imageField->getValue();
    if ( NULL==dataImage )
    {
        printf("Error: data image is null\n");
        return NULL;
    }

    SbXipImage * result = dataImage->get();
    if ( NULL==result )
    {
        printf("result is null!\n");
        return NULL;
    }

    SbXipImageDimensions dim = result->getDimStored();

    bufSize = result->getComponents()*dim[0]*dim[1];

    unsigned char* src = (unsigned char*)result->refBufferPtr();

    return (unsigned char*)result->refBufferPtr();
}

void XipRenderAction::setWindowWidth(SoEngine* renderer, int w)
{
    SoSFInt32* width = (SoSFInt32*)renderer->getField("width");

    if ( NULL==width ) return;

    if ( width->getValue()!=w ) width->setValue(w);
}

void XipRenderAction::setWindowHeight(SoEngine* renderer, int h)
{
    SoSFInt32* height = (SoSFInt32*)renderer->getField("height");

    if ( NULL==height ) return;

    if ( height->getValue()!=h ) height->setValue(h);
}

void XipRenderAction::setMatrix(SoNode* matrixNode, float *m)
{
    if ( NULL==matrixNode ) return;

    SbMatrix mat(
        m[0], m[1], m[2], m[3],
        m[4], m[5], m[6], m[7], 
        m[8], m[9], m[10], m[11],
        m[12], m[13], m[14], m[15]);

    printf("%f %f %f %f\n", m[0], m[1], m[2], m[3]);
    printf("%f %f %f %f\n", m[4], m[5], m[6], m[7]);
    printf("%f %f %f %f\n", m[8], m[9], m[10], m[11]);
    printf("%f %f %f %f\n", m[12], m[13], m[14], m[15]);
    printf("\n");

    SoSFMatrix* matrix = (SoSFMatrix*)matrixNode->getField(SbName("matrix"));
    if ( matrix ) matrix->setValue(mat);
}

void XipRenderAction::getModelMatrix(float *m)
{
    SoNode* volTex = SoNode::getByName(SbName("volumeTexture"));
    if ( NULL==volTex )
    {
        return;
    }

    SoXipSFDataImage* imageField = (SoXipSFDataImage*)volTex->getField(SbName("image"));

    if ( NULL==imageField ) return;

    SoXipDataImage* dataImage = imageField->getValue();
    if ( NULL==dataImage ) return;

    SbXipImage* image = dataImage->get();
    if ( NULL==image ) return;

    SbMatrix mat = image->getModelMatrix();
    float *ptr = mat.operator float *();

    for (int i=0; i<16; i++)
    {
        m[i] = ptr[i];
    }
}

void XipRenderAction::loadDicom(const char* location)
{
    if ( NULL==mDicomLoader ) return;

    SoMFString* name = (SoMFString*)mDicomLoader->getField(SbName("name"));
    if ( NULL!=name )
    {
        name->setValue(SbString(location));
        mDicomLoader->touch();
        int temp;
        getOutput(temp);
    }
}

void XipRenderAction::setLutRampWidth(float width)
{
	if ( NULL==mVrtLut ) return;

	SoSFFloat* rampWidth = (SoSFFloat*)mVrtLut->getField(SbName("rampWidth"));
	if ( NULL!=rampWidth )
	{
		rampWidth->setValue(width);
		mVrtLut->touch();
	}

}

void XipRenderAction::setLutRampCenter(float center)
{
	if ( NULL==mVrtLut ) return;

	SoSFFloat* rampCenter = (SoSFFloat*)mVrtLut->getField(SbName("rampCenter"));
	if ( NULL!=rampCenter )
	{
		rampCenter->setValue(center);
		mVrtLut->touch();
	}
}

void XipRenderAction::setMode(short mode)
{
    if ( (NULL==mSlicer) || (NULL==mSwitch) || (mMode==mode)) return;

    if ( mode==XIP_RENDERMODE_MPR )
    {
        mMode = mode;
        SoSFEnum *modeField = (SoSFEnum*)mSlicer->getField(SbName("mode"));
        if ( NULL!=modeField )
        {
            modeField->setValue(0);
        }
        SoSFInt32 *childField = (SoSFInt32*)mSwitch->getField(SbName("whichChild"));
        if ( NULL!=childField )
        {
            childField->setValue(1);
        }
    }
    else if ( mode==XIP_RENDERMODE_VRT_COLOR )
    {
        mMode = mode;
        SoSFEnum *modeField = (SoSFEnum*)mSlicer->getField(SbName("mode"));
        if ( NULL!=modeField )
        {
            modeField->setValue(5);
        }

        SoSFInt32 *childField = (SoSFInt32*)mSwitch->getField(SbName("whichChild"));
        if ( NULL!=childField )
        {
            childField->setValue(0);
        }
    }
    else
    {
        printf("Error: unsupport rendering mode!\n");
    }
}

int XipRenderAction::setLut(XipTreeRequestReceiver &reqReceiver)
{
    // Get the name of lut
    int len = 0;
    bool res = reqReceiver.getUniqueIntElement(LUTACTION_LUTNAMESIZE, len);
    if ( !res ) return 0;
    
    reqReceiver.rNtohl(&len);
    if ( len<2 ) return 0;

    char* lutName = reqReceiver.getElementContent(LUTACTION_LUTNAME, len);

    SoNode* lut = SoNode::getByName(SbName(lutName));
    if ( NULL==lut ) return 0;

    // check input mode
    int ival;
    res = reqReceiver.getUniqueIntElement(LUTACTION_INPUTMODE, ival);
    if ( res )
    {
        reqReceiver.rNtohl(&ival);
        SoSFEnum* inputMode = (SoSFEnum*)lut->getField(SbName("inputMode"));
        if ( inputMode ) inputMode->setValue(ival);
    }

    // check alpha mode
    res = reqReceiver.getUniqueIntElement(LUTACTION_ALPHAMODE, ival);
    if ( res )
    {
        reqReceiver.rNtohl(&ival);
        SoSFEnum* alphaMode = (SoSFEnum*)lut->getField(SbName("alphaMode"));
        if ( alphaMode ) alphaMode->setValue(ival);
    }

    // check file mode
    res = reqReceiver.getUniqueIntElement(LUTACTION_FILEMODE, ival);
    if ( res )
    {
        reqReceiver.rNtohl(&ival);
        SoSFEnum* fileMode = (SoSFEnum*)lut->getField(SbName("fileMode"));
        if ( fileMode ) fileMode->setValue(ival);
    }

    res = reqReceiver.getUniqueIntElement(LUTACTION_OUTPUTMODE, ival);
    if ( res )
    {
        reqReceiver.rNtohl(&ival);
        SoSFEnum* outputMode = (SoSFEnum*)lut->getField(SbName("outputMode"));
        if ( outputMode ) outputMode->setValue(ival);
    }

    short sval;
    // check bitsused
    res = reqReceiver.getUniqueShortElement(LUTACTION_BITSUSED, sval);
    if ( res )
    {
        reqReceiver.rNtohs(&sval);
        SoSFShort* bitsUsed = (SoSFShort*)lut->getField(SbName("bitsUsed"));
        if ( bitsUsed ) bitsUsed->setValue(sval);
    }

    float fval;
    // check rampWidth
    res = reqReceiver.getUniqueFloatElement(LUTACTION_RAMPWIDTH, fval);
    if ( res )
    {
        reqReceiver.rSwapf(&fval);
        SoSFFloat* rampWidth = (SoSFFloat*)lut->getField(SbName("rampWidth"));
        if ( rampWidth ) rampWidth->setValue(fval);
    }

    // check rampCenter
    res = reqReceiver.getUniqueFloatElement(LUTACTION_RAMPCENTER, fval);
    if ( res )
    {
        reqReceiver.rSwapf(&fval);
        SoSFFloat* rampWidth = (SoSFFloat*)lut->getField(SbName("rampCenter"));
        if ( rampWidth ) rampWidth->setValue(fval);
    }

    // check alphaFactor
    res = reqReceiver.getUniqueFloatElement(LUTACTION_ALPHAFACTOR, fval);
    if ( res )
    {
        reqReceiver.rSwapf(&fval);
        SoSFFloat* rampWidth = (SoSFFloat*)lut->getField(SbName("alphaFactor"));
        if ( rampWidth ) rampWidth->setValue(fval);
    }

    // check slopeWidth
    res = reqReceiver.getUniqueFloatElement(LUTACTION_SLOPEWIDTH, fval);
    if ( res )
    {
        reqReceiver.rSwapf(&fval);
        SoSFFloat* slopeWidth = (SoSFFloat*)lut->getField(SbName("slopeWidth"));
        if ( slopeWidth ) slopeWidth->setValue(fval);
    }

    // check slopeCenter
    res = reqReceiver.getUniqueFloatElement(LUTACTION_SLOPECENTER, fval);
    if ( res )
    {
        reqReceiver.rSwapf(&fval);
        SoSFFloat* slopeCenter = (SoSFFloat*)lut->getField(SbName("slopeCenter"));
        if ( slopeCenter ) slopeCenter->setValue(fval);
    }

    // check bottom color
    float* color = (float*)reqReceiver.getElementContent(LUTACTION_COLORBOTTOM, 3*sizeof(float));
    if ( color )
    {
        reqReceiver.rSwapf(color, 3);
        SoSFColor* colorBottom = (SoSFColor*)lut->getField(SbName("colorBottom"));
        if ( colorBottom ) colorBottom->setValue(color);
    }

    // check middle color
    color = (float*)reqReceiver.getElementContent(LUTACTION_COLORMIDDLE, 3*sizeof(float));
    if ( color )
    {
        reqReceiver.rSwapf(color, 3);
        SoSFColor* colorMiddle = (SoSFColor*)lut->getField(SbName("colorMiddle"));
        if ( colorMiddle ) colorMiddle->setValue(color);
    }

    // check top color
    color = (float*)reqReceiver.getElementContent(LUTACTION_COLORTOP, 3*sizeof(float));
    if ( color )
    {
        reqReceiver.rSwapf(color, 3);
        SoSFColor* colorTop = (SoSFColor*)lut->getField(SbName("colorTop"));
        if ( colorTop ) colorTop->setValue(color);
    }

    // check lut filename
    res = reqReceiver.getUniqueIntElement(LUTACTION_FILENAMESIZE, len);
    if ( res )
    {
        reqReceiver.rNtohl(&len);
        if ( len>1 )
        {
            char *filename = reqReceiver.getElementContent(LUTACTION_FILENAME, len);
            if ( filename )
            {
                SoSFString* fileIn = (SoSFString*)lut->getField(SbName("fileIn"));
                if ( fileIn ) fileIn->setValue(filename);
            }

        }
        else
        {
            SoSFString* fileIn = (SoSFString*)lut->getField(SbName("fileIn"));
            if ( fileIn ) fileIn->setValue(SbString(""));
        }
    }
    //else
    //{
    //    SoSFString* fileIn = (SoSFString*)lut->getField(SbName("fileIn"));
    //    if ( fileIn ) fileIn->setValue(SbString(""));
    //}

    // check lut entries
    res = reqReceiver.getUniqueIntElement(LUTACTION_FILEENTRIES, ival);
    if ( res )
    {
        reqReceiver.rNtohl(&ival);
        SoSFInt32* fileEntries = (SoSFInt32*)lut->getField(SbName("fileEntries"));
        if ( fileEntries ) fileEntries->setValue(ival);
    }

    lut->touch();

    return 1;
}
