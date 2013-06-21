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
*	@file	SoXipPlot2Histogram.cpp
*	@brief	Implementation of the SoXipPlot2Histogram class
*	@author	Julien Gein
**/

#include <xip/system/standard.h>
#include <vector>
#include <Inventor/actions/SoActions.h>
#include <Inventor/events/SoLocation2Event.h>
#include <Inventor/events/SoMouseButtonEvent.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoFaceSet.h>
#include <Inventor/sensors/SoFieldSensor.h>
#include "SoXipPlot2Histogram.h"

SO_KIT_SOURCE( SoXipPlot2Histogram );

SoXipPlot2Histogram::SoXipPlot2Histogram()
{
	SO_KIT_CONSTRUCTOR(SoXipPlot2Histogram);

	SO_KIT_ADD_CATALOG_ENTRY(separator, SoSeparator, FALSE, this, \0 , FALSE);
	SO_KIT_ADD_CATALOG_ENTRY(shapeHints, SoShapeHints, FALSE, separator, \0 , FALSE);
	SO_KIT_ADD_CATALOG_ENTRY(coordinate, SoCoordinate3, FALSE, separator, \0 , FALSE);
	SO_KIT_ADD_CATALOG_ENTRY(faceSet, SoFaceSet, FALSE, separator, \0 , FALSE);
	SO_KIT_INIT_INSTANCE();

	SO_NODE_ADD_FIELD(values, (0));
	values.setNum(0);
	SO_NODE_ADD_FIELD(validRange, (SbVec2f(0, 0)));
	SO_NODE_ADD_FIELD(numBins, (10));

	mValueSensor = new SoFieldSensor(fieldSensorCBFunc, this);
	mValueSensor->attach(&values);
	mValidRangeSensor = new SoFieldSensor(fieldSensorCBFunc, this);;
	mValidRangeSensor->attach(&validRange);
	mNumBinsSensor = new SoFieldSensor(fieldSensorCBFunc, this);;
	mNumBinsSensor->attach(&numBins);

	SoNode *sh = getAnyPart("shapeHints", TRUE);
	if (sh)
		sh->set("vertexOrdering COUNTERCLOCKWISE	faceType UNKNOWN_FACE_TYPE");
}

SoXipPlot2Histogram::~SoXipPlot2Histogram()
{
	if (mValueSensor)
		delete mValueSensor;
	if (mValidRangeSensor)
		delete mValidRangeSensor;
	if (mNumBinsSensor)
		delete mNumBinsSensor;
}

void 
SoXipPlot2Histogram::initClass()
{
	SO_KIT_INIT_CLASS( SoXipPlot2Histogram, SoBaseKit, "BaseKit" );
}

void 
SoXipPlot2Histogram::update()
{
	int i;
	SbVec2f range = validRange.getValue();

	SoCoordinate3 *mCoord = (SoCoordinate3 *) getAnyPart("coordinate", TRUE);
	SoFaceSet *mFaceSet = (SoFaceSet *) getAnyPart("faceSet", TRUE);

	if (mCoord && mFaceSet)
	{
		mCoord->point.setNum(0);
		mFaceSet->numVertices.setNum(0);

		if ((values.getNum() <= 0) || (numBins.getValue() <= 0)) return;

		float minVal = *values.getValues(0);
		float maxVal = *values.getValues(0);
		for (i = 1; i < values.getNum(); i++)
		{
			if (minVal > *values.getValues(i))
			{
				minVal = *values.getValues(i);
			}
			if (maxVal < *values.getValues(i))
			{
				maxVal = *values.getValues(i);
			}
		}

		// valid range is empty, allow all values
		if ((range[1] - range[0]) == 0)
		{
			range[0] = minVal;
			range[1] = maxVal;
		}
		else
		{
			// crop min/max values to valid range
			if (minVal < range[0]) minVal = range[0];
			if (maxVal > range[1]) maxVal = range[1];
		}

		float binSize = (maxVal - minVal) / (float) numBins.getValue();
		if (binSize > 0)
		{
			std::vector<unsigned int> bins;
			bins.resize(numBins.getValue());

			for (i = 0; i < numBins.getValue(); i++)
				bins[0] = 0;

			for (i = 0; i < values.getNum(); i++)
			{
				float v = *values.getValues(i);

				if ((v >= range[0]) && (v <= range[1]))
				{
					int bin = std::min(numBins.getValue() - 1, (int) ((v - minVal) / binSize));
					bins[bin]++;
				}
			}

			SbVec3f pt(minVal, 0, 0);
			mCoord->point.set1Value(mCoord->point.getNum(), SbVec3f(minVal, 0, 0));
			mCoord->point.set1Value(mCoord->point.getNum(), SbVec3f(maxVal, 0, 0));

			for (i = numBins.getValue() - 1; i >= 0; i--)
			{
				SbVec3f pt(minVal + (float) i * binSize, 0, 0);

				mCoord->point.set1Value(mCoord->point.getNum(), pt + SbVec3f(binSize, bins[i], 0));
				mCoord->point.set1Value(mCoord->point.getNum(), pt + SbVec3f(0, bins[i], 0));
			}
			mFaceSet->numVertices.set1Value(0, mCoord->point.getNum());
		}
	}
}

void 
SoXipPlot2Histogram::fieldSensorCBFunc(void *user, SoSensor* sensor)
{
	((SoXipPlot2Histogram*) user)->update();
}
