/*
 *
 *  Copyright (C) 2003 MeVis gGmbH  All Rights Reserved.
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
 * Copyright (C) 2003   MeVis Research GmbH
 *
 _______________________________________________________________________
 _______________  M E V I S   R E S E A R C H   G M B H  _______________
 |
 |   $Revision$
 |
 |   Description:
 |   Manages stencil bits of the OpenGL stencil buffer
 |
 |   Author(s)      : Felix Ritter
 |
 _______________  M E V I S   R E S E A R C H   G M B H  _______________
 _______________________________________________________________________
 */

#ifndef _SO_STENCIL_BITS_ELEMENT_
#define _SO_STENCIL_BITS_ELEMENT_

#include <Inventor/system/SbSystem.h>
#include <Inventor/elements/SoInt32Element.h>

SoEXTENDER class INVENTOR_API SoStencilBitsElement : public SoInt32Element
{
   typedef SoInt32Element inherited;
   
   SO_ELEMENT_HEADER(SoStencilBitsElement);
   
   public:

      // Initializes element
      virtual void	init(SoState *state);

      // Acquires a certain number of bits for stencil operations.
      // This returns a mask of the acquired bits or 0x0 if there
      // are not enough stencil bits available.
      static uint32_t   acquireBits(SoState *state, SoNode *node, int num);
      
      // Releases the stencil bits specified by the mask.
      static void       releaseBits(SoState *state, uint32_t mask);
      
      // Returns a mask of the current stencil bits in use.
      static uint32_t   get(SoState *state) {
	 return (uint32_t)SoInt32Element::get(classStackIndex, state);
      }

      // Returns the default mask of stencil bits in use.
      static uint32_t   getDefault() {
	 return 0x0;
      }
      
      // Returns the number of stencil bits not currently used.
      static int        getNumRemainingBits(SoState *state);

      // Returns the number of bits supported by GL implementation.
      static int        getNumGLBits();
      
      // Overrides push() method to copy values from next instance in the stack.
      virtual void      push(SoState *state);

   protected:

      // Number of positions a value must be shifted according to mask.
      static int	getNumBitPositionsToShift(uint32_t mask);
      
      // Destructor.
      virtual		~SoStencilBitsElement();

   SoINTERNAL public:

      // Initializes the SoStencilBitsElement class.
      static void       initClass();

   private:

      // Stores number of bits supported by GL implementation.
      static int        numGLBits;
};

#endif  // _SO_STENCIL_BITS_ELEMENT_
