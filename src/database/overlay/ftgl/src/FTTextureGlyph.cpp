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
*/#include    "FTTextureGlyph.h"

GLint FTTextureGlyph::activeTextureID = 0;
 
FTTextureGlyph::FTTextureGlyph( FT_GlyphSlot glyph, int id, int xOffset, int yOffset, GLsizei width, GLsizei height)
:   FTGlyph( glyph),
    destWidth(0),
    destHeight(0),
    glTextureID(id)
{
    err = FT_Render_Glyph( glyph, FT_RENDER_MODE_NORMAL);
    if( err || glyph->format != ft_glyph_format_bitmap)
    {
        return;
    }

    FT_Bitmap      bitmap = glyph->bitmap;

    destWidth  = bitmap.width;
    destHeight = bitmap.rows;
    
    if( destWidth && destHeight)
    {
        glPushClientAttrib( GL_CLIENT_PIXEL_STORE_BIT);
        glPixelStorei( GL_UNPACK_LSB_FIRST, GL_FALSE);
        glPixelStorei( GL_UNPACK_ROW_LENGTH, 0);
        glPixelStorei( GL_UNPACK_ALIGNMENT, 1);

        glBindTexture( GL_TEXTURE_2D, glTextureID);
        glTexSubImage2D( GL_TEXTURE_2D, 0, xOffset, yOffset, destWidth, destHeight, GL_ALPHA, GL_UNSIGNED_BYTE, bitmap.buffer);

        glPopClientAttrib();
    }


//      0    
//      +----+
//      |    |
//      |    |
//      |    |
//      +----+
//           1
    
    uv[0].X( static_cast<float>(xOffset) / static_cast<float>(width));
    uv[0].Y( static_cast<float>(yOffset) / static_cast<float>(height));
    uv[1].X( static_cast<float>( xOffset + destWidth) / static_cast<float>(width));
    uv[1].Y( static_cast<float>( yOffset + destHeight) / static_cast<float>(height));
    
    pos.X( glyph->bitmap_left);
    pos.Y( glyph->bitmap_top);
}


FTTextureGlyph::~FTTextureGlyph()
{}


const FTPoint& FTTextureGlyph::Render( const FTPoint& pen)
{
    if( activeTextureID != glTextureID)
    {
        glBindTexture( GL_TEXTURE_2D, (GLuint)glTextureID);
        activeTextureID = glTextureID;
    }
    
    glTranslatef( pen.X(),  pen.Y(), 0.0f);

    glBegin( GL_QUADS);
        glTexCoord2f( uv[0].X(), uv[0].Y());
        glVertex2f( pos.X(), pos.Y());

        glTexCoord2f( uv[0].X(), uv[1].Y());
        glVertex2f( pos.X(), pos.Y() - destHeight);

        glTexCoord2f( uv[1].X(), uv[1].Y());
        glVertex2f( destWidth + pos.X(), pos.Y() - destHeight);
        
        glTexCoord2f( uv[1].X(), uv[0].Y());
        glVertex2f( destWidth + pos.X(), pos.Y());
    glEnd();

    return advance;
}

