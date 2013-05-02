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

#include <xip/inventor/core/SoXipKit.h>

#include <Inventor/misc/SoChildList.h>
#include <Inventor/SoDB.h>
#include <Inventor/SoInput.h>
#include <Inventor/SoOutput.h>
#include <Inventor/actions/SoActions.h>
#include <Inventor/errors/SoDebugError.h>
#include <Inventor/errors/SoReadError.h>
#include <Inventor/fields/SoFieldData.h>
#include <Inventor/elements/SoCacheElement.h>

SO_NODE_ABSTRACT_SOURCE(SoXipKit);

SoXipKit::SoXipKit()
{
    children = new SoChildList(this);
    SO_NODE_CONSTRUCTOR(SoXipKit);
    isBuiltIn = TRUE;

	mIsSearchingChildren = FALSE;
	mIsWritingChildren = FALSE;

	connectionsSetUp = FALSE;
	setUpConnections( TRUE, TRUE );
}

SoXipKit::SoXipKit(int nChildren)
{
    children = new SoChildList(this, nChildren);
    SO_NODE_CONSTRUCTOR(SoXipKit);
    isBuiltIn = TRUE;
}

SoXipKit::~SoXipKit()
{
    delete children;
}

void
SoXipKit::initClass()
{
    SO_NODE_INIT_ABSTRACT_CLASS( SoXipKit, SoNode, "Node" );
}

void
SoXipKit::addChild(SoNode *child)
{
    if (child == 0) {
		SoDebugError::post("SoXipKit::addChild", "NULL child node");
	return;
    }

    children->append(child);
}

void
SoXipKit::insertChild(SoNode *child, int newChildIndex)
{

    if (child == 0) {
		SoDebugError::post("SoXipKit::insertChild", "NULL child node");
	return;
    }

    // Make sure index is reasonable
    if (newChildIndex < 0 || newChildIndex > getNumChildren()) {
	SoDebugError::post("SoXipKit::insertChild",
			   "Index %d is out of range %d - %d",
			   newChildIndex, 0, getNumChildren());
	return;
    }

    // See if adding at end
    if (newChildIndex >= getNumChildren())
	children->append(child);

    else
	children->insert(child, newChildIndex);
}

SoNode *
SoXipKit::getChild(int index) const
{
    return(*children)[index];
}

int
SoXipKit::getNumChildren() const
{
    return children->getLength();
}

int
SoXipKit::findChild(const SoNode *child) const
{
    int i, num;

    num = getNumChildren();

    for (i = 0; i < num; i++)
	if (getChild(i) == child) return(i);

    return(-1);
}

void
SoXipKit::removeChild(int index)
{
    if (index < 0 || index >= getNumChildren()) {
	SoDebugError::post("SoXipKit::removeChild",
			   "Index %d is out of range %d - %d",
			   index, 0, getNumChildren() - 1);
	return;
    }

    // Play it safe anyway...
    if (index >= 0) {
	children->remove(index);
    }
}

void
SoXipKit::removeAllChildren()
{
    children->truncate(0);
}

void
SoXipKit::replaceChild(int index, SoNode *newChild)
{

    if (index < 0 || index >= getNumChildren()) {
	SoDebugError::post("SoXipKit::replaceChild",
			   "Index %d is out of range %d - %d",
			   index, 0, getNumChildren() - 1);
	return;
    }

    // Play it safe anyway...
    if (index >= 0)
	children->set(index, newChild);
}

SoChildList *
SoXipKit::getChildren() const
{
    return children;
}

void
SoXipKit::doAction(SoAction *action)
{
    int		numIndices = 0;
    const int	*indices = 0;

    if (action->getPathCode(numIndices, indices) == SoAction::IN_PATH)
	children->traverse(action, 0, indices[numIndices - 1]);

    else
	children->traverse(action);
}

void
SoXipKit::callback(SoCallbackAction *action)
{
    SoXipKit::doAction(action);
}

void
SoXipKit::GLRender(SoGLRenderAction *action)
{
    int numIndices = 0;
    const int *indices = 0;
    SoAction::PathCode pc = action->getPathCode(numIndices, indices);

    // Perform fast-path GLRender traversal:
    if (pc != SoAction::IN_PATH) {
	action->pushCurPath();
	for (int i = 0; i < children->getLength(); i++) {

	    action->popPushCurPath(i);
            if (! action->abortNow())
	        ((SoNode*)(children->get(i)))->GLRender(action);
    	    else
             	SoCacheElement::invalidate(action->getState());

            // Stop if action has reached termination condition. (For
            // example, search has found what it was looking for, or event
            // was handled.)
            if (action->hasTerminated())
                break;
        }
	action->popCurPath();
    }

    else {

	// This is the same as SoChildList::traverse(), except that it
	// checks render abort for each child

	int lastChild = indices[numIndices - 1];
	for (int i = 0; i <= lastChild; i++) {

	    SoNode *child = (SoNode *) children->get(i);

	    if (pc == SoAction::OFF_PATH && ! child->affectsState())
		continue;

	    action->pushCurPath(i);
	    if (action->getCurPathCode() != SoAction::OFF_PATH ||
		child->affectsState()) {

		if (! action->abortNow())
		    child->GLRender(action);
		else
		    SoCacheElement::invalidate(action->getState());
	    }

	    action->popCurPath(pc);

	    if (action->hasTerminated())
		break;
	}
    }
}

void
SoXipKit::getBoundingBox(SoGetBoundingBoxAction *action)
{
    SbVec3f	totalCenter(0,0,0);
    int		numCenters = 0;
    int		numIndices = 0;
    const int	*indices = 0;
    int		lastChild;

    if (action->getPathCode(numIndices, indices) == SoAction::IN_PATH)
	lastChild = indices[numIndices - 1];
    else
	lastChild = getNumChildren() - 1;

    for (int i = 0; i <= lastChild; i++) {
	children->traverse(action, i, i);
	if (action->isCenterSet()) {
	    totalCenter += action->getCenter();
	    numCenters++;
	    action->resetCenter();
	}
    }
    // Now, set the center to be the average. Don't re-transform the
    // average, which should already be transformed.
    if (numCenters != 0)
	action->setCenter(totalCenter / numCenters, FALSE);
}

void
SoXipKit::handleEvent(SoHandleEventAction *action)
{
    SoXipKit::doAction(action);
}

void
SoXipKit::pick(SoPickAction *action)
{
    SoXipKit::doAction(action);
}

void
SoXipKit::search(SoSearchAction *action)
{
    // First see if the caller is searching for this node
    SoNode::search(action);

	if( isSearchingChildren() )
	{
		// Then recurse on children if not already found
		if (! action->isFound())
		SoXipKit::doAction(action);
	}
}

void
SoXipKit::setSearchingChildren( SbBool state )
{
	mIsSearchingChildren = state;
}

SbBool
SoXipKit::isSearchingChildren() const
{
	return mIsSearchingChildren;
}

void
SoXipKit::getMatrix(SoGetMatrixAction *action)
{
    int		numIndices = 0;
    const int	*indices = 0;

    // Only need to compute matrix if group is a node in middle of
    // current path chain or is off path chain (since the only way
    // this could be called if it is off the chain is if the group is
    // under a group that affects the chain).

    switch (action->getPathCode(numIndices, indices)) {

      case SoAction::NO_PATH:
	break;

      case SoAction::IN_PATH:
	children->traverse(action, 0, indices[numIndices - 1]);
	break;

      case SoAction::BELOW_PATH:
	break;

      case SoAction::OFF_PATH:
	children->traverse(action);
	break;
    }
}

void
SoXipKit::copyContents(const SoFieldContainer *fromFC, SbBool copyConnections)
{
    SbBool wasSetUp = setUpConnections( FALSE );

    // Copy the usual stuff
    SoNode::copyContents(fromFC, copyConnections);

    // Copy the kids
    const SoXipKit *fromGroup = (const SoXipKit *) fromFC;
    for (int i = 0; i < fromGroup->getNumChildren(); i++) {

	// If this node is being copied, it must be "inside" (see
	// SoNode::copy() for details.) Therefore, all of its children
	// must be inside, as well.
	SoNode *fromKid = fromGroup->getChild(i);
	SoNode *kidCopy = (SoNode *) findCopy(fromKid, copyConnections);

	if (kidCopy == 0)
	    SoDebugError::post("(internal) SoXipKit::copyContents",
			       "Child %d has not been copied yet", i);

	addChild(kidCopy);
    }

	setUpConnections( wasSetUp );
}

SbBool 
SoXipKit::setUpConnections( SbBool onOff, SbBool doItAlways )
{
    if ( !doItAlways && connectionsSetUp == onOff)
		return onOff;
	connectionsSetUp = onOff;
    return !connectionsSetUp;
}

SbBool
SoXipKit::readChildren(SoInput* in)
{
    SoBase	*base;
    SbBool	ret = TRUE;

    // If reading binary, read number of children first
    if (in->isBinary()) {

	int	numToRead, i;

	if (!in->read(numToRead))
	    ret = FALSE;

	else {
	    for (i = 0; i < numToRead; i++) {

		if (SoBase::read(in, base, SoNode::getClassTypeId()) &&
		    base != 0)
		    addChild((SoNode *) base);

		// Running out of children is now an error, since the
		// number of children in the file must be exact
		else {
		    ret = FALSE;
		    break;
		}
	    }
	    // If we are reading a 1.0 file, read the GROUP_END_MARKER
	    if (ret && in->getIVVersion() == 1.0f) {
		const int GROUP_END_MARKER = -1;
		int marker;

		// Read end marker if it is there. If not, some sort of
		// error occurred.
		if (! in->read(marker) || marker != GROUP_END_MARKER)
		    ret = FALSE;
	    }
	}
    }

    // ASCII: Read children until none left. Deal with children
    // causing errors by adding them as is.
    else {
//prevent warning due to constant conditional expression
#pragma warning (disable: 4127)
	while (TRUE) {
	    ret = SoBase::read(in, base, SoNode::getClassTypeId()) && ret;

	    // Add child, even if error occurred, unless there is no
	    // child to add.
	    if (base != 0)
			addChild((SoNode *) base);

	    // Stop when we run out of valid children
	    else
		break;
	}
#pragma warning (default: 4127)
    }

    return ret;
}

SbBool
SoXipKit::readInstance( SoInput *in, unsigned short flags )
{
    SbBool readOK = TRUE;

	SbBool saveNotify = enableNotify(FALSE);
	SbBool wasSetUp = setUpConnections( FALSE );
    
	if( !mIsWritingChildren )
	{
		readOK = SoNode::readInstance( in, flags );
	}
	else
	{
		// Read field info. We can't just call
		// SoFieldContainer::readInstance() to read the fields here
		// because we need to tell the SoFieldData that it's ok if a name
		// is found that is not a valid field name - it could be the name
		// of a child node.
		SbBool notBuiltIn; // Not used
		readOK = getFieldData()->read(in, this, FALSE, notBuiltIn);
		if (!readOK) return readOK;

		// If binary BUT was written without children (which can happen
		// if it was read as an unknown node and then written out in
		// binary), don't try to read children:
		if (!in->isBinary() || (flags & IS_GROUP)) 
		readOK = readChildren(in);
	}
    
   	setUpConnections( wasSetUp );
	enableNotify(saveNotify); 

    return readOK;
}

void
SoXipKit::setWritingChildren( SbBool writeChildren )
{
	mIsWritingChildren = writeChildren;
}

SbBool
SoXipKit::isWritingChildren() const
{
	return mIsWritingChildren;
}

void
SoXipKit::write( SoWriteAction* action )
{
	if( !mIsWritingChildren )
	{
		SoNode::write( action );
	}
	else
	{
		SoOutput	*out = action->getOutput();

		// In write-reference counting phase
		if (out->getStage() == SoOutput::COUNT_REFS) {

		// Increment our write reference count
		addWriteReference(out);

		// If this is the first reference (i.e., we don't now have
		// multiple references), also count the appropriate children
		if (! hasMultipleWriteRefs())
			SoXipKit::doAction(action);
		}

		// In writing phase, we have to do some more work
		else if (! writeHeader(out, TRUE, FALSE)) {

		// Write fields
		const SoFieldData	*fieldData = getFieldData();
		fieldData->write(out, this);

		// See which children to traverse
		int i = 0;
                int lastChild = 0;
                int numIndices = 0;
		const int * indices = 0;

		if (action->getPathCode(numIndices, indices) == SoAction::IN_PATH)
			lastChild = indices[numIndices - 1];
		else
			lastChild = getNumChildren() - 1;

		int numChildren = 0;
		for (i = 0; i <= lastChild; i++)
			if (getChild(i)->shouldWrite() > 0)
			numChildren++;

		// If writing binary format, write out number of children
		// that are going to be written
		if (out->isBinary())
			out->write(numChildren);

		// In the writing stage, we can't use standard traversal,
		// because if we are writing out one path of a path list, we
		// might need to write out children that are not relevant to
		// the current path (but are relevant to another path in the
		// list). Therefore, we implement a different traversal that
		// writes out each child that is referenced.
		for (i = 0; i <= lastChild; i++)
			if (getChild(i)->shouldWrite())
			children->traverse(action, i);

		// Write post-children stuff
		writeFooter(out);
		}
	}
}
