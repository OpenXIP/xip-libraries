# Modified by Sylvain Jaume <sylvain.jaume@siemens.com> 2008

project(dcmimage)

# declare include directories which hold for all subdirectories
include_directories(
  include
  ../ofstd/include
  ../dcmdata/include
  ../dcmimgle/include
  ${ZLIB_INCDIR}
  ${LIBTIFF_INCDIR}
  ${LIBPNG_INCDIR})

#add_subdirectory(apps)

#--------------------------------------------------------------------
# Define the header files
#
set(HEADERS
  include/dcmtk/dcmimage/diargimg.h
  include/dcmtk/dcmimage/diargpxt.h
  include/dcmtk/dcmimage/dicmyimg.h
  include/dcmtk/dcmimage/dicmypxt.h
  include/dcmtk/dcmimage/dicocpt.h
  include/dcmtk/dcmimage/dicoflt.h
  include/dcmtk/dcmimage/dicoimg.h
  include/dcmtk/dcmimage/dicomot.h
  include/dcmtk/dcmimage/dicoopx.h
  include/dcmtk/dcmimage/dicoopxt.h
  include/dcmtk/dcmimage/dicopx.h
  include/dcmtk/dcmimage/dicopxt.h
  include/dcmtk/dcmimage/dicorot.h
  include/dcmtk/dcmimage/dicosct.h
  include/dcmtk/dcmimage/dihsvimg.h
  include/dcmtk/dcmimage/dihsvpxt.h
  include/dcmtk/dcmimage/dipalimg.h
  include/dcmtk/dcmimage/dipalpxt.h
  include/dcmtk/dcmimage/dipipng.h
  include/dcmtk/dcmimage/dipitiff.h
  include/dcmtk/dcmimage/diqtcmap.h
  include/dcmtk/dcmimage/diqtctab.h
  include/dcmtk/dcmimage/diqtfs.h
  include/dcmtk/dcmimage/diqthash.h
  include/dcmtk/dcmimage/diqthitl.h
  include/dcmtk/dcmimage/diqthitm.h
  include/dcmtk/dcmimage/diqtid.h
  include/dcmtk/dcmimage/diqtpbox.h
  include/dcmtk/dcmimage/diqtpix.h
  include/dcmtk/dcmimage/diqtstab.h
  include/dcmtk/dcmimage/diqttype.h
  include/dcmtk/dcmimage/diquant.h
  include/dcmtk/dcmimage/diregist.h
  include/dcmtk/dcmimage/dirgbimg.h
  include/dcmtk/dcmimage/dirgbpxt.h
  include/dcmtk/dcmimage/diybrimg.h
  include/dcmtk/dcmimage/diybrpxt.h
  include/dcmtk/dcmimage/diyf2img.h
  include/dcmtk/dcmimage/diyf2pxt.h
  include/dcmtk/dcmimage/diyp2img.h
  include/dcmtk/dcmimage/diyp2pxt.h)

#--------------------------------------------------------------------
# Define the source files
#
set(SOURCES
  libsrc/diargimg.cxx
  libsrc/dicmyimg.cxx
  libsrc/dicoimg.cxx
  libsrc/dicoopx.cxx
  libsrc/dicopx.cxx
  libsrc/dihsvimg.cxx
  libsrc/dipalimg.cxx
  libsrc/dipipng.cxx
  libsrc/dipitiff.cxx
  libsrc/diqtctab.cxx
  libsrc/diqtfs.cxx
  libsrc/diqthash.cxx
  libsrc/diqthitl.cxx
  libsrc/diqtpbox.cxx
  libsrc/diquant.cxx
  libsrc/diregist.cxx
  libsrc/dirgbimg.cxx
  libsrc/diybrimg.cxx
  libsrc/diyf2img.cxx
  libsrc/diyp2img.cxx)

#--------------------------------------------------------------------
# Compile the library
#
add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCES})

#--------------------------------------------------------------------
# Install the header files
#
install(FILES ${HEADERS}
  DESTINATION include/dcmtk/${PROJECT_NAME})

#--------------------------------------------------------------------
# Install the library
#
install(TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION bin/release CONFIGURATIONS Release
	ARCHIVE DESTINATION lib/release CONFIGURATIONS Release
  LIBRARY DESTINATION lib/release CONFIGURATIONS Release
  BUNDLE  DESTINATION lib/release CONFIGURATIONS Release)

install(TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION bin/debug CONFIGURATIONS Debug
  ARCHIVE DESTINATION lib/debug CONFIGURATIONS Debug
  LIBRARY DESTINATION lib/debug CONFIGURATIONS Debug
  BUNDLE  DESTINATION lib/debug CONFIGURATIONS Debug)
