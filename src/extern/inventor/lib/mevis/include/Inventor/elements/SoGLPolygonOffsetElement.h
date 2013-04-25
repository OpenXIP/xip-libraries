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
 * Copyright (C) 2004   MeVis Research GmbH
 *
 _______________________________________________________________________
 _______________  M E V I S   R E S E A R C H   G M B H  _______________
 |
 |   $Revision$
 |
 |   Description:
 |   ...
 |
 |   Author(s)      : Felix Ritter
 |
 _______________  M E V I S   R E S E A R C H   G M B H  _______________
 _______________________________________________________________________
 */

#ifndef _SO_GL_POLYGON_OFFSET_ELEMENT_
#define _SO_GL_POLYGON_OFFSET_ELEMENT_

#include <Inventor/system/SbSystem.h>
#include <Inventor/elements/SoPolygonOffsetElement.h>

SoEXTENDER class INVENTOR_API SoGLPolygonOffsetElement : public SoPolygonOffsetElement
{
   typedef SoPolygonOffsetElement inherited;

   SO_ELEMENT_HEADER(SoGLPolygonOffsetElement);

   public:

      // Initializes element
      virtual void	init(SoState *state);

      // Override push() method to copy state pointer and value of
      // previous element, to avoid sending GL commands if the elements
      // are the same.
      virtual void	push(SoState *state);

      // Override pop() method so side effects can occur in GL
      virtual void	pop(SoState *state, const SoElement *childElt);
      
      friend int operator ==(const SoGLPolygonOffsetElement &e1, const SoGLPolygonOffsetElement &e2);
      friend int operator !=(const SoGLPolygonOffsetElement &e1, const SoGLPolygonOffsetElement &e2) {
         return !(e1 == e2);
      }

   protected:

      virtual void	setElt(float factor, float units, Style styles, SbBool on);

      // Destructor.
      virtual		~SoGLPolygonOffsetElement();

   SoINTERNAL public:

      // Initializes the SoGLPolygonOffsetElement class.
      static void       initClass();

   private:

      // This variable is TRUE if the value in this element was copied
      // from our parent.  If set is called with the same value, no GL
      // commands have to be done-- it is as if this element doesn't
      // exist, and the parent's value is used.  Of course, a cache
      // dependency will have to be added in this case (if the parent
      // changes, the cache is not valid).  Set sets this flag to false.
      SbBool   _copiedFromParent;
      
      Style    _currentstyles;
      float    _currentoffsetfactor;
      float    _currentoffsetunits;

      // We need to store the state.
      SoState *_state;

      // Sends changes in element to GL
      void		send();
};

#endif  // _SO_GL_POLYGON_OFFSET_ELEMENT_
