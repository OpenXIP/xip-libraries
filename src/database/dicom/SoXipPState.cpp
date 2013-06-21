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
