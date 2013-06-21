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
