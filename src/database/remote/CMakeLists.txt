# Sylvain Jaume 2007

project(remote)

#--------------------------------------------------------------------
# Header files.
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
# Source files.
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
# Subdirectories.
#
add_subdirectory(jpegWrapper)
add_subdirectory(losslessCompression)
add_subdirectory(stream)

#--------------------------------------------------------------------
# Definitions.
#
add_definitions(-DNDEBUG -D_LIB -D__DISABLE_WARNING -DXMD_H)

if(WIN32)
  add_definitions(-DXIPIVREMOTE_EXPORTS)
else(WIN32)
  add_definitions(-DHAVE_CONFIG_H)
endif(WIN32)

#--------------------------------------------------------------------
# Include directories.
#
include_directories(
  ${Xip_SOURCE_DIR}/include
  ../../extern/jpeg-6b)

if(UNIX)
  include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}) # for generated config.h
endif(UNIX)

#--------------------------------------------------------------------
# Library creation.
#
add_library(xipivremote SHARED ${HEADERS} ${SOURCES})

#--------------------------------------------------------------------
# Linking.
#
target_link_libraries(xipivremote
  xipivcore
  jpegWrapper
  losslessCompression
  stream
  opengl32)

if(WIN32)
  target_link_libraries(xipivremote
    ws2_32)
endif(WIN32)

#--------------------------------------------------------------------
# Install.
#
install(TARGETS xipivremote
  RUNTIME DESTINATION bin/debug CONFIGURATIONS Debug
  ARCHIVE DESTINATION bin/debug CONFIGURATIONS Debug
  LIBRARY DESTINATION lib/debug CONFIGURATIONS Debug)

install(TARGETS xipivremote
  RUNTIME DESTINATION bin/release CONFIGURATIONS Release
  ARCHIVE DESTINATION bin/release CONFIGURATIONS Release
  LIBRARY DESTINATION lib/release CONFIGURATIONS Release)

if(WIN32)
  install(FILES ${LIBRARY_OUTPUT_PATH}/debug/xipivremote.pdb
    DESTINATION bin/debug CONFIGURATIONS Debug)
endif(WIN32)
