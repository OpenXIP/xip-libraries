# Copyright Siemens Corporate Research Inc. 2007
# Author Sylvain Jaume <sylvain.jaume@siemens.com>

project(core)

#--------------------------------------------------------------------
# Define the header files
#
set(HEADERS
  SoXipAnchor.h
  # SoXipAntiAliasing.h
  SoXipApplyLutToImage.h
  SoXipAutoScale.h
  SoXipBackground.h
  SoXipBoundingBox.h
  SoXipCheckGLStacks.h
  SoXipClipPlane.h
  SoXipComposeMFImage.h
  SoXipComposeVec6.h
  SoXipConvertMFImageToSFImage.h
  SoXipConvertMatrixToPlane.h
  SoXipConvertSFImageToMFImage.h
  SoXipConvertToEnum.h
  SoXipDecomposeMFImage.h
  SoXipDecomposeVec6.h
  SoXipDisableTexturing.h
  SoXipDogEar.h
  SoXipDrawQuad.h
  ../../../include/xip/inventor/core/SoXipExaminer.h
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
  SoXipInvertMatrix.h
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
  SoXipProxy.h
  SoXipQuad.h
  SoXipRenderMode.h
  SoXipSaveRaw.h
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
  SoXipWindowSize.h
  ../../../include/xip/inventor/core/SoXipConvertToTrigger.h
  SoXipRegistrationTransform.h
  ../../../include/xip/inventor/core/SoXipRegistrationElement.h
  ../../../include/xip/inventor/core/SbXipValueConvertBase.h
  ../../../include/xip/inventor/core/SoXipSlopeInterceptConvert.h
  ../../../include/xip/inventor/core/SoXipValueConvertElement.h
  )	

#--------------------------------------------------------------------
# Define the source files
#
set(SOURCES
  SbRectangle3f.cpp
  SbVariant.cpp
  SbXipCoordinateTransform.cpp
  SbXipDirtyFieldList.cpp
  SbXipImage.cpp
  SbXipImageFile.cpp
  SbXipSlopeInterceptConvert.cpp
  SbXipThread.cpp
  SbXipThreadMutex.cpp
  SoMFVariant.cpp
  SoSFVariant.cpp
  SoXipActiveViewportElement.cpp
  SoXipAnchor.cpp
  SoXipApplyLutToImage.cpp
  SoXipAutoScale.cpp
  SoXipBackground.cpp
  SoXipBoundingBox.cpp
  SoXipCheckGLStacks.cpp
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
  SoXipDisableTexturing.cpp
  SoXipDogEar.cpp
  SoXipDrawQuad.cpp
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
  SoXipIntersectionPlane.cpp
  SoXipInvertMatrix.cpp
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
  SoXipProxy.cpp
  SoXipRenderMode.cpp
  SoXipRenderModeElement.cpp
  SoXipSaveRaw.cpp
  SoXipQuad.cpp
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
  SoXipTrackballToMouse.cpp
  SoXipViewportBorder.cpp
  SoXipViewportGroup.cpp
  SoXipVolDataElement.cpp
  SoXipVolGroup.cpp
  SoXipVolGroupElement.cpp
  SoXipWindowLevelManip.cpp
  SoXipWindowLevelElement.cpp
  SoXipWindowSize.cpp
  XipStringUtils.cpp
  XipGeomUtils.cpp
  XipInventorUtils.cpp
  SoXipConvertToTrigger.cpp
  SoXipConvertMatrixToPlane.cpp
  SoXipConvertToEnum.cpp
  SoXipAnchor.cpp
  SoXipPickRadiusElement.cpp
  SoXipStringConcatenate.cpp
  SoXipConvertToTrigger.cpp
  SoXipRegistrationTransform.cpp
  SoXipRegistrationElement.cpp
  SoXipSlopeInterceptConvert.cpp
  SoXipValueConvertElement.cpp
  init.cpp
  )

#--------------------------------------------------------------------
# Define the compiler flags
#
if(WIN32)
  add_definitions(-DXIPIVCORE_EXPORTS)
else(WIN32)
  add_definitions(-DHAVE_CONFIG_H)
endif(WIN32)

#--------------------------------------------------------------------
# Define the include directories
#
if(UNIX)
  include_directories(
    ${PROJECT_BINARY_DIR} # for generated config.h
    /usr/include 
    /usr/include/libxml2/) 
endif(UNIX)

#--------------------------------------------------------------------
# Compile the library
#
if(BUILD_SHARED_LIBS)
  add_library(xipivcore SHARED ${HEADERS} ${SOURCES})
else(BUILD_SHARED_LIBS)
  add_library(xipivcore STATIC ${HEADERS} ${SOURCES})
endif(BUILD_SHARED_LIBS)

set_target_properties(xipivcore
  PROPERTIES VERSION ${XIP_VERSION_STRING}
  SOVERSION ${XIP_VERSION_STRING})

#--------------------------------------------------------------------
# Link the library
#
target_link_libraries(xipivcore
	${XIP_COMMON_LIBRARY}
	${INVENTOR_LIBRARY}
	${OPENGL_LIBRARIES})

add_dependencies(xipivcore xipcommon)
	
#--------------------------------------------------------------------
# Install the library
#
install(TARGETS xipivcore
  RUNTIME DESTINATION bin/release CONFIGURATIONS Release
  ARCHIVE DESTINATION lib/release CONFIGURATIONS Release
  LIBRARY DESTINATION lib/release CONFIGURATIONS Release
  BUNDLE  DESTINATION lib/release CONFIGURATIONS Release)

install(TARGETS xipivcore
  RUNTIME DESTINATION bin/debug   CONFIGURATIONS Debug
  ARCHIVE DESTINATION lib/debug   CONFIGURATIONS Debug
  LIBRARY DESTINATION lib/debug   CONFIGURATIONS Debug
  BUNDLE  DESTINATION lib/debug   CONFIGURATIONS Debug)

if(WIN32)
  install(FILES ${LIBRARY_OUTPUT_PATH}/debug/xipivcore${CMAKE_DEBUG_POSTFIX}.pdb
    DESTINATION bin/debug CONFIGURATIONS Debug)
endif(WIN32)

if(UNIX)
  install(TARGETS xipivcore
    NAMES xipinv
    PATHS /usr/local/lib
          /usr/lib
          ENV LD_LIBRARY_PATH
          ENV DYLD_LIBRARY_PATH)
endif(UNIX)
