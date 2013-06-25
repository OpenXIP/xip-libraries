/*
Copyright (c) 2011, Siemens Corporate Research a Division of Siemens Corporation 
All rights reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
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
