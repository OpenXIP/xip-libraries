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

#include <xip/inventor/remote/losslessCompression/huffmanCoder.h>
#include <xip/inventor/remote/losslessCompression/functions.h>
#include <mmintrin.h>

/*
* Constructor
*/
huffmanCoder::huffmanCoder()
{
	this->cpuID = functions::CPU();
	diffStream = NULL;
	mInSize = 0;
}

/*
* Destructor
*/
huffmanCoder::~huffmanCoder()
{
	delete[] diffStream;
	diffStream = NULL;
}

void huffmanCoder::bitWrite( sStream *stream, unsigned int x, unsigned int bits )
{
  unsigned int mask = 1 << (bits-1);
  for( unsigned int cnt = 0; cnt < bits; ++ cnt )
  {
	bitEncoding(stream, &x, &mask);
	if( !stream->bitPos ){ ++ stream->pByte; }
  }
};

void huffmanCoder::compressionWriteLoop( unsigned char *in, sSymbol *sym,
										 const unsigned int *insize, sStream *stream )
{
  unsigned int symbol;
  for(unsigned int k = 0; k < *insize; ++ k )
  {
	symbol = in[k];
	bitWrite( stream, sym[symbol].cd, sym[symbol].bts );
  }
};


int huffmanCoder::indexSymbol( encNode *node, sSymbol *sym, unsigned int *code,
							   unsigned int *bits )
{
	unsigned int sym_idx;

	for(sym_idx = 0; sym_idx < 256; ++ sym_idx )
	{
		if( sym[sym_idx].symbol == node->symbol ) break;
	}
	if( cpuID >=3 )
	{
		_mm_empty(); // emms
		*((__m64*)(&(sym[sym_idx].cd))) = _mm_setr_pi32( *code,  *bits);
		_mm_empty(); // emms
	}
	else
	{
		sym[sym_idx].cd = *code;
		sym[sym_idx].bts = *bits;
	}

	return sym_idx;
};

void huffmanCoder::createTree( sSymbol *sym, sStream *stream )
{
  encNode nodes[NODES], *node_1, *node_2, *root;
  unsigned int k, num_symbols, nodes_left, next_idx;
  num_symbols = 0;

  for( k = 0; k < 256; ++ k )
  {
	if( sym[k].cnt > 0 )
	{
	  initLeafNodes( &sym[k], &nodes[num_symbols] );
	  num_symbols ++;
	}
  }


  root = (encNode *) 0;
  nodes_left = num_symbols;
  next_idx = num_symbols;
  while( nodes_left > 1 )
  {
    node_1 = (encNode *) 0;//Find the two lightest nodes
    node_2 = (encNode *) 0;


    for( k = 0; k < next_idx; ++ k )
    {
      if( nodes[k].cnt > 0 )
      {
        if( !node_1 || (nodes[k].cnt <= node_1->cnt) )
        {
			node_2 = node_1;
			node_1 = &nodes[k];
        }
        else if( !node_2 || (nodes[k].cnt <= node_2->cnt) )
        {
			node_2 = &nodes[k];
        }
      }
    }

	// join the nodes
	/*
		SMALL EXAMPLE:

		first creates the new fictive node,
		put the value to -1 (not a byte) the probabilities
		get it by adding the probabilities from the
		last two elements of the list,
		and then the pointers to the new elements
		just to the next position in the binary tree.
		And then following this fictive node put the two combined elements.
		Now increments the pointer of the list
		and then put here the new fictive node, just by adding the last probability
		and the current one, and putting the value -1.
		When there are only two elements in the probabilities list it's the end.

    		    root
    			/  \
   		  Child1    Child2
   		     |         |
   		    \ /       \ /
   		   node1     node2


		struct sEncNode
		{
			int cnt;		  // the probability of the byte
			int symbol;		  // if it's a byte or a node
			encNode *C1, *C2; // pointer to Child1 and pointer Child2
		};

		simple string as an example: 'acbacaa'
		Byte   Prob
		'a'     4
		'b'		1
		'c'		2

		sort them, the biggest first. (probability)
		Byte   Prob
		'a'     4
		'c'		2
		'b'		1

		Start to build the binary tree:
			Get the last two elements and combine them in another binary tree,
			first put both elements and the fictive new node pointing to them,
			then discard both of them, in the probabilities list, and put a new element,
			with the probabilities of both of them.
			(in the binary tree '&c' means a pointer to the node containing 'c')
		Byte   Prob  Join					Huffman Tree
		'a'     4							(-1(1),3,&c,&b)
		'c'		2	\ node1							  /  \
		'b'		1	/ (prob=> 2+1=3)	     ('c',2,0,0) ('b',1,0,0)

		Find the two lightest nodes

		Byte  Prob 	Join					Huffman Tree
		'a'    4 	\ node2					(-1(2),7,&-1(1),&a)
		node1  3    / (prob=> 4+3=7)				     /	\
										   (-1(1),3,&c,&b)  ('a',4,0,0)
													 /  \
										   ('c',2,0,0)  ('b',1,0,0)

	    The following is a detailed explanation

		Pointer to list					Pointer to tree
		Symbol Prob	 *C1  *C2			Symbol Prob	 *C1  *C2
		'a'		4    0	  0					  --empty--
		'c'     2    0    0
		'b'     1    0    0

	    The list of probabilities hold the byte itself, its probability and two pointers,
		this will make creating the binary tree easier.
		Assume the value of the pointer to the (start of the) binary tree is 00050000h.

		1- Copies both LAST elements

			Pointer to list					Pointer to tree
			Symbol Prob	 *C1  *C2			Symbol Prob	 *C1	*C2		Offset
			'a'		4    0	  0				'c'     2    0		0		50010h
			'c'     2    0    0				'b'     1    0		0		50000h
			'b'     1    0    0

		2- Creates the new fictive node

			Pointer to list					Pointer to tree
			Symbol Prob	 *C1  *C2			Symbol Prob	 *C1	*C2		Offset
			'a'		4    0	  0				-1      3	 50010h 50000h 	50020h
			'c'     2    0    0				'c'     2    0		0	    50010h
			'b'     1    0    0			    'b'     1    0		0		50000h


		Putting the correct offsets in the fictive node is only matter
		of subtracting to the current pointer (to the fictive node) the lenght
		of every element, that is 10h (16 bytes).

		3- Discards both elements and do a new one (fictive element)

			Pointer to list					Pointer to tree
			Symbol Prob	 *C1  *C2			Symbol Prob	 *C1	*C2		Offset
			'a'		4    0	  0				-1      3	 50010h 50000h 	50020h
			-1      3    0    0				'c'     2    0		0	    50010h
										    'b'     1    0		0		50000h

		4- First checks if there are at least two elements.
		   If there are more, repeat the same, starting at 1,
		   otherwise, there are only two elements left:

			 - Copy FIRST element

				Pointer to list					Pointer to tree
				Symbol Prob	 *C1  *C2			Symbol Prob	 *C1	*C2		Offset
				'a'		4    0	  0				'a'     4    0		0	    50030h
				-1      3    0    0				-1      3	 50010h 50000h 	50020h
												'c'     2    0		0	    50010h
												'b'     1    0		0		50000h

		5- Makes fictive pointer (this is the ROOT)

			  Pointer to tree
			  Symbol Prob	 *C1	*C2		Offset
			  -1	  7		50020h 	50030h 	50040h
			  'a'     4		0		0	    50030h
			  -1      3		50010h  50000h 	50020h
			  'c'     2		0		0	    50010h
			  'b'     1		0		0		50000h

		Save the pointer to the ROOT, is possible to scan the binary tree.

		At this point the binary tree is made.
		The bytes with the HIGHEST probability are at the top
		and those bytes with LOWEST probability are at the bottom of it.
		Now, the binary tree must be scanned:
		every time the scanning goes to the right is necessary to assign a 0 to the code,
		and when it goes to the left it assigns a 1.
		Once it arrives to a byte, it assignes that code to the byte.
		Pseudo code:

		    * Increments 'length'
		    * is a byte?
			* yes
				-> Assignes to this byte 'code' and 'length'
				-> end (go to return)
			* no
				-> Is right pointer valid? (no if 0)
				-> yes
					- shif to the left 'code' and or with 0
					- call bitEncoding
					- next pointer
				-> no
					- next pointer
				-> Is left pointer valid?  (next pointer)
				-> yes
					- shif to the left 'code' and or with 1
					- call bitEncoding
					- end (go to return)
				-> no
					- end (go to return)
			* return


		example:

					Pointer to tree
		  Symbol Prob	 *C1	*C2		Offset
		  -1	  7		50020h 	50030h 	50040h
		  'a'     4		0		0	    50030h
		  -1      3		50010h  50000h 	50020h
		  'c'     2		0		0	    50010h
		  'b'     1		0		0		50000h

			 (257(2),7,&257(1),&a)
                      /          \
		     (257,3,&c,&b)   ('a',4,0,0)
			        /    \
			('c',2,0,0) ('b',1,0,0)

		Code = 0b Length = 0

		* Read root.
		  Length=0.
		  Not a byte.
		  Right pointer valid.
		  Code=0b.
		  call again.

		* Read 'a'.
		  Length=1.
		  A byte.
		  Assign code 0b.
		  Return.

		* Reading root.
		  Left pointer valid.
		  Code=1.
		  call again.

		* Read fictive node.
		  length=2.
		  Not a byte.
		  Right pointer valid.
		  Code=10b.
		  call.

		* Read 'b'.
		  Byte.
		  Assign code 10b.
		  Return.

		* Read fictive node.
		  Left pointer valid.
		  Code=11b.
		  call again.

		* Read 'c'.
		  Byte.
		  Assign code 11b.
		  Return.

		* Return and end.


		The final codes are:

		Byte  	Code  	Length
		'a'		0b		1
		'b'		10b		2
		'c'		11b		2

		Bit stream
		Once you have this list you reescan the whole file and output for every byte its code with its length.
		Example for our string 'acbacaa':

		* Read 'a' -> Output 0b.
		* Read 'c' -> Output 11b.
		* Read 'b' -> Output 10b.
		* Read 'a' -> Output 0b.
		* Read 'c' -> Output 11b.
		* Read 'a' -> Output 0b.
		* Read 'a' -> Output 0b.

		this is the bit stream: 0111001100b.



    */
    root = &nodes[next_idx];

    setRootChilds(root, node_1, node_2);
	setNode2Zero(node_1, node_2);

	next_idx ++;
    nodes_left --;
  }

  if( root )
  {
    saveTree( root, sym, stream, 0, 0 );
  }
  else
  {
    root = &nodes[0];
    saveTree( root, sym, stream, 0, 1 );
  }
};

/*
* createTree()
*/

decNode * huffmanCoder::recoveryTree( decNode *nodes,
  sStream *stream, unsigned int *nodenum )
{
  decNode * this_node;

  this_node = &nodes[*nodenum];
  *nodenum = *nodenum + 1;

  initThisNode(this_node);

  if( bitRead( stream ) )
  {
    this_node->symbol = byteRead( stream );

    return this_node;
  }

  this_node->C1 = recoveryTree( nodes, stream, nodenum );
  this_node->C2 = recoveryTree( nodes, stream, nodenum );

  return this_node;
};


void huffmanCoder::saveTree( encNode *node, sSymbol *sym,
						 sStream *stream, unsigned int code, unsigned int bits )
{
  unsigned int sym_idx;

  if( node->symbol >= 0 ) // node or byte
  {
    bitWrite( stream, 1, 1 );
    bitWrite( stream, node->symbol, 8 );

	// symbol index and store the code informations into the symbol array
	sym_idx = indexSymbol( node, sym, &code, &bits );

    return;
  }
  else
  {
    bitWrite( stream, 0, 1 ); // no
  }

  saveTree( node->C1, sym, stream, (code<<1)+0, bits+1 );
  saveTree( node->C2, sym, stream, (code<<1)+1, bits+1 );
};

void huffmanCoder::shellSort(sSymbol *sym)
{
  int i, j, increment;
  sSymbol temp;

  increment = 3;

  while (increment > 0)
  {
	for (i=0; i < 255; i++)
	{
	  j = i;
	  temp = sym[i];
	  while ((j >= increment) && (sym[j-increment].symbol > temp.symbol))
	  {
		sym[j] = sym[j - increment];
		j = j - increment;
	  }
	  sym[j] = temp;
	}
	if (increment/2 != 0)
	  increment = increment/2;
	else if (increment == 1)
	  increment = 0;
	else
	  increment = 1;
  }
}
/************************* COMPRESSION *****************************/

int huffmanCoder::HUFFMAN_C( unsigned char *in, unsigned int insize,
							 unsigned char *out, unsigned char *buff )
{
  sSymbol       sym[256];
  sStream stream;
  unsigned int     k, total_bytes;

  init( &stream, out);

  if(cpuID >= 3)
	  for( k = 0; k < 256; ++ k )
		  *(__m128i*)&sym[k] = _mm_setr_epi32((int)k,0,0,0);
  else
	  for( k = 0; k < 256; ++ k )
		  initSymbols( &sym[k], &k );

  for( k = insize; k; -- k ) histogram( &in[k], sym, &buff[k]);

  createTree( sym, &stream );

  shellSort(sym);

  compressionWriteLoop(in, sym, &insize, &stream);

  total_bytes = (int)(stream.pByte - out);
  if( stream.bitPos > 0 )
  {
    ++ total_bytes;
  }
  return total_bytes;
};


int huffmanCoder::HUFFMAN_C( unsigned char *in, unsigned int insize, unsigned char *out )
{
  sSymbol       sym[256];
  sStream stream;
  unsigned int     k, total_bytes;

  init( &stream, out );

  if(cpuID >= 3)
	  for( k = 0; k < 256; ++ k )
		  *(__m128i*)&sym[k] = _mm_setr_epi32((int)k,0,0,0);
  else
	  for( k = 0; k < 256; ++ k )
		  initSymbols( &sym[k], &k);

  for( k = insize; k; -- k ) histogram( &in[k], sym );

  createTree( sym, &stream );

  shellSort(sym);

  compressionWriteLoop(in, sym, &insize, &stream);

  total_bytes = (int)(stream.pByte - out);

  if( stream.bitPos > 0 ) ++ total_bytes;

  return total_bytes;
};


int huffmanCoder::HUFFMAN_C_Diff( unsigned char *in1, const unsigned int insize,unsigned char *in2,
								  unsigned char *out, unsigned char *buff )
{
  sSymbol sym[256];
  sStream stream;
  unsigned int k, total_bytes;

  if (mInSize < (int)insize)
  {
	  delete[] diffStream;
	  diffStream = new unsigned char[insize];
	  mInSize = insize;
  }

  init( &stream, out );

  if( cpuID >= 3)
	  for( k = 0; k < 256; ++ k )
		  *(__m128i*)&sym[k] = _mm_setr_epi32((int)k,0,0,0);
  else
	  for( k = 0; k < 256; ++ k )
		  initSymbols( &sym[k], &k);

  unsigned int inputPosition = 0;

  if( cpuID >= 3)
  {

	  differentials::SymmetricDifference_EncDec(in1,in2, diffStream, insize);
	  fastMemTransfer::fastMemcopy(buff, in2, insize);

	  do
	  {
		sym[diffStream[inputPosition]].cnt ++;
		inputPosition ++;
	  }
	  while(inputPosition < insize);
  }
  else
  {

	  do
	  {
		histogram( in1, in2, diffStream, buff, sym, inputPosition );
		inputPosition ++;
	  }
	  while(inputPosition < insize);
  }

  createTree( sym, &stream );
  shellSort(sym);

  compressionWriteLoop( (unsigned char *)&diffStream[0], sym, &insize, &stream );

  total_bytes = (int)(stream.pByte - out);
  if( stream.bitPos > 0 )
  {
    ++ total_bytes;
  }

  return total_bytes;

};

/***************************** UNCOMPRESSION ********************************/


void huffmanCoder::HUFFMAN_U ( unsigned char *in, unsigned int insize, unsigned char *out,
							   unsigned char *mprBuffer, unsigned int outsize)
{
  decNode nodes[NODES], *root, *node;
  sStream  stream;
  unsigned int k, node_count;
  unsigned char *buf, *mprBuf;

  init( &stream, in );

  node_count = 0;
  root = recoveryTree( nodes, &stream, &node_count );

  buf = out;
  mprBuf = mprBuffer;
  for( k = 0; k < outsize; ++ k )
  {
    node = root;
    while( node->symbol < 0 )
    {
      if( bitRead( &stream ) )
        node = node->C2;
      else
        node = node->C1;
    }

     mprBuf[k] = (unsigned char) node->symbol;
	 buf[k] = (unsigned char) node->symbol;
  }
};


void huffmanCoder::HUFFMAN_U ( unsigned char *in, unsigned int insize,
							   unsigned char *out, unsigned int outsize)
{
  decNode nodes[NODES], *root, *node;
  sStream  stream;
  unsigned int      k, node_count;
  unsigned char     *buf;

  init( &stream, in );

  node_count = 0;
  root = recoveryTree( nodes, &stream, &node_count );

  buf = out;

  for( k = 0; k < outsize; ++ k )
  {
    node = root;
    while( node->symbol < 0 )
    {
      if( bitRead( &stream ) )
        node = node->C2;
      else
        node = node->C1;
    }
	 buf[k] = (unsigned char) node->symbol;
  }
};


void huffmanCoder::HUFFMAN_U_Diff( unsigned char *in1, unsigned int insize,
								   unsigned char *in2, unsigned int outsize)
{
  decNode nodes[NODES], *root, *node;
  sStream  stream;
  unsigned int      k, node_count;
  unsigned char     *dffStrm;

  init( &stream, in1 );

  node_count = 0;
  root = recoveryTree( nodes, &stream, &node_count );

  dffStrm = in2;
  for( k = 0; k < outsize; ++ k )
  {
    node = root;
    while( node->symbol < 0 )
    {
      if( bitRead( &stream ) )
        node = node->C2;
      else
        node = node->C1;
    }

	in2[k] = (unsigned char) node->symbol ^ *dffStrm++;

  }
};
