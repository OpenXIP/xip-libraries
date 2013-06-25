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

#include <Inventor/errors/SoError.h> 
#include <xip/inventor/dicom/SoXipDataDicom.h>
#include <xip/inventor/dicom/SoXipPState.h>
#include <xip/inventor/dicom/xipivDicomUtils.h>
#include <xip/inventor/core/SbXipCoordinateTransform.h>

#include "SoXipShapeList.h"
#include <xip/inventor/overlay/SoXipManipulableShape.h>
#include "SoXipSaveOverlayPState.h"

SO_ENGINE_SOURCE(SoXipSaveOverlayPState);


void SoXipSaveOverlayPState::initClass()
{
	SO_ENGINE_INIT_CLASS(SoXipSaveOverlayPState, SoEngine, "Engine");
}


SoXipSaveOverlayPState::SoXipSaveOverlayPState()
{
	SO_ENGINE_CONSTRUCTOR(SoXipSaveOverlayPState);

	SO_ENGINE_ADD_INPUT(overlays, (0));
	SO_ENGINE_ADD_INPUT( image, (0) );
	SO_ENGINE_ADD_INPUT(pstateFile, (""));
	SO_ENGINE_ADD_INPUT(save, ());
	SO_ENGINE_ADD_OUTPUT(status, SoSFString);
}


SoXipSaveOverlayPState::~SoXipSaveOverlayPState()
{
}

void SoXipSaveOverlayPState::inputChanged(SoField *whichField)
{
	if (whichField == &save)
	{
		SO_ENGINE_OUTPUT(status, SoSFString, setValue(""));

		SoXipDataDicom* dicomData = image.getValue();
		if (!dicomData)
			return;

		const SbString strName = pstateFile.getValue();
		if (strName.getLength() == 0)	// empty string
			return;

		//DCMTBD
		DcmDataset *dataset = (DcmDataset *) dicomData->getDataset().getItem("DcmItem");
		if (!dataset)
		{
			SoError::post("Unsupported data type for DICOM presentation state!");
			return;
		}

		SbMatrix modelMatrix = getModelMatrixFromDICOM(dataset);
		XipDicomAttributes imageAttributes = getAttributesFromDicom(dataset);
		SbXipImageDimensions imgDimension(imageAttributes.width, imageAttributes.height, imageAttributes.numberOfSlices);

		try
		{
			// create presentation state
			SoXipPState *pState = new SoXipPState(dataset);
			pState->ref();

			// add layer to presentation state
			pState->addLayer("Layer1", "SampleLayer");
			int currentLayerIndex = 0;

			for( int i = 0; i < overlays.getNum(); ++ i )
			{
				SoXipShapeList* shapeList = (SoXipShapeList *) overlays[i];
				int numShapes = shapeList->getNumChildren();

				for( int j = 0; j < numShapes; ++ j )
				{
					SoXipManipulableShape* shape = (SoXipManipulableShape *) shapeList->getChild(j);

					SoType classType = shape->getTypeId();

					if ( strcmp(classType.getName().getString(),"SoXipAnnotation") == 0 )
					{
						// add the annotation to presentation state
						this->addAnnotationToPState(shape, pState, modelMatrix, imgDimension, currentLayerIndex);
					}
					else if ( strcmp(classType.getName().getString(),"SoXipEllipse") == 0 ||
						strcmp(classType.getName().getString(),"SoXipRectangle") == 0 ||
						strcmp(classType.getName().getString(),"SoXipLine") == 0 ||
						strcmp(classType.getName().getString(),"SoXipPolyLine") == 0)
					{
						// add the graphic shape to presentation state
						this->addGraphicToPState(shape, pState, modelMatrix, imgDimension, currentLayerIndex);
					}

				}
			}

			// save presentation state to file
			pState->saveToFile(strName.getString());
			pState->close();

			if (pState)
			{
				pState->unref();;
				pState = 0;
			}

			SO_ENGINE_OUTPUT(status, SoSFString, setValue("OK"));
		}
		catch (...)
		{
			SoDebugError::post( __FILE__, "Unexpected error in inputChanged()" );
		}
	}
}

void SoXipSaveOverlayPState::evaluate()
{
}

void SoXipSaveOverlayPState::addGraphicToPState(SoXipManipulableShape* shape, SoXipPState *pstate, SbMatrix modelMatrix, SbXipImageDimensions imgDimension, int layerIdx)
{
	if (!(shape && pstate))
		return;

	SoMFVec3f linePoints;
	SoMFInt32 dummyCoordIndex;
	SbBool dummyClosed;

	float *ptsArray = 0;
	int i;
	
	try
	{
		// extract points from the shape
		shape->extractGeometries( linePoints, dummyCoordIndex, dummyClosed );

		int nPoints = (shape->isClosed()) ? linePoints.getNum() * 2 + 2 : linePoints.getNum() * 2;
		ptsArray = new float[nPoints];

		XipWorldToImageConvert worldToImage(modelMatrix, imgDimension);
		SbVec3s imagecoordinates;

		for ( i = 0; i < linePoints.getNum(); ++i)
		{
			//Now covert the real-world co-ordinates to image co-ordinates
			imagecoordinates = worldToImage.getIndex(linePoints[i]);
			ptsArray[i*2] = imagecoordinates[0];
			ptsArray[i*2+1] = imagecoordinates[1];
		}

		if (shape->isClosed())
		{
			// close the loop by adding first point at the end
			ptsArray[i*2] = ptsArray[0];
			ptsArray[i*2+1] = ptsArray[1];
		}

		SoType classType = shape->getTypeId();
		if ( strcmp(classType.getName().getString(),"SoXipEllipse") == 0 )
			pstate->addGraphicObject(SbXipPStateGraphicObject::POLYLINE, linePoints.getNum() + 1, ptsArray, layerIdx);
		else if ( strcmp(classType.getName().getString(),"SoXipRectangle") == 0 )
			pstate->addGraphicObject(SbXipPStateGraphicObject::POLYLINE, linePoints.getNum() + 1, ptsArray, layerIdx);
		if ( strcmp(classType.getName().getString(),"SoXipPolyLine") == 0 || strcmp(classType.getName().getString(),"SoXipLine") == 0)
			pstate->addGraphicObject(SbXipPStateGraphicObject::POLYLINE, linePoints.getNum() , ptsArray, layerIdx);

		if (ptsArray) 
		{
			delete ptsArray;
			ptsArray = 0;
		}
	}
	catch ( ... )
	{
		if (ptsArray) 
		{
			delete ptsArray;
			ptsArray = 0;
		}

		SoDebugError::post( __FILE__, "Unexpected error in addGraphicToPState()" );
	}
}

void SoXipSaveOverlayPState::addAnnotationToPState(SoXipManipulableShape* shape, SoXipPState *pstate, SbMatrix modelMatrix, SbXipImageDimensions imgDimension, int layerIdx)
{
	if (!(shape && pstate))
		return;

	bool isBoundingBox = true;
	bool isAnchor = true;

	SoMFVec3f linePoints;
	SoMFInt32 dummyCoordIndex;
	SbBool dummyClosed;

	float *ptsArray = 0;

	try
	{
		// extract points from the shape
		shape->extractGeometries( linePoints, dummyCoordIndex, dummyClosed );

		//add the anchor line associated with the text
		int nPoints = linePoints.getNum();
		ptsArray = new float[nPoints];

		XipWorldToImageConvert worldToImage(modelMatrix, imgDimension);
		SbVec3s imagecoordinates;

		for ( int i = 0; i < nPoints; ++i)
		{
			//Now covert the real-world co-ordinates to image co-ordinates
			imagecoordinates = worldToImage.getIndex(linePoints[i]);
			ptsArray[i*2] = imagecoordinates[0];
			ptsArray[i*2+1] = imagecoordinates[1];
		}

		// get the text
		SbString sText = shape->caption.getValue();

		// get the text position
		SbVec3f txtPos = shape->textPosition.getValue();
		SbVec3s txtPosObjCoordinates = worldToImage.getIndex(txtPos);;

		// add the text object into presentation state
		pstate->addTextObject( sText.getString(),
								txtPosObjCoordinates[0],
								txtPosObjCoordinates[1],
								ptsArray[0],
								ptsArray[1],
								isBoundingBox,
								isAnchor,
								layerIdx);
	}
	catch( ... )
	{
		if (ptsArray) 
		{
			delete ptsArray;
			ptsArray = 0;
		}

		SoDebugError::post( __FILE__, "Unexpected error in addAnnotationToPState()" );
	}
}
