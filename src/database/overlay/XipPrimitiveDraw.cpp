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
*	@file	XipPrimitiveDraw.cpp
*	@brief	Implementation of the XipPrimitiveDraw class
*	@author	Julien Gein
**/

#include <xip/inventor/overlay/XipPrimitiveDraw.h>
#include <Inventor/elements/SoLinePatternElement.h>
#include <Inventor/elements/SoLineWidthElement.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/nodes/SoGroup.h>
#include <Inventor/nodes/SoSwitch.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoTranslation.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoLineSet.h>
#include <Inventor/nodes/SoIndexedLineSet.h>
#include <Inventor/nodes/SoFaceSet.h>

XipPrimitiveDraw::XipPrimitiveDraw()
{
	m_Material = new SoMaterial;
	m_Material->ref();

	m_Offset = new SoTranslation;
	m_Offset->ref();
	
	m_Coords = new SoCoordinate3;
	m_Coords->ref();

	m_LineSet = new SoLineSet;
	m_LineSet->ref();

	m_IndexedLineSet = new SoIndexedLineSet;
	m_IndexedLineSet->ref();

	m_FaceSet = new SoFaceSet;
	m_FaceSet->ref();
}

XipPrimitiveDraw::~XipPrimitiveDraw()
{
	m_Material->ref();
	m_Offset->ref();
	m_Coords->ref();
	m_LineSet->ref();
	m_IndexedLineSet->ref();
	m_FaceSet->ref();
}

void 
XipPrimitiveDraw::quad( SoGLRenderAction* action, const SbVec3f& origin, const SbVec2f& size, const SbColor& color, const float alpha )
{
	action->getState()->push();
	{
		GLboolean depthTest;
		glGetBooleanv( GL_DEPTH_TEST, &depthTest );

		if( depthTest )
			glDisable( GL_DEPTH_TEST );

		m_Material->diffuseColor.setValue( color );
		m_Material->transparency.setValue( alpha );

		action->traverse( m_Material );

		m_Coords->point.setNum(4);
		m_Coords->point.set1Value( 0, origin );
		m_Coords->point.set1Value( 1, origin + SbVec3f( size[0],       0, 0 ) );
		m_Coords->point.set1Value( 2, origin + SbVec3f( size[0], size[1], 0 ) );
		m_Coords->point.set1Value( 3, origin + SbVec3f(       0, size[1], 0 ) );

		action->traverse( m_Coords );

		m_FaceSet->numVertices.setValue(4);

		action->traverse( m_FaceSet );		
		
		if( depthTest )
			glEnable( GL_DEPTH_TEST );
	}
	action->getState()->pop();
}

void 
XipPrimitiveDraw::triangle( SoGLRenderAction* action,
						    const SbVec3f& p1, const SbVec3f& p2, const SbVec3f& p3,
							const SbColor& color, const float alpha )
{
	action->getState()->push();
	{
		GLboolean depthTest;
		glGetBooleanv( GL_DEPTH_TEST, &depthTest );

		if( depthTest )
			glDisable( GL_DEPTH_TEST );

		m_Material->diffuseColor.setValue( color );
		m_Material->transparency.setValue( alpha );

		action->traverse( m_Material );

		m_Coords->point.setNum(3);
		m_Coords->point.set1Value( 0, p1 );
		m_Coords->point.set1Value( 1, p2 );
		m_Coords->point.set1Value( 2, p3 );

		action->traverse( m_Coords );

		m_FaceSet->numVertices.setValue(3);

		action->traverse( m_FaceSet );
		
		if( depthTest )
			glEnable( GL_DEPTH_TEST );
	}
	action->getState()->pop();
}

void 
XipPrimitiveDraw::line( SoGLRenderAction* action,
					    const SbVec3f& origin, const SbVec3f& dest, const SbColor& color, const float alpha,
						const float lineWidth, const unsigned short linePattern )
{
	action->getState()->push();
	{
		GLboolean depthTest;
		glGetBooleanv( GL_DEPTH_TEST, &depthTest );

		if( depthTest )
			glDisable( GL_DEPTH_TEST );

		SoLinePatternElement::set( action->getState(), linePattern );
		SoLineWidthElement::set( action->getState(), lineWidth );

		m_Material->diffuseColor.setValue( color );
		m_Material->transparency.setValue( alpha );

		action->traverse( m_Material );

		m_Coords->point.setNum(2);
		m_Coords->point.set1Value( 0, origin );
		m_Coords->point.set1Value( 1, dest );

		action->traverse( m_Coords );

		m_LineSet->numVertices.setValue(2);

		action->traverse( m_LineSet );

		if( depthTest )
			glEnable( GL_DEPTH_TEST );
	}
	action->getState()->pop();
}

void 
XipPrimitiveDraw::lines( SoGLRenderAction* action,
						 const SoMFVec3f& coord, const SbColor& color, const float alpha,
						 const float lineWidth, const unsigned short linePattern )
{
	action->getState()->push();
	{
		GLboolean depthTest;
		glGetBooleanv( GL_DEPTH_TEST, &depthTest );

		if( depthTest )
			glDisable( GL_DEPTH_TEST );

		SoLinePatternElement::set( action->getState(), linePattern );
		SoLineWidthElement::set( action->getState(), lineWidth );
		
		m_Material->diffuseColor.setValue( color );
		m_Material->transparency.setValue( alpha );

		action->traverse( m_Material );

		m_Coords->point.copyFrom( coord );

		action->traverse( m_Coords );

		m_LineSet->numVertices.setValue( coord.getNum() );

		action->traverse( m_LineSet );
		
		if( depthTest )
			glEnable( GL_DEPTH_TEST );
	}
	action->getState()->pop();
}

void 
XipPrimitiveDraw::lines( SoGLRenderAction* action,
						 const SoMFVec3f& coord, const SoMFInt32& index, const SbColor& color, const float alpha,
						 const float lineWidth, const unsigned short linePattern )
{
	action->getState()->push();
	{
		GLboolean depthTest;
		glGetBooleanv( GL_DEPTH_TEST, &depthTest );

		if( depthTest )
			glDisable( GL_DEPTH_TEST );

		SoLinePatternElement::set( action->getState(), linePattern );
		SoLineWidthElement::set( action->getState(), lineWidth );

		m_Material->diffuseColor.setValue( color );
		m_Material->transparency.setValue( alpha );

		action->traverse( m_Material );

		m_Coords->point.copyFrom( coord );

		action->traverse( m_Coords );

		m_IndexedLineSet->coordIndex.copyFrom( index );

		action->traverse( m_IndexedLineSet );

		if( depthTest )
			glEnable( GL_DEPTH_TEST );
	}
	action->getState()->pop();
}
