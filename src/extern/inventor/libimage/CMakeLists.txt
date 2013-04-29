# Sylvain Jaume 2008

project(image)

#
# Definitions.
#
if(WIN32)
  add_definitions(-DINVENTOR_EXPORTS -D__SGIOIV_BUILD_DLL)
endif(WIN32)

#
# Header file.
#
set(HEADERS
  image.h)

#
# Source files.
#
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

#
# Archive creation.
#
add_library(image STATIC ${HEADERS} ${SOURCES})
