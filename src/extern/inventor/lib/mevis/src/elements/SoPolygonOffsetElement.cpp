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

#include <Inventor/elements/SoPolygonOffsetElement.h>

SO_ELEMENT_SOURCE(SoPolygonOffsetElement);

SoPolygonOffsetElement::~SoPolygonOffsetElement()
{
}

void
SoPolygonOffsetElement::initClass()
{
   SO_ELEMENT_INIT_CLASS(SoPolygonOffsetElement, inherited);
}

void
SoPolygonOffsetElement::init(SoState * state)
{
   SoPolygonOffsetElement::getDefault(_offsetfactor, _offsetunits, _style, _active);
}

void
SoPolygonOffsetElement::set(SoState *state, SoNode *node, float factor, float units, Style styles, SbBool on)
{
   SoPolygonOffsetElement *elem = (SoPolygonOffsetElement *)SoReplacedElement::getElement(state, classStackIndex, node);
   
   if(elem != NULL)
      elem->setElt(factor, units, styles, on);
}

void
SoPolygonOffsetElement::get(SoState *state, float &factor, float &units, Style &styles, SbBool &on)
{
   const SoPolygonOffsetElement *elem= (const SoPolygonOffsetElement *)SoElement::getConstElement(state, classStackIndex);

   factor = elem->_offsetfactor;
   units  = elem->_offsetunits;
   styles = elem->_style;
   on     = elem->_active;
}

SoPolygonOffsetElement::Style
SoPolygonOffsetElement::getStyle(SoState *state)
{
   const SoPolygonOffsetElement *elem= (const SoPolygonOffsetElement *)SoElement::getConstElement(state, classStackIndex);

   return elem->_style;
}

void
SoPolygonOffsetElement::setElt(float factor, float units, Style styles, SbBool on)
{
   _offsetfactor = factor;
   _offsetunits  = units;
   _style        = styles;
   _active       = on;
}

void
SoPolygonOffsetElement::getDefault(float &factor, float &units, Style &styles, SbBool &on)
{
   factor = 0.0f;
   units  = 0.0f;
   styles = SoPolygonOffsetElement::FILLED;
   on     = FALSE;
}
