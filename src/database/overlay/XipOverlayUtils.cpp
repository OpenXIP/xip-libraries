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
