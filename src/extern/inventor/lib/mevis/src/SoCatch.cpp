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
 *  Visualization GmbH, Universit‰tsallee 29, D-28359 Bremen, GERMANY, or:
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
 |   Macro file to implement exception handlers around some code to make
 |   code safe. In the case of caught exception an error message is composed
 |   and send to SoError.
 |   The usage of the exception handler is optional and can be enabled/disabled
 |   by the static class function SoCatch::enableExceptionHandling().
 |
 |   Author(s)      : Wolf Spindler, Felix Ritter
 |
 ______________________  M E V I S   G G M B H  ________________________
 _______________________________________________________________________
 */

#include <Inventor/SoCatch.h>
#include <Inventor/SoTrace.h>


SbBool SoCatch::_isExceptionHandlingEnabled=false;


SbBool
SoCatch::isExceptionHandlingEnabled()
{
   return _isExceptionHandlingEnabled;
}

void
SoCatch::enableExceptionHandling(SbBool on)
{
   _isExceptionHandlingEnabled = on;
}

void
SoCatch::initClass()
{
   _isExceptionHandlingEnabled = false;
}

void
SoCatch::postExceptionMessage(SoType      ERR_OBJ_TYPE_ID,
                              const char *OP_DESCR_STR,
                              SoType      ACTION_TYPE_ID,
                              const char *END_STR)
{
   SbString objName = "<unknown object>";
   try {
      if(ERR_OBJ_TYPE_ID != SoType::badType()) {
      	 objName = ERR_OBJ_TYPE_ID.getName().getString();
      }
   }
   catch(...) {
      objName="<error getting objTypeName>";
   }

   SbString opString = "";
   try {
      if(OP_DESCR_STR) {
      	 opString = OP_DESCR_STR;
      }
   }
   catch(...) {
      opString = "<error getting description>";
   }

   SbString actionName = "";
   try {
      if(ACTION_TYPE_ID != SoType::badType()) {
      	 actionName = ACTION_TYPE_ID.getName().getString();
      }
   }
   catch(...) {
      actionName="<error getting action type name>";
   }

   SbString endString = "";
   try {
      if(END_STR) {
      	 endString = END_STR;
      }
   }
   catch(...) {
      endString = "<error getting endStr name>";
   }

   SbString traceInfos ="";
   try {
      traceInfos = SoGlobalTraceBuffer.getTraceDumpString();
   }
   catch(...) {
      traceInfos="<error getting traceInfos name>";
   }

   try {
      SoError::post("Crash in %s while %s %s %s %s",
                    objName   .getString(),
                    opString  .getString(),
                    actionName.getString(),
                    endString .getString(),
                    traceInfos.getString());
   }
   catch(...) {
      SoError::post("<Could not create error message after catching error>");
   }
}
