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

#include <Inventor/sensors/SoDelayQueueSensor.h>
#include <xip/inventor/core/SoXipMFData.h>
#include <xip/inventor/core/SbXipDirtyFieldList.h>


SoXipMFData::~SoXipMFData()
{
	SbXipDirtyFieldList::remove(this);
}


const SoXipData** SoXipMFData::getDataValues(int start) const
{
	evaluate();
	return (const SoXipData**) (values + start);
}


void SoXipMFData::setDataValues(int start, int num, const SoXipData** newValues)
{
	int	newNum = start + num;

	if( newNum > getNum() )
		makeRoom( newNum );

	for( int i = 0; i < num; ++ i )
		set1Value_( start + i, newValues[i] );

	valueChanged();
}


void SoXipMFData::set1DataValue( int index, SoXipData* newValue )
{
	if( index >= getNum() )
		makeRoom( index + 1 );
	set1Value_( index, newValue );
	valueChanged();
}


void SoXipMFData::setDataValue( SoXipData* newValue )
{
	makeRoom(1);
	set1Value_( 0, newValue );
	valueChanged();
}


void SoXipMFData::set1Value_( int index, const SoXipData* constNewValue )
{
	SoXipData* newValue = const_cast< SoXipData* >( constNewValue );
	if( newValue == values[ index ] )
		return ;

	if( newValue != NULL )
		newValue->ref();

	if( values[ index ] != NULL )
	{
		values[ index ]->removeAuditor( this, SoNotRec::FIELD );
		values[ index ]->unref();
	}

	values[ index ] = newValue;

	if( values[ index ] != NULL )
	{
		values[ index ]->ref();
		values[ index ]->addAuditor( this, SoNotRec::FIELD );
	}

	if( newValue != NULL )
		newValue->unref();
}


int SoXipMFData::find( SoXipData* targetValue, SbBool addIfNotFound )
{
	int	num = getNum();

	for( int i = 0; i < num; ++ i )
	if( values[i] == targetValue )
		return i;

	if( addIfNotFound )
		set1DataValue( num, targetValue );

	return -1;
}


int SoXipMFData::operator ==( const SoXipMFData& other ) const
{
	int num = getNum();
	if( num != other.getNum() )
		return false;

	const SoXipData** lhs = getDataValues(0);
	const SoXipData** rhs = other.getDataValues(0);

	for( int i = 0; i < num; ++ i )
	{
		if( lhs[i] != rhs[i] )
			return false;
	}

	return true;
}


int SoXipMFData::operator !=( const SoXipMFData& other ) const
{
	return !(*this == other);
}


void SoXipMFData::allocValues( int newNum )
{
	if( values == NULL )
	{
		if( newNum > 0 )
		{
			values = new SoXipData*[ newNum ];
			memset( values, 0, newNum * sizeof( SoXipData* ) );
		}
	}
	else
	{
		int pNum = getNum();
		SoXipData** pValues = values;

		if( newNum > 0 )
		{
			values = new SoXipData*[ newNum ];

			for( int i = 0; i < newNum; ++ i )
			{
				values[i] = ( i < pNum ) ? pValues[i] : NULL;
			}
		}
		else
		{
			values = NULL;
		}

		for( int i = newNum; i < pNum; i ++ )
		{
			if( pValues[i] != NULL )
			{
				pValues[i]->removeAuditor( this, SoNotRec::FIELD );
				pValues[i]->unref();
			}
		}

		delete [] pValues;
	}

	num = maxNum = newNum;
}


void SoXipMFData::deleteAllValues()
{
	allocValues(0);
}


void SoXipMFData::copyValue( int to, int from )
{
	set1Value_( to, values[ from ] );
}


SbBool SoXipMFData::read1Value( SoInput* in, int index )
{
	SbName name;
	if( in->read( name ) )
	{
		if( name == "NULL" || name == "DATA" || name == "\"NULL\"" || name == "\"DATA\"" )
		{
			set1DataValue( index, NULL );
			SbXipDirtyFieldList::append(this);
			return TRUE;
		}
		else in->putBack( name.getString() );
	}

	SoBase* base;
	if(! SoBase::read( in, base, SoXipData::getClassTypeId() ) )
	{
		set1DataValue( index, NULL );
		return FALSE;
	}

	set1DataValue( index, NULL );
	SbXipDirtyFieldList::append(this);
	return TRUE;
}


void SoXipMFData::write1Value( SoOutput* out, int index ) const
{
	if( values[ index ] != NULL )
		out->write( "\"DATA\"" );
	else
		out->write( "\"NULL\"" );
}


void SoXipMFData::countWriteRefs( SoOutput* out ) const
{
	SoField::countWriteRefs( out );

	int num = getNum();
	for( int i = 0; i < num; ++ i )
	{
		if( values[i] != NULL )
			values[i]->addWriteReference( out );
	}
}

