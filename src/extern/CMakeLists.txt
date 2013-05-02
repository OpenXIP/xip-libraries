# Copyright Siemens Corporate Research Inc. 2008
# Author Sylvain Jaume <sylvain.jaume@siemens.com>

project(extern)

#--------------------------------------------------------------------
# Recurse into subdirectories
#
if(WIN32)
  add_subdirectory(zlib-1.2.3)
  add_subdirectory(freetype-2.2.1)
  add_subdirectory(jpeg-6b)
  add_subdirectory(libiconv-1.11)
  add_subdirectory(EasyBMP-1.06)
  set(ICONV_LIBRARY libiconv)
else(WIN32)
  find_library(ICONV_LIBRARY libiconv.so
    ${XIP_SOURCE_DIR}/../libiconv-1.12/lib/.libs)
endif(WIN32)

if(HAS_DCMTK)
  add_subdirectory(dcmtk-3.5.4)
endif(HAS_DCMTK)

add_subdirectory(inventor)
