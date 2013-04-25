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

#include "SoVtkAssembly.h"

#include <Inventor/elements/SoLocalBBoxMatrixElement.h>

#include "SoVtkActor.h"
#include "SoVtkVolume.h"
#include "SoVtkActor2D.h"
#include "SoVtkImageActor.h"
#include "SoVtkLODActor.h"

#include "vtkProp3DCollection.h"

SO_NODE_SOURCE(SoVtkAssembly);

SoVtkAssembly::SoVtkAssembly()
{
	SO_NODE_CONSTRUCTOR(SoVtkAssembly);

	mAssembly = vtkAssembly::New();
	mAssembly->Register(0);

	SbVec3f vec3fInitValue(0, 0, 0);
	SO_NODE_ADD_FIELD(Origin, (vec3fInitValue));
	SO_NODE_ADD_FIELD(Position, (vec3fInitValue));

	nodeId = 0;

}

SoVtkAssembly::~SoVtkAssembly()
{
	if( mAssembly )
	{
		mAssembly->UnRegister(0);
		mAssembly->Delete();
		mAssembly = 0;
	}
}

void SoVtkAssembly::initClass()
{
  SO_NODE_INIT_CLASS(SoVtkAssembly, SoGroup, "Group");
}


void SoVtkAssembly::getBoundingBox(SoGetBoundingBoxAction *action)
{
	SbBox3f	bbox;
	SbVec3f	center;

	if (mAssembly)
	{
		const double *bounds = mAssembly->GetBounds();
		SbBox3f bbox(bounds[0], bounds[2], bounds[4], bounds[1], bounds[3], bounds[5]);
		action->extendBy(bbox);
		action->setCenter(bbox.getCenter(), FALSE);
	}
}


void SoVtkAssembly::GLRender(SoGLRenderAction *action)
{
	try
	{
		SoGroup::GLRender(action);

		if ( nodeId != getNodeId() )
		{
			nodeId = getNodeId();
			updateChildren();
		}



		// Perform setPosition and setOrigin transformations
		SbVec3f position = Position.getValue();
		SbVec3f origin = Origin.getValue();
		mAssembly->SetOrigin(origin[0], origin[1], origin[2]);
		mAssembly->SetPosition(position[0], position[1], position[2]);

	}
	catch(...)
	{
		SoDebugError::post( __FILE__, "Unknown Exception" );
		return ;
	}
}

void SoVtkAssembly::updateChildren()
{
	for (int i = 0; i < SoGroup::getNumChildren(); i++)
	{
		SoNode *child = SoGroup::getChild(i);
	
		if (child->isOfType(SoVtkAssembly::getClassTypeId()))
		{
			// assembly
			SoVtkAssembly *assembly = (SoVtkAssembly *) child;
			assembly->updateChildren();
		}
	}

	vtkProp3DCollection *parts = mAssembly->GetParts();

	for (int i = 0; i < parts->GetNumberOfItems(); i++)
	{
		mAssembly->RemovePart(vtkProp3D::SafeDownCast(parts->GetItemAsObject(i)));
	}

	for (int i = 0; i < SoGroup::getNumChildren(); i++)
	{
		SoNode *child = SoGroup::getChild(i);

		if (child->isOfType(SoVtkActor::getClassTypeId()))
		{
			// actor
			SoVtkActor *actor = (SoVtkActor *) child;
			mAssembly->AddPart(actor->getActor());
		}

		if (child->isOfType(SoVtkLODActor::getClassTypeId()))
		{
			// actor
			SoVtkLODActor *actor = (SoVtkLODActor *) child;
			mAssembly->AddPart(actor->getLODActor());
		}

		if (child->isOfType(SoVtkActor2D::getClassTypeId()))
		{
			// actor 2D
			SoVtkActor2D *actor = (SoVtkActor2D *) child;
			mAssembly->AddPart(vtkProp3D::SafeDownCast(actor->getActor2D()));
		}

		if (child->isOfType(SoVtkImageActor::getClassTypeId()))
		{
			// image actor
			SoVtkImageActor *actor = (SoVtkImageActor *) child;
			mAssembly->AddPart(actor->getImageActor());
		}

		if (child->isOfType(SoVtkVolume::getClassTypeId()))
		{
			// volume
			SoVtkVolume *vol = (SoVtkVolume *) child;
			mAssembly->AddPart(vol->getVolume());
		}
		
		if (child->isOfType(SoVtkAssembly::getClassTypeId()))
		{
			// assembly
			SoVtkAssembly *assembly = (SoVtkAssembly *) child;
			mAssembly->AddPart(vtkAssembly::SafeDownCast(assembly->getAssembly()));
		}
	}
}

vtkAssembly *
SoVtkAssembly::getAssembly() const
{
	return mAssembly;
}