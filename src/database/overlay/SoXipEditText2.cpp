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

#include <xip/inventor/core/SoXipCursor.h>
#include <Inventor/actions/SoHandleEventAction.h>
#include <Inventor/SoPickedPoint.h>
#include <Inventor/events/SoMouseButtonEvent.h>
#include <Inventor/events/SoLocation2Event.h>
#include <Inventor/events/SoKeyboardEvent.h>
#include <Inventor/sensors/SoFieldSensor.h>
#include <xip/inventor/overlay/SoXipEditText2.h>
#include <string.h>
#include <xip/system/defines.h>

SO_NODE_SOURCE( SoXipEditText2 );

SoXipEditText2::SoXipEditText2()
{
	SO_NODE_CONSTRUCTOR( SoXipEditText2 );

	SO_NODE_ADD_FIELD( displayBBox, (FALSE) );
	SO_NODE_ADD_FIELD( isEditing, (FALSE) );

	mEditString = std::string( string.getValue().getString() );	

	mEditingSensor = new SoFieldSensor( editingSensorCB, this );
	mEditingSensor->setPriority(0);
	mEditingSensor->attach( &isEditing );
}

void
SoXipEditText2::initClass()
{
	SO_NODE_INIT_CLASS( SoXipEditText2, SoXipText2, "SoXipText2" );
}

SoXipEditText2::~SoXipEditText2()
{
	if( mEditingSensor )
		delete mEditingSensor;
	mEditingSensor = 0;
}

void
SoXipEditText2::onStringChange()
{
	mEditString = std::string( string.getValue().getString() );
}

void
SoXipEditText2::editingSensorCB( void* userData, SoSensor* )
{
	((SoXipEditText2 *) userData)->toggleEditing();
}

void
SoXipEditText2::toggleEditing()
{
	if( isEditing.getValue() )
	{
		SoXipCursor::setCursor( "EDIT" );

		mCursorPos = string.getValue().getLength();

		mEditString.insert( mCursorPos, 1, '_' );
	}
	else
	{
		mEditString.erase( mCursorPos, 1 );		
	}

	// Update the string without triggering the field sensor
	mStringSensor->detach();
	string.setValue( mEditString.c_str() );
	mStringSensor->attach( &string );
}

SbBool
SoXipEditText2::isPicked( SoHandleEventAction* action ) const
{
	const SoPickedPoint* pickedPoint = action->getPickedPoint();
	if( pickedPoint )
	{
		SoFullPath* path = (SoFullPath *) pickedPoint->getPath();

		return path->containsNode( this );
	}
	return FALSE;
}

void
SoXipEditText2::handleEvent( SoHandleEventAction* action )
{
    if( action->isHandled() )
		return ;
    
    // Mouse Press Event
    //
	if( SO_MOUSE_PRESS_EVENT( action->getEvent(), BUTTON1 ) )
	{
        if( isEditing.getValue() == TRUE && isPicked( action ) == FALSE )
		{            
            isEditing.setValue( FALSE );

            action->releaseGrabber();
            action->setHandled();
		}
        
        if( action->getEvent()->wasShiftDown() )
		{
			if( isEditing.getValue() == FALSE && isPicked( action ) == TRUE )
			{
				// Set editing mode to true. Set the grabber to get the next
				// keyboard events.
				isEditing.setValue( TRUE );

				action->setHandled();
				action->setGrabber( this );
			}
		}
	}
    
    // Mouse Move Event
    //
    else if( action->getEvent()->isOfType( SoLocation2Event::getClassTypeId() ) )
	{
        if( isEditing.getValue() || isPicked( action ) )
        {
            action->setHandled();
			SoXipCursor::setCursor( "EDIT" );
        }
	}
	
    // Keyboard Event
    //
	else if( action->getEvent()->isOfType( SoKeyboardEvent::getClassTypeId() ) && SO_KEY_PRESS_EVENT( action->getEvent(), ANY ) )
	{
		if( isEditing.getValue() )
		{
			action->setHandled();

			const SoKeyboardEvent* kEvent = (const SoKeyboardEvent *) action->getEvent();
			
			switch( kEvent->getKey() )
			{
			case SoKeyboardEvent::ESCAPE:
				isEditing.setValue( FALSE );				
				action->releaseGrabber();
				break ;
			case SoKeyboardEvent::KEY_DELETE:
				// Add -1 for the underscore, showing the cursor position
				if( mCursorPos < string.getValue().getLength() - 1)
					mEditString.erase( mCursorPos, 1 );

				break ;

			case SoKeyboardEvent::BACKSPACE:
				if ( mCursorPos > 0 )
					mEditString.erase( mCursorPos-- - 1, 1 );
				break ;

			case SoKeyboardEvent::LEFT_ARROW:
				if( mCursorPos > 0 )
					-- mCursorPos;
				break ;
				
			case SoKeyboardEvent::RIGHT_ARROW:
				if( mCursorPos < string.getValue().getLength() )
					++ mCursorPos;
				break ;

			case SoKeyboardEvent::RETURN:
				mEditString.insert( mCursorPos, 1, '\n' );
				++ mCursorPos;
				break ;

			default:
				{
					char printableChar;
					if( ( printableChar = kEvent->getPrintableCharacter() ) )
					{
						mEditString.insert( mCursorPos, 1, printableChar );
						++ mCursorPos;
					}
					else return ;						
				}
			}

			// Update the string without triggering the field sensor
			mStringSensor->detach();
			string.setValue( mEditString.c_str() );
			mStringSensor->attach( &string );
		}
	}
}


void
SoXipEditText2::GLRender(SoGLRenderAction *action)
{
	SoXipText2::GLRender( action );

	if( displayBBox.getValue() )
	{
		glPushAttrib(GL_POLYGON_BIT);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		const float *minf = mBBox.getMin().getValue(), *maxf = mBBox.getMax().getValue();

		glBegin(GL_QUADS);
		glVertex3f(minf[0], minf[1], minf[2]);
		glVertex3f(maxf[0], minf[1], maxf[2]);
		glVertex3f(maxf[0], maxf[1], maxf[2]);
		glVertex3f(minf[0], maxf[1], minf[2]);
		glVertex3f(minf[0], minf[1], minf[2]);
		glEnd();
		glPopAttrib();
	}
}
