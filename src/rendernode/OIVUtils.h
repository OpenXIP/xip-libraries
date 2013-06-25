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
#ifndef OIVUTILS_H
#define OIVUTILS_H

#include <Inventor/SbString.h>

class SoNode*
createNode( const SbString& className );

class SoEngine*
createEngine( const SbString& className );

#define THROW_CREATE_NODE(Node, ClassName, NodeName )									\
	if(!(Node = (SoNode *) createNode( #ClassName )))									\
	{																					\
		throw RadException(__LINE__, __FILE__, RadException::MEMORY_HEAP_ERROR,			\
			L"Could not create " L#NodeName);											\
	}

#define THROW_CREATE_ENGINE(Engine, ClassName, EngineName )								\
	if(!(Engine = (SoEngine *) createEngine( #ClassName )))								\
	{																					\
		throw RadException(__LINE__, __FILE__, RadException::MEMORY_HEAP_ERROR,			\
			L"Could not create " L#EngineName);											\
	}

#define THROW_GET_FIELD(Field, Node, FieldName, FieldType )								\
	{																					\
		Field = (FieldType *) Node->getField(FieldName);								\
		if( !Field )																	\
		{																				\
			throw RadException(__LINE__, __FILE__, RadException::INVALID_PARAM_ERROR,	\
				L"Cannot find field '" L#FieldName L"'");								\
		}																				\
		if( !Field->isOfType( FieldType::getClassTypeId() ) )							\
		{																				\
			throw RadException(__LINE__, __FILE__, RadException::INVALID_PARAM_ERROR,	\
				L"Field '" L#FieldName L"' is not of type '" L#FieldType L"'");			\
		}																				\
	}

#define THROW_GET_ENGINE_OUTPUT(Output, Engine, OutputName)								\
	{																					\
		Output = Engine->getOutput(OutputName);											\
		if( !Output )																	\
		{																				\
			throw RadException(__LINE__, __FILE__, RadException::INVALID_PARAM_ERROR,	\
				L"Cannot find output '" L#OutputName L"'");								\
		}																				\
	}

#define THROW_CALL_FIELD(Node, FieldName, FieldType, Method )							\
	{																					\
		FieldType* field;																\
		THROW_GET_FIELD( field, Node, FieldName, FieldType );							\
		field->Method;																	\
	}

#define THROW_GET_NODE(Node, NodeName)													\
	{																					\
		if( !(Node = SoNode::getByName( NodeName )) )									\
		{																				\
			throw RadException(__LINE__, __FILE__, RadException::INVALID_PARAM_ERROR,	\
				L"'" L#NodeName L"' was not found");									\
		}																				\
	}

#define THROW_GET_ENGINE(Engine, EngineName)											\
	{																					\
	if( !(Engine = SoEngine::getByName( EngineName )) )									\
		{																				\
			throw Exception(__LINE__, __FILE__, RadException::INVALID_PARAM_ERROR,	\
				L"'" L#EngineName L"' was not found");									\
		}																				\
	}

#endif // RADINVENTORUTILS_H