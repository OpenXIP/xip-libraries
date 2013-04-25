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

#include <Inventor/actions/SoSearchAction.h>
#include <Inventor/actions/SoWriteAction.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoBaseColor.h>
#include  <xip/inventor/overlay/SoXipManipulableShape.h>
#include "SoXipShapeList.h"
#include <xip/inventor/overlay/XipOverlayUtils.h>

SoNode*
XipOverlayUtils::loadNode( SoInput* in )
{
	SoNode* root = 0;

	SoDB::read( in, root );	

	return root;
}

SoNode*
XipOverlayUtils::loadNodeFromString( const char* str, int size )
{
	SoInput in;
	in.setBuffer( const_cast< char* >( str ), size );

	return loadNode( &in );
}

SoNode*
XipOverlayUtils::loadNodeFromFile( const char* filename )
{
	SoInput in;
	if( !in.openFile( filename, TRUE ) )
	{
		SoDebugError::post( __FILE__, "Unable to open file '%s'", filename );
		return 0;
	}

	return loadNode( &in );
}

SoNodeList
XipOverlayUtils::loadOverlaysFromNode( SoNode* root, SoType type, SbBool searchAll )
{
	SoNodeList overlays;

	if( root )
	{
		// Reference the root node before applying the action
		root->ref();

		SoSearchAction sa;
		sa.setType( type );
		sa.setInterest( SoSearchAction::ALL );
		sa.setSearchingAll( searchAll );
		sa.apply( root );

		// Now that the action is done, restore the reference count
		// of the root node. Do not delete (in case user did not ref the node
		// before calling us)
		root->unrefNoDelete();

		SoPathList paths = sa.getPaths();
		int numPaths = paths.getLength();
		for( int i = 0; i < numPaths; ++ i )
		{
			overlays.append( ((SoFullPath *) paths[i])->getTail() );
		}		
	}

	return overlays;
}

SoNodeList
XipOverlayUtils::loadOverlaysFromNode( SoNode* root, SbBool searchAll )
{
	return loadOverlaysFromNode( root, SoXipShapeList::getClassTypeId(), searchAll );
}

SoNodeList
XipOverlayUtils::loadOverlaysFromString( const char* str, int size, SbBool searchAll )
{
	return loadOverlaysFromNode( loadNodeFromString( str, size ), searchAll );
}

SoNodeList
XipOverlayUtils::loadOverlaysFromFile( const char* filename, SbBool searchAll )
{
	return loadOverlaysFromNode( loadNodeFromFile( filename ), searchAll );
}

void
XipOverlayUtils::saveOverlays( const SoNodeList& shapes, SoOutput* out )
{
	out->resetBuffer();

	SoSeparator* shapeSep = new SoSeparator;
	shapeSep->ref();

	for( int i = 0; i < shapes.getLength(); ++ i )
	{
		shapeSep->addChild( shapes[i] );
	}

	SoWriteAction wa( out );
	wa.apply( shapeSep );

	shapeSep->unref();
}

SbString
XipOverlayUtils::saveOverlaysToString( const SoNodeList& shapes )
{
	SoOutput out;
	out.setBuffer( malloc(1024), 1024, realloc );

	saveOverlays( shapes, &out );

	SbString result;

	void *bufferOut = 0;  
	size_t bufferSize = 0;
	if (out.getBuffer( bufferOut, bufferSize))
	{
		if (bufferOut)
		{
			result = SbString((char*) bufferOut, 0, bufferSize);
			free(bufferOut);
		}
	}

	return result;
}

void
XipOverlayUtils::saveOverlaysToFile( const SoNodeList& shapes, const char* filename )
{
	SoOutput out;
	if( !out.openFile( filename ) )
	{
		SoDebugError::post( __FILE__, "Unable to open file'%s'", filename );
		return ;
	}

	saveOverlays( shapes, &out );
}

SbString
XipOverlayUtils::saveNodeToString( SoNode* root )
{
	SoOutput out;
	out.setBuffer( malloc(1024), 1024, realloc );

	SoWriteAction wa( &out );
	wa.apply( root );

	SbString result;

	void *bufferOut = 0;  
	size_t bufferSize = 0;
	if (out.getBuffer( bufferOut, bufferSize))
	{
		if (bufferOut)
		{
			result = SbString((char*) bufferOut, 0, bufferSize);
			free(bufferOut);
		}
	}

	return result;
}

void
XipOverlayUtils::saveNodeToFile( SoNode* root, const char* filename )
{
	SoOutput out;
	if( !out.openFile( filename ) )
	{
		SoDebugError::post( __FILE__, "Unable to open file'%s'", filename );
		return ;
	}

	SoWriteAction wa( &out );
	wa.apply( root );	
}

SoNodeList
XipOverlayUtils::getManipulableShapes( SoNode* root, SbBool isSelected )
{
	SoNodeList list;

	if( root )
	{
		SoSearchAction sa;
		sa.setType( SoXipManipulableShape::getClassTypeId() );
		sa.setInterest( SoSearchAction::ALL );	
		sa.setSearchingAll( TRUE );
		sa.apply( root );

		SoPathList paths = sa.getPaths();
		int numPaths = paths.getLength();

		for( int i = 0; i < numPaths; ++ i )
		{
			SoFullPath* path = (SoFullPath *) paths[i];		

			if( path->getTail()->isOfType( SoXipManipulableShape::getClassTypeId() ) )
			{
				SoXipManipulableShape* shape = (SoXipManipulableShape *) path->getTail();

				if( !isSelected || shape->isSelected() )
					list.append( shape );
			}
		}
	}

	return list;
}

SoNodeList
XipOverlayUtils::getTopLevelShapes( SoNode* root, SbBool isSelected )
{
	SoNodeList list;

	if( root )
	{
		SoSearchAction sa;
		sa.setType( SoXipShape::getClassTypeId() );
		sa.setInterest( SoSearchAction::ALL );
		sa.setSearchingAll( FALSE );
		sa.apply( root );

		SoPathList paths = sa.getPaths();
		int numPaths = paths.getLength();

		for( int i = 0; i < numPaths; ++ i )
		{
			SoFullPath* path = (SoFullPath *) paths[i];

			if( path->getTail()->isOfType( SoXipShape::getClassTypeId() ) )
			{
				SoXipShape* shape = (SoXipShape *) path->getTail();

				if( !isSelected || shape->isSelected() )				
					list.append( path->getTail() );
			}
		}
	}

	return list;
}

void 
XipOverlayUtils::fillCoordIndex( const SoMFVec3f& point, const SbBool& closed, SoMFInt32& coordIndex )
{
	// Set default to no coordinate indices
	coordIndex.setNum(0);

	if( closed )
	{
		if( point.getNum() >= 3 )
		{
			coordIndex.setNum( point.getNum() + 2 );
			int* coordIndexPtr = coordIndex.startEditing();
			{
				for( int i = 0 ; i < point.getNum(); ++ i )
					coordIndexPtr[i] = i;
				coordIndexPtr[point.getNum()] = 0;
				coordIndexPtr[point.getNum() + 1] = -1;
			}
			coordIndex.finishEditing();
		}
	}
	else
	{
		if( point.getNum() >= 2 )
		{
			coordIndex.setNum( point.getNum() + 1 );
			int* coordIndexPtr = coordIndex.startEditing();
			{
				for( int i = 0 ; i < point.getNum(); ++ i )
					coordIndexPtr[i] = i;
				coordIndexPtr[point.getNum()] = -1;
			}
			coordIndex.finishEditing();
		}
	}
}

SoNodeList 
XipOverlayUtils::filterOverlays( const SoNodeList& shapeLists, 
								 const SoMFString& label, const SbString& type, const SbString& caption,
								 const SbBool selected )
{
	SoNodeList shapeListsOut;

	for( int k = 0; k < shapeLists.getLength(); ++ k )
	{
		SoXipShapeList* shapeList = (SoXipShapeList *) shapeLists[k];
		if( shapeList->isOfType( SoXipShapeList::getClassTypeId() ) )
		{
			SoXipShapeList* newShapeList = new SoXipShapeList;
			newShapeList->ref();
			newShapeList->label.setValue( shapeList->label.getValue() );

			for( int j = 0; j < shapeList->getNumChildren(); ++ j )
				newShapeList->addChild( shapeList->getChild(j) );

			shapeListsOut.append( newShapeList );

			newShapeList->unref();
		}
	}
	
	// Initialize overlay type to base type (SoXipShape)
	SoType classType = SoXipShape::getClassTypeId();
	if( type.getLength() )
		classType = SoType::fromName( type );

	if( classType.isBad() || !classType.isDerivedFrom( SoXipShape::getClassTypeId() ) )
	{
		SoDebugError::post( __FILE__, "Type must derived from SoXipShape" );
		return SoNodeList();
	}

	for( int i = 0; i < shapeListsOut.getLength(); ++ i )
	{
		SoXipShapeList* shapeList = (SoXipShapeList *) shapeListsOut[i];

		for( int j = 0; j < shapeList->getNumChildren(); ++ j )
		{
			// Filter with type
			SoXipShape* shape = (SoXipShape *) shapeList->getChild( j );
			if( !shape->isOfType( classType ) )
			{
				shapeList->removeChild( j-- );
				continue ;
			}

			// Filter with caption
			if( caption.getLength() && shape->caption.getValue() != caption )
			{
				shapeList->removeChild( j-- );
				continue ;
			}

			// Filter with label
			SbBool labelMatch = TRUE;
			for( int labelIndex = 0; labelIndex < label.getNum(); ++ labelIndex )
			{				
				if( shape->label.find( label[labelIndex] ) == -1 )
				{
					labelMatch = FALSE;
					break ;
				}
			}

			if( !labelMatch )
			{
				shapeList->removeChild( j-- );
				continue ;
			}

			// Filter with selection state
			if( selected && shape->isSelected() == FALSE )
			{
				shapeList->removeChild( j-- );
				continue ;
			}
		}

		if( shapeList->getNumChildren() == 0 )
		{
			shapeListsOut.remove( i-- );
			continue;
		}
	}

	return shapeListsOut;
}