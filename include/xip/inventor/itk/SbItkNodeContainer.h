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
#ifndef SB_ITK_NODE_CONTAINER_H_
# define SB_ITK_NODE_CONTAINER_H_

# include <vector>
# include <Inventor/SbLinear.h>

class SbItkNodeContainer
{
public:
	typedef std::vector< SbVec3f > SeedVector;
	typedef std::vector< float > LabelVector;

public:
	SbItkNodeContainer();
	SbItkNodeContainer( int numElements );

	bool operator ==( const SbItkNodeContainer& rhs ) const;

	bool isEmpty() const;
	int getNumElements() const;

	const SbVec3f& getSeed( int index ) const;
	float getLabel( int index ) const;

	void insertNode( int index, SbVec3f seed, float label );

	~SbItkNodeContainer();

protected:
	int mNumElements;
	SeedVector mSeeds;
	LabelVector mLabels;

};

#endif // SB_ITK_NODE_CONTAINER_H_
