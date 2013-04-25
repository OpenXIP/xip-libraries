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

# include "SoVtkColorTransferFunction.h"
# include "SoVtkUtils.h"



SO_ENGINE_SOURCE( SoVtkColorTransferFunction )

SoVtkColorTransferFunction::SoVtkColorTransferFunction()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkColorTransferFunction);

	mObject = vtkColorTransferFunction::New();

	mObject->Register(0);mObject->SetGlobalWarningDisplay(0);

	vtkColorTransferFunction *aColorTransferFunction = vtkColorTransferFunction::New();
	double *x;
	int *y;

	SO_ENGINE_ADD_INPUT(RGBSegment, ());
	RGBSegment.setFormat("double double double double double double double double");

	SO_ENGINE_ADD_INPUT(HSVWrap, (0));
	HSVWrap.setValue(aColorTransferFunction->GetHSVWrap());

	SO_ENGINE_ADD_INPUT(VectorComponent, (0));
	VectorComponent.setValue(aColorTransferFunction->GetVectorComponent());

	SO_ENGINE_ADD_INPUT(ColorSpace, (0));
	ColorSpace.setValue(aColorTransferFunction->GetColorSpace());

	SO_ENGINE_ADD_INPUT(Clamping, (0));
	Clamping.setValue(aColorTransferFunction->GetClamping());

	SO_ENGINE_ADD_INPUT(HSVSegment, ());
	HSVSegment.setFormat("double double double double double double double double");

	SO_ENGINE_ADD_INPUT(RGBPoint, ());
	RGBPoint.setFormat("double double double double");

	SO_ENGINE_ADD_INPUT(HSVPoint, ());
	HSVPoint.setFormat("double double double double");

	SO_ENGINE_ADD_INPUT(VectorMode, (0));
	VectorMode.setValue(aColorTransferFunction->GetVectorMode());

	SO_ENGINE_ADD_INPUT(Alpha, (0));
	Alpha.setValue(aColorTransferFunction->GetAlpha());

	aColorTransferFunction->Delete();


	SO_ENGINE_ADD_OUTPUT(Output, SoSFVtkObject );
	mOutput = 0;

}

SoVtkColorTransferFunction::~SoVtkColorTransferFunction()
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

void SoVtkColorTransferFunction::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkColorTransferFunction, SoEngine, "Engine" );
}

void SoVtkColorTransferFunction::evaluate()
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


void SoVtkColorTransferFunction::inputChanged(SoField * f)
{
	// Get the RGBSegment value
	if ( f == &RGBSegment )
	{
		SbVariant *vRGBSegment = (SbVariant *)RGBSegment.getValues(0);
		SoInput input;
		int nb_fields = RGBSegment.getNum();

		double val0;
		double val1;
		double val2;
		double val3;
		double val4;
		double val5;
		double val6;
		double val7;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vRGBSegment[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			input.read(val2);
			input.read(val3);
			input.read(val4);
			input.read(val5);
			input.read(val6);
			input.read(val7);
			mObject->AddRGBSegment( 
				(double) val0,
				(double) val1,
				(double) val2,
				(double) val3,
				(double) val4,
				(double) val5,
				(double) val6,
				(double) val7
			);
		}
	}

	// Get the HSVWrap value
	if ( f == &HSVWrap )
		SO_VTK_SET_FIELD_VALUE( mObject, HSVWrap);

	// Get the VectorComponent value
	if ( f == &VectorComponent )
		SO_VTK_SET_FIELD_VALUE( mObject, VectorComponent);

	// Get the ColorSpace value
	if ( f == &ColorSpace )
		SO_VTK_SET_FIELD_VALUE( mObject, ColorSpace);

	// Get the Clamping value
	if ( f == &Clamping )
		SO_VTK_SET_FIELD_VALUE( mObject, Clamping);

	// Get the HSVSegment value
	if ( f == &HSVSegment )
	{
		SbVariant *vHSVSegment = (SbVariant *)HSVSegment.getValues(0);
		SoInput input;
		int nb_fields = HSVSegment.getNum();

		double val0;
		double val1;
		double val2;
		double val3;
		double val4;
		double val5;
		double val6;
		double val7;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vHSVSegment[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			input.read(val2);
			input.read(val3);
			input.read(val4);
			input.read(val5);
			input.read(val6);
			input.read(val7);
			mObject->AddHSVSegment( 
				(double) val0,
				(double) val1,
				(double) val2,
				(double) val3,
				(double) val4,
				(double) val5,
				(double) val6,
				(double) val7
			);
		}
	}

	// Get the RGBPoint value
	if ( f == &RGBPoint )
	{
		SbVariant *vRGBPoint = (SbVariant *)RGBPoint.getValues(0);
		SoInput input;
		int nb_fields = RGBPoint.getNum();

		double val0;
		double val1;
		double val2;
		double val3;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vRGBPoint[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			input.read(val2);
			input.read(val3);
			mObject->AddRGBPoint( 
				(double) val0,
				(double) val1,
				(double) val2,
				(double) val3
			);
		}
	}

	// Get the HSVPoint value
	if ( f == &HSVPoint )
	{
		SbVariant *vHSVPoint = (SbVariant *)HSVPoint.getValues(0);
		SoInput input;
		int nb_fields = HSVPoint.getNum();

		double val0;
		double val1;
		double val2;
		double val3;
		for (int i=0; i < nb_fields; i++)
		{
			input.setBuffer((void *)vHSVPoint[i].getField().getString(),256);
			input.read(val0);
			input.read(val1);
			input.read(val2);
			input.read(val3);
			mObject->AddHSVPoint( 
				(double) val0,
				(double) val1,
				(double) val2,
				(double) val3
			);
		}
	}

	// Get the VectorMode value
	if ( f == &VectorMode )
		SO_VTK_SET_FIELD_VALUE( mObject, VectorMode);

	// Get the Alpha value
	if ( f == &Alpha )
		SO_VTK_SET_FIELD_VALUE( mObject, Alpha);

	
}
