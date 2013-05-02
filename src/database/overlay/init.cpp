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

#endif /* WIN32 */

