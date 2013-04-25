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
 
 
 
# include "SoVtkDistributedStreamTracer.h"
# include "SoVtkUtils.h"

# include "vtkInterpolatedVelocityField.h"
# include "vtkMultiProcessController.h"
# include "vtkAlgorithmOutput.h"
# include "vtkDataSet.h"
# include "vtkInitialValueProblemSolver.h"
# include "vtkPolyData.h"


SO_ENGINE_SOURCE( SoVtkDistributedStreamTracer )

SoVtkDistributedStreamTracer::SoVtkDistributedStreamTracer()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkDistributedStreamTracer);

	mObject = vtkDistributedStreamTracer::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkDistributedStreamTracer *aDistributedStreamTracer = vtkDistributedStreamTracer::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(InterpolatorPrototype, (0));

	SO_ENGINE_ADD_INPUT(StartPosition, (0,0,0));

	x = aDistributedStreamTracer->GetStartPosition();
	StartPosition.setValue(x[0],x[1],x[2]);

	SO_ENGINE_ADD_INPUT(MinimumIntegrationStep, (0));
	SO_ENGINE_ADD_INPUT(InitialIntegrationStepUnit, (0));
	InitialIntegrationStepUnit.setValue(aDistributedStreamTracer->GetInitialIntegrationStepUnit());

	SO_ENGINE_ADD_INPUT(MaximumPropagation, (0));
	SO_ENGINE_ADD_INPUT(Controller, (0));

	SO_ENGINE_ADD_INPUT(MaximumIntegrationStepUnit, (0));
	MaximumIntegrationStepUnit.setValue(aDistributedStreamTracer->GetMaximumIntegrationStepUnit());

	SO_ENGINE_ADD_INPUT(SourceConnection, (0));

	SO_ENGINE_ADD_INPUT(TerminalSpeed, (0));
	TerminalSpeed.setValue(aDistributedStreamTracer->GetTerminalSpeed());

	SO_ENGINE_ADD_INPUT(IntegrationDirection, (0));
	IntegrationDirection.setValue(aDistributedStreamTracer->GetIntegrationDirection());

	SO_ENGINE_ADD_INPUT(Source, (0));

	SO_ENGINE_ADD_INPUT(RotationScale, (0));
	RotationScale.setValue(aDistributedStreamTracer->GetRotationScale());

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	SO_ENGINE_ADD_INPUT(IntegratorType, (0));
	SO_ENGINE_ADD_INPUT(MinimumIntegrationStepUnit, (0));
	MinimumIntegrationStepUnit.setValue(aDistributedStreamTracer->GetMinimumIntegrationStepUnit());

	SO_ENGINE_ADD_INPUT(ComputeVorticity, (0));
	ComputeVorticity.setValue(aDistributedStreamTracer->GetComputeVorticity());

	SO_ENGINE_ADD_INPUT(MaximumError, (0));
	MaximumError.setValue(aDistributedStreamTracer->GetMaximumError());

	SO_ENGINE_ADD_INPUT(InitialIntegrationStep, (0));
	SO_ENGINE_ADD_INPUT(Integrator, (0));

	SO_ENGINE_ADD_INPUT(MaximumIntegrationStep, (0));
	SO_ENGINE_ADD_INPUT(MaximumPropagationUnit, (0));
	MaximumPropagationUnit.setValue(aDistributedStreamTracer->GetMaximumPropagationUnit());

	aDistributedStreamTracer->Delete();


	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;
	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;
	SO_ENGINE_ADD_OUTPUT( oSource, SoSFVtkObject );
	mSource = 0;


	addCalled = 0;
}

SoVtkDistributedStreamTracer::~SoVtkDistributedStreamTracer()
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
	
	if ( mSource )
	{
	
		mSource->unref();
		mSource = 0;
	}
	
	if ( mObject )
	{
		mObject->UnRegister(0);
		mObject->Delete();
		mObject = 0;
	}
	

}

void SoVtkDistributedStreamTracer::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkDistributedStreamTracer, SoEngine, "Engine" );
}

void SoVtkDistributedStreamTracer::evaluate()
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
		
		if ( mSource )
		{
		
			mSource->unref();
			mSource = 0;
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

		mObject->GetSource();
		mSource = new SoVtkObject();
		mSource->ref();
		mSource->setPointer( mObject->GetSource() );

	}
	catch(...)
	{
		SoDebugError::post( __FILE__, "Unknown Exception" );
		return;
	}
	SO_ENGINE_OUTPUT( Output, SoSFVtkObject, setValue( mOutput ) );
	SO_ENGINE_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput, setValue( mOutputPort ) );
	SO_ENGINE_OUTPUT( oSource, SoSFVtkObject, setValue( mSource ) );
}


void SoVtkDistributedStreamTracer::inputChanged(SoField * f)
{
	// Get the InterpolatorPrototype value
	if ( f == &InterpolatorPrototype )
		SO_VTK_SET_FIELD_DATA( mObject, InterpolatorPrototype, vtkInterpolatedVelocityField);

	// Get the StartPosition value
	if ( f == &StartPosition )
		SO_VTK_SET_FIELD_VEC3F( mObject, StartPosition);

	// Get the MinimumIntegrationStep value
	if ( f == &MinimumIntegrationStep )
		SO_VTK_SET_FIELD_VALUE( mObject, MinimumIntegrationStep);

	// Get the InitialIntegrationStepUnit value
	if ( f == &InitialIntegrationStepUnit )
		SO_VTK_SET_FIELD_VALUE( mObject, InitialIntegrationStepUnit);

	// Get the MaximumPropagation value
	if ( f == &MaximumPropagation )
		SO_VTK_SET_FIELD_VALUE( mObject, MaximumPropagation);

	// Get the Controller value
	if ( f == &Controller )
		SO_VTK_SET_FIELD_DATA( mObject, Controller, vtkMultiProcessController);

	// Get the MaximumIntegrationStepUnit value
	if ( f == &MaximumIntegrationStepUnit )
		SO_VTK_SET_FIELD_VALUE( mObject, MaximumIntegrationStepUnit);

	// Get the SourceConnection value
	if ( f == &SourceConnection )
		SO_VTK_SET_FIELD_DATA( mObject, SourceConnection, vtkAlgorithmOutput);

	// Get the TerminalSpeed value
	if ( f == &TerminalSpeed )
		SO_VTK_SET_FIELD_VALUE( mObject, TerminalSpeed);

	// Get the IntegrationDirection value
	if ( f == &IntegrationDirection )
		SO_VTK_SET_FIELD_VALUE( mObject, IntegrationDirection);

	// Get the Source value
	if ( f == &Source )
		SO_VTK_SET_FIELD_DATA( mObject, Source, vtkDataSet);

	// Get the RotationScale value
	if ( f == &RotationScale )
		SO_VTK_SET_FIELD_VALUE( mObject, RotationScale);

	// Get the IntegratorType value
	if ( f == &IntegratorType )
		SO_VTK_SET_FIELD_VALUE( mObject, IntegratorType);

	// Get the MinimumIntegrationStepUnit value
	if ( f == &MinimumIntegrationStepUnit )
		SO_VTK_SET_FIELD_VALUE( mObject, MinimumIntegrationStepUnit);

	// Get the ComputeVorticity value
	if ( f == &ComputeVorticity )
		SO_VTK_SET_FIELD_VALUE( mObject, ComputeVorticity);

	// Get the MaximumError value
	if ( f == &MaximumError )
		SO_VTK_SET_FIELD_VALUE( mObject, MaximumError);

	// Get the InitialIntegrationStep value
	if ( f == &InitialIntegrationStep )
		SO_VTK_SET_FIELD_VALUE( mObject, InitialIntegrationStep);

	// Get the Integrator value
	if ( f == &Integrator )
		SO_VTK_SET_FIELD_DATA( mObject, Integrator, vtkInitialValueProblemSolver);

	// Get the MaximumIntegrationStep value
	if ( f == &MaximumIntegrationStep )
		SO_VTK_SET_FIELD_VALUE( mObject, MaximumIntegrationStep);

	// Get the MaximumPropagationUnit value
	if ( f == &MaximumPropagationUnit )
		SO_VTK_SET_FIELD_VALUE( mObject, MaximumPropagationUnit);

	mObject->Update();
}

void SoVtkDistributedStreamTracer::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkDistributedStreamTracer::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the InterpolatorPrototype value
	
		SO_VTK_SET_FIELD_DATA( mObject, InterpolatorPrototype, vtkInterpolatedVelocityField);

	// Get the StartPosition value
	
		SO_VTK_SET_FIELD_VEC3F( mObject, StartPosition);

	// Get the MinimumIntegrationStep value
	
		SO_VTK_SET_FIELD_VALUE( mObject, MinimumIntegrationStep);

	// Get the InitialIntegrationStepUnit value
	
		SO_VTK_SET_FIELD_VALUE( mObject, InitialIntegrationStepUnit);

	// Get the MaximumPropagation value
	
		SO_VTK_SET_FIELD_VALUE( mObject, MaximumPropagation);

	// Get the Controller value
	
		SO_VTK_SET_FIELD_DATA( mObject, Controller, vtkMultiProcessController);

	// Get the MaximumIntegrationStepUnit value
	
		SO_VTK_SET_FIELD_VALUE( mObject, MaximumIntegrationStepUnit);

	// Get the SourceConnection value
	
		SO_VTK_SET_FIELD_DATA( mObject, SourceConnection, vtkAlgorithmOutput);

	// Get the TerminalSpeed value
	
		SO_VTK_SET_FIELD_VALUE( mObject, TerminalSpeed);

	// Get the IntegrationDirection value
	
		SO_VTK_SET_FIELD_VALUE( mObject, IntegrationDirection);

	// Get the Source value
	
		SO_VTK_SET_FIELD_DATA( mObject, Source, vtkDataSet);

	// Get the RotationScale value
	
		SO_VTK_SET_FIELD_VALUE( mObject, RotationScale);

	// Get the IntegratorType value
	
		SO_VTK_SET_FIELD_VALUE( mObject, IntegratorType);

	// Get the MinimumIntegrationStepUnit value
	
		SO_VTK_SET_FIELD_VALUE( mObject, MinimumIntegrationStepUnit);

	// Get the ComputeVorticity value
	
		SO_VTK_SET_FIELD_VALUE( mObject, ComputeVorticity);

	// Get the MaximumError value
	
		SO_VTK_SET_FIELD_VALUE( mObject, MaximumError);

	// Get the InitialIntegrationStep value
	
		SO_VTK_SET_FIELD_VALUE( mObject, InitialIntegrationStep);

	// Get the Integrator value
	
		SO_VTK_SET_FIELD_DATA( mObject, Integrator, vtkInitialValueProblemSolver);

	// Get the MaximumIntegrationStep value
	
		SO_VTK_SET_FIELD_VALUE( mObject, MaximumIntegrationStep);

	// Get the MaximumPropagationUnit value
	
		SO_VTK_SET_FIELD_VALUE( mObject, MaximumPropagationUnit);

	mObject->Update();
}
