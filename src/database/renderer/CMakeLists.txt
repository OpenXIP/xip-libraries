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
# Link directories.
#
link_directories(${Xip_BINARY_DIR}/out)

#--------------------------------------------------------------------
# Create library.
#
add_library(xipivrenderer SHARED ${SOURCES} ${HEADERS})

#--------------------------------------------------------------------
# Link library.
#
target_link_libraries(xipivrenderer
  xipivcore
  xipivcoregl
  ${OPENGL_LIBRARIES})

#--------------------------------------------------------------------
# Install.
#
install(TARGETS xipivrenderer
  RUNTIME DESTINATION bin/debug CONFIGURATIONS Debug
  ARCHIVE DESTINATION bin/debug CONFIGURATIONS Debug
  LIBRARY DESTINATION lib/debug CONFIGURATIONS Debug)

install(TARGETS xipivrenderer
  RUNTIME DESTINATION bin/release CONFIGURATIONS Release
  ARCHIVE DESTINATION bin/release CONFIGURATIONS Release
  LIBRARY DESTINATION lib/release CONFIGURATIONS Release)

if(WIN32)
  install(FILES ${LIBRARY_OUTPUT_PATH}/debug/xipivrenderer.pdb
    DESTINATION bin/debug CONFIGURATIONS Debug)
endif(WIN32)
