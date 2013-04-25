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

#include "SoXipRemoteLut.h"
#include <Inventor/actions/SoGLRenderAction.h>
#include "SoXipClientElement.h"

SO_NODE_SOURCE(SoXipRemoteLut);

SoXipRemoteLut::SoXipRemoteLut()
{
    SO_NODE_CONSTRUCTOR(SoXipRemoteLut);

	/////////////////////////////////////

	SO_NODE_DEFINE_ENUM_VALUE(InputType, RAMP);
	SO_NODE_DEFINE_ENUM_VALUE(InputType, TRAPEZOID);
	SO_NODE_DEFINE_ENUM_VALUE(InputType, FILE);
	SO_NODE_DEFINE_ENUM_VALUE(InputType, ARRAY);
	SO_NODE_DEFINE_ENUM_VALUE(InputType, RAMP_FILE);
	SO_NODE_SET_SF_ENUM_TYPE(inputMode, InputType);
	SO_NODE_ADD_FIELD( inputMode, (RAMP) );

	SO_NODE_DEFINE_ENUM_VALUE(AlphaType, DEFAULT);
	SO_NODE_DEFINE_ENUM_VALUE(AlphaType, CONSTANT);
	SO_NODE_DEFINE_ENUM_VALUE(AlphaType, INTENSITY);
	SO_NODE_DEFINE_ENUM_VALUE(AlphaType, RAMP_MINMAX);
	SO_NODE_DEFINE_ENUM_VALUE(AlphaType, STEP_RAMP);
	SO_NODE_DEFINE_ENUM_VALUE(AlphaType, STEP_CENTER);
	SO_NODE_DEFINE_ENUM_VALUE(AlphaType, STEP_SECOND);
	SO_NODE_SET_SF_ENUM_TYPE(alphaMode, AlphaType);
	SO_NODE_ADD_FIELD( alphaMode, (DEFAULT) );

	SO_NODE_DEFINE_ENUM_VALUE(FileType, FLOAT_COMMA);
	SO_NODE_DEFINE_ENUM_VALUE(FileType, FLOAT_SPACE);
	SO_NODE_DEFINE_ENUM_VALUE(FileType, BYTE_COMMA);
	SO_NODE_DEFINE_ENUM_VALUE(FileType, BYTE_SPACE);
	SO_NODE_SET_SF_ENUM_TYPE(fileMode, FileType);
	SO_NODE_ADD_FIELD(fileMode, (BYTE_SPACE));

	SO_NODE_DEFINE_ENUM_VALUE(OutputType, COLOR_ALPHA);
	SO_NODE_DEFINE_ENUM_VALUE(OutputType, COLOR);
	SO_NODE_DEFINE_ENUM_VALUE(OutputType, LUMINANCE);
	SO_NODE_SET_SF_ENUM_TYPE(outputMode, OutputType);
	SO_NODE_ADD_FIELD(outputMode, (COLOR_ALPHA));

	SO_NODE_ADD_FIELD( bitsUsed, (0) );
//	SO_NODE_ADD_FIELD( constantAlpha, (FALSE));

	SO_NODE_ADD_FIELD( rampWidth, (1.f) );
	SO_NODE_ADD_FIELD( rampCenter, (0.5f) );
	SO_NODE_ADD_FIELD( alphaFactor, (1.f) );
	SO_NODE_ADD_FIELD( slopeWidth, (1.f) );
	SO_NODE_ADD_FIELD( slopeCenter, (0.5f) );
	SO_NODE_ADD_FIELD( colorBottom, (SbColor(0, 0, 0)) );
	SO_NODE_ADD_FIELD( colorMiddle, (SbColor(0.5, 0.5, 0.5)) );
	SO_NODE_ADD_FIELD( colorTop, (SbColor(1, 1, 1)) );

	SO_NODE_ADD_FIELD( fileIn, ("") );
	SO_NODE_ADD_FIELD( fileEntries, (0) );
	/////////////////////////////////////

    SO_NODE_ADD_FIELD(lutName, (SbString()));
    SO_NODE_ADD_FIELD(connection, (NULL));

    mStream = NULL;

    m_bHasChangedValues = false;

    SoFieldSensor *fieldSensor=NULL;
    SoField *fields[] = {&inputMode, &alphaMode, &fileMode, &outputMode, &bitsUsed, &rampWidth, &rampCenter,
                         &alphaFactor, &slopeWidth, &slopeCenter, &colorBottom, &colorMiddle,
                         &colorTop, &fileIn, &fileEntries, &lutName, &connection};
    for (int i=0; i<(sizeof(fields)/sizeof(SoField*)); i++)
    {
        fieldSensor = new SoFieldSensor(&fieldSensorCBFunc, this);
        fieldSensor->attach(fields[i]);
        mInputSensors.push_back(fieldSensor);
    }
}

SoXipRemoteLut::~SoXipRemoteLut()
{
    std::vector<SoFieldSensor *>::iterator i;
    for (i = mInputSensors.begin(); i != mInputSensors.end(); i++)
    {
        delete (*i);
    }
}

void SoXipRemoteLut::initClass()
{
    SO_NODE_INIT_CLASS(SoXipRemoteLut, SoNode, "Node");

    SO_ENABLE(SoGLRenderAction, SoXipClientElement);
}

void SoXipRemoteLut::fieldSensorCBFunc(void *usr, SoSensor *sensor)
{
    ((SoXipRemoteLut*)usr)->inputChanged(((SoFieldSensor*) sensor)->getAttachedField());
}

void SoXipRemoteLut::inputChanged(SoField *whichField)
{
    if ( whichField==&inputMode )
    {
        sendInputMode();
    }
    else if ( whichField==&alphaMode )
    {
        sendAlphaMode();
    }
    else if ( whichField==&fileMode )
    {
        sendFileMode();
    }
    else if ( whichField==&outputMode )
    {
        sendOutputMode();
    }
    else if ( whichField==&bitsUsed )
    {
        sendBitsUsed();
    }
    else if ( whichField==&rampWidth )
    {
        sendRampWidth();
    }
    else if ( whichField==&rampCenter )
    {
        sendRampCenter();
    }
    else if ( whichField==&alphaFactor )
    {
        sendAlphaFactor();
    }
    else if ( whichField==&slopeWidth )
    {
        sendSlopeWidth();
    }
    else if ( whichField==&slopeCenter )
    {
        sendSlopeCenter();
    }
    else if ( whichField==&colorBottom )
    {
        sendColorBottom();
    }
    else if ( whichField==&colorMiddle )
    {
        sendColorMiddle();
    }
    else if ( whichField==&colorTop )
    {
        sendColorTop();
    }
    else if ( whichField==&fileIn )
    {
        sendFileIn();
    }
    else if ( whichField==&fileEntries )
    {
        sendFileEntries();
    }
    else if ( whichField==&lutName )
    {

    }
    else if ( whichField==&connection )
    {
        XipStreamBase *Stream = 0;

        SoXipDataConnection *vol = connection.getValue();
        if(vol)
        {
            XipDataConnection * sVol = vol->get();
            if(sVol)
            {
                Stream = sVol->mStream;
            }
        }

        if(mStream != Stream)
        {
            mStream = Stream;
            if ( NULL!=mStream )
            {
                sendAll();
            }
        }
    }
}

int SoXipRemoteLut::sendAll()
{
    if ( lutName.getValue()==SbString("") ) return -1;

    mReqSender.initSender(mStream, LUT_ACTION);

    //lut name on the server side
    const SbString& lutname = lutName.getValue();
    int lutnamelen = lutname.getLength()+1;
    mReqSender.rHtonl(&lutnamelen);
    mReqSender.addChildElement(LUT_ACTION, LUTACTION_LUTNAMESIZE, sizeof(int), &lutnamelen);
    mReqSender.addChildElement(LUT_ACTION, LUTACTION_LUTNAME, lutname.getLength()+1, (void*)lutname.getString());

    //inputMode
    int imode = inputMode.getValue();
    mReqSender.rHtonl(&imode);
    mReqSender.addChildElement(LUT_ACTION, LUTACTION_INPUTMODE, sizeof(int), &imode);

    //alphaMode
    int amode = alphaMode.getValue();
    mReqSender.rHtonl(&amode);
    mReqSender.addChildElement(LUT_ACTION, LUTACTION_ALPHAMODE, sizeof(int), &amode);

    //fileMode
    int fmode = fileMode.getValue();
    mReqSender.rHtonl(&fmode);
    mReqSender.addChildElement(LUT_ACTION, LUTACTION_FILEMODE, sizeof(int), &fmode);

    //outputMode
    int omode = outputMode.getValue();
    mReqSender.rHtonl(&omode);
    mReqSender.addChildElement(LUT_ACTION, LUTACTION_OUTPUTMODE, sizeof(int), &omode);

    short bits = bitsUsed.getValue();
    mReqSender.rHtons(&bits);
    mReqSender.addChildElement(LUT_ACTION, LUTACTION_BITSUSED, sizeof(short), &bits);

    float rw = rampWidth.getValue();
    mReqSender.rSwapf(&rw);
    mReqSender.addChildElement(LUT_ACTION, LUTACTION_RAMPWIDTH, sizeof(float), &rw);

    float rc = rampCenter.getValue();
    mReqSender.rSwapf(&rc);
    mReqSender.addChildElement(LUT_ACTION, LUTACTION_RAMPCENTER, sizeof(float), &rc);

    float af = alphaFactor.getValue();
    mReqSender.rSwapf(&af);
    mReqSender.addChildElement(LUT_ACTION, LUTACTION_ALPHAFACTOR, sizeof(float), &af);

    float sw = slopeWidth.getValue();
    mReqSender.rSwapf(&sw);
    mReqSender.addChildElement(LUT_ACTION, LUTACTION_SLOPEWIDTH, sizeof(float), &sw);

    float sc = slopeCenter.getValue();
    mReqSender.rSwapf(&sc);
    mReqSender.addChildElement(LUT_ACTION, LUTACTION_SLOPECENTER, sizeof(float), &sc);

    float bc[3];
    memcpy(bc, colorBottom.getValue().getValue(), sizeof(float)*3);
    mReqSender.rSwapf(bc);
    mReqSender.addChildElement(LUT_ACTION, LUTACTION_COLORBOTTOM, 3*sizeof(float), bc);

    float mc[3];
    memcpy(mc, colorMiddle.getValue().getValue(), sizeof(float)*3);
    mReqSender.rSwapf(mc);
    mReqSender.addChildElement(LUT_ACTION, LUTACTION_COLORBOTTOM, 3*sizeof(float), mc);

    float tc[3];
    memcpy(tc, colorTop.getValue().getValue(), sizeof(float)*3);
    mReqSender.rSwapf(tc);
    mReqSender.addChildElement(LUT_ACTION, LUTACTION_COLORBOTTOM, 3*sizeof(float), tc);

    const SbString& filename = fileIn.getValue();
    int filenamelen = filename.getLength()+1;
    mReqSender.rHtonl(&filenamelen);
    mReqSender.addChildElement(LUT_ACTION, LUTACTION_FILENAMESIZE, sizeof(int), &filenamelen);
    mReqSender.addChildElement(LUT_ACTION, LUTACTION_FILENAME, filename.getLength()+1, (void*)filename.getString());

    int entries = fileEntries.getValue();
    mReqSender.rHtonl(&entries);
    mReqSender.addChildElement(LUT_ACTION, LUTACTION_FILEENTRIES, sizeof(int), &entries);
    mReqSender.send();

    // expect the validation response from the server
    mReqReceiver.initReceiver(mStream);
    mReqReceiver.receive();
    if(mReqReceiver.getFirstElementId() != LUT_ACTION)
        return -1;

    int done=0;
    bool res = mReqReceiver.getUniqueIntElement(LUTACTIONRESPONSE_DONE, done);
    
    if ( res )
    {
        mReqReceiver.rNtohl(&done);
        if ( done==1 )
        {
            this->update();
            return 0;
        }
    }

    return -1;
}

int SoXipRemoteLut::sendInputMode()
{
    if ( lutName.getValue()==SbString("") || (NULL==mStream)) return -1;

    mReqSender.initSender(mStream, LUT_ACTION);

    //lut name on the server side
    const SbString& lutname = lutName.getValue();
    int lutnamelen = lutname.getLength()+1;
    mReqSender.rHtonl(&lutnamelen);
    mReqSender.addChildElement(LUT_ACTION, LUTACTION_LUTNAMESIZE, sizeof(int), &lutnamelen);
    mReqSender.addChildElement(LUT_ACTION, LUTACTION_LUTNAME, lutname.getLength()+1, (void*)lutname.getString());

    //inputMode
    int imode = inputMode.getValue();
    mReqSender.rHtonl(&imode);
    mReqSender.addChildElement(LUT_ACTION, LUTACTION_INPUTMODE, sizeof(int), &imode);

    mReqSender.send();

    // expect the validation response from the server
    mReqReceiver.initReceiver(mStream);
    mReqReceiver.receive();
    if(mReqReceiver.getFirstElementId() != LUT_ACTION)
        return -1;

    int done=0;
    bool res = mReqReceiver.getUniqueIntElement(LUTACTIONRESPONSE_DONE, done);

    if ( res )
    {
        mReqReceiver.rNtohl(&done);
        if ( done==1 )
        {
            this->update();
            return 0;
        }
    }

    return -1;
}

int SoXipRemoteLut::sendAlphaMode()
{
    if ( lutName.getValue()==SbString("") || (NULL==mStream)) return -1;

    mReqSender.initSender(mStream, LUT_ACTION);

    //lut name on the server side
    const SbString& lutname = lutName.getValue();
    int lutnamelen = lutname.getLength()+1;
    mReqSender.rHtonl(&lutnamelen);
    mReqSender.addChildElement(LUT_ACTION, LUTACTION_LUTNAMESIZE, sizeof(int), &lutnamelen);
    mReqSender.addChildElement(LUT_ACTION, LUTACTION_LUTNAME, lutname.getLength()+1, (void*)lutname.getString());

    //alphaMode
    int amode = alphaMode.getValue();
    mReqSender.rHtonl(&amode);
    mReqSender.addChildElement(LUT_ACTION, LUTACTION_ALPHAMODE, sizeof(int), &amode);

    mReqSender.send();

    // expect the validation response from the server
    mReqReceiver.initReceiver(mStream);
    mReqReceiver.receive();
    if(mReqReceiver.getFirstElementId() != LUT_ACTION)
        return -1;

    int done=0;
    bool res = mReqReceiver.getUniqueIntElement(LUTACTIONRESPONSE_DONE, done);

    if ( res )
    {
        mReqReceiver.rNtohl(&done);
        if ( done==1 )
        {
            this->update();
            return 0;
        }
    }

    return -1;
}

int SoXipRemoteLut::sendFileMode()
{
    if ( lutName.getValue()==SbString("") || (NULL==mStream)) return -1;

    mReqSender.initSender(mStream, LUT_ACTION);

    //lut name on the server side
    const SbString& lutname = lutName.getValue();
    int lutnamelen = lutname.getLength()+1;
    mReqSender.rHtonl(&lutnamelen);
    mReqSender.addChildElement(LUT_ACTION, LUTACTION_LUTNAMESIZE, sizeof(int), &lutnamelen);
    mReqSender.addChildElement(LUT_ACTION, LUTACTION_LUTNAME, lutname.getLength()+1, (void*)lutname.getString());

    //fileMode
    int fmode = fileMode.getValue();
    mReqSender.rHtonl(&fmode);
    mReqSender.addChildElement(LUT_ACTION, LUTACTION_FILEMODE, sizeof(int), &fmode);
    mReqSender.send();

    // expect the validation response from the server
    mReqReceiver.initReceiver(mStream);
    mReqReceiver.receive();
    if(mReqReceiver.getFirstElementId() != LUT_ACTION)
        return -1;

    int done=0;
    bool res = mReqReceiver.getUniqueIntElement(LUTACTIONRESPONSE_DONE, done);

    if ( res )
    {
        mReqReceiver.rNtohl(&done);
        if ( done==1 )
        {
            this->update();
            return 0;
        }
    }

    return -1;
}

int SoXipRemoteLut::sendOutputMode()
{
    if ( lutName.getValue()==SbString("") || (NULL==mStream)) return -1;

    mReqSender.initSender(mStream, LUT_ACTION);

    //lut name on the server side
    const SbString& lutname = lutName.getValue();
    int lutnamelen = lutname.getLength()+1;
    mReqSender.rHtonl(&lutnamelen);
    mReqSender.addChildElement(LUT_ACTION, LUTACTION_LUTNAMESIZE, sizeof(int), &lutnamelen);
    mReqSender.addChildElement(LUT_ACTION, LUTACTION_LUTNAME, lutname.getLength()+1, (void*)lutname.getString());

    //outputMode
    int omode = outputMode.getValue();
    mReqSender.rHtonl(&omode);
    mReqSender.addChildElement(LUT_ACTION, LUTACTION_OUTPUTMODE, sizeof(int), &omode);
    mReqSender.send();

    // expect the validation response from the server
    mReqReceiver.initReceiver(mStream);
    mReqReceiver.receive();
    if(mReqReceiver.getFirstElementId() != LUT_ACTION)
        return -1;

    int done=0;
    bool res = mReqReceiver.getUniqueIntElement(LUTACTIONRESPONSE_DONE, done);

    if ( res )
    {
        mReqReceiver.rNtohl(&done);
        if ( done==1 )
        {
            this->update();
            return 0;
        }
    }

    return -1;
}

int SoXipRemoteLut::sendBitsUsed()
{
    if ( lutName.getValue()==SbString("") || (NULL==mStream)) return -1;

    mReqSender.initSender(mStream, LUT_ACTION);

    //lut name on the server side
    const SbString& lutname = lutName.getValue();
    int lutnamelen = lutname.getLength()+1;
    mReqSender.rHtonl(&lutnamelen);
    mReqSender.addChildElement(LUT_ACTION, LUTACTION_LUTNAMESIZE, sizeof(int), &lutnamelen);
    mReqSender.addChildElement(LUT_ACTION, LUTACTION_LUTNAME, lutname.getLength()+1, (void*)lutname.getString());

    short bits = bitsUsed.getValue();
    mReqSender.rHtons(&bits);
    mReqSender.addChildElement(LUT_ACTION, LUTACTION_BITSUSED, sizeof(short), &bits);
    mReqSender.send();

    // expect the validation response from the server
    mReqReceiver.initReceiver(mStream);
    mReqReceiver.receive();
    if(mReqReceiver.getFirstElementId() != LUT_ACTION)
        return -1;

    int done=0;
    bool res = mReqReceiver.getUniqueIntElement(LUTACTIONRESPONSE_DONE, done);

    if ( res )
    {
        mReqReceiver.rNtohl(&done);
        if ( done==1 )
        {
            this->update();
            return 0;
        }
    }

    return -1;
}

int SoXipRemoteLut::sendRampWidth()
{
    if ( lutName.getValue()==SbString("") || (NULL==mStream)) return -1;

    mReqSender.initSender(mStream, LUT_ACTION);

    //lut name on the server side
    const SbString& lutname = lutName.getValue();
    int lutnamelen = lutname.getLength()+1;
    mReqSender.rHtonl(&lutnamelen);
    mReqSender.addChildElement(LUT_ACTION, LUTACTION_LUTNAMESIZE, sizeof(int), &lutnamelen);
    mReqSender.addChildElement(LUT_ACTION, LUTACTION_LUTNAME, lutname.getLength()+1, (void*)lutname.getString());

    float rw = rampWidth.getValue();
    mReqSender.rSwapf(&rw);
    mReqSender.addChildElement(LUT_ACTION, LUTACTION_RAMPWIDTH, sizeof(float), &rw);

    mReqSender.send();

    // expect the validation response from the server
    mReqReceiver.initReceiver(mStream);
    mReqReceiver.receive();
    if(mReqReceiver.getFirstElementId() != LUT_ACTION)
        return -1;

    int done=0;
    bool res = mReqReceiver.getUniqueIntElement(LUTACTIONRESPONSE_DONE, done);

    if ( res )
    {
        mReqReceiver.rNtohl(&done);
        if ( done==1 )
        {
            this->update();
            return 0;
        }
    }

    return -1;
}

int SoXipRemoteLut::sendRampCenter()
{
    if ( lutName.getValue()==SbString("") || (NULL==mStream)) return -1;

    mReqSender.initSender(mStream, LUT_ACTION);

    //lut name on the server side
    const SbString& lutname = lutName.getValue();
    int lutnamelen = lutname.getLength()+1;
    mReqSender.rHtonl(&lutnamelen);
    mReqSender.addChildElement(LUT_ACTION, LUTACTION_LUTNAMESIZE, sizeof(int), &lutnamelen);
    mReqSender.addChildElement(LUT_ACTION, LUTACTION_LUTNAME, lutname.getLength()+1, (void*)lutname.getString());

    float rc = rampCenter.getValue();
    mReqSender.rSwapf(&rc);
    mReqSender.addChildElement(LUT_ACTION, LUTACTION_RAMPCENTER, sizeof(float), &rc);
    mReqSender.send();

    // expect the validation response from the server
    mReqReceiver.initReceiver(mStream);
    mReqReceiver.receive();
    if(mReqReceiver.getFirstElementId() != LUT_ACTION)
        return -1;

    int done=0;
    bool res = mReqReceiver.getUniqueIntElement(LUTACTIONRESPONSE_DONE, done);

    if ( res )
    {
        mReqReceiver.rNtohl(&done);
        if ( done==1 )
        {
            this->update();
            return 0;
        }
    }

    return -1;
}

int SoXipRemoteLut::sendAlphaFactor()
{
    if ( lutName.getValue()==SbString("") || (NULL==mStream)) return -1;

    mReqSender.initSender(mStream, LUT_ACTION);

    //lut name on the server side
    const SbString& lutname = lutName.getValue();
    int lutnamelen = lutname.getLength()+1;
    mReqSender.rHtonl(&lutnamelen);
    mReqSender.addChildElement(LUT_ACTION, LUTACTION_LUTNAMESIZE, sizeof(int), &lutnamelen);
    mReqSender.addChildElement(LUT_ACTION, LUTACTION_LUTNAME, lutname.getLength()+1, (void*)lutname.getString());

    float af = alphaFactor.getValue();
    mReqSender.rSwapf(&af);
    mReqSender.addChildElement(LUT_ACTION, LUTACTION_ALPHAFACTOR, sizeof(float), &af);
    mReqSender.send();

    // expect the validation response from the server
    mReqReceiver.initReceiver(mStream);
    mReqReceiver.receive();
    if(mReqReceiver.getFirstElementId() != LUT_ACTION)
        return -1;

    int done=0;
    bool res = mReqReceiver.getUniqueIntElement(LUTACTIONRESPONSE_DONE, done);

    if ( res )
    {
        mReqReceiver.rNtohl(&done);
        if ( done==1 )
        {
            this->update();
            return 0;
        }
    }

    return -1;
}

int SoXipRemoteLut::sendSlopeWidth()
{
    if ( lutName.getValue()==SbString("") || (NULL==mStream)) return -1;

    mReqSender.initSender(mStream, LUT_ACTION);

    //lut name on the server side
    const SbString& lutname = lutName.getValue();
    int lutnamelen = lutname.getLength()+1;
    mReqSender.rHtonl(&lutnamelen);
    mReqSender.addChildElement(LUT_ACTION, LUTACTION_LUTNAMESIZE, sizeof(int), &lutnamelen);
    mReqSender.addChildElement(LUT_ACTION, LUTACTION_LUTNAME, lutname.getLength()+1, (void*)lutname.getString());

    float sw = slopeWidth.getValue();
    mReqSender.rSwapf(&sw);
    mReqSender.addChildElement(LUT_ACTION, LUTACTION_SLOPEWIDTH, sizeof(float), &sw);
    mReqSender.send();

    // expect the validation response from the server
    mReqReceiver.initReceiver(mStream);
    mReqReceiver.receive();
    if(mReqReceiver.getFirstElementId() != LUT_ACTION)
        return -1;

    int done=0;
    bool res = mReqReceiver.getUniqueIntElement(LUTACTIONRESPONSE_DONE, done);

    if ( res )
    {
        mReqReceiver.rNtohl(&done);
        if ( done==1 )
        {
            this->update();
            return 0;
        }
    }

    return -1;
}

int SoXipRemoteLut::sendSlopeCenter()
{
    if ( lutName.getValue()==SbString("") || (NULL==mStream)) return -1;

    mReqSender.initSender(mStream, LUT_ACTION);

    //lut name on the server side
    const SbString& lutname = lutName.getValue();
    int lutnamelen = lutname.getLength()+1;
    mReqSender.rHtonl(&lutnamelen);
    mReqSender.addChildElement(LUT_ACTION, LUTACTION_LUTNAMESIZE, sizeof(int), &lutnamelen);
    mReqSender.addChildElement(LUT_ACTION, LUTACTION_LUTNAME, lutname.getLength()+1, (void*)lutname.getString());

    float sc = slopeCenter.getValue();
    mReqSender.rSwapf(&sc);
    mReqSender.addChildElement(LUT_ACTION, LUTACTION_SLOPECENTER, sizeof(float), &sc);
    mReqSender.send();

    // expect the validation response from the server
    mReqReceiver.initReceiver(mStream);
    mReqReceiver.receive();
    if(mReqReceiver.getFirstElementId() != LUT_ACTION)
        return -1;

    int done=0;
    bool res = mReqReceiver.getUniqueIntElement(LUTACTIONRESPONSE_DONE, done);

    if ( res )
    {
        mReqReceiver.rNtohl(&done);
        if ( done==1 )
        {
            this->update();
            return 0;
        }
    }

    return -1;
}

int SoXipRemoteLut::sendColorBottom()
{
    if ( lutName.getValue()==SbString("") || (NULL==mStream)) return -1;

    mReqSender.initSender(mStream, LUT_ACTION);

    //lut name on the server side
    const SbString& lutname = lutName.getValue();
    int lutnamelen = lutname.getLength()+1;
    mReqSender.rHtonl(&lutnamelen);
    mReqSender.addChildElement(LUT_ACTION, LUTACTION_LUTNAMESIZE, sizeof(int), &lutnamelen);
    mReqSender.addChildElement(LUT_ACTION, LUTACTION_LUTNAME, lutname.getLength()+1, (void*)lutname.getString());

    float bc[3];
    memcpy(bc, colorBottom.getValue().getValue(), sizeof(float)*3);
    mReqSender.rSwapf(bc);
    mReqSender.addChildElement(LUT_ACTION, LUTACTION_COLORBOTTOM, 3*sizeof(float), bc);
    mReqSender.send();

    // expect the validation response from the server
    mReqReceiver.initReceiver(mStream);
    mReqReceiver.receive();
    if(mReqReceiver.getFirstElementId() != LUT_ACTION)
        return -1;

    int done=0;
    bool res = mReqReceiver.getUniqueIntElement(LUTACTIONRESPONSE_DONE, done);

    if ( res )
    {
        mReqReceiver.rNtohl(&done);
        if ( done==1 )
        {
            this->update();
            return 0;
        }
    }

    return -1;
}

int SoXipRemoteLut::sendColorMiddle()
{
    if ( lutName.getValue()==SbString("") || (NULL==mStream)) return -1;

    mReqSender.initSender(mStream, LUT_ACTION);

    //lut name on the server side
    const SbString& lutname = lutName.getValue();
    int lutnamelen = lutname.getLength()+1;
    mReqSender.rHtonl(&lutnamelen);
    mReqSender.addChildElement(LUT_ACTION, LUTACTION_LUTNAMESIZE, sizeof(int), &lutnamelen);
    mReqSender.addChildElement(LUT_ACTION, LUTACTION_LUTNAME, lutname.getLength()+1, (void*)lutname.getString());

    float mc[3];
    memcpy(mc, colorMiddle.getValue().getValue(), sizeof(float)*3);
    mReqSender.rSwapf(mc);
    mReqSender.addChildElement(LUT_ACTION, LUTACTION_COLORBOTTOM, 3*sizeof(float), mc);
    mReqSender.send();

    // expect the validation response from the server
    mReqReceiver.initReceiver(mStream);
    mReqReceiver.receive();
    if(mReqReceiver.getFirstElementId() != LUT_ACTION)
        return -1;

    int done=0;
    bool res = mReqReceiver.getUniqueIntElement(LUTACTIONRESPONSE_DONE, done);

    if ( res )
    {
        mReqReceiver.rNtohl(&done);
        if ( done==1 )
        {
            this->update();
            return 0;
        }
    }

    return -1;
}

int SoXipRemoteLut::sendColorTop()
{
    if ( lutName.getValue()==SbString("") || (NULL==mStream)) return -1;

    mReqSender.initSender(mStream, LUT_ACTION);

    //lut name on the server side
    const SbString& lutname = lutName.getValue();
    int lutnamelen = lutname.getLength()+1;
    mReqSender.rHtonl(&lutnamelen);
    mReqSender.addChildElement(LUT_ACTION, LUTACTION_LUTNAMESIZE, sizeof(int), &lutnamelen);
    mReqSender.addChildElement(LUT_ACTION, LUTACTION_LUTNAME, lutname.getLength()+1, (void*)lutname.getString());

    float tc[3];
    memcpy(tc, colorTop.getValue().getValue(), sizeof(float)*3);
    mReqSender.rSwapf(tc);
    mReqSender.addChildElement(LUT_ACTION, LUTACTION_COLORBOTTOM, 3*sizeof(float), tc);
    mReqSender.send();

    // expect the validation response from the server
    mReqReceiver.initReceiver(mStream);
    mReqReceiver.receive();
    if(mReqReceiver.getFirstElementId() != LUT_ACTION)
        return -1;

    int done=0;
    bool res = mReqReceiver.getUniqueIntElement(LUTACTIONRESPONSE_DONE, done);

    if ( res )
    {
        mReqReceiver.rNtohl(&done);
        if ( done==1 )
        {
            this->update();
            return 0;
        }
    }

    return -1;
}

int SoXipRemoteLut::sendFileIn()
{
    if ( lutName.getValue()==SbString("") || (NULL==mStream)) return -1;

    mReqSender.initSender(mStream, LUT_ACTION);

    //lut name on the server side
    const SbString& lutname = lutName.getValue();
    int lutnamelen = lutname.getLength()+1;
    mReqSender.rHtonl(&lutnamelen);
    mReqSender.addChildElement(LUT_ACTION, LUTACTION_LUTNAMESIZE, sizeof(int), &lutnamelen);
    mReqSender.addChildElement(LUT_ACTION, LUTACTION_LUTNAME, lutname.getLength()+1, (void*)lutname.getString());

    const SbString& filename = fileIn.getValue();
    int filenamelen = filename.getLength()+1;
    mReqSender.rHtonl(&filenamelen);
    mReqSender.addChildElement(LUT_ACTION, LUTACTION_FILENAMESIZE, sizeof(int), &filenamelen);
    mReqSender.addChildElement(LUT_ACTION, LUTACTION_FILENAME, filename.getLength()+1, (void*)filename.getString());
    mReqSender.send();

    // expect the validation response from the server
    mReqReceiver.initReceiver(mStream);
    mReqReceiver.receive();
    if(mReqReceiver.getFirstElementId() != LUT_ACTION)
        return -1;

    int done=0;
    bool res = mReqReceiver.getUniqueIntElement(LUTACTIONRESPONSE_DONE, done);

    if ( res )
    {
        mReqReceiver.rNtohl(&done);
        if ( done==1 )
        {
            this->update();
            return 0;
        }
    }

    return -1;
}

int SoXipRemoteLut::sendFileEntries()
{
    if ( lutName.getValue()==SbString("") || (NULL==mStream)) return -1;

    mReqSender.initSender(mStream, LUT_ACTION);

    //lut name on the server side
    const SbString& lutname = lutName.getValue();
    int lutnamelen = lutname.getLength()+1;
    mReqSender.rHtonl(&lutnamelen);
    mReqSender.addChildElement(LUT_ACTION, LUTACTION_LUTNAMESIZE, sizeof(int), &lutnamelen);
    mReqSender.addChildElement(LUT_ACTION, LUTACTION_LUTNAME, lutname.getLength()+1, (void*)lutname.getString());

    int entries = fileEntries.getValue();
    mReqSender.rHtonl(&entries);
    mReqSender.addChildElement(LUT_ACTION, LUTACTION_FILEENTRIES, sizeof(int), &entries);
    mReqSender.send();

    // expect the validation response from the server
    mReqReceiver.initReceiver(mStream);
    mReqReceiver.receive();
    if(mReqReceiver.getFirstElementId() != LUT_ACTION)
        return -1;

    int done=0;
    bool res = mReqReceiver.getUniqueIntElement(LUTACTIONRESPONSE_DONE, done);

    if ( res )
    {
        mReqReceiver.rNtohl(&done);
        if ( done==1 )
        {
            this->update();
            return 0;
        }
    }

    return -1;
}

void SoXipRemoteLut::update()
{
    this->touch();
    m_bHasChangedValues = true;
}


void SoXipRemoteLut::GLRender(SoGLRenderAction * action)
{	
    doAction(action);
}

void SoXipRemoteLut::doAction(SoAction *action)
{
    if ( m_bHasChangedValues )
    {
        SoState   *state = action->getState();
        SoXipClientElement::set(state, this, m_bHasChangedValues);
        m_bHasChangedValues = false;
    }
}

