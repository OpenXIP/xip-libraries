# Copyright Siemens Corporate Research Inc. 2007
# Author Sylvain Jaume <sylvain.jaume@siemens.com>

project(dicom)

#--------------------------------------------------------------------
# Define the header files
#
set(HEADERS
  SbXipDicomProviderDcmtk.h
  SoXipComposeMFDicom.h
  SoXipConvertDicom.h
  SoXipConvertDicomToXipImage.h
  SoXipDecomposeMFDicom.h
  SoXipDicomExaminer.h
  SoXipDicomExtractSlice.h
  SoXipDicomSort3D.h
  SoXipDicomWindowLevel.h
  SoXipGetDicom.h
  SoXipGetDicomReference.h
  SoXipGetDicomString.h
  SoXipLoadDicom.h
  SoXipLoadPState.h
  SoXipSaveDicom.h
  SoXipSortDicom.h
  SoXipSwitchMFDataDicom.h
  SoXipVolumeDicom.h
  XipDicomSortAlg.h
  XipDicomSortImage.h
  XipDicomSortUtil.h)

#--------------------------------------------------------------------
# Define the source files
#
set(SOURCES
  init.cpp
  SoXipConvertDicom.cpp
  SoXipConvertDicomToXipImage.cpp
  SoXipComposeMFDicom.cpp
  SoXipDataDicom.cpp
  SoXipDataDicomElement.cpp
  SoXipDecomposeMFDicom.cpp
  SoXipDicomExaminer.cpp
  SoXipDicomExtractSlice.cpp
  SbXipDicomProviderDcmtk.cpp
  SoXipDicomSort3D.cpp
  SoXipDicomWindowLevel.cpp
  SoXipGetDicom.cpp
  SoXipGetDicomReference.cpp
  SoXipGetDicomString.cpp
  SoXipLoadDicom.cpp
  SoXipLoadPState.cpp
  SoXipMFDataDicom.cpp
  SoXipPState.cpp
  SoXipSaveDicom.cpp
  SoXipSFDataDicom.cpp
  SoXipSFPState.cpp
  SoXipSortDicom.cpp
  SoXipSwitchMFDataDicom.cpp
  SoXipVolumeDicom.cpp
  XipDicomSortAlg.cpp
  XipDicomSortImage.cpp
  XipDicomSortUtil.cpp
  xipivDicomUtils.cpp)

#--------------------------------------------------------------------
# Define the compiler flags
#
if(WIN32)
  add_definitions(-DXIPIVDICOM_EXPORTS)
else(WIN32)
  add_definitions(-DHAVE_CONFIG_H)
endif(WIN32)

#--------------------------------------------------------------------
# Define the link directories
#
if(UNIX)
  link_directories(
    ${CMAKE_CURRENT_BINARY_DIR} # for generated config.h
    ${DCMTK_DIR}/lib)
endif(UNIX)

#--------------------------------------------------------------------
# Compile the library
#
if(BUILD_SHARED_LIBS)
  add_library(xipivdicom SHARED ${HEADERS} ${SOURCES})
else(BUILD_SHARED_LIBS)
  add_library(xipivdicom STATIC ${HEADERS} ${SOURCES})
endif(BUILD_SHARED_LIBS)

set_target_properties(xipivdicom
  PROPERTIES VERSION ${XIP_VERSION_STRING}
  SOVERSION ${XIP_VERSION_STRING})

#--------------------------------------------------------------------
# Link the library
#
target_link_libraries(xipivdicom
  xipivcore
  ${DCMTK_LIBRARIES})

if(WIN32)
  target_link_libraries(xipivdicom
    wsock32
    netapi32)
else(WIN32)
  target_link_libraries(xipivdicom
    z)
endif(WIN32)

#--------------------------------------------------------------------
# Install the library
#
install(TARGETS xipivdicom
  RUNTIME DESTINATION bin/release CONFIGURATIONS Release
  ARCHIVE DESTINATION lib/release CONFIGURATIONS Release
  LIBRARY DESTINATION lib/release CONFIGURATIONS Release
  BUNDLE  DESTINATION lib/release CONFIGURATIONS Release)

install(TARGETS xipivdicom
  RUNTIME DESTINATION bin/debug   CONFIGURATIONS Debug
  ARCHIVE DESTINATION lib/debug   CONFIGURATIONS Debug
  LIBRARY DESTINATION lib/debug   CONFIGURATIONS Debug
  BUNDLE  DESTINATION lib/debug   CONFIGURATIONS Debug)

if(WIN32)
  install(FILES ${LIBRARY_OUTPUT_PATH}/debug/xipivdicomd.pdb
    DESTINATION bin/debug CONFIGURATIONS Debug)
endif(WIN32)
