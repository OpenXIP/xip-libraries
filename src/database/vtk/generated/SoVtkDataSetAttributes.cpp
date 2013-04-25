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
 
 
 
# include "SoVtkDataSetAttributes.h"
# include "SoVtkUtils.h"

# include "vtkDataArray.h"


SO_ENGINE_SOURCE( SoVtkDataSetAttributes )

SoVtkDataSetAttributes::SoVtkDataSetAttributes()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkDataSetAttributes);

	mObject = vtkDataSetAttributes::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkDataSetAttributes *aDataSetAttributes = vtkDataSetAttributes::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(CopyVectors, (0));
	CopyVectors.setValue(aDataSetAttributes->GetCopyVectors());

	SO_ENGINE_ADD_INPUT(CopyScalars, (0));
	CopyScalars.setValue(aDataSetAttributes->GetCopyScalars());

	SO_ENGINE_ADD_INPUT(CopyAttribute, ());
	CopyAttribute.setFormat("int int");

	SO_ENGINE_ADD_INPUT(CopyNormals, (0));
	CopyNormals.setValue(aDataSetAttributes->GetCopyNormals());

	SO_ENGINE_ADD_INPUT(Component, ());
	Component.setFormat("const vtkIdType const int const double");

	SO_ENGINE_ADD_INPUT(CopyTensors, (0));
	CopyTensors.setValue(aDataSetAttributes->GetCopyTensors());

	SO_ENGINE_ADD_INPUT(CopyTCoords, (0));
	CopyTCoords.setValue(aDataSetAttributes->GetCopyTCoords());

	aDataSetAttributes->Delete();

	SO_ENGINE_DEFINE_ENUM_VALUE( AttributeLimitTypes, NOLIMIT );
	SO_ENGINE_DEFINE_ENUM_VALUE( AttributeLimitTypes, EXACT );
	SO_ENGINE_DEFINE_ENUM_VALUE( AttributeLimitTypes, MAX );
	SO_ENGINE_SET_SF_ENUM_TYPE( AttributeLimitTypesEnum, AttributeLimitTypes );
	SO_ENGINE_DEFINE_ENUM_VALUE( AttributeTypes, TCOORDS );
	SO_ENGINE_DEFINE_ENUM_VALUE( AttributeTypes, NUM_ATTRIBUTES );
	SO_ENGINE_DEFINE_ENUM_VALUE( AttributeTypes, VECTORS );
	SO_ENGINE_DEFINE_ENUM_VALUE( AttributeTypes, TENSORS );
	SO_ENGINE_DEFINE_ENUM_VALUE( AttributeTypes, NORMALS );
	SO_ENGINE_DEFINE_ENUM_VALUE( AttributeTypes, SCALARS );
	SO_ENGINE_SET_SF_ENUM_TYPE( AttributeTypesEnum, AttributeTypes );

	SO_ENGINE_ADD_OUTPUT( oTensors, SoSFVtkObject );
	mTensors = 0;
	SO_ENGINE_ADD_OUTPUT( oScalars, SoSFVtkObject );
	mScalars = 0;
	SO_ENGINE_ADD_OUTPUT( oTCoords, SoSFVtkObject );
	mTCoords = 0;
	SO_ENGINE_ADD_OUTPUT( oNormals, SoSFVtkObject );
	mNormals = 0;
	SO_ENGINE_ADD_OUTPUT( oVectors, SoSFVtkObject );
	mVectors = 0;
	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;


	addCalled = 0;
}

SoVtkDataSetAttributes::~SoVtkDataSetAttributes()
{
	// Deletion of the objects if they exist
	if ( mTensors )
	{
	
		mTensors->unref();
		mTensors = 0;
	}
	
	if ( mScalars )
	{
	
		mScalars->unref();
		mScalars = 0;
	}
	
	if ( mTCoords )
	{
	
		mTCoords->unref();
		mTCoords = 0;
	}
	
	if ( mNormals )
	{
	
		mNormals->unref();
		mNormals = 0;
	}
	
	if ( mVectors )
	{
	
		mVectors->unref();
		mVectors = 0;
	}
	
	if ( mObject )
	{
		mObject->UnRegister(0);
		mObject->Delete();
		mObject = 0;
	}
	

}

void SoVtkDataSetAttributes::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkDataSetAttributes, SoEngine, "Engine" );
}

void SoVtkDataSetAttributes::evaluate()
{
	try
	{
		// Get the input type(s)
		// Deletion of the objects if they exist
		if ( mTensors )
		{
		
			mTensors->unref();
			mTensors = 0;
		}
		
		if ( mScalars )
		{
		
			mScalars->unref();
			mScalars = 0;
		}
		
		if ( mTCoords )
		{
		
			mTCoords->unref();
			mTCoords = 0;
		}
		
		if ( mNormals )
		{
		
			mNormals->unref();
			mNormals = 0;
		}
		
		if ( mVectors )
		{
		
			mVectors->unref();
			mVectors = 0;
		}
		
		if ( addCalled )
		{
			reset();
			addCalled = 0;
		}

		mObject->GetTensors();
		mTensors = new SoVtkObject();
		mTensors->ref();
		mTensors->setPointer( mObject->GetTensors() );

		mObject->GetScalars();
		mScalars = new SoVtkObject();
		mScalars->ref();
		mScalars->setPointer( mObject->GetScalars() );

		mObject->GetTCoords();
		mTCoords = new SoVtkObject();
		mTCoords->ref();
		mTCoords->setPointer( mObject->GetTCoords() );

		mObject->GetNormals();
		mNormals = new SoVtkObject();
		mNormals->ref();
		mNormals->setPointer( mObject->GetNormals() );

		mObject->GetVectors();
		mVectors = new SoVtkObject();
		mVectors->ref();
		mVectors->setPointer( mObject->GetVectors() );

		mOutput = new SoVtkObject();
		mOutput->ref();
		mOutput->setPointer( mObject );

	}
	catch(...)
	{
		SoDebugError::post( __FILE__, "Unknown Exception" );
		return;
	}
	SO_ENGINE_OUTPUT( oTensors, SoSFVtkObject, setValue( mTensors ) );
	SO_ENGINE_OUTPUT( oScalars, SoSFVtkObject, setValue( mScalars ) );
	SO_ENGINE_OUTPUT( oTCoords, SoSFVtkObject, setValue( mTCoords ) );
	SO_ENGINE_OUTPUT( oNormals, SoSFVtkObject, setValue( mNormals ) );
	SO_ENGINE_OUTPUT( oVectors, SoSFVtkObject, setValue( mVectors ) );
	SO_ENGINE_OUTPUT( Output, SoSFVtkObject, setValue( mOutput ) );
}


void SoVtkDataSetAttributes::inputChanged(SoField * f)
{
	// Get the CopyVectors value
	if ( f == &CopyVectors )
		SO_VTK_SET_FIELD_VALUE( mObject, CopyVectors);

	// Get the CopyScalars value
	if ( f == &CopyScalars )
		SO_VTK_SET_FIELD_VALUE( mObject, CopyScalars);

	// Get the CopyAttribute value
	if ( f == &CopyAttribute )
	{
		SbVariant *vCopyAttribute = (SbVariant *)CopyAttribute.getValues(0);
		SoInput input;
		int nb_fields = CopyAttribute.getNum();

		int val0;
		int val1;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vCopyAttribute[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			mObject->SetCopyAttribute( 
				(int) val0,
				(int) val1
			);
		}
	}

	// Get the CopyNormals value
	if ( f == &CopyNormals )
		SO_VTK_SET_FIELD_VALUE( mObject, CopyNormals);

	// Get the Component value
	if ( f == &Component )
	{
		SbVariant *vComponent = (SbVariant *)Component.getValues(0);
		SoInput input;
		int nb_fields = Component.getNum();

		vtkIdType val0;
		int val1;
		double val2;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vComponent[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			input.read(val2);
			mObject->SetComponent( 
				(const vtkIdType) val0,
				(const int) val1,
				(const double) val2
			);
		}
	}

	// Get the CopyTensors value
	if ( f == &CopyTensors )
		SO_VTK_SET_FIELD_VALUE( mObject, CopyTensors);

	// Get the CopyTCoords value
	if ( f == &CopyTCoords )
		SO_VTK_SET_FIELD_VALUE( mObject, CopyTCoords);

}

void SoVtkDataSetAttributes::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkDataSetAttributes::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	// Get the CopyVectors value
	
		SO_VTK_SET_FIELD_VALUE( mObject, CopyVectors);

	// Get the CopyScalars value
	
		SO_VTK_SET_FIELD_VALUE( mObject, CopyScalars);

	// Get the CopyAttribute value
	if (addCalled == 1)
	{
		SbVariant *vCopyAttribute = (SbVariant *)CopyAttribute.getValues(0);
		SoInput input;
		int nb_fields = CopyAttribute.getNum();

		int val0;
		int val1;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vCopyAttribute[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			mObject->SetCopyAttribute( 
				(int) val0,
				(int) val1
			);
		}
	}

	// Get the CopyNormals value
	
		SO_VTK_SET_FIELD_VALUE( mObject, CopyNormals);

	// Get the Component value
	if (addCalled == 1)
	{
		SbVariant *vComponent = (SbVariant *)Component.getValues(0);
		SoInput input;
		int nb_fields = Component.getNum();

		vtkIdType val0;
		int val1;
		double val2;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vComponent[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			input.read(val2);
			mObject->SetComponent( 
				(const vtkIdType) val0,
				(const int) val1,
				(const double) val2
			);
		}
	}

	// Get the CopyTensors value
	
		SO_VTK_SET_FIELD_VALUE( mObject, CopyTensors);

	// Get the CopyTCoords value
	
		SO_VTK_SET_FIELD_VALUE( mObject, CopyTCoords);

}
