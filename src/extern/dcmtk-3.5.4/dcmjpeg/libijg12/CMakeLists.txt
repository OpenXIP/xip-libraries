# Modified by Sylvain Jaume <sylvain.jaume@siemens.com> 2008

#--------------------------------------------------------------------
# Define the header files
#
set(HEADERS
jchuff12.h
jconfig12.h
jdct12.h
jdhuff12.h
jerror12.h
jinclude12.h
jlossls12.h
jlossy12.h
jmemsys12.h
jmorecfg12.h
jpegint12.h
jpeglib12.h
jversion12.h)

#--------------------------------------------------------------------
# Define the source files
#
set(SOURCES
jdcolor.c
jddctmgr.c
jddiffct.c
jdhuff.c
jdinput.c
jdlhuff.c
jdlossls.c
jdlossy.c
jdmainct.c
jdmarker.c
jdmaster.c
jdmerge.c
jdphuff.c
jdpostct.c
jdpred.c
jdsample.c
jdscale.c
jdshuff.c
jdtrans.c
jerror.c
jfdctflt.c
jfdctfst.c
jfdctint.c
jidctflt.c
jidctfst.c
jidctint.c
jidctred.c
jmemmgr.c
jmemnobs.c
jquant1.c
jquant2.c
jutils.c)				

#--------------------------------------------------------------------
# Compile the library
#
add_library(ijg12 STATIC ${HEADERS} ${SOURCES})
