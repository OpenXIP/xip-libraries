# Modified by Sylvain Jaume <sylvain.jaume@siemens.com> 2008

project(dcmsign)

#--------------------------------------------------------------------
# Define the include directories
#
include_directories(
  include
  ../ofstd/include
  ../dcmdata/include
  ${ZLIB_INCDIR}
  ${OPENSSL_INCDIR})

#add_subdirectory(apps)

#--------------------------------------------------------------------
# Define the header files
#
set(HEADERS
  include/dcmtk/dcmsign/dcsignat.h
  include/dcmtk/dcmsign/sialgo.h
  include/dcmtk/dcmsign/siautopr.h
  include/dcmtk/dcmsign/sibrsapr.h
  include/dcmtk/dcmsign/sicert.h
  include/dcmtk/dcmsign/sicertvf.h
  include/dcmtk/dcmsign/sicreapr.h
  include/dcmtk/dcmsign/sidsa.h
  include/dcmtk/dcmsign/simac.h
  include/dcmtk/dcmsign/simaccon.h
  include/dcmtk/dcmsign/simd5.h
  include/dcmtk/dcmsign/sinullpr.h
  include/dcmtk/dcmsign/siprivat.h
  include/dcmtk/dcmsign/siripemd.h
  include/dcmtk/dcmsign/sirsa.h
  include/dcmtk/dcmsign/sisha1.h
  include/dcmtk/dcmsign/sisprof.h
  include/dcmtk/dcmsign/sitstamp.h
  include/dcmtk/dcmsign/sitypes.h)

#--------------------------------------------------------------------
# Define the sources
#
set(SOURCES
  libsrc/csignat.cxx
  libsrc/siautopr.cxx
  libsrc/sibrsapr.cxx
  libsrc/sicert.cxx
  libsrc/sicertvf.cxx
  libsrc/sicreapr.cxx
  libsrc/sidsa.cxx
  libsrc/simaccon.cxx
  libsrc/simd5.cxx
  libsrc/sinullpr.cxx
  libsrc/siprivat.cxx
  libsrc/siripemd.cxx
  libsrc/sirsa.cxx
  libsrc/sisha1.cxx
  libsrc/sisprof.cxx
  libsrc/sitypes.cxx)

#--------------------------------------------------------------------
# Compile the library dcmdsig <> PROJECT_NAME: dcmsign
#
add_library(dcmdsig STATIC ${HEADERS} ${SOURCES})

#--------------------------------------------------------------------
# Install the header files
#
install(FILES ${HEADERS}
  DESTINATION include/dcmtk/${PROJECT_NAME})

#--------------------------------------------------------------------
# Install the library
#
install(TARGETS dcmdsig
  RUNTIME DESTINATION bin/release CONFIGURATIONS Release
	ARCHIVE DESTINATION lib/release CONFIGURATIONS Release
  LIBRARY DESTINATION lib/release CONFIGURATIONS Release
  BUNDLE  DESTINATION lib/release CONFIGURATIONS Release)

install(TARGETS dcmdsig
  RUNTIME DESTINATION bin/debug CONFIGURATIONS Debug
  ARCHIVE DESTINATION lib/debug CONFIGURATIONS Debug
  LIBRARY DESTINATION lib/debug CONFIGURATIONS Debug
  BUNDLE  DESTINATION lib/debug CONFIGURATIONS Debug)

#if(WIN32)
#  install(FILES ${LIBRARY_OUTPUT_PATH}/debug/${PROJECT_NAME}${CMAKE_DEBUG_POSTFIX}.pdb
#    DESTINATION bin/debug CONFIGURATIONS Debug)
#endif(WIN32)