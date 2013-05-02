# Copyright Siemens Corporate Research Inc. 2007
# Author Sylvain Jaume <sylvain.jaume@siemens.com>

project(coregl)

#--------------------------------------------------------------------
# Define the header files
#
set(HEADERS
  SoXipBindTextures.h
  SoXipBlendFunc.h
  SoXipBufferMask.h
  SoXipClearBuffer.h
  SoXipClearFbo.h
  SoXipClipPlaneKit.h
  SoXipCube.h
  SoXipDecomposeMFInt32.h
  SoXipDecomposeMFMatrix.h
  SoXipDepthTest.h
  SoXipDrawClipPlane.h
  SoXipFbo.h
  SoXipFboAttachColor.h
  SoXipFboAttachColor3D.h
  SoXipFboAttachDepth.h
  SoXipFboAttachDepth3D.h
  SoXipFramebufferGroup.h
  SoXipGetCameraProperties.h
  SoXipGLSLComponentProgram.h
  SoXipGLSLLoadComponents.h
  SoXipGLSLPrograms.h
  SoXipGLSLUniformGroup.h
  SoXipGLSLUseProgram.h
  SoXipGLStringMarker.h
  SoXipLoadShaders.h
  SoXipLogGLState.h
  SoXipLutTexture.h
  SoXipOpenGLError.h
  SoXipPingPong.h
  SoXipPingPongFlip.h
  SoXipTextureUnit.h
  SoXipTransparentGeometryRenderer.h
  SoXipUniformVariable.h)

#--------------------------------------------------------------------
# Define the source files
#
set(SOURCES
  FramebufferObject.cpp
  gpgpuContext.cpp
  ShaderComponentLibrary.cpp
  ShaderEngine.cpp
  ShaderProgramManager.cpp
  ShaderSourceComponent.cpp
  SoXipBindTextures.cpp
  SoXipBlendFunc.cpp
  SoXipBlendFuncElement.cpp
  SoXipBufferMask.cpp
  SoXipBufferMaskElement.cpp
  SoXipCaptureImage.cpp
  SoXipClearBuffer.cpp
  SoXipClearFbo.cpp
  SoXipClipPlaneKit.cpp
  SoXipCube.cpp
  SoXipDecomposeMFInt32.cpp
  SoXipDecomposeMFMatrix.cpp
  SoXipDepthTest.cpp
  SoXipDepthTestElement.cpp
  SoXipDrawBuffersElement.cpp
  SoXipDrawClipPlane.cpp
  SoXipDrawImage.cpp
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
  SoXipGetCameraProperties.cpp
  SoXipGetTransform.cpp
  SoXipGlowElement.cpp
  SoXipGLSLComponentProgram.cpp
  SoXipGLSLLoadComponents.cpp
  SoXipGLSLPrograms.cpp
  SoXipGLSLShaderProgramElement.cpp
  SoXipGLSLUniformGroup.cpp
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
# Define the compiler flags
#
if(WIN32)
  add_definitions(-DXIPIVCOREGL_EXPORTS)
else(WIN32)
  add_definitions(-DHAVE_CONFIG_H)
endif(WIN32)

#--------------------------------------------------------------------
# Define the include directories
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
# Compile the library
#
if(BUILD_SHARED_LIBS)
  add_library(xipivcoregl SHARED ${HEADERS} ${SOURCES})
else(BUILD_SHARED_LIBS)
  add_library(xipivcoregl STATIC ${HEADERS} ${SOURCES})
endif(BUILD_SHARED_LIBS)

set_target_properties(xipivcoregl
  PROPERTIES VERSION ${XIP_VERSION_STRING}
  SOVERSION ${XIP_VERSION_STRING})

#--------------------------------------------------------------------
# Link the library
#
target_link_libraries(xipivcoregl
  ${XIP_CORE_LIBRARY}
  ${OPENGL_LIBRARIES}
  ${GLEW_LIBRARIES}
)

add_dependencies(xipivcoregl xipivcore)
	
#--------------------------------------------------------------------
# Install the library
#
install(TARGETS xipivcoregl
  RUNTIME DESTINATION bin/release CONFIGURATIONS Release
  ARCHIVE DESTINATION lib/release CONFIGURATIONS Release
  LIBRARY DESTINATION lib/release CONFIGURATIONS Release
  BUNDLE  DESTINATION lib/release CONFIGURATIONS Release)

install(TARGETS xipivcoregl
  RUNTIME DESTINATION bin/debug   CONFIGURATIONS Debug
  ARCHIVE DESTINATION lib/debug   CONFIGURATIONS Debug
  LIBRARY DESTINATION lib/debug   CONFIGURATIONS Debug
  BUNDLE  DESTINATION lib/debug   CONFIGURATIONS Debug)

if(WIN32)
  install(FILES ${LIBRARY_OUTPUT_PATH}/debug/xipivcoregl${CMAKE_DEBUG_POSTFIX}.pdb
    DESTINATION bin/debug CONFIGURATIONS Debug)
endif(WIN32)
