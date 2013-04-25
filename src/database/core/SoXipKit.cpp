#include <Inventor/misc/SoChildList.h>
#include <Inventor/SoDB.h>
#include <Inventor/SoInput.h>
#include <Inventor/SoOutput.h>
#include <Inventor/actions/SoActions.h>
#include <Inventor/errors/SoDebugError.h>
#include <Inventor/errors/SoReadError.h>
#include <Inventor/fields/SoFieldData.h>
#include <Inventor/elements/SoCacheElement.h>
#include <xip/inventor/core/SoXipKit.h>

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
#ifdef DEBUG
    if (child == NULL) {
	SoDebugError::post("SoXipKit::addChild", "NULL child node");
	return;
    }
#endif /* DEBUG */

    children->append(child);
}

void
SoXipKit::insertChild(SoNode *child, int newChildIndex)
{
#ifdef DEBUG
    if (child == NULL) {
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
#endif /* DEBUG */

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
#ifdef DEBUG
    if (index < 0 || index >= getNumChildren()) {
	SoDebugError::post("SoXipKit::removeChild",
			   "Index %d is out of range %d - %d",
			   index, 0, getNumChildren() - 1);
	return;
    }
#endif /* DEBUG */

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
#ifdef DEBUG
    if (index < 0 || index >= getNumChildren()) {
	SoDebugError::post("SoXipKit::replaceChild",
			   "Index %d is out of range %d - %d",
			   index, 0, getNumChildren() - 1);
	return;
    }
#endif /* DEBUG */

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
    int		numIndices;
    const int	*indices;

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
    int numIndices;
    const int *indices;
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
    int		numIndices;
    const int	*indices;
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
    int		numIndices;
    const int	*indices;

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

#ifdef DEBUG
	if (kidCopy == NULL)
	    SoDebugError::post("(internal) SoXipKit::copyContents",
			       "Child %d has not been copied yet", i);
#endif /* DEBUG */

	addChild(kidCopy);
    }

	setUpConnections( wasSetUp );
}

SbBool 
SoXipKit::setUpConnections( SbBool onOff, SbBool doItAlways )
{
    if ( !doItAlways && connectionsSetUp == onOff)
	return onOff;
    return !(connectionsSetUp = onOff);
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
		    base != NULL)
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
	while (TRUE) {
	    ret = SoBase::read(in, base, SoNode::getClassTypeId()) && ret;

	    // Add child, even if error occurred, unless there is no
	    // child to add.
	    if (base != NULL)
			addChild((SoNode *) base);

	    // Stop when we run out of valid children
	    else
		break;
	}
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
		int			i, lastChild, numIndices;
		const int		*indices;
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