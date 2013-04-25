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

/**
*	@file    SoXipShapeGroup.h
*	@brief   Base class for all compound shapes
*	@author  Julien Gein
**/

#ifndef SOXIPSHAPEGROUP_H
#define SOXIPSHAPEGROUP_H

#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoMFNode.h>
#include <Inventor/sensors/SoFieldSensor.h>
#include <xip/inventor/overlay/SoXipShape.h>

/**
*	@class SoXipShapeGroup
*
* This class can be used as base class for all the shapes
* that are a composition of one or more SoXipShape. The shape group
* is handled by the framework as one overlay (same id, etc.) although
* its children can be manipulated individually.
*
**/
class SoXipShapeGroup : public SoXipShape
{
	SO_NODE_ABSTRACT_HEADER( SoXipShapeGroup );

public:
	/// Constructor
	SoXipShapeGroup();

	/// If children are linked, then selecting/unselecting one child of this group is
	/// like selecting/unselecting all the children
	SoSFBool			childrenLinked;
	/// List of children
	SoMFNode			children;

	/// Open Inventor class initialization
	static void initClass();

	/// Is the shape group being edited ?
	virtual SbBool isEditing() const;
	/// Is the shape group being created ?
	virtual SbBool isCreating() const;
	/// Is the shape group selected ?
	virtual SbBool isSelected() const;

	/// Return the number of children shapes
	int getNumChildren() const;
	/// Return the child shape at given position
	SoNode* getChild( int index ) const;
	/// Add a child shape to the group
    void addChild( SoNode* child );
	/// Insert a child shape to the group at the given position
    void insertChild( SoNode* child, int newChildIndex );
	/// Remove child from the group at the given position
    void removeChild( int index );
	/// Remove all child shapes from the group
    void removeAllChildren();
	/// Replace the child at given position by given node
    void replaceChild( int index, SoNode* newChild );

	/// Set the index of the child that will terminate the group creation
	void setCreationChild( int index );
	/// Set the child that will terminate the group creation
	void setCreationChild( SoNode* child );

	/// Set the order of the group (back to front)
	virtual void setOrder( int order ) {}
	/// Set the label (name) of the group
	virtual void setLabel( const SoMFString& label );
	/// Set the rank (enumeration) of the group
	virtual void setRank( int rank ) {}
	/// Set the caption (annotation) of the group
	virtual void setCaption( const SbString& caption ) {}

	virtual void invalidateGeometries();
	virtual void updateGeometries();

	/**
    *   @brief  Callback function called before the shape creation
    *
    **/
	virtual void beforeCreation();

	/**
    *   @brief  Callback function called after the shape creation
    *
    **/
	virtual void afterCreation();

protected:
	/// Destructor
	virtual ~SoXipShapeGroup();

	virtual SbBool readInstance( SoInput* in, unsigned short flags );
	virtual SbBool setUpConnections( SbBool onOff, SbBool doItAlways = FALSE );

    virtual void search( SoSearchAction* action );

private:
	static void creationStatusSensorCB( void* userData, SoSensor* sensor );
	static void shapeSensorCB( void* userData, SoSensor* sensor );

	SoFieldSensor*		mCreationStatusSensor;
	SoFieldSensor*		mShapeSensors[2];
	int					mCreationChildIndex;

};

#endif // SOXIPSHAPEGROUP_H