# Copyright Siemens Corporate Research Inc. 2008
# Author Sylvain Jaume <sylvain.jaume@siemens.com>

project(inventor)

#--------------------------------------------------------------------
# Define the compiler flags
#
if(WIN32)
  add_definitions(-DINVENTOR_EXPORTS)
endif(WIN32)

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  add_definitions(-DDARWIN)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

#--------------------------------------------------------------------
# Define the include directories
#
include_directories(
  lib/database/include
  lib/interaction/include
  lib/mevis/include
  lib/nodekits/include
  lib/xip/include
  ../../../include)

#--------------------------------------------------------------------
# Compile the executable
#
if(WIN32)
  add_custom_command(TARGET xipinv240
    PRE_BUILD COMMAND ${PROJECT_SOURCE_DIR}/gensources.bat)
else(WIN32)
  #add_executable(ppp tools/ppp/ppp.c++)
  add_custom_command(TARGET xipinv240
    PRE_BUILD COMMAND gensources.sh)
endif(WIN32)

#--------------------------------------------------------------------
# Build projects inside subdirectories
#
add_subdirectory(libFL)
add_subdirectory(libimage)
add_subdirectory(lib)

#add_dependencies(xipinv240 ppp)
