/*
 *  COPYRIGHT NOTICE.  Copyright (C) 2005 Siemens Corporate Research, 
 *  Inc. ("caBIG(tm) Participant"). eXtensible Imaging Platform (XIP)
 *  was created with NCI funding and is part of the caBIG(tm) 
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

#ifndef SOXIPMFDATA_H
#define SOXIPMFDATA_H

#include <Inventor/fields/SoSubField.h>
#include <xip/inventor/core/xipivcore.h>
#include <xip/inventor/core/SoXipData.h>


// base class for multiple value fields containing non-serializable pointers
class XIPIVCORE_API SoXipMFData : public SoMField
{
public:
	SbBool isReadOnly() const { return FALSE; };

    const SoXipData** getDataValues(int start) const;
	void setDataValues(int start, int num, const SoXipData** newValues);
	void setDataValue( SoXipData* newValue );
	void set1DataValue( int index, SoXipData* newValue );

	int operator ==( const SoXipMFData& other ) const;
	int operator !=( const SoXipMFData& other ) const;

protected:
	virtual ~SoXipMFData();

	// inventor internal
	int find( SoXipData* targetValue, SbBool addIfNotFound );
	virtual void allocValues( int newNum );
	virtual void deleteAllValues();
	virtual void copyValue( int to, int from );
	virtual SbBool read1Value( SoInput* in, int index );
	virtual void write1Value( SoOutput* out, int index ) const;
	virtual void countWriteRefs( SoOutput* out ) const;
	void SoXipMFData::set1Value_( int index, const SoXipData* constNewValue );

    SoXipData **values;
};


#if !defined(COIN_DLL) && !defined(COIN_NO_DLL)

// SGI Inventor:

// Unfortunately with SGI Inventor we cannot use SO_MFDATA_VALUE_HEADER()
// and SO_MFDATA_VALUE_SOURCE() due to the use of const attributes in
// some headers. Therefore we need to provide our own implementation (we
// implement only the necessary ones).
#define XIP_MFDATA_VALUE_HEADER(classname, type, notUsed)					\
	public:																	\
	type operator [](int i) const;											\
	const type *getValues(int start) const;									\
	void setValues(int start, int num, const type *newValues);				\
	void set1Value(int index, type newValue);								\
	void setValue(type newValue);											\
	type operator =(type newValue);											\
	type *startEditing();													\
	void finishEditing();


#define XIP_MFDATA_VALUE_SOURCE(classname, type, notUsed)					\
	type classname::operator [](int i) const								\
	{ evaluate(); return (type) values[i]; }								\
																			\
    const type * classname::getValues(int start) const						\
	{ return (const type *) getDataValues(start); }							\
																			\
	void classname::setValues(int start, int num, const type* newValues)	\
	{ setDataValues(start, num, (const SoXipData**) newValues); }			\
																			\
	void classname::set1Value( int index, type newValue )					\
	{ set1DataValue(index, newValue); }										\
																			\
	void classname::setValue( type newValue )								\
	{ setDataValue(newValue); }												\
																			\
	type *classname::startEditing()											\
	{ evaluate(); return (type *) values; }									\
																			\
	void classname::finishEditing()											\
	{ valueChanged(); }



#define XIP_MFDATA_HEADER(classname, type)									\
	SO_MFIELD_REQUIRED_HEADER( classname );									\
	SO_MFIELD_CONSTRUCTOR_HEADER( classname );								\
	XIP_MFDATA_VALUE_HEADER( classname, type*, type* );						\
																			\
	public:																	\
	static void initClass();

#define XIP_MFDATA_SOURCE(classname, type)									\
	SO_MFIELD_REQUIRED_SOURCE( classname )									\
	SO_MFIELD_CONSTRUCTOR_SOURCE( classname )								\
	XIP_MFDATA_VALUE_SOURCE( classname , type*, type* )						\
																			\
	void classname::initClass()												\
	{ SO_SFIELD_INIT_CLASS( classname, SoMField ); }


#else 

// COIN:

#define XIP_MFDATA_HEADER(classname, type)									\
    SO_SFIELD_REQUIRED_HEADER( classname );									\
    SO_SFIELD_CONSTRUCTOR_HEADER( classname );								\
	SO_MFIELD_VALUE_HEADER(classname, type*, type*);						\
																			\
	public:																	\
	static void initClass();

#define XIP_MFDATA_SOURCE(classname, type)									\
	SO_MFIELD_REQUIRED_SOURCE(classname);									\
	SO_MFIELD_CONSTRUCTOR_SOURCE(classname);								\
	SO_MFIELD_VALUE_SOURCE(classname, type*, type*);						\
	SO_MFIELD_MALLOC_SOURCE(classname, type*);								\
																			\
	SbBool classname::read1Value(SoInput * in, int idx)						\
	{ return SoXipMFData::read1Value(in, idx); };							\
																			\
	void classname::write1Value(SoOutput * out, int idx) const				\
	{ SoXipMFData::write1Value(out, idx); };								\
																			\
	void classname::initClass()												\
	{ SO_SFIELD_INIT_CLASS( classname, SoMField ); }

#endif


#endif	// SOXIPMFDATA_H

