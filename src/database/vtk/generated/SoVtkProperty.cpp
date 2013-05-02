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

# include "SoVtkProperty.h"
# include "SoVtkUtils.h"



SO_ENGINE_SOURCE( SoVtkProperty )

SoVtkProperty::SoVtkProperty()
{
	SO_ENGINE_CONSTRUCTOR(SoVtkProperty);

	mObject = vtkProperty::New();

	mObject->Register(0);mObject->SetGlobalWarningDisplay(0);

	vtkProperty *aProperty = vtkProperty::New();
	double *x;

	SO_ENGINE_ADD_INPUT(Representation, (0));
	Representation.setValue(aProperty->GetRepresentation());

	SO_ENGINE_ADD_INPUT(Diffuse, (0));
	Diffuse.setValue(aProperty->GetDiffuse());

	SO_ENGINE_ADD_INPUT(AmbientColor, (0,0,0));

	x= aProperty->GetAmbientColor();
	AmbientColor.setValue(x[0],x[1],x[2]);

	SO_ENGINE_ADD_INPUT(Color, ());
	Color.setFormat("double double double");

	SO_ENGINE_ADD_INPUT(FrontfaceCulling, (0));
	FrontfaceCulling.setValue(aProperty->GetFrontfaceCulling());

	SO_ENGINE_ADD_INPUT(BackfaceCulling, (0));
	BackfaceCulling.setValue(aProperty->GetBackfaceCulling());

	SO_ENGINE_ADD_INPUT(EdgeVisibility, (0));
	EdgeVisibility.setValue(aProperty->GetEdgeVisibility());

	SO_ENGINE_ADD_INPUT(Opacity, (0));
	Opacity.setValue(aProperty->GetOpacity());

	SO_ENGINE_ADD_INPUT(DiffuseColor, (0,0,0));

	x= aProperty->GetDiffuseColor();
	DiffuseColor.setValue(x[0],x[1],x[2]);

	SO_ENGINE_ADD_INPUT(Interpolation, (0));
	Interpolation.setValue(aProperty->GetInterpolation());

	SO_ENGINE_ADD_INPUT(Ambient, (0));
	Ambient.setValue(aProperty->GetAmbient());

	SO_ENGINE_ADD_INPUT(LineWidth, (0));
	LineWidth.setValue(aProperty->GetLineWidth());

	SO_ENGINE_ADD_INPUT(LineStipplePattern, (0));
	LineStipplePattern.setValue(aProperty->GetLineStipplePattern());

	SO_ENGINE_ADD_INPUT(Specular, (0));
	Specular.setValue(aProperty->GetSpecular());

	SO_ENGINE_ADD_INPUT(SpecularColor, (0,0,0));

	x= aProperty->GetSpecularColor();
	SpecularColor.setValue(x[0],x[1],x[2]);

	SO_ENGINE_ADD_INPUT(LineStippleRepeatFactor, (0));
	LineStippleRepeatFactor.setValue(aProperty->GetLineStippleRepeatFactor());

	SO_ENGINE_ADD_INPUT(SpecularPower, (0));
	SpecularPower.setValue(aProperty->GetSpecularPower());

	SO_ENGINE_ADD_INPUT(EdgeColor, (0,0,0));

	x= aProperty->GetEdgeColor();
	EdgeColor.setValue(x[0],x[1],x[2]);

	SO_ENGINE_ADD_INPUT(PointSize, (0));
	PointSize.setValue(aProperty->GetPointSize());

	aProperty->Delete();


	SO_ENGINE_ADD_OUTPUT(Output, SoSFVtkObject );
	mOutput = 0;

}

SoVtkProperty::~SoVtkProperty()
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

void SoVtkProperty::initClass()
{
	SO_ENGINE_INIT_CLASS( SoVtkProperty, SoEngine, "Engine" );
}

void SoVtkProperty::evaluate()
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


void SoVtkProperty::inputChanged(SoField * f)
{
	// Get the Representation value
	if ( f == &Representation )
		SO_VTK_SET_FIELD_VALUE( mObject, Representation);

	// Get the Diffuse value
	if ( f == &Diffuse )
		SO_VTK_SET_FIELD_VALUE( mObject, Diffuse);

	// Get the AmbientColor value
	if ( f == &AmbientColor )
		SO_VTK_SET_FIELD_VEC3F( mObject, AmbientColor);

	// Get the Color value
	if ( f == &Color )
	{
		SbVariant vColor = (SbVariant)Color.getValue();
		SoInput input;
		double val0;
		double val1;
		double val2;
	
		input.setBuffer((void *)vColor.getField().getString(),256);
		input.read(val0);
		input.read(val1);
		input.read(val2);
		mObject->SetColor( 
			(double) val0,
			(double) val1,
			(double) val2
		);
	}
	// Get the FrontfaceCulling value
	if ( f == &FrontfaceCulling )
		SO_VTK_SET_FIELD_VALUE( mObject, FrontfaceCulling);

	// Get the BackfaceCulling value
	if ( f == &BackfaceCulling )
		SO_VTK_SET_FIELD_VALUE( mObject, BackfaceCulling);

	// Get the EdgeVisibility value
	if ( f == &EdgeVisibility )
		SO_VTK_SET_FIELD_VALUE( mObject, EdgeVisibility);

	// Get the Opacity value
	if ( f == &Opacity )
		SO_VTK_SET_FIELD_VALUE( mObject, Opacity);

	// Get the DiffuseColor value
	if ( f == &DiffuseColor )
		SO_VTK_SET_FIELD_VEC3F( mObject, DiffuseColor);

	// Get the Interpolation value
	if ( f == &Interpolation )
		SO_VTK_SET_FIELD_VALUE( mObject, Interpolation);

	// Get the Ambient value
	if ( f == &Ambient )
		SO_VTK_SET_FIELD_VALUE( mObject, Ambient);

	// Get the LineWidth value
	if ( f == &LineWidth )
		SO_VTK_SET_FIELD_VALUE( mObject, LineWidth);

	// Get the LineStipplePattern value
	if ( f == &LineStipplePattern )
		SO_VTK_SET_FIELD_VALUE( mObject, LineStipplePattern);

	// Get the Specular value
	if ( f == &Specular )
		SO_VTK_SET_FIELD_VALUE( mObject, Specular);

	// Get the SpecularColor value
	if ( f == &SpecularColor )
		SO_VTK_SET_FIELD_VEC3F( mObject, SpecularColor);

	// Get the LineStippleRepeatFactor value
	if ( f == &LineStippleRepeatFactor )
		SO_VTK_SET_FIELD_VALUE( mObject, LineStippleRepeatFactor);

	// Get the SpecularPower value
	if ( f == &SpecularPower )
		SO_VTK_SET_FIELD_VALUE( mObject, SpecularPower);

	// Get the EdgeColor value
	if ( f == &EdgeColor )
		SO_VTK_SET_FIELD_VEC3F( mObject, EdgeColor);

	// Get the PointSize value
	if ( f == &PointSize )
		SO_VTK_SET_FIELD_VALUE( mObject, PointSize);

	
}

