#ifndef _SORADLOSSLESS_H__
#define _SORADLOSSLESS_H__

#include "rleCoder.h"
#include "huffmanCoder.h"
#include "differentials.h"
#include "functions.h"


class losslessCompression: public functions, public rleCoder, public huffmanCoder,
					 public differentials
{

};
#endif /* _SORADLOSSLESS_H__ */
