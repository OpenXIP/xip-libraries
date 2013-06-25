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
#ifndef SBXIPSEARCHTREE_H
#define SBXIPSEARCHTREE_H

#include <map>
#include <Inventor/fields/SoMFString.h>

struct SbStringLessFunctor : public std::binary_function< SbString, SbString, bool >
{
	bool operator()( const SbString& s1, const SbString& s2 ) const
	{
		return strcmp( s1.getString(), s2.getString() ) < 0;
	}
};

template< typename T >
class SbXipSearchTree
{
public:
	struct Node
	{
		typedef std::map< SbString, Node*, SbStringLessFunctor > NodeMap;

		Node() : hasData( FALSE )
		{}

		~Node()
		{
			typename NodeMap::iterator it;
			for( it = children.begin(); it != children.end(); ++ it )
				delete it->second;
		}

		SbBool		hasData;
		SbString	label;
		T   		userData;
		NodeMap		children;
	};

public:
	SbXipSearchTree();

	void clear();

	void copy( const SbXipSearchTree& rhs );

	SbXipSearchTree& operator = ( const SbXipSearchTree& rhs );

	void set( const SoMFString& label, const T& userData );

	SbBool get( const SoMFString& label, T& userData );

	~SbXipSearchTree();

protected:
	void sortAlpha( const SoMFString& label, SoMFString& sortedAlpha  );

	Node* copy_rec( Node* from );

	void set_rec( const SoMFString& label, int index, Node* node, const T& userData );

	SbBool get_rec( const SoMFString& label, int index, Node* node, T& userData );

	Node* m_Root;

};

/// Implementation file
#include "SbXipSearchTree.hxx"

#endif // SBXIPSEARCHTREE_H
