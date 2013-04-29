# Sylvain Jaume 2007

project(coregl)
cmake_minimum_required(VERSION 2.6)

#--------------------------------------------------------------------
# Source files
#
set(SOURCES
  FramebufferObject.cpp
  gpgpuContext.cpp
  ShaderProgramManager.cpp
  SoXipBindTextures.cpp
  SoXipBufferMask.cpp
  SoXipBufferMaskElement.cpp
  SoXipCaptureImage.cpp
  SoXipClearBuffer.cpp
  SoXipClearFbo.cpp
  SoXipCube.cpp
  SoXipDecomposeMFInt32.cpp
  SoXipDepthTest.cpp
  SoXipDepthTestElement.cpp
  SoXipDrawBuffersElement.cpp
  SoXipDrawImage.cpp
  SoXipDrawQuad.cpp
  SoXipFbo.cpp
  SoXipFboAttachColor.cpp
  SoXipFboAttachColor3D.cpp
  SoXipFboAttachDepth.cpp
  SoXipFboAttachDepth3D.cpp
  SoXipFboElement.cpp
  SoXipFramebufferElement.cpp
  SoXipFramebufferFlip.cpp
  SoXipFramebufferGroup.cpp
  SoXipFrameRate.cpp
  SoXipGetTransform.cpp
  SoXipGlowElement.cpp
  SoXipGLSLPrograms.cpp
  SoXipGLSLShaderProgramElement.cpp
  SoXipGLSLUseProgram.cpp
  SoXipGLStringMarker.cpp
  SoXipLoadShaders.cpp
  SoXipLogGLState.cpp
  SoXipLutTexture.cpp
  SoXipMultiplyMatrices.cpp
  SoXipOffscreenRenderer.cpp
  SoXipOpenGLError.cpp
  SoXipPingPong.cpp
  SoXipPingPongFlip.cpp
  SoXipSetTransform.cpp
  SoXipShaderProgramElement.cpp
  SoXipTextureUnit.cpp
  SoXipTransparentGeometryRenderer.cpp
  SoXipUniformVariable.cpp
  init.cpp)	

#--------------------------------------------------------------------
# Definitions.
#
if(WIN32)
  add_definitions(-DXIPIVCOREGL_EXPORTS)
else(WIN32)
  add_definitions(-DHAVE_CONFIG_H)
endif(WIN32)


#--------------------------------------------------------------------
# Include directories.
#
if(UNIX)
  include_directories(
    /usr/include
    ${CMAKE_CURRENT_BINARY_DIR} # for generated config.h
    ${OIV_PATH}/include/
    ../../../include
    ../../extern/inventor/lib/mevis/include
    ../../extern/inventor/lib/xip/include
    .)
endif(UNIX)

#--------------------------------------------------------------------
# Create library
#
add_library(xipivcoregl SHARED ${SOURCES})
set(XIP_LIBRARIES ${XIP_LIBRARIES} xipivcoregl)

set_target_properties(xipivcoregl
  PROPERTIES VERSION ${XIP_VERSION_STRING}
  SOVERSION ${XIP_VERSION_STRING})

#--------------------------------------------------------------------
# Link library
#
target_link_libraries(xipivcoregl
  xipivcore
  ${OPENGL_LIBRARIES})

#--------------------------------------------------------------------
# Copy library to install directory
#
install(TARGETS xipivcoregl
  RUNTIME DESTINATION bin/debug CONFIGURATIONS Debug
  ARCHIVE DESTINATION lib/debug CONFIGURATIONS Debug
  LIBRARY DESTINATION lib/debug CONFIGURATIONS Debug)

install(TARGETS xipivcoregl
  RUNTIME DESTINATION bin/release CONFIGURATIONS Release
  ARCHIVE DESTINATION lib/release CONFIGURATIONS Release
  LIBRARY DESTINATION lib/release CONFIGURATIONS Release)

if(WIN32)
  install(FILES ${EXECUTABLE_OUTPUT_PATH}/debug/xipivcoregl.pdb
    DESTINATION bin/debug CONFIGURATIONS Debug)
endif(WIN32)
