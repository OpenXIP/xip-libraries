/*
 *
 *  Copyright (C) 2009-2009, OFFIS
 *
 *  This software and supporting documentation were developed by
 *
 *    Babu Samuel
 *    Siemens Corporate Research Inc.,
 *    755 College Road East
 *    Princeton, NJ, USA
 *
 *  THIS SOFTWARE IS MADE AVAILABLE,  AS IS,  AND OFFIS MAKES NO  WARRANTY
 *  REGARDING  THE  SOFTWARE,  ITS  PERFORMANCE,  ITS  MERCHANTABILITY  OR
 *  FITNESS FOR ANY PARTICULAR USE, FREEDOM FROM ANY COMPUTER DISEASES  OR
 *  ITS CONFORMITY TO ANY SPECIFICATION. THE ENTIRE RISK AS TO QUALITY AND
 *  PERFORMANCE OF THE SOFTWARE IS WITH THE USER.
 *
 *  Module: dcmpstat
 *
 *  Author: Babu Samuel
 *
 *  Purpose:
 *    classes: DcmColorPresentationState
 *
 *  Last Update:      $Author: Babu Samuel $
 *  Update Date:      $Date: 2009/02/24 11:08:29 $
 *  CVS/RCS Revision: $Revision: 1.2 $
 *  Status:           $State: Exp $
 *
 *  CVS/RCS Log at end of file
 *
 */

#include "dcmtk/config/osconfig.h"    /* make sure OS specific configuration is included first */
#include "dcmtk/dcmpstat/dcmcpstat.h"

#include "dcmtk/ofstd/ofstd.h"       /* for class OFStandard */
#include "dcmtk/ofstd/ofstream.h"
#include "dcmtk/ofstd/ofstring.h"
#include "dcmtk/dcmpstat/dvpsdef.h"     /* for constants and macros */
#include "dcmtk/dcmpstat/dvpscu.h"      /* for DVPSCurve */
#include "dcmtk/dcmpstat/dvpsvl.h"      /* for DVPSVOILUT */
#include "dcmtk/dcmpstat/dvpsvw.h"      /* for DVPSVOIWindow */
#include "dcmtk/dcmpstat/dvpsov.h"      /* for DVPSOverlay */
#include "dcmtk/dcmpstat/dvpsda.h"      /* for DVPSDisplayedArea */
#include "dcmtk/dcmpstat/dvpssv.h"      /* for DVPSSoftcopyVOI */
#include "dcmtk/dcmpstat/dvpshlp.h"     /* for class DVPSHelper */

#include "dcmtk/dcmpstat/dvpsgl.h"      /* for DVPSGraphicLayer, needed by MSVC5 with STL */
#include "dcmtk/dcmpstat/dvpsrs.h"      /* for DVPSReferencedSeries, needed by MSVC5 with STL */
#include "dcmtk/dcmpstat/dvpsal.h"      /* for DVPSOverlayCurveActivationLayer, needed by MSVC5 with STL */
#include "dcmtk/dcmpstat/dvpsga.h"      /* for DVPSGraphicAnnotation, needed by MSVC5 with STL */
#include "dcmtk/dcmpstat/dvpsri.h"      /* for DVPSReferencedImage, needed by MSVC5 with STL */
#include "dcmtk/dcmpstat/dvpstx.h"      /* for DVPSTextObject, needed by MSVC5 with STL */
#include "dcmtk/dcmpstat/dvpsgr.h"      /* for DVPSGraphicObject, needed by MSVC5 with STL */

#define INCLUDE_CSTDLIB
#define INCLUDE_CSTDIO
#define INCLUDE_CSTRING
#define INCLUDE_CMATH
#define INCLUDE_CTIME
#define INCLUDE_LIBC
#define INCLUDE_UNISTD
#include "dcmtk/ofstd/ofstdinc.h"

/* --------------- class DcmColorPresentationState --------------- */

DcmColorPresentationState::DcmColorPresentationState()
: patientName(DCM_PatientsName)
, patientID(DCM_PatientID)
, patientBirthDate(DCM_PatientsBirthDate)
, patientSex(DCM_PatientsSex)
, studyInstanceUID(DCM_StudyInstanceUID)
, studyDate(DCM_StudyDate)
, studyTime(DCM_StudyTime)
, referringPhysiciansName(DCM_ReferringPhysiciansName)
, studyID(DCM_StudyID)
, accessionNumber(DCM_AccessionNumber)
, seriesInstanceUID(DCM_SeriesInstanceUID)
, seriesNumber(DCM_SeriesNumber)
, manufacturer(DCM_Manufacturer)
, displayedAreaSelectionList()
, imageNumber(DCM_InstanceNumber)
, presentationLabel(DCM_ContentLabel)
, presentationDescription(DCM_ContentDescription)
, presentationCreationDate(DCM_PresentationCreationDate)
, presentationCreationTime(DCM_PresentationCreationTime)
, presentationCreatorsName(DCM_ContentCreatorsName)
, referencedSeriesList()
, sOPInstanceUID(DCM_SOPInstanceUID)
, specificCharacterSet(DCM_SpecificCharacterSet)
, instanceCreationDate(DCM_InstanceCreationDate)
, instanceCreationTime(DCM_InstanceCreationTime)
, instanceCreatorUID(DCM_InstanceCreatorUID)
, useShutterRectangular(OFFalse)
, useShutterCircular(OFFalse)
, useShutterPolygonal(OFFalse)
, useShutterBitmap(OFFalse)
, shutterShape(DCM_ShutterShape)
, shutterLeftVerticalEdge(DCM_ShutterLeftVerticalEdge)
, shutterRightVerticalEdge(DCM_ShutterRightVerticalEdge)
, shutterUpperHorizontalEdge(DCM_ShutterUpperHorizontalEdge)
, shutterLowerHorizontalEdge(DCM_ShutterLowerHorizontalEdge)
, centerOfCircularShutter(DCM_CenterOfCircularShutter)
, radiusOfCircularShutter(DCM_RadiusOfCircularShutter)
, verticesOfThePolygonalShutter(DCM_VerticesOfThePolygonalShutter)
, shutterPresentationValue(DCM_ShutterPresentationValue)
, shutterOverlayGroup(DCM_ShutterOverlayGroup)
, overlayList()
, activationLayerList()
, graphicAnnotationList()
, imageRotation(DCM_ImageRotation)
, imageHorizontalFlip(DCM_ImageHorizontalFlip)
, graphicLayerList()
, iccProfile(DCM_ICCProfile)
, logstream(&ofConsole)
, verboseMode(OFFalse)
, debugMode(OFFalse)
{
  createInstanceUID();
}


DcmColorPresentationState::~DcmColorPresentationState()
{
}

void DcmColorPresentationState::clear()
{
  patientName.clear();
  patientID.clear();
  patientBirthDate.clear();
  patientSex.clear();
  studyInstanceUID.clear();
  studyDate.clear();
  studyTime.clear();
  referringPhysiciansName.clear();
  studyID.clear();
  accessionNumber.clear();
  seriesInstanceUID.clear();
  seriesNumber.clear();
  manufacturer.clear();
  displayedAreaSelectionList.clear();
  imageNumber.clear();
  presentationLabel.clear();
  presentationDescription.clear();
  presentationCreationDate.clear();
  presentationCreationTime.clear();
  presentationCreatorsName.clear();
  referencedSeriesList.clear();
  sOPInstanceUID.clear();
  specificCharacterSet.clear();
  instanceCreationDate.clear();
  instanceCreationTime.clear();
  instanceCreatorUID.clear();
  shutterShape.clear();
  shutterLeftVerticalEdge.clear();
  shutterRightVerticalEdge.clear();
  shutterUpperHorizontalEdge.clear();
  shutterLowerHorizontalEdge.clear();
  centerOfCircularShutter.clear();
  radiusOfCircularShutter.clear();
  verticesOfThePolygonalShutter.clear();
  shutterPresentationValue.clear();
  shutterOverlayGroup.clear();
  overlayList.clear();
  activationLayerList.clear();
  graphicAnnotationList.clear();
  imageRotation.clear();
  imageHorizontalFlip.clear();
  graphicLayerList.clear();
  iccProfile.clear();
  return;
}


const char *DcmColorPresentationState::createInstanceUID()
{
  char uid[100];
  OFString aString;
  char *puid = NULL;

  OFCondition result = sOPInstanceUID.putString(dcmGenerateUniqueIdentifier(uid));
  DVPSHelper::currentDate(aString);
  DVPSHelper::setDefault(result, instanceCreationDate, aString.c_str());
  DVPSHelper::currentTime(aString);
  DVPSHelper::setDefault(result, instanceCreationTime, aString.c_str());
  if (EC_Normal == result)
  {
    if (EC_Normal != sOPInstanceUID.getString(puid)) puid=NULL;
  }
  return puid;
}


const char *DcmColorPresentationState::getInstanceUID()
{
  char *puid = NULL;
  if (EC_Normal != sOPInstanceUID.getString(puid)) puid=NULL;
  return puid;
}


const char *DcmColorPresentationState::getSOPClassUID()
{
  return UID_GrayscaleSoftcopyPresentationStateStorage;
}


const char *DcmColorPresentationState::getPatientID()
{
  char *c = NULL;
  if (EC_Normal == patientID.getString(c)) return c; else return NULL;
}


const char *DcmColorPresentationState::getStudyUID()
{
  char *c = NULL;
  if (EC_Normal == studyInstanceUID.getString(c)) return c; else return NULL;
}


OFCondition DcmColorPresentationState::createDummyValues(OFBool replaceSOPInstanceUID)
{
  OFCondition result = EC_Normal;
  char uid[100];
  OFString aString;

  DVPSHelper::setDefault(result, patientName, DEFAULT_patientName);
  SET_UID(studyInstanceUID)
  SET_UID(seriesInstanceUID)

  DVPSHelper::setDefault(result, imageNumber, DEFAULT_imageNumber);
  DVPSHelper::setDefault(result, presentationLabel, DEFAULT_presentationLabel);
  DVPSHelper::currentDate(aString);
  DVPSHelper::setDefault(result, presentationCreationDate, aString.c_str() );
  DVPSHelper::currentTime(aString);
  DVPSHelper::setDefault(result, presentationCreationTime, aString.c_str() );

  if ((result==EC_Normal)&&(replaceSOPInstanceUID ||(sOPInstanceUID.getLength()==0)))
  {
    sOPInstanceUID.putString(dcmGenerateUniqueIdentifier(uid));
    DVPSHelper::currentDate(aString);
    DVPSHelper::setDefault(result, instanceCreationDate, aString.c_str() );
    DVPSHelper::currentTime(aString);
    DVPSHelper::setDefault(result, instanceCreationTime, aString.c_str() );
  }

  // default for specific character set is -absent-.
  // DVPSHelper::setDefault(result, specificCharacterSet, DEFAULT_specificCharacterSet );

  // create some dummy defaults for shutters
  if (shutterPresentationValue.getVM() != 1) shutterPresentationValue.putUint16(0);
  DVPSHelper::setDefault(result, shutterLeftVerticalEdge, "1");
  DVPSHelper::setDefault(result, shutterRightVerticalEdge, "1024");
  DVPSHelper::setDefault(result, shutterUpperHorizontalEdge, "1");
  DVPSHelper::setDefault(result, shutterLowerHorizontalEdge, "1024");
  DVPSHelper::setDefault(result, centerOfCircularShutter, "512\\512");
  DVPSHelper::setDefault(result, radiusOfCircularShutter, "512");
  DVPSHelper::setDefault(result, verticesOfThePolygonalShutter, "1\\1\\1\\1024\\1024\\1024\\1024\\1\\1\\1");
  if (shutterOverlayGroup.getVM() != 1) shutterOverlayGroup.putUint16(0x6000);

  // create defaults for Spatial Transformation Module
  if (result==EC_Normal)
  {
    if (imageRotation.getVM() != 1) result = imageRotation.putUint16(0);
  }
  DVPSHelper::setDefault(result, imageHorizontalFlip, "N");

  return result;
}


OFCondition DcmColorPresentationState::read(DcmItem &dset)
{
  OFCondition result = EC_Normal;
  DcmStack stack;

  clear(); // re-initialize Presentation State object

  /* check SOP class UID and modality first */
  DcmUniqueIdentifier sopclassuid(DCM_SOPClassUID);
  DcmCodeString modality(DCM_Modality);
  OFString aString;
  READ_FROM_DATASET(DcmUniqueIdentifier, sopclassuid)
  READ_FROM_DATASET(DcmCodeString, modality)

  if (sopclassuid.getLength() == 0)
  {
    result=EC_IllegalCall;
    if (verboseMode)
    {
      logstream->lockCerr() << "Error: SOPClassUID absent or empty in presentation state" << endl;
      logstream->unlockCerr();
    }
  }
  else if (sopclassuid.getVM() != 1)
  {
    result=EC_IllegalCall;
    if (verboseMode)
    {
      logstream->lockCerr() << "Error: SOPClassUID VM != 1 in presentation state" << endl;
      logstream->unlockCerr();
    }
  }

  if (modality.getLength() == 0)
  {
    result=EC_IllegalCall;
    if (verboseMode)
    {
      logstream->lockCerr() << "Error: Modality absent or empty in presentation state" << endl;
      logstream->unlockCerr();
    }
  }
  else if (modality.getVM() != 1)
  {
    result=EC_IllegalCall;
    if (verboseMode)
    {
      logstream->lockCerr() << "Error: Modality VM != 1 in presentation state" << endl;
      logstream->unlockCerr();
    }
  }

  sopclassuid.getOFString(aString,0);
  if (aString != UID_GrayscaleSoftcopyPresentationStateStorage)
  {
    result=EC_IllegalCall;
    if (verboseMode)
    {
      logstream->lockCerr() << "Error: SOP Class UID does not match GrayscaleSoftcopyPresentationStateStorage" << endl;
      logstream->unlockCerr();
    }
  }

  modality.getOFString(aString,0);
  if (aString != "PR")
  {
    result=EC_IllegalCall;
    if (verboseMode)
    {
      logstream->lockCerr() << "Error: Modality does not match 'PR' for presentation state" << endl;
      logstream->unlockCerr();
    }
  }

  if (result==EC_Normal)
  {
    READ_FROM_DATASET(DcmPersonName, patientName)
    READ_FROM_DATASET(DcmLongString, patientID)
    READ_FROM_DATASET(DcmDate, patientBirthDate)
    READ_FROM_DATASET(DcmCodeString, patientSex)
    READ_FROM_DATASET(DcmUniqueIdentifier, studyInstanceUID)
    READ_FROM_DATASET(DcmDate, studyDate)
    READ_FROM_DATASET(DcmTime, studyTime)
    READ_FROM_DATASET(DcmPersonName, referringPhysiciansName)
    READ_FROM_DATASET(DcmShortString, studyID)
    READ_FROM_DATASET(DcmShortString, accessionNumber)
    READ_FROM_DATASET(DcmUniqueIdentifier, seriesInstanceUID)
    READ_FROM_DATASET(DcmIntegerString, seriesNumber)
    READ_FROM_DATASET(DcmLongString, manufacturer)
    READ_FROM_DATASET(DcmIntegerString, imageNumber)
    READ_FROM_DATASET(DcmCodeString, presentationLabel)
    READ_FROM_DATASET(DcmLongString, presentationDescription)
    READ_FROM_DATASET(DcmDate, presentationCreationDate)
    READ_FROM_DATASET(DcmTime, presentationCreationTime)
    READ_FROM_DATASET(DcmPersonName, presentationCreatorsName)
    READ_FROM_DATASET(DcmUniqueIdentifier, sOPInstanceUID)
    READ_FROM_DATASET(DcmCodeString, specificCharacterSet)
    READ_FROM_DATASET(DcmDate, instanceCreationDate)
    READ_FROM_DATASET(DcmTime, instanceCreationTime)
    READ_FROM_DATASET(DcmUniqueIdentifier, instanceCreatorUID)
    READ_FROM_DATASET(DcmCodeString, shutterShape)
    READ_FROM_DATASET(DcmIntegerString, shutterLeftVerticalEdge)
    READ_FROM_DATASET(DcmIntegerString, shutterRightVerticalEdge)
    READ_FROM_DATASET(DcmIntegerString, shutterUpperHorizontalEdge)
    READ_FROM_DATASET(DcmIntegerString, shutterLowerHorizontalEdge)
    READ_FROM_DATASET(DcmIntegerString, centerOfCircularShutter)
    READ_FROM_DATASET(DcmIntegerString, radiusOfCircularShutter)
    READ_FROM_DATASET(DcmIntegerString, verticesOfThePolygonalShutter)
    READ_FROM_DATASET(DcmUnsignedShort, shutterPresentationValue)
    READ_FROM_DATASET(DcmUnsignedShort, shutterOverlayGroup)
    READ_FROM_DATASET(DcmUnsignedShort, imageRotation)
    READ_FROM_DATASET(DcmCodeString, imageHorizontalFlip)
	READ_FROM_DATASET(DcmOtherByteOtherWord, iccProfile)
  }

  if (result==EC_Normal) result = overlayList.read(dset);
  if (result==EC_Normal) result = activationLayerList.read(dset);
  if (result==EC_Normal) result = graphicLayerList.read(dset);
  if (result==EC_Normal) result = referencedSeriesList.read(dset);
  if (result==EC_Normal) result = graphicAnnotationList.read(dset);
  if (result==EC_Normal) result = displayedAreaSelectionList.read(dset);

  /* Now perform basic sanity checks and adjust use flags */

  if (result==EC_Normal)
  {

  if (patientName.getLength() == 0)
  {
    result=EC_IllegalCall;
    if (verboseMode)
    {
      logstream->lockCerr() << "Error: patientName absent or empty in presentation state" << endl;
      logstream->unlockCerr();
    }
  }
  else if (patientName.getVM() != 1)
  {
    result=EC_IllegalCall;
    if (verboseMode)
    {
      logstream->lockCerr() << "Error: patientName VM != 1 in presentation state" << endl;
      logstream->unlockCerr();
    }
  }

  if (studyInstanceUID.getLength() == 0)
  {
    result=EC_IllegalCall;
    if (verboseMode)
    {
      logstream->lockCerr() << "Error: studyInstanceUID absent or empty in presentation state" << endl;
      logstream->unlockCerr();
    }
  }
  else if (studyInstanceUID.getVM() != 1)
  {
    result=EC_IllegalCall;
    if (verboseMode)
    {
      logstream->lockCerr() << "Error: studyInstanceUID VM != 1 in presentation state" << endl;
      logstream->unlockCerr();
    }
  }

  if (displayedAreaSelectionList.size() == 0)
  {
    result=EC_IllegalCall;
    if (verboseMode)
    {
      logstream->lockCerr() << "Error: displayedAreaSelectionSQ absent or empty in presentation state" << endl;
      logstream->unlockCerr();
    }
  }

  if (imageNumber.getLength() == 0)
  {
    result=EC_IllegalCall;
    if (verboseMode)
    {
      logstream->lockCerr() << "Error: instanceNumber absent or empty in presentation state" << endl;
      logstream->unlockCerr();
    }
  }
  else if (imageNumber.getVM() != 1)
  {
    result=EC_IllegalCall;
    if (verboseMode)
    {
      logstream->lockCerr() << "Error: instanceNumber VM != 1 in presentation state" << endl;
      logstream->unlockCerr();
    }
  }

  if (presentationLabel.getLength() == 0)
  {
    result=EC_IllegalCall;
    if (verboseMode)
    {
      logstream->lockCerr() << "Error: presentationLabel absent or empty in presentation state" << endl;
      logstream->unlockCerr();
    }
  }
  else if (presentationLabel.getVM() != 1)
  {
    result=EC_IllegalCall;
    if (verboseMode)
    {
      logstream->lockCerr() << "Error: presentationLabel VM != 1 in presentation state" << endl;
      logstream->unlockCerr();
    }
  }

  if (presentationCreationDate.getLength() == 0)
  {
    result=EC_IllegalCall;
    if (verboseMode)
    {
      logstream->lockCerr() << "Error: presentationCreationDate absent or empty in presentation state" << endl;
      logstream->unlockCerr();
    }
  }
  else if (presentationCreationDate.getVM() != 1)
  {
    result=EC_IllegalCall;
    if (verboseMode)
    {
      logstream->lockCerr() << "Error: presentationCreationDate VM != 1 in presentation state" << endl;
      logstream->unlockCerr();
    }
  }

  if (presentationCreationTime.getLength() == 0)
  {
    result=EC_IllegalCall;
    if (verboseMode)
    {
      logstream->lockCerr() << "Error: presentationCreationTime absent or empty in presentation state" << endl;
      logstream->unlockCerr();
    }
  }
  else if (presentationCreationTime.getVM() != 1)
  {
    result=EC_IllegalCall;
    if (verboseMode)
    {
      logstream->lockCerr() << "Error: presentationCreationTime VM != 1 in presentation state" << endl;
      logstream->unlockCerr();
    }
  }

  if (sOPInstanceUID.getLength() == 0)
  {
    result=EC_IllegalCall;
    if (verboseMode)
    {
      logstream->lockCerr() << "Error: sOPInstanceUID absent or empty in presentation state" << endl;
      logstream->unlockCerr();
    }
  }
  else if (sOPInstanceUID.getVM() != 1)
  {
    result=EC_IllegalCall;
    if (verboseMode)
    {
      logstream->lockCerr() << "Error: sOPInstanceUID VM != 1 in presentation state" << endl;
      logstream->unlockCerr();
    }
  }

    /* if imageRotation or imageHorizontalFlip are present, then both must be present. */
    if ((imageRotation.getLength() > 0)&&(imageHorizontalFlip.getLength() == 0))
    {
      result=EC_IllegalCall;
      if (verboseMode)
      {
        logstream->lockCerr() << "Error: imageRotation present but imageHorizontalFlip absent or empty in presentation state" << endl;
        logstream->unlockCerr();
      }
    }

    if ((imageRotation.getLength() == 0)&&(imageHorizontalFlip.getLength() > 0))
    {
      result=EC_IllegalCall;
      if (verboseMode)
      {
        logstream->lockCerr() << "Error: imageHorizontalFlip present but imageRotation absent or empty in presentation state" << endl;
        logstream->unlockCerr();
      }
    }

	if (iccProfile.getLength() == 0)
	{
		result=EC_IllegalCall;
		if (verboseMode)
		{
		  logstream->lockCerr() << "Error: ICC Profile absent or empty in presentation state" << endl;
		  logstream->unlockCerr();
		}
	}

  } /* end result==EC_Normal */

  /* check shutters */
  if (result==EC_Normal)
  {
    // now we examine the shutterShape for the Shutter modules
    Uint32 i;
    aString.clear();
    useShutterRectangular=OFFalse;
    useShutterCircular=OFFalse;
    useShutterPolygonal=OFFalse;
    useShutterBitmap=OFFalse;
    for (i=0; i<shutterShape.getVM(); i++)
    {
      shutterShape.getOFString(aString, i, OFTrue);
      if (aString == "RECTANGULAR") useShutterRectangular=OFTrue;
      else if (aString == "CIRCULAR") useShutterCircular=OFTrue;
      else if (aString == "POLYGONAL") useShutterPolygonal=OFTrue;
      else if (aString == "BITMAP") useShutterBitmap=OFTrue;
      else
      {
        result=EC_IllegalCall;
        if (verboseMode)
        {
          logstream->lockCerr() << "Error: unknown shutter type '" << aString << "'" << endl;
          logstream->unlockCerr();
        }
      }
    }

    if (useShutterRectangular)
    {
      if ((shutterLeftVerticalEdge.getLength() == 0)||(shutterLeftVerticalEdge.getVM() != 1))
      {
        result=EC_IllegalCall;
        if (verboseMode)
        {
          logstream->lockCerr() << "Error: rectangular shutter used but shutterLeftVerticalEdge absent or VM != 1 in presentation state" << endl;
          logstream->unlockCerr();
        }
      }
      if ((shutterRightVerticalEdge.getLength() == 0)||(shutterRightVerticalEdge.getVM() != 1))
      {
        result=EC_IllegalCall;
        if (verboseMode)
        {
          logstream->lockCerr() << "Error: rectangular shutter used but shutterRightVerticalEdge absent or VM != 1 in presentation state" << endl;
          logstream->unlockCerr();
        }
      }
      if ((shutterUpperHorizontalEdge.getLength() == 0)||(shutterUpperHorizontalEdge.getVM() != 1))
      {
        result=EC_IllegalCall;
        if (verboseMode)
        {
          logstream->lockCerr() << "Error: rectangular shutter used but shutterUpperHorizontalEdge absent or VM != 1 in presentation state" << endl;
          logstream->unlockCerr();
        }
      }
      if ((shutterLowerHorizontalEdge.getLength() == 0)||(shutterLowerHorizontalEdge.getVM() != 1))
      {
        result=EC_IllegalCall;
        if (verboseMode)
        {
          logstream->lockCerr() << "Error: rectangular shutter used but shutterLowerHorizontalEdge absent or VM != 1 in presentation state" << endl;
          logstream->unlockCerr();
        }
      }
    }
    if (useShutterCircular)
    {
      if ((centerOfCircularShutter.getLength() == 0)||(centerOfCircularShutter.getVM() != 2))
      {
        result=EC_IllegalCall;
        if (verboseMode)
        {
          logstream->lockCerr() << "Error: circular shutter used but centerOfCircularShutter absent or VM != 2 in presentation state" << endl;
          logstream->unlockCerr();
        }
      }
      if ((radiusOfCircularShutter.getLength() == 0)||(radiusOfCircularShutter.getVM() != 1))
      {
        result=EC_IllegalCall;
        if (verboseMode)
        {
          logstream->lockCerr() << "Error: circular shutter used but radiusOfCircularShutter absent or VM != 1 in presentation state" << endl;
          logstream->unlockCerr();
        }
      }
    }
    if (useShutterPolygonal)
    {
      /* check that VM == 2-2n */
      if ((verticesOfThePolygonalShutter.getLength() == 0) ||
          (verticesOfThePolygonalShutter.getVM() < 2) ||
          ((verticesOfThePolygonalShutter.getVM() % 2) != 0))
      {
        result=EC_IllegalCall;
        if (verboseMode)
        {
          logstream->lockCerr() << "Error: polygonal shutter used but verticesOfThePolygonalShutter absent or VM != 2-2n in presentation state" << endl;
          logstream->unlockCerr();
        }
      }
    }
    if (useShutterBitmap)
    {
      if ((shutterOverlayGroup.getLength() == 0)||(shutterOverlayGroup.getVM() != 1))
      {
        result=EC_IllegalCall;
        if (verboseMode)
        {
          logstream->lockCerr() << "Error: bitmap shutter used but shutterOverlayGroup absent or VM != 1 in presentation state" << endl;
          logstream->unlockCerr();
        }
      }
    }
    if (useShutterRectangular || useShutterCircular || useShutterPolygonal || useShutterBitmap)
    {
      if ((shutterPresentationValue.getLength() == 0)||(shutterPresentationValue.getVM() != 1))
      {
        result=EC_IllegalCall;
        if (verboseMode)
        {
          logstream->lockCerr() << "Error: shutter used but shutterPresentationValue absent or VM != 1 in presentation state" << endl;
          logstream->unlockCerr();
        }
      }
    }
    /* we can either have rect/circ/poly shutter or bitmap shutter but not both */
    if (useShutterBitmap && (useShutterRectangular || useShutterCircular || useShutterPolygonal))
    {
      result=EC_IllegalCall;
      if (verboseMode)
      {
        logstream->lockCerr() << "Error: both bitmap and rect/circ/poly shutter specified in presentation state" << endl;
        logstream->unlockCerr();
      }
    }
  }

  /* check that overlays referenced as bitmap shutter really exist */
  if ((result==EC_Normal) && useShutterBitmap)
  {
    Uint16 shuttergroup = 0;
    shutterOverlayGroup.getUint16(shuttergroup);
    if (shuttergroup >= 0x6000)
    {
      if (!overlayList.haveOverlayGroup(shuttergroup))
      {
        result=EC_IllegalCall;
        if (verboseMode)
        {
          logstream->lockCerr() << "Error: bitmap shutter specified but referenced overlay group missing in presentation state" << endl;
          logstream->unlockCerr();
        }
      }
    } else {
        result=EC_IllegalCall;
        if (verboseMode)
        {
          logstream->lockCerr() << "Error: wrong overlay group specified for bitmap shutter in presentation state" << endl;
          logstream->unlockCerr();
        }
    }
  }

  /* check that referenced series list is non-empty and that every series contains images
     and that all referenced images share the same SOP class UID.
   */
  if (result.good() && (!referencedSeriesList.isValid()))
  {
    // referencedSeriesList.isValid() has already displayed an error message in verbose mode
    result = EC_IllegalCall;
  }

  /* check that there is no mask module present. We don't support Mask and therefore
     are obliged to reject any presentation state containing a mask! */

  stack.clear();
  if (EC_Normal == dset.search(DCM_MaskSubtractionSequence, stack, ESM_fromHere, OFFalse))
  {
      result=EC_IllegalCall;
      if (verboseMode)
      {
        logstream->lockCerr() << "Error: mask module present in presentation state, but unsupported" << endl;
        logstream->unlockCerr();
      }
  }
  stack.clear();
  if (EC_Normal == dset.search(DCM_RecommendedViewingMode, stack, ESM_fromHere, OFFalse))
  {
      result=EC_IllegalCall;
      if (verboseMode)
      {
        logstream->lockCerr() << "Error: mask module present in presentation state, but unsupported" << endl;
        logstream->unlockCerr();
      }
  }

  return result;
}

OFCondition DcmColorPresentationState::createDefaultDisplayedArea(DcmItem &dset)
{
  DcmUnsignedShort rows(DCM_Rows);
  DcmUnsignedShort columns(DCM_Columns);
  DcmUniqueIdentifier sopclassUID(DCM_SOPClassUID);
  DcmUniqueIdentifier imageUID(DCM_SOPInstanceUID);
  DcmDecimalString imagerPixelSpacing(DCM_ImagerPixelSpacing);
  DcmDecimalString pixelSpacing(DCM_PixelSpacing);
  DcmIntegerString pixelAspectRatio(DCM_PixelAspectRatio);
  Uint16 cols_uint=0;
  Uint16 rows_uint=0;
  char *c_sopclassUID = NULL;
  char *c_imageUID = NULL;
  char *pixelspacing = NULL;
  OFCondition result = EC_Normal;
  DcmStack stack;

  READ_FROM_DATASET(DcmUnsignedShort, rows)
  READ_FROM_DATASET(DcmUnsignedShort, columns)
  READ_FROM_DATASET(DcmUniqueIdentifier, sopclassUID)
  READ_FROM_DATASET(DcmUniqueIdentifier, imageUID)
  READ_FROM_DATASET(DcmDecimalString, imagerPixelSpacing)
  READ_FROM_DATASET(DcmDecimalString, pixelSpacing)
  READ_FROM_DATASET(DcmIntegerString, pixelAspectRatio)

  if (result == EC_Normal) result = columns.getUint16(cols_uint,0);
  if (result == EC_Normal) result = rows.getUint16(rows_uint,0);
  if (result == EC_Normal) result = sopclassUID.getString(c_sopclassUID);
  if (result == EC_Normal) result = imageUID.getString(c_imageUID);

  /* create displayed area selection item for this image */
  if (EC_Normal == result)
  {
    DVPSDisplayedArea *area = displayedAreaSelectionList.createDisplayedArea(
      referencedSeriesList, c_sopclassUID, c_imageUID, 1, 1, DVPSB_currentImage);
    if (area)
    {
      if (EC_Normal == result) result = area->setDisplayedArea(DVPSD_scaleToFit, (Sint32)1, (Sint32)1, (Sint32)cols_uint, (Sint32)rows_uint);
      if (EC_Normal == result)
      {
        OFBool foundRatio = OFFalse;
        if ((imagerPixelSpacing.getVM()==2)&&(EC_Normal==imagerPixelSpacing.getString(pixelspacing)))
        {
          result = area->setDisplayedAreaPixelSpacing(pixelspacing);
          if (EC_Normal==result) foundRatio = OFTrue;
        }
        if ((! foundRatio)&&(pixelSpacing.getVM()==2)&&(EC_Normal==pixelSpacing.getString(pixelspacing)))
        {
          result = area->setDisplayedAreaPixelSpacing(pixelspacing);
          if (EC_Normal==result) foundRatio = OFTrue;
        }
        if ((! foundRatio)&&(pixelAspectRatio.getVM()==2)&&(EC_Normal==pixelAspectRatio.getString(pixelspacing)))
        {
          result = area->setDisplayedAreaPixelAspectRatio(pixelspacing);
          if (EC_Normal==result) foundRatio = OFTrue;
        }
        if (! foundRatio) result = area->setDisplayedAreaPixelAspectRatio(1.0);
      }
    } else result = EC_MemoryExhausted;
  }
  return result;
}

OFCondition DcmColorPresentationState::createFromImage(
  DcmItem &dset,
  DVPSoverlayActivation overlayActivation,
  OFBool curveActivation,
  OFBool shutterActivation,
  DVPSGraphicLayering layering,
  const char *aetitle,
  const char *filesetID,
  const char *filesetUID)
{
  OFCondition result = EC_Normal;
  DcmStack stack;
  char uid[100];
  OFString aString;
  OFString ofsopclassUID;
  OFString ofimageUID;
  OFBool isMonochrome1 = OFFalse;
  DcmUniqueIdentifier sopclassUID(DCM_SOPClassUID);
  DcmUniqueIdentifier imageUID(DCM_SOPInstanceUID);
  DcmCodeString photometricInterpretation(DCM_PhotometricInterpretation);

  clear(); // re-initialize Presentation State object

  /* copy some image attributes we will need later */
  READ_FROM_DATASET(DcmCodeString, photometricInterpretation)
  READ_FROM_DATASET(DcmUniqueIdentifier, sopclassUID)
  READ_FROM_DATASET(DcmUniqueIdentifier, imageUID)
  sopclassUID.getOFString(ofsopclassUID,0);
  imageUID.getOFString(ofimageUID,0);

  /* copy attributes for Patient, General Study and General Equipment
   * modules from image object. Also copy specific character set (SOP common). */
  READ_FROM_DATASET(DcmPersonName, patientName)
  READ_FROM_DATASET(DcmLongString, patientID)
  READ_FROM_DATASET(DcmDate, patientBirthDate)
  READ_FROM_DATASET(DcmCodeString, patientSex)
  READ_FROM_DATASET(DcmUniqueIdentifier, studyInstanceUID)
  READ_FROM_DATASET(DcmDate, studyDate)
  READ_FROM_DATASET(DcmTime, studyTime)
  READ_FROM_DATASET(DcmPersonName, referringPhysiciansName)
  READ_FROM_DATASET(DcmShortString, studyID)
  READ_FROM_DATASET(DcmShortString, accessionNumber)
  READ_FROM_DATASET(DcmLongString, manufacturer)
  READ_FROM_DATASET(DcmCodeString, specificCharacterSet)
  READ_FROM_DATASET(DcmOtherByteOtherWord, iccProfile)

  if ((result==EC_Normal) && shutterActivation)
  {
    /* if there is a display shutter in the image (i.e. in XA, RF, DX), copy it.
     * We never copy bitmap shutters.
     */
    READ_FROM_DATASET(DcmCodeString, shutterShape)
    READ_FROM_DATASET(DcmIntegerString, shutterLeftVerticalEdge)
    READ_FROM_DATASET(DcmIntegerString, shutterRightVerticalEdge)
    READ_FROM_DATASET(DcmIntegerString, shutterUpperHorizontalEdge)
    READ_FROM_DATASET(DcmIntegerString, shutterLowerHorizontalEdge)
    READ_FROM_DATASET(DcmIntegerString, centerOfCircularShutter)
    READ_FROM_DATASET(DcmIntegerString, radiusOfCircularShutter)
    READ_FROM_DATASET(DcmIntegerString, verticesOfThePolygonalShutter)
    READ_FROM_DATASET(DcmUnsignedShort, shutterPresentationValue)
  }

  /* copy overlays if appropriate */
  if ((result==EC_Normal)&&(overlayActivation==DVPSO_copyOverlays)) result = overlayList.read(dset);

  /* Now perform basic sanity checks and adjust use flags */

  if ((studyInstanceUID.getLength() == 0)||(studyInstanceUID.getVM() != 1)) result=EC_IllegalCall;


  if (photometricInterpretation.getVM() == 1)
  {
    aString.clear();
    photometricInterpretation.getOFString(aString,0);
    if ((aString == "MONOCHROME1")||(aString == "MONOCHROME 1")) isMonochrome1 = OFTrue;
    else if ((aString != "MONOCHROME2")&&(aString != "MONOCHROME 2"))
    {
      result = EC_IllegalCall;
      if (verboseMode)
      {
        logstream->lockCerr() << "Error: Wrong image photometric interpretation - not MONOCHROME1/2" << endl;
        logstream->unlockCerr();
      }
    }
  }

  if (result==EC_Normal)
  {
    if ((patientName.getLength() == 0)||(patientName.getVM() != 1))
      result = patientName.putString(DEFAULT_patientName);
  }
  if (result==EC_Normal)
  {
    result = imageNumber.putString(DEFAULT_imageNumber);
  }
  if (result==EC_Normal)
  {
    result = presentationLabel.putString(DEFAULT_presentationLabel);
  }
  if (result==EC_Normal)
  {
    aString.clear();
    DVPSHelper::currentDate(aString);
    result = presentationCreationDate.putString(aString.c_str());
  }
  if (result==EC_Normal)
  {
    aString.clear();
    DVPSHelper::currentTime(aString);
    result = presentationCreationTime.putString(aString.c_str());
  }
  if (result==EC_Normal) result = seriesInstanceUID.putString(dcmGenerateUniqueIdentifier(uid, SITE_SERIES_UID_ROOT));
  if (result==EC_Normal) result = sOPInstanceUID.putString(dcmGenerateUniqueIdentifier(uid));
  if (result==EC_Normal) result = seriesNumber.putString(DEFAULT_seriesNumber);
  if (result==EC_Normal) result = specificCharacterSet.putString(DEFAULT_specificCharacterSet);

  /* check shutters */
  if (result==EC_Normal)
  {
    // now we examine the shutterShape for the Shutter modules
    Uint32 i;
    aString.clear();
    useShutterRectangular=OFFalse;
    useShutterCircular=OFFalse;
    useShutterPolygonal=OFFalse;
    useShutterBitmap=OFFalse;
    for (i=0; i<shutterShape.getVM(); i++)
    {
      shutterShape.getOFString(aString, i, OFTrue);
      if (aString == "RECTANGULAR") useShutterRectangular=OFTrue;
      if (aString == "CIRCULAR") useShutterCircular=OFTrue;
      if (aString == "POLYGONAL") useShutterPolygonal=OFTrue;
      else { /* forget this shutter! */ }
    }

    if (useShutterRectangular)
    {
      if ((shutterLeftVerticalEdge.getLength() == 0)||(shutterLeftVerticalEdge.getVM() != 1)) useShutterRectangular=OFFalse;
      if ((shutterRightVerticalEdge.getLength() == 0)||(shutterRightVerticalEdge.getVM() != 1)) useShutterRectangular=OFFalse;
      if ((shutterUpperHorizontalEdge.getLength() == 0)||(shutterUpperHorizontalEdge.getVM() != 1)) useShutterRectangular=OFFalse;
      if ((shutterLowerHorizontalEdge.getLength() == 0)||(shutterLowerHorizontalEdge.getVM() != 1)) useShutterRectangular=OFFalse;
    }
    if (useShutterCircular)
    {
      if ((centerOfCircularShutter.getLength() == 0)||(centerOfCircularShutter.getVM() != 2)) useShutterCircular=OFFalse;
      if ((radiusOfCircularShutter.getLength() == 0)||(radiusOfCircularShutter.getVM() != 1)) useShutterCircular=OFFalse;
    }
    if (useShutterPolygonal)
    {
      /* check that VM == 2-2n */
      if ((verticesOfThePolygonalShutter.getLength() == 0) ||
          (verticesOfThePolygonalShutter.getVM() < 2) ||
          ((verticesOfThePolygonalShutter.getVM() % 2) != 0)) useShutterPolygonal=OFFalse;
    }
    if (useShutterRectangular || useShutterCircular || useShutterPolygonal)
    {
      aString.clear();
      if (useShutterRectangular) aString = "RECTANGULAR";
      if (useShutterCircular)
      {
        if (aString.size() >0) aString += '\\';
        aString += "CIRCULAR";
      }
      if (useShutterPolygonal)
      {
        if (aString.size() >0) aString += '\\';
        aString += "POLYGONAL";
      }
      shutterShape.putString(aString.c_str());
      if ((shutterPresentationValue.getLength() == 0)||(shutterPresentationValue.getVM() != 1))
      {
        shutterPresentationValue.clear();
        shutterPresentationValue.putUint16(DEFAULT_shutterPresentationValue,0);
      }
    }
  }

  /* browse the image for overlays and curves, create activation tags and
   * graphic layers as appropriate.
   */
  if (result==EC_Normal) result = activationLayerList.createFromImage(dset,
    graphicLayerList, overlayList, overlayActivation, curveActivation, layering);

  /* create reference for this image */
  if (EC_Normal == result) result = addImageReference(dset, aetitle, filesetID, filesetUID);

  /* create displayed area selection item for this image */
  if (EC_Normal == result) result = createDefaultDisplayedArea(dset);

  return result;
}


OFCondition DcmColorPresentationState::write(DcmItem &dset, OFBool replaceSOPInstanceUID)
{
  OFCondition result = EC_Normal;
  DcmElement *delem=NULL;
  DcmSequenceOfItems *dseq=NULL;
  DcmItem *ditem=NULL;

  cleanupLayers(); /* remove unused layers */
  createDummyValues(replaceSOPInstanceUID);

  /* add SOP Class UID */
  DcmUniqueIdentifier sopclassuid(DCM_SOPClassUID);
  if (result==EC_Normal)
  {
     result = sopclassuid.putString(UID_GrayscaleSoftcopyPresentationStateStorage);
  }
  ADD_TO_DATASET(DcmUniqueIdentifier, sopclassuid)

  /* add Modality */
  DcmCodeString modality(DCM_Modality);
  if (result==EC_Normal)
  {
     result = modality.putString("PR");
  }
  ADD_TO_DATASET(DcmCodeString, modality)

  ADD_TO_DATASET(DcmPersonName, patientName)
  ADD_TO_DATASET(DcmLongString, patientID)
  ADD_TO_DATASET(DcmDate, patientBirthDate)
  ADD_TO_DATASET(DcmCodeString, patientSex)
  ADD_TO_DATASET(DcmUniqueIdentifier, studyInstanceUID)
  ADD_TO_DATASET(DcmDate, studyDate)
  ADD_TO_DATASET(DcmTime, studyTime)
  ADD_TO_DATASET(DcmPersonName, referringPhysiciansName)
  ADD_TO_DATASET(DcmShortString, studyID)
  ADD_TO_DATASET(DcmShortString, accessionNumber)
  ADD_TO_DATASET(DcmCodeString, modality)
  ADD_TO_DATASET(DcmUniqueIdentifier, seriesInstanceUID)
  ADD_TO_DATASET(DcmIntegerString, seriesNumber)
  ADD_TO_DATASET(DcmLongString, manufacturer)
  ADD_TO_DATASET(DcmIntegerString, imageNumber)
  ADD_TO_DATASET(DcmCodeString, presentationLabel)
  ADD_TO_DATASET(DcmLongString, presentationDescription)
  ADD_TO_DATASET(DcmDate, presentationCreationDate)
  ADD_TO_DATASET(DcmTime, presentationCreationTime)
  ADD_TO_DATASET(DcmPersonName, presentationCreatorsName)
  ADD_TO_DATASET(DcmOtherByteOtherWord, iccProfile)


  ADD_TO_DATASET(DcmUniqueIdentifier, sOPInstanceUID)
  if (specificCharacterSet.getLength() >0) { ADD_TO_DATASET(DcmCodeString, specificCharacterSet) }
  if (instanceCreationDate.getLength() >0) { ADD_TO_DATASET(DcmDate, instanceCreationDate) }
  if (instanceCreationTime.getLength() >0) { ADD_TO_DATASET(DcmTime, instanceCreationTime) }
  if (instanceCreatorUID.getLength() >0) { ADD_TO_DATASET(DcmUniqueIdentifier, instanceCreatorUID) }

  shutterShape.clear();
  if (useShutterRectangular || useShutterCircular || useShutterPolygonal)
  {
    OFString aString;
    if (useShutterRectangular) aString = "RECTANGULAR";
    if (useShutterCircular)
    {
      if (aString.size() > 0) aString += '\\';
      aString += "CIRCULAR";
    }
    if (useShutterPolygonal)
    {
      if (aString.size() > 0) aString += '\\';
      aString += "POLYGONAL";
    }
    shutterShape.putString(aString.c_str());
  } else if (useShutterBitmap)
  {
    shutterShape.putString("BITMAP");
  }
  if (useShutterRectangular || useShutterCircular || useShutterPolygonal)
  {
    ADD_TO_DATASET(DcmCodeString, shutterShape)
    ADD_TO_DATASET(DcmUnsignedShort, shutterPresentationValue)
    if (useShutterRectangular)
    {
      ADD_TO_DATASET(DcmIntegerString, shutterLeftVerticalEdge)
      ADD_TO_DATASET(DcmIntegerString, shutterRightVerticalEdge)
      ADD_TO_DATASET(DcmIntegerString, shutterUpperHorizontalEdge)
      ADD_TO_DATASET(DcmIntegerString, shutterLowerHorizontalEdge)
    }
    if (useShutterCircular)
    {
      ADD_TO_DATASET(DcmIntegerString, centerOfCircularShutter)
      ADD_TO_DATASET(DcmIntegerString, radiusOfCircularShutter)
    }
    if (useShutterPolygonal)
    {
      ADD_TO_DATASET(DcmIntegerString, verticesOfThePolygonalShutter)
    }
  }
  else if (useShutterBitmap)
  {
    ADD_TO_DATASET(DcmCodeString, shutterShape)
    ADD_TO_DATASET(DcmUnsignedShort, shutterPresentationValue)
    ADD_TO_DATASET(DcmUnsignedShort, shutterOverlayGroup)
  }

  if (EC_Normal == result) result = referencedSeriesList.write(dset);
  if (EC_Normal == result) result = overlayList.write(dset);
  if (EC_Normal == result) result = activationLayerList.write(dset);
  if (EC_Normal == result) result = graphicAnnotationList.write(dset);
  if (EC_Normal == result) result = displayedAreaSelectionList.write(dset);
  if (EC_Normal == result) result = graphicLayerList.write(dset);

  // strictly speaking we are not allowed to include the Spatial Transformation
  // Module if neither rotation nor flipping are needed.
  OFString aString;
  OFBool haveRotation=OFFalse;
  OFBool haveFlip=OFFalse;
  if (imageRotation.getVM() == 1)
  {
    Uint16 urot=0;
    imageRotation.getUint16(urot,0);
    if (urot) haveRotation=OFTrue;
  }
  if (imageHorizontalFlip.getLength() > 0)
  {
    imageHorizontalFlip.getOFString(aString, 0, OFTrue);
    if (aString == "Y") haveFlip=OFTrue;
  }

  if (haveRotation || haveFlip)
  {
    ADD_TO_DATASET(DcmUnsignedShort, imageRotation)
    ADD_TO_DATASET(DcmCodeString, imageHorizontalFlip)
  }

  return result;
}


OFCondition DcmColorPresentationState::addImageReference(
    const char *studyUID,
    const char *seriesUID,
    const char *sopclassUID,
    const char *instanceUID,
    const char *frames,
    const char *aetitle,
    const char *filesetID,
    const char *filesetUID)
{
  if ((studyUID==NULL)||(seriesUID==NULL)||(sopclassUID==NULL)||(instanceUID==NULL)) return EC_IllegalCall;

  OFString study;
  studyInstanceUID.getOFString(study,0);
  if (study != studyUID)
  {
    if (verboseMode)
    {
      logstream->lockCerr() << "Error: cannot add reference to image with different Study Instance UID." << endl;
      logstream->unlockCerr();
    }
    return EC_IllegalCall;
  }
  return referencedSeriesList.addImageReference(seriesUID, sopclassUID, instanceUID, frames, aetitle, filesetID, filesetUID);
}


OFCondition DcmColorPresentationState::addImageReference(
    DcmItem &dset,
    const char *aetitle,
    const char *filesetID,
    const char *filesetUID)
{
  DcmIntegerString numberOfFrames(DCM_NumberOfFrames);
  DcmUniqueIdentifier studyUID(DCM_StudyInstanceUID);
  DcmUniqueIdentifier seriesUID(DCM_SeriesInstanceUID);
  DcmUniqueIdentifier sopclassUID(DCM_SOPClassUID);
  DcmUniqueIdentifier imageUID(DCM_SOPInstanceUID);

  OFString ofstudyUID;
  OFString ofseriesUID;
  OFString ofsopclassUID;
  OFString ofimageUID;
  OFString aString;
  char buf[20];
  Sint32 i=0;
  Sint32 ofnumberOfFrames=0;
  DcmStack stack;

  READ_FROM_DATASET(DcmIntegerString, numberOfFrames)
  READ_FROM_DATASET(DcmUniqueIdentifier, studyUID)
  READ_FROM_DATASET(DcmUniqueIdentifier, seriesUID)
  READ_FROM_DATASET(DcmUniqueIdentifier, sopclassUID)
  READ_FROM_DATASET(DcmUniqueIdentifier, imageUID)

  numberOfFrames.getSint32(ofnumberOfFrames,0);
  seriesUID.getOFString(ofseriesUID,0);
  sopclassUID.getOFString(ofsopclassUID,0);
  imageUID.getOFString(ofimageUID,0);
  studyUID.getOFString(ofstudyUID,0);

  OFCondition result = EC_Normal;
  /* if the image is multiframe, reference all frames */
  if (ofnumberOfFrames > 1)
  {
    for (i=0; i<ofnumberOfFrames; i++)
    {
        if (aString.length() > 0) sprintf(buf, "\\%ld", (long)(i+1)); else sprintf(buf, "%ld", (long)(i+1));
        aString += buf;
    }
    result = addImageReference(ofstudyUID.c_str(), ofseriesUID.c_str(), ofsopclassUID.c_str(),
      ofimageUID.c_str(), aString.c_str(), aetitle, filesetID, filesetUID);
  } else {
    result = addImageReference(ofstudyUID.c_str(), ofseriesUID.c_str(), ofsopclassUID.c_str(),
      ofimageUID.c_str(), NULL, aetitle, filesetID, filesetUID);
  }
  /* create default displayed area entry for the new referenced image */
  if (result == EC_Normal)
    createDefaultDisplayedArea(dset);
  /* what is about VOI LUT sequence, annotations, etc. ? */
  return result;
}


OFCondition DcmColorPresentationState::removeImageReference(
    const char *studyUID,
    const char *seriesUID,
    const char *instanceUID)
{
  if ((studyUID==NULL)||(seriesUID)||(instanceUID==NULL)) return EC_IllegalCall;

  OFString study;
  studyInstanceUID.getOFString(study,0);
  if (study != studyUID) return EC_IllegalCall;
  referencedSeriesList.removeImageReference(seriesUID, instanceUID);

  /* still need to remove references from displayed area list, etc. */

  return EC_Normal;
}


OFCondition DcmColorPresentationState::removeImageReference(DcmItem &dset)
{
  DcmUniqueIdentifier studyUID(DCM_StudyInstanceUID);
  DcmUniqueIdentifier seriesUID(DCM_SeriesInstanceUID);
  DcmUniqueIdentifier imageUID(DCM_SOPInstanceUID);

  OFString ofstudyInstanceUID;
  OFString ofstudyUID;
  OFString ofseriesUID;
  OFString ofimageUID;
  DcmStack stack;

  READ_FROM_DATASET(DcmUniqueIdentifier, studyUID)
  READ_FROM_DATASET(DcmUniqueIdentifier, seriesUID)
  READ_FROM_DATASET(DcmUniqueIdentifier, imageUID)

  seriesUID.getOFString(ofseriesUID,0);
  studyInstanceUID.getOFString(ofstudyInstanceUID,0);
  if (ofstudyInstanceUID != ofstudyUID) return EC_IllegalCall;

  imageUID.getOFString(ofimageUID,0);
  studyUID.getOFString(ofstudyUID,0);
  referencedSeriesList.removeImageReference(ofseriesUID.c_str(), ofimageUID.c_str());

  /* still need to remove references from displayed area list, etc. */

  return EC_Normal;
}

size_t DcmColorPresentationState::numberOfImageReferences()
{
  return referencedSeriesList.numberOfImageReferences();
}

OFCondition DcmColorPresentationState::getImageReference(
    size_t idx,
    OFString& studyUID,
    OFString& seriesUID,
    OFString& sopclassUID,
    OFString& instanceUID,
    OFString& frames,
    OFString& aetitle,
    OFString& filesetID,
    OFString& filesetUID)
{
  OFCondition result = referencedSeriesList.getImageReference(idx, seriesUID, sopclassUID,
    instanceUID, frames, aetitle, filesetID, filesetUID);
  if (EC_Normal == result) result = studyInstanceUID.getOFString(studyUID,0);
  return result;
}

DVPSRotationType DcmColorPresentationState::getRotation()
{
  DVPSRotationType result = DVPSR_0_deg;
  Uint16 rotation=0;
  imageRotation.getUint16(rotation,0);
  if (rotation==90) result = DVPSR_90_deg;
  else if (rotation==180) result = DVPSR_180_deg;
  else if (rotation==270) result = DVPSR_270_deg;
  return result;
}


OFBool DcmColorPresentationState::getFlip()
{
  OFBool result = OFFalse;
  OFString flip;
  imageHorizontalFlip.getOFString(flip,0);
  if (flip=="Y") result = OFTrue;
  return result;
}


OFCondition DcmColorPresentationState::setRotation(DVPSRotationType rotation)
{
  // Re-compute all displayed areas
  DVPSRotationType oldRotation = getRotation();
  OFBool flip = getFlip();
  displayedAreaSelectionList.rotateAndFlip(oldRotation, flip, rotation, flip);

  OFCondition result = EC_Normal;
  switch (rotation)
  {
    case DVPSR_0_deg:
      result = imageRotation.putUint16(0);
      break;
    case DVPSR_90_deg:
      result = imageRotation.putUint16(90);
      break;
    case DVPSR_180_deg:
      result = imageRotation.putUint16(180);
      break;
    case DVPSR_270_deg:
      result = imageRotation.putUint16(270);
      break;
  }

  return result;
}


OFCondition DcmColorPresentationState::setFlip(OFBool isFlipped)
{
  // Re-compute all displayed areas
  DVPSRotationType rotation = getRotation();
  OFBool oldFlip = getFlip();
  displayedAreaSelectionList.rotateAndFlip(rotation, oldFlip, rotation, isFlipped);

  if (isFlipped) return imageHorizontalFlip.putString("Y");
  else return imageHorizontalFlip.putString("N");
}


OFBool DcmColorPresentationState::haveShutter(DVPSShutterType type)
{
  OFBool result = OFFalse;
  switch (type)
  {
    case DVPSU_rectangular:
      result = useShutterRectangular;
      break;
    case DVPSU_circular:
      result = useShutterCircular;
      break;
    case DVPSU_polygonal:
      result = useShutterPolygonal;
      break;
    case DVPSU_bitmap:
      result = useShutterBitmap;
      break;
  }
  return result;
}


Sint32 DcmColorPresentationState::getRectShutterLV()
{
  Sint32 result=0;
  shutterLeftVerticalEdge.getSint32(result,0);
  return result;
}

Sint32 DcmColorPresentationState::getRectShutterRV()
{
  Sint32 result=0;
  shutterRightVerticalEdge.getSint32(result,0);
  return result;
}

Sint32 DcmColorPresentationState::getRectShutterUH()
{
  Sint32 result=0;
  shutterUpperHorizontalEdge.getSint32(result,0);
  return result;
}

Sint32 DcmColorPresentationState::getRectShutterLH()
{
  Sint32 result=0;
  shutterLowerHorizontalEdge.getSint32(result,0);
  return result;
}


Sint32 DcmColorPresentationState::getCenterOfCircularShutter_x()
{
  Sint32 result=0;
  centerOfCircularShutter.getSint32(result,1);
  return result;
}

Sint32 DcmColorPresentationState::getCenterOfCircularShutter_y()
{
  Sint32 result=0;
  centerOfCircularShutter.getSint32(result,0);
  return result;
}

Sint32 DcmColorPresentationState::getRadiusOfCircularShutter()
{
  Sint32 result=0;
  radiusOfCircularShutter.getSint32(result,0);
  return result;
}


size_t DcmColorPresentationState::getNumberOfPolyShutterVertices()
{
  return (verticesOfThePolygonalShutter.getVM() / 2);
}

OFCondition DcmColorPresentationState::getPolyShutterVertex(size_t idx, Sint32& x, Sint32& y)
{
  x=0;
  y=0;
  OFCondition result = verticesOfThePolygonalShutter.getSint32(y,2*idx);
  if (EC_Normal==result) result = verticesOfThePolygonalShutter.getSint32(x,2*idx+1);
  return result;
}

OFCondition DcmColorPresentationState::setPolyShutterOrigin(Sint32 x, Sint32 y)
{
  char buf[80];
  useShutterPolygonal = OFFalse;
  verticesOfThePolygonalShutter.clear();
  sprintf(buf, "%ld\\%ld", (long)y, (long)x);
  return verticesOfThePolygonalShutter.putString(buf);
}


Uint16 DcmColorPresentationState::getShutterPresentationValue()
{
  Uint16 result=0;
  shutterPresentationValue.getUint16(result,0);
  return result;
}

OFCondition DcmColorPresentationState::setShutterPresentationValue(Uint16 pvalue)
{
  return shutterPresentationValue.putUint16(pvalue,0);
}

const char *DcmColorPresentationState::getPresentationLabel()
{
  char *value = NULL;
  if (EC_Normal != presentationLabel.getString(value)) return NULL;
  return value;
}

const char *DcmColorPresentationState::getPresentationDescription()
{
  char *value = NULL;
  if (EC_Normal != presentationDescription.getString(value)) return NULL;
  return value;
}

const char *DcmColorPresentationState::getPresentationCreatorsName()
{
  char *value = NULL;
  if (EC_Normal != presentationCreatorsName.getString(value)) return NULL;
  return value;
}

OFCondition DcmColorPresentationState::setPresentationLabel(const char *label)
{
  return presentationLabel.putString(label);
}

OFCondition DcmColorPresentationState::setPresentationDescription(const char *descr)
{
  return presentationDescription.putString(descr);
}

OFCondition DcmColorPresentationState::setPresentationCreatorsName(const char *name)
{
  return presentationCreatorsName.putString(name);
}


void DcmColorPresentationState::sortGraphicLayers()
{
  graphicLayerList.sortGraphicLayers();
  return;
}

size_t DcmColorPresentationState::getNumberOfGraphicLayers()
{
  return graphicLayerList.size();
}

const char *DcmColorPresentationState::getGraphicLayerName(size_t idx)
{
  return graphicLayerList.getGraphicLayerName(idx);
}

size_t DcmColorPresentationState::getGraphicLayerIndex(const char *name)
{
  return graphicLayerList.getGraphicLayerIndex(name);
}

const char *DcmColorPresentationState::getGraphicLayerDescription(size_t idx)
{
  return graphicLayerList.getGraphicLayerDescription(idx);
}

OFBool DcmColorPresentationState::haveGraphicLayerRecommendedDisplayValue(size_t idx)
{
  return graphicLayerList.haveGraphicLayerRecommendedDisplayValue(idx);
}

OFCondition DcmColorPresentationState::getGraphicLayerRecommendedDisplayValueGray(size_t idx, Uint16& gray)
{
  return graphicLayerList.getGraphicLayerRecommendedDisplayValueGray(idx,gray);
}

OFCondition DcmColorPresentationState::getGraphicLayerRecommendedDisplayValueRGB(size_t idx, Uint16& r, Uint16& g, Uint16& b)
{
  return graphicLayerList.getGraphicLayerRecommendedDisplayValueRGB(idx,r,g,b);
}

OFCondition DcmColorPresentationState::setGraphicLayerRecommendedDisplayValueGray(size_t idx, Uint16 gray)
{
  return graphicLayerList.setGraphicLayerRecommendedDisplayValueGray(idx,gray);
}

OFCondition DcmColorPresentationState::setGraphicLayerRecommendedDisplayValueRGB(size_t idx, Uint16 r, Uint16 g, Uint16 b)
{
  return graphicLayerList.setGraphicLayerRecommendedDisplayValueRGB(idx,r,g,b);
}

void DcmColorPresentationState::removeGraphicLayerRecommendedDisplayValue(size_t idx, OFBool rgb, OFBool monochrome)
{
  graphicLayerList.removeGraphicLayerRecommendedDisplayValue(idx, rgb, monochrome);
  return;
}

OFCondition DcmColorPresentationState::setGraphicLayerName(size_t idx, const char *name)
{
  const char *oname = graphicLayerList.getGraphicLayerName(idx);
  if (name==NULL) return EC_IllegalCall;
  OFString oldName(oname); // make a copy of the pointer which will become invalid
  OFCondition result=graphicLayerList.setGraphicLayerName(idx, name);
  if (EC_Normal==result)
  {
    activationLayerList.renameLayer(oldName.c_str(), name);
    graphicAnnotationList.renameLayer(oldName.c_str(), name);
  }
  return result;
}

OFCondition DcmColorPresentationState::setGraphicLayerDescription(size_t idx, const char *descr)
{
  return graphicLayerList.setGraphicLayerDescription(idx, descr);
}

OFCondition DcmColorPresentationState::toFrontGraphicLayer(size_t idx)
{
  return graphicLayerList.toFrontGraphicLayer(idx);
}

OFCondition DcmColorPresentationState::toBackGraphicLayer(size_t idx)
{
  return graphicLayerList.toBackGraphicLayer(idx);
}

OFCondition DcmColorPresentationState::exchangeGraphicLayers(size_t idx1, size_t idx2)
{
  return graphicLayerList.exchangeGraphicLayers(idx1, idx2);
}

OFCondition DcmColorPresentationState::addGraphicLayer(
     const char *gLayer,
     const char *gLayerDescription)
{
  return graphicLayerList.addGraphicLayer(gLayer,gLayerDescription);
}

void DcmColorPresentationState::cleanupLayers()
{
  graphicAnnotationList.cleanupLayers();
  graphicLayerList.cleanupLayers(activationLayerList, graphicAnnotationList);
}


OFCondition DcmColorPresentationState::setCharset(DVPScharacterSet charset)
{
  if (charset==DVPSC_other) return EC_IllegalCall;

  const char *cname=NULL;
  switch (charset)
  {
    case DVPSC_latin1:
      cname = "ISO_IR 100";
      break;
    case DVPSC_latin2:
      cname = "ISO_IR 101";
      break;
    case DVPSC_latin3:
      cname = "ISO_IR 109";
      break;
    case DVPSC_latin4:
      cname = "ISO_IR 110";
      break;
    case DVPSC_latin5:
      cname = "ISO_IR 148";
      break;
    case DVPSC_cyrillic:
      cname = "ISO_IR 144";
      break;
    case DVPSC_arabic:
      cname = "ISO_IR 127";
      break;
    case DVPSC_greek:
      cname = "ISO_IR 126";
      break;
    case DVPSC_hebrew:
      cname = "ISO_IR 138";
      break;
    case DVPSC_japanese:
      cname = "ISO_IR 13";
      break;
    default: // can only be DVPSC_ascii
      break;
  }
  if (cname) return specificCharacterSet.putString(cname);
  else
  {
    specificCharacterSet.clear();
    return EC_Normal;
  }
}

OFCondition DcmColorPresentationState::setICCProfile(const Uint8 *value, const unsigned long count)
{
	if (!value || count == 0) return EC_IllegalCall;

	OFCondition status = EC_Normal;

	status = iccProfile.putUint8Array(value, count);

	return status;
}

DVPScharacterSet DcmColorPresentationState::getCharset()
{
  if (specificCharacterSet.getLength()==0) return DVPSC_ascii;

  OFString aString;
  specificCharacterSet.getOFString(aString,0);
  if (aString == "ISO_IR 6") return DVPSC_ascii;
  else if (aString == "ISO_IR 100") return DVPSC_latin1;
  else if (aString == "ISO_IR 101") return DVPSC_latin2;
  else if (aString == "ISO_IR 109") return DVPSC_latin3;
  else if (aString == "ISO_IR 110") return DVPSC_latin4;
  else if (aString == "ISO_IR 148") return DVPSC_latin5;
  else if (aString == "ISO_IR 144") return DVPSC_cyrillic;
  else if (aString == "ISO_IR 127") return DVPSC_arabic;
  else if (aString == "ISO_IR 126") return DVPSC_greek;
  else if (aString == "ISO_IR 138") return DVPSC_hebrew;
  else if (aString == "ISO_IR 13")  return DVPSC_japanese;
  /* default */
  return DVPSC_other;
}

const char *DcmColorPresentationState::getCharsetString()
{
  char *c = NULL;
  if (EC_Normal == specificCharacterSet.getString(c)) return c; else return NULL;
}


size_t DcmColorPresentationState::getNumberOfCurves(size_t layer)
{
  return activationLayerList.getNumberOfActivations(
    graphicLayerList.getGraphicLayerName(layer), OFTrue);
}


OFCondition DcmColorPresentationState::removeCurve(size_t layer, size_t idx)
{
  Uint16 group = activationLayerList.getActivationGroup(
    graphicLayerList.getGraphicLayerName(layer), idx, OFTrue);
  if (group == 0) return EC_IllegalCall;
  activationLayerList.removeActivation(group);
  return EC_Normal;
}

OFCondition DcmColorPresentationState::moveCurve(size_t old_layer, size_t idx, size_t new_layer)
{
  const char *lname = graphicLayerList.getGraphicLayerName(new_layer);
  if (lname==NULL) return EC_IllegalCall;

  Uint16 group = activationLayerList.getActivationGroup(
    graphicLayerList.getGraphicLayerName(old_layer), idx, OFTrue);
  if (group == 0) return EC_IllegalCall;

  activationLayerList.removeActivation(group);
  return activationLayerList.setActivation(group, lname);
}


size_t DcmColorPresentationState::getNumberOfActiveOverlays(size_t layer)
{
  return activationLayerList.getNumberOfActivations(
    graphicLayerList.getGraphicLayerName(layer), OFFalse);
}

Uint16 DcmColorPresentationState::getActiveOverlayGroup(size_t layer, size_t idx)
{
  return activationLayerList.getActivationGroup(graphicLayerList.getGraphicLayerName(layer),
           idx, OFFalse);
}

size_t DcmColorPresentationState::getNumberOfOverlaysInPresentationState()
{
  return overlayList.size();
}

Uint16 DcmColorPresentationState::getOverlayInPresentationStateGroup(size_t idx)
{
  DVPSOverlay *overlay = overlayList.getOverlay(idx);
  if (overlay) return (0x6000+overlay->getOverlayGroup());
  return 0;
}

const char *DcmColorPresentationState::getOverlayInPresentationStateLabel(size_t idx)
{
  DVPSOverlay *overlay = overlayList.getOverlay(idx);
  if (overlay) return overlay->getOverlayLabel();
  return NULL;
}

const char *DcmColorPresentationState::getOverlayInPresentationStateDescription(size_t idx)
{
  DVPSOverlay *overlay = overlayList.getOverlay(idx);
  if (overlay) return overlay->getOverlayDescription();
  return NULL;
}

size_t DcmColorPresentationState::getOverlayInPresentationStateActivationLayer(size_t idx)
{
  DVPSOverlay *overlay = overlayList.getOverlay(idx);
  if (overlay)
  {
    const char *layerName = activationLayerList.getActivationLayer(0x6000+overlay->getOverlayGroup());
    if (layerName) return graphicLayerList.getGraphicLayerIndex(layerName);
  }
  return DVPS_IDX_NONE;
}

OFBool DcmColorPresentationState::overlayIsBitmapShutter(size_t idx)
{
  if (shutterOverlayGroup.getLength() == 0) return OFFalse;

  Uint16 shutterGroup=0;
  if (EC_Normal == shutterOverlayGroup.getUint16(shutterGroup,0))
  {
    DVPSOverlay *overlay = overlayList.getOverlay(idx);
    if (overlay) return (shutterGroup == 0x6000+overlay->getOverlayGroup());
  }
  return OFFalse;
}

OFBool DcmColorPresentationState::overlayInPresentationStateIsROI(size_t idx)
{
  DVPSOverlay *overlay = overlayList.getOverlay(idx);
  if (overlay) return overlay->isROI();
  return OFFalse;
}

OFCondition DcmColorPresentationState::moveOverlay(size_t old_layer, size_t idx, size_t new_layer)
{
  const char *lname = graphicLayerList.getGraphicLayerName(new_layer);
  if (lname==NULL) return EC_IllegalCall;

  Uint16 group = activationLayerList.getActivationGroup(
    graphicLayerList.getGraphicLayerName(old_layer), idx, OFFalse);
  if (group == 0) return EC_IllegalCall;

  activationLayerList.removeActivation(group);
  return activationLayerList.setActivation(group, lname);
}

void DcmColorPresentationState::setLog(OFConsole *stream, OFBool verbMode, OFBool dbgMode)
{
  if (stream) logstream = stream; else logstream = &ofConsole;
  verboseMode = verbMode;
  debugMode = dbgMode;
  displayedAreaSelectionList.setLog(logstream, verbMode, dbgMode);
  referencedSeriesList.setLog(logstream, verbMode, dbgMode);
  overlayList.setLog(logstream, verbMode, dbgMode);
  activationLayerList.setLog(logstream, verbMode, dbgMode);
  graphicAnnotationList.setLog(logstream, verbMode, dbgMode);
  graphicLayerList.setLog(logstream, verbMode, dbgMode);
}

