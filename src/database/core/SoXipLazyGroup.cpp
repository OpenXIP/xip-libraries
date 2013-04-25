

#include <Inventor/actions/SoGLRenderAction.h>
#include "SoXipLazyGroup.h"


SO_NODE_SOURCE( SoXipLazyGroup );

SoXipLazyGroup::SoXipLazyGroup()
{
    SO_NODE_CONSTRUCTOR(SoXipLazyGroup);

    mNodeID = 0;
}

void SoXipLazyGroup::initClass()
{
    SO_NODE_INIT_CLASS(SoXipLazyGroup, SoGroup, "Group")
}

void SoXipLazyGroup::GLRender(SoGLRenderAction *action)
{
    if(mNodeID != getNodeId())
    {
        mNodeID = getNodeId();
        SoGroup::GLRender(action); // traverse children...
    }
}

