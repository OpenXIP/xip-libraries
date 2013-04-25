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
 |   This include file contains code for handling UTF-8 path names.
 |
 |   Author(s)      : Florian Link, Felix Ritter
 |
 ______________________  M E V I S   G G M B H  ________________________
 _______________________________________________________________________
 */

#include <xip/system/standard.h>
#include <stdio.h>

FILE *
fopen_utf8(const char *filename, const char *mode)
{
  FILE *file = NULL;
  WCHAR wMode[32];
  WCHAR wFileName[MAX_PATH];

  // convert the mode from ascii to ucs2
  MultiByteToWideChar(CP_ACP, 0, mode, strlen(mode)+1, wMode, 32);
  
  // convert the filename from utf8 to ucs2
  int r = MultiByteToWideChar(CP_UTF8, 0, filename,
                              strlen(filename)+1, wFileName, MAX_PATH);
  if (r!=0) {
    file = _wfopen(wFileName, wMode);
  }
  return file;
}
