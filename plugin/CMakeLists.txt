# Copyright Siemens Corporate Research Inc. 2008
# Author Sylvain Jaume <sylvain.jaume@siemens.com>

project(xipplugin)

#--------------------------------------------------------------------
# Define the required CMake version
#
cmake_minimum_required(VERSION 2.6.3)

#--------------------------------------------------------------------
# Define the header files
#
set(HEADERS
  SoXipPluginSlicer.h)

#--------------------------------------------------------------------
# Define the source files
#
set(SOURCES
  SoXipPluginSlicer.cpp
  init.cpp)

#--------------------------------------------------------------------
# Define the compiler flags
#
if(WIN32)
  add_definitions(-DXIPPLUGIN_EXPORTS)
else(WIN32)
  add_definitions(-DHAVE_CONFIG_H)
endif(WIN32)

#--------------------------------------------------------------------
# Disable deprecation warnings for standard C functions
#
if(CMAKE_COMPILER_2005)
  add_definitions(
    -D_CRT_SECURE_NO_DEPRECATE
    -D_CRT_NONSTDC_NO_DEPRECATE)
endif(CMAKE_COMPILER_2005)

#--------------------------------------------------------------------
# Locate XIP libraries and include directories
#
find_package(XIP REQUIRED)
include(${XIP_USE_FILE})

#--------------------------------------------------------------------
# Compile the library
#
add_library(xipplugin SHARED ${HEADERS} ${SOURCES})

set_target_properties(xipplugin
  PROPERTIES VERSION ${XIP_VERSION_STRING}
  SOVERSION ${XIP_VERSION_STRING})

#--------------------------------------------------------------------
# Link the library
#
target_link_libraries(xipplugin ${XIP_LIBRARIES})
