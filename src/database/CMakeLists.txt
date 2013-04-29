# Sylvain Jaume 2007

project(database)

#--------------------------------------------------------------------
# Link to libraries in the library output path
#
link_directories(${LIBRARY_OUTPUT_PATH})

#--------------------------------------------------------------------
# Build projects in the subdirectories
#
add_subdirectory(core)
add_subdirectory(coregl)
add_subdirectory(renderer)

if(WIN32)
  add_subdirectory(remote) # FIXME: issues with ppc architecture
endif(WIN32)

#--------------------------------------------------------------------
# Build the DICOM module that wraps the DCMTK libraries
#
if(HAS_DCMTK)

  find_package(DCMTK)

  find_library(DCMTK_dcmdata_LIBRARY dcmdata
    ${XIP_SOURCE_DIR}/../xipext-win32-vs8/dcmtk/lib/release
    ${XIP_SOURCE_DIR}/../xipext-mac-xcode/dcmtk/lib/release
    ${XIP_SOURCE_DIR}/../xipext-linux-gcc/dcmtk/lib/release
    /usr/local/dicom/lib)

  if(DCMTK_dcmdata_LIBRARY)
    get_filename_component(DCMTK_DIR ${DCMTK_dcmdata_LIBRARY} PATH)
  endif(DCMTK_dcmdata_LIBRARY)
  
  find_library(DCMTK_dcmimgle_LIBRARY dcmimgle
    ${DCMTK_DIR}
    ${XIP_SOURCE_DIR}/../xipext-win32-vs8/dcmtk/lib/release
    ${XIP_SOURCE_DIR}/../xipext-mac-xcode/dcmtk/lib/release
    ${XIP_SOURCE_DIR}/../xipext-linux-gcc/dcmtk/lib/release
    /usr/local/dicom/lib)

  mark_as_advanced(DCMTK_dcmnet_LIBRARY)
  #dcmnet
  #  ${DCMTK_DIR}
  #  ${XIP_SOURCE_DIR}/../xipext-win32-vs8/dcmtk/lib/release
  #  ${XIP_SOURCE_DIR}/../xipext-mac-xcode/dcmtk/lib/release
  #  ${XIP_SOURCE_DIR}/../xipext-linux-gcc/dcmtk/lib/release
  #  /usr/local/dicom/lib)

  find_library(DCMTK_imagedb_LIBRARY dcmimage
    ${DCMTK_DIR}
    ${XIP_SOURCE_DIR}/../xipext-win32-vs8/dcmtk/lib/release
    ${XIP_SOURCE_DIR}/../xipext-mac-xcode/dcmtk/lib/release
    ${XIP_SOURCE_DIR}/../xipext-linux-gcc/dcmtk/lib/release
    /usr/local/dicom/lib)

  find_library(DCMTK_ofstd_LIBRARY ofstd
    ${DCMTK_DIR}
    ${XIP_SOURCE_DIR}/../xipext-win32-vs8/dcmtk/lib/release
    ${XIP_SOURCE_DIR}/../xipext-mac-xcode/dcmtk/lib/release
    ${XIP_SOURCE_DIR}/../xipext-linux-gcc/dcmtk/lib/release
    /usr/local/dicom/lib)

  find_path(DCMTK_config_INCLUDE_DIR osconfig.h
    ${XIP_SOURCE_DIR}/../xipext-win32-vs8/dcmtk/include/dcmtk/config
    ${XIP_SOURCE_DIR}/../xipext-mac-xcode/dcmtk/include/dcmtk/config
    ${XIP_SOURCE_DIR}/../xipext-linux-gcc/dcmtk/include/dcmtk/config
    /usr/local/dicom/include/dcmtk/config)

  find_path(DCMTK_dcmdata_INCLUDE_DIR dcmetinf.h
    ${XIP_SOURCE_DIR}/../xipext-win32-vs8/dcmtk/include/dcmtk/dcmdata
    ${XIP_SOURCE_DIR}/../xipext-mac-xcode/dcmtk/include/dcmtk/dcmdata
    ${XIP_SOURCE_DIR}/../xipext-linux-gcc/dcmtk/include/dcmtk/dcmdata
    /usr/local/dicom/include/dcmtk/dcmdata)

  find_path(DCMTK_dcmimgle_INCLUDE_DIR dcmimage.h
    ${XIP_SOURCE_DIR}/../xipext-win32-vs8/dcmtk/include/dcmtk/dcmimgle
    ${XIP_SOURCE_DIR}/../xipext-mac-xcode/dcmtk/include/dcmtk/dcmimgle
    ${XIP_SOURCE_DIR}/../xipext-linux-gcc/dcmtk/include/dcmtk/dcmimgle
    /usr/local/dicom/include/dcmtk/dcmimgle)

  find_path(DCMTK_ofstd_INCLUDE_DIR ofstd.h
    ${XIP_SOURCE_DIR}/../xipext-win32-vs8/dcmtk/include/dcmtk/ofstd
    ${XIP_SOURCE_DIR}/../xipext-mac-xcode/dcmtk/include/dcmtk/ofstd
    ${XIP_SOURCE_DIR}/../xipext-linux-gcc/dcmtk/include/dcmtk/ofstd
    /usr/local/dicom/include/dcmtk/ofstd)

  # Go two directories up
  get_filename_component(DCMTK_INCLUDE_DIR ${DCMTK_config_INCLUDE_DIR}
    PATH)
  get_filename_component(DCMTK_INCLUDE_DIR ${DCMTK_INCLUDE_DIR} PATH)
  
  # build DICOM module
  add_subdirectory(dicom)

  # build module for 2D annotation
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
