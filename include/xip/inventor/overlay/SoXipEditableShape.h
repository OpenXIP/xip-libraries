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
*	@file	SoXipEditableShape.h
*	@brief	Base class for all editable shapes
*	@author	Julien Gein
**/

#ifndef SOXIPEDITABLESHAPE_H
#define SOXIPEDITABLESHAPE_H

#include <xip/inventor/overlay/SoXipSubShape.h>
#include  <xip/inventor/overlay/xipivoverlay.h>
/**
*	@class SoXipEditableShape
*
* Base class for all editable shapes
*
**/
class XIPIVOVERLAY_API SoXipEditableShape : public SoXipManipulableShape
{
	SO_NODE_ABSTRACT_HEADER( SoXipEditableShape );

	SO_XIP_KIT_ENTRY_HEADER( mControlPointsSwitch );
	SO_XIP_KIT_ENTRY_HEADER( mControlPointsSeparator );
	SO_XIP_KIT_TYPE_ENTRY_HEADER( mControlPointsCoords, SoCoordinate3 );
	SO_XIP_KIT_ENTRY_HEADER( mControlPointsStyle );
	SO_XIP_KIT_ENTRY_HEADER( mControlPointsSet );
    
	// List of editable points
    SO_XIP_SHAPE_FIELD( point, SoMFVec3f );
	// Is the shape opened or closed ?
    SO_XIP_SHAPE_FIELD( closed, SoSFBool );

public:
	/// Constructor
	SoXipEditableShape();

	/// should the shape be closed on double click?
	SoSFBool			closeOnDblClick;

	/// Open Inventor class initialization
	static void initClass();

	/// is the shape opened or closed?
	virtual SbBool isClosed() const;

	/**
	*	@brief	Extract the shape geometries based on the shape
	* characteristics.
	*
	**/
	virtual void updateGeometries();

	/**
	*	@brief	Compute the position of the annotation
	*
	*	@param	computed position
	*
	**/
	virtual void updateAnnotationPosition( SoSFVec3f& position );

	/**
	*	@brief	Compute the position of the enumeration
	*
	*	@param	computed position
	*
	**/
	virtual void updateEnumerationPosition( SoSFVec3f& position );

	/// Apply the given transformation to the editable points
	virtual void transform( const SbMatrix& matrix );

	/// Pick a control point. Return its id.
	virtual int  pickControlPoint( SoHandleEventAction* action );

	/// Add a control point on the editable shape
	virtual void addPoint( SoNode* node, const SbVec2s& screenPt );

	/// Delete a control point from the editable shape at given position
	virtual void deletePoint( int id );

    /**
    *   @brief  Callback function called before the shape editing
    *
    **/
	virtual void startEditing();

    /**
    *   @brief  Callback function called after the shape editing
    *
    **/
	virtual void finishEditing();

    /**
    *   @brief  Callback function called before the shape creation
    *
    **/
	virtual void beforeCreation();
	
    /**
    *   @brief  Extract the shape geometries
    *
    * This method is called by the base class to retrieve the points and segments
    * defining the shape. 
    *
    *   @param point			output array of points
    *   @param coordIndex		output array of point indices
	*	@param closed			is the shape closed?
	*
    **/
	virtual void extractGeometries( SoMFVec3f& point, SoMFInt32& coordIndex, SbBool& closed );

protected:
	/// Destructor
	~SoXipEditableShape();

	/// Event handler method
	virtual void handleEvent( SoHandleEventAction* action );

	/// return wheter a point belong to the contour or not
	virtual bool belongsToContour( const SbVec3f& worldPt, int &id );
	
	/**
    *   @brief  Map a displayed line index to its preceding control point.
	*
    * This method is called when the shape is edited and a control point
	* needs to be added. The editor only knows about the extracted point, not
	* the control points.
    *
    *   @param id	index 
	*
	*	@return	index of the preceding control point
	**/
	virtual int  getPreviousControlPoint( int id ) const;

    /**
    *   @brief  Extract control points that are used to edit the shape
    *
    *   @param points   output array of points
    **/
	virtual void extractControlPoints( SoMFVec3f& points );

	/// Picked shape
	SoXipShape*			mPickedShape;
	/// Id of the control point picked
	int					mControlPointId;

};

#endif // SOXIPEDITABLESHAPE_H