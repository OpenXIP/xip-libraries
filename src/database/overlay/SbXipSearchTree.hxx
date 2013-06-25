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
#ifndef SBXIPSEARCHTREE_HXX
#define SBXIPSEARCHTREE_HXX

#include <set>

template< typename T >
SbXipSearchTree<T>::SbXipSearchTree() : m_Root(0)
{

}

template< typename T >
SbXipSearchTree<T>::~SbXipSearchTree()
{
	clear();
}

template< typename T >
void
SbXipSearchTree<T>::clear()
{
	if( m_Root )
	{
		delete m_Root;
		m_Root = 0;
	}
}

template< typename T >
typename SbXipSearchTree<T>::Node*
SbXipSearchTree<T>::copy_rec( typename SbXipSearchTree<T>::Node* from )
{
	if( from )
	{
		Node* dest = new Node;
		dest->label = from->label;
		dest->userData = from->userData;
		dest->hasData = from->hasData;

		typename Node::NodeMap::iterator it;
		for( it = from->children.begin(); it != from->children.end(); ++ it )
		{
			dest->children[ it->first ] = copy_rec( it->second );
		}

		return dest;
	}

	return 0;
}

template< typename T >
void
SbXipSearchTree<T>::copy( const SbXipSearchTree<T>& rhs )
{
	clear();

	m_Root = copy_rec( rhs.m_Root );
}


template< typename T >
SbXipSearchTree<T>&
SbXipSearchTree<T>::operator = ( const SbXipSearchTree<T>& rhs )
{
	copy( rhs );

	return *this;
}

template< typename T >
void
SbXipSearchTree<T>::sortAlpha( const SoMFString& label, SoMFString& sortedLabel )
{
	typedef std::set< SbString, SbStringLessFunctor > SbStringSortSet;

	// Clear array
	sortedLabel.setNum(0);

	SbStringSortSet sset;
	for( int i = 0; i < label.getNum(); ++ i )
		sset.insert( label[i] );

	int index = 0;
	SbStringSortSet::iterator it;
	for( it = sset.begin(); it != sset.end(); ++ it )
	{
		sortedLabel.set1Value( index ++, *it );
	}
}

template< typename T >
void
SbXipSearchTree<T>::set_rec( const SoMFString& label, int index, Node* node, const T& userData )
{
	if( index == label.getNum() )
	{
		node->userData = userData;
		node->hasData = TRUE;
	}
	else
	{
		Node* child = node->children[ label[index] ];
		if( !child )
		{
			child = new Node;
			child->label = label[index];

			node->children[ label[index] ] = child;
		}

		set_rec( label, index + 1, child, userData );
	}
}

template< typename T >
void
SbXipSearchTree<T>::set( const SoMFString& label, const T& userData )
{
	if( label.getNum() )
	{
		// Sort the labels alphabetically (and remove dupplicates)
		SoMFString sortedLabels;
		sortAlpha( label, sortedLabels );

		// Make sure the search tree has a root
		if( !m_Root )
		{
			m_Root = new Node;
			m_Root->label = "";
		}

		set_rec( sortedLabels, 0, m_Root, userData );
	}
}

template< typename T >
SbBool
SbXipSearchTree<T>::get_rec( const SoMFString& label, int index, Node* node, T& userData )
{
	if( node->hasData )
		userData = node->userData;

	if( index < label.getNum() )
	{
		SbString currentLabel = label[index];

		Node* child = node->children[ label[index] ];
		if( child )
		{
			if( get_rec( label, index + 1, child, userData ) )
				return TRUE;
		}
		else
		{
			if( get_rec( label, index + 1, node, userData ) )
				return TRUE;
		}
	}

	return node->hasData;
}

template< typename T >
SbBool
SbXipSearchTree<T>::get( const SoMFString& label, T& userData )
{
	if( !m_Root )
		return FALSE;

	// Sort the labels alphabetically (and remove dupplicates)
	SoMFString sortedLabels;
	sortAlpha( label, sortedLabels );

	int index = 0;
	while( index < sortedLabels.getNum() )
	{
		if( get_rec( sortedLabels, index, m_Root, userData ) )
			return TRUE;
	
		++ index;
	}
	
	return FALSE;
}

#endif // SBXIPSEARCHTREE_HXX