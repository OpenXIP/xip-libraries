# Sylvain Jaume 2008
project(extern)

if(WIN32)
  add_subdirectory(freetype-2.2.1)
  add_subdirectory(jpeg-6b)
  add_subdirectory(libiconv-1.11)
endif(WIN32)

if(BUILD_INVENTOR)
  add_subdirectory(inventor)
endif(BUILD_INVENTOR)
