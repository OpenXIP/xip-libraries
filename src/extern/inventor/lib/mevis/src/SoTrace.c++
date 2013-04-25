/*
 *
 *  Copyright (C) 2004 MeVis gGmbH  All Rights Reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  Further, this software is distributed without any warranty that it is
 *  free of the rightful claim of any third person regarding infringement
 *  or the like.  Any license provided herein, whether implied or
 *  otherwise, applies only to this software file.  Patent licenses, if
 *  any, provided herein do not apply to combinations of this program with
 *  other software, or any other product whatsoever.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *  Contact information: MeVis, Center for Medical Diagnostic Systems and
 *  Visualization GmbH, Universitätsallee 29, D-28359 Bremen, GERMANY, or:
 *
 *  http://www.mevis.de
 *
 */

/*
 * Copyright (C) 2004   MeVis gGmbH
 *
 _______________________________________________________________________
 ______________________  M E V I S   G G M B H  ________________________
 |
 |   $Revision$
 |
 |   Description:
 |   This file contains a class to manage a buffer for a stack and a list
 |   of string pointers for tracing debug and release code.
 |
 |   Author(s)      : Wolf Spindler, Felix Ritter
 |
 ______________________  M E V I S   G G M B H  ________________________
 _______________________________________________________________________
 */

#include <string.h>
#include <Inventor/SoTrace.h>


template <typename INDEXTYPE> 
SbString
SoTraceBuffer<INDEXTYPE>::getTraceDumpString() const
{
  try {
    // A buffer to string number into it.
    char num[512] = "";

    SbString endLineStr = "\n";

    // Scan all trace list in global tracing instance. Start with the newest entry
    // and increment it until it reaches the current one. Note that it is a ring buffer.
    SbString                traceListStr = "";
    SoGlobalTraceBufferType indexCounter = 0;
    SoGlobalTraceBufferType entry        = 0;
    
    if((_maxNumTraceStackDumps > 0) && (getTraceStackTop() > 0)) {
      sprintf(num, "\nCall stack of the last %d traced functions:\n", _maxNumTraceStackDumps);
      traceListStr += num;

      // Create trace stack string.
      SoGlobalTraceBufferType stackCnt    = 0;
      const char * const *traceStack      = getTraceStack();
      SoGlobalTraceBufferType stackTop    = getTraceStackTop();
      SoGlobalTraceBufferType stackPreTop = stackTop;
      stackPreTop--;
      indexCounter = 1;

      for(entry = stackPreTop; (entry != stackTop) && (stackCnt < _maxNumTraceStackDumps); entry--, stackCnt++) {
        // Create a number string from indexCounter.
        sprintf(num, "%5d ", indexCounter);

        // Get entry. Note that it might be empty or NULL.
        const char *entryStrPtr = traceStack[entry];

        if(entryStrPtr) {
          traceListStr += ((SbString)num);
          traceListStr += entryStrPtr;
          traceListStr += endLineStr;
        }

        // Go to previous entry.
        indexCounter++;
      }
    }

    if(_maxNumTraceListDumps > 0) {
      SoGlobalTraceBufferType listCnt = 0;
      sprintf(num, "\nCall list of the %d most recently traced functions:\n", _maxNumTraceListDumps);
      traceListStr += num;
      SoGlobalTraceBufferType listEnd    = getTraceListEnd();
      SoGlobalTraceBufferType listPreEnd = listEnd;
      listPreEnd--;
      indexCounter = 1;
      const char * const *traceList = SoGlobalTraceBuffer.getTraceList();
      entry=0;

      for(entry = listPreEnd; (entry != listEnd) && (listCnt < _maxNumTraceListDumps); entry--, listCnt++) {
        // Create a number string from indexCounter.
        sprintf(num, "%5d ", indexCounter);

        // Get entry. Note that it might be empty or NULL.
        const char *entryStrPtr = traceList[entry];

        if(entryStrPtr) {
          traceListStr += ((SbString)num);
          traceListStr += entryStrPtr;
          traceListStr += endLineStr;
        }

        // Go to previous entry.
        indexCounter++;
      }
    }

    // Return composed list.
    return traceListStr;
  }
  catch(...) {
    return "<Could not determine last called functions or function stack>";
  }
}


SoTraceBuffer<SoGlobalTraceBufferType> SoGlobalTraceBuffer;


#if defined(__sgi)

// The #pragma instantiate directive causes a specific instance of a template declaration to be immediately instantiated.
#pragma instantiate SbString SoTraceBuffer<SoGlobalTraceBufferType>::getTraceDumpString() const

#else

// Dummy function not to be called. It is only used to force
// the instantiation of template functionality implemented in .c++.
void
_dummyFunction_DO_NOT_CALL()
{
  SoGlobalTraceBuffer.getTraceDumpString();
}

#endif
