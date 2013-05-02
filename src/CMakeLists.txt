# Copyright Siemens Corporate Research Inc. 2007
# Author Sylvain Jaume <sylvain.jaume@siemens.com>

project(src)

#--------------------------------------------------------------------
# Set preprocessor definition for SbSystem.h to indicate whether 
# to use the debug postfix
#
if(DEBUG_POSTFIX)
	add_definitions(-D_DEBUG_POSTFIX)
endif(DEBUG_POSTFIX)


#--------------------------------------------------------------------
# Define the compiler flags
#
if(WIN32)
  add_definitions(-DNOMINMAX)
endif(WIN32)

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
 add_definitions(-DDARWIN)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")


#--------------------------------------------------------------------
# Set preprocessor definition for SbSystem.h to indicate whether 
# to use the debug postfix
#
if(DEBUG_POSTFIX)
	add_definitions(-D_DEBUG_POSTFIX)
endif(DEBUG_POSTFIX)

#--------------------------------------------------------------------
# Define the include directories
#
include_directories(
  ../include
  extern/inventor/lib/database/include
  extern/inventor/lib/interaction/include
  extern/inventor/lib/mevis/include
  extern/inventor/lib/nodekits/include
  extern/inventor/lib/xip/include
  /opt/local/include) # Used for Macports

#--------------------------------------------------------------------
# Build the subprojects
#
add_subdirectory(common)
add_subdirectory(extern)
add_subdirectory(database)

if(WIN32) # Not yet supported on MacOSX
  add_subdirectory(rendernode)
endif(WIN32)
