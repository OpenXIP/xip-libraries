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

#include <xip/inventor/core/SoXipDataImage.h>
#include <xip/inventor/core/SoXipDataImageElement.h>
#include <Inventor/actions/SoCallbackAction.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/actions/SoHandleEventAction.h>
#include <Inventor/actions/SoRayPickAction.h>
#include <Inventor/actions/SoWriteAction.h>
#include <Inventor/actions/SoSearchAction.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoSwitch.h>
#include <Inventor/nodes/SoBaseColor.h>
#include <Inventor/nodes/SoLabel.h>
#include <Inventor/sensors/SoFieldSensor.h>
#include <Inventor/sensors/SoNodeSensor.h>
#include <Inventor/sensors/SoTimerSensor.h>
#include "SoXipSegmentationOverlayManager.h"
#include <xip/inventor/overlay/SoXipShape.h>
#include "SoXipContour.h"
#include "SoXipLine.h"
#include "SoXipShapeList.h"
#include <xip/inventor/overlay/XipOverlayUtils.h>
// Inventor events
#include <Inventor/events/SoMouseButtonEvent.h>
#include <Inventor/events/SoLocation2Event.h>
#include <Inventor/events/SoKeyboardEvent.h>

#include <xip/system/standard.h>

SO_NODE_SOURCE( SoXipSegmentationOverlayManager );

SoXipSegmentationOverlayManager::SoXipSegmentationOverlayManager()
{
	SO_NODE_CONSTRUCTOR( SoXipSegmentationOverlayManager );

	SO_NODE_ADD_FIELD( OverlayOption, ("") );
	//SO_NODE_ADD_FIELD( OverlayAction, (0) );
	//SO_NODE_ADD_FIELD( OverlayEnable, (true) );

	//!
	mMouseDownTime			= SbTime::zero();
	mMouseUpTime			= SbTime::zero();
	mMouseDownPos			= SbVec2s(-1, -1);

}

SoXipSegmentationOverlayManager::~SoXipSegmentationOverlayManager()
{
}

void SoXipSegmentationOverlayManager::initClass()
{
	SO_NODE_INIT_CLASS( SoXipSegmentationOverlayManager, SoXipOverlayManager, "SoXipOverlayManager" );
}

void SoXipSegmentationOverlayManager::GLRender( SoGLRenderAction* action )
{
	int numShapes = 0 ;

    SoXipOverlayManager::GLRender( action );
}

void SoXipSegmentationOverlayManager::handleEvent( SoHandleEventAction* action )
{
	int numShapes = 0 ;
	SoXipShapeList* list = getCurrentList ( ) ;
	if (list != NULL) numShapes = list->getNumChildren ( ) ;

	//if (numShapes > 0)
	//{
	//	SoXipShape *pshape = (SoXipShape*)list->getChild(numShapes-1) ;
	//	if (pshape != NULL) SetupOverlayAction ( action, pshape ) ;
	//}

	if( action->isHandled() ) return ;
	
	SoXipOverlayManager::handleEvent( action );

	if (list != NULL)
	{
		int nnumShapes = list->getNumChildren ( ) ;
		//! A shape created 
		if (nnumShapes > numShapes)
		{
		    // Returns pointer to nth child node
			SoXipShape *pshape = (SoXipShape*)list->getChild(numShapes) ;
			if (pshape != NULL) SetupOverlayOption ( pshape, OverlayOption ) ;
		}
	}
}

void SoXipSegmentationOverlayManager::pick( SoPickAction* action)
{
	SoXipOverlayManager::pick( action );
}

void SoXipSegmentationOverlayManager::callback( SoCallbackAction* action)
{
	SoXipOverlayManager::callback( action );
}

int SoXipSegmentationOverlayManager::SetupOverlayOption ( SoXipShape *pshape, SoMFString& OO )
{
	if (pshape == NULL) return ( 0 ) ;

	const SbString& classname = shapeClassName.getValue();

	int sh, len ;
	SbString *pstr ;
	char *sz, szTemp[256] ;
	char *szPrefix =  "SoXip" ;
	char *szSuffix =  "/SoXip" ;

	{
		char *szName = (char*)classname.getString () ;
		//
		if (szName == NULL) return ( 0 ) ;
		pstr = (SbString*)OO.getValues ( 0 ) ;
		if (pstr == NULL) return ( 0 ) ;
	
		//! Default operations 
		strncpy ( szTemp, szName, 5 ) ; szTemp[5] = 0 ;
#ifdef WIN32
		if (stricmp ( szTemp, szPrefix ) == 0)
#else
		if (strcasecmp ( szTemp, szPrefix ) == 0)
#endif /* WIN32 */
		{
			pshape->setRank ( -1 ) ;
		}

#ifdef WIN32
		if (stricmp ( szName, "SoXipContour" ) == 0)
#else
		if (strcasecmp ( szName, "SoXipContour" ) == 0)
#endif /* WIN32 */
		{
			SoXipContour *p = (SoXipContour*)pshape ;
			//! Default settings
			//p->closeOnDblClick = false ;
			//p->closed = false ;

			for (sh=0; sh<OO.getNum(); sh++)
			{
				sz = (char*)pstr[sh].getString ( ) ; if (sz == NULL) continue ;
				len = pstr[sh].getLength ( ) ; if (len < 1) continue ;

				//if (stricmp ( sz, "NonClosed" ) == 0)	{ p->closed = false ;	p->closeOnDblClick = false ;	continue ; }
				//if (stricmp ( sz, "Closed" ) == 0)		{ p->closed = true ;	p->closeOnDblClick = true ;		continue ; }
				// SoDebugError::postInfo ( szName, sz ) ;
			}
		}
	}

	return ( 1 ) ;
}

int SoXipSegmentationOverlayManager::SetupOverlayAction ( SoHandleEventAction* action, SoXipShape *pshape )
{
	// Maximal distance between two consecutive mouse down positions
	// allowed to generate a double-click.
	int DoubleClickMaxJump = 2;
	// Maximal time between two mouse clicks to be considered as a
	// double-click.
	SbTime DoubleClickTime = SbTime(0.5);
	// Time corresponding to a click
	SbTime ClickTime = SbTime(0.1);

	if (pshape == NULL) return ( 0 ) ;
	const SbString& classname = shapeClassName.getValue();
	char *szName = (char*)classname.getString () ;
	if (szName == NULL) return ( 0 ) ;

	SoDebugError::postInfo ( szName, "test" ) ;

	SbVec3f pos;
	const SbVec2s& mousePosition = action->getEvent()->getPosition() ;
	
	//if( SO_MOUSE_RELEASE_EVENT( action->getEvent(), BUTTON1 ) && action->getGrabber() == this ) 
	if( SO_MOUSE_RELEASE_EVENT( action->getEvent(), BUTTON1 )) 
	{
		SoDebugError::postInfo ( szName, "test" ) ;
		mMouseUpTime = action->getEvent()->getTime();
		{
		}
	}
	else if( SO_MOUSE_PRESS_EVENT( action->getEvent(), BUTTON1 ) )
	{
		SbTime tim = action->getEvent()->getTime();

		// Compute the distance between the last mouse press event and this one
		SbVec2s v = (mMouseDownPos - mousePosition);
		float mouseJump = sqrtf( v.dot(v) );

		// Do not perform a double-click if the time between two mouse press
		// events is higher than the default time set for double-clicks, or if
		// the mouse jumped further than the tolerance set (without tolerance
		// it is more difficult to get a double-click.
		if ( (tim - mMouseDownTime) < DoubleClickTime && mouseJump < DoubleClickMaxJump )
		{
			mMouseDownTime = SbTime::zero();
			mMouseDownPos = SbVec2s(-1, -1);
		}
		else
		{
			mMouseDownTime = action->getEvent()->getTime() ;
		}
	}

	return ( 1 ) ;
}


