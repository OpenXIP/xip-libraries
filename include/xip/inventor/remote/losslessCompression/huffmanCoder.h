//----------------------------------------------------------------------------------
//! cpuID
/*!
// \file    SoRadRLE.h
// \author  Mathia Scucchiari
// \date    2007-05-21
//
// Huffman Encoder/Decoder 
// To compile the code with VC6 the Processor Pack 5 and the Service pack 5 are required
*/
//----------------------------------------------------------------------------------
#ifndef _SORADHUFFMAN_H__
#define _SORADHUFFMAN_H__

#include <emmintrin.h>
#include <xmmintrin.h>

#include "differentials.h"
#include "fastMemTransfer.h"

#define NODES 511

//stream
typedef struct 
{
	unsigned char *pByte;
	unsigned int  bitPos;
} sStream;


//symbol - used to describe the source
typedef struct 
{
	long symbol;        
	unsigned long cnt;
	unsigned long cd; 
	unsigned long bts;
} sSymbol;

//encoded node
typedef struct sEncNode encNode;

struct sEncNode 
{
	encNode *C1, *C2; //child A and child B
	int cnt;
	int symbol;
};

//decoded node
typedef struct sDecNode decNode;

struct sDecNode 
{
	decNode *C1, *C2; //child A and child B
	int symbol;
};


class huffmanCoder
{
	public:
 
		huffmanCoder::huffmanCoder();
		huffmanCoder::~huffmanCoder();

		/*!
		* \brief Compress a block of data using a Huffman coder.
		*
		* \param unsigned char *in  : source
		* \param unsigned int insize: size in byte
		* \param unsigned char *out : destination (compressed data)
		* \return unsigned char *buff: buffer used for the differential compression
		*/
		int huffmanCoder::HUFFMAN_C( unsigned char *in, unsigned int insize, unsigned char *out,
									 unsigned char *buff);
		
		/*!
		* \brief Compress a block of data using a Huffman coder.
		*
		* \param unsigned char *in  : source
		* \return unsigned int insize: size in byte
		* \param unsigned char *out : destination (compressed data)
		*/		
		int huffmanCoder::HUFFMAN_C( unsigned char *in,unsigned int insize, unsigned char *out);
        
		/*!
		* \brief Compress a block of data using a Huffman coder 
		* with a symmetric differential coding.
		*
		* \param unsigned char *in1 : source
		* \param unsigned int insize: size in byte
		* \param unsigned char *in2 : source
		* \param unsigned char *out : destination (compressed data)
		* \return unsigned char *buff: buffer used for the differential compression
		*/ 		
		int huffmanCoder::HUFFMAN_C_Diff( unsigned char *in1,const unsigned int insize, unsigned char *in2,
										  unsigned char *out, unsigned char *buff );
		
		/*!
		* \brief Uncompress a block of data using a Huffman
		*
		* \param unsigned char *in  : source (comressed data)
		* \param unsigned int insize: size in byte (compressed data)
		* \param unsigned char *out : destination (uncompressed data)
		* \param unsigned char *mprBuffer : mpr buffer
		* \return unsigned int outsize: size in byte (uncompressed data)
		*/		
		void huffmanCoder::HUFFMAN_U ( unsigned char *in, unsigned int insize,unsigned char *out,unsigned char *mprBuffer,
										 unsigned int outsize);

		/*!
		* \brief Uncompress a block of data using a Huffman
		*
		* \param unsigned char *in  : source (comressed data)
		* \param unsigned int insize: size in byte (compressed data)		
		* \param unsigned char *out : destination (uncompressed data)
		* \param unsigned int outsize: size in byte (uncompressed data)
		*/
		void huffmanCoder::HUFFMAN_U ( unsigned char *in, unsigned int insize,unsigned char *out,  
										unsigned int outsize);

		/*!
		* \brief Uncompress a block of data using a Huffman
		*
		* \param unsigned char *in1  : source (comressed data)
		* \param unsigned int insize: size in byte (compressed data)
		* \param unsigned char *in2  : source/destination (compressed/uncompressed data) 
		* \param unsigned int outsize: size in byte (uncompressed data)
		*/ 		
		void huffmanCoder::HUFFMAN_U_Diff( unsigned char *in1, unsigned int insize, unsigned char *in2, 
										   unsigned int outsize);

	
	private:
		/*!
		* Initialize the bitstream used by the compression algorithm.
		*/
		inline void huffmanCoder::init( sStream *stream, unsigned char *buf  )
		{
		  stream->pByte  = buf;
		  stream->bitPos   = 0;
		};
		
		/*!
		* Initialize the symbols before to create the histogram.
		*/
		inline void huffmanCoder::initSymbols( sSymbol *sym, unsigned int *k )
		{
 			sym->symbol = *k;
			sym->cnt  = 0;
			sym->cd   = 0;
			sym->bts   = 0;
		}

		/*! 
		* Increment the number of occurencies of a particular symbol
		*/
		inline void huffmanCoder::histogram( unsigned char *input, sSymbol *sym)
		{
		    sym[*input].cnt ++;
		};
		
		/*!
		* Increment the number of occurencies of a particular symbol 
		*				and copy that one in another buffer.
		*/
		inline void huffmanCoder::histogram( unsigned char *input, sSymbol *sym,
												    unsigned char *buffer )
		{
 			sym[*input].cnt ++;
			*buffer  = *input ;
		};

		/*!	
		* Increment the number of occurencies of a particular symbol 
		*		  and copy that one in another buffer.
		*		  It computes also the difference between two imput streams.
		*/
		inline void huffmanCoder::histogram( unsigned char *input1, unsigned char *input2, unsigned char *diff,
							   unsigned char *buffer, sSymbol *sym, unsigned int inputPosition )
		{
 				diff[inputPosition] =  input1[inputPosition] ^ input2[inputPosition];
				sym[diff[inputPosition]].cnt ++;
				buffer[inputPosition] =input2[inputPosition];
		};
		
		/*!	
		* \brief Used to sort the histogram.
		*/
		void huffmanCoder::shellSort(sSymbol *sym);
 
		/*!
		* \brief Set the node in input to 0.
		*/
		inline void huffmanCoder::setNode2Zero(encNode *node_1, encNode *node_2)
		{
			node_1->cnt = 0;
			node_2->cnt = 0;
		};

		/*!	
		* \brief Use to join two nodes into a new parent node
		*/
		inline void huffmanCoder::setRootChilds(encNode *root, encNode *node_1, encNode *node_2)
		{
			root->C1 = node_1;
			root->C2 = node_2;
			
			if(cpuID >= 3)
			{
				_mm_empty(); // emms 
				*(__m64*)&(root->cnt) = _mm_setr_pi32(node_1->cnt + node_2->cnt, -1);
				_mm_empty(); // emms 
			}
			else
			{
				root->cnt = node_1->cnt + node_2->cnt;
				root->symbol = -1;//not a byte
			}

		};

		/*!	
		* \brief Init the input node. Used during the recovery of the tree
		*/
		inline void huffmanCoder::initThisNode(decNode *this_node)
		{
			this_node->symbol = -1;
			if(cpuID >= 3)
			{
				_mm_empty(); // emms 
				*(__m64*)&(this_node->C1) = _mm_setr_pi32( 0,  0);
				_mm_empty(); // emms
			}
			else
			{
				this_node->C1 = (decNode *) 0;
				this_node->C2 = (decNode *) 0;
			}
		};

		/*!	
		* \brief Copy node pointers 
		*/
		inline void huffmanCoder::setNode(encNode *node_1, encNode *node_2)
		{
			node_1 = node_2;
		};

		/*!
		* \brief Init a leaf node
		*/
		inline void huffmanCoder::initLeafNodes( sSymbol *sym, encNode *nodes )
		{
			  nodes->C1 = (encNode *) 0;
			  nodes->C2 = (encNode *) 0;
			  if( cpuID >= 3 )
			  {
				  _mm_empty(); // emms 
				  *(__m64*)&(nodes->cnt) = _mm_setr_pi32(sym->cnt, sym->symbol);
				  _mm_empty(); // emms
			  }
			  else
			  {
				  nodes->symbol = sym->symbol;
				  nodes->cnt = sym->cnt;
			  }
		}

		/*!
		* \brief Generates a Huffman tree.
		*/
		void huffmanCoder::createTree( sSymbol *sym, sStream *stream );

		/*!
		* \brief Reads one bit from the input stream
		*/
		inline unsigned int huffmanCoder::bitRead( sStream *stream )
		{
		  unsigned int x = (*stream->pByte & (1<<(7-stream->bitPos))) ? 1 : 0;
		  stream->bitPos = (stream->bitPos+1) & 7;
		  if( !stream->bitPos ) ++ stream->pByte;

		  return x;
		};

		/*!
		* \brief Recovers the tree
		*/
		decNode * huffmanCoder::recoveryTree( decNode *nodes, sStream *stream, unsigned int *nodenum );

		/*!
		* \brief finds the index of a particular symbol and store code informations into the symbol array
		*/
		int huffmanCoder::indexSymbol( encNode *node, sSymbol *sym, unsigned int *code, unsigned int *bits);

		/*!
		* \briefStore the input symbol on the tree (used as a lookup table)
		*/
		void huffmanCoder::saveTree( encNode *node, sSymbol *sym, sStream *stream, 
									 unsigned int code, unsigned int bits );

		/*!
		* \brief Writes on the stream 
		*/
		void bitWrite( sStream *stream, unsigned int x, unsigned int bits );

		/*!
		* \brief Encode and save on the stream the input bit 
		*/
		inline void huffmanCoder::bitEncoding( sStream *stream, unsigned int *x, unsigned int *mask)
		{
			*stream->pByte = ((*x & *mask ? 1 : 0) << (7-stream->bitPos))+(*stream->pByte & (255^(1<<(7-stream->bitPos))));
			*x <<= 1;
			stream->bitPos = (stream->bitPos+1) & 7;
		};

		/*!
		* \brief Read a byte from the stream
		*/
		inline unsigned int huffmanCoder::byteRead( sStream *stream )
		{

		  unsigned int x = (*stream->pByte << stream->bitPos) | (stream->pByte[1] >> (8-stream->bitPos));
		  ++ stream->pByte;
		  return x;
		};

		/*!
		* \brief Write symbols on the stream
		*/
		void huffmanCoder::compressionWriteLoop( unsigned char *in, sSymbol *sym,
							   const unsigned int *insize, sStream *stream);

	private:
		int  huffmanCoder::cpuID;
		unsigned char *diffStream;
		int mInSize;
};
#endif /* _SORADHUFFMAN_H__ */
