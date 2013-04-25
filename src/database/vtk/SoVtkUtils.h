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

#ifndef SO_VTK_UTILS_H_
 #define SO_VTK_UTILS_H_


// Define used to set values for SFBool, SFInt32, SFShort, SFLong, SFFloat, SFUInt32, SFUShort, SFULong
#define SO_VTK_SET_FIELD_VALUE(object,field)\
{\
	object->Set##field(field.getValue());\
}

#define SO_VTK_ADD_FIELD_VALUE(object,field)\
{\
	object->Add##field(field.getValue());\
}

// Define used for two value fields
#define SO_VTK_SET_FIELD_VEC2F(object,field)\
{\
	SbVec2f __tmp_ = field.getValue();\
	object->Set##field(__tmp_[0], __tmp_[1]);\
}

#define SO_VTK_SET_FIELD_VEC2S(object,field)\
{\
	SbVec2s __tmp_ = field.getValue();\
	object->Set##field(__tmp_[0], __tmp_[1]);\
}

#define SO_VTK_ADD_FIELD_VEC2F(object,field)\
{\
	SbVec2f __tmp_ = field.getValue();\
	object->Add##field(__tmp_[0], __tmp_[1]);\
}

#define SO_VTK_ADD_FIELD_VEC2S(object,field)\
{\
	SbVec2s __tmp_ = field.getValue();\
	object->Add##field(__tmp_[0], __tmp_[1]);\
}

// Define used for three value fields
#define SO_VTK_SET_FIELD_VEC3F(object,field)\
{\
	SbVec3f __tmp_ = field.getValue();\
	object->Set##field(__tmp_[0], __tmp_[1], __tmp_[2]);\
}

#define SO_VTK_SET_FIELD_VEC3S(object,field)\
{\
	SbVec3s __tmp_ = field.getValue();\
	object->Set##field(__tmp_[0], __tmp_[1], __tmp_[2]);\
}

#define SO_VTK_ADD_FIELD_VEC3F(object,field)\
{\
	SbVec3f __tmp_ = field.getValue();\
	object->Add##field(__tmp_[0], __tmp_[1], __tmp_[2]);\
}

#define SO_VTK_ADD_FIELD_VEC3S(object,field)\
{\
	SbVec3s __tmp_ = field.getValue();\
	object->Add##field(__tmp_[0], __tmp_[1], __tmp_[2]);\
}

#define SO_VTK_SET_FIELD_VEC3F_NO_SET(object,field)\
{\
	SbVec3f __tmp_ = field.getValue();\
	object->field(__tmp_[0], __tmp_[1], __tmp_[2]);\
}

// Define used for four value fields
#define SO_VTK_SET_FIELD_VEC4F(object,field)\
{\
	SbVec4f __tmp_ = field.getValue();\
	object->Set##field(__tmp_[0], __tmp_[1], __tmp_[2], __tmp_[3]);\
}

#define SO_VTK_ADD_FIELD_VEC4F(object,field)\
{\
	SbVec4f __tmp_ = field.getValue();\
	object->Add##field(__tmp_[0], __tmp_[1], __tmp_[2], __tmp_[3]);\
}

// Defines used for multiple value fields
# define SO_VTK_SET_FIELD_MFBOOL(object,field) \
{\
	bool *__val_ = (bool*)field.getValues(0);\
	object->Set##field( __val_);\
}

# define SO_VTK_ADD_FIELD_MFBOOL(object,field) \
{\
	bool *__val_ = (bool*)field.getValues(0);\
	object->Add##field( __val_);\
}

# define SO_VTK_SET_FIELD_MFINT32(object,field) \
{\
	int *__val_ = (int *)field.getValues(0);\
	object->Set##field(__val_);\
}

# define SO_VTK_SET_6_FIELD_MFINT32(object,field) \
{\
	int *__val_ = (int *)field.getValues(0);\
	object->Set##field(__val_[0],__val_[1],__val_[2],__val_[3],__val_[4],__val_[5]);\
}

# define SO_VTK_ADD_FIELD_MFINT32(object,field) \
{\
	int *__val_ = (int *)field.getValues(0);\
	object->Add##field(__val_);\
}

# define SO_VTK_SET_FIELD_MFFLOAT(object,field) \
{\
	float *__val_ = (float*)field.getValues(0);\
	object->Set##field( __val_);\
}

# define SO_VTK_ADD_FIELD_MFFLOAT(object,field) \
{\
	float *__val_ = (float*)field.getValues(0);\
	object->Add##field( __val_);\
}

# define SO_VTK_SET_FIELD_MFDOUBLE(object,field) \
{\
	double *__val_ = (double*)field.getValues(0);\
	object->Set##field( __val_);\
}

# define SO_VTK_SET_6_FIELD_MFDOUBLE(object,field) \
{\
	double *__val_ = (double*)field.getValues(0);\
	object->Set##field( __val_[0],__val_[1],__val_[2],__val_[3],__val_[4],__val_[5]);\
}

# define SO_VTK_ADD_FIELD_MFDOUBLE(object,field) \
{\
	double *__val_ = (double*)field.getValues(0);\
	object->Add##field( __val_);\
}

# define SO_VTK_ADD_8_FIELD_MFDOUBLE(object,field) \
{\
	double *__val_ = (double*)field.getValues(0);\
	object->Add##field( __val_[0],__val_[1],__val_[2],__val_[3],__val_[4],__val_[5],__val_[6],__val_[7]);\
}

# define SO_VTK_SET_FIELD_MFSHORT(object,field) \
{\
	short *__val_ = (short*)field.getValues(0);\
	object->Set##field( __val_);\
}

# define SO_VTK_ADD_FIELD_MFSHORT(object,field) \
{\
	short *__val_ = (short*)field.getValues(0);\
	object->Add##field( __val_);\
}

# define SO_VTK_SET_FIELD_MFLONG(object,field) \
{\
	long *__val_ = (long*)field.getValues(0);\
	object->Set##field( __val_);\
}

# define SO_VTK_ADD_FIELD_MFLONG(object,field) \
{\
	long *__val_ = (long*)field.getValues(0);\
	object->Add##field( __val_);\
}

# define SO_VTK_SET_FIELD_MFUSHORT(object,field) \
{\
	unsigned short *__val_ = (unsigned short*)field.getValues(0);\
	object->Set##field( __val_);\
}

# define SO_VTK_ADD_FIELD_MFUSHORT(object,field) \
{\
	unsigned short *__val_ = (unsigned short*)field.getValues(0);\
	object->Add##field( __val_);\
}

# define SO_VTK_SET_FIELD_MFULONG(object,field) \
{\
	unsigned long *__val_ = (unsigned long*)field.getValues(0);\
	object->Set##field( __val_);\
}

# define SO_VTK_ADD_FIELD_MFULONG(object,field) \
{\
	unsigned long *__val_ = (unsigned long*)field.getValues(0);\
	object->Add##field( __val_);\
}

# define SO_VTK_SET_FIELD_MFUINT32(object,field) \
{\
	unsigned int *__val_ = (unsigned int *)field.getValues(0);\
	object->Set##field(__val_);\
}

# define SO_VTK_ADD_FIELD_MFUINT32(object,field) \
{\
	unsigned int *__val_ = (unsigned int *)field.getValues(0);\
	object->Add##field(__val_);\
}

#define SO_VTK_SET_FIELD_SFSTRING(object,field)\
{\
	char *__val_ = (char *)field.getValue().getString();\
	object->Set##field( __val_ );\
}

#define SO_VTK_SET_FIELD_MFSTRING(object,field)\
{\
	const char *__val_ = (const char *)field.getValues(0)->getString();\
	object->Set##field(__val_);\
}

#define SO_VTK_ADD_FIELD_MFSTRING(object,field)\
{\
	const char *__val_ = field.getValues(0)->getString();\
	object->Add##field((char*) __val_);\
}

# define QUOTE(str) #str

# define SO_VTK_SET_FIELD_DATA(object,field,type) \
{\
	SoVtkObject *__obj_ = field.getValue();\
	if (__obj_)\
	{\
		if ( __obj_->getPointer()->IsA(QUOTE(type)))\
		{\
		object->Set##field(type::SafeDownCast(__obj_->getPointer()));\
		}\
	}\
}

/**
 * This function will connect the given itk::VTKImageExport filter to
 * the given vtkImageImport filter.
 */
template <typename ITK_Exporter, typename VTK_Importer>
void ConnectPipelines(ITK_Exporter exporter, VTK_Importer* importer)
{
  importer->SetUpdateInformationCallback(exporter->GetUpdateInformationCallback());
  importer->SetPipelineModifiedCallback(exporter->GetPipelineModifiedCallback());
  importer->SetWholeExtentCallback(exporter->GetWholeExtentCallback());
  importer->SetSpacingCallback(exporter->GetSpacingCallback());
  importer->SetOriginCallback(exporter->GetOriginCallback());
  importer->SetScalarTypeCallback(exporter->GetScalarTypeCallback());
  importer->SetNumberOfComponentsCallback(exporter->GetNumberOfComponentsCallback());
  importer->SetPropagateUpdateExtentCallback(exporter->GetPropagateUpdateExtentCallback());
  importer->SetUpdateDataCallback(exporter->GetUpdateDataCallback());
  importer->SetDataExtentCallback(exporter->GetDataExtentCallback());
  importer->SetBufferPointerCallback(exporter->GetBufferPointerCallback());
  importer->SetCallbackUserData(exporter->GetCallbackUserData());
}

/**
 * This function will connect the given vtkImageExport filter to
 * the given itk::VTKImageImport filter.
 */
template <typename VTK_Exporter, typename ITK_Importer>
void ConnectPipelines(VTK_Exporter* exporter, ITK_Importer importer)
{
  importer->SetUpdateInformationCallback(exporter->GetUpdateInformationCallback());
  importer->SetPipelineModifiedCallback(exporter->GetPipelineModifiedCallback());
  importer->SetWholeExtentCallback(exporter->GetWholeExtentCallback());
  importer->SetSpacingCallback(exporter->GetSpacingCallback());
  importer->SetOriginCallback(exporter->GetOriginCallback());
  importer->SetScalarTypeCallback(exporter->GetScalarTypeCallback());
  importer->SetNumberOfComponentsCallback(exporter->GetNumberOfComponentsCallback());
  importer->SetPropagateUpdateExtentCallback(exporter->GetPropagateUpdateExtentCallback());
  importer->SetUpdateDataCallback(exporter->GetUpdateDataCallback());
  importer->SetDataExtentCallback(exporter->GetDataExtentCallback());
  importer->SetBufferPointerCallback(exporter->GetBufferPointerCallback());
  importer->SetCallbackUserData(exporter->GetCallbackUserData());
}



#endif //SO_VTK_UTILS_H_
