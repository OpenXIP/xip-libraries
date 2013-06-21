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
#include <Inventor/elements/SoViewportRegionElement.h>
#include <Inventor/actions/SoGetBoundingBoxAction.h>
#include <Inventor/fields/SoSFMatrix.h>
#include "SoXipSlicerVolRender.h"
#include "SoXipSlicer.h"

SO_KIT_SOURCE(SoXipSlicerVolRender);

/**
 *	Constructor
 */
SoXipSlicerVolRender::SoXipSlicerVolRender()
{
	SO_KIT_CONSTRUCTOR(SoXipSlicerVolRender);

	//	The kit contains a SoXipUniformMatrix4 (xip_boundingModelMatrix)
	SO_KIT_ADD_CATALOG_ENTRY(boundingBoxMatrix, SoXipUniformMatrix4, FALSE, this, \0 , FALSE);	
	//	The kit contains the original SoXipSlicer node
	SO_KIT_ADD_CATALOG_ENTRY(slicer, SoXipSlicer, FALSE, this, \0 , FALSE);

	SO_KIT_INIT_INSTANCE();

    SO_NODE_ADD_FIELD( numSlices, (512) );

    SO_NODE_ADD_FIELD(compositing, (BACK_TO_FRONT));
	SO_NODE_ADD_FIELD(mode, (VRT));

    // Set up static info for enumerated type field
    SO_NODE_DEFINE_ENUM_VALUE(Compositing, BACK_TO_FRONT);
    SO_NODE_DEFINE_ENUM_VALUE(Compositing, FRONT_TO_BACK);

	SO_NODE_DEFINE_ENUM_VALUE(Mode, VRT);
	SO_NODE_DEFINE_ENUM_VALUE(Mode, MAXIP);
	SO_NODE_DEFINE_ENUM_VALUE(Mode, MINIP);

    // Set up info in enumerated type field
    SO_NODE_SET_SF_ENUM_TYPE(compositing, Compositing);
	SO_NODE_SET_SF_ENUM_TYPE(mode, Mode);
}


SoXipSlicerVolRender::~SoXipSlicerVolRender()
{
}


void SoXipSlicerVolRender::initClass()
{
	SO_KIT_INIT_CLASS(SoXipSlicerVolRender, SoBaseKit, "BaseKit");

}

void SoXipSlicerVolRender::GLRender(SoGLRenderAction * action)
{

    SoNode *bboxMatObj = (SoNode*) getAnyPart("boundingBoxMatrix", TRUE);
    if (bboxMatObj)
    {
        SbViewportRegion viewportRegion = SoViewportRegionElement::get(action->getState());

        SbMatrix mat;
        mat.identity();
        const SoPath *path = action->getCurPath();
        if (path)
        {
            // get the node one before this
            SoNode *node = path->getNodeFromTail(1);
            if (node)
            {

                // compute bounding box
                SoGetBoundingBoxAction bboxAction(viewportRegion);

                // Find the bounding box of the scene
                bboxAction.apply(node);

                SbBox3f box = bboxAction.getBoundingBox();

				//	create the modelview matrix taking the bouding box into account
                if (!box.isEmpty())
                {
                    SbVec3f origin, size;

                    box.getOrigin(origin[0], origin[1], origin[2]);
                    box.getSize(size[0], size[1], size[2]);

                    mat.setTransform(origin, SbRotation(SbMatrix::identity()), size);
                }

            }
        }

		// Set the matrix node's value
        bboxMatObj->set("name xip_boundingModelMatrix");
		SoSFMatrix *matrixField = (SoSFMatrix *) bboxMatObj->getField("value");
		if (matrixField)
			matrixField->setValue(mat);
    }

	//	Updates fields of the original slicer node
    SoXipSlicer *slicerObj = (SoXipSlicer*) getAnyPart("slicer", TRUE);
    if (slicerObj)
    {
        if (slicerObj->compositing.getValue() != compositing.getValue())
            slicerObj->compositing.setValue(compositing.getValue());

        if (slicerObj->numSlices.getValue() != numSlices.getValue())
            slicerObj->numSlices.setValue(numSlices.getValue());

		if (slicerObj->mode.getValue() != mode.getValue())
					slicerObj->mode.setValue(mode.getValue());
    }


	doAction(action); 

	SoBaseKit::GLRender(action); 
}


