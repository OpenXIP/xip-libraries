/*
Copyright (c) 2011, Siemens Corporate Research a Division of Siemens Corporation 
All rights reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/
#ifndef  _SO_SF_VARIANT_
#define  _SO_SF_VARIANT_

#include <Inventor/fields/SoSubField.h>
#include <xip/inventor/core/xipivcore.h>
#include <xip/inventor/core/SbVariant.h>

//////////////////////////////////////////////////////////////////////////////
//
//  SoSFVariant subclass of SoSField.
//
//////////////////////////////////////////////////////////////////////////////

class XIPIVCORE_API SoSFVariant : public SoSField 
{
    // Use standard field stuff
    SO_SFIELD_HEADER(SoSFVariant, SbVariant, const SbVariant&);

  SoINTERNAL public:
    static void		initClass();

	void			setValue();
	void			setFormat(const char *);
};

#endif /* _SO_SF_VARIANT_ */
