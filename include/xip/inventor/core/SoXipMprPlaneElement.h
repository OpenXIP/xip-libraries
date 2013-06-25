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
*/#ifndef  SOXIPMPRPLANEELEMENT_H
#define  SOXIPMPRPLANEELEMENT_H

#include <Inventor/SbLinear.h>
#include <Inventor/SbColor.h>
#include <Inventor/SbPList.h>
#include <Inventor/elements/SoAccumulatedElement.h>
#include <xip/inventor/core/xipivcore.h>


class SoSFMatrix;
class SoSFVec3f;


// element for storing an MPR plane and optional field for manipulations
class XIPIVCORE_API SoXipMprPlaneElement : public SoAccumulatedElement 
{
	SO_ELEMENT_HEADER(SoXipMprPlaneElement);

public:
	static void initClass();

protected:
	virtual ~SoXipMprPlaneElement();

public:
	static void	add(SoState *state, SoNode *node, const SbMatrix &planeMatrix, const SbVec3f &center, const SbColor &color, int id, float stepSize, float thickness, SoSFMatrix *planeField, SoSFVec3f *centerField);
	static SoXipMprPlaneElement* getInstance(SoState *state);

	virtual void init(SoState *state);
	virtual void push(SoState *state);
	virtual void pop(SoState *state, const SoElement *prevTopElement);
	virtual int getNum() const;
	virtual void setMatrix(int index, const SbMatrix &matrix);
	virtual const SbMatrix& getMatrix(int index) const;
	virtual void setCenter(int index, const SbVec3f &center);
	virtual const SbVec3f& getCenter(int index) const;
	virtual SoSFMatrix*	getMatrixField(int index) const;
	virtual SoSFVec3f*	getCenterField(int index) const;
	virtual const SbColor& getColor(int index) const; 
	virtual const int getId(int index) const; 
	virtual const float getStepSize(int index) const; 
	virtual const float getThickness(int index) const;

protected:
	virtual void addToElt(const SbMatrix &planeMatrix, const SbVec3f &center, const SbColor &color, int id, float stepSize, float thickness, SoSFMatrix *planeField, SoSFVec3f *centerField);

	SbPList mMprPlanes;
	int	mStartIndex;
};

#endif // SOXIPMPRPLANEELEMENT_H

