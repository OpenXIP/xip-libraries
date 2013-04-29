# Sylvain Jaume 2007

project(core)

#--------------------------------------------------------------------
# OpenGL
#
find_package(OpenGL)

if(WIN32 AND OPENGL-NOTFOUND)
  set(OPENGL_LIBRARIES opengl32 glu32)
endif(WIN32 AND OPENGL-NOTFOUND)

#--------------------------------------------------------------------
# Source files
#
set(SOURCES
  SbVariant.cpp
  SbXipCoordinateTransform.cpp
  SbXipDirtyFieldList.cpp
  SbXipImage.cpp
  SbXipImageFile.cpp
  SbXipThread.cpp
  SbXipThreadMutex.cpp
  SoMFVariant.cpp
  SoSFVariant.cpp
  SoXipActiveViewportElement.cpp
  SoXipAnchor.cpp
  SoXipAutoScale.cpp
  SoXipBackground.cpp
  SoXipBoundingBox.cpp
  SoXipClipPlane.cpp
  SoXipClipPlaneElement.cpp
  SoXipComposeMFImage.cpp
  SoXipComposeVec6.cpp
  SoXipComposeVec6.h
  SoXipConvertMatrixToPlane.cpp
  SoXipConvertMFImageToSFImage.cpp
  SoXipConvertSFImageToMFImage.cpp
  SoXipConvertToEnum.cpp
  SoXipCursor.cpp
  SoXipData.cpp
  SoXipDataImage.cpp
  SoXipDataImageElement.cpp
  SoXipDecomposeMFImage.cpp
  SoXipDecomposeVec6.cpp
  SoXipDecomposeVec6.h
  SoXipDogEar.cpp
  SoXipExaminer.cpp
  SoXipExtractSlice.cpp
  SoXipGetImage.cpp
  SoXipImage.cpp
  SoXipImageAttributes.cpp
  SoXipImageExaminer.cpp
  SoXipImageExaminerBase.cpp
  SoXipImageOperation.cpp
  SoXipImageText.cpp
  SoXipImageTextElement.cpp
  SoXipIncrement.cpp
  SoXipIncrement.h
  SoXipIntersectionPlane.cpp
  SoXipKit.cpp
  SoXipLazyGroup.cpp
  SoXipLoadRaw.cpp
  SoXipLut.cpp
  SoXipLutElement.cpp
  SoXipMFData.cpp
  SoXipMFDataImage.cpp
  SoXipMouseToggle.cpp
  SoXipMprActive.cpp
  SoXipMprActiveElement.cpp
  SoXipMprAlign.cpp
  SoXipMprExaminer.cpp
  SoXipMprIntersectionLine.cpp
  SoXipMprIntersectionManip.cpp
  SoXipMprIntersectionPlanes.cpp
  SoXipMprLock.cpp
  SoXipMprLockElement.cpp
  SoXipMprPlane.cpp
  SoXipMprPlaneElement.cpp
  SoXipMultiTextureElement.cpp
  SoXipOrientationCube.cpp
  SoXipPerformance.cpp
  SoXipPerformanceCounter.cpp
  SoXipPickAction.cpp
  SoXipPickRadiusElement.cpp
  SoXipPlaneManipBase.cpp
  SoXipRenderMode.cpp
  SoXipRenderModeElement.cpp
  SoXipSFData.cpp
  SoXipSFDataImage.cpp
  SoXipSFDataImageToSFImage.cpp
  SoXipStringConcatenate.cpp
  SoXipSwitchMFDataImage.cpp
  SoXipTexture.cpp
  SoXipThreadManager.cpp
  SoXipThreadQueueSensor.cpp
  SoXipTimerFunction.cpp
  SoXipTrackballToMouse.cpp
  SoXipTransparentGeometryGroup.cpp
  SoXipTransparentGeometryGroupElement.cpp
  SoXipViewportBorder.cpp
  SoXipViewportGroup.cpp
  SoXipVolDataElement.cpp
  SoXipVolGroup.cpp
  SoXipVolGroupElement.cpp
  SoXipWindowLevelManip.cpp
  SoXipWindowLevelElement.cpp
  SoXipWindowSize.cpp
  XipGeomUtils.cpp
  XipInventorUtils.cpp
  XipStringUtils.cpp
  init.cpp)

#--------------------------------------------------------------------
# Header files
#
set(HEADERS
  SoXipAnchor.h
  SoXipAntiAliasing.h
  SoXipAutoScale.h
  SoXipBackground.h
  SoXipBoundingBox.h
  SoXipClipPlane.h
  SoXipComposeMFImage.h
  SoXipComposeVec6.h
  SoXipConvertMFImageToSFImage.h
  SoXipConvertMatrixToPlane.h
  SoXipConvertSFImageToMFImage.h
  SoXipConvertToEnum.h
  SoXipDecomposeMFImage.h
  SoXipDecomposeVec6.h
  SoXipDogEar.h
  #SoXipExaminer.h
  SoXipExtractSlice.h
  SoXipGetImage.h
  SoXipImage.h
  SoXipImageAttributes.h
  SoXipImageExaminer.h
  SoXipImageExaminerBase.h
  SoXipImageOperation.h
  SoXipImageText.h
  SoXipIncrement.h
  SoXipIntersectionPlane.h
  SoXipLazyGroup.h
  SoXipLoadRaw.h
  SoXipLut.h
  SoXipMouseToggle.h
  SoXipMprActive.h
  SoXipMprAlign.h
  SoXipMprExaminer.h
  SoXipMprIntersectionLine.h
  SoXipMprIntersectionManip.h
  SoXipMprIntersectionPlanes.h
  SoXipMprLock.h
  SoXipMprPlane.h
  SoXipOrientationCube.h
  SoXipPerformance.h
  SoXipPickAction.h
  SoXipPlaneManipBase.h
  SoXipRenderMode.h
  SoXipSFDataImageToSFImage.h
  SoXipStringConcatenate.h
  SoXipSwitchMFDataImage.h
  SoXipTexture.h
  SoXipTimerFunction.h
  SoXipTrackballToMouse.h
  SoXipTransparentGeometryGroup.h
  SoXipViewportBorder.h
  SoXipViewportGroup.h
  SoXipVolGroup.h
  SoXipWindowLevelManip.h
  SoXipWindowSize.h)	

#--------------------------------------------------------------------
# Define compiler flags
#
if(WIN32)
  add_definitions(-DXIPIVCORE_EXPORTS)
else(WIN32)
  add_definitions(-DHAVE_CONFIG_H)
endif(WIN32)

#--------------------------------------------------------------------
# Include directories
#
if(UNIX)
  include_directories(
    ${CMAKE_CURRENT_BINARY_DIR} # for generated config.h
    ${OIV_PATH}/include/
    ../../../include
    /usr/include 
    /usr/include/libxml2/) 
endif(UNIX)

#--------------------------------------------------------------------
# Link directories
#
link_directories(${LIBRARY_OUTPUT_PATH})

#--------------------------------------------------------------------
# Compile library
#
add_library(xipivcore SHARED ${SOURCES} ${HEADERS})

set_target_properties(xipivcore
  PROPERTIES VERSION ${XIP_VERSION_STRING}
  SOVERSION ${XIP_VERSION_STRING})

#--------------------------------------------------------------------
# Link library
#
target_link_libraries(xipivcore
  xipcommon
  debug xipinv240d
  optimized xipinv240
  ${OPENGL_LIBRARIES})

#--------------------------------------------------------------------
# Install library
#
install(TARGETS xipivcore
  RUNTIME DESTINATION bin/debug CONFIGURATIONS Debug
  ARCHIVE DESTINATION lib/debug CONFIGURATIONS Debug
  LIBRARY DESTINATION lib/debug CONFIGURATIONS Debug)

install(TARGETS xipivcore
  RUNTIME DESTINATION bin/release CONFIGURATIONS Release
  ARCHIVE DESTINATION lib/release CONFIGURATIONS Release
  LIBRARY DESTINATION lib/release CONFIGURATIONS Release)

if(WIN32)
  install(FILES ${LIBRARY_OUTPUT_PATH}/debug/xipivcore.pdb
    DESTINATION bin/debug CONFIGURATIONS Debug)
endif(WIN32)
