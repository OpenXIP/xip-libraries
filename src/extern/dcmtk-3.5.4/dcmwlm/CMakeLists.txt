# Modified by Sylvain Jaume <sylvain.jaume@siemens.com> 2008

project(dcmwlm)

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
  include/dcmtk/dcmwlm/wlds.h
  include/dcmtk/dcmwlm/wldsfs.h
  include/dcmtk/dcmwlm/wlfsim.h
  include/dcmtk/dcmwlm/wlmactmg.h
  include/dcmtk/dcmwlm/wltypdef.h)

#--------------------------------------------------------------------
# Defines the source files
#
set(SOURCES
  libsrc/wlds.cxx
	libsrc/wldsfs.cxx
	libsrc/wlfsim.cxx
	libsrc/wlmactmg.cxx)

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