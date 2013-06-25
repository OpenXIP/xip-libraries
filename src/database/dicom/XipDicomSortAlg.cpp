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
#include "XipDicomSortAlg.h"
#include "XipDicomSortImage.h"
#include <string.h>


// compares the two strings a and b, an optional string terminator character can be specified
static int compareStrings(char *a, char *b, char terminator = 0)
{
	int rc = 0;

	if (a != b)
	{
		if (a && b)
		{
			char *ta = 0, *tb = 0;

			if (terminator != 0)
			{
				ta = strchr(a, terminator);
				tb = strchr(b, terminator);

				if (ta) *ta = 0;
				if (tb) *tb = 0;
			}

			rc = strcmp(a, b);

			if (ta) *ta = terminator;
			if (tb) *tb = terminator;
		}
		else
		{
			rc = a ? 1 : -1;
		}
	}

	return rc;
}


XipDicomSortAlg::XipDicomSortAlg(const XipDicomSortImage *image)
{
	mImage = image;
}


XipDicomSortAlg::~XipDicomSortAlg()
{

}


bool XipDicomSortAlg::operator < (const XipDicomSortAlg& v) const
{
	int r;

	r = compareStrings(mImage->getAttributes()->patientID, v.mImage->getAttributes()->patientID);
	if (r < 0) return true;
	if (r > 0) return false;

	r = compareStrings(mImage->getAttributes()->studyUID, v.mImage->getAttributes()->studyUID);
	if (r < 0) return true;
	if (r > 0) return false;

	r = compareStrings(mImage->getAttributes()->seriesUID, v.mImage->getAttributes()->seriesUID);
	if (r < 0) return true;
	if (r > 0) return false;

	r = compareStrings(mImage->getAttributes()->modality, v.mImage->getAttributes()->modality);
	if (r < 0) return true;
	if (r > 0) return false;

	r = compareStrings(mImage->getAttributes()->imageType, v.mImage->getAttributes()->imageType, '\\');
	if (r < 0) return true;
	if (r > 0) return false;

	for (int i = 0; i < 6; i++)
	{
		if (mImage->getAttributes()->imageOrientation[i] < v.mImage->getAttributes()->imageOrientation[i]) return true;
		if (mImage->getAttributes()->imageOrientation[i] > v.mImage->getAttributes()->imageOrientation[i]) return false;
	}
	if (mImage->getAttributes()->echoTime < v.mImage->getAttributes()->echoTime) return true;
	if (mImage->getAttributes()->echoTime > v.mImage->getAttributes()->echoTime) return false;

	// equal
	return false;
}


bool XipDicomSortAlg::operator > (const XipDicomSortAlg& v) const
{
	int r;

	r = compareStrings(mImage->getAttributes()->patientID, v.mImage->getAttributes()->patientID);
	if (r > 0) return true;
	if (r < 0) return false;

	r = compareStrings(mImage->getAttributes()->studyUID, v.mImage->getAttributes()->studyUID);
	if (r > 0) return true;
	if (r < 0) return false;

	r = compareStrings(mImage->getAttributes()->seriesUID, v.mImage->getAttributes()->seriesUID);
	if (r > 0) return true;
	if (r < 0) return false;

	r = compareStrings(mImage->getAttributes()->modality, v.mImage->getAttributes()->modality);
	if (r > 0) return true;
	if (r < 0) return false;

	r = compareStrings(mImage->getAttributes()->imageType, v.mImage->getAttributes()->imageType, '\\');
	if (r > 0) return true;
	if (r < 0) return false;

	for (int i = 0; i < 6; i++)
	{
		if (mImage->getAttributes()->imageOrientation[i] > v.mImage->getAttributes()->imageOrientation[i]) return true;
		if (mImage->getAttributes()->imageOrientation[i] < v.mImage->getAttributes()->imageOrientation[i]) return false;
	}
	if (mImage->getAttributes()->echoTime > v.mImage->getAttributes()->echoTime) return true;
	if (mImage->getAttributes()->echoTime < v.mImage->getAttributes()->echoTime) return false;

	// equal
	return false;
}


bool XipDicomSortAlg::operator == (const XipDicomSortAlg& v) const
{
	// identical objects?
	if (mImage == v.mImage) return true;
	if (!mImage || !v.mImage) return false;

	// check attributes
	if (compareStrings(mImage->getAttributes()->patientID, v.mImage->getAttributes()->patientID) != 0) return false;
	if (compareStrings(mImage->getAttributes()->studyUID, v.mImage->getAttributes()->studyUID) != 0) return false;
	if (compareStrings(mImage->getAttributes()->seriesUID, v.mImage->getAttributes()->seriesUID) != 0) return false;
	if (compareStrings(mImage->getAttributes()->modality, v.mImage->getAttributes()->modality) != 0) return false;
	if (compareStrings(mImage->getAttributes()->imageType, v.mImage->getAttributes()->imageType, '\\') != 0) return false;
	for (int i = 0; i < 6; i++)
	{
		if (mImage->getAttributes()->imageOrientation[i] != v.mImage->getAttributes()->imageOrientation[i]) return false;
	}
	if (mImage->getAttributes()->echoTime != v.mImage->getAttributes()->echoTime) return false;

	return true;
}


bool XipDicomSortAlg::operator != (const XipDicomSortAlg& v) const
{
	return !(*this == v);
}


void XipDicomSortAlg::operator = (const XipDicomSortAlg& v)
{
	mImage = v.mImage;	
}

