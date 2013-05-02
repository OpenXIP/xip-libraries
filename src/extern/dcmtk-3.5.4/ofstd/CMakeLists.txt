# Modified by Sylvain Jaume <sylvain.jaume@siemens.com> 2008

project(ofstd)

#--------------------------------------------------------------------
# Define the header files
#
set(HEADERS
  include/dcmtk/ofstd/ofalgo.h
  include/dcmtk/ofstd/ofbmanip.h
  include/dcmtk/ofstd/ofcast.h
  include/dcmtk/ofstd/ofcmdln.h
  include/dcmtk/ofstd/ofconapp.h
  include/dcmtk/ofstd/ofcond.h
  include/dcmtk/ofstd/ofconfig.h
  include/dcmtk/ofstd/ofconsol.h
  include/dcmtk/ofstd/ofcrc32.h
  include/dcmtk/ofstd/ofdate.h
  include/dcmtk/ofstd/ofdatime.h
  include/dcmtk/ofstd/offname.h
  include/dcmtk/ofstd/ofglobal.h
  include/dcmtk/ofstd/oflist.h
  include/dcmtk/ofstd/oflogfil.h
  include/dcmtk/ofstd/ofoset.h
  include/dcmtk/ofstd/ofset.h
  include/dcmtk/ofstd/ofsetit.h
  include/dcmtk/ofstd/ofstack.h
  include/dcmtk/ofstd/ofstd.h
  include/dcmtk/ofstd/ofstdinc.h
  include/dcmtk/ofstd/ofstream.h
  include/dcmtk/ofstd/ofstring.h
  include/dcmtk/ofstd/ofthread.h
  include/dcmtk/ofstd/oftime.h
  include/dcmtk/ofstd/oftimer.h
  include/dcmtk/ofstd/oftypes.h
  include/dcmtk/ofstd/ofuoset.h)

#--------------------------------------------------------------------
# Define the source files
#
set(SOURCES
  libsrc/ofcmdln.cxx
  libsrc/ofconapp.cxx
  libsrc/ofcond.cxx
  libsrc/ofconfig.cxx
  libsrc/ofconsol.cxx
  libsrc/ofcrc32.cxx
  libsrc/ofdate.cxx
  libsrc/ofdatime.cxx
  libsrc/offname.cxx
  libsrc/oflist.cxx
  libsrc/oflogfil.cxx
  libsrc/ofstd.cxx
  libsrc/ofstring.cxx
  libsrc/ofthread.cxx
  libsrc/oftime.cxx)

#--------------------------------------------------------------------
# Define the include directories
#
include_directories(
  include
	)
	
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

#if(WIN32)
#  install(FILES ${LIBRARY_OUTPUT_PATH}/debug/${PROJECT_NAME}${CMAKE_DEBUG_POSTFIX}.pdb
#    DESTINATION bin/debug CONFIGURATIONS Debug)
#endif(WIN32)