# Sylvain Jaume 2008
project(image)

if(WIN32)
  add_definitions(-DWIN32 -DINVENTOR_EXPORTS -D__SGIOIV_BUILD_DLL)
endif(WIN32)

set(HEADERS image.h)

set(SOURCES
  close.c
  filbuf.c
  flsbuf.c
  name.c
  open.c
  pix.c
  rdwr.c
  rle.c
  row.c)

add_library(image STATIC ${HEADERS} ${SOURCES})
