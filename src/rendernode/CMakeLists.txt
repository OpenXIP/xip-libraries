# Copyright Siemens Corporate Research Inc. 2007
# Author Sylvain Jaume <sylvain.jaume@siemens.com>

project(rendernode)

#--------------------------------------------------------------------
# Define the header files
#
set(HEADERS
  OIVUtils.h
  XipRenderAction.h
  XipRenderTask.h)

#--------------------------------------------------------------------
# Define the source files
#
set(SOURCES
  OIVUtils.cpp
  RenderNode.cpp
  XipRenderAction.cpp
  XipRenderTask.cpp)

#--------------------------------------------------------------------
# Compile the executable
#
add_executable(rendernode ${HEADERS} ${SOURCES})

set_target_properties(rendernode PROPERTIES DEBUG_POSTFIX d)

if(WIN32)
#set_target_properties(rendernode PROPERTIES LINK_FLAGS
#"/DELAYLOAD:xipivcore.dll")
endif(WIN32)

#--------------------------------------------------------------------
# Link the executable
#
target_link_libraries(rendernode
  xipivcore
  stream)

if(NOT CMAKE_CL_64)
  target_link_libraries(rendernode
    losslessCompression
    jpegWrapper)
endif(NOT CMAKE_CL_64)

if(WIN32)
  target_link_libraries(rendernode
    wsock32)
endif(WIN32)

#--------------------------------------------------------------------
# Install the executable
#
install(TARGETS rendernode
  RUNTIME DESTINATION bin/release CONFIGURATIONS Release)

install(TARGETS rendernode
  RUNTIME DESTINATION bin/debug   CONFIGURATIONS Debug)

if(WIN32)
  install(FILES ${EXECUTABLE_OUTPUT_PATH}/debug/rendernoded.pdb
    DESTINATION bin/debug CONFIGURATIONS Debug)
endif(WIN32)
