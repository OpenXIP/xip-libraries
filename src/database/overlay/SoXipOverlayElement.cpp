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
#include <Inventor/errors/SoDebugError.h>
#include <xip/inventor/overlay/SoXipOverlayElement.h>
SO_ELEMENT_SOURCE( SoXipOverlayElement );

SoXipOverlayElement::~SoXipOverlayElement()
{

}

void
SoXipOverlayElement::initClass()
{
	SO_ELEMENT_INIT_CLASS( SoXipOverlayElement, SoReplacedElement );
}

void
SoXipOverlayElement::init( SoState* )
{
	
}

void
SoXipOverlayElement::set( SoState* state, SoNode* node, SbXipOverlaySettings settings )
{
    SoXipOverlayElement* elt = (SoXipOverlayElement *)
		getElement( state, classStackIndex, node );

    if( elt )
		elt->mSettings = settings;
}

SbBool
SoXipOverlayElement::matches( const SoElement* elt ) const
{
	return mSettings	== ((const SoXipOverlayElement *) elt)->mSettings;
}

SoElement*
SoXipOverlayElement::copyMatchInfo() const
{
    SoXipOverlayElement* result = (SoXipOverlayElement *) getTypeId().createInstance();

	if( result )
		result->mSettings = mSettings;

	return result;
}

SbXipOverlaySettings
SoXipOverlayElement::get( SoState* state )
{
	const SoXipOverlayElement* elt = (const SoXipOverlayElement*)
		getConstElement( state, classStackIndex );
	
	return elt ? elt->mSettings : SbXipOverlaySettings();
}

// SbXipOverlaySettings
// 
SbXipOverlaySettings::SbXipOverlaySettings()
{
	mLocation			= SoXipOverlayElement::FOCAL_PLANE;
	mShowAnnotation		= TRUE;
	mShowEnumeration	= TRUE;
}

SbXipOverlaySettings::SbXipOverlaySettings( int location, SbBool showAnnotation, SbBool showEnumeration )

	: mLocation( location )
	, mShowAnnotation( showAnnotation )
	, mShowEnumeration( showEnumeration )
{

}

SbXipOverlaySettings::SbXipOverlaySettings( const SbXipOverlaySettings& other)
{
	mLocation			= other.mLocation;
	mShowAnnotation		= other.mShowAnnotation;
	mShowEnumeration	= other.mShowEnumeration;
}

SbBool 
SbXipOverlaySettings::operator == ( const SbXipOverlaySettings& other) const
{
	return 
		mLocation			== other.mLocation &&
		mShowAnnotation		== other.mShowAnnotation &&
		mShowEnumeration	== other.mShowEnumeration;
}

SbBool 
SbXipOverlaySettings::getLocation() const
{
	return mLocation;
}

SbBool 
SbXipOverlaySettings::shouldDisplayAnnotation() const
{
	return mShowAnnotation;
}

SbBool 
SbXipOverlaySettings::shouldDisplayEnumeration() const
{
	return mShowEnumeration;
}
