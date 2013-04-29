# Sylvain Jaume 2007

project(src)

#--------------------------------------------------------------------
# Definitions
#
if(WIN32)
  add_definitions(-DNOMINMAX)
endif(WIN32)

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
 add_definitions(-DDARWIN)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

#--------------------------------------------------------------------
# Include directories
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
# Subdirectories
#
add_subdirectory(common)
add_subdirectory(database)

if(WIN32) # Not yet supported on MacOSX
  add_subdirectory(rendernode)
endif(WIN32)

if(BUILD_INVENTOR)
  add_subdirectory(extern)
endif(BUILD_INVENTOR)
