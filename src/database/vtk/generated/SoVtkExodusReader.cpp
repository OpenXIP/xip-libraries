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
 
 
 
# include "SoVtkExodusReader.h"
# include "SoVtkUtils.h"

# include "vtkAlgorithmOutput.h"
# include "vtkUnstructuredGrid.h"


SO_ENGINE_SOURCE( SoVtkExodusReader )

SoVtkExodusReader::SoVtkExodusReader()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkExodusReader);

	mObject = vtkExodusReader::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkExodusReader *aExodusReader = vtkExodusReader::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(NodeSetArrayStatus, ());
	NodeSetArrayStatus.setFormat("int int");

	SO_ENGINE_ADD_INPUT(ApplyDisplacements, (0));
	ApplyDisplacements.setValue(aExodusReader->GetApplyDisplacements());

	SO_ENGINE_ADD_INPUT(CellArrayStatus, ());
	CellArrayStatus.setFormat("int int");

	SO_ENGINE_ADD_INPUT(FilterOutputVar, (""));

	SO_ENGINE_ADD_INPUT(GenerateGlobalNodeIdArray, (0));
	GenerateGlobalNodeIdArray.setValue(aExodusReader->GetGenerateGlobalNodeIdArray());

	SO_ENGINE_ADD_INPUT(AllPartArrayStatus, (0));
	SO_ENGINE_ADD_INPUT(XMLFileName, (""));

	SO_ENGINE_ADD_INPUT(PartArrayStatus, ());
	PartArrayStatus.setFormat("int int");

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	SO_ENGINE_ADD_INPUT(FilterDenominatorWeight, (0));
	SO_ENGINE_ADD_INPUT(AllAssemblyArrayStatus, (0));
	SO_ENGINE_ADD_INPUT(MaterialArrayStatus, ());
	MaterialArrayStatus.setFormat("int int");

	SO_ENGINE_ADD_INPUT(ExodusModelMetadata, (0));
	ExodusModelMetadata.setValue(aExodusReader->GetExodusModelMetadata());

	SO_ENGINE_ADD_INPUT(AssemblyArrayStatus, ());
	AssemblyArrayStatus.setFormat("int int");

	SO_ENGINE_ADD_INPUT(PointArrayStatus, ());
	PointArrayStatus.setFormat("int int");

	SO_ENGINE_ADD_INPUT(FileName, (""));

	SO_ENGINE_ADD_INPUT(HierarchyArrayStatus, ());
	HierarchyArrayStatus.setFormat("int int");

	SO_ENGINE_ADD_INPUT(SideSetArrayStatus, ());
	SideSetArrayStatus.setFormat("int int");

	SO_ENGINE_ADD_INPUT(FilterInputVar, (""));

	SO_ENGINE_ADD_INPUT(DisplacementMagnitude, (0));
	DisplacementMagnitude.setValue(aExodusReader->GetDisplacementMagnitude());

	SO_ENGINE_ADD_INPUT(AllPointArrayStatus, (0));
	SO_ENGINE_ADD_INPUT(BlockArrayStatus, ());
	BlockArrayStatus.setFormat("int int");

	SO_ENGINE_ADD_INPUT(PackExodusModelOntoOutput, (0));
	PackExodusModelOntoOutput.setValue(aExodusReader->GetPackExodusModelOntoOutput());

	SO_ENGINE_ADD_INPUT(AllBlockArrayStatus, (0));
	SO_ENGINE_ADD_INPUT(AllCellArrayStatus, (0));
	SO_ENGINE_ADD_INPUT(DisplayType, (0));
	SO_ENGINE_ADD_INPUT(TimeStep, (0));
	TimeStep.setValue(aExodusReader->GetTimeStep());

	SO_ENGINE_ADD_INPUT(FilterNumeratorWeight, (0));
	SO_ENGINE_ADD_INPUT(GenerateGlobalElementIdArray, (0));
	GenerateGlobalElementIdArray.setValue(aExodusReader->GetGenerateGlobalElementIdArray());

	SO_ENGINE_ADD_INPUT(TimeStepRange, (0,0));

	y = (int *) aExodusReader->GetTimeStepRange();
	TimeStepRange.setValue((float) y[0],(float) y[1]);

	SO_ENGINE_ADD_INPUT(GenerateBlockIdCellArray, (0));
	GenerateBlockIdCellArray.setValue(aExodusReader->GetGenerateBlockIdCellArray());

	SO_ENGINE_ADD_INPUT(AllHierarchyArrayStatus, (0));
	SO_ENGINE_ADD_INPUT(FilterForwardNumeratorWeight, (0));
	SO_ENGINE_ADD_INPUT(AllMaterialArrayStatus, (0));
	aExodusReader->Delete();

	SO_ENGINE_DEFINE_ENUM_VALUE( ArrayType, BLOCK );
	SO_ENGINE_DEFINE_ENUM_VALUE( ArrayType, POINT );
	SO_ENGINE_DEFINE_ENUM_VALUE( ArrayType, CELL );
	SO_ENGINE_DEFINE_ENUM_VALUE( ArrayType, NUM_ARRAY_TYPES );
	SO_ENGINE_DEFINE_ENUM_VALUE( ArrayType, HIERARCHY );
	SO_ENGINE_DEFINE_ENUM_VALUE( ArrayType, ASSEMBLY );
	SO_ENGINE_DEFINE_ENUM_VALUE( ArrayType, PART );
	SO_ENGINE_DEFINE_ENUM_VALUE( ArrayType, UNKNOWN_TYPE );
	SO_ENGINE_DEFINE_ENUM_VALUE( ArrayType, MATERIAL );
	SO_ENGINE_SET_SF_ENUM_TYPE( ArrayTypeEnum, ArrayType );

	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;
	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;


	addCalled = 0;
}

SoVtkExodusReader::~SoVtkExodusReader()
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

void SoVtkExodusReader::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkExodusReader, SoEngine, "Engine" );
}

void SoVtkExodusReader::evaluate()
{
	try
	{
		// Get the input type(s)
		SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
		
		if (inputPortPtr)
			mObject->SetInputConnection(inputPortPtr->getPointer());

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
		
		if ( addCalled )
		{
			reset();
			addCalled = 0;
		}

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


void SoVtkExodusReader::inputChanged(SoField * f)
{
	// Get the NodeSetArrayStatus value
	if ( f == &NodeSetArrayStatus )
	{
		SbVariant *vNodeSetArrayStatus = (SbVariant *)NodeSetArrayStatus.getValues(0);
		SoInput input;
		int nb_fields = NodeSetArrayStatus.getNum();

		int val0;
		int val1;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vNodeSetArrayStatus[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			mObject->SetNodeSetArrayStatus( 
				(int) val0,
				(int) val1
			);
		}
	}

	// Get the ApplyDisplacements value
	if ( f == &ApplyDisplacements )
		SO_VTK_SET_FIELD_VALUE( mObject, ApplyDisplacements);

	// Get the CellArrayStatus value
	if ( f == &CellArrayStatus )
	{
		SbVariant *vCellArrayStatus = (SbVariant *)CellArrayStatus.getValues(0);
		SoInput input;
		int nb_fields = CellArrayStatus.getNum();

		int val0;
		int val1;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vCellArrayStatus[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			mObject->SetCellArrayStatus( 
				(int) val0,
				(int) val1
			);
		}
	}

	// Get the FilterOutputVar value
	if ( f == &FilterOutputVar )
		addCalled = 1;
	// Get the GenerateGlobalNodeIdArray value
	if ( f == &GenerateGlobalNodeIdArray )
		SO_VTK_SET_FIELD_VALUE( mObject, GenerateGlobalNodeIdArray);

	// Get the AllPartArrayStatus value
	if ( f == &AllPartArrayStatus )
		SO_VTK_SET_FIELD_VALUE( mObject, AllPartArrayStatus);

	// Get the XMLFileName value
	if ( f == &XMLFileName )
		SO_VTK_SET_FIELD_MFSTRING( mObject, XMLFileName);

	// Get the PartArrayStatus value
	if ( f == &PartArrayStatus )
	{
		SbVariant *vPartArrayStatus = (SbVariant *)PartArrayStatus.getValues(0);
		SoInput input;
		int nb_fields = PartArrayStatus.getNum();

		int val0;
		int val1;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vPartArrayStatus[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			mObject->SetPartArrayStatus( 
				(int) val0,
				(int) val1
			);
		}
	}

	// Get the FilterDenominatorWeight value
	if ( f == &FilterDenominatorWeight )
		addCalled = 1;
	// Get the AllAssemblyArrayStatus value
	if ( f == &AllAssemblyArrayStatus )
		SO_VTK_SET_FIELD_VALUE( mObject, AllAssemblyArrayStatus);

	// Get the MaterialArrayStatus value
	if ( f == &MaterialArrayStatus )
	{
		SbVariant *vMaterialArrayStatus = (SbVariant *)MaterialArrayStatus.getValues(0);
		SoInput input;
		int nb_fields = MaterialArrayStatus.getNum();

		int val0;
		int val1;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vMaterialArrayStatus[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			mObject->SetMaterialArrayStatus( 
				(int) val0,
				(int) val1
			);
		}
	}

	// Get the ExodusModelMetadata value
	if ( f == &ExodusModelMetadata )
		SO_VTK_SET_FIELD_VALUE( mObject, ExodusModelMetadata);

	// Get the AssemblyArrayStatus value
	if ( f == &AssemblyArrayStatus )
	{
		SbVariant *vAssemblyArrayStatus = (SbVariant *)AssemblyArrayStatus.getValues(0);
		SoInput input;
		int nb_fields = AssemblyArrayStatus.getNum();

		int val0;
		int val1;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vAssemblyArrayStatus[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			mObject->SetAssemblyArrayStatus( 
				(int) val0,
				(int) val1
			);
		}
	}

	// Get the PointArrayStatus value
	if ( f == &PointArrayStatus )
	{
		SbVariant *vPointArrayStatus = (SbVariant *)PointArrayStatus.getValues(0);
		SoInput input;
		int nb_fields = PointArrayStatus.getNum();

		int val0;
		int val1;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vPointArrayStatus[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			mObject->SetPointArrayStatus( 
				(int) val0,
				(int) val1
			);
		}
	}

	// Get the FileName value
	if ( f == &FileName )
		SO_VTK_SET_FIELD_MFSTRING( mObject, FileName);

	// Get the HierarchyArrayStatus value
	if ( f == &HierarchyArrayStatus )
	{
		SbVariant *vHierarchyArrayStatus = (SbVariant *)HierarchyArrayStatus.getValues(0);
		SoInput input;
		int nb_fields = HierarchyArrayStatus.getNum();

		int val0;
		int val1;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vHierarchyArrayStatus[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			mObject->SetHierarchyArrayStatus( 
				(int) val0,
				(int) val1
			);
		}
	}

	// Get the SideSetArrayStatus value
	if ( f == &SideSetArrayStatus )
	{
		SbVariant *vSideSetArrayStatus = (SbVariant *)SideSetArrayStatus.getValues(0);
		SoInput input;
		int nb_fields = SideSetArrayStatus.getNum();

		int val0;
		int val1;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vSideSetArrayStatus[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			mObject->SetSideSetArrayStatus( 
				(int) val0,
				(int) val1
			);
		}
	}

	// Get the FilterInputVar value
	if ( f == &FilterInputVar )
		addCalled = 1;
	// Get the DisplacementMagnitude value
	if ( f == &DisplacementMagnitude )
		SO_VTK_SET_FIELD_VALUE( mObject, DisplacementMagnitude);

	// Get the AllPointArrayStatus value
	if ( f == &AllPointArrayStatus )
		SO_VTK_SET_FIELD_VALUE( mObject, AllPointArrayStatus);

	// Get the BlockArrayStatus value
	if ( f == &BlockArrayStatus )
	{
		SbVariant *vBlockArrayStatus = (SbVariant *)BlockArrayStatus.getValues(0);
		SoInput input;
		int nb_fields = BlockArrayStatus.getNum();

		int val0;
		int val1;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vBlockArrayStatus[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			mObject->SetBlockArrayStatus( 
				(int) val0,
				(int) val1
			);
		}
	}

	// Get the PackExodusModelOntoOutput value
	if ( f == &PackExodusModelOntoOutput )
		SO_VTK_SET_FIELD_VALUE( mObject, PackExodusModelOntoOutput);

	// Get the AllBlockArrayStatus value
	if ( f == &AllBlockArrayStatus )
		SO_VTK_SET_FIELD_VALUE( mObject, AllBlockArrayStatus);

	// Get the AllCellArrayStatus value
	if ( f == &AllCellArrayStatus )
		SO_VTK_SET_FIELD_VALUE( mObject, AllCellArrayStatus);

	// Get the DisplayType value
	if ( f == &DisplayType )
		SO_VTK_SET_FIELD_VALUE( mObject, DisplayType);

	// Get the TimeStep value
	if ( f == &TimeStep )
		SO_VTK_SET_FIELD_VALUE( mObject, TimeStep);

	// Get the FilterNumeratorWeight value
	if ( f == &FilterNumeratorWeight )
		addCalled = 1;
	// Get the GenerateGlobalElementIdArray value
	if ( f == &GenerateGlobalElementIdArray )
		SO_VTK_SET_FIELD_VALUE( mObject, GenerateGlobalElementIdArray);

	// Get the TimeStepRange value
	if ( f == &TimeStepRange )
		SO_VTK_SET_FIELD_VEC2F( mObject, TimeStepRange);

	// Get the GenerateBlockIdCellArray value
	if ( f == &GenerateBlockIdCellArray )
		SO_VTK_SET_FIELD_VALUE( mObject, GenerateBlockIdCellArray);

	// Get the AllHierarchyArrayStatus value
	if ( f == &AllHierarchyArrayStatus )
		SO_VTK_SET_FIELD_VALUE( mObject, AllHierarchyArrayStatus);

	// Get the FilterForwardNumeratorWeight value
	if ( f == &FilterForwardNumeratorWeight )
		addCalled = 1;
	// Get the AllMaterialArrayStatus value
	if ( f == &AllMaterialArrayStatus )
		SO_VTK_SET_FIELD_VALUE( mObject, AllMaterialArrayStatus);

	mObject->Update();
}

void SoVtkExodusReader::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkExodusReader::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the NodeSetArrayStatus value
	if (addCalled == 1)
	{
		SbVariant *vNodeSetArrayStatus = (SbVariant *)NodeSetArrayStatus.getValues(0);
		SoInput input;
		int nb_fields = NodeSetArrayStatus.getNum();

		int val0;
		int val1;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vNodeSetArrayStatus[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			mObject->SetNodeSetArrayStatus( 
				(int) val0,
				(int) val1
			);
		}
	}

	// Get the ApplyDisplacements value
	
		SO_VTK_SET_FIELD_VALUE( mObject, ApplyDisplacements);

	// Get the CellArrayStatus value
	if (addCalled == 1)
	{
		SbVariant *vCellArrayStatus = (SbVariant *)CellArrayStatus.getValues(0);
		SoInput input;
		int nb_fields = CellArrayStatus.getNum();

		int val0;
		int val1;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vCellArrayStatus[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			mObject->SetCellArrayStatus( 
				(int) val0,
				(int) val1
			);
		}
	}

	// Get the FilterOutputVar value
	
		SO_VTK_ADD_FIELD_MFSTRING( mObject, FilterOutputVar);

	// Get the GenerateGlobalNodeIdArray value
	
		SO_VTK_SET_FIELD_VALUE( mObject, GenerateGlobalNodeIdArray);

	// Get the AllPartArrayStatus value
	
		SO_VTK_SET_FIELD_VALUE( mObject, AllPartArrayStatus);

	// Get the XMLFileName value
	
		SO_VTK_SET_FIELD_MFSTRING( mObject, XMLFileName);

	// Get the PartArrayStatus value
	if (addCalled == 1)
	{
		SbVariant *vPartArrayStatus = (SbVariant *)PartArrayStatus.getValues(0);
		SoInput input;
		int nb_fields = PartArrayStatus.getNum();

		int val0;
		int val1;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vPartArrayStatus[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			mObject->SetPartArrayStatus( 
				(int) val0,
				(int) val1
			);
		}
	}

	// Get the FilterDenominatorWeight value
	
		SO_VTK_ADD_FIELD_VALUE( mObject, FilterDenominatorWeight);

	// Get the AllAssemblyArrayStatus value
	
		SO_VTK_SET_FIELD_VALUE( mObject, AllAssemblyArrayStatus);

	// Get the MaterialArrayStatus value
	if (addCalled == 1)
	{
		SbVariant *vMaterialArrayStatus = (SbVariant *)MaterialArrayStatus.getValues(0);
		SoInput input;
		int nb_fields = MaterialArrayStatus.getNum();

		int val0;
		int val1;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vMaterialArrayStatus[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			mObject->SetMaterialArrayStatus( 
				(int) val0,
				(int) val1
			);
		}
	}

	// Get the ExodusModelMetadata value
	
		SO_VTK_SET_FIELD_VALUE( mObject, ExodusModelMetadata);

	// Get the AssemblyArrayStatus value
	if (addCalled == 1)
	{
		SbVariant *vAssemblyArrayStatus = (SbVariant *)AssemblyArrayStatus.getValues(0);
		SoInput input;
		int nb_fields = AssemblyArrayStatus.getNum();

		int val0;
		int val1;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vAssemblyArrayStatus[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			mObject->SetAssemblyArrayStatus( 
				(int) val0,
				(int) val1
			);
		}
	}

	// Get the PointArrayStatus value
	if (addCalled == 1)
	{
		SbVariant *vPointArrayStatus = (SbVariant *)PointArrayStatus.getValues(0);
		SoInput input;
		int nb_fields = PointArrayStatus.getNum();

		int val0;
		int val1;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vPointArrayStatus[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			mObject->SetPointArrayStatus( 
				(int) val0,
				(int) val1
			);
		}
	}

	// Get the FileName value
	
		SO_VTK_SET_FIELD_MFSTRING( mObject, FileName);

	// Get the HierarchyArrayStatus value
	if (addCalled == 1)
	{
		SbVariant *vHierarchyArrayStatus = (SbVariant *)HierarchyArrayStatus.getValues(0);
		SoInput input;
		int nb_fields = HierarchyArrayStatus.getNum();

		int val0;
		int val1;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vHierarchyArrayStatus[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			mObject->SetHierarchyArrayStatus( 
				(int) val0,
				(int) val1
			);
		}
	}

	// Get the SideSetArrayStatus value
	if (addCalled == 1)
	{
		SbVariant *vSideSetArrayStatus = (SbVariant *)SideSetArrayStatus.getValues(0);
		SoInput input;
		int nb_fields = SideSetArrayStatus.getNum();

		int val0;
		int val1;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vSideSetArrayStatus[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			mObject->SetSideSetArrayStatus( 
				(int) val0,
				(int) val1
			);
		}
	}

	// Get the FilterInputVar value
	
		SO_VTK_ADD_FIELD_MFSTRING( mObject, FilterInputVar);

	// Get the DisplacementMagnitude value
	
		SO_VTK_SET_FIELD_VALUE( mObject, DisplacementMagnitude);

	// Get the AllPointArrayStatus value
	
		SO_VTK_SET_FIELD_VALUE( mObject, AllPointArrayStatus);

	// Get the BlockArrayStatus value
	if (addCalled == 1)
	{
		SbVariant *vBlockArrayStatus = (SbVariant *)BlockArrayStatus.getValues(0);
		SoInput input;
		int nb_fields = BlockArrayStatus.getNum();

		int val0;
		int val1;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vBlockArrayStatus[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			mObject->SetBlockArrayStatus( 
				(int) val0,
				(int) val1
			);
		}
	}

	// Get the PackExodusModelOntoOutput value
	
		SO_VTK_SET_FIELD_VALUE( mObject, PackExodusModelOntoOutput);

	// Get the AllBlockArrayStatus value
	
		SO_VTK_SET_FIELD_VALUE( mObject, AllBlockArrayStatus);

	// Get the AllCellArrayStatus value
	
		SO_VTK_SET_FIELD_VALUE( mObject, AllCellArrayStatus);

	// Get the DisplayType value
	
		SO_VTK_SET_FIELD_VALUE( mObject, DisplayType);

	// Get the TimeStep value
	
		SO_VTK_SET_FIELD_VALUE( mObject, TimeStep);

	// Get the FilterNumeratorWeight value
	
		SO_VTK_ADD_FIELD_VALUE( mObject, FilterNumeratorWeight);

	// Get the GenerateGlobalElementIdArray value
	
		SO_VTK_SET_FIELD_VALUE( mObject, GenerateGlobalElementIdArray);

	// Get the TimeStepRange value
	
		SO_VTK_SET_FIELD_VEC2F( mObject, TimeStepRange);

	// Get the GenerateBlockIdCellArray value
	
		SO_VTK_SET_FIELD_VALUE( mObject, GenerateBlockIdCellArray);

	// Get the AllHierarchyArrayStatus value
	
		SO_VTK_SET_FIELD_VALUE( mObject, AllHierarchyArrayStatus);

	// Get the FilterForwardNumeratorWeight value
	
		SO_VTK_ADD_FIELD_VALUE( mObject, FilterForwardNumeratorWeight);

	// Get the AllMaterialArrayStatus value
	
		SO_VTK_SET_FIELD_VALUE( mObject, AllMaterialArrayStatus);

	mObject->Update();
}
