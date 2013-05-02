# Copyright Siemens Corporate Research Inc. 2007
# Author Sylvain Jaume <sylvain.jaume@siemens.com>

project(XIP)
cmake_minimum_required(VERSION 2.6.2)

#--------------------------------------------------------------------
# Set build type to Release
#
mark_as_advanced(CMAKE_BUILD_TYPE
  CMAKE_CONFIGURATION_TYPES
  CMAKE_OSX_ARCHITECTURES
  CMAKE_OSX_SYSROOT)

if(NOT WIN32 AND NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING
  "Choose the type of build, options are: Debug Release 
  RelWithDebInfo MinSizeRel." FORCE)
endif(NOT WIN32 AND NOT CMAKE_BUILD_TYPE)

#--------------------------------------------------------------------
# Build shared libs or static libs
option(BUILD_SHARED_LIBS "Build shared libs or static libs" ON)
mark_as_advanced(BUILD_SHARED_LIBS)

if(${CMAKE_GENERATOR} MATCHES "Visual Studio 8 2005"
  AND NOT ${CMAKE_CXX_COMPILER} MATCHES "Visual Studio 9 2008")
  string(REGEX REPLACE "9.0" "8" CMAKE_CXX_COMPILER ${CMAKE_CXX_COMPILER})
  string(REGEX REPLACE "9.0" "8" CMAKE_C_COMPILER ${CMAKE_C_COMPILER})
endif(${CMAKE_GENERATOR} MATCHES "Visual Studio 8 2005"
	AND NOT ${CMAKE_CXX_COMPILER} MATCHES "Visual Studio 9 2008")

#--------------------------------------------------------------------
# Set up CPack support, to be able to distribute XIP binary packages.
# An even minor version number corresponds to a release.
#
include(InstallRequiredSystemLibraries)

set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "eXtensible Imaging Platorm")
set(CPACK_PACKAGE_VENDOR "Siemens Corporate Research Inc.")

#set(CPACK_PACKAGE_DESCRIPTION_FILE ${CMAKE_SOURCE_DIR}/README.txt)
set(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_SOURCE_DIR}/XIP_LICENSE.txt)

set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "2")
set(CPACK_PACKAGE_VERSION_PATCH "1")

set(XIP_VERSION_STRING ${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH})

set(CPACK_PACKAGE_INSTALL_DIRECTORY
  "XIP ${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}"
  CACHE INTERNAL "where the XIP package will be created")

set(CPACK_PACKAGE_NAME "xip-${XIP_VERSION_STRING}"
  CACHE INTERNAL "name of the XIP package")

string(REGEX REPLACE "Visual Studio " "vs" PACKAGE_SUFFIX
  ${CMAKE_GENERATOR})
string(REGEX REPLACE " 2003"        "" PACKAGE_SUFFIX ${PACKAGE_SUFFIX})
string(REGEX REPLACE " 2005"        "" PACKAGE_SUFFIX ${PACKAGE_SUFFIX})
string(REGEX REPLACE " 2008"        "" PACKAGE_SUFFIX ${PACKAGE_SUFFIX})
string(REGEX REPLACE " WMake"       "" PACKAGE_SUFFIX ${PACKAGE_SUFFIX})
string(REGEX REPLACE " Makefiles"   "" PACKAGE_SUFFIX ${PACKAGE_SUFFIX})
string(REGEX REPLACE " .NET" "-dotnet" PACKAGE_SUFFIX ${PACKAGE_SUFFIX})
string(REGEX REPLACE " "            "" PACKAGE_SUFFIX ${PACKAGE_SUFFIX})

if(${PACKAGE_SUFFIX} MATCHES Win64)
  string(REGEX REPLACE "Win64" "" PACKAGE_SUFFIX ${PACKAGE_SUFFIX})
  set(PACKAGE_SUFFIX win64-${PACKAGE_SUFFIX})
endif(${PACKAGE_SUFFIX} MATCHES Win64)

if(WIN32)
  set(PACKAGE_SUFFIX win32-${PACKAGE_SUFFIX})
endif(WIN32)

if(APPLE)
  set(PACKAGE_SUFFIX mac-${PACKAGE_SUFFIX})
endif(APPLE)

if(UNIX AND NOT APPLE)
  set(PACKAGE_SUFFIX linux-${PACKAGE_SUFFIX})
endif(UNIX AND NOT APPLE)

set(CPACK_PACKAGE_FILE_NAME "xip-${XIP_VERSION_STRING}-${PACKAGE_SUFFIX}"
  CACHE INTERNAL "self-extracting file containing the binaries")

set(CPACK_SOURCE_PACKAGE_FILE_NAME "xip-${XIP_VERSION_STRING}-src"
  CACHE INTERNAL "self-extracting file containing the source code")

if(WIN32)
  string(REGEX REPLACE "/" "\\\\\\\\" CPACK_PACKAGE_ICON
    "${CMAKE_SOURCE_DIR}/doc/xip_logo.bmp")

  string(REGEX REPLACE "/" "\\\\\\\\" CPACK_NSIS_MUI_ICON
    "${CMAKE_SOURCE_DIR}/build/xip_icon.ico")

  set(CPACK_NSIS_DISPLAY_NAME "${CPACK_PACKAGE_NAME}")
  set(CPACK_NSIS_HELP_LINK "https://collab01a.scr.siemens.com/xipwiki/")
  set(CPACK_NSIS_URL_INFO_ABOUT "http://www.openxip.org")
  set(CPACK_NSIS_CONTACT "tim.horz@siemens.com")

  set(CPACK_GENERATOR NSIS)
  set(CPACK_SOURCE_GENERATOR ZIP)
endif(WIN32)

if(APPLE)
  set(CPACK_GENERATOR PackageMaker)
  set(CPACK_SOURCE_GENERATOR TZ)
endif(APPLE)

if(UNIX AND NOT APPLE)
  set(CPACK_GENERATOR TZ)
  set(CPACK_SOURCE_GENERATOR TZ)
endif(UNIX AND NOT APPLE)

# The following components are regex's to match anywhere (unless anchored)
# in absolute path + filename to find files or directories to be excluded
# from source tarball.
set(CPACK_SOURCE_IGNORE_FILES
  "~$"
  "\\\\.svn$"
  "^${PROJECT_SOURCE_DIR}.*/.svn/")

include(CPack)

#--------------------------------------------------------------------
# If CMake is the version we're expecting, don't show the
# CMAKE_BACKWARDS_COMPATIBILITY option. If the version is higher than the
# minimal version required, then show the backward compatibility option.
#
if("${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}" MATCHES "^2\\.6$")
  mark_as_advanced(FORCE CMAKE_BACKWARDS_COMPATIBILITY)
else("${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}" MATCHES "^2\\.6$")
  mark_as_advanced(CLEAR CMAKE_BACKWARDS_COMPATIBILITY)
endif("${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}" MATCHES "^2\\.6$")

#--------------------------------------------------------------------
# Configure the testing framework
#
option(BUILD_TESTING "Create the testing framework" OFF)
mark_as_advanced(BUILD_TESTING)

if(BUILD_TESTING)
  enable_testing()
endif(BUILD_TESTING)

include(Dart)
mark_as_advanced(DART_ROOT)

#--------------------------------------------------------------------
# Options to build with third party libraries
#
if(NOT ${CMAKE_GENERATOR} STREQUAL "MSYS Makefiles")
option(HAS_DCMTK "Build the DCMTK library and the DICOM module." ON)

option(HAS_ITK "Build the ITK module. Requires the external
  libraries the Insight Toolkit found in the xipext zip file." ON)

option(HAS_VTK "Build the VTK module. Requires the external libraries
  of the Visualization Toolkit found in the xipext zip file." ON)
endif(NOT ${CMAKE_GENERATOR} STREQUAL "MSYS Makefiles")

mark_as_advanced(CMAKE_INSTALL_PREFIX HAS_DCMTK)

if(WIN32 AND CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX
    "C:/Program Files/${CPACK_PACKAGE_INSTALL_DIRECTORY}"
    CACHE PATH "Where XIP will be installed" FORCE)
endif(WIN32 AND CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)

if(CMAKE_CL_64)
  add_definitions(-DWIN64)
endif(CMAKE_CL_64)

#--------------------------------------------------------------------
# Set the debug postfix
#
option(DEBUG_POSTFIX "If this option is enabled, a \"d\" will be added as debug postfix." ON)
mark_as_advanced(DEBUG_POSTFIX)

if(DEBUG_POSTFIX)
	set (CMAKE_DEBUG_POSTFIX d)
else(DEBUG_POSTFIX)
	set (CMAKE_DEBUG_POSTFIX )
endif(DEBUG_POSTFIX)


#--------------------------------------------------------------------
# Options to build OpenInventor
#
option(BUILD_INVENTOR "Build the Open Inventor library" ON)
mark_as_advanced(BUILD_INVENTOR)

#--------------------------------------------------------------------
# Generate the Doxygen documentation
#
option(BUILD_DOCUMENTATION "Generate the Doxygen documentation" OFF)
mark_as_advanced(BUILD_DOCUMENTATION)

if(BUILD_DOCUMENTATION)
  find_package(Doxygen)
endif(BUILD_DOCUMENTATION)

#--------------------------------------------------------------------
# Locate the OpenGL libraries
#
find_package(OpenGL REQUIRED)

#--------------------------------------------------------------------
# Define the XIP include directories
#
set(XIP_INCLUDE_DIRS
  ${CMAKE_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/src/extern/inventor/lib/database/include
  ${CMAKE_SOURCE_DIR}/src/extern/inventor/lib/interaction/include
  ${CMAKE_SOURCE_DIR}/src/extern/inventor/lib/mevis/include
  ${CMAKE_SOURCE_DIR}/src/extern/inventor/lib/nodekits/include
  ${CMAKE_SOURCE_DIR}/src/extern/inventor/lib/xip/include
  ${CMAKE_SOURCE_DIR}/src/extern/inventor/libSoXt/include
  ${CMAKE_INSTALL_PREFIX}/include)

#--------------------------------------------------------------------
# Define the XIP libraries
#
set(XIP_COMMON_LIBRARY
	optimized xipcommon
	debug xipcommon${CMAKE_DEBUG_POSTFIX})

set(INVENTOR_LIBRARY
	${OPENGL_LIBRARIES}
  ${XIP_COMMON_LIBRARY}
	optimized xipinv240
 	debug xipinv240${CMAKE_DEBUG_POSTFIX})
	
set(XIP_EXTRA_LIBRARY
	${INVENTOR_LIBRARY}
	optimized xipivextra
	debug xipivextra${CMAKE_DEBUG_POSTFIX})

set(XIP_CORE_LIBRARY
	${XIP_EXTRA_LIBRARY}
	optimized xipivcore
	debug xipivcore${CMAKE_DEBUG_POSTFIX})

set(XIP_COREGL_LIBRARY
	${XIP_CORE_LIBRARY}
	optimized xipivcoregl
	debug xipivcoregl${CMAKE_DEBUG_POSTFIX})

set(XIP_RENDERER_LIBRARY
	${XIP_COREGL_LIBRARY}
	optimized xipivrenderer
	debug xipivrenderer${CMAKE_DEBUG_POSTFIX})

set(XIP_REMOTE_LIBRARY
  ${XIP_COREGL_LIBRARY}
	optimized xipivremote
	debug xipivremote${CMAKE_DEBUG_POSTFIX})

set(XIP_DICOM_LIBRARY
	${XIP_COREGL_LIBRARY}
	optimized xipivdicom
	debug xipivdicom${CMAKE_DEBUG_POSTFIX})

set(XIP_OVERLAY_LIBRARY
	${XIP_COREGL_LIBRARY}
	optimized xipivoverlay
	debug xipivoverlay${CMAKE_DEBUG_POSTFIX})

set(XIP_ITK_LIBRARY
	${XIP_COREGL_LIBRARY}
	optimized xipivitk
	debug xipivitk${CMAKE_DEBUG_POSTFIX})

set(XIP_VTK_LIBRARY
	${XIP_COREGL_LIBRARY}
	optimized xipivvtk
	debug xipivvtk${CMAKE_DEBUG_POSTFIX})

set(XIP_LIBRARIES ${XIP_RENDERER_LIBRARY})

if(WIN32)
  set(XIP_LIBRARIES ${XIP_LIBRARIES}
  ${XIP_REMOTE_LIBRARY})
endif(WIN32)

if(HAS_DCMTK)
  set(XIP_LIBRARIES ${XIP_LIBRARIES}
  ${XIP_DICOM_LIBRARY}
  ${XIP_OVERLAY_LIBRARY})
endif(HAS_DCMTK)

if(HAS_ITK)
  set(XIP_LIBRARIES ${XIP_LIBRARIES}
  ${XIP_ITK_LIBRARY})
endif(HAS_ITK)

if(WIN32)
  set(XIP_EXECUTABLES
	optimized rendernode
	debug rendernode${CMAKE_DEBUG_POSTFIX})
endif(WIN32)

#--------------------------------------------------------------------
# Find external libraries
#
if(NOT BUILD_INVENTOR)
    if(CMAKE_CL_64)			
		find_path(OIV_PATH bin/xipinv240.dll
			../xipext-win64-vs8-release/inventor
			../xipext-win64-vs8-debug/inventor
			"Directory where Open Inventor is installed")
    endif(CMAKE_CL_64)

	if(WIN32 AND NOT CMAKE_CL_64)
		find_path(OIV_PATH bin/xipinv240.dll
			../xipext-win32-vs8-release/inventor
			../xipext-win32-vs8-debug/inventor
			"Directory where Open Inventor is installed")
    endif(WIN32 AND NOT CMAKE_CL_64)
	
    if(DARWIN)
		find_path(OIV_PATH bin/xipinv240.dll
			../xipext-mac-xcode/inventor
			"Directory where Open Inventor is installed")	
    endif(DARWIN)

	if(UNIX AND NOT DARWIN)
		find_path(OIV_PATH bin/xipinv240.dll
			../xipext-linux-32bit/inventor
			"Directory where Open Inventor is installed")
    endif(UNIX AND NOT DARWIN)
endif(NOT BUILD_INVENTOR)

#--------------------------------------------------------------------
# Locate VTK libraries
#
if(HAS_VTK)

  set(XIP_LIBRARIES ${XIP_LIBRARIES}
    optimized xipivvtk debug xipivvtk${CMAKE_DEBUG_POSTFIX})

	if(${CMAKE_BINARY_DIR} MATCHES debug)
	
    if(CMAKE_CL_64)
    find_package(VTK REQUIRED PATHS
		${CMAKE_SOURCE_DIR}/../xipext-win64-vs8-debug/VTK/lib/vtk-5.2)
    endif(CMAKE_CL_64)

    if(WIN32 AND NOT CMAKE_CL_64)
    find_package(VTK REQUIRED PATHS
		${CMAKE_SOURCE_DIR}/../xipext-win32-vs8-debug/VTK/lib/vtk-5.2)
	  endif(WIN32 AND NOT CMAKE_CL_64)

    if(DARWIN)
    find_package(VTK REQUIRED PATHS
    ${CMAKE_SOURCE_DIR}/../xipext-mac-xcode-debug/VTK/lib/vtk-5.2)
    endif(DARWIN)

    if(UNIX AND NOT DARWIN)
    find_package(VTK REQUIRED PATHS
    ${CMAKE_SOURCE_DIR}/../xipext-linux-32bit-debug/VTK/lib/vtk-5.2)
    endif(UNIX AND NOT DARWIN)

  else(${CMAKE_BINARY_DIR} MATCHES debug)

    if(CMAKE_CL_64)
    find_package(VTK REQUIRED PATHS
    ${CMAKE_SOURCE_DIR}/../xipext-win64-vs8-release/VTK/lib/vtk-5.2)
    endif(CMAKE_CL_64)

    if(WIN32 AND NOT CMAKE_CL_64)
    find_package(VTK REQUIRED PATHS
    ${CMAKE_SOURCE_DIR}/../xipext-win32-vs8-release/VTK/lib/vtk-5.2)
    endif(WIN32 AND NOT CMAKE_CL_64)

    if(DARWIN)
    find_package(VTK REQUIRED PATHS
    ${CMAKE_SOURCE_DIR}/../xipext-mac-xcode-release/VTK/lib/vtk-5.2)
    endif(DARWIN)

    if(UNIX AND NOT DARWIN)
    find_package(VTK REQUIRED PATHS
    ${CMAKE_SOURCE_DIR}/../xipext-linux-32bit-release/VTK/lib/vtk-5.2)
    endif(UNIX AND NOT DARWIN)

  endif(${CMAKE_BINARY_DIR} MATCHES debug)

  include(${VTK_USE_FILE})

	if(NOT ${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION} EQUAL 5.2)
    message(FATAL_ERROR "VTK 5.2 Required. Found VTK version "
						${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION})
	endif(NOT ${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION} EQUAL 5.2)

  mark_as_advanced(VTK_GLEXT_FILE VTK_GLXEXT_FILE VTK_WGLEXT_FILE)

  if(NOT VTK_LIBRARIES)
    set(VTK_LIBRARIES
    vtkCommon
    vtkDICOMParser
    vtkFiltering
    vtkGenericFiltering
    vtkGraphics
    vtkHybrid
    vtkIO
    vtkImaging
    vtkInfovis
    vtkNetCDF
    vtkParallel
    vtkRendering
    vtkViews
    vtkVolumeRendering
    vtkWidgets
    vtkexoIIc
    vtkexpat
    vtkfreetype
    vtkftgl
    vtkjpeg
    vtklibxml2
    vtkmetaio
    vtkpng
    vtksqlite
    vtksys
    vtktiff
    vtkverdict
    vtkzlib)
  endif(NOT VTK_LIBRARIES)

endif(HAS_VTK)

#--------------------------------------------------------------------
# Define the VTK link directories
#
if(NOT VTK_LIBRARY_DIRS)
  set(VTK_LIBRARY_DIRS ${VTK_DIR}/lib/release)
endif(NOT VTK_LIBRARY_DIRS)

if(NOT VTK_INCLUDE_DIRS)
  set(VTK_INCLUDE_DIRS ${VTK_DIR}/include/vtk-5.2)
endif(NOT VTK_INCLUDE_DIRS)

include_directories(${VTK_INCLUDE_DIRS})
link_directories(${VTK_LIBRARY_DIRS})

#--------------------------------------------------------------------
# DCMTK variables
#
if(NOT DCMTK_INCLUDE_DIRS)
  set(DCMTK_INCLUDE_DIRS
    ${CMAKE_SOURCE_DIR}/src/extern/zlib-1.2.3
    ${CMAKE_SOURCE_DIR}/src/extern/dcmtk-3.5.4/config/include
    ${CMAKE_SOURCE_DIR}/src/extern/dcmtk-3.5.4/dcmdata/include
    ${CMAKE_SOURCE_DIR}/src/extern/dcmtk-3.5.4/dcmimage/include
    ${CMAKE_SOURCE_DIR}/src/extern/dcmtk-3.5.4/dcmimgle/include
    ${CMAKE_SOURCE_DIR}/src/extern/dcmtk-3.5.4/dcmjpeg/include
    ${CMAKE_SOURCE_DIR}/src/extern/dcmtk-3.5.4/dcmnet/include
    ${CMAKE_SOURCE_DIR}/src/extern/dcmtk-3.5.4/dcmpstat/include
    ${CMAKE_SOURCE_DIR}/src/extern/dcmtk-3.5.4/dcmqrdb/include
    ${CMAKE_SOURCE_DIR}/src/extern/dcmtk-3.5.4/dcmsign/include
    ${CMAKE_SOURCE_DIR}/src/extern/dcmtk-3.5.4/dcmsr/include
    ${CMAKE_SOURCE_DIR}/src/extern/dcmtk-3.5.4/dcmtls/include
    ${CMAKE_SOURCE_DIR}/src/extern/dcmtk-3.5.4/dcmwlm/include
    ${CMAKE_SOURCE_DIR}/src/extern/dcmtk-3.5.4/docs/include
    ${CMAKE_SOURCE_DIR}/src/extern/dcmtk-3.5.4/doxygen/include
    ${CMAKE_SOURCE_DIR}/src/extern/dcmtk-3.5.4/ofstd/include)
endif(NOT DCMTK_INCLUDE_DIRS)

set(XIP_INCLUDE_DIRS ${XIP_INCLUDE_DIRS} ${DCMTK_INCLUDE_DIRS})

if(NOT DCMTK_LIBRARIES)
  set(DCMTK_LIBRARIES
    optimized ofstd    debug ofstd${CMAKE_DEBUG_POSTFIX}
    optimized dcmdata  debug dcmdata${CMAKE_DEBUG_POSTFIX}
    optimized dcmimgle debug dcmimgle${CMAKE_DEBUG_POSTFIX}
    optimized dcmimage debug dcmimage${CMAKE_DEBUG_POSTFIX}
    optimized dcmjpeg  debug dcmjpeg${CMAKE_DEBUG_POSTFIX}
    optimized dcmpstat debug dcmpstat${CMAKE_DEBUG_POSTFIX})
endif(NOT DCMTK_LIBRARIES)

#--------------------------------------------------------------------
# Output directories
#
if(NOT EXECUTABLE_OUTPUT_PATH)
  set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin CACHE PATH
    "Single output directory for building all executables.")
endif(NOT EXECUTABLE_OUTPUT_PATH)

if(NOT LIBRARY_OUTPUT_PATH)
  set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib CACHE PATH
    "Single output directory for building all libraries.")
endif(NOT LIBRARY_OUTPUT_PATH)

mark_as_advanced(EXECUTABLE_OUTPUT_PATH LIBRARY_OUTPUT_PATH)

#--------------------------------------------------------------------
# Define compiler flags
#
if(WIN32)
  add_definitions(-DXIPCOMMON_EXPORTS) # for XIPException.h
endif(WIN32)

#--------------------------------------------------------------------
# Disable deprecation warnings for standard C functions
#
if(UNIX AND NOT APPLE)
  add_definitions(-DGL_EXT_timer_query)
endif(UNIX AND NOT APPLE)

if(CMAKE_COMPILER_2005)
  add_definitions(
	  -D_CRT_SECURE_NO_DEPRECATE
		-D_CRT_NONSTDC_NO_DEPRECATE)
endif(CMAKE_COMPILER_2005)

#--------------------------------------------------------------------
# Find the xipbuilder executable, required for testing.
#
if(BUILD_TESTING)
  find_file(XIP_BUILDER xipbuilder${CMAKE_DEBUG_POSTFIX}.exe
    ${CPACK_PACKAGE_INSTALL_DIRECTORY})
  mark_as_advanced(XIP_BUILDER)
endif(BUILD_TESTING)

#--------------------------------------------------------------------
# Define the include directories
#
include_directories(${XIP_INCLUDE_DIRS})

if(OIV_PATH)
  include_directories(${OIV_PATH}/include)
endif(OIV_PATH)

#--------------------------------------------------------------------
# Define the link directories
#
link_directories(
  ${LIBRARY_OUTPUT_PATH}
  .) # Put "." in the rpath of all XIP shared libraries.

#--------------------------------------------------------------------
# Build projects inside subdirectories
#
add_subdirectory(src)

if(BUILD_TESTING AND HAS_VTK)
  add_subdirectory(test)
endif(BUILD_TESTING AND HAS_VTK)

#--------------------------------------------------------------------
# Install the xipbuilder executable
#
if(XIP_BUILDER_DEBUG)
  install(FILES ${XIP_BUILDER_DEBUG}
    DESTINATION bin/debug CONFIGURATIONS Debug)
endif(XIP_BUILDER_DEBUG)

if(XIP_BUILDER_RELEASE)
  install(FILES ${XIP_BUILDER_RELEASE}
    DESTINATION bin/release CONFIGURATIONS Release)
endif(XIP_BUILDER_RELEASE)

#--------------------------------------------------------------------
# Copy Qt files to the install directory
#
option(INSTALL_QT "Copy Qt files to the install directory" OFF)
mark_as_advanced(INSTALL_QT)

if(INSTALL_QT)
  find_package(Qt4)
  if(QT4_FOUND)
    install(FILES
      ${QT_INCLUDE_DIR}/../bin/QtCore4.dll
      ${QT_INCLUDE_DIR}/../bin/QtGui4.dll
      ${QT_INCLUDE_DIR}/../bin/QtOpenGL4.dll
      ${QT_INCLUDE_DIR}/../bin/QtSvg4.dll
      ${QT_INCLUDE_DIR}/../bin/QtXml4.dll
      ${QT_INCLUDE_DIR}/../bin/QtScript4.dll
      DESTINATION bin/release
      CONFIGURATIONS Release)

    install(FILES
      ${QT_INCLUDE_DIR}/../bin/QtCored4.dll
      ${QT_INCLUDE_DIR}/../bin/QtGuid4.dll
      ${QT_INCLUDE_DIR}/../bin/QtOpenGLd4.dll
      ${QT_INCLUDE_DIR}/../bin/QtSvgd4.dll
      ${QT_INCLUDE_DIR}/../bin/QtXmld4.dll
      ${QT_INCLUDE_DIR}/../bin/QtScriptd4.dll
      ${QT_INCLUDE_DIR}/../bin/QtCored4.pdb
      ${QT_INCLUDE_DIR}/../bin/QtGuid4.pdb
      ${QT_INCLUDE_DIR}/../bin/QtOpenGLd4.pdb
      ${QT_INCLUDE_DIR}/../bin/QtSvgd4.pdb
      ${QT_INCLUDE_DIR}/../bin/QtXmld4.pdb
      ${QT_INCLUDE_DIR}/../bin/QtScriptd4.pdb
      DESTINATION bin/debug
      CONFIGURATIONS Debug)

  endif(QT4_FOUND)
endif(INSTALL_QT)

#--------------------------------------------------------------------
# Install header files located in the include directory
#
set(XIP_HEADER_FILES
  include/xip/common/XipCommon.h
  include/xip/common/XipException.h
  include/xip/inventor/core/SbVariant.h
  include/xip/inventor/core/SbXipCoordinateTransform.h
  include/xip/inventor/core/SbXipDirtyFieldList.h
  include/xip/inventor/core/SbXipImage.h
  include/xip/inventor/core/SbXipImageAdaptor.h
  include/xip/inventor/core/SbXipImageFile.h
  include/xip/inventor/core/SbXipThread.h
  include/xip/inventor/core/SbXipThreadMutex.h
  include/xip/inventor/core/SoMFVariant.h
  include/xip/inventor/core/SoSFVariant.h
  include/xip/inventor/core/SoXipActiveViewportElement.h
  include/xip/inventor/core/SoXipClipPlaneElement.h
  include/xip/inventor/core/SoXipCursor.h
  include/xip/inventor/core/SoXipData.h
  include/xip/inventor/core/SoXipDataImage.h
  include/xip/inventor/core/SoXipDataImageElement.h
  include/xip/inventor/core/SoXipExaminer.h
  include/xip/inventor/core/SoXipImageTextElement.h
  include/xip/inventor/core/SoXipKit.h
  include/xip/inventor/core/SoXipLutElement.h
  include/xip/inventor/core/SoXipMFData.h
  include/xip/inventor/core/SoXipMFDataImage.h
  include/xip/inventor/core/SoXipMprActiveElement.h
  include/xip/inventor/core/SoXipMprLockElement.h
  include/xip/inventor/core/SoXipMprPlaneElement.h
  include/xip/inventor/core/SoXipMultiTextureElement.h
  include/xip/inventor/core/SoXipPickRadiusElement.h
  include/xip/inventor/core/SoXipPluginLoader.h
  include/xip/inventor/core/SoXipRenderModeElement.h
  include/xip/inventor/core/SoXipSFData.h
  include/xip/inventor/core/SoXipSFDataImage.h
  include/xip/inventor/core/SoXipSubData.h
  include/xip/inventor/core/SoXipSubKit.h
  include/xip/inventor/core/SoXipThreadManager.h
  include/xip/inventor/core/SoXipThreadQueueSensor.h
  include/xip/inventor/core/SoXipTransparentGeometryGroupElement.h
  include/xip/inventor/core/SoXipVolDataElement.h
  include/xip/inventor/core/SoXipVolGroupElement.h
  include/xip/inventor/core/SoXipWindowLevelElement.h
  include/xip/inventor/core/XipGeomUtils.h
  include/xip/inventor/core/XipInventorUtils.h
  include/xip/inventor/core/xipivcore.h
  include/xip/inventor/core/XipStringUtils.h
  include/xip/inventor/coregl/FramebufferObject.h
  include/xip/inventor/coregl/gpgpuContext.h
  include/xip/inventor/coregl/SoXipBufferMaskElement.h
  include/xip/inventor/coregl/SoXipCaptureImage.h
  include/xip/inventor/coregl/SoXipDepthTestElement.h
  include/xip/inventor/coregl/SoXipDrawBuffersElement.h
  include/xip/inventor/coregl/SoXipDrawImage.h
  include/xip/inventor/coregl/SoXipDrawQuad.h
  include/xip/inventor/coregl/SoXipFboElement.h
  include/xip/inventor/coregl/SoXipFramebufferElement.h
  include/xip/inventor/coregl/SoXipFramebufferFlip.h
  include/xip/inventor/coregl/SoXipFrameRate.h
  include/xip/inventor/coregl/SoXipGetTransform.h
  include/xip/inventor/coregl/SoXipGlowElement.h
  include/xip/inventor/coregl/SoXipGLSLShaderProgramElement.h
  include/xip/inventor/coregl/SoXipMultiplyMatrices.h
  include/xip/inventor/coregl/SoXipOffscreenRenderer.h
  include/xip/inventor/coregl/SoXipSetTransform.h
  include/xip/inventor/coregl/SoXipShaderProgramElement.h
  include/xip/inventor/coregl/xipivcoregl.h
  include/xip/inventor/dicom/SoXipDataDicom.h
  include/xip/inventor/dicom/SoXipDataDicomElement.h
  include/xip/inventor/dicom/SoXipMFDataDicom.h
  include/xip/inventor/dicom/SoXipPState.h
  include/xip/inventor/dicom/SoXipSFDataDicom.h
  include/xip/inventor/dicom/SoXipSFPState.h
  include/xip/inventor/dicom/xipivdicom.h
  include/xip/inventor/dicom/xipivDicomUtils.h
  include/xip/inventor/itk/SbItkNodeContainer.h
  include/xip/inventor/itk/SoItkDataArray.h
  include/xip/inventor/itk/SoItkDataDecorator.h
  include/xip/inventor/itk/SoItkDataImage.h
  include/xip/inventor/itk/SoItkDataImageMetric.h
  include/xip/inventor/itk/SoItkDataInterpolator.h
  include/xip/inventor/itk/SoItkDataMatrix.h
  include/xip/inventor/itk/SoItkDataNeighborhood.h
  include/xip/inventor/itk/SoItkDataOptimizer.h
  include/xip/inventor/itk/SoItkDataPointSet.h
  include/xip/inventor/itk/SoItkDataTransform.h
  include/xip/inventor/itk/SoItkMFDataImage.h
  include/xip/inventor/itk/SoItkSFDataArray.h
  include/xip/inventor/itk/SoItkSFDataDecorator.h
  include/xip/inventor/itk/SoItkSFDataImage.h
  include/xip/inventor/itk/SoItkSFDataImageMetric.h
  include/xip/inventor/itk/SoItkSFDataInterpolator.h
  include/xip/inventor/itk/SoItkSFDataMatrix.h
  include/xip/inventor/itk/SoItkSFDataNeighborhood.h
  include/xip/inventor/itk/SoItkSFDataOptimizer.h
  include/xip/inventor/itk/SoItkSFDataPointSet.h
  include/xip/inventor/itk/SoItkSFDataTransform.h
  include/xip/inventor/itk/SoItkSFNodeContainer.h
  include/xip/inventor/itk/SoItkUtils.h
  include/xip/inventor/itk/xipivitk.h
  include/xip/inventor/overlay/geomutils.h
  include/xip/inventor/overlay/SbXipMarkerShapes.h
  include/xip/inventor/overlay/SbXipPlot2LegendInfo.h
  include/xip/inventor/overlay/SoXipEditableShape.h
  include/xip/inventor/overlay/SoXipEditText2.h
  include/xip/inventor/overlay/SoXipEllipse.h
  include/xip/inventor/overlay/SoXipFontTypeElement.h
  include/xip/inventor/overlay/SoXipHandlerShape.h
  include/xip/inventor/overlay/SoXipImageTextColorElement.h
  include/xip/inventor/overlay/SoXipManipulableShape.h
  include/xip/inventor/overlay/SoXipOverlayColor.h
  include/xip/inventor/overlay/SoXipOverlayElement.h
  include/xip/inventor/overlay/SoXipOverlayManipBase.h
  include/xip/inventor/overlay/SoXipOverlayManipulatedElement.h
  include/xip/inventor/overlay/SoXipPlot2AreaElement.h
  include/xip/inventor/overlay/SoXipPlot2Element.h
  include/xip/inventor/overlay/SoXipShape.h
  include/xip/inventor/overlay/SoXipSubShape.h
  include/xip/inventor/overlay/SoXipText2.h
  include/xip/inventor/overlay/xipivoverlay.h
  include/xip/inventor/overlay/XipOverlayUtils.h
  include/xip/inventor/overlay/XipPrimitiveDraw.h
  include/xip/inventor/renderer/xipivrenderer.h
  include/xip/inventor/extra/SoMFDouble.h
  include/xip/inventor/extra/SoSFDouble.h
  include/xip/system/defines.h
  include/xip/system/GL/gl.h
  include/xip/system/GL/glext.h
  include/xip/system/GL/glu.h
  include/xip/system/GL/glxext.h
  include/xip/system/GL/standard/gl.h
  include/xip/system/GL/standard/glext.h
  include/xip/system/GL/wglext.h
  include/xip/system/GL/xipglwindow.h
  include/xip/system/linux/standard.h
  include/xip/system/osx/defines.h
  include/xip/system/osx/standard.h
  include/xip/system/standard.h
  include/xip/system/windows/standard.h
  include/xip/utils/XipBasicOperators.h
  include/xip/utils/XipColor.h)

if(WIN32 AND NOT CMAKE_CL_64)
set(XIP_HEADER_FILES ${XIP_HEADER_FILES}
  include/xip/inventor/remote/jpegWrapper/bufferImage.h
  include/xip/inventor/remote/jpegWrapper/bufferImageJpeg.h
  include/xip/inventor/remote/jpegWrapper/buffObj.h
  include/xip/inventor/remote/jpegWrapper/memoryObj.h
  include/xip/inventor/remote/losslessCompression/cpuID.h
  include/xip/inventor/remote/losslessCompression/differentials.h
  include/xip/inventor/remote/losslessCompression/fastMemTransfer.h
  include/xip/inventor/remote/losslessCompression/functions.h
  include/xip/inventor/remote/losslessCompression/huffmanCoder.h
  include/xip/inventor/remote/losslessCompression/losslessCompression.h
  include/xip/inventor/remote/losslessCompression/rleCoder.h)
endif(WIN32 AND NOT CMAKE_CL_64)

if(WIN32)
set(XIP_HEADER_FILES ${XIP_HEADER_FILES}
  include/xip/inventor/remote/XipDataConnectorBase.h
  include/xip/inventor/remote/XipDataObjectBase.h
  include/xip/inventor/remote/xipivremote.h
  include/xip/inventor/remote/XipRenderActionParams.h
  include/xip/inventor/remote/XipRequestManager.h
  include/xip/inventor/remote/XipStream.h)
endif(WIN32)
  
if(HAS_VTK)
set(XIP_HEADER_FILES ${XIP_HEADER_FILES}
  include/xip/inventor/vtk/SoSFVtkAlgorithmOutput.h
  include/xip/inventor/vtk/SoSFVtkObject.h
  include/xip/inventor/vtk/SoVtkAlgorithmOutput.h
  include/xip/inventor/vtk/SoVtkObject.h
  include/xip/inventor/vtk/xipivvtk.h)
endif(HAS_VTK)

foreach(HEADER_FILE ${XIP_HEADER_FILES})
  get_filename_component(INSTALL_PATH ${HEADER_FILE} PATH)
  install(FILES ${HEADER_FILE} DESTINATION ${INSTALL_PATH})
endforeach(HEADER_FILE ${XIP_HEADER_FILES})

#--------------------------------------------------------------------
# Install header files located in src/extern/inventor/lib
#
set(XIP_INVENTOR_HEADER_FILES
  database/include/Inventor/actions/SoAction.h
  database/include/Inventor/actions/SoActions.h
  database/include/Inventor/actions/SoCallbackAction.h
  database/include/Inventor/actions/SoGetBoundingBoxAction.h
  database/include/Inventor/actions/SoGetMatrixAction.h
  database/include/Inventor/actions/SoGLRenderAction.h
  database/include/Inventor/actions/SoHandleEventAction.h
  database/include/Inventor/actions/SoPickAction.h
  database/include/Inventor/actions/SoRayPickAction.h
  database/include/Inventor/actions/SoSearchAction.h
  database/include/Inventor/actions/SoSubAction.h
  database/include/Inventor/actions/SoWriteAction.h
  database/include/Inventor/bundles/SoBundle.h
  database/include/Inventor/bundles/SoMaterialBundle.h
  database/include/Inventor/bundles/SoNormalBundle.h
  database/include/Inventor/bundles/SoTextureCoordinateBundle.h
  database/include/Inventor/caches/SoBoundingBoxCache.h
  database/include/Inventor/caches/SoCache.h
  database/include/Inventor/caches/SoGLCacheList.h
  database/include/Inventor/caches/SoGLRenderCache.h
  database/include/Inventor/caches/SoNormalCache.h
  database/include/Inventor/details/SoConeDetail.h
  database/include/Inventor/details/SoCubeDetail.h
  database/include/Inventor/details/SoCylinderDetail.h
  database/include/Inventor/details/SoDetail.h
  database/include/Inventor/details/SoDetails.h
  database/include/Inventor/details/SoFaceDetail.h
  database/include/Inventor/details/SoLineDetail.h
  database/include/Inventor/details/SoPointDetail.h
  database/include/Inventor/details/SoSubDetail.h
  database/include/Inventor/details/SoTextDetail.h
  database/include/Inventor/elements/SoAccumulatedElement.h
  database/include/Inventor/elements/SoAmbientColorElement.h
  database/include/Inventor/elements/SoBBoxModelMatrixElement.h
  database/include/Inventor/elements/SoCacheElement.h
  database/include/Inventor/elements/SoClipPlaneElement.h
  database/include/Inventor/elements/SoComplexityElement.h
  database/include/Inventor/elements/SoComplexityTypeElement.h
  database/include/Inventor/elements/SoCoordinateElement.h
  database/include/Inventor/elements/SoCreaseAngleElement.h
  database/include/Inventor/elements/SoCullVolumeElement.h
  database/include/Inventor/elements/SoCurrentGLMaterialElement.h
  database/include/Inventor/elements/SoDiffuseColorElement.h
  database/include/Inventor/elements/SoDrawStyleElement.h
  database/include/Inventor/elements/SoElement.h
  database/include/Inventor/elements/SoElements.h
  database/include/Inventor/elements/SoEmissiveColorElement.h
  database/include/Inventor/elements/SoFloatElement.h
  database/include/Inventor/elements/SoFocalDistanceElement.h
  database/include/Inventor/elements/SoFontNameElement.h
  database/include/Inventor/elements/SoFontSizeElement.h
  database/include/Inventor/elements/SoGLAmbientColorElement.h
  database/include/Inventor/elements/SoGLCacheContextElement.h
  database/include/Inventor/elements/SoGLClipPlaneElement.h
  database/include/Inventor/elements/SoGLColorIndexElement.h
  database/include/Inventor/elements/SoGLCoordinateElement.h
  database/include/Inventor/elements/SoGLDiffuseColorElement.h
  database/include/Inventor/elements/SoGLDrawStyleElement.h
  database/include/Inventor/elements/SoGLEmissiveColorElement.h
  database/include/Inventor/elements/SoGLLazyElement.h
  database/include/Inventor/elements/SoGLLightIdElement.h
  database/include/Inventor/elements/SoGLLightModelElement.h
  database/include/Inventor/elements/SoGLLinePatternElement.h
  database/include/Inventor/elements/SoGLLineWidthElement.h
  database/include/Inventor/elements/SoGLMaterialIndexElement.h
  database/include/Inventor/elements/SoGLModelMatrixElement.h
  database/include/Inventor/elements/SoGLNormalElement.h
  database/include/Inventor/elements/SoGLPointSizeElement.h
  database/include/Inventor/elements/SoGLPolygonStippleElement.h
  database/include/Inventor/elements/SoGLProjectionMatrixElement.h
  database/include/Inventor/elements/SoGLRenderPassElement.h
  database/include/Inventor/elements/SoGLShapeHintsElement.h
  database/include/Inventor/elements/SoGLShininessElement.h
  database/include/Inventor/elements/SoGLSpecularColorElement.h
  database/include/Inventor/elements/SoGLTextureBlendColorElement.h
  database/include/Inventor/elements/SoGLTextureCoordinateElement.h
  database/include/Inventor/elements/SoGLTextureEnabledElement.h
  database/include/Inventor/elements/SoGLTextureImageElement.h
  database/include/Inventor/elements/SoGLTextureMatrixElement.h
  database/include/Inventor/elements/SoGLTextureModelElement.h
  database/include/Inventor/elements/SoGLTextureQualityElement.h
  database/include/Inventor/elements/SoGLTextureWrapSElement.h
  database/include/Inventor/elements/SoGLTextureWrapTElement.h
  database/include/Inventor/elements/SoGLUpdateAreaElement.h
  database/include/Inventor/elements/SoGLViewingMatrixElement.h
  database/include/Inventor/elements/SoGLViewportRegionElement.h
  database/include/Inventor/elements/SoInt32Element.h
  database/include/Inventor/elements/SoLazyElement.h
  database/include/Inventor/elements/SoLightAttenuationElement.h
  database/include/Inventor/elements/SoLightModelElement.h
  database/include/Inventor/elements/SoLinePatternElement.h
  database/include/Inventor/elements/SoLineWidthElement.h
  database/include/Inventor/elements/SoLocalBBoxMatrixElement.h
  database/include/Inventor/elements/SoLongElement.h
  database/include/Inventor/elements/SoMaterialBindingElement.h
  database/include/Inventor/elements/SoModelMatrixElement.h
  database/include/Inventor/elements/SoNormalBindingElement.h
  database/include/Inventor/elements/SoNormalElement.h
  database/include/Inventor/elements/SoOverrideElement.h
  database/include/Inventor/elements/SoPickRayElement.h
  database/include/Inventor/elements/SoPickStyleElement.h
  database/include/Inventor/elements/SoPointSizeElement.h
  database/include/Inventor/elements/SoProfileCoordinateElement.h
  database/include/Inventor/elements/SoProfileElement.h
  database/include/Inventor/elements/SoProjectionMatrixElement.h
  database/include/Inventor/elements/SoReplacedElement.h
  database/include/Inventor/elements/SoShapeHintsElement.h
  database/include/Inventor/elements/SoShapeStyleElement.h
  database/include/Inventor/elements/SoShininessElement.h
  database/include/Inventor/elements/SoSpecularColorElement.h
  database/include/Inventor/elements/SoSubElement.h
  database/include/Inventor/elements/SoSwitchElement.h
  database/include/Inventor/elements/SoTextureBlendColorElement.h
  database/include/Inventor/elements/SoTextureCoordinateBindingElement.h
  database/include/Inventor/elements/SoTextureCoordinateElement.h
  database/include/Inventor/elements/SoTextureImageElement.h
  database/include/Inventor/elements/SoTextureMatrixElement.h
  database/include/Inventor/elements/SoTextureModelElement.h
  database/include/Inventor/elements/SoTextureQualityElement.h
  database/include/Inventor/elements/SoTextureWrapSElement.h
  database/include/Inventor/elements/SoTextureWrapTElement.h
  database/include/Inventor/elements/SoTransparencyElement.h
  database/include/Inventor/elements/SoUnitsElement.h
  database/include/Inventor/elements/SoViewingMatrixElement.h
  database/include/Inventor/elements/SoViewportRegionElement.h
  database/include/Inventor/elements/SoViewVolumeElement.h
  database/include/Inventor/elements/SoWindowElement.h
  database/include/Inventor/engines/SoBoolOperation.h
  database/include/Inventor/engines/SoCalculator.h
  database/include/Inventor/engines/SoCompose.h
  database/include/Inventor/engines/SoComputeBoundingBox.h
  database/include/Inventor/engines/SoConcatenate.h
  database/include/Inventor/engines/SoCounter.h
  database/include/Inventor/engines/SoElapsedTime.h
  database/include/Inventor/engines/SoEngine.h
  database/include/Inventor/engines/SoEngines.h
  database/include/Inventor/engines/SoFieldConverter.h
  database/include/Inventor/engines/SoGate.h
  database/include/Inventor/engines/SoInterpolate.h
  database/include/Inventor/engines/SoOneShot.h
  database/include/Inventor/engines/SoOnOff.h
  database/include/Inventor/engines/SoOutputData.h
  database/include/Inventor/engines/SoSelectOne.h
  database/include/Inventor/engines/SoSubEngine.h
  database/include/Inventor/engines/SoTimeCounter.h
  database/include/Inventor/engines/SoTransformVec3f.h
  database/include/Inventor/engines/SoTriggerAny.h
  database/include/Inventor/errors/SoDebugError.h
  database/include/Inventor/errors/SoError.h
  database/include/Inventor/errors/SoErrors.h
  database/include/Inventor/errors/SoMemoryError.h
  database/include/Inventor/errors/SoReadError.h
  database/include/Inventor/events/SoButtonEvent.h
  database/include/Inventor/events/SoEvent.h
  database/include/Inventor/events/SoEvents.h
  database/include/Inventor/events/SoKeyboardEvent.h
  database/include/Inventor/events/SoLocation2Event.h
  database/include/Inventor/events/SoMotion3Event.h
  database/include/Inventor/events/SoMouseButtonEvent.h
  database/include/Inventor/events/SoSpaceballButtonEvent.h
  database/include/Inventor/events/SoSubEvent.h
  database/include/Inventor/fields/SoField.h
  database/include/Inventor/fields/SoFieldContainer.h
  database/include/Inventor/fields/SoFieldData.h
  database/include/Inventor/fields/SoFields.h
  database/include/Inventor/fields/SoMFBitMask.h
  database/include/Inventor/fields/SoMFBool.h
  database/include/Inventor/fields/SoMFColor.h
  database/include/Inventor/fields/SoMFEngine.h
  database/include/Inventor/fields/SoMFEnum.h
  database/include/Inventor/fields/SoMFFloat.h
  database/include/Inventor/fields/SoMFInt32.h
  database/include/Inventor/fields/SoMFLong.h
  database/include/Inventor/fields/SoMFMatrix.h
  database/include/Inventor/fields/SoMFName.h
  database/include/Inventor/fields/SoMFNode.h
  database/include/Inventor/fields/SoMFPath.h
  database/include/Inventor/fields/SoMFPlane.h
  database/include/Inventor/fields/SoMFRotation.h
  database/include/Inventor/fields/SoMFShort.h
  database/include/Inventor/fields/SoMFString.h
  database/include/Inventor/fields/SoMFTime.h
  database/include/Inventor/fields/SoMFUInt32.h
  database/include/Inventor/fields/SoMFULong.h
  database/include/Inventor/fields/SoMFUShort.h
  database/include/Inventor/fields/SoMFVec2f.h
  database/include/Inventor/fields/SoMFVec3f.h
  database/include/Inventor/fields/SoMFVec4f.h
  database/include/Inventor/fields/SoSFBitMask.h
  database/include/Inventor/fields/SoSFBool.h
  database/include/Inventor/fields/SoSFColor.h
  database/include/Inventor/fields/SoSFEngine.h
  database/include/Inventor/fields/SoSFEnum.h
  database/include/Inventor/fields/SoSFFloat.h
  database/include/Inventor/fields/SoSFImage.h
  database/include/Inventor/fields/SoSFInt32.h
  database/include/Inventor/fields/SoSFLong.h
  database/include/Inventor/fields/SoSFMatrix.h
  database/include/Inventor/fields/SoSFName.h
  database/include/Inventor/fields/SoSFNode.h
  database/include/Inventor/fields/SoSFPath.h
  database/include/Inventor/fields/SoSFPlane.h
  database/include/Inventor/fields/SoSFRotation.h
  database/include/Inventor/fields/SoSFShort.h
  database/include/Inventor/fields/SoSFString.h
  database/include/Inventor/fields/SoSFTime.h
  database/include/Inventor/fields/SoSFTrigger.h
  database/include/Inventor/fields/SoSFUInt32.h
  database/include/Inventor/fields/SoSFULong.h
  database/include/Inventor/fields/SoSFUShort.h
  database/include/Inventor/fields/SoSFVec2f.h
  database/include/Inventor/fields/SoSFVec3f.h
  database/include/Inventor/fields/SoSFVec4f.h
  database/include/Inventor/fields/SoSubField.h
  database/include/Inventor/misc/SoAuditorList.h
  database/include/Inventor/misc/SoBase.h
  database/include/Inventor/misc/SoBasic.h
  database/include/Inventor/misc/SoByteStream.h
  database/include/Inventor/misc/SoCallbackList.h
  database/include/Inventor/misc/SoChildList.h
  database/include/Inventor/misc/SoCompactPathList.h
  database/include/Inventor/misc/SoNormalGenerator.h
  database/include/Inventor/misc/SoNotification.h
  database/include/Inventor/misc/SoState.h
  database/include/Inventor/misc/SoTempPath.h
  database/include/Inventor/misc/SoTranscribe.h
  database/include/Inventor/misc/upgraders/SoUpgrader.h
  database/include/Inventor/misc/upgraders/SoV1CustomNode.h
  database/include/Inventor/nodes/glVertArray.h
  database/include/Inventor/nodes/SoAnnotation.h
  database/include/Inventor/nodes/SoArray.h
  database/include/Inventor/nodes/SoAsciiText.h
  database/include/Inventor/nodes/SoBaseColor.h
  database/include/Inventor/nodes/SoBlinker.h
  database/include/Inventor/nodes/SoCallback.h
  database/include/Inventor/nodes/SoCamera.h
  database/include/Inventor/nodes/SoClipPlane.h
  database/include/Inventor/nodes/SoColorIndex.h
  database/include/Inventor/nodes/SoComplexity.h
  database/include/Inventor/nodes/SoCone.h
  database/include/Inventor/nodes/SoCoordinate3.h
  database/include/Inventor/nodes/SoCoordinate4.h
  database/include/Inventor/nodes/SoCube.h
  database/include/Inventor/nodes/SoCylinder.h
  database/include/Inventor/nodes/SoDirectionalLight.h
  database/include/Inventor/nodes/SoDrawStyle.h
  database/include/Inventor/nodes/SoEnvironment.h
  database/include/Inventor/nodes/SoEventCallback.h
  database/include/Inventor/nodes/SoFaceSet.h
  database/include/Inventor/nodes/SoFile.h
  database/include/Inventor/nodes/SoFont.h
  database/include/Inventor/nodes/SoFontStyle.h
  database/include/Inventor/nodes/SoGroup.h
  database/include/Inventor/nodes/SoIndexedFaceSet.h
  database/include/Inventor/nodes/SoIndexedLineSet.h
  database/include/Inventor/nodes/SoIndexedNurbsCurve.h
  database/include/Inventor/nodes/SoIndexedNurbsSurface.h
  database/include/Inventor/nodes/SoIndexedShape.h
  database/include/Inventor/nodes/SoIndexedTriangleStripSet.h
  database/include/Inventor/nodes/SoInfo.h
  database/include/Inventor/nodes/SoLabel.h
  database/include/Inventor/nodes/SoLevelOfDetail.h
  database/include/Inventor/nodes/SoLight.h
  database/include/Inventor/nodes/SoLightModel.h
  database/include/Inventor/nodes/SoLinearProfile.h
  database/include/Inventor/nodes/SoLineSet.h
  database/include/Inventor/nodes/SoLocateHighlight.h
  database/include/Inventor/nodes/SoLOD.h
  database/include/Inventor/nodes/SoMaterial.h
  database/include/Inventor/nodes/SoMaterialBinding.h
  database/include/Inventor/nodes/SoMaterialIndex.h
  database/include/Inventor/nodes/SoMatrixTransform.h
  database/include/Inventor/nodes/SoMultipleCopy.h
  database/include/Inventor/nodes/SoNode.h
  database/include/Inventor/nodes/SoNodes.h
  database/include/Inventor/nodes/SoNonIndexedShape.h
  database/include/Inventor/nodes/SoNormal.h
  database/include/Inventor/nodes/SoNormalBinding.h
  database/include/Inventor/nodes/SoNurbsCurve.h
  database/include/Inventor/nodes/SoNurbsProfile.h
  database/include/Inventor/nodes/SoNurbsSurface.h
  database/include/Inventor/nodes/SoOrthographicCamera.h
  database/include/Inventor/nodes/SoPackedColor.h
  database/include/Inventor/nodes/SoPathSwitch.h
  database/include/Inventor/nodes/SoPendulum.h
  database/include/Inventor/nodes/SoPerspectiveCamera.h
  database/include/Inventor/nodes/SoPickStyle.h
  database/include/Inventor/nodes/SoPointLight.h
  database/include/Inventor/nodes/SoPointSet.h
  database/include/Inventor/nodes/SoProfile.h
  database/include/Inventor/nodes/SoProfileCoordinate2.h
  database/include/Inventor/nodes/SoProfileCoordinate3.h
  database/include/Inventor/nodes/SoQuadMesh.h
  database/include/Inventor/nodes/SoResetTransform.h
  database/include/Inventor/nodes/SoRotation.h
  database/include/Inventor/nodes/SoRotationXYZ.h
  database/include/Inventor/nodes/SoRotor.h
  database/include/Inventor/nodes/SoScale.h
  database/include/Inventor/nodes/SoSeparator.h
  database/include/Inventor/nodes/SoShape.h
  database/include/Inventor/nodes/SoShapeHints.h
  database/include/Inventor/nodes/SoShuttle.h
  database/include/Inventor/nodes/SoSphere.h
  database/include/Inventor/nodes/SoSpotLight.h
  database/include/Inventor/nodes/SoSubNode.h
  database/include/Inventor/nodes/SoSwitch.h
  database/include/Inventor/nodes/SoText2.h
  database/include/Inventor/nodes/SoText3.h
  database/include/Inventor/nodes/SoTexture2.h
  database/include/Inventor/nodes/SoTexture2Transform.h
  database/include/Inventor/nodes/SoTextureCoordinate2.h
  database/include/Inventor/nodes/SoTextureCoordinateBinding.h
  database/include/Inventor/nodes/SoTextureCoordinateDefault.h
  database/include/Inventor/nodes/SoTextureCoordinateEnvironment.h
  database/include/Inventor/nodes/SoTextureCoordinateFunction.h
  database/include/Inventor/nodes/SoTextureCoordinatePlane.h
  database/include/Inventor/nodes/SoTransform.h
  database/include/Inventor/nodes/SoTransformation.h
  database/include/Inventor/nodes/SoTransformSeparator.h
  database/include/Inventor/nodes/SoTranslation.h
  database/include/Inventor/nodes/SoTriangleStripSet.h
  database/include/Inventor/nodes/SoUnits.h
  database/include/Inventor/nodes/SoVertexArray.h
  database/include/Inventor/nodes/SoVertexProperty.h
  database/include/Inventor/nodes/SoVertexShape.h
  database/include/Inventor/nodes/SoWWWAnchor.h
  database/include/Inventor/nodes/SoWWWInline.h
  database/include/Inventor/projectors/SbCylinderPlaneProjector.h
  database/include/Inventor/projectors/SbCylinderProjector.h
  database/include/Inventor/projectors/SbCylinderSectionProjector.h
  database/include/Inventor/projectors/SbCylinderSheetProjector.h
  database/include/Inventor/projectors/SbLineProjector.h
  database/include/Inventor/projectors/SbPlaneProjector.h
  database/include/Inventor/projectors/SbProjector.h
  database/include/Inventor/projectors/SbProjectors.h
  database/include/Inventor/projectors/SbSpherePlaneProjector.h
  database/include/Inventor/projectors/SbSphereProjector.h
  database/include/Inventor/projectors/SbSphereSectionProjector.h
  database/include/Inventor/projectors/SbSphereSheetProjector.h
  database/include/Inventor/Sb.h
  database/include/Inventor/SbBasic.h
  database/include/Inventor/SbBox.h
  database/include/Inventor/SbColor.h
  database/include/Inventor/SbDict.h
  database/include/Inventor/SbLinear.h
  database/include/Inventor/SbPList.h
  database/include/Inventor/SbString.h
  database/include/Inventor/SbTime.h
  database/include/Inventor/SbViewportRegion.h
  database/include/Inventor/sensors/SoAlarmSensor.h
  database/include/Inventor/sensors/SoDataSensor.h
  database/include/Inventor/sensors/SoDelayQueueSensor.h
  database/include/Inventor/sensors/SoFieldSensor.h
  database/include/Inventor/sensors/SoIdleSensor.h
  database/include/Inventor/sensors/SoNodeSensor.h
  database/include/Inventor/sensors/SoOneShotSensor.h
  database/include/Inventor/sensors/SoPathSensor.h
  database/include/Inventor/sensors/SoSensor.h
  database/include/Inventor/sensors/SoSensorManager.h
  database/include/Inventor/sensors/SoSensors.h
  database/include/Inventor/sensors/SoTimerQueueSensor.h
  database/include/Inventor/sensors/SoTimerSensor.h
  database/include/Inventor/So.h
  database/include/Inventor/SoDB.h
  database/include/Inventor/SoInput.h
  database/include/Inventor/SoLists.h
  database/include/Inventor/SoOffscreenRenderer.h
  database/include/Inventor/SoOutput.h
  database/include/Inventor/SoPath.h
  database/include/Inventor/SoPickedPoint.h
  database/include/Inventor/SoPrimitiveVertex.h
  database/include/Inventor/SoType.h
  database/include/machine.h
  database/include/SoDebug.h
  database/include/SoUnknownEngine.h
  database/include/SoUnknownNode.h
  interaction/include/Inventor/actions/SoBoxHighlightRenderAction.h
  interaction/include/Inventor/actions/SoLineHighlightRenderAction.h
  interaction/include/Inventor/draggers/SoCenterballDragger.h
  interaction/include/Inventor/draggers/SoDirectionalLightDragger.h
  interaction/include/Inventor/draggers/SoDragger.h
  interaction/include/Inventor/draggers/SoDragPointDragger.h
  interaction/include/Inventor/draggers/SoHandleBoxDragger.h
  interaction/include/Inventor/draggers/SoJackDragger.h
  interaction/include/Inventor/draggers/SoPointLightDragger.h
  interaction/include/Inventor/draggers/SoRotateCylindricalDragger.h
  interaction/include/Inventor/draggers/SoRotateDiscDragger.h
  interaction/include/Inventor/draggers/SoRotateSphericalDragger.h
  interaction/include/Inventor/draggers/SoScale1Dragger.h
  interaction/include/Inventor/draggers/SoScale2Dragger.h
  interaction/include/Inventor/draggers/SoScale2UniformDragger.h
  interaction/include/Inventor/draggers/SoScaleUniformDragger.h
  interaction/include/Inventor/draggers/SoSpotLightDragger.h
  interaction/include/Inventor/draggers/SoTabBoxDragger.h
  interaction/include/Inventor/draggers/SoTabPlaneDragger.h
  interaction/include/Inventor/draggers/SoTrackballDragger.h
  interaction/include/Inventor/draggers/SoTransformBoxDragger.h
  interaction/include/Inventor/draggers/SoTransformerDragger.h
  interaction/include/Inventor/draggers/SoTranslate1Dragger.h
  interaction/include/Inventor/draggers/SoTranslate2Dragger.h
  interaction/include/Inventor/manips/SoCenterballManip.h
  interaction/include/Inventor/manips/SoDirectionalLightManip.h
  interaction/include/Inventor/manips/SoHandleBoxManip.h
  interaction/include/Inventor/manips/SoJackManip.h
  interaction/include/Inventor/manips/SoPointLightManip.h
  interaction/include/Inventor/manips/SoSpotLightManip.h
  interaction/include/Inventor/manips/SoTabBoxManip.h
  interaction/include/Inventor/manips/SoTrackballManip.h
  interaction/include/Inventor/manips/SoTransformBoxManip.h
  interaction/include/Inventor/manips/SoTransformerManip.h
  interaction/include/Inventor/manips/SoTransformManip.h
  interaction/include/Inventor/nodekits/SoInteractionKit.h
  interaction/include/Inventor/nodes/SoAntiSquish.h
  interaction/include/Inventor/nodes/SoSelection.h
  interaction/include/Inventor/nodes/SoSurroundScale.h
  interaction/include/Inventor/SoInteraction.h
  interaction/include/Inventor/SoSceneManager.h
  mevis/include/inttypes.h
  mevis/include/Inventor/elements/SoGLPolygonOffsetElement.h
  mevis/include/Inventor/elements/SoGLStencilBitsElement.h
  mevis/include/Inventor/elements/SoPolygonOffsetElement.h
  mevis/include/Inventor/elements/SoStencilBitsElement.h
  mevis/include/Inventor/fields/SoSFVec2s.h
  mevis/include/Inventor/fields/SoSFVec3s.h
  mevis/include/Inventor/nodes/SoPolygonOffset.h
  mevis/include/Inventor/SoCatch.h
  mevis/include/Inventor/SoInventor.h
  mevis/include/Inventor/SoMeVis.h
  mevis/include/Inventor/SoTrace.h
  mevis/include/Inventor/system/SbConfig.h
  mevis/include/Inventor/system/SbSystem.h
  mevis/include/SoWinEnterScope.h
  mevis/include/SoWinLeaveScope.h
  nodekits/include/Inventor/details/SoNodeKitDetail.h
  nodekits/include/Inventor/misc/upgraders/SoV1AppearanceKit.h
  nodekits/include/Inventor/misc/upgraders/SoV1BaseKit.h
  nodekits/include/Inventor/misc/upgraders/SoV1CameraKit.h
  nodekits/include/Inventor/misc/upgraders/SoV1ConeKit.h
  nodekits/include/Inventor/misc/upgraders/SoV1CubeKit.h
  nodekits/include/Inventor/misc/upgraders/SoV1CylinderKit.h
  nodekits/include/Inventor/misc/upgraders/SoV1DirectionalLightKit.h
  nodekits/include/Inventor/misc/upgraders/SoV1FaceSetKit.h
  nodekits/include/Inventor/misc/upgraders/SoV1GroupKit.h
  nodekits/include/Inventor/misc/upgraders/SoV1IndexedFaceSetKit.h
  nodekits/include/Inventor/misc/upgraders/SoV1IndexedLineSetKit.h
  nodekits/include/Inventor/misc/upgraders/SoV1IndexedNurbsCurveKit.h
  nodekits/include/Inventor/misc/upgraders/SoV1IndexedNurbsSurfaceKit.h
  nodekits/include/Inventor/misc/upgraders/SoV1IndexedTriangleMeshKit.h
  nodekits/include/Inventor/misc/upgraders/SoV1LightKit.h
  nodekits/include/Inventor/misc/upgraders/SoV1LineSetKit.h
  nodekits/include/Inventor/misc/upgraders/SoV1NodeKit.h
  nodekits/include/Inventor/misc/upgraders/SoV1NodekitCatalog.h
  nodekits/include/Inventor/misc/upgraders/SoV1NodekitParts.h
  nodekits/include/Inventor/misc/upgraders/SoV1NurbsCurveKit.h
  nodekits/include/Inventor/misc/upgraders/SoV1NurbsSurfaceKit.h
  nodekits/include/Inventor/misc/upgraders/SoV1OrthographicCameraKit.h
  nodekits/include/Inventor/misc/upgraders/SoV1PerspectiveCameraKit.h
  nodekits/include/Inventor/misc/upgraders/SoV1PointLightKit.h
  nodekits/include/Inventor/misc/upgraders/SoV1PointSetKit.h
  nodekits/include/Inventor/misc/upgraders/SoV1QuadMeshKit.h
  nodekits/include/Inventor/misc/upgraders/SoV1SceneKit.h
  nodekits/include/Inventor/misc/upgraders/SoV1ShapeKit.h
  nodekits/include/Inventor/misc/upgraders/SoV1SphereKit.h
  nodekits/include/Inventor/misc/upgraders/SoV1SpotLightKit.h
  nodekits/include/Inventor/misc/upgraders/SoV1SubKit.h
  nodekits/include/Inventor/misc/upgraders/SoV1Text2Kit.h
  nodekits/include/Inventor/misc/upgraders/SoV1Text3Kit.h
  nodekits/include/Inventor/misc/upgraders/SoV1TriangleStripSetKit.h
  nodekits/include/Inventor/misc/upgraders/SoV1VertexShapeKit.h
  nodekits/include/Inventor/misc/upgraders/SoV1WrapperKit.h
  nodekits/include/Inventor/nodekits/SoAppearanceKit.h
  nodekits/include/Inventor/nodekits/SoBaseKit.h
  nodekits/include/Inventor/nodekits/SoCameraKit.h
  nodekits/include/Inventor/nodekits/SoLightKit.h
  nodekits/include/Inventor/nodekits/SoNodeKit.h
  nodekits/include/Inventor/nodekits/SoNodekitCatalog.h
  nodekits/include/Inventor/nodekits/SoNodeKitListPart.h
  nodekits/include/Inventor/nodekits/SoNodekitParts.h
  nodekits/include/Inventor/nodekits/SoSceneKit.h
  nodekits/include/Inventor/nodekits/SoSeparatorKit.h
  nodekits/include/Inventor/nodekits/SoShapeKit.h
  nodekits/include/Inventor/nodekits/SoSubKit.h
  nodekits/include/Inventor/nodekits/SoWrapperKit.h
  nodekits/include/Inventor/SoNodeKitPath.h
  xip/include/Inventor/events/SoMouseWheelEvent.h
  xip/include/Inventor/SoXip.h
  xip/include/Inventor/system/SoVersion.h)
  
foreach(HEADER_FILE ${XIP_INVENTOR_HEADER_FILES})

  get_filename_component(MYPATH ${HEADER_FILE} PATH)

  string(REGEX REPLACE "database/"    "" MYPATH ${MYPATH})
  string(REGEX REPLACE "interaction/" "" MYPATH ${MYPATH})
  string(REGEX REPLACE "mevis/"       "" MYPATH ${MYPATH})
  string(REGEX REPLACE "nodekits/"    "" MYPATH ${MYPATH})
  string(REGEX REPLACE "xip/"         "" MYPATH ${MYPATH})

  install(FILES src/extern/inventor/lib/${HEADER_FILE}
    DESTINATION ${MYPATH})
 
endforeach(HEADER_FILE ${XIP_INVENTOR_HEADER_FILES})

#--------------------------------------------------------------------
# XIP example directory
#
set(XIP_EXAMPLES_DIR
  ${CMAKE_CURRENT_SOURCE_DIR}/examples)

#--------------------------------------------------------------------
# RAD examples
#
if(HAS_ITK)
set(RAD_EXAMPLES
"itk/Functor Filters/Binary Functor Filters/itkDivideImageFilter.rad"
"itk/Functor Filters/Binary Functor Filters/itkInterpolateImageFilter.rad"
"itk/Functor Filters/Binary Functor Filters/itkMaskImageFilter.rad"
"itk/Functor Filters/Binary Functor Filters/itkMaskNegatedImageFilter.rad"
"itk/Functor Filters/Binary Functor Filters/itkMaximumImageFilter.rad"
"itk/Functor Filters/Binary Functor Filters/itkMultiplyImageFilter.rad"
"itk/Functor Filters/Binary Functor Filters/itkSquaredDifferenceImageFilter.rad"
"itk/Functor Filters/Binary Functor Filters/itkSubtractImageFilter.rad"
"itk/Functor Filters/Unary Functor Filters/Atan2ImageFilter.rad"
"itk/Functor Filters/Unary Functor Filters/BSpline Filters/BSplineDecompositionImageFilter.rad"
"itk/Functor Filters/Unary Functor Filters/BSpline Filters/BSplineDownsampleImageFilter.xip"
"itk/Functor Filters/Unary Functor Filters/BSpline Filters/BSplineUpsampleImageFilter.xip"
"itk/Functor Filters/Unary Functor Filters/ExpNegativeImageFilter.rad"
"itk/Functor Filters/Unary Functor Filters/GetAverageSliceImageFilter.rad"
"itk/Functor Filters/Unary Functor Filters/Log10ImageFilter.rad"
"itk/Functor Filters/Unary Functor Filters/LogImageFilter.rad"
"itk/Functor Filters/Unary Functor Filters/NormalizeImageFilter.rad"
"itk/Functor Filters/Unary Functor Filters/NotImageFilter.rad"
"itk/Functor Filters/Unary Functor Filters/SigmoidImageFilter.rad"
"itk/Functor Filters/Unary Functor Filters/SinImageFilter.rad"
"itk/Functor Filters/Unary Functor Filters/SqrtImageFilter.rad"
"itk/Functor Filters/Unary Functor Filters/SquareImageFilter.rad"
"itk/Functor Filters/Unary Functor Filters/TanImageFilter.rad"
"itk/Functor Filters/Unary Functor Filters/TrigoImageFilters.rad"
"itk/Neighborhood Filters/BlackTopHatImageFilter.xip"
"itk/Neighborhood Filters/ConnectedComponentImageFilter.xip"
"itk/Neighborhood Filters/HardConnectedImageFilter.xip"
"itk/Neighborhood Filters/MeanImageFilter.rad"
"itk/Neighborhood Filters/MedianImageFilter.rad"
"itk/Neighborhood Filters/Morphology Image Filters/BinaryMedianImageFilter.rad"
"itk/Neighborhood Filters/Morphology Image Filters/BinaryPrunningImageFilter.rad"
"itk/Neighborhood Filters/Morphology Image Filters/BinaryThinningImageFilter.rad"
"itk/Neighborhood Filters/Morphology Image Filters/MaskNeighborhoodOperatorImageFilter.xip"
"itk/Neighborhood Filters/Morphology Image Filters/NeighborhoodOperatorImageFilter.rad"
"itk/Neighborhood Filters/Voting Filters/VotingBinaryHoleFillingImageFilter.rad"
"itk/Neighborhood Filters/Voting Filters/VotingBinaryImageFilter.rad"
"itk/Neighborhood Filters/Voting Filters/VotingBinaryIterativeHoleFillingImageFilter.rad"
"itk/Neighborhood Filters/WhiteTopHatImageFilter.xip"
"itk/Neighborhood Filters/ZeroCrossingImageFilter.rad"
"itk/Reading and Writing/ImageFileReader.rad"
"itk/Reading and Writing/ImageFileWriter.xip"
"itk/Reading and Writing/ImportImageFilter.rad"
"itk/Registration/2DRigidRegistration.xip"
"itk/Segmentation/Level sets/CannySegmentationLevelSetImageFilter.rad"
"itk/Segmentation/StapleImageFilter.rad"
"itk/Smoothing, Derivatve Filters/AntiAliasBinaryFilter.rad"
"itk/Smoothing, Derivatve Filters/BinaryMagnitudeImageFilter.rad"
"itk/Smoothing, Derivatve Filters/BinaryMinMaxCurvatureFlowImageFilter.rad"
"itk/Smoothing, Derivatve Filters/BinomialBlurImageFilter.rad"
"itk/Smoothing, Derivatve Filters/BSplineSmoothing.rad"
"itk/Smoothing, Derivatve Filters/CurvatureFlowImageFilter.rad"
"itk/Smoothing, Derivatve Filters/DerivativeImageFilter.rad"
"itk/Smoothing, Derivatve Filters/DiscreteGaussianImageFilter.rad"
"itk/Smoothing, Derivatve Filters/GradientMagnitudeImageFilter.rad"
"itk/Smoothing, Derivatve Filters/GradientMagnitudeRecursiveGaussianImageFilter.rad"
"itk/Smoothing, Derivatve Filters/LaplacianImageFilter.rad"
"itk/Smoothing, Derivatve Filters/LaplacianRecursiveGaussianImageFilter.rad"
"itk/Smoothing, Derivatve Filters/LaplacianSharpeningImageFilter.rad"
"itk/Smoothing, Derivatve Filters/MinMaxCurvatureFlowImageFilter.rad"
"itk/Smoothing, Derivatve Filters/NoiseImageFilter.rad"
"itk/Smoothing, Derivatve Filters/RecursiveGaussianImageFilter.rad"
"itk/Smoothing, Derivatve Filters/SmoothingRecursiveGaussianImageFilter.rad"
"itk/Statistics, Informations Filters/StatisticsImageFilter.rad"
itk/Threshold/BinaryThresholdImageFilter.rad
itk/Threshold/DoubleThresholdImageFilter.rad)
endif(HAS_ITK)

#if(WIN32)
#set(RAD_EXAMPLES ${RAD_EXAMPLES}
#  remote/mprclient.rad
#  remote/offline_renderer.rad)
#endif(WIN32)

#--------------------------------------------------------------------
# XIP examples
#
set(XIP_EXAMPLES ${RAD_EXAMPLES}
  core/display_raw_image.xip
  core/two_viewports.xip
  coregl/FboManagement/FboAdvancedMedical.xip
  coregl/FboManagement/FboSimpleMedical.xip
  coregl/offscreenRenderer/xip_offline.xip
  coregl/shader/shader.xip
  coregl/ShaderManagement/ShaderManagerMedical.xip
  coregl/TransparentGeometry/transparent_geometry_none.xip
  coregl/TransparentGeometry/transparent_geometry_pingpong.xip
	# this example is broken
	#coregl/TransparentGeometry/transparent_geometry_texture3D.xip
  inventor/cone1.xip
  inventor/cone2.xip
  inventor/cone3.xip
  overlay/all_shapes.xip
  overlay/display_text.xip
  overlay/lutcolorbar.xip
  overlay/measurements.xip
  overlay/overlay_color.xip
  overlay/overlay_drawstyle.xip
  overlay/overlay_manager.xip
  overlay/overlay_manipulation.xip
  overlay/overlay_menu.xip
  overlay/overlay_multi_label_search.xip
  overlay/overlay_reading_saving.xip
  overlay/overlay_search_contour.xip
  overlay/overlay_set_properties.xip
  overlay/plotting_1.xip
  overlay/plotting_2.xip
  overlay/plotting_3.xip
  overlay/plotting_4.xip
  overlay/plotting_5.xip
  overlay/shape_measurements.xip)
  
if(HAS_DCMTK)
set(XIP_EXAMPLES ${XIP_EXAMPLES}
  dicom/display_dicom_image.xip
  dicom/display_dicom_images.xip
  dicom/get_dicom_string.xip
  dicom/load_presentation_state.xip
  dicom/overlay_dicom_tag.xip
  dicom/overlay_dicom_tag_scale_bar.xip
  dicom/save_presentation_state.xip)
endif(HAS_DCMTK)

if(HAS_ITK)
set(XIP_EXAMPLES ${XIP_EXAMPLES}
  "itk/Casting, Intensity Mapping/itkAdaptiveHistogramEqualizationImageFilter.xip"
  "itk/Casting, Intensity Mapping/itkCastImageFilter.xip"
  "itk/Casting, Intensity Mapping/itkHistogramMatchingImageFilter.xip"
  "itk/Casting, Intensity Mapping/itkIntensityWindowingImageFilter.xip"
  "itk/Casting, Intensity Mapping/itkRelabelComponentImageFilter.xip"
  "itk/Casting, Intensity Mapping/itkRescaleIntensityImageFilter.xip"
  "itk/Distance Map/itkApproximateSignedDistanceMapImageFilter.xip"
  "itk/Distance Map/itkDanielssonDistanceMapImageFilter.xip"
  "itk/Distance Map/itkSignedDanielssonDistanceMapImageFilter.xip"
  "itk/Edge Detection/itkCannyEdgeDetectionImageFilters.xip"
  "itk/Edge Detection/itkSimpleContourExtractorImageFilter.xip"
  "itk/Edge Detection/itkZeroCrossingBasedEdgeDetectionImageFilter.xip"
  "itk/Functor Filters/Binary Functor Filters/Binary Images Filters/itkAndImageFilter.xip"
  "itk/Functor Filters/Binary Functor Filters/Binary Images Filters/itkNotImageFilter.xip"
  "itk/Functor Filters/Binary Functor Filters/Binary Images Filters/itkOrImageFilter.xip"
  "itk/Functor Filters/Binary Functor Filters/Binary Images Filters/itkXorImageFilter.xip"
  "itk/Functor Filters/Binary Functor Filters/itkAbsoluteValueDifferenceImageFilter.xip"
  "itk/Functor Filters/Binary Functor Filters/itkAddImageFilter.xip"
  "itk/Functor Filters/Binary Functor Filters/itkConstrainedValueAdditionImageFilter.xip"
  "itk/Functor Filters/Binary Functor Filters/itkConstrainedValueDifferenceImageFilter.xip"
  "itk/Functor Filters/Binary Functor Filters/itkDifferenceImageFilter.xip"
  "itk/Functor Filters/Binary Functor Filters/itkWeightedAddImageFilter.xip"
  "itk/Functor Filters/Ternary Functor Filters/itkTernaryAddImageFilter.xip"
  "itk/Functor Filters/Ternary Functor Filters/itkTernaryMagnitudeImageFilter.xip"
  "itk/Functor Filters/Ternary Functor Filters/itkTernaryMagnitudeSquaredImageFilter.xip"
  "itk/Functor Filters/Unary Functor Filters/AccumulateImageFilter.xip"
  "itk/Functor Filters/Unary Functor Filters/AcosImageFilter.xip"
  "itk/Functor Filters/Unary Functor Filters/AsinImageFilter.xip"
  "itk/Functor Filters/Unary Functor Filters/AtanImageFilter.xip"
  "itk/Functor Filters/Unary Functor Filters/BoundedReciprocalImageFilter.xip"
  "itk/Functor Filters/Unary Functor Filters/CosImageFilter.xip"
  "itk/Functor Filters/Unary Functor Filters/ExpImageFilter.xip"
  "itk/Functor Filters/Unary Functor Filters/HConcaveImageFilter.xip"
  "itk/Functor Filters/Unary Functor Filters/HConvexImageFilter.xip"
  "itk/Functor Filters/Unary Functor Filters/HMaximalImageFilter.xip"
  "itk/Functor Filters/Unary Functor Filters/HMinimalImageFilter.xip"
  "itk/Geometric Transformations/itkCheckerBoardImageFilter.xip"
  "itk/Geometric Transformations/itkCropImageFilter.xip"
  "itk/Geometric Transformations/itkExtractImageFilter.xip"
  "itk/Geometric Transformations/itkFlipImageFilter.xip"
  "itk/Geometric Transformations/itkMultiResolutionPyramidImageFilter.xip"
  "itk/Geometric Transformations/itkNonThreadedShrinkImageFilter.xip"
  "itk/Geometric Transformations/itkPasteImageFilter.xip"
  "itk/Geometric Transformations/itkPermuteAxesImageFilter.xip"
  "itk/Geometric Transformations/itkReflectImageFilter.xip"
  "itk/Geometric Transformations/itkRegionOfInterestImageFilter.xip"
  "itk/Geometric Transformations/itkShiftScaleImageFilter.xip"
  "itk/Geometric Transformations/itkShrinkImageFilter.xip"
  "itk/Geometric Transformations/itkTileImageFilter.xip"
  "itk/Geometric Transformations/Padding Image Filters/itkConstantPadImageFilter.xip"
  "itk/Geometric Transformations/Padding Image Filters/itkMirrorPadImageFilter.xip"
  "itk/Geometric Transformations/Padding Image Filters/itkPadImageFilters.xip"
  "itk/Geometric Transformations/Padding Image Filters/itkWrapPadImageFilter.xip"
  itk/PointSet/BinaryMaskToNarrowBandPointSetFilter.xip
  "itk/Segmentation/Level sets/ShapeDetectionLevelSetImageFilter.xip"
  "itk/Segmentation/Region Growth/CollidingFrontsImageFilter.xip"
  "itk/Segmentation/Region Growth/ConfidenceConnectedImageFilter.xip"
  "itk/Segmentation/Region Growth/ConnectedThresholdImageFilter.xip"
  "itk/Segmentation/Region Growth/IsolatedConnectedImageFilters.xip"
  itk/Segmentation/Watershed/IsolatedWatershedImageFilter.xip
  renderer/MPR/CPUmpr.xip
  renderer/MPR/mpr.xip
  renderer/MPR/mpr_loadraw.xip
  renderer/MPR/mpr_loadraw_multiple.xip
  renderer/MPR/simple_mpr.xip
  renderer/slicer/dicomSlicer.xip
  renderer/slicer/slicer.xip
  renderer/slicer/slicerWithLut.xip
  renderer/slicer/slicerWithLutShaded.xip)
endif(HAS_ITK)

#if(WIN32)
#set(XIP_EXAMPLES ${XIP_EXAMPLES}
#  remote/client.xip
#  remote/render.xip
#  remote/server.xip)
#endif(WIN32)

if(HAS_VTK)
set(XIP_EXAMPLES ${XIP_EXAMPLES}
  vtk/Converters/vtkXipImageToVtk.xip
  vtk/DICOM/vtkVolumeRendering.xip
  vtk/Tutorial/vtkConeSource.xip
  vtk/VisualizationAlgorithms/vtkClipCow.xip
  vtk/VisualizationAlgorithms/vtkOfficeTube.xip
  vtk/VolumeRendering/vtkVolumeRendering.xip
  vtk/VolumeRendering/vtkPseudoVolumeRendering.xip
  vtk/VolumeRendering/vtkSimpleRayCast.xip
  vtk/VolumeRendering/vtkSimpleTextureMap2D.xip)
endif(HAS_VTK)

#--------------------------------------------------------------------
# GLSL files
#
set(XIP_GLSL_FILES
coregl/FboManagement/shaders/color_fp.glsl
coregl/FboManagement/shaders/color_vp.glsl
coregl/FboManagement/shaders/mask_fp.glsl
coregl/FboManagement/shaders/mask_vp.glsl
coregl/FboManagement/shaders/slicer_fp.glsl
coregl/FboManagement/shaders/slicer_vp.glsl
coregl/FboManagement/shaders/tex_fp.glsl
coregl/FboManagement/shaders/tex_vp.glsl
coregl/ShaderManagement/shaders/slicer1_fp.glsl
coregl/ShaderManagement/shaders/slicer2_fp.glsl
coregl/ShaderManagement/shaders/slicer3_fp.glsl
coregl/ShaderManagement/shaders/slicer_vp.glsl
coregl/TransparentGeometry/shaders/composite_frag.glsl
coregl/TransparentGeometry/shaders/composite_texture3D_frag.glsl
coregl/TransparentGeometry/shaders/transparent_geometry_frag.glsl
coregl/TransparentGeometry/shaders/transparent_geometry_texture3D_frag.glsl
renderer/MPR/mpr_fp.glsl
renderer/MPR/mpr_vp.glsl
renderer/MPR/slicerfp.glsl
renderer/slicer/simpleLut_tf_fp.glsl
renderer/slicer/slicer_fp.glsl
renderer/slicer/slicer_lut_shading_fp.glsl
renderer/slicer/slicer_lut_shading_vp.glsl
renderer/slicer/dicomSlicer_simple_tf_fp.glsl
renderer/slicer/dicomSlicer_simple_vp.glsl
coregl/offscreenRenderer/red.glsl.frag.txt
coregl/shader/edgedetect.glsl.frag.txt
coregl/shader/emboss.glsl.frag.txt
coregl/shader/engrave.glsl.frag.txt
coregl/shader/mean.glsl.frag.txt
coregl/shader/sharpness.glsl.frag.txt
coregl/shader/simple.glsl.frag.txt
data/CT_WHOLE.txt
data/head_ct256.txt
overlay/overlays.txt
renderer/MPR/SplineShaded.txt
renderer/slicer/ctAbdomen.txt
renderer/slicer/default.txt)

#if(WIN32)
#set(XIP_GLSL_FILES ${XIP_GLSL_FILES}
#  remote/mpr_fp.glsl
#  remote/mpr_vp.glsl
#  remote/shade_tf_fp.glsl
#  remote/simpleLut_tf_fp.glsl
#  remote/simple_tf_fp.glsl
#  remote/simple_vp.glsl
#  remote/AngioRunOff.txt
#  remote/SplineShaded.txt)
#endif(WIN32)

#--------------------------------------------------------------------
# Data in the examples directory
#
set(XIP_DATA_FILES
  data/24884367.dcm
  data/Acetabulum/ACETABULUM_1
  data/Acetabulum/ACETABULUM_10
  data/Acetabulum/ACETABULUM_100
  data/Acetabulum/ACETABULUM_101
  data/Acetabulum/ACETABULUM_102
  data/Acetabulum/ACETABULUM_103
  data/Acetabulum/ACETABULUM_104
  data/Acetabulum/ACETABULUM_105
  data/Acetabulum/ACETABULUM_106
  data/Acetabulum/ACETABULUM_107
  data/Acetabulum/ACETABULUM_108
  data/Acetabulum/ACETABULUM_109
  data/Acetabulum/ACETABULUM_11
  data/Acetabulum/ACETABULUM_110
  data/Acetabulum/ACETABULUM_111
  data/Acetabulum/ACETABULUM_112
  data/Acetabulum/ACETABULUM_113
  data/Acetabulum/ACETABULUM_114
  data/Acetabulum/ACETABULUM_115
  data/Acetabulum/ACETABULUM_116
  data/Acetabulum/ACETABULUM_117
  data/Acetabulum/ACETABULUM_118
  data/Acetabulum/ACETABULUM_119
  data/Acetabulum/ACETABULUM_12
  data/Acetabulum/ACETABULUM_13
  data/Acetabulum/ACETABULUM_14
  data/Acetabulum/ACETABULUM_15
  data/Acetabulum/ACETABULUM_16
  data/Acetabulum/ACETABULUM_17
  data/Acetabulum/ACETABULUM_18
  data/Acetabulum/ACETABULUM_19
  data/Acetabulum/ACETABULUM_2
  data/Acetabulum/ACETABULUM_20
  data/Acetabulum/ACETABULUM_21
  data/Acetabulum/ACETABULUM_22
  data/Acetabulum/ACETABULUM_23
  data/Acetabulum/ACETABULUM_24
  data/Acetabulum/ACETABULUM_25
  data/Acetabulum/ACETABULUM_26
  data/Acetabulum/ACETABULUM_27
  data/Acetabulum/ACETABULUM_28
  data/Acetabulum/ACETABULUM_29
  data/Acetabulum/ACETABULUM_3
  data/Acetabulum/ACETABULUM_30
  data/Acetabulum/ACETABULUM_31
  data/Acetabulum/ACETABULUM_32
  data/Acetabulum/ACETABULUM_33
  data/Acetabulum/ACETABULUM_34
  data/Acetabulum/ACETABULUM_35
  data/Acetabulum/ACETABULUM_36
  data/Acetabulum/ACETABULUM_37
  data/Acetabulum/ACETABULUM_38
  data/Acetabulum/ACETABULUM_39
  data/Acetabulum/ACETABULUM_4
  data/Acetabulum/ACETABULUM_40
  data/Acetabulum/ACETABULUM_41
  data/Acetabulum/ACETABULUM_42
  data/Acetabulum/ACETABULUM_43
  data/Acetabulum/ACETABULUM_44
  data/Acetabulum/ACETABULUM_45
  data/Acetabulum/ACETABULUM_46
  data/Acetabulum/ACETABULUM_47
  data/Acetabulum/ACETABULUM_48
  data/Acetabulum/ACETABULUM_49
  data/Acetabulum/ACETABULUM_5
  data/Acetabulum/ACETABULUM_50
  data/Acetabulum/ACETABULUM_51
  data/Acetabulum/ACETABULUM_52
  data/Acetabulum/ACETABULUM_53
  data/Acetabulum/ACETABULUM_54
  data/Acetabulum/ACETABULUM_55
  data/Acetabulum/ACETABULUM_56
  data/Acetabulum/ACETABULUM_57
  data/Acetabulum/ACETABULUM_58
  data/Acetabulum/ACETABULUM_59
  data/Acetabulum/ACETABULUM_6
  data/Acetabulum/ACETABULUM_60
  data/Acetabulum/ACETABULUM_61
  data/Acetabulum/ACETABULUM_62
  data/Acetabulum/ACETABULUM_63
  data/Acetabulum/ACETABULUM_64
  data/Acetabulum/ACETABULUM_65
  data/Acetabulum/ACETABULUM_66
  data/Acetabulum/ACETABULUM_67
  data/Acetabulum/ACETABULUM_68
  data/Acetabulum/ACETABULUM_69
  data/Acetabulum/ACETABULUM_7
  data/Acetabulum/ACETABULUM_70
  data/Acetabulum/ACETABULUM_71
  data/Acetabulum/ACETABULUM_72
  data/Acetabulum/ACETABULUM_73
  data/Acetabulum/ACETABULUM_74
  data/Acetabulum/ACETABULUM_75
  data/Acetabulum/ACETABULUM_76
  data/Acetabulum/ACETABULUM_77
  data/Acetabulum/ACETABULUM_78
  data/Acetabulum/ACETABULUM_79
  data/Acetabulum/ACETABULUM_8
  data/Acetabulum/ACETABULUM_80
  data/Acetabulum/ACETABULUM_81
  data/Acetabulum/ACETABULUM_82
  data/Acetabulum/ACETABULUM_83
  data/Acetabulum/ACETABULUM_84
  data/Acetabulum/ACETABULUM_85
  data/Acetabulum/ACETABULUM_86
  data/Acetabulum/ACETABULUM_87
  data/Acetabulum/ACETABULUM_88
  data/Acetabulum/ACETABULUM_89
  data/Acetabulum/ACETABULUM_9
  data/Acetabulum/ACETABULUM_90
  data/Acetabulum/ACETABULUM_91
  data/Acetabulum/ACETABULUM_92
  data/Acetabulum/ACETABULUM_93
  data/Acetabulum/ACETABULUM_94
  data/Acetabulum/ACETABULUM_95
  data/Acetabulum/ACETABULUM_96
  data/Acetabulum/ACETABULUM_97
  data/Acetabulum/ACETABULUM_98
  data/Acetabulum/ACETABULUM_99
  data/BrainProtonDensitySlice.PNG
  data/combq.bin
  data/combxyz.bin
  data/coronary/coronary_0.IMA
  data/coronary/coronary_1.IMA
  data/coronary/coronary_2.IMA
  data/coronary/coronary_3.IMA
  data/coronary/coronary_4.IMA
  data/coronary/coronary_5.IMA
  data/coronary/coronary_6.IMA
  data/coronary/coronary_7.IMA
  data/cow.g
  data/CTHead/CTHd000
  data/CTHead/CTHd001
  data/CTHead/CTHd002
  data/CTHead/CTHd003
  data/CTHead/CTHd004
  data/CTHead/CTHd005
  data/CTHead/CTHd006
  data/CTHead/CTHd007
  data/CTHead/CTHd008
  data/CTHead/CTHd009
  data/CTHead/CTHd010
  data/CTHead/CTHd011
  data/CTHead/CTHd012
  data/CTHead/CTHd013
  data/CTHead/CTHd014
  data/CTHead/CTHd015
  data/CTHead/CTHd016
  data/CTHead/CTHd017
  data/CTHead/CTHd018
  data/CTHead/CTHd019
  data/CTHead/CTHd020
  data/CTHead/CTHd021
  data/CTHead/CTHd022
  data/CTHead/CTHd023
  data/CTHead/CTHd024
  data/CTHead/CTHd025
  data/CTHead/CTHd026
  data/CTHead/CTHd027
  data/CTHead/CTHd028
  data/CTHead/CTHd029
  data/CTHead/CTHd030
  data/CTHead/CTHd031
  data/CTHead/CTHd032
  data/CTHead/CTHd033
  data/CTHead/CTHd034
  data/CTHead/CTHd035
  data/CTHead/CTHd036
  data/CTHead/CTHd037
  data/CTHead/CTHd038
  data/CTHead/CTHd039
  data/CTHead/CTHd040
  data/CTHead/CTHd041
  data/CTHead/CTHd042
  data/CTHead/CTHd043
  data/CTHead/CTHd044
  data/CTHead/CTHd045
  data/CTHead/CTHd046
  data/CTHead/CTHd047
  data/CTHead/CTHd048
  data/CTHead/CTHd049
  data/CTHead/CTHd050
  data/CTHead/CTHd051
  data/CTHead/CTHd052
  data/CTHead/CTHd053
  data/CTHead/CTHd054
  data/CTHead/CTHd055
  data/CTHead/CTHd056
  data/CTHead/CTHd057
  data/CTHead/CTHd058
  data/CTHead/CTHd059
  data/CTHead/CTHd060
  data/CTHead/CTHd061
  data/CTHead/CTHd062
  data/CTHead/CTHd063
  data/CTHead/CTHd064
  data/CTHead/CTHd065
  data/CTHead/CTHd066
  data/CTHead/CTHd067
  data/CTHead/CTHd068
  data/CTHead/CTHd069
  data/CTHead/CTHd070
  data/CTHead/CTHd071
  data/CTHead/CTHd072
  data/CTHead/CTHd073
  data/CTHead/CTHd074
  data/CTHead/CTHd075
  data/CTHead/CTHd076
  data/CTHead/CTHd077
  data/CTHead/CTHd078
  data/CTHead/CTHd079
  data/CTHead/CTHd080
  data/CTHead/CTHd081
  data/CTHead/CTHd082
  data/CTHead/CTHd083
  data/CTHead/CTHd084
  data/CTHead/CTHd085
  data/CTHead/CTHd086
  data/CTHead/CTHd087
  data/CTHead/CTHd088
  data/CTHead/CTHd089
  data/CTHead/CTHd090
  data/CTHead/CTHd091
  data/CTHead/CTHd092
  data/CTHead/CTHd093
  data/CTHead/CTHd094
  data/CTHead/CTHd095
  data/CTHead/CTHd096
  data/CTHead/CTHd097
  data/CTHead/CTHd098
  data/CTHead/CTHd099
  data/CTHead/CTHd100
  data/CTHead/CTHd101
  data/CTHead/CTHd102
  data/CTHead/CTHd103
  data/CTHead/CTHd104
  data/CTHead/CTHd105
  data/CTHead/CTHd106
  data/CTHead/CTHd107
  data/CTHead/CTHd108
  data/CTHead/CTHd109
  data/CTHead/CTHd110
  data/CTHead/CTHd111
  data/CTHead/CTHd112
  data/cthead1.png
  data/CT_WHOLE.img
  data/CT_WHOLE.txt
  data/head_ct256.hdr
  data/head_ct256.img
  data/head_ct256.txt
  data/head_ct_8bit.hdr
  data/head_ct_8bit.img
  data/head_ct_8bit.png
  data/head_ct_8bit_32x32x32.img
  data/ironProt.vtk
  data/lena-256x256x12.raw
  data/lena-256x256x16.raw
  data/lena-256x256x8.raw
  data/lena.raw
  data/mummy.128.vtk
  data/office.binary.vtk
  data/test.raw)

#--------------------------------------------------------------------
# Install the XIP examples and GLSL files
#
foreach(EXAMPLE ${XIP_EXAMPLES} ${XIP_GLSL_FILES} ${XIP_DATA_FILES})
  get_filename_component(MYPATH ${EXAMPLE} PATH)
  install(FILES ${XIP_EXAMPLES_DIR}/${EXAMPLE} DESTINATION
				 examples/${MYPATH})
endforeach(EXAMPLE ${XIP_EXAMPLES} ${XIP_GLSL_FILES} ${XIP_DATA_FILES})

#--------------------------------------------------------------------
# Extra files that need to be installed
#
set(XIP_EXTRA_FILES_TO_INSTALL
  HELP.html
  #README.txt
  #RELEASE_0.1.2.txt
  RELEASE_0.2.1.txt
  XIP_LICENSE.txt
  doc/XIPOverview.ppt
  doc/XIPStarterGuide.doc
  doc/xip_logo.bmp
  doc/xip_logo.png
  doc/xipbuilder_logo.png
  plugin/CMakeLists.txt
  plugin/README.txt
  plugin/SoXipPluginSlicer.cpp
  plugin/SoXipPluginSlicer.h
  plugin/ctAbdomen.txt
  plugin/pluginSlicer.xip
  plugin/init.cpp
  plugin/simple_tf_fp.glsl
  plugin/simple_vp.glsl
  plugin/xipplugin.h)

foreach(MYFILE ${XIP_EXTRA_FILES_TO_INSTALL})
	get_filename_component(MYPATH ${MYFILE} PATH)
	if(MYPATH)
    install(FILES ${MYFILE} DESTINATION ${MYPATH})
	else(MYPATH)
    install(FILES ${MYFILE} DESTINATION .)
	endif(MYPATH)
endforeach(MYFILE ${XIP_EXTRA_FILES_TO_INSTALL})


#--------------------------------------------------------------------
# Testing
#
if(BUILD_TESTING)
set(TESTING_DIR ${CMAKE_BINARY_DIR}/Testing/Temporary)

foreach(EXAMPLE ${XIP_EXAMPLES})
  get_filename_component(SHORT_FILENAME ${EXAMPLE} NAME_WE)

  set(TESTED_SCREENSHOT ${TESTING_DIR}/${SHORT_FILENAME}.png)
  set(DIFFERENCE_IMAGE ${TESTING_DIR}/${SHORT_FILENAME}_diff.png)
  set(FILE_COMPARE_XML ${TESTING_DIR}/${SHORT_FILENAME}.xml)
  set(RENDER_FILE ${TESTING_DIR}/${SHORT_FILENAME}.txt)

  set(EXPECTED_SCREENSHOT
    ${CMAKE_CURRENT_SOURCE_DIR}/test/expected/${SHORT_FILENAME}.png)
  set(EXPECTED_ACCURACY
    ${CMAKE_CURRENT_SOURCE_DIR}/test/expected/${SHORT_FILENAME}.txt)

  if(EXISTS ${EXPECTED_SCREENSHOT})
    file(WRITE ${RENDER_FILE}
      "render(256,256,\"" ${TESTED_SCREENSHOT} "\");")
    add_test(${SHORT_FILENAME}Screenshot
      #${XIP_BUILDER_RELEASE} ${EXAMPLE}
      xipbuilder ${XIP_EXAMPLES_DIR}/${EXAMPLE}
      /config=${CMAKE_BINARY_DIR}/config
      /cmd=${RENDER_FILE})

  endif(EXISTS ${EXPECTED_SCREENSHOT})

endforeach(EXAMPLE ${XIP_EXAMPLES})

endif(BUILD_TESTING)

#--------------------------------------------------------------------
# Configure files for the Doxygen documentation
#
configure_file(${CMAKE_SOURCE_DIR}/build/Doxyfile.in
  ${CMAKE_BINARY_DIR}/config/Doxyfile)

#--------------------------------------------------------------------
# Configure files to locate the XIP binaries
#
configure_file(${CMAKE_SOURCE_DIR}/build/XIPConfig.cmake.in
  ${CMAKE_BINARY_DIR}/XIPConfig.cmake)

configure_file(${CMAKE_SOURCE_DIR}/build/UseXIP.cmake.in
  ${CMAKE_BINARY_DIR}/UseXIP.cmake)

configure_file(${CMAKE_SOURCE_DIR}/build/XIPFooter.html
  ${CMAKE_BINARY_DIR}/config/XIPFooter.html)

configure_file(${CMAKE_SOURCE_DIR}/build/XIPConfigInstall.cmake.in
  ${CMAKE_BINARY_DIR}/config/XIPConfig.cmake)

configure_file(${CMAKE_SOURCE_DIR}/build/UseXIPInstall.cmake.in
  ${CMAKE_BINARY_DIR}/config/UseXIP.cmake)

#--------------------------------------------------------------------
# Configure text files and icons
#
#configure_file(${CMAKE_SOURCE_DIR}/README.txt
#  ${CMAKE_BINARY_DIR}/README.txt COPYONLY)

configure_file(${CMAKE_SOURCE_DIR}/XIP_LICENSE.txt
  ${CMAKE_BINARY_DIR}/XIP_LICENSE.txt COPYONLY)

configure_file(${CMAKE_SOURCE_DIR}/HELP.html
  ${CMAKE_BINARY_DIR}/HELP.html COPYONLY)

configure_file(${CMAKE_SOURCE_DIR}/doc/xip_logo.bmp
  ${CMAKE_BINARY_DIR}/config/xip_logo.bmp COPYONLY)

configure_file(${CMAKE_SOURCE_DIR}/build/xip_icon.ico
  ${CMAKE_BINARY_DIR}/config/xip_icon.ico COPYONLY)

#--------------------------------------------------------------------
# Export the build settings and library dependencies
#
include(CMakeExportBuildSettings)

cmake_export_build_settings(
  ${CMAKE_BINARY_DIR}/XIPBuildSettings.cmake)

export_library_dependencies(
  ${CMAKE_BINARY_DIR}/XIPLibraryDepends.cmake)

#--------------------------------------------------------------------
# Install the packaging files for use by find_package(XIP)
#
install(FILES
  ${CMAKE_BINARY_DIR}/config/UseXIP.cmake
  ${CMAKE_BINARY_DIR}/config/XIPConfig.cmake
  ${CMAKE_BINARY_DIR}/XIPBuildSettings.cmake
  ${CMAKE_BINARY_DIR}/XIPLibraryDepends.cmake
  DESTINATION lib)

#--------------------------------------------------------------------
# Doxygen commands
#
if(false)
add_custom_command(TARGET target POST_BUILD
  COMMAND DOT_EXECUTABLE ${CMAKE_BINARY_DIR}/Doxyfile
  ${CMAKE_BINARY_DIR}
  COMMENT "Generate the Doxygen documentation")
endif(false)
