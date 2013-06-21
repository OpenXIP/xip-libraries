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
/**
*	@file    SoXipPState.h
*	@brief   Declaration of the SoXipPState class
*	@author  Babu Samuel
**/

#ifndef SOXIPPSTATE_H
#define SOXIPPSTATE_H

#include <xip/inventor/core/SoXipData.h>
#include <xip/inventor/dicom/xipivdicom.h>

class DcmDataset;
class DVPSGraphicObject;
class DVPSTextObject;
class DVPresentationState;

// helper class representing a graphic objects in a presentation state (DVPSGraphicObject)
class XIPIVDICOM_API SbXipPStateGraphicObject
{
public:
	enum GraphicType
	{
		POINT,			// single point
		POLYLINE,		// non-interpolated polygonal line
		INTERPOLATED,	// interpolated polygonal line
		CIRCLE,			// circle
		ELLIPSE			// ellipse
	};

	SbXipPStateGraphicObject(DVPSGraphicObject *graphicObj);

	// Gets the number of graphic points
	unsigned short getNumberOfPoints();

	// Get one point from the graphic data
	SbBool getPoint(size_t idx, float& x, float& y);

	// Gets the graphic type of this graphic object
	GraphicType getGraphicType();

protected:
	DVPSGraphicObject	*mGraphicObject;
};

// helper class representing a text objects in a presentation state (DVPSTextObject)
class XIPIVDICOM_API SbXipPStateTextObject
{
public:
	SbXipPStateTextObject(DVPSTextObject *textObj);

	// Checks if this text object contains an anchor point
	SbBool haveAnchorPoint();

	// Checks if this text object contains bounding box
	SbBool haveBoundingBox();

	// Gets the unformatted text value for this text object
	const char* getText();

	// Gets the bounding box TLHC x value
	double  getBoundingBoxTLHC_x ();

	// Gets the bounding box TLHC y value
	double  getBoundingBoxTLHC_y ();

	// Gets the bounding box BRHC x value
	double  getBoundingBoxBRHC_x ();

	// Gets the bounding box BRHC y value
	double  getBoundingBoxBRHC_y ();

	// Gets the anchor point x value
	double  getAnchorPoint_x ();

	// Gets the anchor point y value
	double  getAnchorPoint_y ();

protected:
	DVPSTextObject	*mTextObject;
};

// dicom presentation state wrapper class
class XIPIVDICOM_API SoXipPState : public SoXipData
{
	XIP_DATA_HEADER(SoXipDataDicom);

public:
	SoXipPState(DcmDataset *dataset);
	static void initClass();

	// gets tje presentation state object
	DVPresentationState*	getPresentationState() const;

	// gets the dicom dataset attached to the presentation state
	DcmDataset*		getDataset() const;

	// read presentation state from file
	SbBool read(const char *fileName);

	// detach image from presenation state
	void close();

	// add layer and description into presentation state
	SbBool addLayer(const char* pName, const char* pDesc);

	// gets the number of layer in the presentation state
	unsigned short getNumberOfLayers();

	// gets the number of text objects in the presentation state
	unsigned short getNumberOfTextObjects(unsigned short layerIndex);

	// gets the number of graphic objects in the presentation state
	unsigned short getNumberOfGraphicObjects(unsigned short layerIndex);

	// gets the text object for the given layer and index
	SbXipPStateTextObject* getTextObject(unsigned short layer, unsigned short index);

	// gets the graphic object for the given layer and index
	SbXipPStateGraphicObject* getGraphicObject(unsigned short layer, unsigned short index);

	// adds the graphic object into presentation state
	SbBool addGraphicObject(SbXipPStateGraphicObject::GraphicType type, int nPoints, float* points, int layerIdx);

	// adds the text object into presentation state
	SbBool addTextObject(const char* text, int imagePosX, int imagePosY, int anchPosX, int anchPosY, bool isBoundingBox, bool isAnchor, int layerIdx);

	// save presentation state in the file
	SbBool saveToFile(const char* fileName);

protected:
	virtual ~SoXipPState();

	DcmDataset			*mDataset;
	DVPresentationState *mPresentationState;
};

#endif	// SOXIPPSTATE_H
