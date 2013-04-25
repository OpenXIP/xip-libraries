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

# include "SoVtkPLOT3DReader.h"
# include "SoVtkUtils.h"

# include "vtkAlgorithmOutput.h"
# include "vtkStructuredGrid.h"


SO_ENGINE_SOURCE( SoVtkPLOT3DReader )

SoVtkPLOT3DReader::SoVtkPLOT3DReader()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkPLOT3DReader);

	mObject = vtkPLOT3DReader::New();

	mObject->Register(0);mObject->SetGlobalWarningDisplay(0);

	vtkPLOT3DReader *aPLOT3DReader = vtkPLOT3DReader::New();
	double *x;
	int *y;

	SO_ENGINE_ADD_INPUT(HasByteCount, (0));
	HasByteCount.setValue(aPLOT3DReader->GetHasByteCount());

	SO_ENGINE_ADD_INPUT(ByteOrder, (0));
	ByteOrder.setValue(aPLOT3DReader->GetByteOrder());

	SO_ENGINE_ADD_INPUT(QFileName, (""));

	SO_ENGINE_ADD_INPUT(Uvinf, (0));
	Uvinf.setValue(aPLOT3DReader->GetUvinf());

	SO_ENGINE_ADD_INPUT(Function, ());
	Function.setFormat("int");

	SO_ENGINE_ADD_INPUT(ScalarFunctionNumber, (0));
	ScalarFunctionNumber.setValue(aPLOT3DReader->GetScalarFunctionNumber());

	SO_ENGINE_ADD_INPUT(DoNotReduceNumberOfOutputs, (0));
	DoNotReduceNumberOfOutputs.setValue(aPLOT3DReader->GetDoNotReduceNumberOfOutputs());

	SO_ENGINE_ADD_INPUT(InputArrayToProcess, ());
	InputArrayToProcess.setFormat("int int int int char*");

	SO_ENGINE_ADD_INPUT(Vvinf, (0));
	Vvinf.setValue(aPLOT3DReader->GetVvinf());

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	SO_ENGINE_ADD_INPUT(BinaryFile, (0));
	BinaryFile.setValue(aPLOT3DReader->GetBinaryFile());

	SO_ENGINE_ADD_INPUT(IBlanking, (0));
	IBlanking.setValue(aPLOT3DReader->GetIBlanking());

	SO_ENGINE_ADD_INPUT(TwoDimensionalGeometry, (0));
	TwoDimensionalGeometry.setValue(aPLOT3DReader->GetTwoDimensionalGeometry());

	SO_ENGINE_ADD_INPUT(Wvinf, (0));
	Wvinf.setValue(aPLOT3DReader->GetWvinf());

	SO_ENGINE_ADD_INPUT(NumberOfInputConnections, ());
	NumberOfInputConnections.setFormat("int int");

	SO_ENGINE_ADD_INPUT(Gamma, (0));
	Gamma.setValue(aPLOT3DReader->GetGamma());

	SO_ENGINE_ADD_INPUT(VectorFunctionNumber, (0));
	VectorFunctionNumber.setValue(aPLOT3DReader->GetVectorFunctionNumber());

	SO_ENGINE_ADD_INPUT(ForceRead, (0));
	ForceRead.setValue(aPLOT3DReader->GetForceRead());

	SO_ENGINE_ADD_INPUT(FileName, (""));

	SO_ENGINE_ADD_INPUT(R, (0));
	R.setValue(aPLOT3DReader->GetR());

	SO_ENGINE_ADD_INPUT(MultiGrid, (0));
	MultiGrid.setValue(aPLOT3DReader->GetMultiGrid());

	SO_ENGINE_ADD_INPUT(XYZFileName, (""));

	aPLOT3DReader->Delete();


	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;
	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;

}

SoVtkPLOT3DReader::~SoVtkPLOT3DReader()
{
	// Deletion of the objects if they exist
	if ( mOutput )
	{
	
		mOutput->unref();
		mOutput = 0;
	}
	
	if ( mOutputPort )
	{
	
		mOutputPort->unref();
		mOutputPort = 0;
	}
	
	if ( mObject )
	{
		mObject->UnRegister(0);
		mObject->Delete();
		mObject = 0;
	}
	

}

void SoVtkPLOT3DReader::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkPLOT3DReader, SoEngine, "Engine" );
}

void SoVtkPLOT3DReader::evaluate()
{
	try
	{
		// Deletion of the objects if they exist
		if ( mOutput )
		{
		
			mOutput->unref();
			mOutput = 0;
		}
		
		if ( mOutputPort )
		{
		
			mOutputPort->unref();
			mOutputPort = 0;
		}
		
		// Get the input type(s)
		SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
		
		if (inputPortPtr)
			mObject->SetInputConnection(inputPortPtr->getPointer());

		mObject->GetOutput()->Register(0);
		mOutput = new SoVtkObject();
		mOutput->ref();
		mOutput->setPointer( mObject->GetOutput() );

		if ( mObject->GetNumberOfOutputPorts() > 0 )
		{
			mObject->GetOutputPort()->Register(0);
			mOutputPort = new SoVtkAlgorithmOutput();
			mOutputPort->ref();
			mOutputPort->setPointer( mObject->GetOutputPort() );
		}

	}
	catch(...)
	{
		SoDebugError::post( __FILE__, "Unknown Exception" );
		return;
	}
	SO_ENGINE_OUTPUT( Output, SoSFVtkObject, setValue( mOutput ) );
	SO_ENGINE_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput, setValue( mOutputPort ) );
}


void SoVtkPLOT3DReader::inputChanged(SoField * f)
{
	// Get the HasByteCount value
	if ( f == &HasByteCount )
		SO_VTK_SET_FIELD_VALUE( mObject, HasByteCount);

	// Get the ByteOrder value
	if ( f == &ByteOrder )
		SO_VTK_SET_FIELD_VALUE( mObject, ByteOrder);

	// Get the QFileName value
	if ( f == &QFileName )
		SO_VTK_SET_FIELD_MFSTRING( mObject, QFileName);

	// Get the Uvinf value
	if ( f == &Uvinf )
		SO_VTK_SET_FIELD_VALUE( mObject, Uvinf);

	// Get the Function value
	if ( f == &Function )
	{
		SbVariant *vFunction = (SbVariant *)Function.getValues(0);
		SoInput input;
		int nb_fields = Function.getNum();

		int val0;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vFunction[i].getField().getString(),256);
			input.read(val0);
			mObject->AddFunction( 
				(int) val0
			);
		}
	}

	// Get the ScalarFunctionNumber value
	if ( f == &ScalarFunctionNumber )
		SO_VTK_SET_FIELD_VALUE( mObject, ScalarFunctionNumber);

	// Get the DoNotReduceNumberOfOutputs value
	if ( f == &DoNotReduceNumberOfOutputs )
		SO_VTK_SET_FIELD_VALUE( mObject, DoNotReduceNumberOfOutputs);

	// Get the InputArrayToProcess value
	if ( f == &InputArrayToProcess )
	{
		SbVariant vInputArrayToProcess = (SbVariant)InputArrayToProcess.getValue();
		SoInput input;
		int val0;
		int val1;
		int val2;
		int val3;
		SbString val4;
	
		input.setBuffer((void *)vInputArrayToProcess.getField().getString(),256);
		input.read(val0);
		input.read(val1);
		input.read(val2);
		input.read(val3);
		input.read(val4);
		mObject->SetInputArrayToProcess( 
			(int) val0,
			(int) val1,
			(int) val2,
			(int) val3,
			val4.getString()
		);
	}
	// Get the Vvinf value
	if ( f == &Vvinf )
		SO_VTK_SET_FIELD_VALUE( mObject, Vvinf);

	// Get the BinaryFile value
	if ( f == &BinaryFile )
		SO_VTK_SET_FIELD_VALUE( mObject, BinaryFile);

	// Get the IBlanking value
	if ( f == &IBlanking )
		SO_VTK_SET_FIELD_VALUE( mObject, IBlanking);

	// Get the TwoDimensionalGeometry value
	if ( f == &TwoDimensionalGeometry )
		SO_VTK_SET_FIELD_VALUE( mObject, TwoDimensionalGeometry);

	// Get the Wvinf value
	if ( f == &Wvinf )
		SO_VTK_SET_FIELD_VALUE( mObject, Wvinf);

	// Get the NumberOfInputConnections value
	if ( f == &NumberOfInputConnections )
	{
		SbVariant vNumberOfInputConnections = (SbVariant)NumberOfInputConnections.getValue();
		SoInput input;
		int val0;
		int val1;
	
		input.setBuffer((void *)vNumberOfInputConnections.getField().getString(),256);
		input.read(val0);
		input.read(val1);
		mObject->SetNumberOfInputConnections( 
			(int) val0,
			(int) val1
		);
	}
	// Get the Gamma value
	if ( f == &Gamma )
		SO_VTK_SET_FIELD_VALUE( mObject, Gamma);

	// Get the VectorFunctionNumber value
	if ( f == &VectorFunctionNumber )
		SO_VTK_SET_FIELD_VALUE( mObject, VectorFunctionNumber);

	// Get the ForceRead value
	if ( f == &ForceRead )
		SO_VTK_SET_FIELD_VALUE( mObject, ForceRead);

	// Get the FileName value
	if ( f == &FileName )
		SO_VTK_SET_FIELD_MFSTRING( mObject, FileName);

	// Get the R value
	if ( f == &R )
		SO_VTK_SET_FIELD_VALUE( mObject, R);

	// Get the MultiGrid value
	if ( f == &MultiGrid )
		SO_VTK_SET_FIELD_VALUE( mObject, MultiGrid);

	// Get the XYZFileName value
	if ( f == &XYZFileName )
		SO_VTK_SET_FIELD_MFSTRING( mObject, XYZFileName);

	//mObject->Update();
	
}
