# Modified by Sylvain Jaume <sylvain.jaume@siemens.com> 2008

project(dcmsr)

#--------------------------------------------------------------------
# Define the include directories
#
include_directories(
  include
  ../ofstd/include
  ../dcmdata/include
  ${ZLIB_INCDIR}
  ${LIBXML_INCDIR})

#add_subdirectory(apps)
#add_subdirectory(tests)

#--------------------------------------------------------------------
# Define the header files
#
set(HEADERS
  include/dcmtk/dcmsr/dsrbascc.h
  include/dcmtk/dcmsr/dsrchecc.h
  include/dcmtk/dcmsr/dsrcitem.h
  include/dcmtk/dcmsr/dsrcodtn.h
  include/dcmtk/dcmsr/dsrcodvl.h
  include/dcmtk/dcmsr/dsrcomcc.h
  include/dcmtk/dcmsr/dsrcomtn.h
  include/dcmtk/dcmsr/dsrcomvl.h
  include/dcmtk/dcmsr/dsrcontn.h
  include/dcmtk/dcmsr/dsrcsidl.h
  include/dcmtk/dcmsr/dsrdattn.h
  include/dcmtk/dcmsr/dsrdoc.h
  include/dcmtk/dcmsr/dsrdoctn.h
  include/dcmtk/dcmsr/dsrdoctr.h
  include/dcmtk/dcmsr/dsrdtitn.h
  include/dcmtk/dcmsr/dsrenhcc.h
  include/dcmtk/dcmsr/dsrimgfr.h
  include/dcmtk/dcmsr/dsrimgtn.h
  include/dcmtk/dcmsr/dsrimgvl.h
  include/dcmtk/dcmsr/dsriodcc.h
  include/dcmtk/dcmsr/dsrkeycc.h
  include/dcmtk/dcmsr/dsrmamcc.h
  include/dcmtk/dcmsr/dsrnumtn.h
  include/dcmtk/dcmsr/dsrnumvl.h
  include/dcmtk/dcmsr/dsrpnmtn.h
  include/dcmtk/dcmsr/dsrprocc.h
  include/dcmtk/dcmsr/dsrreftn.h
  include/dcmtk/dcmsr/dsrscogr.h
  include/dcmtk/dcmsr/dsrscotn.h
  include/dcmtk/dcmsr/dsrscovl.h
  include/dcmtk/dcmsr/dsrsoprf.h
  include/dcmtk/dcmsr/dsrstrvl.h
  include/dcmtk/dcmsr/dsrtcodt.h
  include/dcmtk/dcmsr/dsrtcosp.h
  include/dcmtk/dcmsr/dsrtcotn.h
  include/dcmtk/dcmsr/dsrtcoto.h
  include/dcmtk/dcmsr/dsrtcovl.h
  include/dcmtk/dcmsr/dsrtextn.h
  include/dcmtk/dcmsr/dsrtimtn.h
  include/dcmtk/dcmsr/dsrtlist.h
  include/dcmtk/dcmsr/dsrtncsr.h
  include/dcmtk/dcmsr/dsrtree.h
  include/dcmtk/dcmsr/dsrtypes.h
  include/dcmtk/dcmsr/dsruidtn.h
  include/dcmtk/dcmsr/dsrwavch.h
  include/dcmtk/dcmsr/dsrwavtn.h
  include/dcmtk/dcmsr/dsrwavvl.h
  include/dcmtk/dcmsr/dsrxmlc.h
  include/dcmtk/dcmsr/dsrxmld.h
  include/dcmtk/dcmsr/dsrxrdcc.h)

#--------------------------------------------------------------------
# Define the source files
#
set(SOURCES
  libsrc/dsrbascc.cxx
  libsrc/dsrchecc.cxx
  libsrc/dsrcitem.cxx
  libsrc/dsrcodtn.cxx
  libsrc/dsrcodvl.cxx
  libsrc/dsrcomcc.cxx
  libsrc/dsrcomtn.cxx
  libsrc/dsrcomvl.cxx
  libsrc/dsrcontn.cxx
  libsrc/dsrcsidl.cxx
  libsrc/dsrdattn.cxx
  libsrc/dsrdoc.cxx
  libsrc/dsrdoctn.cxx
  libsrc/dsrdoctr.cxx
  libsrc/dsrdtitn.cxx
  libsrc/dsrenhcc.cxx
  libsrc/dsrimgfr.cxx
  libsrc/dsrimgtn.cxx
  libsrc/dsrimgvl.cxx
  libsrc/dsriodcc.cxx
  libsrc/dsrkeycc.cxx
  libsrc/dsrmamcc.cxx
  libsrc/dsrnumtn.cxx
  libsrc/dsrnumvl.cxx
  libsrc/dsrpnmtn.cxx
  libsrc/dsrprocc.cxx
  libsrc/dsrreftn.cxx
  libsrc/dsrscogr.cxx
  libsrc/dsrscotn.cxx
  libsrc/dsrscovl.cxx
  libsrc/dsrsoprf.cxx
  libsrc/dsrstrvl.cxx
  libsrc/dsrtcodt.cxx
  libsrc/dsrtcosp.cxx
  libsrc/dsrtcotn.cxx
  libsrc/dsrtcoto.cxx
  libsrc/dsrtcovl.cxx
  libsrc/dsrtextn.cxx
  libsrc/dsrtimtn.cxx
  libsrc/dsrtncsr.cxx
  libsrc/dsrtree.cxx
  libsrc/dsrtypes.cxx
  libsrc/dsruidtn.cxx
  libsrc/dsrwavch.cxx
  libsrc/dsrwavtn.cxx
  libsrc/dsrwavvl.cxx
  libsrc/dsrxmlc.cxx
  libsrc/dsrxmld.cxx
  libsrc/dsrxrdcc.cxx)

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
