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
 * Copyright (C) 2003   MeVis gGmbH
 *
 _______________________________________________________________________
 ______________________  M E V I S   G G M B H  ________________________
 |
 |   $Revision$
 |
 |   Description:
 |   ...
 |
 |   Author(s)      : Felix Ritter
 |
 ______________________  M E V I S   G G M B H  ________________________
 _______________________________________________________________________
 */


#include <Inventor/elements/SoStencilBitsElement.h>
#include OPENGL_GL_H

SO_ELEMENT_SOURCE(SoStencilBitsElement)

// This holds the number of bits supported by GL implementation
int SoStencilBitsElement::numGLBits = -1;

SoStencilBitsElement::~SoStencilBitsElement()
{
}

void
SoStencilBitsElement::initClass()
{
   SO_ELEMENT_INIT_CLASS(SoStencilBitsElement, inherited);
}

void
SoStencilBitsElement::init(SoState *)
{
   data = getDefault();
}

uint32_t
SoStencilBitsElement::acquireBits(SoState *state, SoNode *, int num)
{
   // Get an instance we can change (pushing if necessary)
   SoStencilBitsElement *elt = (SoStencilBitsElement *)getElement(state, classStackIndex);

   // Being overridden?
   if(elt == NULL)
      return 0x0;

   int max_num_bits = getNumGLBits();
   
   uint32_t avail_bits = ~ (uint32_t)elt->data;
   uint32_t mask = 0x0;
   
   for(uint32_t bit_test = 0x1; num > 0 && bit_test < ((uint32_t)0x1 << max_num_bits); bit_test <<= 1) {
      if(avail_bits & bit_test) {       // Is this bit available?
         mask |= bit_test;
         
         num--;
      }
   }
   
   if(num > 0)  // Not enough bits remaining!
      return 0x0;

   elt->data = (uint32_t)elt->data | mask;
   
   return mask;
}

void
SoStencilBitsElement::releaseBits(SoState *state, uint32_t mask)
{
   // Get an instance we can change (pushing if necessary)
   SoStencilBitsElement *elt = (SoStencilBitsElement *)getElement(state, classStackIndex);

   // Being overridden?
   if(elt == NULL)
      return;

   elt->data = (uint32_t)elt->data ^ mask;
}

int
SoStencilBitsElement::getNumBitPositionsToShift(uint32_t mask)
{
   if(mask == 0x0)
      return 0;
   
   int max_num_bits = getNumGLBits();
   int num = 0;
   
   for(uint32_t bit_test = 0x1; bit_test < ((uint32_t)0x1 << max_num_bits); bit_test <<= 1) {
      if(mask & bit_test) {       // Is this bit set in mask?
         break;
      }
      num++;
   }
   
   return num;
}

int
SoStencilBitsElement::getNumRemainingBits(SoState *state)
{
   const SoStencilBitsElement *elt= (SoStencilBitsElement *)getConstElement(state, classStackIndex);

   int max_num_bits = getNumGLBits();
   
   uint32_t avail_bits = ~ (uint32_t)elt->data;
   int remaining_bits = 0;
   
   for(uint32_t bit_test = 0x1; bit_test < ((uint32_t)0x1 << max_num_bits); bit_test <<= 1) {
      if(avail_bits & bit_test) // Is this bit available?
         remaining_bits++;
   }
   
   return remaining_bits;
}

int
SoStencilBitsElement::getNumGLBits()
{
   // Inquire GL if not already done
   if(numGLBits < 0) {
      GLint num;
      glGetIntegerv(GL_STENCIL_BITS, &num);

      numGLBits = num;
   }

   return numGLBits;
}

void
SoStencilBitsElement::push(SoState * /*state*/)
{
   // Copying current mask of stencil bits in use from
   // previous top instance.
   data = ((SoStencilBitsElement *)getNextInStack())->data;
}
