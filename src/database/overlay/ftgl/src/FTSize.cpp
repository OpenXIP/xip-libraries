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
*/#include    "FTSize.h"


FTSize::FTSize()
:   ftFace(0),
    ftSize(0),
    size(0),
    xResolution(0),
    yResolution(0),
    err(0)
{}


FTSize::~FTSize()
{}


bool FTSize::CharSize( FT_Face* face, unsigned int pointSize, unsigned int xRes, unsigned int yRes )
{
    if( size != pointSize || xResolution != xRes || yResolution != yRes)
    {
        err = FT_Set_Char_Size( *face, 0L, pointSize * 64, xResolution, yResolution);

        if( !err)
        {
            ftFace = face;
            size = pointSize;
            xResolution = xRes;
            yResolution = yRes;
            ftSize = (*ftFace)->size;
        }
        else
        {
            ftFace = 0;
            size = 0;
            xResolution = 0;
            yResolution = 0;
            ftSize = 0;
        }
    }
    
    return !err;
}


unsigned int FTSize::CharSize() const
{
    return size;
}


float FTSize::Ascender() const
{
    return ftSize == 0 ? 0.0f : static_cast<float>( ftSize->metrics.ascender) / 64.0f;
}


float FTSize::Descender() const
{
    return ftSize == 0 ? 0.0f : static_cast<float>( ftSize->metrics.descender) / 64.0f;
}


float FTSize::Height() const
{
    if( 0 == ftSize)
    {
        return 0.0f;
    }
    
    if( FT_IS_SCALABLE((*ftFace)))
    {
        return ( (*ftFace)->bbox.yMax - (*ftFace)->bbox.yMin) * ( (float)ftSize->metrics.y_ppem / (float)(*ftFace)->units_per_EM);
    }
    else
    {
        return static_cast<float>( ftSize->metrics.height) / 64.0f;
    }
}


float FTSize::Width() const
{
    if( 0 == ftSize)
    {
        return 0.0f;
    }
    
    if( FT_IS_SCALABLE((*ftFace)))
    {
        return ( (*ftFace)->bbox.xMax - (*ftFace)->bbox.xMin) * ( static_cast<float>(ftSize->metrics.x_ppem) / static_cast<float>((*ftFace)->units_per_EM));
    }
    else
    {
        return static_cast<float>( ftSize->metrics.max_advance) / 64.0f;
    }
}


float FTSize::Underline() const
{
    return 0.0f;
}

