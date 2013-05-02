# Copyright Siemens Corporate Research Inc. 2007, 2009
# Author Sylvain Jaume <sylvain.jaume@siemens.com>


project(xipivrenderer)

#--------------------------------------------------------------------
# Define the header files
#
set(HEADERS
  SoXipMprRender.h
  SoXipSimpleVolumeRenderKit.h
  SoXipSlicer.h
  SoXipSlicerShader.h
  SoXipSlicerVolRender.h
  SoXipCPUMprRender.h
  SoXipGpuProcessTexture.h
  SoXipGpuProcessTextureKit.h
  SoXipDirectRaycaster.h
  SoXipClipPlanesShaderSetup.h
)

#--------------------------------------------------------------------
# Define the source files
#
set(SOURCES
  SoXipMprRender.cpp
  SoXipSimpleVolumeRenderKit.cpp
  SoXipSlicer.cpp
  SoXipSlicerShader.cpp
  SoXipSlicerVolRender.cpp
  SoXipCPUMprRender.cpp
  SoXipGpuProcessTexture.cpp
  SoXipGpuProcessTextureKit.cpp
  SoXipDirectRaycaster.cpp
  SoXipClipPlanesShaderSetup.cpp
  init.cpp
)

#--------------------------------------------------------------------
# Define the compiler flags
#
if(WIN32)
  add_definitions(-DXIPIVRENDERER_EXPORTS)
else(WIN32)
  add_definitions(-DHAVE_CONFIG_H)
endif(WIN32)

#--------------------------------------------------------------------
# Define the include directories
#
if(UNIX)
  # for generated config.h
  include_directories(${CMAKE_CURRENT_BINARY_DIR})
endif(UNIX)

#--------------------------------------------------------------------
# Compile the library
#
if(BUILD_SHARED_LIBS)
  add_library(xipivrenderer SHARED ${HEADERS} ${SOURCES})
else(BUILD_SHARED_LIBS)
  add_library(xipivrenderer STATIC ${HEADERS} ${SOURCES})
endif(BUILD_SHARED_LIBS)

set_target_properties(xipivrenderer
  PROPERTIES VERSION ${XIP_VERSION_STRING}
  SOVERSION ${XIP_VERSION_STRING})

#--------------------------------------------------------------------
# Link the library
#
target_link_libraries(xipivrenderer
	${XIP_COREGL_LIBRARY})

#--------------------------------------------------------------------
# Install the library
#
install(TARGETS xipivrenderer
  RUNTIME DESTINATION bin/release CONFIGURATIONS Release
  ARCHIVE DESTINATION lib/release CONFIGURATIONS Release
  LIBRARY DESTINATION lib/release CONFIGURATIONS Release
  BUNDLE  DESTINATION lib/release CONFIGURATIONS Release)

install(TARGETS xipivrenderer
  RUNTIME DESTINATION bin/debug   CONFIGURATIONS Debug
  ARCHIVE DESTINATION lib/debug   CONFIGURATIONS Debug
  LIBRARY DESTINATION lib/debug   CONFIGURATIONS Debug
  BUNDLE  DESTINATION lib/debug   CONFIGURATIONS Debug)

if(WIN32)
  install(FILES ${LIBRARY_OUTPUT_PATH}/debug/xipivrenderer${CMAKE_DEBUG_POSTFIX}.pdb
    DESTINATION bin/debug CONFIGURATIONS Debug)
endif(WIN32)
