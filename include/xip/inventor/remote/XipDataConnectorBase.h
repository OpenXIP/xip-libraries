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

#ifndef RADDATACONNECTORBASE_H
#define RADDATACONNECTORBASE_H

//
// Copyright (c) 2003 - 2004 by Siemens Corporate Research, Inc.
// All Rights Reserved.
//
// No part of this software may be reproduced or transmitted in any
// form or by any means including photocopying or recording without
// written permission of the copyright owner.
//

#include <rad/common/RadTypes.h>
#include <rad/common/RadPluginBase.h>

class RadDataObjectBase;
class RadDataConnectorBase;


/** \class RadDataObjectNameListBase
 *	\brief Interface to access a list of object names.
 *
 *  An object inherited from this class is returned by RadDataConnectorBase::translateDragAndDrop.
 *	It provides methods to query the number of names in the list and each object name itself.
 * 
 */
class RadDataObjectNameListBase
{
public:
	/**
	 *	\brief Declaration of virtual destructor.
	 *
	 *	The reason for this declaration is purely to make the destructor for all
	 *	inherited classes virtual.
	 *
	 */
	virtual ~RadDataObjectNameListBase() {};

	/**
	 *	\brief Returns a given object name.
	 *
	 *	This method can be used to read a single object name providing it's index in the list.
	 *
	 *	\param	index	Specifies the index in the list ranging from 0 to RadDataObjectNameListBase::getSize() - 1.
	 *	\return	Constant pointer to object name. This pointer may not be freed by the caller
	 *			but is deleted by the destructor of this object.
	 *
	 */
	virtual const wchar_t* get(unsigned int index) const = 0;

	/**
	 *	\brief Returns the number of entries in the list.
	 *
	 *	Using this method the caller can determine how many object names have been returned
	 *	by RadDataConnectorBase::translateDragAndDrop.
	 *
	 *	\return	Number of object names in this list.
	 *
	 */
	virtual unsigned int getSize() const = 0;

	/**
	 *	\brief Returns a pointer to the data connector associated with the names in this list.
	 *
	 *	This method can be used to read a single object name providing it's index in the list.
	 *
	 *	\param	index	Specifies the index in the list ranging from 0 to RadDataObjectNameListBase::getSize() - 1.
	 *	\return	Constant pointer to object name. This pointer may not be freed by the caller
	 *			but is deleted by the destructor of this object.
	 *
	 */
	virtual const RadDataConnectorBase* getDataConnector() const = 0;
};


/** \class RadDataConnectorBase
 *	\brief Interface declaration for data plugins.
 *
 *  Data base access in the RAD framework is encapsulated into plugins for the different
 *	data sources. This abstract base class defines all public interfaces that must be
 *	supported by all data plugins. The most important method provided is the class factory
 *	method to create instances of type RadDataObjectBase, which are used to access a
 *	particular data object.
 * 
 */
class RadDataConnectorBase : public RadPluginBase
{
public:
	/**
	 *	\brief Data object class factory method.
	 *
	 *	This method is provided by all data plugins to create an instance of a data object.
	 *	Data objects can then be used like files to read the desired attributes.
	 *
	 *	\return Pointer to instance of object inherited from RadDataObjectBase. It is the
	 *			responsibility of the caller to delete this object when it is no longer
	 *			needed using the RadDataConnectorBase::deleteDataObject().
	 *
	 */
	virtual RadDataObjectBase* createDataObject() const = 0;

	/**
	 *	\brief Deletes a data object.
	 *
	 *	This method is provided by all data plugins to delete an instance of a data object
	 *	that has been created by a call to RadDataConnectorBase::createDataObject().
	 *
	 *	\param dataObject Pointer to instance of data object that will be deleted. The
	 *                    passed parameter will be reset to zero when the method returns.
	 *
	 */
	virtual void deleteDataObject(RadDataObjectBase *&dataObject) const = 0;

	/**
	 *	\brief Translation of drag & drop message to data object list.
	 *
	 *	This method is provided to translate a Windows drag & drop message into a list
	 *	of data object names. Those names can be used to open the object and read it's
	 *	attributes (see RadDataObjectBase::open).
	 *
	 *	\param	messageParam1	First parameter received through the drag & drop message.
	 *	\param	messageParam2	Second, optional parameter received through the drag & drop message.
	 *	\return A object of type RadDataObjectNameListBase that contains a list of all object names.
	 *			It is the responsibility of the caller to delete this object when it is no
	 *			longer needed.
	 *
	 */
	virtual const RadDataObjectNameListBase* translateDragAndDrop(unsigned int messageParam1, unsigned int messageParam2) = 0;

	/**
	 *	\brief Translation of the string to data object list.
	 *
	 *	This method is provided to translate a string into a list of data object names. Those names can be used to 
	 *  open the object and read it's attributes (see RadDataObjectBase::open). The contents of the string and their
	 *  interpretation depends on the given implementation. Please also refer the documentation for the required
	 *  plug-in implementations.
	 *
	 *	\param	param	String to be translated into data object list.
	 *	\return A object of type RadDataObjectNameListBase that contains a list of all object names.
	 *			It is the responsibility of the caller to delete this object when it is no
	 *			longer needed.
	 *
	 */
	virtual const RadDataObjectNameListBase * translateString(const wchar_t *param)= 0;

	/**
	 *	\brief Registers a window for drag & drop of objects supported by a plugin instance.
	 *
	 *	The application must use this method to register a window for drag & drop objects
	 *	that are known to the given instance of a data plugin.
	 *
	 *	\param	window	Window handle that will be enabled for drag & drop.
	 *
	 */
	virtual void registerDragAndDrop(RadWindowHandleType window) = 0;

	/**
	 *	\brief Unregisters a window from drag & drop of objects supported by a plugin instance.
	 *
	 *	Before a data plugin is unloaded any for drag and drop registered window should be
	 *	unregistered using this method.
	 *
	 *	\param	window	Window handle where drag & drop will be disabled.
	 *
	 */
	virtual void unregisterDragAndDrop(RadWindowHandleType window) = 0;

	/**
	 *	\brief Writes an extended parameter of the connector object.
	 *
	 *	Using this method the application can set extended parameters and configure the loaded plugin. 
	 *  The parameters that can be set through this interface depend on the data plugin implementation 
	 *  and are documented there.
	 *
	 *  \see RadDataIdentifiers.h for a list of supported extended parameter identifiers.
	 *
	 *	\param attribute	Generic attribute identifier.
	 *	\param type			Type of parameter passed through input buffer.
	 *	\param dimension	Dimension of attribute.
	 *	\param bufferSize	Size of the input buffer in bytes.
	 *	\param buffer		Pointer to buffer that contains parameter data.
	 *	 
	 */
	virtual void setParamEx(unsigned int param, RadIdentifiers::types type, unsigned int dimension, unsigned int bufferSize, const void* buffer) = 0;

	/**
	 *	\brief Reads an extended connector object parameter.
	 *
	 *	Using this method the application has access to extended connector parameters. 
	 *  The parameters that can be queried through this interface depend on the data plugin implementation 
	 *  and are documented there.
	 *
	 *  \see RadDataIdentifiers.h for a list of supported extended parameter identifiers.
	 *
	 *	\param attribute	Generic attribute identifier.
	 *	\param type			Type of parameter expected in output buffer.
	 *	\param dimension	Dimension of attribute.
	 *	\param bufferSize	Size of the output buffer in bytes.
	 *	\param buffer		Pointer to buffer that receives queried parameter data. If NULL is
	 *						passed for this parameter the method will return the required
	 *						buffer size to read this attribute.
	 *  \return	The method returns the number of bytes written into the output buffer or the
	 *			required buffer size in bytes for this attribute if buffer parameter is NULL.
	 *
	 */
	virtual unsigned int getParamEx(unsigned int param, RadIdentifiers::types type, unsigned int dimension, unsigned int bufferSize, void* buffer) = 0;

};


#endif
