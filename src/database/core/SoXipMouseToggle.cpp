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

#include "SoXipMouseToggle.h"
#include <Inventor/actions/SoActions.h>
#include <Inventor/events/SoLocation2Event.h>
#include <Inventor/events/SoMouseButtonEvent.h>
#include <Inventor/sensors/SoFieldSensor.h>


SO_NODE_SOURCE(SoXipMouseToggle);


void SoXipMouseToggle::initClass()
{
	SO_NODE_INIT_CLASS(SoXipMouseToggle, SoNode, "Node");
}


SoXipMouseToggle::SoXipMouseToggle()
{
	SO_NODE_CONSTRUCTOR(SoXipMouseToggle);

	mMouseDownPos = SbVec2f(0, 0);
	mViewportRegion = SbViewportRegion(1, 1);
	mIndex = -1;

    SO_NODE_DEFINE_ENUM_VALUE(mouseButtonType, BUTTON1);
    SO_NODE_DEFINE_ENUM_VALUE(mouseButtonType, BUTTON2);
    SO_NODE_DEFINE_ENUM_VALUE(mouseButtonType, BUTTON3);
    SO_NODE_SET_SF_ENUM_TYPE(mouse, mouseButtonType);
	SO_NODE_ADD_FIELD(mouse, (BUTTON3));

	SO_NODE_ADD_FIELD(sequence, (0));

    SO_NODE_DEFINE_ENUM_VALUE(valueType, VALUE_0);
    SO_NODE_DEFINE_ENUM_VALUE(valueType, VALUE_1);
    SO_NODE_DEFINE_ENUM_VALUE(valueType, VALUE_2);
    SO_NODE_DEFINE_ENUM_VALUE(valueType, VALUE_3);
    SO_NODE_DEFINE_ENUM_VALUE(valueType, VALUE_4);
    SO_NODE_DEFINE_ENUM_VALUE(valueType, VALUE_5);
    SO_NODE_DEFINE_ENUM_VALUE(valueType, VALUE_6);
    SO_NODE_DEFINE_ENUM_VALUE(valueType, VALUE_7);
    SO_NODE_DEFINE_ENUM_VALUE(valueType, VALUE_8);
    SO_NODE_DEFINE_ENUM_VALUE(valueType, VALUE_9);
    SO_NODE_DEFINE_ENUM_VALUE(valueType, VALUE_10);
    SO_NODE_DEFINE_ENUM_VALUE(valueType, VALUE_11);
    SO_NODE_DEFINE_ENUM_VALUE(valueType, VALUE_12);
    SO_NODE_DEFINE_ENUM_VALUE(valueType, VALUE_13);
    SO_NODE_DEFINE_ENUM_VALUE(valueType, VALUE_14);
    SO_NODE_DEFINE_ENUM_VALUE(valueType, VALUE_15);
    SO_NODE_SET_SF_ENUM_TYPE(value, valueType);
	SO_NODE_ADD_FIELD(value, (0));

	mSequenceSensor = new SoFieldSensor(sequenceSensorCBFunc, this);
	mSequenceSensor->attach(&sequence);
}


SoXipMouseToggle::~SoXipMouseToggle()
{
	if (mSequenceSensor)
		delete mSequenceSensor;
}


void SoXipMouseToggle::sequenceSensorCBFunc(void *usr, SoSensor *sensor)
{
	SoXipMouseToggle *thisPtr = (SoXipMouseToggle *) usr;

	// sequence has changed, move to first occurence of current selection or firts item
	for (int i = 0; i < thisPtr->sequence.getNum(); i++)
	{
		if (thisPtr->sequence[i] == thisPtr->value.getValue())
		{
			thisPtr->mIndex = i;
			return;
		}
	}

	if (thisPtr->sequence.getNum() > 0)
	{
		thisPtr->mIndex = 0;
		thisPtr->value.setValue(thisPtr->sequence[thisPtr->mIndex]);
	}
	else
	{
		thisPtr->mIndex = -1;
		thisPtr->value.setValue(0);
	}
}


void SoXipMouseToggle::handleEvent(SoHandleEventAction *action)
{
	int i;
	if (!action) return;
	const SoEvent *e = action->getEvent();

	if (SoMouseButtonEvent::isButtonReleaseEvent(e, (SoMouseButtonEvent::Button) mouse.getValue()))
	{
		action->setHandled();
	}
	else if (SoMouseButtonEvent::isButtonPressEvent(e, (SoMouseButtonEvent::Button) mouse.getValue()))
	{
		action->setHandled();

		if (mIndex < 0)
		{
			// first time, move index to what is set in the output
			for (i = 0; i < sequence.getNum(); i++)
			{
				if (*sequence.getValues(i) == value.getValue())
				{
					mIndex = i;

					int v = *sequence.getValues(mIndex);
					if (v < 16)
					{
						value.setValue(v);
					}

					break;
				}
			}
		}
		else if (sequence.getNum() > 0)
		{
			// avoid duplicate entries in sequence, (such as [ 1, 1, 2 ])
			int baseIndex = mIndex;
			for (i = 1; i < sequence.getNum(); i++)
			{
				mIndex = (baseIndex + i) % sequence.getNum();
				if (sequence[mIndex] != sequence[baseIndex]) break;
			}
		
			int v = *sequence.getValues(mIndex);
			if (v < 16)
			{
				value.setValue(v);
			}
		}

		if (action->getWhatAppliedTo() == SoAction::NODE)
		{
			// send a location event after updating the mode
			// so the mouse cursor is updated by manipulators / examiner
			SoHandleEventAction ha(action->getViewportRegion());
			SoLocation2Event ev;
			ev.setPosition(e->getPosition());
			ev.setTime(e->getTime());
			ev.setShiftDown(e->wasShiftDown());
			ev.setCtrlDown(e->wasCtrlDown());
			ev.setAltDown(e->wasAltDown());
			ha.setEvent(&ev);

			ha.apply(action->getNodeAppliedTo());
		}
	}
}

