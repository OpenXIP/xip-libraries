# Copyright Siemens Corporate Research Inc. 2007
# Author Sylvain Jaume <sylvain.jaume@siemens.com>

project(ftgl)

#--------------------------------------------------------------------
# Define compiler flags
#
add_definitions(-DFTGL_LIBRARY_STATIC)

#--------------------------------------------------------------------
# Include directories
#
include_directories(
  include
  ../../../extern/freetype-2.2.1/include)

#--------------------------------------------------------------------
# Header files
#
set(HEADERS
  include/FTBBox.h
  include/FTBitmapGlyph.h
  include/FTCharToGlyphIndexMap.h
  include/FTCharmap.h
  include/FTContour.h
  include/FTExtrdGlyph.h
  include/FTFace.h
  include/FTFont.h
  include/FTGL.h
  include/FTGLBitmapFont.h
  include/FTGLExtrdFont.h
  include/FTGLOutlineFont.h
  include/FTGLPixmapFont.h
  include/FTGLPolygonFont.h
  include/FTGLTextureFont.h
  include/FTGlyph.h
  include/FTGlyphContainer.h
  include/FTLibrary.h
  include/FTList.h
  include/FTOutlineGlyph.h
  include/FTPixmapGlyph.h
  include/FTPoint.h
  include/FTPolyGlyph.h
  include/FTSize.h
  include/FTTextureGlyph.h
  include/FTVector.h
  include/FTVectoriser.h)

#--------------------------------------------------------------------
# Source files
#
set(SOURCES
  src/FTBitmapGlyph.cpp
  src/FTCharmap.cpp
  src/FTContour.cpp
  src/FTExtrdGlyph.cpp
  src/FTFace.cpp
  src/FTFont.cpp
  src/FTGLBitmapFont.cpp
  src/FTGLExtrdFont.cpp
  src/FTGLOutlineFont.cpp
  src/FTGLPixmapFont.cpp
  src/FTGLPolygonFont.cpp
  src/FTGLTextureFont.cpp
  src/FTGlyph.cpp
  src/FTGlyphContainer.cpp
  src/FTLibrary.cpp
  src/FTOutlineGlyph.cpp
  src/FTPixmapGlyph.cpp
  src/FTPoint.cpp
  src/FTPolyGlyph.cpp
  src/FTSize.cpp
  src/FTTextureGlyph.cpp
  src/FTVectoriser.cpp)

#--------------------------------------------------------------------
# Compile library
#
add_library(ftgl STATIC ${HEADERS} ${SOURCES})
