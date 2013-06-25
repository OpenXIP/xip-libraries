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
#include <Inventor/fields/SoMFNode.h>
#include <xip/inventor/dicom/SoXipPState.h>
#include <xip/inventor/dicom/xipivDicomUtils.h>
#include <xip/inventor/core/SbXipImage.h>
#include <xip/inventor/core/SbXipCoordinateTransform.h>

#include <xip/inventor/overlay/SoXipEditableShape.h>
#include "SoXipAnnotation.h"
#include "SoXipShapeList.h"
#include "SoXipLoadOverlayPState.h"


SO_ENGINE_SOURCE(SoXipLoadOverlayPState);


void SoXipLoadOverlayPState::initClass()
{
	SO_ENGINE_INIT_CLASS(SoXipLoadOverlayPState, SoEngine, "Engine");
}


SoXipLoadOverlayPState::SoXipLoadOverlayPState()
{
	SO_ENGINE_CONSTRUCTOR(SoXipLoadOverlayPState);

	SO_ENGINE_ADD_INPUT( presentationstate, (0) );
	SO_ENGINE_ADD_OUTPUT(overlays, SoMFNode);

	mShapeList = 0;
}


SoXipLoadOverlayPState::~SoXipLoadOverlayPState()
{
	if (mShapeList)
	{
		mShapeList->unref();
	}
}

SoXipShape* SoXipLoadOverlayPState::createNewShape(const SbString classname)
{
	SoType type = SoType::fromName( classname );
	if( !type.canCreateInstance() )
	{
		SoDebugError::post( __FILE__, "Unknown shape type '%s'", classname  );
		return 0;
	}

	if( !type.isDerivedFrom( SoXipShape::getClassTypeId() ) )
	{
		SoDebugError::post( __FILE__, "Invalid shape class '%s'", classname );
		return 0;
	}

	SoXipShape* newShape = (SoXipShape *) type.createInstance();
	if( !newShape )
	{
		SoDebugError::post( __FILE__, "Shape creation failed" );
		return 0;
	}

	if (mShapeList)
		mShapeList->addChild(newShape);

	return newShape;
}

void SoXipLoadOverlayPState::evaluate()
{
	if (!mShapeList)
	{
		mShapeList = new SoXipShapeList;
		mShapeList->ref();
	}

	mShapeList->removeAllChildren();

	SO_ENGINE_OUTPUT( overlays, SoMFNode, setValue(mShapeList) );

	SoXipPState *pState = presentationstate.getValue();

	if (!pState)
		return;

	try
	{
		SbMatrix modelMatrix = getModelMatrixFromDICOM(pState->getDataset());
		XipDicomAttributes imageAttributes = getAttributesFromDicom(pState->getDataset());
		SbXipImageDimensions imgDimension(imageAttributes.width, imageAttributes.height, imageAttributes.numberOfSlices);

		XipImageToWorldConvert imageToWorld(modelMatrix, imgDimension);

		int nLayer = pState->getNumberOfLayers();
		for ( int i = 0 ; i < nLayer; i++)
		{
			/* Text Object */
			SbXipPStateTextObject* pTxtObj = NULL;
			int nTextObjects = pState->getNumberOfTextObjects(i);

			for ( int tIndex = 0; tIndex < nTextObjects; tIndex++ )
			{
				pTxtObj = pState->getTextObject(i, tIndex);
				if ( !pTxtObj ) 
					break;

				SoXipShape* shape = createNewShape("SoXipAnnotation");
				if(!shape)
					continue;

				if ( pTxtObj->haveAnchorPoint())
					((SoXipAnnotation*)shape)->textAnchored.setValue(true);

				// set status to NONE
				((SoXipAnnotation*)shape)->status.setValue(0);

				//Points
				SbVec3f pnts[2];
				pnts[0].setValue(pTxtObj->getAnchorPoint_x(), pTxtObj->getAnchorPoint_y(), 0);
				pnts[1].setValue(pTxtObj->getBoundingBoxTLHC_x(), pTxtObj->getBoundingBoxTLHC_y(), 0);

				((SoXipAnnotation*)shape)->point.set1Value(0, imageToWorld.get3DPoint(pnts[0]));
				((SoXipAnnotation*)shape)->point.set1Value(1, imageToWorld.get3DPoint(pnts[1]));

				//Rank
				((SoXipAnnotation*)shape)->setRank(tIndex+1);

				// get text
				SbString sText = pTxtObj->getText();

				// set caption
				((SoXipAnnotation*)shape)->setCaption(sText);

				if (pTxtObj) 
				{
					delete pTxtObj;
					pTxtObj = 0;
				}
			}
			
			/* Graphic Object */
			SbXipPStateGraphicObject* pGraphicObj = NULL;
			int nGraphicObjects = pState->getNumberOfGraphicObjects(i);

			for ( int gIndex = 0;  gIndex < nGraphicObjects; gIndex++ )
			{
				pGraphicObj = pState->getGraphicObject(i, gIndex);

				switch ( pGraphicObj->getGraphicType() )
				{
				case SbXipPStateGraphicObject::POLYLINE:
						{
							SoXipShape* shape = createNewShape("SoXipPolyLine");
							if(!shape)
								continue;

							SbVec3f pt(0., 0., 0.);
							int nPoints = pGraphicObj->getNumberOfPoints();
							for ( int i=0; i< nPoints; i++)
							{
								pGraphicObj->getPoint(i, pt[0], pt[1]);
								((SoXipPolyLine*)shape)->point.set1Value(i, imageToWorld.get3DPoint(pt));
							}

							// set status to NONE
							((SoXipPolyLine*)shape)->status.setValue(0);
						}
							break;
				case SbXipPStateGraphicObject::INTERPOLATED:
							break;
				case SbXipPStateGraphicObject::CIRCLE:
							break;
				case SbXipPStateGraphicObject::ELLIPSE:
							break;
				case SbXipPStateGraphicObject::POINT:
							break;
				}

				if (pGraphicObj) 
				{
					delete pGraphicObj;
					pGraphicObj = 0;
				}
			}
		}

	}
	catch (...)
	{
		SoError::post("Failed to load overlays from presentation state in SoXipLoadOverlayPState.");
	}

	SO_ENGINE_OUTPUT( overlays, SoMFNode, setValue(mShapeList) );
}
