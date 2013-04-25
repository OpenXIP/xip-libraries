#ifndef XIP_DATAOBJECTBASE_H
#define XIP_DATAOBJECTBASE_H

//
// Copyright (c) 2003 - 2004 by Siemens Corporate Research, Inc.
// All Rights Reserved.
//
// No part of this software may be reproduced or transmitted in any
// form or by any means including photocopying or recording without
// written permission of the copyright owner.
//

#include <xip/common/XipTypes.h>


/** \class RadDataObjectBase
 *	\brief Interface for data objects like images.
 *
 *  This abstract base class represents a data object in the RAD framework. Using 
 *  this interface class applications can access image attributes and pixel data.
 *  DICOM group and element IDs are used to identify any given attribute.
 *
 *	Instances of from RadDataObjectBase inherited objects should be created by
 *	calling the class factory RadDataConnectorBase::createDataObject. Data object
 *	interfaces are then used like files. They can be opened, read and need to be
 *	closed after the transfer is completed.
 * 
 *	\b Example:
	\code
	 
	// This example demonstrates reading the image position and the pixel data from
	// a data object. First, a data plugin is created. Then, a data object is instantiated
	// and opened to read the attributes. At last, tbe objects are freed.

	RadPluginBase *ptr = NULL;
	RadDataObjectBase *dobject = NULL;
	HMODULE module = 0;

	// load plugin
	ptr = RadPluginLoader::load(L"raddataoffisdcm", module);

	// create and open data object (2346936 is a DICOM file name)
	dobject = ((RadDataConnectorBase*) ptr)->createDataObject();
	dobject->open(L"2346936");

	// read image position
	double imagePositionPatient[3];
	dobject->getElement(
		RAD_IMAGE_POSITIONPATIENT_DICOMGROUP,
		RAD_IMAGE_POSITIONPATIENT_DICOMELEMENT,
		RadDataObjectBase::FLT64,
		3,
		sizeof(imagePositionPatient),
		imagePositionPatient);

  	// read pixel data (assumes 512 * 512 dimensions, 16 bit)
	unsigned short buffer[512 * 512];
	dobject->getElement(
		RAD_IMAGE_PIXEL_DATA_DICOMGROUP,
		RAD_IMAGE_PIXEL_DATA_DICOMELEMENT,
		RadDataObjectBase::UINT16,
		512 * 512,
		512 * 512 * sizeof(unsigned short),
		buffer);

	// close and delete data object
	dobject->close();
	((RadDataConnectorBase*) ptr)->deleteDataObject(dobject);

	// unload plugin
	RadPluginLoader::unload(module, ptr);
	\endcode
 */
class RadDataObjectBase
{
public:

	/**
	 *	\brief Enumeration for different supported return types of RadDataObjectBase::getElement method.
	 *
	 *	One of these types must be specified when reading elements from a data object
	 *	using the RadDataObjectBase::getElement method. It defines the value returned
	 *	by RadDataObjectBase::getElement, which is not necessarily the native format in
	 *	which it is stored in the data source.
	 *
	 */
	enum ElementType
	{ 
		/// 8-bit unsigned integer.
		UINT8 = RadIdentifiers::UINT8,
		/// 8-bit signed integer.
		SINT8 = RadIdentifiers::SINT8,
		/// 16-bit unsigned integer.
		UINT16 = RadIdentifiers::UINT16,
		/// 16-bit signed integer.
		SINT16 = RadIdentifiers::SINT16,
		/// 32-bit unsigned integer.
		UINT32 = RadIdentifiers::UINT32,
		/// 32-bit signed integer.
		SINT32 = RadIdentifiers::SINT32,
		/// 32-bit floating point.
		UINT64 = RadIdentifiers::UINT64,
		/// 64-bit unsigend integer (for extended attributes only).
		FLT32 = RadIdentifiers::FLT32,
		/// 64-bit floating point.
		FLT64 = RadIdentifiers::FLT64,
		/// Boolean (32-bit).
		STRING = RadIdentifiers::STRING,
		/// Dicom Long String
		LO	   = RadIdentifiers::LO,
		/// Dicom Code String
		CS	   = RadIdentifiers::CS,
		/// Dicom Integer String
		IS	   = RadIdentifiers::IS,
		/// Custom object pointer.
		POINTER,
		/// Reserved for undefined or unknown types.
		UNDEFINED
	};

public:
	/**
	 *	\brief Declaration of virtual destructor.
	 *
	 *	The reason for this declaration is purely to make the destructor for all
	 *	inherited classes virtual.
	 *
	 */
	virtual ~RadDataObjectBase() {};

	/**
	 *	\brief Opens a data object.
	 *
	 *	Before any attributes can be queried from a data object it must be opened.
	 *	Any previously opened data object of this instance is being closed before
	 *	when calling this method (see also RadDataObjectBase::close()).
	 *
	 *  \param objectName String that identifies object to be opened. The value of
	 *                    this parameter depends on the data plugin used. In the case
	 *                    of the DCMTK data plugin for example, it is the path of a
	 *                    DICOM file.
	 *	\param option     Optional parameter specifying special instructions for opening
	 *                    a data object (currently not used).
	 *
	 */
	virtual void open(const wchar_t * objectName, unsigned int option = 0) = 0;
	
	/**
	 *	\brief Closes a data object.
	 *
	 *	Closing a data object frees all allocated memory associated with this object.
	 *	Previously requested pointers to any buffer become invalid at this point.
	 *
	 */
	virtual void close() = 0;

	/**
	 *	\brief Checks if an object is opened.
	 *
	 *	Returns the status (open/close) of this instance (see also RadDataObjectBase::open()).
	 *
	 *	\return	Returns true if a data object has been opened, otherwise false.
	 *
	 */
	virtual bool isOpen() const = 0;

	/**
	 *	\brief Reads a data object attribute.
	 *
	 *	The attribute to be read is specified by its DICOM group and element number.
	 *	Furthermore, the requested attribute type, the dimension (e.g. vector [3]) as
	 *	well as a buffer to receive the data needs to be specified when calling this method.
	 *
	 *	\param group		DICOM group identifier of the queried attribute.
	 *	\param element		DICOM element identifier of the queried attribute.
	 *	\param type			Type of elements to be written into output buffer.
	 *	\param dimension	Dimension of attribute (e.g. vector of 3 for image position patient).
	 *	\param bufferSize	Size of the output buffer in bytes.
	 *	\param buffer		Pointer to buffer that receives queried attribute data. If NULL is
	 *						passed for this parameter the method will return the required
	 *						buffer size to read this attribute.
	 *  \return	The method returns the number of bytes written into the output buffer or the
	 *			required buffer size in bytes for this attribute if buffer parameter is NULL.
	 *
	 *	\b Example:
	\code
	 
	// read the patient's image position
	// (dataObject assumed to be created and opened)
	double imagePositionPatient[3];
	dataObject->getElement(
		RAD_IMAGEPOSITION_GROUP,
		RAD_IMAGEPOSITION_ELEMENT,
		RadDataObjectBase::FLT64,
		3,
		sizeof(imagePositionPatient),
		imagePositionPatient);

	\endcode
	 */
	virtual unsigned int getElement(RadDICOMGroupType group, RadDICOMElementType element, ElementType type, unsigned int dimension, unsigned int bufferSize, void *buffer) = 0;

	/**
	 *	\brief Query for element properties.
	 *
	 *  The application can use this method to query certain properties, for example the
	 *  dimension, of any element. Also this query allows testing if an element exists in the
	 *  data object.
	 *
	 *  \see RadDataIdentifiers.h for a list of supported identifiers.
	 *
	 *	\param group		DICOM group identifier of the queried attribute.
	 *	\param element		DICOM element identifier of the queried attribute.
	 *	\param property		Type of element property to be queried (see description above).
	 *  \return	The method's return value depends on the property parameter.
	 *
	 *	\b Example:
	 *\code

	// query the object for existance of patient's image position
	// (dataObject assumed to be created and opened)
	if ( dataObject->getElementProperty( RAD_IMAGEPOSITION_GROUP, RAD_IMAGEPOSITION_ELEMENT, RAD_DATA_PROP_EXISTS )
	{
		//image position attribute exists.
	}
	\endcode
	 */
	virtual unsigned int getElementProperty(RadDICOMGroupType group, RadDICOMElementType element, unsigned int property) = 0;

	/**
	 *	\brief Writes a data object attribute.
	 *
	 *	The attribute to be set is specified by its DICOM group and element number.
	 *	Furthermore, the requested attribute type, the dimension (e.g. vector [3]) as
	 *	well as the buffer providing the data needs to be specified when calling this method.
	 *
	 *	\param group		DICOM group identifier of the attribute to be modified.
	 *	\param element		DICOM element identifier of the attribute to be modified.
	 *	\param type			Type of elements passed through input buffer.
	 *	\param dimension	Dimension of attribute (e.g. vector of 3 for image position patient).
	 *	\param bufferSize	Size of the input buffer in bytes.
	 *	\param buffer		Pointer to buffer that contains attribute data.
	 *
	 *	\b Example:
	\code
	 
	// sets the patient's image position
	// (dataObject assumed to be created and opened)
	double imagePositionPatient[3] = { 1.0, 1.0, 1.0 };
	dataObject->setElement(
		RAD_IMAGEPOSITION_GROUP,
		RAD_IMAGEPOSITION_ELEMENT,
		RadDataObjectBase::FLT64,
		3,
		sizeof(imagePositionPatient),
		imagePositionPatient);

	\endcode
	 */
	virtual void setElement(RadDICOMGroupType group, RadDICOMElementType element, ElementType type, unsigned int dimension, unsigned int bufferSize, const void *buffer) = 0;

	/**
	 *	\brief Reads an extended data object attribute.
	 *
	 *	Using this method the application has access to extended attributes and parameters that
	 *	are not necessarily covered by the DICOM standard. The attributes that can be queried
	 *	through this interface depend on the data plugin implementation and are documented
	 *	there.
	 *
	 *  \see RadDataIdentifiers.h for a list of supported extended attribute identifiers.
	 *
	 *	\param attribute	Generic attribute identifier.
	 *	\param type			Type of elements expected in output buffer.
	 *	\param dimension	Dimension of attribute.
	 *	\param bufferSize	Size of the output buffer in bytes.
	 *	\param buffer		Pointer to buffer that receives queried attribute data. If NULL is
	 *						passed for this parameter the method will return the required
	 *						buffer size to read this attribute.
	 *  \return	The method returns the number of bytes written into the output buffer or the
	 *			required buffer size in bytes for this attribute if buffer parameter is NULL.
	 *
	 *	\b Example:
	\code
	 
	// retrieves a sharename identifier that can be
	// used to create a shared memory object
	wchar_t sharename[200]; 
	dataObject->getElementEx(
		RAD_DATA_EX_SHARENAME,
		RadDataObjectBase::STRING,
		1,
		sizeof(sharename),
		sharename);

	\endcode
	 */
	virtual unsigned int getElementEx(unsigned int attibute, ElementType type, unsigned int dimension, unsigned int bufferSize, void* buffer) = 0;

	/**
	 *	\brief Writes an extended data object attribute.
	 *
	 *	Using this method the application can set extended attributes and parameters that
	 *	are not necessarily covered by the DICOM standard. The attributes that can be set
	 *	through this interface depend on the data plugin implementation and are documented
	 *	there.
	 *
	 *  \see RadDataIdentifiers.h for a list of supported extended attribute identifiers.
	 *
	 *	\param attribute	Generic attribute identifier.
	 *	\param type			Type of elements passed through input buffer.
	 *	\param dimension	Dimension of attribute.
	 *	\param bufferSize	Size of the input buffer in bytes.
	 *	\param buffer		Pointer to buffer that contains attribute data.
	 *	 
	 *	\b Example:
	\code
	 
	// sets the sharename identifier that can be used to create a shared memory object
	wchar_t sharename[MAX_PATH]; 
	wsprintf(sharename,
			 L"%s",
			 L"rad_frame_sopInstanceUid_share" );

	dataObject->setElementEx(	RAD_DATA_EX_SHARENAME, 
								RadDataObjectBase::STRING,
								1,
								sizeof(sharename),
								sharename);

	\endcode
	 */
	virtual void setElementEx(unsigned int attribute, ElementType type, unsigned int dimension, unsigned int bufferSize, const void* buffer) = 0;

	/**
	 *	\brief Creates a compatible data object.
	 *
	 *	Given any existing data object this method initializes another data object to be
	 *	compatible with the input object. For this purpose all meta data information like
	 *	patient name, image attributes etc. are copied into the new object. However, the
	 *	pixel data is by default not considered for this operation. The application might
	 *	include the pixel data by specifying the option RAD_DATA_OPT_INCL_PIXELDATA.
	 *
	 *	The default location and storage type for the newly created object depends on the
	 *	data plugin being used. Extended attributes (see RadDataObjectBase::setElementEx())
	 *	might be used to change the default behaviour.
	 *
	 *	\param object	A data object instance that is compatible to the data object specified
	 *					through this parameter will be created.
	 *	\param option	Using this parameter the default behaviour for the operation can be
	 *					altered.
	 *					- RAD_DATA_OPT_INCL_PIXELDATA: Include pixel data.
	 *  \return	This method returns the object name of the newly created instance. The
	 *			returned pointer is valid until the object is closed and may not be modified.
	 *
	 *	\b Example:
	\code
	 
	// create a compatible data object using a reference object
	// (assumes data plugin is loaded in ptr and referenceFrame is created and open)
	const wchar_t* objectName = 0;

	// copies the object attributes from referenceFrame to compatibleObject, excluding
	// pixel data
	RadDataObjectBase *compatibleObject = ((RadDataConnectorBase*) ptr)->createDataObject();
	objectName = compatibleObject->createCompatible(referenceFrame);

	// set pixel data for new object (assume pixelData is filled and dimension is 512x512)
	dobject->setElement(
		RAD_IMAGE_PIXEL_DATA_DICOMGROUP,
		RAD_IMAGE_PIXEL_DATA_DICOMELEMENT,
		RadDataObjectBase::UINT16,
		512 * 512,
		512 * 512 * sizeof(unsigned short),
		pixelData);

	// sync changes and close object
	compatibleObject->sync();
	compatibleObject->close();

	\endcode
	 */
	virtual const wchar_t* createCompatible(const RadDataObjectBase* object, unsigned int option = 0) = 0;

	/**
	 *	\brief Synchronizes changes of a data object with data storage.
	 *
	 *	This method ensures changes to a data object are comitted to a data base or written
	 *	to disk. However, depending on the data plugin being used changes might be stored
	 *	permanently already as soon attributes are set. 
	 *
	 *	\param option	Optional flag for operation (currently not used).
	 *
	 *	\b Example:
	\code
	 
	// sets the patient's image position
	// (dataObject assumed to be created and opened)
	double imagePositionPatient[3] = { 1.0, 1.0, 1.0 };
	dataObject->setElement(
		RAD_IMAGEPOSITION_GROUP,
		RAD_IMAGEPOSITION_ELEMENT,
		RadDataObjectBase::FLT64,
		3,
		sizeof(imagePositionPatient),
		imagePositionPatient);

	//this call commits the above values into the dicom file / database object contained by the dataObject.
	dataObject->sync();

	\endcode
	 */
	virtual void sync(unsigned int option = 0) = 0;

	/**
	 *	\brief Serialization method.
	 *
	 *	Using this method a data object can be stored into a sequential buffer. By default
	 *	the pixel data is not considered for this operation. The application might
	 *	include the pixel data by specifying the option RAD_DATA_OPT_INCL_PIXELDATA. A
	 *	serialized data object can be deserialized (see RadDataObjectBase::deserialize())
	 *	at the same or a different computer using any data plugin. DICOM is used as
	 *	serialization format, which means only the information embedded into DICOM elements
	 *	is being serialized.
	 *
	 *	The application can query the required size for the output buffer by passing a NULL
	 *	pointer for the buffer parameter. In this case only an estimate is returned to the
	 *	caller, not the exact size of the output to be generated. The precise size is only
	 *	returned when the actual output is written.
	 *
	 *	\param bufferSize	Size of the output buffer.
	 *	\param buffer		Pointer to buffer that receives serialized data or NULL if the
	 *						required size for the output buffer is being queried.
	 *	\param option		Optional parameter for serialization options.
	 *						- RAD_DATA_OPT_INCL_PIXELDATA: Include pixel data.
	 *  \return	This method returns the number of bytes written into the output buffer
	 *			or the size of the buffer in bytes required to receive all serialized data
	 *			if buffer is NULL (estimate only).
	 *
	 *
	 *	\b Example:
	\code
	 
	// serialize complete content of data object to memory buffer
	unsigned char buffer[BUFFER_SIZE];
	int length = dataObject->serialize(
					BUFFER_SIZE,
					buffer,
					RAD_DATA_OPT_INCL_PIXELDATA);

	\endcode
	 */
	virtual unsigned int serialize(unsigned int bufferSize, void* buffer, unsigned int option = 0) = 0;

	/**
	 *	\brief Deserialization method.
	 *
	 *	With this method a data object can be initialized using a serialized buffer
	 *	(see RadDataObjectBase::serialize()). Pixel data is only set in the data object
	 *	if it is contained in the provided buffer.
	 *
	 *	\param bufferSize			Size of the input buffer.
	 *	\param buffer				Pointer to buffer with serialized data.
	 *	\param option				Optional parameter for serialization options (currently not used).
	 *
	 *	\b Example:
	\code
	 
	// deserialize a data object from a given buffer
	// (assumes data plugin is loaded in ptr and buffer contains DICOM data)

	RadDataObjectBase *dataObject = ((RadDataConnectorBase*) ptr)->createDataObject();
	dataObject->deserialize(bufferSize, buffer);

	// sync changes and close object
	dataObject->sync();
	dataObject->close();

	\endcode
	 */
	virtual void deserialize(unsigned int bufferSize, const void* buffer, unsigned int option = 0) = 0;


	

	/**
	 *	\brief Reads a data item of a attribute of type sequence
	 *
	 *	The attribute to be read is specified by its DICOM group and element number 
	 *	and index of the item
	 *
	 *	\param group		DICOM group identifier of the queried attribute.
	 *	\param element		DICOM element identifier of the queried attribute.
	 *	\param itemIndex	Index of item in the sequence
	 *  \return	The method returns an instance of RadDataObjectBase created with
	 *          item of the sequence.
	 *
	 */
	virtual RadDataObjectBase* getSequenceItem(RadDICOMGroupType group, RadDICOMElementType element, int itemIndex)
    {
        return 0;
    }

	

	/**
	 *	\brief Writes a data item of a attribute of type sequence
	 *
	 *	The attribute to be read is specified by its DICOM group and element number 
	 *	and index of the item
	 *
	 *	\param group		DICOM group identifier of the queried attribute.
	 *	\param element		DICOM element identifier of the queried attribute.
	 *	\param itemIndex	Index of item in the sequence
	 *	\param item			Data items in the sequence
	 *
	 */
	virtual void setSequenceItem(RadDICOMGroupType group, RadDICOMElementType element, RadDataObjectBase *seqDataObj=0, int itemIndex=-2)
	{
	}
};


#endif
