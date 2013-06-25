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

#include <xip/inventor/core/xipivcore.h>
#include <xip/inventor/coregl/xipivcoregl.h>
#include <xip/inventor/dicom/xipivdicom.h>

#include <xip/inventor/overlay/SoXipFontTypeElement.h>
#include "SoXipFontType.h"
#include <xip/inventor/overlay/SoXipText2.h>
#include <xip/inventor/overlay/SoXipEditText2.h>
#include "SoXipBox.h"
#include "SoXipMeasDistance.h"
#include "SoXipMeasPixelLens.h"

// Elements and Style
#include "SoXipDropShadowElement.h"
#include "SoXipDropShadowStyle.h"
#include <xip/inventor/overlay/SoXipOverlayElement.h>
#include <xip/inventor/overlay/SoXipOverlayManipulatedElement.h>
#include "SoXipOverlayColorElement.h"
#include "SoXipOverlayDrawStyleElement.h"
#include <xip/inventor/overlay/SoXipOverlayColor.h>
#include "SoXipOverlayDrawStyle.h"
#include "SoXipOverlaySettings.h"

// Shapes
#include <xip/inventor/overlay/SoXipShape.h>
#include "SoXipShapeGroup.h"
#include <xip/inventor/overlay/SoXipEllipse.h>
#include "SoXipRectangle.h"
#include "xip/inventor/overlay/SoXipHandlerShape.h"
#include "SoXipPoint.h"
#include "SoXipLine.h"
#include "SoXipLineMeasurement.h"
#include "SoXipAnnotation.h"
#include "SoXipAngle.h"
#include <xip/inventor/overlay/SoXipEditableShape.h>
#include "SoXipContour.h"
#include "SoXipPolygon.h"
#include "SoXipBSpline.h"
#include "SoXipHermiteSpline.h"
#include "SoXipShapeList.h"

// Manipulators
#include <xip/inventor/overlay/SoXipOverlayManipBase.h>
#include "SoXipOverlayTranslationManip.h"
#include "SoXipOverlayTransformBoxManip.h"
#include "SoXipOverlaySelectionManip.h"
#include "SoXipOverlaySelectionFrame.h"
#include "SoXipOverlayHandlerManip.h"
#include "SoXipOverlayManips.h"

// Manager
#include "SoXipOverlayManager.h"
#include "SoXipImageOverlayManager.h"
#include "SoXipDicomOverlayManager.h"
#include "SoXipSegmentationOverlayManager.h"

#include "SoXipImageOverlaySearch.h"
#include "SoXipImageOverlayAdd.h"
#include "SoXipImageOverlayClear.h"

// Utils
#include "SoXipOverlayActions.h"
#include "SoXipLoadOverlay.h"
#include "SoXipSaveOverlay.h"
#include "SoXipOverlayExtractContour.h"
#include "SoXipOverlaySearch.h"
#include "SoXipOverlaySearchContour.h"
#include "SoXipOverlayProperties.h"

// Widgets
#include "SoXipWidgetCamera.h"
#include "SoXipMenuStyleElement.h"
#include "SoXipMenuStyle.h"
#include "SoXipMenuItemBase.h"
#include "SoXipMenuItemSeparator.h"
#include "SoXipMenuItem.h"
#include "SoXipMenuBase.h"
#include "SoXipMenu.h"
#include "SoXipIcon.h"

// Font size
#include "SoXipFontAutoScale.h"

// Measurements
#include "SoXipPolygonArea.h"

// Presentation State
#include "SoXipSaveOverlayPState.h"
#include "SoXipLoadOverlayPState.h"

// Plotting
#include <xip/inventor/overlay/SoXipPlot2AreaElement.h>
#include <xip/inventor/overlay/SoXipPlot2Element.h>
#include "SoXipMarkerSet.h"
#include "SoXipPlot2Area.h"
#include "SoXipPlot2Columns.h"
#include "SoXipPlot2Curve.h"
#include "SoXipPlot2Extent.h"
#include "SoXipPlot2Grid.h"
#include "SoXipPlot2Histogram.h"
#include "SoXipPlot2Legend.h"
#include "SoXipPlot2Ruler.h"
#include "SoXipPlot2Samples.h"

#include "SoXipLutColorBar.h"
#include "SoXipScaleBar.h"
#include "SoXipDisplayImageText.h"
#include "SoXipOverlayFilter.h"
#include "SoXipOverlayFilterElement.h"

#include "SoXipSegmentationOverlayManager.h"

#include "SoXipImageTextColor.h"
#include <xip/inventor/overlay/SoXipImageTextColorElement.h>


int XIPIVOVERLAY_API xipivoverlay_init()
{
	static bool isInit = false;
	if(isInit)
		return 1;
	isInit = true;

	xipivcore_init();
	xipivcoregl_init();
	xipivdicom_init();

  // Elements and Style
  SoXipDropShadowElement::initClass();
  SoXipDropShadowStyle::initClass();
  SoXipOverlayElement::initClass();
  SoXipOverlayManipulatedElement::initClass();
  SoXipOverlayColorElement::initClass();
  SoXipOverlayDrawStyleElement::initClass();
  SoXipOverlayColor::initClass();
  SoXipOverlayDrawStyle::initClass();
  SoXipOverlaySettings::initClass();
  SoXipFontTypeElement::initClass();
  SoXipOverlayFilterElement::initClass();

  SoXipBox::initClass();
  SoXipFontType::initClass();
  SoXipText2::initClass();
  SoXipEditText2::initClass();
  SoXipMeasDistance::initClass();
  SoXipMeasPixelLens::initClass();

  // Shapes
  SoXipShape::initClass();
  SoXipShapeGroup::initClass();
  SoXipManipulableShape::initClass();
  SoXipEllipse::initClass();
  SoXipRectangle::initClass();
  SoXipHandlerShape::initClass();
  SoXipPolyLine::initClass();
  SoXipLine::initClass();
  SoXipLineMeasurement::initClass();
  SoXipPoint::initClass();
  SoXipAnnotation::initClass();
  SoXipAngle::initClass();
  SoXipEditableShape::initClass();
  SoXipPolygon::initClass();
  SoXipContour::initClass();
  SoXipBSpline::initClass();
  SoXipHermiteSpline::initClass();
  SoXipShapeList::initClass();

  // Manipulators
  SoXipOverlayManipBase::initClass();
  SoXipOverlayTranslationManip::initClass();
  SoXipOverlayTransformBoxManip::initClass();
  SoXipOverlaySelectionManip::initClass();
  SoXipOverlaySelectionFrame::initClass();
  SoXipOverlayHandlerManip::initClass();
  SoXipOverlayManips::initClass();

	// Manager
	SoXipOverlayManager::initClass();	
	SoXipDicomOverlayManager::initClass();
	SoXipImageOverlayManager::initClass();
	SoXipImageOverlaySearch::initClass();
	SoXipImageOverlayAdd::initClass();
	SoXipImageOverlayClear::initClass();

  // Segmentation
  SoXipSegmentationOverlayManager::initClass();

  // Utils
  SoXipOverlayActions::initClass();
  SoXipLoadOverlay::initClass();
  SoXipSaveOverlay::initClass();
  SoXipOverlayExtractContour::initClass();
  SoXipOverlaySearch::initClass();
  SoXipOverlaySearchContour::initClass();
  SoXipOverlayProperties::initClass();
		
	// Widgets
	SoXipWidgetCamera::initClass();
	SoXipMenuStyleElement::initClass();
	SoXipMenuStyle::initClass();
	SoXipMenuItemBase::initClass();
	SoXipMenuItemSeparator::initClass();
	SoXipMenuItem::initClass();
	SoXipMenuBase::initClass();
	SoXipMenu::initClass();
	SoXipIcon::initClass();

    // Measurements
    SoXipPolygonArea::initClass();

	// Font size
	SoXipFontAutoScale::initClass();

	// Presentation State
	SoXipSaveOverlayPState::initClass();
	SoXipLoadOverlayPState::initClass();

	// Plotting
	SoXipPlot2Element::initClass();
	SoXipPlot2AreaElement::initClass();
	SoXipMarkerSet::initClass();
	SoXipPlot2Area::initClass();
	SoXipPlot2Columns::initClass();
	SoXipPlot2Curve::initClass();
	SoXipPlot2Extent::initClass();
	SoXipPlot2Grid::initClass();
	SoXipPlot2Histogram::initClass();
	SoXipPlot2Legend::initClass();
	SoXipPlot2Ruler::initClass();
	SoXipPlot2Samples::initClass();

	SoXipLutColorBar::initClass();
	SoXipScaleBar::initClass();
	SoXipDisplayImageText::initClass();
        SoXipOverlayFilter::initClass();

	SoXipSegmentationOverlayManager::initClass();

	SoXipImageTextColorElement::initClass();
	SoXipImageTextColor::initClass();

	return 1;
}

static int initted = FALSE;    // a little protection--probably unnecessary

#ifdef WIN32

BOOL APIENTRY DllMain( HINSTANCE hinstDLL, DWORD reason, LPVOID )
{
	if( reason == DLL_PROCESS_ATTACH )
		xipivoverlay_init();

	return TRUE;
}

#else /* not WIN32 */

void __attribute__ ((constructor)) _init(void)// don't write this if DllMain is to be used
{
	int err;

	xipivoverlay_init();

	initted = TRUE;
	//return 0;
}

void __attribute__ ((destructor)) _fini(void)
{
	//printf ("fini print.\n");
}

//forcing initialization through static member (as workaround)
static const bool initMe = xipivoverlay_init();

#endif /* WIN32 */

