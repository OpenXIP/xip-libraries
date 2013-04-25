# Sylvain Jaume 2008

project(jpeg)

if(WIN32)
  add_definitions(-DUSE_MSDOS_MEMMGR -DNEED_FAR_POINTERS)
endif(WIN32)

if(APPLE)
  add_definitions(-DUSE_MAC_MEMMGR)
endif(APPLE)

set(HEADERS
  jchuff.h
  jdhuff.h
  jdct.h
  jerror.h
  jinclude.h
  jmemsys.h
  jmorecfg.h
  jpegint.h
  jpeglib.h
  jversion.h
  cdjpeg.h
  cderror.h
  transupp.h)

set(SOURCES
  jcapimin.c
  jcapistd.c
  jccoefct.c
  jccolor.c
  jcdctmgr.c
  jchuff.c
  jcinit.c
  jcmainct.c
  jcmarker.c
  jcmaster.c
  jcomapi.c
  jcparam.c
  jcphuff.c
  jcprepct.c
  jcsample.c
  jctrans.c
  jdapimin.c
  jdapistd.c
  jdatadst.c
  jdatasrc.c
  jdcoefct.c
  jdcolor.c
  jddctmgr.c
  jdhuff.c
  jdinput.c
  jdmainct.c
  jdmarker.c
  jdmaster.c
  jdmerge.c
  jdphuff.c
  jdpostct.c
  jdsample.c
  jdtrans.c
  jerror.c
  jfdctflt.c
  jfdctfst.c
  jfdctint.c
  jidctflt.c
  jidctfst.c
  jidctint.c
  jidctred.c
  jquant1.c
  jquant2.c
  jutils.c
  jmemmgr.c)

# memmgr back ends: compile only one of these into a working library
set(SYSDEPSOURCES
  #jmemansi.c
  #jmemname.c
  jmemnobs.c)

# FIXME: issue with 'far' pointers (see jmemdosa.asm)
if(WIN32)
#  set(SYSDEPSOURCES ${SYSDEPSOURCES} jmemdos.c)
endif(WIN32)

if(APPLE)
  set(SYSDEPSOURCES ${SYSDEPSOURCES} jmemmac.c)
endif(APPLE)

# source files: cjpeg/djpeg/jpegtran applications, also rdjpgcom/wrjpgcom
set(APPSOURCES
  cjpeg.c
  djpeg.c
  jpegtran.c
  rdjpgcom.c
  wrjpgcom.c
  cdjpeg.c
  rdcolmap.c
  rdswitch.c
  transupp.c
  rdppm.c
  wrppm.c
  rdgif.c
  wrgif.c
  rdtarga.c
  wrtarga.c
  rdbmp.c
  wrbmp.c
  rdrle.c
  wrrle.c)

add_library(jpeg STATIC ${HEADERS} ${SOURCES} ${SYSDEPSOURCES} ${APPSOURCES})
