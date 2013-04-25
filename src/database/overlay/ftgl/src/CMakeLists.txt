# Sylvain Jaume 2007

project(ftgl)

add_definitions(-DFTGL_LIBRARY_STATIC)

include_directories(
  ${Xip_SOURCE_DIR}/src/extern/freetype-2.2.1/include
  ../include)

set(SOURCES
  FTBitmapGlyph.cpp
  FTCharmap.cpp
  FTContour.cpp
  FTExtrdGlyph.cpp
  FTFace.cpp
  FTFont.cpp
  FTGLBitmapFont.cpp
  FTGLExtrdFont.cpp
  FTGLOutlineFont.cpp
  FTGLPixmapFont.cpp
  FTGLPolygonFont.cpp
  FTGLTextureFont.cpp
  FTGlyph.cpp
  FTGlyphContainer.cpp
  FTLibrary.cpp
  FTOutlineGlyph.cpp
  FTPixmapGlyph.cpp
  FTPoint.cpp
  FTPolyGlyph.cpp
  FTSize.cpp
  FTTextureGlyph.cpp
  FTVectoriser.cpp)

add_library(ftgl STATIC ${SOURCES})
