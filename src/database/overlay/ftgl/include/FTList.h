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
*/#ifndef    __FTList__
#define    __FTList__

#include "FTGL.h"

/**
* Provides a non-STL alternative to the STL list
 */
template <typename FT_LIST_ITEM_TYPE>
class FTGL_EXPORT FTList
{
    public:
        typedef FT_LIST_ITEM_TYPE value_type;
        typedef value_type& reference;
        typedef const value_type& const_reference;
        typedef size_t size_type;

        /**
         * Constructor
         */
        FTList()
        :   listSize(0),
            tail(0)
        {
            tail = NULL;
            head = new Node;
        }

        /**
         * Destructor
         */
        ~FTList()
        {
            Node* next;
            
            for( Node *walk = head; walk; walk = next)
            {
                next = walk->next;
                delete walk;
            }
        }

        /**
         * Get the number of items in the list
         */
        size_type size() const
        {
            return listSize;
        }

        /**
         * Add an item to the end of the list
         */
        void push_back( const value_type& item)
        {
            Node* node = new Node( item);
            
            if( head->next == NULL)
            {
                head->next = node;
            }

            if( tail)
            {
                tail->next = node;
            }
            tail = node;
            ++listSize;
        }
        
        /**
         * Get the item at the front of the list
         */
        reference front() const
        {
            return head->next->payload;
        }

        /**
         * Get the item at the end of the list
         */
        reference back() const
        {
            return tail->payload;
        }

    private:
        struct Node
        {
            Node()
            :	next(NULL)
            {}

            Node( const value_type& item)
            :	next(NULL)
            {
                payload = item;
            }
            
            Node* next;
            
            value_type payload;
        };
        
        size_type listSize;

        Node* head;
        Node* tail;
};

#endif // __FTList__

