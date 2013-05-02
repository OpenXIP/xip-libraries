# Copyright Siemens Corporate Research Inc. 2007
# Author Sylvain Jaume <sylvain.jaume@siemens.com>

project(remote)

#--------------------------------------------------------------------
# Define the header files
#
set(HEADERS
  PreciseTimer.h
  SoXipClientBase.h
  SoXipClientElement.h
  SoXipDataConnection.h
  SoXipRemoteClient.h
  SoXipRemoteLut.h
  SoXipRemoteVolRender.h
  SoXipRemoteVolume.h)

#--------------------------------------------------------------------
# Define the source files
#
set(SOURCES
  PreciseTimer.cpp
  SoXipClientBase.cpp
  SoXipDataConnection.cpp
  SoXipRemoteClient.cpp
  SoXipRemoteLut.cpp
  SoXipRemoteVolRender.cpp
  SoXipClientElement.cpp
  init.cpp)

#--------------------------------------------------------------------
# Build subprojects
#
add_subdirectory(stream)

if(NOT CMAKE_CL_64)
  add_subdirectory(jpegWrapper)
  add_subdirectory(losslessCompression)
endif(NOT CMAKE_CL_64)

#--------------------------------------------------------------------
# Define the compiler flags
#
add_definitions(-D_LIB -D__DISABLE_WARNING)

if(WIN32)
  add_definitions(-DXIPIVREMOTE_EXPORTS)
else(WIN32)
  add_definitions(-DHAVE_CONFIG_H)
endif(WIN32)

#--------------------------------------------------------------------
# Include directories
#
include_directories(../../extern/jpeg-6b)

if(UNIX)
  include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}) # for generated config.h
endif(UNIX)

#--------------------------------------------------------------------
# Compile the library
#
if(BUILD_SHARED_LIBS)
  add_library(xipivremote SHARED ${HEADERS} ${SOURCES})
else(BUILD_SHARED_LIBS)
  add_library(xipivremote STATIC ${HEADERS} ${SOURCES})
endif(BUILD_SHARED_LIBS)

set_target_properties(xipivremote
  PROPERTIES VERSION ${XIP_VERSION_STRING}
  SOVERSION ${XIP_VERSION_STRING})

#--------------------------------------------------------------------
# Link the library
#
target_link_libraries(xipivremote
  xipivcore
  jpegWrapper
  losslessCompression
  stream
  ${OPENGL_LIBRARIES})

if(WIN32)
  target_link_libraries(xipivremote
    ws2_32)
endif(WIN32)

#--------------------------------------------------------------------
# Install the library
#
install(TARGETS xipivremote
  RUNTIME DESTINATION bin/release CONFIGURATIONS Release
  ARCHIVE DESTINATION lib/release CONFIGURATIONS Release
  LIBRARY DESTINATION lib/release CONFIGURATIONS Release
  BUNDLE  DESTINATION lib/release CONFIGURATIONS Release)

install(TARGETS xipivremote
  RUNTIME DESTINATION bin/debug   CONFIGURATIONS Debug
  ARCHIVE DESTINATION lib/debug   CONFIGURATIONS Debug
  LIBRARY DESTINATION lib/debug   CONFIGURATIONS Debug
  BUNDLE  DESTINATION lib/debug   CONFIGURATIONS Debug)

if(WIN32)
  install(FILES ${LIBRARY_OUTPUT_PATH}/debug/xipivremoted.pdb
    DESTINATION bin/debug CONFIGURATIONS Debug)
endif(WIN32)
