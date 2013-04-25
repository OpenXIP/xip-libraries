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
 |   ...
 |
 |   Author(s)      : Felix Ritter
 |
 ______________________  M E V I S   G G M B H  ________________________
 _______________________________________________________________________
 */

#include <Inventor/elements/SoGLPolygonOffsetElement.h>
#include OPENGL_GL_H

SO_ELEMENT_SOURCE(SoGLPolygonOffsetElement);

SoGLPolygonOffsetElement::~SoGLPolygonOffsetElement()
{
}

void
SoGLPolygonOffsetElement::initClass()
{
   SO_ELEMENT_INIT_CLASS(SoGLPolygonOffsetElement, inherited);
}

void
SoGLPolygonOffsetElement::init(SoState *state)
{
   inherited::init(state);
   
   _copiedFromParent= FALSE;
   
   // Save the state.
   _state = state;

   _currentstyles       = (Style)0;
   _currentoffsetfactor = 1.0f;
   _currentoffsetunits  = 1.0f;
}

void
SoGLPolygonOffsetElement::push(SoState *state)
{
   const SoGLPolygonOffsetElement *prevElt = (const SoGLPolygonOffsetElement*)getNextInStack();

   _offsetfactor = prevElt->_offsetfactor;
   _offsetunits  = prevElt->_offsetunits;
   _style        = prevElt->_style;
   _active       = prevElt->_active;
   
   _currentstyles= prevElt->_currentstyles;
   _currentoffsetfactor= prevElt->_currentoffsetfactor;
   _currentoffsetunits= prevElt->_currentoffsetunits;
   
   _copiedFromParent= TRUE;
   _state= state;
}

void
SoGLPolygonOffsetElement::pop(SoState *state, const SoElement *childElt)
{
   // Since popping this element has GL side effects, make sure any
   // open caches capture it.  We may not send any GL commands, but
   // the cache dependency must exist even if we don't send any GL
   // commands, because if the element changes, the _lack_ of GL
   // commands here is a bug (remember, GL commands issued here are
   // put inside the cache).
   capture(state);
   _copiedFromParent = FALSE;
   
   // If the previous element didn't have the same value...
   const SoGLPolygonOffsetElement *child = (const SoGLPolygonOffsetElement*)childElt;

   _currentstyles       = child->_currentstyles;
   _currentoffsetfactor = child->_currentoffsetfactor;
   _currentoffsetunits  = child->_currentoffsetunits;

   if(*this != *child)
      send();
}

void
SoGLPolygonOffsetElement::setElt(float factor, float units, Style styles, SbBool on)
{
   // Optimization:  on push, we copy the value from the previous
   // element.  If the element is set to the same value, we don't
   // bother sending it, but do add a cache dependency on the
   // previous element.

   if(   _style        != styles
      || _active       != on
      || _offsetfactor != factor
      || _offsetunits  != units
   ) {
       inherited::setElt(factor, units, styles, on);
       send();
       _copiedFromParent = FALSE;
   }
   else if(_copiedFromParent) {
       SoGLPolygonOffsetElement *parent = (SoGLPolygonOffsetElement *)getNextInStack();
       parent->capture(_state);
   }
}

void
SoGLPolygonOffsetElement::send()
{
   if(_active) {
      if(_style & FILLED) {
         if(!(_currentstyles & FILLED))
            glEnable(GL_POLYGON_OFFSET_FILL);
      }
      else {
         if(_currentstyles & FILLED)
            glDisable(GL_POLYGON_OFFSET_FILL);
      }
      if(_style & LINES) {
         if(!(_currentstyles & LINES))
            glEnable(GL_POLYGON_OFFSET_LINE);
      }
      else {
         if(_currentstyles & LINES)
            glDisable(GL_POLYGON_OFFSET_LINE);
      }
      if(_style & POINTS) {
         if(!(_currentstyles & POINTS))
            glEnable(GL_POLYGON_OFFSET_POINT);
      }
      else {
         if(_currentstyles & POINTS)
            glDisable(GL_POLYGON_OFFSET_POINT);
      }

      glPolygonOffset(_offsetfactor, _offsetunits);

      _currentstyles = _style;
   }
   else { // ! active
      if(_currentstyles & FILLED)
         glDisable(GL_POLYGON_OFFSET_FILL);
      if(_currentstyles & LINES)
         glDisable(GL_POLYGON_OFFSET_LINE);
      if(_currentstyles & POINTS)
         glDisable(GL_POLYGON_OFFSET_POINT);

      _currentstyles = (Style)0;
   }  

   // update current offset values before returning
   _currentoffsetfactor = _offsetfactor;
   _currentoffsetunits  = _offsetunits;
}

int
operator ==(const SoGLPolygonOffsetElement &e1, const SoGLPolygonOffsetElement &e2)
{
   return(e1._style               == e2._style
       && e1._active              == e2._active
       && e1._offsetfactor        == e2._offsetfactor
       && e1._offsetunits         == e2._offsetunits

       && e1._currentstyles       == e2._currentstyles
       && e1._currentoffsetfactor == e2._currentoffsetfactor
       && e1._currentoffsetunits  == e2._currentoffsetunits);
}
