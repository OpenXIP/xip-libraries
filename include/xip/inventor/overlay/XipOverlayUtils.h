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
*	@file	XipOverlayUtils.h
*	@brief	Contains utilities to facilitate overlay loading, saving, and retrieving.
*	@author	Julien Gein
**/
 
#ifndef XIPOVERLAYUTILS_H
#define XIPOVERLAYUTILS_H

#include <xip/inventor/overlay/xipivoverlay.h>
#include <Inventor/fields/SoMFVec3f.h>
#include <Inventor/fields/SoMFInt32.h>
#include <Inventor/fields/SoMFString.h>
#include <Inventor/SbString.h>
#include <Inventor/SoLists.h>

// Forward declarations
class SoNode;
class SoInput;
class SoOutput;
class SoSeparator;

class XIPIVOVERLAY_API XipOverlayUtils
{
public:
	/**
	*	@brief	Load a tree from a streamed input
	*
	*	@param input	streamed input
	*
	*	@return a pointer to a tree
	*
	**/
	static SoNode* loadNode( SoInput* in );

	/**
	*	@brief	Load a tree from a string
	*
	*	@param str		input string
	*	@param size		size of the string
	*
	*	@return a pointer to a tree
	*
	**/
	static SoNode* loadNodeFromString( const char* str, int size );

	/**
	*	@brief	Load a tree from a file
	*
	*	@param filename		filename
	*
	*	@return a pointer to a tree
	*
	**/
	static SoNode* loadNodeFromFile( const char* filename );

	/**
	*	@brief	Serialize a tree to a string
	*
	*	@param root			root node of the tree
	*
	*	@return a string
	*
	**/
	static SbString saveNodeToString( SoNode* root );

	/**
	*	@brief	Serialize a tree to a file
	*
	*	@param root			root node of the tree
	*	@param filename		filename
	*
	**/
	static void saveNodeToFile( SoNode* root, const char* filename );

	/**
	*	@brief	Load a list of overlays of a specific type from a tree
	*
	*	@param root			root node of the tree where overlays are searched for
	*	@param type			overlay type
	*	@param searchAll	searchAll flag of the search action used to retrieve the overlays
	* from the root node
	*
	*	@return a list of overlays
	*
	**/
	static SoNodeList loadOverlaysFromNode( SoNode* root, SoType type, SbBool searchAll );

	/**
	*	@brief	Load a list of overlays from a tree
	*
	*	@param root			root node of the tree where overlays are searched for
	*	@param searchAll	searchAll flag of the search action used to retrieve the overlays
	* from the root node
	*
	*	@return a list of overlays
	*
	**/
	static SoNodeList loadOverlaysFromNode( SoNode* root, SbBool searchAll );

	/**
	*	@brief	Load a list of overlays from a string
	*
	*	@param str			input string
	*	@param searchAll	searchAll flag of the search action used to retrieve the overlays
	* from the Open Inventor string
	*
	*	@return a list of overlays
	*
	**/
	static SoNodeList loadOverlaysFromString( const char* str, int size, SbBool searchAll );

	/**
	*	@brief	Load a list of overlays from a file
	*
	*	@param filename		filename
	*	@param searchAll	searchAll flag of the search action used to retrieve the overlays
	* from the Open Inventor file
	*
	*	@return a list of overlays
	*
	**/
	static SoNodeList loadOverlaysFromFile( const char* filename, SbBool searchAll );

	/**
	*	@brief	Serialize a list of overlays to a SoOutput
	*
	*	@param overlays		list of overlays
	*	@param out			streamed output
	*
	**/
	static void saveOverlays( const SoNodeList& overlays, SoOutput* out );

	/**
	*	@brief	Serialize a list of overlays to a string
	*
	*	@param overlays		list of overlays
	*
	*	@return a string
	*
	**/
	static SbString saveOverlaysToString( const SoNodeList& shapes );

	/**
	*	@brief	Serialize a list of overlays to a file
	*
	*	@param shapes		list of overlays
	*	@param filename		filename
	*
	**/
	static void saveOverlaysToFile( const SoNodeList& overlays, const char* filename );

	/**
	*	@brief	Get all scene manipulable shapes
	*
	* Manipulable shapes can be considered as terminal nodes. For instance two line
	* shapes compound to form an angle shape (derived from SoXipShapeGroup) are
	* shapes that can be manipulated independently.
	*
	*	@param root			root node where the search action is applied
	*	@param isSelected	if true, only returns selected shapes
	*
	*	@return list of shapes
	**/
	static SoNodeList getManipulableShapes( SoNode* root, SbBool isSelected );
	
	/**
	*	@brief	Get all the top-level shapes
	*
	* Returns only the top level shapes, i.e. shape groups do not search their own children.
	*
	*	@param root			root node where the search action is applied
	*
	*	@return list of shapes
	**/
	static SoNodeList getTopLevelShapes( SoNode* root, SbBool isSelected = FALSE );
    
	/**
	*	@brief	Fill a point indices array given a list of point and the type of shape
	*
	*	@param point			input array of points
    *   @param closed           is the shape closed or not?
    *   @param coordIndex       output array of point indices
    *
	**/
    static void fillCoordIndex( const SoMFVec3f& point, const SbBool& closed, SoMFInt32& coordIndex );

	/**
	*	@brief	Filter a list of overlay nodes with multiple criteria
	*
	*	@param overlays			input array of overlay nodes
    *   @param label			list of overlay labels
    *   @param type				overlay base type class name
    *   @param caption			overlay caption
	*	@param selected			should the overlay be selected or not?
    *
	**/
	static SoNodeList filterOverlays( const SoNodeList& overlays,
		const SoMFString& label, const SbString& type, const SbString& caption,
		const SbBool selected = FALSE );

};

#endif // XIPOVERLAYUTILS_H
