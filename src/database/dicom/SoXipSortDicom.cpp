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
// Disable the warning raised because of the std::map<>
#pragma warning ( disable : 4786 )

#include <map>
#include <vector>

#include <dcmtk/dcmdata/dctk.h>
#include <xip/inventor/dicom/SoXipDataDicom.h>
#include "SoXipSortDicom.h"

SO_ENGINE_SOURCE( SoXipSortDicom );

void SoXipSortDicom::initClass()
{
	SO_ENGINE_INIT_CLASS( SoXipSortDicom, SoEngine, "Engine" );
}

SoXipSortDicom::SoXipSortDicom()
{
	SO_ENGINE_CONSTRUCTOR( SoXipSortDicom );

	SO_ENGINE_ADD_INPUT( input, (0) );
	input.setNum(0);

	SO_ENGINE_ADD_OUTPUT( output, SoXipMFDataDicom );
}

SoXipSortDicom::~SoXipSortDicom()
{
}

int SoXipSortDicom::getNumSlices( DcmDataset* dataset )
{
	unsigned short numberOfSlices = 1;

	if (!dataset)
		return numberOfSlices;
	
	DcmStack stack;
	DcmElement *element;

	if ( dataset->search(DCM_NumberOfSlices, stack) == EC_Normal )
	{
		element = OFstatic_cast(DcmElement *, stack.top());

		if (element->ident() == EVR_US)
			element->getUint16(numberOfSlices);
	}

	return numberOfSlices;
}

double SoXipSortDicom::computePositionZ( DcmDataset* dataset )
{
	double zPos = 0.0;

	if (!dataset)
		return zPos;

	double imagePositionPatient[3]={0};
	double imageOrientationPatient[6] = { 1.0, 0.0, 0.0,
			                              0.0, -1.0, 0.0 };

	DcmStack stack;
	DcmElement *element;

	// patient position
	if ( dataset->search(DCM_ImagePositionPatient, stack) == EC_Normal )
	{
		element = OFstatic_cast(DcmElement *, stack.top());

		if (element->ident() == EVR_DS)
		{
			for (unsigned int i = 0; i < element->getVM(); i++)
				element->getFloat64(imagePositionPatient[i], i);
		}
	}

	// patient orientation
	if ( dataset->search(DCM_ImageOrientationPatient, stack) == EC_Normal )
	{
		element = OFstatic_cast(DcmElement *, stack.top());

		if (element->ident() == EVR_DS)
		{
			for (unsigned int i = 0; i < element->getVM(); i++)
				element->getFloat64(imageOrientationPatient[i], i);
		}

	}

	SbVec3f normal = 
		SbVec3f( imageOrientationPatient[0], imageOrientationPatient[1], imageOrientationPatient[2] ).cross( 
		SbVec3f( imageOrientationPatient[3], imageOrientationPatient[4], imageOrientationPatient[5] ) );

	zPos = imagePositionPatient[0] * normal[0] +
		   imagePositionPatient[1] * normal[1] +
		   imagePositionPatient[2] * normal[2];

	return zPos;
}

void SoXipSortDicom::evaluate()
{
	SO_ENGINE_OUTPUT( output, SoXipMFDataDicom, setNum(0) );

	int numInputs = input.getNum();

	if (numInputs == 0)
		return;

	typedef std::vector< int > IndexList;
	typedef std::map< double, IndexList > SortMap;

	SortMap zMap;

	for( int i = 0; i < numInputs; ++ i )
	{
		SoXipDataDicom *dataDicom = (SoXipDataDicom*) *(input.getValues(i));

		if( !dataDicom )
		{
			SoError::post( "null dicom data found while sorting slices." );
			return ;
		}

		//DCMTBD
		DcmDataset *dataset = (DcmDataset *) dataDicom->getDataset().getItem("DcmItem");

		if (!dataset)
		{
			SoError::post("null dicom dataset found while sorting slices.");
			return;
		}

		if( getNumSlices( dataset ) == 1 )
		{
			double posZ = computePositionZ(dataset);

			// Store the index i in the map
			zMap[posZ].push_back(i);
		}
	}

	SbPList sortedData;

	// Traverse the map to read the sorted dicom images into tmp
	SortMap::const_iterator it;
	for( it = zMap.begin(); it != zMap.end(); ++ it )
	{
		IndexList::const_iterator it_l;
		for( it_l = it->second.begin(); it_l != it->second.end(); ++ it_l )
		{
			SoXipDataDicom *data = (SoXipDataDicom*) *(input.getValues(*it_l));
			sortedData.append(data);
		}
	}

	int n = sortedData.getLength();
	if (n > 0)
		SO_ENGINE_OUTPUT(output, SoXipMFDataDicom, setValues(0, n, (const SoXipDataDicom**) &sortedData[0]); _eng_out_temp->setNum(n))
	else
		SO_ENGINE_OUTPUT(output, SoXipMFDataDicom, setNum(0));
}

