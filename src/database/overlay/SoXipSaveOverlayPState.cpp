/*
 *  COPYRIGHT NOTICE.  Copyright (C) 2007 Siemens Corporate Research, 
 *  Inc. ("caBIG(tm) Participant"). The eXtensible Imaging Platform
 *  (XIP) was created with NCI funding and is part of the caBIG(tm) 
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