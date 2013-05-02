/*
 *  COPYRIGHT NOTICE.  Copyright (C) 2007 Siemens Corporate Research, 
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
