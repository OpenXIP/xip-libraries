# Sylvain Jaume 2007

project(xipivrenderer)

set(SOURCES
  SoXipMprRender.cpp
  SoXipSlicer.cpp
  SoXipSlicerVolRender.cpp
  SoXipCPUMprRender.cpp
  init.cpp)
	
set(HEADERS
  SoXipMprRender.h
  SoXipSlicer.h
  SoXipSlicerVolRender.h
  SoXipCPUMprRender.h)

#--------------------------------------------------------------------
# Definitions.
#
if(WIN32)
  add_definitions(-DXIPIVRENDERER_EXPORTS)
else(WIN32)
  add_definitions(-DHAVE_CONFIG_H)
endif(WIN32)

#--------------------------------------------------------------------
# Include directories
#
if(UNIX)
  # for generated config.h
  include_directories(${CMAKE_CURRENT_BINARY_DIR})
endif(UNIX)

#--------------------------------------------------------------------
# Compile library
#
add_library(xipivrenderer SHARED ${SOURCES} ${HEADERS})

set_target_properties(xipivrenderer
  PROPERTIES VERSION ${XIP_VERSION_STRING}
  SOVERSION ${XIP_VERSION_STRING})

#--------------------------------------------------------------------
# Link library
#
target_link_libraries(xipivrenderer
  xipivcoregl)

#--------------------------------------------------------------------
# Install library
#
install(TARGETS xipivrenderer
  RUNTIME DESTINATION bin/debug CONFIGURATIONS Debug
  ARCHIVE DESTINATION lib/debug CONFIGURATIONS Debug
  LIBRARY DESTINATION lib/debug CONFIGURATIONS Debug)

install(TARGETS xipivrenderer
  RUNTIME DESTINATION bin/release CONFIGURATIONS Release
  ARCHIVE DESTINATION lib/release CONFIGURATIONS Release
  LIBRARY DESTINATION lib/release CONFIGURATIONS Release)

if(WIN32)
  install(FILES ${LIBRARY_OUTPUT_PATH}/debug/xipivrenderer.pdb
    DESTINATION bin/debug CONFIGURATIONS Debug)
endif(WIN32)
