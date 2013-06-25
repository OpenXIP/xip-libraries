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
*/#include    <string>

#include "FTBitmapGlyph.h"

FTBitmapGlyph::FTBitmapGlyph( FT_GlyphSlot glyph)
:   FTGlyph( glyph),
    destWidth(0),
    destHeight(0),
    data(0)
{
    err = FT_Render_Glyph( glyph, FT_RENDER_MODE_MONO);
    if( err || ft_glyph_format_bitmap != glyph->format)
    {
        return;
    }

    FT_Bitmap bitmap = glyph->bitmap;

    unsigned int srcWidth = bitmap.width;
    unsigned int srcHeight = bitmap.rows;
    unsigned int srcPitch = bitmap.pitch;
    
    destWidth = srcWidth;
    destHeight = srcHeight;
    destPitch = srcPitch;    

    if( destWidth && destHeight)
    {
        data = new unsigned char[destPitch * destHeight];
        unsigned char* dest = data + (( destHeight - 1) * destPitch);

        unsigned char* src = bitmap.buffer;

        for( unsigned int y = 0; y < srcHeight; ++y)
        {
            memcpy( dest, src, srcPitch);
            dest -= destPitch;
            src += srcPitch;
        }
    }

    pos = FTPoint(glyph->bitmap_left, static_cast<int>(srcHeight) - glyph->bitmap_top, 0.0);
}


FTBitmapGlyph::~FTBitmapGlyph()
{
    delete [] data;
}


const FTPoint& FTBitmapGlyph::Render( const FTPoint& pen)
{
    glBitmap( 0, 0, 0.0f, 0.0f, pen.X() + pos.X(), pen.Y() - pos.Y(), (const GLubyte*)0 );
    
    if( data)
    {
        glPixelStorei( GL_UNPACK_ROW_LENGTH, destPitch * 8);
        glBitmap( destWidth, destHeight, 0.0f, 0.0, 0.0, 0.0, (const GLubyte*)data);
    }
    
    glBitmap( 0, 0, 0.0f, 0.0f, -pos.X(), pos.Y(), (const GLubyte*)0 );
    
    return advance;
}
