/*
 *
 *  Copyright (C) 2005 MeVis gGmbH  All Rights Reserved.
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
 * Copyright (C) 2005   MeVis gGmbH
 *
 _______________________________________________________________________
 ______________________  M E V I S   G G M B H  ________________________
 |
 |   $Revision$
 |
 |   Classes:
 |	SoSFVec3s
 |
 |   Author(s)      : Felix Ritter
 |
 ______________________  M E V I S   G G M B H  ________________________
 _______________________________________________________________________
 */

#include <Inventor/fields/SoSFVec3s.h>

SO_SFIELD_SOURCE(SoSFVec3s, SbVec3s, const SbVec3s &);

void
SoSFVec3s::initClass()
{
   SO_SFIELD_INIT_CLASS(SoSFVec3s, inherited);
}

void
SoSFVec3s::setValue(short x, short y, short z)
{
   setValue(SbVec3s(x, y, z));
}

void
SoSFVec3s::setValue(const short xyz[3])
{
   setValue(SbVec3s(xyz));
}

SbBool
SoSFVec3s::readValue(SoInput *in)
{
   return(in->read(value[0]) && in->read(value[1]) && in->read(value[2]));
}

void
SoSFVec3s::writeValue(SoOutput *out) const
{
   out->write(value[0]);

   if(!out->isBinary())
      out->write(' ');

   out->write(value[1]);

   if(!out->isBinary())
      out->write(' ');
   
   out->write(value[2]);
}
