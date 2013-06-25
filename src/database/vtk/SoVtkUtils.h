/*
Copyright (c) 2011, Siemens Corporate Research a Division of Siemens Corporation 
All rights reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
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
