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
/*
 * \brief
 * \author Sylvain Jaume, Francois Huguet
 */

# include "SoVtkPiecewiseFunction.h"
# include "SoVtkUtils.h"

# include "vtkExtentTranslator.h"
# include "vtkFieldData.h"
# include "vtkSource.h"
# include "vtkInformation.h"


SO_ENGINE_SOURCE( SoVtkPiecewiseFunction )

SoVtkPiecewiseFunction::SoVtkPiecewiseFunction()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkPiecewiseFunction);

	mObject = vtkPiecewiseFunction::New();

	mObject->Register(0);mObject->SetGlobalWarningDisplay(0);

	vtkPiecewiseFunction *aPiecewiseFunction = vtkPiecewiseFunction::New();

	SO_ENGINE_ADD_INPUT(ExtentTranslator, (0));

	SO_ENGINE_ADD_INPUT(FieldData, (0));

	SO_ENGINE_ADD_INPUT(Segment, ());
	Segment.setFormat("double double double double");

	SO_ENGINE_ADD_INPUT(MaximumNumberOfPieces, (0));
	MaximumNumberOfPieces.setValue(aPiecewiseFunction->GetMaximumNumberOfPieces());

	SO_ENGINE_ADD_INPUT(RequestExactExtent, (0));
	RequestExactExtent.setValue(aPiecewiseFunction->GetRequestExactExtent());

	SO_ENGINE_ADD_INPUT(UpdatePiece, (0));
	UpdatePiece.setValue(aPiecewiseFunction->GetUpdatePiece());

	SO_ENGINE_ADD_INPUT(WholeBoundingBox, ());
	WholeBoundingBox.setFormat("double double double double double double");

	SO_ENGINE_ADD_INPUT(UpdateExtent, ());
	UpdateExtent.setFormat("int int int");

	SO_ENGINE_ADD_INPUT(UpdateGhostLevel, (0));
	UpdateGhostLevel.setValue(aPiecewiseFunction->GetUpdateGhostLevel());

	SO_ENGINE_ADD_INPUT(UpdateNumberOfPieces, (0));
	UpdateNumberOfPieces.setValue(aPiecewiseFunction->GetUpdateNumberOfPieces());

	SO_ENGINE_ADD_INPUT(Clamping, (0));
	Clamping.setValue(aPiecewiseFunction->GetClamping());

	SO_ENGINE_ADD_INPUT(WholeExtent, ());
	WholeExtent.setFormat("int int int int int int");

	SO_ENGINE_ADD_INPUT(Source, (0));

	SO_ENGINE_ADD_INPUT(PipelineInformation, (0));

	SO_ENGINE_ADD_INPUT(Point, ());
	Point.setFormat("double double");

	aPiecewiseFunction->Delete();


	SO_ENGINE_ADD_OUTPUT(Output, SoSFVtkObject );
	mOutput = 0;

}

SoVtkPiecewiseFunction::~SoVtkPiecewiseFunction()
{
	// Deletion of the objects if they exist
	if ( mOutput )
	{
	
		mOutput->unref();
		mOutput = 0;
	}
	
	if ( mObject )
	{
		mObject->UnRegister(0);
		mObject->Delete();
		mObject = 0;
	}
	

}

void SoVtkPiecewiseFunction::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkPiecewiseFunction, SoEngine, "Engine" );
}

void SoVtkPiecewiseFunction::evaluate()
{
	try
	{
		// Deletion of the objects if they exist
		if ( mOutput )
		{
		
			mOutput->unref();
			mOutput = 0;
		}
		
		// Get the input type(s)
		mOutput = new SoVtkObject();
		mOutput->ref();
		mOutput->setPointer( mObject );

	}
	catch(...)
	{
		SoDebugError::post( __FILE__, "Unknown Exception" );
		return;
	}
	SO_ENGINE_OUTPUT( Output, SoSFVtkObject, setValue( mOutput ) );
}


void SoVtkPiecewiseFunction::inputChanged(SoField * f)
{
	// Get the ExtentTranslator value
	if ( f == &ExtentTranslator )
		SO_VTK_SET_FIELD_DATA( mObject, ExtentTranslator, vtkExtentTranslator);

	// Get the FieldData value
	if ( f == &FieldData )
		SO_VTK_SET_FIELD_DATA( mObject, FieldData, vtkFieldData);

	// Get the Segment value
	if ( f == &Segment )
	{
		SbVariant *vSegment = (SbVariant *)Segment.getValues(0);
		SoInput input;
		int nb_fields = Segment.getNum();

		double val0;
		double val1;
		double val2;
		double val3;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vSegment[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			input.read(val2);
			input.read(val3);
			mObject->AddSegment( 
				(double) val0,
				(double) val1,
				(double) val2,
				(double) val3
			);
		}
	}

	// Get the MaximumNumberOfPieces value
	if ( f == &MaximumNumberOfPieces )
		SO_VTK_SET_FIELD_VALUE( mObject, MaximumNumberOfPieces);

	// Get the RequestExactExtent value
	if ( f == &RequestExactExtent )
		SO_VTK_SET_FIELD_VALUE( mObject, RequestExactExtent);

	// Get the UpdatePiece value
	if ( f == &UpdatePiece )
		SO_VTK_SET_FIELD_VALUE( mObject, UpdatePiece);

	// Get the WholeBoundingBox value
	if ( f == &WholeBoundingBox )
	{
		SbVariant vWholeBoundingBox = (SbVariant)WholeBoundingBox.getValue();
		SoInput input;
		double val0;
		double val1;
		double val2;
		double val3;
		double val4;
		double val5;
	
		input.setBuffer((void *)vWholeBoundingBox.getField().getString(),256);
		input.read(val0);
		input.read(val1);
		input.read(val2);
		input.read(val3);
		input.read(val4);
		input.read(val5);
		mObject->SetWholeBoundingBox( 
			(double) val0,
			(double) val1,
			(double) val2,
			(double) val3,
			(double) val4,
			(double) val5
		);
	}
	// Get the UpdateExtent value
	if ( f == &UpdateExtent )
	{
		SbVariant vUpdateExtent = (SbVariant)UpdateExtent.getValue();
		SoInput input;
		int val0;
		int val1;
		int val2;
	
		input.setBuffer((void *)vUpdateExtent.getField().getString(),256);
		input.read(val0);
		input.read(val1);
		input.read(val2);
		mObject->SetUpdateExtent( 
			(int) val0,
			(int) val1,
			(int) val2
		);
	}
	// Get the UpdateGhostLevel value
	if ( f == &UpdateGhostLevel )
		SO_VTK_SET_FIELD_VALUE( mObject, UpdateGhostLevel);

	// Get the UpdateNumberOfPieces value
	if ( f == &UpdateNumberOfPieces )
		SO_VTK_SET_FIELD_VALUE( mObject, UpdateNumberOfPieces);

	// Get the Clamping value
	if ( f == &Clamping )
		SO_VTK_SET_FIELD_VALUE( mObject, Clamping);

	// Get the WholeExtent value
	if ( f == &WholeExtent )
	{
		SbVariant vWholeExtent = (SbVariant)WholeExtent.getValue();
		SoInput input;
		int val0;
		int val1;
		int val2;
		int val3;
		int val4;
		int val5;
	
		input.setBuffer((void *)vWholeExtent.getField().getString(),256);
		input.read(val0);
		input.read(val1);
		input.read(val2);
		input.read(val3);
		input.read(val4);
		input.read(val5);
		mObject->SetWholeExtent( 
			(int) val0,
			(int) val1,
			(int) val2,
			(int) val3,
			(int) val4,
			(int) val5
		);
	}
	// Get the Source value
	if ( f == &Source )
		SO_VTK_SET_FIELD_DATA( mObject, Source, vtkSource);

	// Get the PipelineInformation value
	if ( f == &PipelineInformation )
		SO_VTK_SET_FIELD_DATA( mObject, PipelineInformation, vtkInformation);

	// Get the Point value
	if ( f == &Point )
	{
		SbVariant *vPoint = (SbVariant *)Point.getValues(0);
		SoInput input;
		int nb_fields = Point.getNum();

		double val0;
		double val1;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vPoint[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			mObject->AddPoint( 
				(double) val0,
				(double) val1
			);
		}
	}

	//mObject->Update();
	
}

