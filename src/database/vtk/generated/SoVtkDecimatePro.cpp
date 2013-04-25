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
 
 
 
# include "SoVtkDecimatePro.h"
# include "SoVtkUtils.h"

# include "vtkAlgorithmOutput.h"
# include "vtkPolyData.h"


SO_ENGINE_SOURCE( SoVtkDecimatePro )

SoVtkDecimatePro::SoVtkDecimatePro()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkDecimatePro);

	mObject = vtkDecimatePro::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkDecimatePro *aDecimatePro = vtkDecimatePro::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(AbsoluteError, (0));
	AbsoluteError.setValue(aDecimatePro->GetAbsoluteError());

	SO_ENGINE_ADD_INPUT(Splitting, (0));
	Splitting.setValue(aDecimatePro->GetSplitting());

	SO_ENGINE_ADD_INPUT(AccumulateError, (0));
	AccumulateError.setValue(aDecimatePro->GetAccumulateError());

	SO_ENGINE_ADD_INPUT(InflectionPointRatio, (0));
	InflectionPointRatio.setValue(aDecimatePro->GetInflectionPointRatio());

	SO_ENGINE_ADD_INPUT(MaximumError, (0));
	MaximumError.setValue(aDecimatePro->GetMaximumError());

	SO_ENGINE_ADD_INPUT(ErrorIsAbsolute, (0));
	ErrorIsAbsolute.setValue(aDecimatePro->GetErrorIsAbsolute());

	SO_ENGINE_ADD_INPUT(TargetReduction, (0));
	TargetReduction.setValue(aDecimatePro->GetTargetReduction());

	SO_ENGINE_ADD_INPUT(BoundaryVertexDeletion, (0));
	BoundaryVertexDeletion.setValue(aDecimatePro->GetBoundaryVertexDeletion());

	SO_ENGINE_ADD_INPUT(PreserveTopology, (0));
	PreserveTopology.setValue(aDecimatePro->GetPreserveTopology());

	SO_ENGINE_ADD_INPUT(PreSplitMesh, (0));
	PreSplitMesh.setValue(aDecimatePro->GetPreSplitMesh());

	SO_ENGINE_ADD_INPUT(Degree, (0));
	Degree.setValue(aDecimatePro->GetDegree());

	SO_ENGINE_ADD_INPUT(FeatureAngle, (0));
	FeatureAngle.setValue(aDecimatePro->GetFeatureAngle());

	SO_ENGINE_ADD_INPUT(SplitAngle, (0));
	SplitAngle.setValue(aDecimatePro->GetSplitAngle());

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	aDecimatePro->Delete();


	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;
	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;


	addCalled = 0;
}

SoVtkDecimatePro::~SoVtkDecimatePro()
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

void SoVtkDecimatePro::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkDecimatePro, SoEngine, "Engine" );
}

void SoVtkDecimatePro::evaluate()
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


void SoVtkDecimatePro::inputChanged(SoField * f)
{
	// Get the AbsoluteError value
	if ( f == &AbsoluteError )
		SO_VTK_SET_FIELD_VALUE( mObject, AbsoluteError);

	// Get the Splitting value
	if ( f == &Splitting )
		SO_VTK_SET_FIELD_VALUE( mObject, Splitting);

	// Get the AccumulateError value
	if ( f == &AccumulateError )
		SO_VTK_SET_FIELD_VALUE( mObject, AccumulateError);

	// Get the InflectionPointRatio value
	if ( f == &InflectionPointRatio )
		SO_VTK_SET_FIELD_VALUE( mObject, InflectionPointRatio);

	// Get the MaximumError value
	if ( f == &MaximumError )
		SO_VTK_SET_FIELD_VALUE( mObject, MaximumError);

	// Get the ErrorIsAbsolute value
	if ( f == &ErrorIsAbsolute )
		SO_VTK_SET_FIELD_VALUE( mObject, ErrorIsAbsolute);

	// Get the TargetReduction value
	if ( f == &TargetReduction )
		SO_VTK_SET_FIELD_VALUE( mObject, TargetReduction);

	// Get the BoundaryVertexDeletion value
	if ( f == &BoundaryVertexDeletion )
		SO_VTK_SET_FIELD_VALUE( mObject, BoundaryVertexDeletion);

	// Get the PreserveTopology value
	if ( f == &PreserveTopology )
		SO_VTK_SET_FIELD_VALUE( mObject, PreserveTopology);

	// Get the PreSplitMesh value
	if ( f == &PreSplitMesh )
		SO_VTK_SET_FIELD_VALUE( mObject, PreSplitMesh);

	// Get the Degree value
	if ( f == &Degree )
		SO_VTK_SET_FIELD_VALUE( mObject, Degree);

	// Get the FeatureAngle value
	if ( f == &FeatureAngle )
		SO_VTK_SET_FIELD_VALUE( mObject, FeatureAngle);

	// Get the SplitAngle value
	if ( f == &SplitAngle )
		SO_VTK_SET_FIELD_VALUE( mObject, SplitAngle);

	mObject->Update();
}

void SoVtkDecimatePro::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkDecimatePro::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the AbsoluteError value
	
		SO_VTK_SET_FIELD_VALUE( mObject, AbsoluteError);

	// Get the Splitting value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Splitting);

	// Get the AccumulateError value
	
		SO_VTK_SET_FIELD_VALUE( mObject, AccumulateError);

	// Get the InflectionPointRatio value
	
		SO_VTK_SET_FIELD_VALUE( mObject, InflectionPointRatio);

	// Get the MaximumError value
	
		SO_VTK_SET_FIELD_VALUE( mObject, MaximumError);

	// Get the ErrorIsAbsolute value
	
		SO_VTK_SET_FIELD_VALUE( mObject, ErrorIsAbsolute);

	// Get the TargetReduction value
	
		SO_VTK_SET_FIELD_VALUE( mObject, TargetReduction);

	// Get the BoundaryVertexDeletion value
	
		SO_VTK_SET_FIELD_VALUE( mObject, BoundaryVertexDeletion);

	// Get the PreserveTopology value
	
		SO_VTK_SET_FIELD_VALUE( mObject, PreserveTopology);

	// Get the PreSplitMesh value
	
		SO_VTK_SET_FIELD_VALUE( mObject, PreSplitMesh);

	// Get the Degree value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Degree);

	// Get the FeatureAngle value
	
		SO_VTK_SET_FIELD_VALUE( mObject, FeatureAngle);

	// Get the SplitAngle value
	
		SO_VTK_SET_FIELD_VALUE( mObject, SplitAngle);

	mObject->Update();
}
