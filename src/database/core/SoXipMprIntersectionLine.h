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
#ifndef SOXIPMPRINTERSECTIONLINE_H
#define SOXIPMPRINTERSECTIONLINE_H

#include <Inventor/nodekits/SoBaseKit.h>
#include <Inventor/fields/SoSFMatrix.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFColor.h>
#include <Inventor/fields/SoSFUShort.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoMatrixTransform.h>
#include <Inventor/nodes/SoBaseColor.h>
#include <Inventor/nodes/SoDrawStyle.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoLineSet.h>


class SoFieldSensor;
class SoSensor;


// utility class for grouping nodes of the intersection line geometry
class SoXipMprIntersectionLineKit : public SoBaseKit 
{
	SO_KIT_HEADER(SoXipMprIntersectionLineKit);

public:
	SoXipMprIntersectionLineKit()
	{
		SO_KIT_CONSTRUCTOR(SoXipMprIntersectionLineKit);

		isBuiltIn = TRUE;

		// Initialize children catalog and add entries to it:
		//
		//           separator
		//               |
		//      +--------+-------+----------+----------+------------+------------+------------+
		//      |        |       |          |          |            |            |            |
		//  transform  color  drawStyle  lineSep  arrowCoord  arrowLineSet  crossCoord  coordLineSet
		//                                  |
		//              +---------+---------+------------+----------+
		//              |         |         |            |          |
		//          lineCoord  lineSet  gapDrawStyle  gapCoord  gapLineSet
		//
		SO_KIT_ADD_CATALOG_ENTRY(separator, SoSeparator, TRUE, this, \0 ,TRUE);
		SO_KIT_ADD_CATALOG_ENTRY(transform, SoMatrixTransform, TRUE, separator, \0 ,TRUE);
		SO_KIT_ADD_CATALOG_ENTRY(color, SoBaseColor, TRUE, separator, \0 ,TRUE);
		SO_KIT_ADD_CATALOG_ENTRY(drawStyle, SoDrawStyle, TRUE, separator, \0 ,TRUE);
		SO_KIT_ADD_CATALOG_ENTRY(lineSep, SoSeparator, TRUE, separator, \0 ,FALSE);
		SO_KIT_ADD_CATALOG_ENTRY(lineCoord, SoCoordinate3, TRUE, lineSep, \0 ,TRUE);
		SO_KIT_ADD_CATALOG_ENTRY(lineSet, SoLineSet, TRUE, lineSep, \0 ,TRUE);
		SO_KIT_ADD_CATALOG_ENTRY(gapDrawStyle, SoDrawStyle, TRUE, lineSep, \0 ,TRUE);
		SO_KIT_ADD_CATALOG_ENTRY(gapCoord, SoCoordinate3, TRUE, lineSep, \0 ,TRUE);
		SO_KIT_ADD_CATALOG_ENTRY(gapLineSet, SoLineSet, TRUE, lineSep, \0 ,TRUE);
		SO_KIT_ADD_CATALOG_ENTRY(arrowCoord, SoCoordinate3, TRUE, separator, \0 ,TRUE);
		SO_KIT_ADD_CATALOG_ENTRY(arrowLineSet, SoLineSet, TRUE, separator, \0 ,TRUE);
		SO_KIT_ADD_CATALOG_ENTRY(crossCoord, SoCoordinate3, TRUE, separator, \0 ,TRUE);
		SO_KIT_ADD_CATALOG_ENTRY(crossLineSet, SoLineSet, TRUE, separator, \0 ,TRUE);

		SO_KIT_INIT_INSTANCE();
	};

	static void initClass()
	{
		SO_KIT_INIT_CLASS(SoXipMprIntersectionLineKit, SoBaseKit, "BaseKit");
	};

public:
	// Defines fields for the new parts in the catalog
	SO_KIT_CATALOG_ENTRY_HEADER(separator);
	SO_KIT_CATALOG_ENTRY_HEADER(transform);
	SO_KIT_CATALOG_ENTRY_HEADER(color);
	SO_KIT_CATALOG_ENTRY_HEADER(drawStyle);
	SO_KIT_CATALOG_ENTRY_HEADER(lineSep);
	SO_KIT_CATALOG_ENTRY_HEADER(lineCoord);
	SO_KIT_CATALOG_ENTRY_HEADER(lineSet);
	SO_KIT_CATALOG_ENTRY_HEADER(gapDrawStyle);
	SO_KIT_CATALOG_ENTRY_HEADER(gapCoord);
	SO_KIT_CATALOG_ENTRY_HEADER(gapLineSet);
	SO_KIT_CATALOG_ENTRY_HEADER(arrowCoord);
	SO_KIT_CATALOG_ENTRY_HEADER(arrowLineSet);
	SO_KIT_CATALOG_ENTRY_HEADER(crossCoord);
	SO_KIT_CATALOG_ENTRY_HEADER(crossLineSet);
};



class SoXipMprIntersectionLine : public SoXipMprIntersectionLineKit 
{
	SO_KIT_HEADER(SoXipMprIntersectionLine);

public:
	SoXipMprIntersectionLine();
	static void initClass();

private:
	virtual ~SoXipMprIntersectionLine();

public:
	SoSFMatrix planeMatrix;
	SoSFMatrix intersectMatrix;
	SoSFVec3f  centerPosition;
	SoSFBool   centerGap;
	SoSFBool   centerCross;
	SoSFBool   normalIndicators;
	SoSFBool   stubs;
	SoSFFloat  stubScale;

protected:
	virtual void update();
	virtual void clear();
	virtual void fieldSensorCB(SoSensor *sensor);
	virtual void GLRender(SoGLRenderAction * action);

	SoBaseKit *myNodeKit;
	SoFieldSensor* mFieldSensors[6];
	float mViewportAspectRatio;
	SbBool mNeedsUpdate;

private:
	static void fieldSensorCBFunc(void *user, SoSensor *sensor);
};


#endif // SOXIPMPRINTERSECTIONLINE_H
