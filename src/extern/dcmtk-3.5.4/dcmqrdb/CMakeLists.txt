# Modified by Sylvain Jaume <sylvain.jaume@siemens.com> 2008

project(dcmqrdb)

#--------------------------------------------------------------------
# Define the include directories
#
include_directories(
  include
  ../ofstd/include
  ../dcmdata/include
  ../dcmnet/include
  ${ZLIB_INCDIR})

#add_subdirectory(apps)
#add_subdirectory(docs)

#--------------------------------------------------------------------
# Define the header files
#
set(HEADERS
  include/dcmtk/dcmqrdb/dcmqrcbf.h
  include/dcmtk/dcmqrdb/dcmqrcbg.h
  include/dcmtk/dcmqrdb/dcmqrcbm.h
  include/dcmtk/dcmqrdb/dcmqrcbs.h
  include/dcmtk/dcmqrdb/dcmqrcnf.h
  include/dcmtk/dcmqrdb/dcmqrdba.h
  include/dcmtk/dcmqrdb/dcmqrdbi.h
  include/dcmtk/dcmqrdb/dcmqrdbs.h
  include/dcmtk/dcmqrdb/dcmqridx.h
  include/dcmtk/dcmqrdb/dcmqropt.h
  include/dcmtk/dcmqrdb/dcmqrptb.h
  include/dcmtk/dcmqrdb/dcmqrsrv.h
  include/dcmtk/dcmqrdb/dcmqrtis.h)

#--------------------------------------------------------------------
# Define the sources
#
set(SOURCES
  libsrc/dcmqrcbf.cxx
  libsrc/dcmqrcbg.cxx
  libsrc/dcmqrcbm.cxx
  libsrc/dcmqrcbs.cxx
  libsrc/dcmqrcnf.cxx
  libsrc/dcmqrdbi.cxx
  libsrc/dcmqrdbs.cxx
  libsrc/dcmqropt.cxx
  libsrc/dcmqrptb.cxx
  libsrc/dcmqrsrv.cxx
  libsrc/dcmqrtis.cxx)

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

install(FILES etc/dcmqrscp.cfg DESTINATION doc)
