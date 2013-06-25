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

#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/actions/SoGetBoundingBoxAction.h> 
#include "SoXipClipPlaneKit.h"


SO_KIT_SOURCE(SoXipClipPlaneKit);


/**
 *	Constructor
 */
SoXipClipPlaneKit::SoXipClipPlaneKit()
{
	SO_KIT_CONSTRUCTOR(SoXipClipPlaneKit);

    SO_NODE_ADD_FIELD(plane,        (SbPlane(SbVec3f(0.0,0.0,1.0), 0.0)));
    SO_NODE_ADD_FIELD(on,           (TRUE));
    SO_NODE_ADD_FIELD(draw,         (FALSE));
    SO_NODE_ADD_FIELD(simMPR,       (FALSE));
    SO_NODE_ADD_FIELD(widthMPR,     (0.1));

    SO_KIT_ADD_CATALOG_ENTRY(top,    SoGroup,           FALSE,  this,   \0, TRUE);

    SO_KIT_ADD_CATALOG_ENTRY(rPlane,    SoXipClipPlane,         TRUE,   top, \0, TRUE);
    SO_KIT_ADD_CATALOG_ENTRY(rDraw,     SoXipDrawClipPlane,     TRUE,   top, \0, TRUE);
    SO_KIT_ADD_CATALOG_ENTRY(rPlaneMpr, SoXipClipPlane,         TRUE,   top, \0, TRUE);
    SO_KIT_ADD_CATALOG_ENTRY(rDrawMpr,  SoXipDrawClipPlane,     TRUE,   top, \0, TRUE);

    SO_KIT_INIT_INSTANCE();

    mNodeId = 0;
}


SoXipClipPlaneKit::~SoXipClipPlaneKit()
{
}


void SoXipClipPlaneKit::initClass()
{
	SO_KIT_INIT_CLASS(SoXipClipPlaneKit, SoBaseKit, "BaseKit");
}

void SoXipClipPlaneKit::setKitConnections()
{
    SoNode * prPlane = getAnyPart("rPlane", TRUE);
    SoNode * prDraw = getAnyPart("rDraw", TRUE);
    SoNode * prPlaneMpr = getAnyPart("rPlaneMpr", TRUE);
    SoNode * prDrawMpr = getAnyPart("rDrawMpr", TRUE);

    if (!prPlane || !prDraw || !prPlaneMpr || !prDrawMpr)
    {
        SoDebugError::post(__FUNCTION__, "missing kit part");
        return;
    }

    //===========//

    prPlaneMpr->getField("flip")->set( "TRUE" );
    prDraw->getField("plane")->connectFrom( prPlane->getField("plane") );
    prDrawMpr->getField("plane")->connectFrom( prPlaneMpr->getField("plane") );

    //===========//

    SoDebugError::postInfo("Clip Plane Kit", "connected");
}




void SoXipClipPlaneKit::GLRender(SoGLRenderAction * action)
{
    //if (mNodeId != getNodeId())
    if (mNodeId == 0)
        setKitConnections();

    if (mNodeId != getNodeId())
    {
        SoNode * prPlane = getAnyPart("rPlane", TRUE);
        SoNode * prDraw = getAnyPart("rDraw", TRUE);
        SoNode * prPlaneMpr = getAnyPart("rPlaneMpr", TRUE);
        SoNode * prDrawMpr = getAnyPart("rDrawMpr", TRUE);

        if (!prPlane || !prDraw || !prPlaneMpr || !prDrawMpr)
        {
            SoDebugError::post(__FUNCTION__, "missing kit part");
            return;
        }

        bool o = (on.getValue() || false);
        bool d = (draw.getValue() || false);
        bool m = (simMPR.getValue() || false);

        if (o && m)
        {
            SbString strP1, strP2;
            SoSFPlane p2f;
            SbPlane p = plane.getValue();
            p2f.setValue( SbPlane( p.getNormal(), p.getDistanceFromOrigin() + widthMPR.getValue() ));
            plane.get( strP1 );
            p2f.get( strP2 );
            prPlane->getField("plane")->set( strP1.getString() );
            prPlane->getField("on")->set( "TRUE" );
            prPlaneMpr->getField("plane")->set( strP2.getString() );
            prPlaneMpr->getField("on")->set( "TRUE" );
        }
        else if (o)
        {
            SbString pStr;
            plane.get( pStr );
            prPlane->getField("plane")->set( pStr.getString() );
            prPlane->getField("on")->set( "TRUE" );
            prPlaneMpr->getField("on")->set( "FALSE" );
        }
        else
        {
            prPlane->getField("on")->set( "FALSE" );
            prPlaneMpr->getField("on")->set( "FALSE" );
        }

        if (d && m)
        {
            prDraw->getField("on")->set( "TRUE" );
            prDrawMpr->getField("on")->set( "TRUE" );
        }
        else if (d)
        {
            prDraw->getField("on")->set( "TRUE" );
            prDrawMpr->getField("on")->set( "FALSE" );
        }
        else
        {
            prDraw->getField("on")->set( "FALSE" );
            prDrawMpr->getField("on")->set( "FALSE" );
        }
    }

	SoBaseKit::GLRender(action); 

    mNodeId = getNodeId();
}

