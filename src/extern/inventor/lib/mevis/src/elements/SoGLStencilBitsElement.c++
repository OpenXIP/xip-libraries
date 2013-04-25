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

#include <Inventor/elements/SoGLStencilBitsElement.h>
#include <Inventor/elements/SoViewportRegionElement.h>
#include OPENGL_GL_H

SO_ELEMENT_SOURCE(SoGLStencilBitsElement)

SoGLStencilBitsElement::~SoGLStencilBitsElement()
{
}

void
SoGLStencilBitsElement::initClass()
{
   SO_ELEMENT_INIT_CLASS(SoGLStencilBitsElement, inherited);
}

void
SoGLStencilBitsElement::clear(SoState *state, uint32_t mask, int32_t value)
{
   if(mask == 0x0)
      return;
   
   value <<= getNumBitPositionsToShift(mask);
   
   const SoGLStencilBitsElement *elt = (SoGLStencilBitsElement *)getConstElement(state, classStackIndex);
   
   // If no other node has stencil bits in use, then
   if((mask & (uint32_t)elt->data) == (uint32_t)elt->data) {
      glClearStencil((GLint)value);
      glClear(GL_STENCIL_BUFFER_BIT);
   }
   else {
      const SbViewportRegion &vp = SoViewportRegionElement::get(state);
      SbVec2s vpSize = vp.getViewportSizePixels();

      glPushAttrib(GL_STENCIL_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

      glEnable(GL_STENCIL_TEST);
      
      glStencilFunc(GL_ALWAYS, (GLint)value, mask);
      glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);

      glDisable(GL_DEPTH_TEST);
      glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);

      glMatrixMode(GL_PROJECTION);
      glPushMatrix();
      glLoadIdentity();
      glOrtho(0, vpSize[0], 0, vpSize[1], -1, 1);
      glMatrixMode(GL_MODELVIEW);
      glPushMatrix();
      glLoadIdentity();

      glBegin(GL_QUADS);
      glVertex2i(0, 0);
      glVertex2i(vpSize[0], 0);
      glVertex2i(vpSize[0], vpSize[1]);
      glVertex2i(0, vpSize[1]);
      glEnd();

      glMatrixMode(GL_PROJECTION);
      glPopMatrix();
      glMatrixMode(GL_MODELVIEW);
      glPopMatrix();

      glPopAttrib();
   }
}
