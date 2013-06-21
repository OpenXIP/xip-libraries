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
*/#include "FTFace.h"
#include "FTCharmap.h"


FTCharmap::FTCharmap( FTFace* face)
:   ftFace( *(face->Face())),
    err(0)
{
    if( !ftFace->charmap)
    {
        err = FT_Set_Charmap( ftFace, ftFace->charmaps[0]);
    }
    
    ftEncoding = ftFace->charmap->encoding;
}


FTCharmap::~FTCharmap()
{
    charMap.clear();
}


bool FTCharmap::CharMap( FT_Encoding encoding)
{
    if( ftEncoding == encoding)
    {
        return true;
    }
    
    err = FT_Select_Charmap( ftFace, encoding );
    
    if( !err)
    {
        ftEncoding = encoding;
    }
    else
    {
        ftEncoding = ft_encoding_none;
    }
        
    charMap.clear();
    return !err;
}


unsigned int FTCharmap::GlyphListIndex( unsigned int characterCode )
{
    return charMap.find( characterCode);
}


unsigned int FTCharmap::FontIndex( unsigned int characterCode )
{
    return FT_Get_Char_Index( ftFace, characterCode);
}


void FTCharmap::InsertIndex( const unsigned int characterCode, const unsigned int containerIndex)
{
    charMap.insert( characterCode, containerIndex);
}
