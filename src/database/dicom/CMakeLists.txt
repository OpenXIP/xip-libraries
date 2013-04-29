# Sylvain Jaume 2007

project(dicom)

if(UNIX)
  find_package(DCMTK REQUIRED)
endif(UNIX)

#--------------------------------------------------------------------
# Source files
#
set(SOURCES
  SoXipConvertDicom.cpp
  SoXipConvertDicomToXipImage.cpp
  SoXipComposeMFDicom.cpp
  SoXipDataDicom.cpp
  SoXipDataDicomElement.cpp
  SoXipDecomposeMFDicom.cpp
  SoXipDicomExaminer.cpp
  SoXipDicomExtractSlice.cpp
  SoXipDicomWindowLevel.cpp
  SoXipGetDicom.cpp
  SoXipGetDicomReference.cpp
  SoXipGetDicomString.cpp
  SoXipLoadDicom.cpp
  SoXipLoadPState.cpp
  SoXipMFDataDicom.cpp
  SoXipPState.cpp
  SoXipSFDataDicom.cpp
  SoXipSFPState.cpp
  SoXipSortDicom.cpp
  SoXipSwitchMFDataDicom.cpp
  SoXipVolumeDicom.cpp
  SbXipDicomProviderDcmtk.cpp
  init.cpp
  xipivDicomUtils.cpp
  XipDicomSortAlg.cpp
  XipDicomSortImage.cpp
  XipDicomSortUtil.cpp
  SoXipDicomSort3D.cpp)

#--------------------------------------------------------------------
# Header files
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
  SoXipSortDicom.h
  SoXipSwitchMFDataDicom.h
  SoXipVolumeDicom.h
  XipDicomSortAlg.h
  XipDicomSortImage.h
  XipDicomSortUtil.h)

#--------------------------------------------------------------------
# Definitions
#
if(WIN32)
  add_definitions(-DXIPIVDICOM_EXPORTS)
else(WIN32)
  add_definitions(-DHAVE_CONFIG_H)
endif(WIN32)

#--------------------------------------------------------------------
# Include directories
#
if(WIN32)
 include_directories(${XIPEXT}/dcmtk/include)
endif(WIN32)

if(UNIX)
  set(DCMTK_INCLUDE_DIRS ${DCMTK_INCLUDE_DIRS}
    ${DCMTK_config_INCLUDE_DIR}
    ${DCMTK_dcmdata_INCLUDE_DIR}
    ${DCMTK_dcmimgle_INCLUDE_DIR}
    ${DCMTK_ofstd_INCLUDE_DIR}
    ${DCMTK_dcmdata_INCLUDE_DIR}
    ${DCMTK_dcmimgle_INCLUDE_DIR})
  include_directories(
    ${DCMTK_INCLUDE_DIRS}
    /usr/local/dicom/include)
endif(UNIX)

#--------------------------------------------------------------------
# Link directories
#
if(WIN32)
  link_directories(${XIPEXT}/dcmtk/lib)
else(WIN32)
  link_directories(/usr/local/dicom/lib)
endif(WIN32)

#--------------------------------------------------------------------
# Compile library
#
add_library(xipivdicom SHARED ${SOURCES} ${HEADERS})

set_target_properties(xipivdicom
  PROPERTIES VERSION ${Xip_VERSION_STRING}
  SOVERSION ${Xip_VERSION_STRING})

#--------------------------------------------------------------------
# Link library
#
target_link_libraries(xipivdicom
  xipivcore
  dcmdata
  ofstd
  dcmimage
  dcmpstat
  dcmimgle)

if(WIN32)
  target_link_libraries(xipivdicom
    zlib
    wsock32
    netapi32)
else(WIN32)
  target_link_libraries(xipivdicom
    z)
endif(WIN32)

#--------------------------------------------------------------------
# Install library
#
install(TARGETS xipivdicom
  RUNTIME DESTINATION bin/debug CONFIGURATIONS Debug
  ARCHIVE DESTINATION lib/debug CONFIGURATIONS Debug
  LIBRARY DESTINATION lib/debug CONFIGURATIONS Debug)

install(TARGETS xipivdicom
  RUNTIME DESTINATION bin/release CONFIGURATIONS Release
  ARCHIVE DESTINATION lib/release CONFIGURATIONS Release
  LIBRARY DESTINATION lib/release CONFIGURATIONS Release)

if(WIN32)
  install(FILES ${EXECUTABLE_OUTPUT_PATH}/debug/xipivdicom.pdb
    DESTINATION bin/debug CONFIGURATIONS Debug)
endif(WIN32)
