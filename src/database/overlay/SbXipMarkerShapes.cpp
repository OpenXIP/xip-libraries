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
*	@file	SbXipMarkerShapes.cpp
*	@brief	Implementation of the SbXipMarkerShapes class
*	@author	Julien Gein
**/

#include <xip/inventor/overlay/SbXipMarkerShapes.h>

const char* SbXipMarkerShapes::mShapes[][3] = 
{
	{"QUAD",	"[ -1 -1 0, 1 -1 0, 1 1 0, -1 1 0 ]", "4"},
	{"CIRCLE",	"[ 1 0 0, 0.984808 0.173648 0, 0.939693 0.34202 0, 0.866025 0.5 0, 0.766044 0.642788 0, 0.642788 0.766044 0, 0.5 0.866025 0, 0.34202 0.939693 0, 0.173648 0.984808 0, 6.12303e-017 1 0, -0.173648 0.984808 0, -0.34202 0.939693 0, -0.5 0.866025 0, -0.642788 0.766044 0, -0.766044 0.642788 0, -0.866025 0.5 0, -0.939693 0.34202 0, -0.984808 0.173648 0, -1 1.22461e-016 0, -0.984808 -0.173648 0, -0.939693 -0.34202 0, -0.866025 -0.5 0, -0.766044 -0.642788 0, -0.642788 -0.766044 0, -0.5 -0.866025 0, -0.34202 -0.939693 0, -0.173648 -0.984808 0, -1.83691e-016 -1 0, 0.173648 -0.984808 0, 0.34202 -0.939693 0, 0.5 -0.866025 0, 0.642788 -0.766044 0, 0.766044 -0.642788 0, 0.866025 -0.5 0, 0.939693 -0.34202 0, 0.984808 -0.173648 0, 1 -2.44921e-016 0 ]", "36"},
	{"DIAMOND",	"[ -1 0 0, 0 -1 0, 1 0 0, 0 1 0 ]", "4"},
	{"TRIANGLE","[ -1 -1 0, 1 -1 0, 0 1 0 ]", "3"},
	{"CROSS",	"[ -1 -1 0, -0.8 -1 0, -0.2 -0.4 0, -0.2 -0.2 0, -0.4 -0.2 0, -1 -0.8 0, 1 -1 0, 1 -0.8 0, 0.4 -0.2 0, 0.2 -0.2 0, 0.2 -0.4 0, 0.8 -1 0, -1 1 0, -1 0.8 0, -0.4 0.2 0, -0.2 0.2 0, -0.2 0.4 0, -0.8 1 0, 1 1 0, 0.8 1 0, 0.2 0.4 0, 0.2 0.2 0, 0.4 0.2 0, 1 0.8 0 ]", "[ 6, 6, 6 ,6 ]"},

	{"NONE",	"[]", "0" }	// this must be the last entry in the list
};

int
SbXipMarkerShapes::getNum()
{
	int n = sizeof(mShapes) / sizeof(const char *) / 3;
	return (n - 1);
}

void
SbXipMarkerShapes::getVertices(int index, SoMFVec3f &vertices)
{
	if ((index < 0) || (index > getNum()))
		index = getNum();

	vertices.set(mShapes[index][1]);
}

void 
SbXipMarkerShapes::getNumVertices(int index, SoMFInt32 &numVertices)
{
	if ((index < 0) || (index > getNum()))
		index = getNum();

	numVertices.set(mShapes[index][2]);
}

const char* 
SbXipMarkerShapes::getName(int index)
{
	if ((index < 0) || (index > getNum()))
		index = getNum();

	return (mShapes[index][0]);
}
