# Sylvain Jaume 2008

project(inventor)

#--------------------------------------------------------------------
# Definitions.
#
if(WIN32)
  add_definitions(-DINVENTOR_EXPORTS)
endif(WIN32)

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  add_definitions(-DDARWIN)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

#--------------------------------------------------------------------
# Include directories.
#
include_directories(
  lib/database/include
  lib/interaction/include
  lib/mevis/include
  lib/nodekits/include
  lib/xip/include)

#--------------------------------------------------------------------
# Executable creation.
#
if(WIN32)
  add_custom_command(TARGET xipinv240
    PRE_BUILD COMMAND ${PROJECT_SOURCE_DIR}/gensources.bat)
else(WIN32)
  add_executable(ppp tools/ppp/ppp.c++)
  add_custom_command(TARGET xipinv240
    PRE_BUILD COMMAND gensources.sh)
ENDIF(WIN32)

#--------------------------------------------------------------------
# Subdirectories.
#
add_subdirectory(libFL)
add_subdirectory(libimage)
add_subdirectory(lib)
