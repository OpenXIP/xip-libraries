# Copyright Siemens Corporate Research Inc. 2007
# Author Sylvain Jaume <sylvain.jaume@siemens.com>

project(database)

#--------------------------------------------------------------------
# Build projects in the subdirectories
#
add_subdirectory(core)
add_subdirectory(coregl)
add_subdirectory(extra)
add_subdirectory(renderer)

if(WIN32)
  add_subdirectory(remote) # FIXME: issues with ppc architecture
endif(WIN32)


if(UNIX AND HAS_DCMTK)

  find_package(DCMTK)

  if(NOT DCMTK_DIR)
    set(DCMTK_DIR ${XIPEXT}/dcmtk)
  endif(NOT DCMTK_DIR)

  find_library(DCMTK_dcmdata_LIBRARY dcmdata
    ${DCMTK_DIR}/lib
    ${XIP_SOURCE_DIR}/../xipext-mac-xcode/dcmtk/lib/release
    ${XIP_SOURCE_DIR}/../xipext-linux-32bit/dcmtk/lib)

  if(DCMTK_dcmdata_LIBRARY)
    get_filename_component(DCMTK_DIR ${DCMTK_dcmdata_LIBRARY} PATH)
  endif(DCMTK_dcmdata_LIBRARY)

  find_library(DCMTK_dcmimgle_LIBRARY dcmimgle
    ${DCMTK_DIR}
    ${XIP_SOURCE_DIR}/../xipext-mac-xcode/dcmtk/lib/release
    ${XIP_SOURCE_DIR}/../xipext-linux-32bit/dcmtk/lib)

  mark_as_advanced(DCMTK_dcmnet_LIBRARY)

  find_library(DCMTK_imagedb_LIBRARY dcmimage
    ${DCMTK_DIR}
    ${XIP_SOURCE_DIR}/../xipext-mac-xcode/dcmtk/lib/release
    ${XIP_SOURCE_DIR}/../xipext-linux-32bit/dcmtk/lib)

  find_library(DCMTK_ofstd_LIBRARY ofstd
    ${DCMTK_DIR}
    ${XIP_SOURCE_DIR}/../xipext-mac-xcode/dcmtk/lib/release
    ${XIP_SOURCE_DIR}/../xipext-linux-32bit/dcmtk/lib)

  find_path(DCMTK_config_INCLUDE_DIR osconfig.h
    ${XIP_SOURCE_DIR}/../xipext-mac-xcode/dcmtk/include/dcmtk/config
    ${XIP_SOURCE_DIR}/../xipext-linux-32bit/dcmtk/include/dcmtk/config)

  find_path(DCMTK_dcmdata_INCLUDE_DIR dcmetinf.h
    ${XIP_SOURCE_DIR}/../xipext-mac-xcode/dcmtk/include/dcmtk/dcmdata
    ${XIP_SOURCE_DIR}/../xipext-linux-32bit/dcmtk/include/dcmtk/dcmdata)

  find_path(DCMTK_dcmimgle_INCLUDE_DIR dcmimage.h
    ${XIP_SOURCE_DIR}/../xipext-mac-xcode/dcmtk/include/dcmtk/dcmimgle
    ${XIP_SOURCE_DIR}/../xipext-linux-32bit/dcmtk/include/dcmtk/dcmimgle)

  find_path(DCMTK_ofstd_INCLUDE_DIR ofstd.h
    ${XIP_SOURCE_DIR}/../xipext-mac-xcode/dcmtk/include/dcmtk/ofstd
    ${XIP_SOURCE_DIR}/../xipext-linux-32bit/dcmtk/include/dcmtk/ofstd)

  set(DCMTK_INCLUDE_DIR ${DCMTK_config_INCLUDE_DIR}/../..)

  set(DCMTK_INCLUDE_DIR ${DCMTK_INCLUDE_DIR}
    ${DCMTK_config_INCLUDE_DIR}
    ${DCMTK_dcmdata_INCLUDE_DIR}
    ${DCMTK_dcmimgle_INCLUDE_DIR}
    ${DCMTK_ofstd_INCLUDE_DIR}
    ${DCMTK_dcmdata_INCLUDE_DIR}
    ${DCMTK_dcmimgle_INCLUDE_DIR})

endif(UNIX AND HAS_DCMTK)

#--------------------------------------------------------------------
# Build the DICOM module that wraps the DCMTK libraries
#
if(HAS_DCMTK)
  add_subdirectory(dicom)
  add_subdirectory(overlay)
endif(HAS_DCMTK)

#--------------------------------------------------------------------
# Build the Insight Toolkit module
#
if(HAS_ITK)
  add_subdirectory(itk)
endif(HAS_ITK)

#--------------------------------------------------------------------
# Build the Visualization Toolkit module
#
if(HAS_VTK)
  add_subdirectory(vtk)
endif(HAS_VTK)
