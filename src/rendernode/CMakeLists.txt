# Sylvain Jaume 2007

project(rendernode)

#--------------------------------------------------------------------
# Header files.
#
set(HEADERS
  OIVUtils.h
  XipRenderAction.h
  XipRenderTask.h)

#--------------------------------------------------------------------
# Source files.
#
set(SOURCES
  OIVUtils.cpp
  RenderNode.cpp
  XipRenderAction.cpp
  XipRenderTask.cpp)

#--------------------------------------------------------------------
# Link directories.
#
link_directories(${Xip_BINARY_DIR}/out)

#--------------------------------------------------------------------
# Executable creation.
#
add_executable(rendernode ${HEADERS} ${SOURCES})

#--------------------------------------------------------------------
# Linking.
#
target_link_libraries(rendernode
  xipivcore
  stream
  losslessCompression
  jpegWrapper)

if(WIN32)
  target_link_libraries(rendernode
    wsock32)
endif(WIN32)

#--------------------------------------------------------------------
# Install.
#
install(TARGETS rendernode
  RUNTIME DESTINATION bin/debug CONFIGURATIONS Debug)

install(TARGETS rendernode
  RUNTIME DESTINATION bin/release CONFIGURATIONS Release)

if(WIN32)
  install(FILES ${EXECUTABLE_OUTPUT_PATH}/debug/rendernode.pdb
    DESTINATION bin/debug CONFIGURATIONS Debug)
endif(WIN32)
