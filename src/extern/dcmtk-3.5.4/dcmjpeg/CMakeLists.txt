# Modified by Sylvain Jaume <sylvain.jaume@siemens.com> 2008

project(dcmjpeg)

#--------------------------------------------------------------------
# Recurse into subdirectories
#
add_subdirectory(libijg8)
add_subdirectory(libijg12)
add_subdirectory(libijg16)
#add_subdirectory(apps)

#--------------------------------------------------------------------
# Define the header files
#
set(HEADERS
  include/dcmtk/dcmjpeg/ddpiimpl.h
  include/dcmtk/dcmjpeg/dipijpeg.h
  include/dcmtk/dcmjpeg/djcodecd.h
  include/dcmtk/dcmjpeg/djcodece.h
  include/dcmtk/dcmjpeg/djcparam.h
  include/dcmtk/dcmjpeg/djdecabs.h
  include/dcmtk/dcmjpeg/djdecbas.h
  include/dcmtk/dcmjpeg/djdecext.h
  include/dcmtk/dcmjpeg/djdeclol.h
  include/dcmtk/dcmjpeg/djdecode.h
  include/dcmtk/dcmjpeg/djdecpro.h
  include/dcmtk/dcmjpeg/djdecsps.h
  include/dcmtk/dcmjpeg/djdecsv1.h
  include/dcmtk/dcmjpeg/djdijg12.h
  include/dcmtk/dcmjpeg/djdijg16.h
  include/dcmtk/dcmjpeg/djdijg8.h
  include/dcmtk/dcmjpeg/djeijg12.h
  include/dcmtk/dcmjpeg/djeijg16.h
  include/dcmtk/dcmjpeg/djeijg8.h
  include/dcmtk/dcmjpeg/djencabs.h
  include/dcmtk/dcmjpeg/djencbas.h
  include/dcmtk/dcmjpeg/djencext.h
  include/dcmtk/dcmjpeg/djenclol.h
  include/dcmtk/dcmjpeg/djencode.h
  include/dcmtk/dcmjpeg/djencpro.h
  include/dcmtk/dcmjpeg/djencsps.h
  include/dcmtk/dcmjpeg/djencsv1.h
  include/dcmtk/dcmjpeg/djrplol.h
  include/dcmtk/dcmjpeg/djrploss.h
  include/dcmtk/dcmjpeg/djutils.h)

#--------------------------------------------------------------------
# Define the sources
#
set(SOURCES
  libsrc/ddpiimpl.cxx
  libsrc/dipijpeg.cxx
  libsrc/djcodecd.cxx
  libsrc/djcodece.cxx
  libsrc/djcparam.cxx
  libsrc/djdecbas.cxx
  libsrc/djdecext.cxx
  libsrc/djdeclol.cxx
  libsrc/djdecode.cxx
  libsrc/djdecpro.cxx
  libsrc/djdecsps.cxx
  libsrc/djdecsv1.cxx
  libsrc/djdijg12.cxx
  libsrc/djdijg16.cxx
  libsrc/djdijg8.cxx
  libsrc/djeijg12.cxx
  libsrc/djeijg16.cxx
  libsrc/djeijg8.cxx
  libsrc/djencbas.cxx
  libsrc/djencext.cxx
  libsrc/djenclol.cxx
  libsrc/djencode.cxx
  libsrc/djencpro.cxx
  libsrc/djencsps.cxx
  libsrc/djencsv1.cxx
  libsrc/djrplol.cxx
  libsrc/djrploss.cxx
  libsrc/djutils.cxx)

#--------------------------------------------------------------------
# Define the include directories
#
include_directories(
  include
  ../ofstd/include
  ../dcmdata/include
  ../dcmimgle/include
  ../dcmimage/include
  libijg8
  libijg12
  libijg16
  ${ZLIB_INCDIR})

#--------------------------------------------------------------------
# Compile the library
#
add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCES})

#--------------------------------------------------------------------
# Install header files
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