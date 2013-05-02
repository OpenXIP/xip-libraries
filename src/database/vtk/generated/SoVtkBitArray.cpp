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
 */

/*
 * \brief
 * \author Sylvain Jaume <sylvain.jaume@siemens.com>, Francois Huguet
 */

#include "SoVtkBitArray.h"
#include "SoVtkUtils.h"

#include "vtkLookupTable.h"

SO_ENGINE_SOURCE( SoVtkBitArray )

SoVtkBitArray::SoVtkBitArray()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkBitArray);

	mObject = vtkBitArray::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkBitArray *aBitArray = vtkBitArray::New();

	SO_ENGINE_ADD_INPUT(Value, ());
	Value.setFormat("vtkIdType int");

	SO_ENGINE_ADD_INPUT(Tuple1, ());
	Tuple1.setFormat("vtkIdType double");

	SO_ENGINE_ADD_INPUT(NumberOfComponents, (0));
	NumberOfComponents.setValue(aBitArray->GetNumberOfComponents());

	SO_ENGINE_ADD_INPUT(Tuple9, ());
	Tuple9.setFormat(
	"vtkIdType double double double double double double double double double");

	SO_ENGINE_ADD_INPUT(LookupTable, (0));

	SO_ENGINE_ADD_INPUT(Component, ());
	Component.setFormat("vtkIdType int double");

	SO_ENGINE_ADD_INPUT(Tuple3, ());
	Tuple3.setFormat("vtkIdType double double double");

	SO_ENGINE_ADD_INPUT(Tuple2, ());
	Tuple2.setFormat("vtkIdType double double");

	SO_ENGINE_ADD_INPUT(Name, (""));

	SO_ENGINE_ADD_INPUT(Tuple4, ());
	Tuple4.setFormat("vtkIdType double double double double");

	aBitArray->Delete();

	SO_ENGINE_ADD_OUTPUT( oLookupTable, SoSFVtkObject );
	mLookupTable = 0;

	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;

	addCalled = 0;
}

SoVtkBitArray::~SoVtkBitArray()
{
	// Deletion of the objects if they exist
	if ( mLookupTable )
	{
	  mLookupTable->unref();
		mLookupTable = 0;
	}
	
	if ( mObject )
	{
		mObject->UnRegister(0);
		mObject->Delete();
		mObject = 0;
	}
}

void SoVtkBitArray::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkBitArray, SoEngine, "Engine" );
}

void SoVtkBitArray::evaluate()
{
	try
	{
		// Get the input type(s)
		// Deletion of the objects if they exist
		if ( mLookupTable )
		{
			mLookupTable->unref();
			mLookupTable = 0;
		}
		
		if ( addCalled )
		{
			reset();
			addCalled = 0;
		}

		mObject->GetLookupTable();
		mLookupTable = new SoVtkObject();
		mLookupTable->ref();
		mLookupTable->setPointer( mObject->GetLookupTable() );

		mOutput = new SoVtkObject();
		mOutput->ref();
		mOutput->setPointer( mObject );
	}
	catch(...)
	{
		SoDebugError::post( __FILE__, "Unknown Exception" );
		return;
	}

	SO_ENGINE_OUTPUT( oLookupTable, SoSFVtkObject, setValue( mLookupTable ) );
	SO_ENGINE_OUTPUT( Output, SoSFVtkObject, setValue( mOutput ) );
}


void SoVtkBitArray::inputChanged(SoField * f)
{
	// Get the Value value
	if ( f == &Value )
	{
		SbVariant *vValue = (SbVariant *)Value.getValues(0);
		SoInput input;
		int nb_fields = Value.getNum();

		vtkIdType val0;
		int val1;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vValue[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			mObject->SetValue( 
				(vtkIdType) val0,
				(int) val1
			);
		}
	}

	// Get the Tuple1 value
	if ( f == &Tuple1 )
	{
		SbVariant *vTuple1 = (SbVariant *)Tuple1.getValues(0);
		SoInput input;
		int nb_fields = Tuple1.getNum();

		vtkIdType val0;
		double val1;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vTuple1[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			mObject->SetTuple1( 
				(vtkIdType) val0,
				(double) val1
			);
		}
	}

	// Get the NumberOfComponents value
	if ( f == &NumberOfComponents )
		SO_VTK_SET_FIELD_VALUE( mObject, NumberOfComponents);

	// Get the Tuple9 value
	if ( f == &Tuple9 )
	{
		SbVariant *vTuple9 = (SbVariant *)Tuple9.getValues(0);
		SoInput input;
		int nb_fields = Tuple9.getNum();

		vtkIdType val0;
		double val1;
		double val2;
		double val3;
		double val4;
		double val5;
		double val6;
		double val7;
		double val8;
		double val9;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vTuple9[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			input.read(val2);
			input.read(val3);
			input.read(val4);
			input.read(val5);
			input.read(val6);
			input.read(val7);
			input.read(val8);
			input.read(val9);
			mObject->SetTuple9( 
				(vtkIdType) val0,
				(double) val1,
				(double) val2,
				(double) val3,
				(double) val4,
				(double) val5,
				(double) val6,
				(double) val7,
				(double) val8,
				(double) val9
			);
		}
	}

	// Get the LookupTable value
	if ( f == &LookupTable )
		SO_VTK_SET_FIELD_DATA( mObject, LookupTable, vtkLookupTable);

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
				(vtkIdType) val0,
				(int) val1,
				(double) val2
			);
		}
	}

	// Get the Tuple3 value
	if ( f == &Tuple3 )
	{
		SbVariant *vTuple3 = (SbVariant *)Tuple3.getValues(0);
		SoInput input;
		int nb_fields = Tuple3.getNum();

		vtkIdType val0;
		double val1;
		double val2;
		double val3;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vTuple3[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			input.read(val2);
			input.read(val3);
			mObject->SetTuple3( 
				(vtkIdType) val0,
				(double) val1,
				(double) val2,
				(double) val3
			);
		}
	}

	// Get the Tuple2 value
	if ( f == &Tuple2 )
	{
		SbVariant *vTuple2 = (SbVariant *)Tuple2.getValues(0);
		SoInput input;
		int nb_fields = Tuple2.getNum();

		vtkIdType val0;
		double val1;
		double val2;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vTuple2[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			input.read(val2);
			mObject->SetTuple2( 
				(vtkIdType) val0,
				(double) val1,
				(double) val2
			);
		}
	}

	// Get the Name value
	if ( f == &Name )
		SO_VTK_SET_FIELD_MFSTRING( mObject, Name);

	// Get the Tuple4 value
	if ( f == &Tuple4 )
	{
		SbVariant *vTuple4 = (SbVariant *)Tuple4.getValues(0);
		SoInput input;
		int nb_fields = Tuple4.getNum();

		vtkIdType val0;
		double val1;
		double val2;
		double val3;
		double val4;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vTuple4[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			input.read(val2);
			input.read(val3);
			input.read(val4);
			mObject->SetTuple4( 
				(vtkIdType) val0,
				(double) val1,
				(double) val2,
				(double) val3,
				(double) val4
			);
		}
	}

}

void SoVtkBitArray::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkBitArray::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	// Get the Value value
	if (addCalled == 1)
	{
		SbVariant *vValue = (SbVariant *)Value.getValues(0);
		SoInput input;
		int nb_fields = Value.getNum();

		vtkIdType val0;
		int val1;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vValue[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			mObject->SetValue( 
				(vtkIdType) val0,
				(int) val1
			);
		}
	}

	// Get the Tuple1 value
	if (addCalled == 1)
	{
		SbVariant *vTuple1 = (SbVariant *)Tuple1.getValues(0);
		SoInput input;
		int nb_fields = Tuple1.getNum();

		vtkIdType val0;
		double val1;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vTuple1[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			mObject->SetTuple1( 
				(vtkIdType) val0,
				(double) val1
			);
		}
	}

	// Get the NumberOfComponents value
	
		SO_VTK_SET_FIELD_VALUE( mObject, NumberOfComponents);

	// Get the Tuple9 value
	if (addCalled == 1)
	{
		SbVariant *vTuple9 = (SbVariant *)Tuple9.getValues(0);
		SoInput input;
		int nb_fields = Tuple9.getNum();

		vtkIdType val0;
		double val1;
		double val2;
		double val3;
		double val4;
		double val5;
		double val6;
		double val7;
		double val8;
		double val9;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vTuple9[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			input.read(val2);
			input.read(val3);
			input.read(val4);
			input.read(val5);
			input.read(val6);
			input.read(val7);
			input.read(val8);
			input.read(val9);
			mObject->SetTuple9( 
				(vtkIdType) val0,
				(double) val1,
				(double) val2,
				(double) val3,
				(double) val4,
				(double) val5,
				(double) val6,
				(double) val7,
				(double) val8,
				(double) val9
			);
		}
	}

	// Get the LookupTable value
	
		SO_VTK_SET_FIELD_DATA( mObject, LookupTable, vtkLookupTable);

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
				(vtkIdType) val0,
				(int) val1,
				(double) val2
			);
		}
	}

	// Get the Tuple3 value
	if (addCalled == 1)
	{
		SbVariant *vTuple3 = (SbVariant *)Tuple3.getValues(0);
		SoInput input;
		int nb_fields = Tuple3.getNum();

		vtkIdType val0;
		double val1;
		double val2;
		double val3;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vTuple3[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			input.read(val2);
			input.read(val3);
			mObject->SetTuple3( 
				(vtkIdType) val0,
				(double) val1,
				(double) val2,
				(double) val3
			);
		}
	}

	// Get the Tuple2 value
	if (addCalled == 1)
	{
		SbVariant *vTuple2 = (SbVariant *)Tuple2.getValues(0);
		SoInput input;
		int nb_fields = Tuple2.getNum();

		vtkIdType val0;
		double val1;
		double val2;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vTuple2[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			input.read(val2);
			mObject->SetTuple2( 
				(vtkIdType) val0,
				(double) val1,
				(double) val2
			);
		}
	}

	// Get the Name value
	
		SO_VTK_SET_FIELD_MFSTRING( mObject, Name);

	// Get the Tuple4 value
	if (addCalled == 1)
	{
		SbVariant *vTuple4 = (SbVariant *)Tuple4.getValues(0);
		SoInput input;
		int nb_fields = Tuple4.getNum();

		vtkIdType val0;
		double val1;
		double val2;
		double val3;
		double val4;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vTuple4[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			input.read(val2);
			input.read(val3);
			input.read(val4);
			mObject->SetTuple4( 
				(vtkIdType) val0,
				(double) val1,
				(double) val2,
				(double) val3,
				(double) val4
			);
		}
	}

}

