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

#include "SoXipDicomSort3D.h"
#include "XipDicomSortUtil.h"
#include <xip/inventor/dicom/SoXipDataDicom.h>



SO_ENGINE_SOURCE(SoXipDicomSort3D);


SoXipDicomSort3D::SoXipDicomSort3D()
{
	SO_ENGINE_CONSTRUCTOR(SoXipDicomSort3D);

	SO_ENGINE_ADD_INPUT(images, (""));
	SO_ENGINE_ADD_INPUT(volumeIndex, (0));

	SO_ENGINE_ADD_OUTPUT(imagesInVolume, SoMFString);
	SO_ENGINE_ADD_OUTPUT(numberOfVolumes, SoSFShort);
}


SoXipDicomSort3D::~SoXipDicomSort3D()
{
}


void SoXipDicomSort3D::initClass()
{
	SO_ENGINE_INIT_CLASS(SoXipDicomSort3D, SoEngine, "Engine");
}


void SoXipDicomSort3D::evaluate()
{
	int i;

	XipDicomSortUtil sorter;
	XipDicomSortImageAttributes attr;

	SoXipDataDicom *dicomData = new SoXipDataDicom;
	if (!dicomData)
	{
		SO_ENGINE_OUTPUT(numberOfVolumes, SoSFShort, setValue(0));
		SO_ENGINE_OUTPUT(imagesInVolume, SoMFString, setNum(0));

		return;
	}

	dicomData->ref();

	// "interpret" may replace folders with files in the folder or DICOMDIR with images
	SoMFString interpreted;
	SoXipDataDicom::interpret(images, interpreted);

	for (i = 0; i < interpreted.getNum(); i++)
	{
		memset(&attr, 0, sizeof(attr));
		attr.acquisitionTime = XIPDICOMSORT_UNDEFINED;
		attr.triggerTime = XIPDICOMSORT_UNDEFINED;
		attr.echoTime = XIPDICOMSORT_UNDEFINED;
		attr.rescaleSlope = 1.f;

		// open
		attr.identifier = interpreted[i].getString();
		dicomData->open(attr.identifier);
		SbXipDicomItem dataset(dicomData->getDataset());

		// get DICOM tags
		SbString patientName;
		dataset.findAndGet(SbXipDicomTagKey(0x0010, 0x0010), patientName);
		attr.patientName = (char*) patientName.getString();

		SbString patientID;
		dataset.findAndGet(SbXipDicomTagKey(0x0010, 0x0020), patientID);
		attr.patientID = (char*) patientID.getString();

		SbString studyUID;
		dataset.findAndGet(SbXipDicomTagKey(0x0020, 0x000D), studyUID);
		attr.studyUID = (char*) studyUID.getString();

		SbString seriesUID;
		dataset.findAndGet(SbXipDicomTagKey(0x0020, 0x000E), seriesUID);
		attr.seriesUID = (char*) seriesUID.getString();

		SbString sopInstanceUID;
		dataset.findAndGet(SbXipDicomTagKey(0x0008, 0x0018), sopInstanceUID);
		attr.sopInstanceUID = (char*) sopInstanceUID.getString();

		SbString seriesTime;
		dataset.findAndGet(SbXipDicomTagKey(0x0008, 0x0031), seriesTime);
		attr.seriesTime = (char*) seriesTime.getString();

		SbString modality;
		dataset.findAndGet(SbXipDicomTagKey(0x0008, 0x0060), modality);
		attr.modality = (char*) modality.getString();

		SbString seriesDescription;
		dataset.findAndGet(SbXipDicomTagKey(0x0008, 0x103E), seriesDescription);
		attr.seriesDescription = (char*) seriesDescription.getString();

		SbString scanOptions;
		dataset.findAndGet(SbXipDicomTagKey(0x0018, 0x0022), scanOptions);
		attr.scanOptions = (char*) scanOptions.getString();

		SbString imageType;
		dataset.findAndGet(SbXipDicomTagKey(0x0008, 0x0008), imageType);
		attr.imageType = (char*) imageType.getString();

		SbString stringValue;
		if (dataset.findAndGet(SbXipDicomTagKey(0x0020, 0x0013), stringValue))
			attr.imageNumber = atoi(stringValue.getString());

		if (dataset.findAndGet(SbXipDicomTagKey(0x0020, 0x0011), stringValue))
			attr.seriesNumber = atoi(stringValue.getString());

		if (dataset.findAndGet(SbXipDicomTagKey(0x0008, 0x0032), stringValue))
			attr.acquisitionTime = atof(stringValue.getString());

		if (dataset.findAndGet(SbXipDicomTagKey(0x0018, 0x1060), stringValue))
		{
			attr.triggerTime = atof(stringValue.getString());
		}
		else
		{
			// for CT trigger time is store in scanOptions
			if (modality == SbString("CT"))
			{
				const char *time = strstr(scanOptions.getString(), "TP");
				if (time)
				{
					attr.triggerTime = atof(time + 2);
				}
			}
		}

		SbString scanningSequence;
		dataset.findAndGet(SbXipDicomTagKey(0x0008, 0x0020), scanningSequence);
		attr.scanningSequence = (char*) scanningSequence.getString();

		SbString sequenceVariant;
		dataset.findAndGet(SbXipDicomTagKey(0x0018, 0x0021), sequenceVariant);
		attr.sequenceVariant = (char*) sequenceVariant.getString();

		if (dataset.findAndGet(SbXipDicomTagKey(0x0018, 0x0081), stringValue))
			attr.echoTime = atof(stringValue.getString());

		if (dataset.findAndGet(SbXipDicomTagKey(0x0028, 0x0103), stringValue))
			attr.pixelRepresentation = atoi(stringValue.getString());

		if (dataset.findAndGet(SbXipDicomTagKey(0x0028, 0x1052), stringValue))
			attr.rescaleIntercept = atof(stringValue.getString());

		if (dataset.findAndGet(SbXipDicomTagKey(0x0028, 0x1053), stringValue))
			attr.rescaleSlope = atof(stringValue.getString());

		if (dataset.findAndGet(SbXipDicomTagKey(0x0028, 0x0100), stringValue))
			attr.bitsAllocated = atoi(stringValue.getString());

		if (dataset.findAndGet(SbXipDicomTagKey(0x0028, 0x0101), stringValue))
			attr.bitsStored = atoi(stringValue.getString());

		if (dataset.findAndGet(SbXipDicomTagKey(0x0028, 0x0102), stringValue))
			attr.highBit = atoi(stringValue.getString());

		if (dataset.findAndGet(SbXipDicomTagKey(0x0028, 0x0010), stringValue))
			attr.rows = atoi(stringValue.getString());

		if (dataset.findAndGet(SbXipDicomTagKey(0x0028, 0x0011), stringValue))
			attr.columns = atoi(stringValue.getString());

		if (dataset.findAndGet(SbXipDicomTagKey(0x0028, 0x0030), stringValue))
			sscanf(stringValue.getString(), "%lf\\%lf", &attr.pixelSpacing[0], &attr.pixelSpacing[1]);

		if (dataset.findAndGet(SbXipDicomTagKey(0x0020, 0x0032), stringValue))
			sscanf(stringValue.getString(), "%lf\\%lf\\%lf", &attr.imagePosition[0], &attr.imagePosition[1], &attr.imagePosition[2]);

		if (dataset.findAndGet(SbXipDicomTagKey(0x0020, 0x0037), stringValue))
			sscanf(stringValue.getString(), "%lf\\%lf\\%lf\\%lf\\%lf\\%lf",
				&attr.imageOrientation[0], &attr.imageOrientation[1], &attr.imageOrientation[2],
				&attr.imageOrientation[3], &attr.imageOrientation[4], &attr.imageOrientation[5]);

		// add image
		sorter.addImage(&attr);
	}

	dicomData->unref();
	dicomData = 0;

	sorter.sort();

	int volIndex = volumeIndex.getValue();
	SoMFString imageList;

	if ((volIndex >= 0) && (volIndex < (int) sorter.getNumVolumes()))
	{
		for (i = 0; i < (int) sorter.getNumSlicesInVolume(volIndex); i++)
		{
			imageList.set1Value(i, SbString(sorter.getImageAttributes(volIndex, i)->identifier));
		}
	}

	SO_ENGINE_OUTPUT(numberOfVolumes, SoSFShort, setValue(sorter.getNumVolumes()));
	SO_ENGINE_OUTPUT(imagesInVolume, SoMFString, setValues(0, imageList.getNum(), imageList.getValues(0)); _eng_out_temp->setNum(imageList.getNum()));
}
