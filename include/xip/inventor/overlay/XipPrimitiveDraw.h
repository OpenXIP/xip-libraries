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
/**
*	@file	XipPrimitiveDraw.h
*	@brief	Declaration of the XipPrimitiveDraw class
*	@author	Julien Gein
**/

#ifndef XIPPRIMITIVEDRAW_H
#define XIPPRIMITIVEDRAW_H

#include <Inventor/fields/SoMFVec3f.h>
#include <Inventor/fields/SoMFInt32.h>
#include <Inventor/SbLinear.h>
#include <Inventor/SbColor.h>

class SoGLRenderAction;
class SoGroup;
class SoSwitch;
class SoMaterial;
class SoTranslation;
class SoCoordinate3;
class SoLineSet;
class SoIndexedLineSet;
class SoFaceSet;

class XipPrimitiveDraw
{
public:
	XipPrimitiveDraw();

	~XipPrimitiveDraw();

	virtual void quad( SoGLRenderAction* action,
		const SbVec3f& origin, const SbVec2f& size, const SbColor& color, const float alpha = 0 );
	virtual void triangle( SoGLRenderAction* action,
		const SbVec3f& p1, const SbVec3f& p2, const SbVec3f& p3, const SbColor& color, const float alpha = 0 );
	virtual void line( SoGLRenderAction* action,		
		const SbVec3f& origin, const SbVec3f& dest, const SbColor& color, const float alpha = 0,
		const float lineWidth = 1, const unsigned short linePattern = 0xffff );
	virtual void lines( SoGLRenderAction* action,
		const SoMFVec3f& coord, const SbColor& color, const float alpha = 0,
		const float lineWidth = 1, const unsigned short linePattern = 0xffff );
	virtual void lines( SoGLRenderAction* action,
		const SoMFVec3f& coord, const SoMFInt32& index, const SbColor& color, const float alpha = 0,
		const float lineWidth = 1, const unsigned short linePattern = 0xffff );

protected:
	SoMaterial*			m_Material;
	SoTranslation*		m_Offset;
	SoCoordinate3*		m_Coords;
	SoLineSet*			m_LineSet;
	SoIndexedLineSet*	m_IndexedLineSet;
	SoFaceSet*			m_FaceSet;

};

#endif // XIPPRIMITIVEDRAW_H
