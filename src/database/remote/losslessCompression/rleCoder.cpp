#include <xip/inventor/remote/losslessCompression/rleCoder.h>
#include <xip/inventor/remote/losslessCompression/functions.h>

rleCoder::rleCoder()
{
	cpuID = functions::CPU();
}

void rleCoder::isRepeatedWrite( unsigned char *outDst, unsigned int *outputPosition,
    unsigned char mark, unsigned char sym, unsigned int cnt )
{
    unsigned int i, idx;

    idx = *outputPosition;
    if( cnt <= 3 )
    {
        if( sym == mark )
        {
            outDst[ idx ++ ] = mark;
            outDst[ idx ++ ] = cnt-1;
        }
        else
        {
            for( i = 0; i < cnt; ++ i )
            {
                outDst[ idx ++ ] = sym;
            }
        }
    }
    else
    {
        outDst[ idx ++ ] = mark;
        cnt--;
        if( cnt >= 128 )
        {
            outDst[ idx ++ ] = (cnt >> 8) | 128;
        }
        outDst[ idx ++ ] = cnt & 255;
        outDst[ idx ++ ] = sym;
    }
    *outputPosition = idx;
}

void rleCoder::isNotRepeatedWrite( unsigned char *outDst, unsigned int *outputPosition,
			unsigned char mark, unsigned char sym )
		{
			unsigned int idx = *outputPosition;

			if( sym == mark )
				{
					outDst[ idx ++ ] = mark;
					outDst[ idx ++ ] = 0;
				}
				else
				{
					outDst[ idx ++ ] = sym;
				}
				*outputPosition = idx;
		};




int rleCoder::RLE_C( unsigned char *inSrc, unsigned int inputSize, unsigned char *outDst)
{
    unsigned char bA, bB, mark;
    unsigned int  inputPosition, outputPosition, cnt, histo[ 256 ];

    if( inputSize < 1 )
    {
        return 0;
    }

    // Create histogram of the input stream
	createHistogram( inSrc, histo, inputSize );

	// Finds the marker that is going to be used with the repeated symbols.
	mark = findTheMarker( histo );

    outDst[ 0 ] = mark;
    outputPosition = 1;

    bA = inSrc[ 0 ];
    inputPosition = 1;
    cnt = 1;

    // is the size at least equal to 2 ?
    if( inputSize >= 2 )
    {
        bB = inSrc[ inputPosition ++ ];
        cnt = 2;

		// start of compression
        do
        {
            //repeated
			if( bA == bB )
            {
				// sequence of repeated symbols
                while( (inputPosition < inputSize) && (bA == bB) && (cnt < 32768) )
                {
                    bB = inSrc[ inputPosition ++ ];
                    ++ cnt;
                }

                if( bA != bB )
				{
                    isRepeatedWrite( outDst, &outputPosition, mark, bA, cnt-1 );
                    bA = bB;
                    cnt = 1;
                }
				else
				{
                    isRepeatedWrite( outDst, &outputPosition, mark, bA, cnt );
                    if( inputPosition < inputSize )
                    {
                        bA = inSrc[ inputPosition ++ ];
                        cnt = 1;
                    }
                    else
                    {
                        cnt = 0;
                    }
                }
           }
            else // non repeated
            {
                isNotRepeatedWrite( outDst, &outputPosition, mark, bA );
                bA = bB;
                cnt = 1;
            }

			// the input source is not finished
            if( inputPosition < inputSize )
            {
                bB = inSrc[ inputPosition ++ ];
                cnt = 2;
            }
        }
        while( (inputPosition < inputSize) || (cnt >= 2) );
    }

	// Last, non repeated, symbol
    if( cnt == 1 )
        isNotRepeatedWrite( outDst, &outputPosition, mark, bA );

    return outputPosition;
}



void rleCoder::RLE_U( unsigned char *inSrc, unsigned int inputSize, unsigned char *outDst)
{
    unsigned char mark, sym;
    unsigned int  inputPosition, outputPosition, cnt, i;

	// extract the marker from the compressed input stream
    inputPosition = 0;
    mark = inSrc[ inputPosition ++ ];

    // decompression loop
    outputPosition = 0;

	if( cpuID >= 1)
	{
		__m64* pIn =(__m64*)0;
		_mm_empty(); // emms
		do
		{
			sym = inSrc[ inputPosition ++ ];

			// found a marker
			if( sym == mark )
			{
				cnt = inSrc[ inputPosition ++ ];

				if( cnt <= 2 ) // marker repetition
				{
 					for( i = 0; (i <= cnt);  )
					{
						if((cnt - i) >= 8)
						{
							pIn = (__m64*) &outDst[outputPosition];
							*pIn = _mm_set_pi8(mark,mark,mark,mark,mark,mark,mark,mark);
							outputPosition += 8;
							i += 8;
						}
						else
						{
							outDst[ outputPosition ++ ] = mark;
							i++;
						}
					}
				}
				else
				{
					if( cnt & 128 )
						cnt = inSrc[ inputPosition ++ ] + ((cnt & 127) << 8);

					sym = inSrc[ inputPosition ++ ];

 					for( i = 0; (i <= cnt);  )
					{
						if((cnt - i) >= 8)
						{
							pIn = (__m64*) &outDst[outputPosition];
							*pIn = _mm_set_pi8(sym,sym,sym,sym,sym,sym,sym,sym);
							outputPosition += 8;
							i += 8;
						}
						else
						{
							outDst[ outputPosition ++ ] = sym;
							i++;
						}
					}
				}
			}
			else // copy as is
			{
				 outDst[ outputPosition ++ ] = sym;
			}
		}
		while( inputPosition < inputSize );
		_mm_empty(); // emms
	}
	else // does not use MMX registers
	{
		do
		{
			sym = inSrc[ inputPosition ++ ];
			if( sym == mark )
			{
				cnt = inSrc[ inputPosition ++ ];
				if( cnt <= 2 )
					outputPosition = isRepeated(outDst, outputPosition, mark, cnt);
				else
				{
					if( cnt & 128 )
						cnt = counter(cnt, inSrc[ inputPosition ++ ]);

					sym = inSrc[ inputPosition ++ ];
					outputPosition = isNotRepeated(outDst, outputPosition, sym, cnt);
				}
			}
			else
				outDst[ outputPosition ++ ] = sym;
		}
		while( inputPosition < inputSize );
	}
}
