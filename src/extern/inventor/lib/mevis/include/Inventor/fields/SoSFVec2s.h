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
 * Copyright (C) 2005   MeVis Research GmbH
 *
 _______________________________________________________________________
 _______________  M E V I S   R E S E A R C H   G M B H  _______________
 |
 |   $Revision$
 |
 |   Classes:
 |	SoSFVec2s
 |
 |   Author(s)      : Felix Ritter
 |
 _______________  M E V I S   R E S E A R C H   G M B H  _______________
 _______________________________________________________________________
 */

#ifndef  _SO_SF_VEC2S_
#define  _SO_SF_VEC2S_

#include <Inventor/system/SbSystem.h>
#include <Inventor/fields/SoSubField.h>
#include <Inventor/SbLinear.h>

class INVENTOR_API SoSFVec2s : public SoSField
{
   typedef SoSField inherited;
   
   SO_SFIELD_HEADER(SoSFVec2s, SbVec2s, const SbVec2s &);

   public:

      //! Set value from 2 shorts
      void         setValue(short x, short y);

      //! Set value from array of 2 shorts
      void         setValue(const short xy[2]);


   SoINTERNAL public:

      //! Initialize class with runtime type system.
      static void  initClass();
};

#endif  // _SO_SF_VEC2S_
