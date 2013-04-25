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

#include <dcmtk/dcmpstat/dvpstx.h>  /* for DVPSTextObject */
#include <dcmtk/dcmpstat/dvpsgr.h>  /* for DVPSGraphicObject */
#include <dcmtk/dcmpstat/dvpstat.h>

#include <Inventor/errors/SoError.h>

#include <xip/inventor/dicom/SoXipPState.h>

const int BoundingBoxOffset = 20;

XIP_DATA_SOURCE(SoXipPState);


void SoXipPState::initClass()
{
	XIP_DATA_INIT_CLASS(SoXipPState, SoXipData, "SoXipData");
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SoXipPState::SoXipPState(DcmDataset *dataset)
{
	XIP_DATA_CONSTRUCTOR(SoXipPState);

	if (!dataset)
	{
		SoError::post("null dicom dataset in the Presentation state object.");
		return;
	}

	mDataset = dataset;

	mPresentationState = new DVPresentationState();

	if (!mPresentationState)
	{
		SoError::post("Presentation state object is null.");
		return;
	}

	if (mPresentationState->createFromImage(*dataset, DVPSO_ignoreOverlays) != EC_Normal)
	{
		if (mPresentationState)
		{
			delete mPresentationState;
			mPresentationState = 0;
		}

		SoError::post("creating presentation state from image failed.");
		return;
	}

	if (mPresentationState->attachImage(dataset, OFFalse) != EC_Normal)
	{
		if (mPresentationState)
		{
			delete mPresentationState;
			mPresentationState = 0;
		}

		SoError::post("Attaching image to the presentation state failed.");
		return;
	}
}

SoXipPState::~SoXipPState()
{
	if (mPresentationState)
	{
		mPresentationState->detachImage();

		delete mPresentationState;
		mPresentationState = 0;
	}
}

DVPresentationState* SoXipPState::getPresentationState() const
{
	return mPresentationState;
}

DcmDataset* SoXipPState::getDataset() const
{
	return mDataset;
}

SbBool SoXipPState::read(const char *fileName)
{
	if (!mPresentationState)
		return FALSE;

	if (!fileName)
		return FALSE;

	DcmFileFormat pStateFileFormat;

	if (!pStateFileFormat.loadFile(fileName).good())
		return FALSE;

	return mPresentationState->read(*pStateFileFormat.getDataset()).good();

}

void SoXipPState::close()
{
	if (!mPresentationState)
		return;

	mPresentationState->detachImage();
}

SbBool SoXipPState::addLayer(const char* pName, const char* pDesc)
{
	if (!mPresentationState)
		return FALSE;

	return mPresentationState->addGraphicLayer(pName, pDesc).good();
}

unsigned short SoXipPState::getNumberOfLayers()
{
	if (!mPresentationState)
		return 0;

	return (unsigned short)mPresentationState->getNumberOfGraphicLayers();
}

unsigned short SoXipPState::getNumberOfTextObjects(unsigned short layerIndex)
{
	if (!mPresentationState)
		return 0;

	return (unsigned short)mPresentationState->getNumberOfTextObjects(layerIndex);
}

unsigned short SoXipPState::getNumberOfGraphicObjects(unsigned short layerIndex)
{
	if (!mPresentationState)
		return 0;

	return (unsigned short)mPresentationState->getNumberOfGraphicObjects(layerIndex);
}

SbXipPStateTextObject* SoXipPState::getTextObject(unsigned short layer, unsigned short index)
{
	if (!mPresentationState)
		return NULL;

	return new SbXipPStateTextObject(mPresentationState->getTextObject(layer, index));
}

SbXipPStateGraphicObject* SoXipPState::getGraphicObject(unsigned short layer, unsigned short index)
{
	if (!mPresentationState)
		return NULL;

	return new SbXipPStateGraphicObject(mPresentationState->getGraphicObject(layer, index));
}

SbBool SoXipPState::addGraphicObject(SbXipPStateGraphicObject::GraphicType type, int nPoints, float* points, int layerIdx)
{
	if (!mPresentationState)
		return FALSE;

	DVPSGraphicObject* graphicObject = mPresentationState->addGraphicObject(layerIdx, /*DVPSB_allImages*/DVPSB_currentImage);
	if (!graphicObject)
		return FALSE;

	DVPSGraphicType gType;

	switch(type)
	{
	case SbXipPStateGraphicObject::POINT: gType = DVPST_point; break;
	case SbXipPStateGraphicObject::POLYLINE: gType = DVPST_polyline; break;
	case SbXipPStateGraphicObject::INTERPOLATED: gType = DVPST_interpolated; break;	
	case SbXipPStateGraphicObject::CIRCLE: gType = DVPST_circle; break;	
	case SbXipPStateGraphicObject::ELLIPSE: gType = DVPST_ellipse; break;
	default : gType = DVPST_polyline; break;	
	}

	graphicObject->setFilled(false);
	graphicObject->setGraphicType(gType);
	graphicObject->setData(nPoints, points, DVPSA_pixels);

	return TRUE;
}

SbBool SoXipPState::addTextObject(const char* text, int imagePosX, int imagePosY, int anchPosX, int anchPosY, bool isBoundingBox, bool isAnchor, int layerIdx)
{
	if (!mPresentationState)
		return FALSE;

	DVPSTextObject* TextObject = mPresentationState->addTextObject(layerIdx, /*DVPSB_allImages*/DVPSB_currentImage);
	if (!TextObject)
		return FALSE;

	TextObject->setText(text);

	if ( isBoundingBox )
		TextObject->setBoundingBox( imagePosX, imagePosY, imagePosX + BoundingBoxOffset,  imagePosY + BoundingBoxOffset, DVPSA_pixels, DVPSX_right);

	if ( isAnchor )
		TextObject->setAnchorPoint( anchPosX, anchPosY, DVPSA_pixels, isAnchor);

	return TRUE;
}

SbBool SoXipPState::saveToFile(const char* fileName)
{
	if (!mPresentationState)
		return FALSE;

	if (!fileName)
		return FALSE;

	DcmFileFormat saveFileFormat;

	OFCondition error = mPresentationState->write(*saveFileFormat.getDataset(), OFTrue);
	if (error != EC_Normal)	
		return FALSE; 

	error = saveFileFormat.saveFile(fileName, EXS_LittleEndianExplicit, EET_ExplicitLength);
	if (error != EC_Normal)	
		return FALSE; 

	return TRUE;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

SbXipPStateGraphicObject::SbXipPStateGraphicObject(DVPSGraphicObject *graphicObj)
{
	mGraphicObject = graphicObj;
}

unsigned short SbXipPStateGraphicObject::getNumberOfPoints()
{
	if (!mGraphicObject)
		return 0;

	return (unsigned short)mGraphicObject->getNumberOfPoints();
}

SbBool SbXipPStateGraphicObject::getPoint(size_t idx, float& x, float& y)
{
	bool status = FALSE;

	if (!mGraphicObject)
		return status;

	if (mGraphicObject->getPoint(idx, x, y) == EC_Normal)
		status = TRUE;

	return status;
}

SbXipPStateGraphicObject::GraphicType SbXipPStateGraphicObject::getGraphicType()
{
	if (!mGraphicObject)
		return POLYLINE;	// default

	GraphicType gType;

	switch(mGraphicObject->getGraphicType())
	{
		case DVPST_point: gType = POINT; break;
		case DVPST_polyline: gType = POLYLINE; break;
		case DVPST_interpolated: gType = INTERPOLATED; break;	
		case DVPST_circle: gType = CIRCLE; break;	
		case DVPST_ellipse: gType = ELLIPSE; break;
		default : gType = POLYLINE; break;	
	}

	return gType;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

SbXipPStateTextObject::SbXipPStateTextObject(DVPSTextObject *textObj)
{
	mTextObject = textObj;
}

SbBool SbXipPStateTextObject::haveAnchorPoint()
{
	if (!mTextObject)
		return FALSE;

	return mTextObject->haveAnchorPoint();
}

SbBool SbXipPStateTextObject::haveBoundingBox()
{
	if (!mTextObject)
		return FALSE;

	return mTextObject->haveBoundingBox();
}

const char* SbXipPStateTextObject::getText()
{
	if (!mTextObject)
		return NULL;

	return mTextObject->getText();
}

double SbXipPStateTextObject::getBoundingBoxTLHC_x ()
{
	if (!mTextObject)
		return 0.0;

	return mTextObject->getBoundingBoxTLHC_x();
}

double SbXipPStateTextObject::getBoundingBoxTLHC_y ()
{
	if (!mTextObject)
		return 0.0;

	return mTextObject->getBoundingBoxTLHC_y();
}

double SbXipPStateTextObject::getBoundingBoxBRHC_x ()
{
	if (!mTextObject)
		return 0.0;

	return mTextObject->getBoundingBoxBRHC_x();
}

double SbXipPStateTextObject::getBoundingBoxBRHC_y ()
{
	if (!mTextObject)
		return 0.0;

	return mTextObject->getBoundingBoxBRHC_y();
}

double SbXipPStateTextObject::getAnchorPoint_x ()
{
	if (!mTextObject)
		return 0.0;

	return mTextObject->getAnchorPoint_x();
}

double SbXipPStateTextObject::getAnchorPoint_y ()
{
	if (!mTextObject)
		return 0.0;

	return mTextObject->getAnchorPoint_y();
}
