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
#include "SoXipOverlayManips.h"
#include "SoXipOverlayTransformBoxManip.h"
#include "SoXipOverlayTranslationManip.h"
#include "SoXipOverlayHandlerManip.h"
#include "SoXipOverlaySelectionManip.h"
#include "SoXipOverlaySelectionFrame.h"

SO_NODE_SOURCE( SoXipOverlayManips );

SoXipOverlayManips::SoXipOverlayManips()
{
	SO_NODE_CONSTRUCTOR( SoXipOverlayManips );

	SO_NODE_ADD_FIELD( numNodesUpToContainer, (2) );
	SO_NODE_ADD_FIELD( multipleSelection, (FALSE) );
	SO_NODE_ADD_FIELD( enableSelection,	  (TRUE)  );

	// Main separator
	SO_XIP_KIT_ADD_ENTRY( mTopSeparator, SoSeparator, this );

	// Manipulators
	SO_XIP_KIT_ADD_ENTRY( mHandlerManip, SoXipOverlayHandlerManip, this );
	SO_XIP_KIT_ADD_ENTRY( mTransformBox, SoXipOverlayTransformBoxManip, this );
	SO_XIP_KIT_ADD_ENTRY( mSelectionManip, SoXipOverlaySelectionManip, this );
	SO_XIP_KIT_ADD_ENTRY( mTranslationManip, SoXipOverlayTranslationManip, this );
	SO_XIP_KIT_ADD_ENTRY( mSelectionFrame, SoXipOverlaySelectionFrame, this );

	((SoXipOverlayManipBase *) mHandlerManip)->numNodesUpToContainer.connectFrom( &numNodesUpToContainer );
	((SoXipOverlayManipBase *) mHandlerManip)->on.connectFrom( &enableSelection );
	((SoXipOverlayManipBase *) mSelectionManip)->numNodesUpToContainer.connectFrom( &numNodesUpToContainer );
    ((SoXipOverlayManipBase *) mSelectionManip)->on.connectFrom( &enableSelection );
	((SoXipOverlayManipBase *) mSelectionFrame)->numNodesUpToContainer.connectFrom( &numNodesUpToContainer );
	((SoXipOverlayManipBase *) mSelectionFrame)->on.connectFrom( &multipleSelection );
	((SoXipOverlayManipBase *) mTransformBox)->numNodesUpToContainer.connectFrom( &numNodesUpToContainer );
	((SoXipOverlayManipBase *) mTransformBox)->on.connectFrom( &enableSelection );
	((SoXipOverlayManipBase *) mTranslationManip)->numNodesUpToContainer.connectFrom( &numNodesUpToContainer );
	((SoXipOverlayManipBase *) mTranslationManip)->on.connectFrom( &enableSelection ); 
}


SoXipOverlayManips::~SoXipOverlayManips()
{

}

void
SoXipOverlayManips::initClass()
{
	SO_NODE_INIT_CLASS( SoXipOverlayManips, SoXipKit, "SoXipKit" );
}
