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
//  -*- C++ -*-

/*
 * Copyright (C) 1990,91   Silicon Graphics, Inc.
 *
 _______________________________________________________________________
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 |
 |   $Revision: 1.1.1.1 $
 |
 |   Description:
 |	This file defines the SoXipKit node class.
 |
 |   Author(s)		: Paul S. Strauss, Nick Thompson
 |
 ______________  S I L I C O N   G R A P H I C S   I N C .  ____________
 _______________________________________________________________________
 */

#ifndef  SO_XIP_KIT_H
#define  SO_XIP_KIT_H

#include <xip/inventor/core/xipivcore.h>
#include <Inventor/nodes/SoSubNode.h>

class SoChildList;


//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoXipKit
//
//  Base group node: all children are traversed.
//
//////////////////////////////////////////////////////////////////////////////

class XIPIVCORE_API SoXipKit : public SoNode
{
    SO_NODE_ABSTRACT_HEADER(SoXipKit);

  public:
    // Default constructor
    // C-api: begin
    SoXipKit();

    // Constructor that takes approximate number of children
    // C-api: name=CreateN
    SoXipKit(int nChildren);

    // Adds a child as last one in group
    void		addChild(SoNode *child);

    // Adds a child so that it becomes the one with the given index
    void		insertChild(SoNode *child, int newChildIndex);

    // Returns pointer to nth child node
    SoNode *		getChild(int index) const;

    // Finds index of given child within group
    int			findChild(const SoNode *child) const;

    // Returns number of children
    int			getNumChildren() const;

    // Removes child with given index from group
    void		removeChild(int index);

    // Removes first instance of given child from group
    // C-api: name=RemoveChildNode
    void		removeChild(SoNode *child)
	{ removeChild(findChild(child)); }

    // Removes all children from group
    void		removeAllChildren();

    // Replaces child with given index with new child
    void		replaceChild(int index, SoNode *newChild);

    // Replaces first instance of given child with new child
    // C-api: name=ReplaceChildNode
    void		replaceChild(SoNode *oldChild, SoNode *newChild)
	{ replaceChild(findChild(oldChild), newChild); }

  public:
    // Implement actions
    virtual void	doAction(SoAction *action);
    virtual void	callback(SoCallbackAction *action);
    virtual void	GLRender(SoGLRenderAction *action);
    virtual void	getBoundingBox(SoGetBoundingBoxAction *action);
    virtual void	getMatrix(SoGetMatrixAction *action);
    virtual void	handleEvent(SoHandleEventAction *action);
    virtual void	pick(SoPickAction *action);
    virtual void	search(SoSearchAction *action);	
    virtual void	write(SoWriteAction *action);	

  public:
    static void		initClass();

    // Returns pointer to children
    virtual SoChildList *getChildren() const;

	virtual void setSearchingChildren( SbBool );
	virtual SbBool isSearchingChildren() const;

	virtual void setWritingChildren( SbBool );
	virtual SbBool isWritingChildren() const;

  protected:
    SoChildList		*children;

    virtual ~SoXipKit();

    // Copies the contents of the given node into this instance
    virtual void copyContents(const SoFieldContainer *fromFC, SbBool copyConnections);

	virtual SbBool setUpConnections( SbBool onOff, SbBool doItAlways = FALSE );
	SbBool connectionsSetUp;

	virtual SbBool readInstance( SoInput* in, unsigned short flags );
	virtual SbBool readChildren( SoInput* in );

	SbBool	mIsSearchingChildren;
	SbBool	mIsWritingChildren;

};

#endif /* SO_XIP_KIT_H */
