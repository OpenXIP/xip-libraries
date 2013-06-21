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
*/#include "FTGLBitmapFont.h"
#include "FTBitmapGlyph.h"


FTGLBitmapFont::FTGLBitmapFont( const char* fontFilePath)
:   FTFont( fontFilePath)
{}


FTGLBitmapFont::FTGLBitmapFont( const unsigned char *pBufferBytes, size_t bufferSizeInBytes)
:   FTFont( pBufferBytes, bufferSizeInBytes)
{}


FTGLBitmapFont::~FTGLBitmapFont()
{}


FTGlyph* FTGLBitmapFont::MakeGlyph( unsigned int g)
{
    FT_GlyphSlot ftGlyph = face.Glyph( g, FT_LOAD_DEFAULT);

    if( ftGlyph)
    {
        FTBitmapGlyph* tempGlyph = new FTBitmapGlyph( ftGlyph);
        return tempGlyph;
    }

    err = face.Error();
    return NULL;
}


void FTGLBitmapFont::Render( const char* string)
{   
    glPushClientAttrib( GL_CLIENT_PIXEL_STORE_BIT);
    glPushAttrib( GL_ENABLE_BIT);
    
    glPixelStorei( GL_UNPACK_LSB_FIRST, GL_FALSE);
    glPixelStorei( GL_UNPACK_ALIGNMENT, 1);

    glDisable( GL_BLEND);

    FTFont::Render( string);

    glPopAttrib();
    glPopClientAttrib();
}


void FTGLBitmapFont::Render( const wchar_t* string)
{   
    glPushClientAttrib( GL_CLIENT_PIXEL_STORE_BIT);
    glPushAttrib( GL_ENABLE_BIT);
    
    glPixelStorei( GL_UNPACK_LSB_FIRST, GL_FALSE);
    glPixelStorei( GL_UNPACK_ALIGNMENT, 1);
    
    glDisable( GL_BLEND);

    FTFont::Render( string);

    glPopAttrib();
    glPopClientAttrib();
}

