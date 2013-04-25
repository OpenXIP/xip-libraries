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
 
 
 
# include "SoVtkImageReslice.h"
# include "SoVtkUtils.h"

# include "vtkImageData.h"
# include "vtkMatrix4x4.h"
# include "vtkAlgorithmOutput.h"
# include "vtkAbstractTransform.h"


SO_ENGINE_SOURCE( SoVtkImageReslice )

SoVtkImageReslice::SoVtkImageReslice()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkImageReslice);

	mObject = vtkImageReslice::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);

	vtkImageReslice *aImageReslice = vtkImageReslice::New();
	double *x = 0;
	int *y = 0;
	float *z = 0;

	SO_ENGINE_ADD_INPUT(BackgroundColor, (0,0,0,0));

	x = aImageReslice->GetBackgroundColor();
	BackgroundColor.setValue(x[0],x[1],x[2],x[3]);

	SO_ENGINE_ADD_INPUT(NumberOfThreads, (0));
	NumberOfThreads.setValue(aImageReslice->GetNumberOfThreads());

	SO_ENGINE_ADD_INPUT(BackgroundLevel, (0));
	BackgroundLevel.setValue(aImageReslice->GetBackgroundLevel());

	SO_ENGINE_ADD_INPUT(OutputOrigin, (0,0,0));

	x = aImageReslice->GetOutputOrigin();
	OutputOrigin.setValue(x[0],x[1],x[2]);

	SO_ENGINE_ADD_INPUT(InformationInput, (0));

	SO_ENGINE_ADD_INPUT(ResliceAxesDirectionCosines, ());
	ResliceAxesDirectionCosines.setFormat("double double double double double double double double double");

	SO_ENGINE_ADD_INPUT(ResliceAxes, (0));

	SO_ENGINE_ADD_INPUT(Wrap, (0));
	Wrap.setValue(aImageReslice->GetWrap());

	SO_ENGINE_ADD_INPUT(ResliceAxesOrigin, ());
	ResliceAxesOrigin.setFormat("double double double");

	SO_ENGINE_ADD_INPUT(Mirror, (0));
	Mirror.setValue(aImageReslice->GetMirror());

	SO_ENGINE_ADD_INPUT(InputConnection, (0));

	SO_ENGINE_ADD_INPUT(Optimization, (0));
	Optimization.setValue(aImageReslice->GetOptimization());

	SO_ENGINE_ADD_INPUT(ResliceTransform, (0));

	SO_ENGINE_ADD_INPUT(OutputDimensionality, (0));
	OutputDimensionality.setValue(aImageReslice->GetOutputDimensionality());

	SO_ENGINE_ADD_INPUT(OutputSpacing, (0,0,0));

	x = aImageReslice->GetOutputSpacing();
	OutputSpacing.setValue(x[0],x[1],x[2]);

	SO_ENGINE_ADD_INPUT(InterpolationMode, (0));
	InterpolationMode.setValue(aImageReslice->GetInterpolationMode());

	SO_ENGINE_ADD_INPUT(OutputExtent, (0));

	SO_ENGINE_ADD_INPUT(Border, (0));
	Border.setValue(aImageReslice->GetBorder());

	SO_ENGINE_ADD_INPUT(AutoCropOutput, (0));
	AutoCropOutput.setValue(aImageReslice->GetAutoCropOutput());

	SO_ENGINE_ADD_INPUT(Interpolate, (0));
	SO_ENGINE_ADD_INPUT(TransformInputSampling, (0));
	TransformInputSampling.setValue(aImageReslice->GetTransformInputSampling());

	aImageReslice->Delete();


	SO_ENGINE_ADD_OUTPUT( Output, SoSFVtkObject );
	mOutput = 0;
	SO_ENGINE_ADD_OUTPUT( OutputPort, SoSFVtkAlgorithmOutput );
	mOutputPort = 0;


	addCalled = 0;
}

SoVtkImageReslice::~SoVtkImageReslice()
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

void SoVtkImageReslice::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkImageReslice, SoEngine, "Engine" );
}

void SoVtkImageReslice::evaluate()
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


void SoVtkImageReslice::inputChanged(SoField * f)
{
	// Get the BackgroundColor value
	if ( f == &BackgroundColor )
		SO_VTK_SET_FIELD_VEC4F( mObject, BackgroundColor);

	// Get the NumberOfThreads value
	if ( f == &NumberOfThreads )
		SO_VTK_SET_FIELD_VALUE( mObject, NumberOfThreads);

	// Get the BackgroundLevel value
	if ( f == &BackgroundLevel )
		SO_VTK_SET_FIELD_VALUE( mObject, BackgroundLevel);

	// Get the OutputOrigin value
	if ( f == &OutputOrigin )
		SO_VTK_SET_FIELD_VEC3F( mObject, OutputOrigin);

	// Get the InformationInput value
	if ( f == &InformationInput )
		SO_VTK_SET_FIELD_DATA( mObject, InformationInput, vtkImageData);

	// Get the ResliceAxesDirectionCosines value
	if ( f == &ResliceAxesDirectionCosines )
	{
		SbVariant *vResliceAxesDirectionCosines = (SbVariant *)ResliceAxesDirectionCosines.getValues(0);
		SoInput input;
		int nb_fields = ResliceAxesDirectionCosines.getNum();

		double val0;
		double val1;
		double val2;
		double val3;
		double val4;
		double val5;
		double val6;
		double val7;
		double val8;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vResliceAxesDirectionCosines[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			input.read(val2);
			input.read(val3);
			input.read(val4);
			input.read(val5);
			input.read(val6);
			input.read(val7);
			input.read(val8);
			mObject->SetResliceAxesDirectionCosines( 
				(double) val0,
				(double) val1,
				(double) val2,
				(double) val3,
				(double) val4,
				(double) val5,
				(double) val6,
				(double) val7,
				(double) val8
			);
		}
	}

	// Get the ResliceAxes value
	if ( f == &ResliceAxes )
		SO_VTK_SET_FIELD_DATA( mObject, ResliceAxes, vtkMatrix4x4);

	// Get the Wrap value
	if ( f == &Wrap )
		SO_VTK_SET_FIELD_VALUE( mObject, Wrap);

	// Get the ResliceAxesOrigin value
	if ( f == &ResliceAxesOrigin )
	{
		SbVariant *vResliceAxesOrigin = (SbVariant *)ResliceAxesOrigin.getValues(0);
		SoInput input;
		int nb_fields = ResliceAxesOrigin.getNum();

		double val0;
		double val1;
		double val2;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vResliceAxesOrigin[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			input.read(val2);
			mObject->SetResliceAxesOrigin( 
				(double) val0,
				(double) val1,
				(double) val2
			);
		}
	}

	// Get the Mirror value
	if ( f == &Mirror )
		SO_VTK_SET_FIELD_VALUE( mObject, Mirror);

	// Get the Optimization value
	if ( f == &Optimization )
		SO_VTK_SET_FIELD_VALUE( mObject, Optimization);

	// Get the ResliceTransform value
	if ( f == &ResliceTransform )
		SO_VTK_SET_FIELD_DATA( mObject, ResliceTransform, vtkAbstractTransform);

	// Get the OutputDimensionality value
	if ( f == &OutputDimensionality )
		SO_VTK_SET_FIELD_VALUE( mObject, OutputDimensionality);

	// Get the OutputSpacing value
	if ( f == &OutputSpacing )
		SO_VTK_SET_FIELD_VEC3F( mObject, OutputSpacing);

	// Get the InterpolationMode value
	if ( f == &InterpolationMode )
		SO_VTK_SET_FIELD_VALUE( mObject, InterpolationMode);

	// Get the OutputExtent value
	if ( f == &OutputExtent )
	{
		if ( OutputExtent.getNum() >= 6)
		{
			SO_VTK_SET_6_FIELD_MFINT32( mObject, OutputExtent);
		}
		else
		{
			SoDebugError::post( __FILE__, "This field must have 6 values." );
		}
	}

	// Get the Border value
	if ( f == &Border )
		SO_VTK_SET_FIELD_VALUE( mObject, Border);

	// Get the AutoCropOutput value
	if ( f == &AutoCropOutput )
		SO_VTK_SET_FIELD_VALUE( mObject, AutoCropOutput);

	// Get the Interpolate value
	if ( f == &Interpolate )
		SO_VTK_SET_FIELD_VALUE( mObject, Interpolate);

	// Get the TransformInputSampling value
	if ( f == &TransformInputSampling )
		SO_VTK_SET_FIELD_VALUE( mObject, TransformInputSampling);

	mObject->Update();
}

void SoVtkImageReslice::reset()
{
	mObject->UnRegister(0);
	mObject->Delete();
	mObject = 0;
	mObject = vtkImageReslice::New();
	mObject->Register(0);
	mObject->SetGlobalWarningDisplay(0);
	// Get the input type(s)
	SoVtkAlgorithmOutput *inputPortPtr = InputConnection.getValue();
	
	if (inputPortPtr)
		mObject->SetInputConnection(inputPortPtr->getPointer());

	// Get the BackgroundColor value
	
		SO_VTK_SET_FIELD_VEC4F( mObject, BackgroundColor);

	// Get the NumberOfThreads value
	
		SO_VTK_SET_FIELD_VALUE( mObject, NumberOfThreads);

	// Get the BackgroundLevel value
	
		SO_VTK_SET_FIELD_VALUE( mObject, BackgroundLevel);

	// Get the OutputOrigin value
	
		SO_VTK_SET_FIELD_VEC3F( mObject, OutputOrigin);

	// Get the InformationInput value
	
		SO_VTK_SET_FIELD_DATA( mObject, InformationInput, vtkImageData);

	// Get the ResliceAxesDirectionCosines value
	if (addCalled == 1)
	{
		SbVariant *vResliceAxesDirectionCosines = (SbVariant *)ResliceAxesDirectionCosines.getValues(0);
		SoInput input;
		int nb_fields = ResliceAxesDirectionCosines.getNum();

		double val0;
		double val1;
		double val2;
		double val3;
		double val4;
		double val5;
		double val6;
		double val7;
		double val8;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vResliceAxesDirectionCosines[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			input.read(val2);
			input.read(val3);
			input.read(val4);
			input.read(val5);
			input.read(val6);
			input.read(val7);
			input.read(val8);
			mObject->SetResliceAxesDirectionCosines( 
				(double) val0,
				(double) val1,
				(double) val2,
				(double) val3,
				(double) val4,
				(double) val5,
				(double) val6,
				(double) val7,
				(double) val8
			);
		}
	}

	// Get the ResliceAxes value
	
		SO_VTK_SET_FIELD_DATA( mObject, ResliceAxes, vtkMatrix4x4);

	// Get the Wrap value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Wrap);

	// Get the ResliceAxesOrigin value
	if (addCalled == 1)
	{
		SbVariant *vResliceAxesOrigin = (SbVariant *)ResliceAxesOrigin.getValues(0);
		SoInput input;
		int nb_fields = ResliceAxesOrigin.getNum();

		double val0;
		double val1;
		double val2;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vResliceAxesOrigin[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			input.read(val2);
			mObject->SetResliceAxesOrigin( 
				(double) val0,
				(double) val1,
				(double) val2
			);
		}
	}

	// Get the Mirror value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Mirror);

	// Get the Optimization value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Optimization);

	// Get the ResliceTransform value
	
		SO_VTK_SET_FIELD_DATA( mObject, ResliceTransform, vtkAbstractTransform);

	// Get the OutputDimensionality value
	
		SO_VTK_SET_FIELD_VALUE( mObject, OutputDimensionality);

	// Get the OutputSpacing value
	
		SO_VTK_SET_FIELD_VEC3F( mObject, OutputSpacing);

	// Get the InterpolationMode value
	
		SO_VTK_SET_FIELD_VALUE( mObject, InterpolationMode);

	// Get the OutputExtent value
	
	{
		if ( OutputExtent.getNum() >= 6)
		{
			SO_VTK_SET_6_FIELD_MFINT32( mObject, OutputExtent);
		}
		else
		{
			SoDebugError::post( __FILE__, "This field must have 6 values." );
		}
	}

	// Get the Border value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Border);

	// Get the AutoCropOutput value
	
		SO_VTK_SET_FIELD_VALUE( mObject, AutoCropOutput);

	// Get the Interpolate value
	
		SO_VTK_SET_FIELD_VALUE( mObject, Interpolate);

	// Get the TransformInputSampling value
	
		SO_VTK_SET_FIELD_VALUE( mObject, TransformInputSampling);

	mObject->Update();
}
