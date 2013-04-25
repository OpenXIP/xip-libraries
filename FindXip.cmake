# - Find an Xip installation or build tree.

# When Xip is found, the XipConfig.cmake file is sourced to setup the
# location and configuration of Xip.  Please read this file, or
# XipConfig.cmake.in from the Xip source tree for the full list of
# definitions.  Of particular interest is Xip_USE_FILE, a CMake source file
# that can be included to set the include directories, library directories,
# and preprocessor macros.  In addition to the variables read from
# XipConfig.cmake, this find module also defines
#  Xip_DIR  - The directory containing XipConfig.cmake.  
#             This is either the root of the build tree, 
#             or the lib/InsightToolkit directory.  
#             This is the only cache entry.
#   
#  Xip_FOUND - Whether Xip was found.  If this is true, 
#              Xip_DIR is okay.
#
#  USE_Xip_FILE - The full path to the UseXip.cmake file.  
#                 This is provided for backward 
#                 compatability.  Use Xip_USE_FILE
#                 instead.


SET(Xip_DIR_STRING "directory containing XipConfig.cmake.  This is either the root of the build tree, or PREFIX/lib/Xip for an installation.")

# Search only if the location is not already known.
IF(NOT Xip_DIR)
  # Get the system search path as a list.
  IF(UNIX)
    STRING(REGEX MATCHALL "[^:]+" Xip_DIR_SEARCH1 "$ENV{PATH}")
  ELSE(UNIX)
    STRING(REGEX REPLACE "\\\\" "/" Xip_DIR_SEARCH1 "$ENV{PATH}")
  ENDIF(UNIX)
  STRING(REGEX REPLACE "/;" ";" Xip_DIR_SEARCH2 ${Xip_DIR_SEARCH1})

  # Construct a set of paths relative to the system search path.
  SET(Xip_DIR_SEARCH "")
  FOREACH(dir ${Xip_DIR_SEARCH2})
    SET(Xip_DIR_SEARCH ${Xip_DIR_SEARCH} "${dir}/../lib/Xip")
  ENDFOREACH(dir)

  #
  # Look for an installation or build tree.
  #
  FIND_PATH(Xip_DIR XipConfig.cmake
    # Look for an environment variable Xip_DIR.
    $ENV{Xip_DIR}

    # Look in places relative to the system executable search path.
    ${Xip_DIR_SEARCH}

    # Look in standard UNIX install locations.
    /usr/local/lib/Xip
    /usr/lib/Xip

    # Read from the CMakeSetup registry entries.  It is likely that
    # Xip will have been recently built.
    [HKEY_CURRENT_USER\\Software\\Siemens\\CMakeSetup\\Settings\\StartPath;WhereBuild1]
    [HKEY_CURRENT_USER\\Software\\Siemens\\CMakeSetup\\Settings\\StartPath;WhereBuild2]
    [HKEY_CURRENT_USER\\Software\\Siemens\\CMakeSetup\\Settings\\StartPath;WhereBuild3]
    [HKEY_CURRENT_USER\\Software\\Siemens\\CMakeSetup\\Settings\\StartPath;WhereBuild4]
    [HKEY_CURRENT_USER\\Software\\Siemens\\CMakeSetup\\Settings\\StartPath;WhereBuild5]
    [HKEY_CURRENT_USER\\Software\\Siemens\\CMakeSetup\\Settings\\StartPath;WhereBuild6]
    [HKEY_CURRENT_USER\\Software\\Siemens\\CMakeSetup\\Settings\\StartPath;WhereBuild7]
    [HKEY_CURRENT_USER\\Software\\Siemens\\CMakeSetup\\Settings\\StartPath;WhereBuild8]
    [HKEY_CURRENT_USER\\Software\\Siemens\\CMakeSetup\\Settings\\StartPath;WhereBuild9]
    [HKEY_CURRENT_USER\\Software\\Siemens\\CMakeSetup\\Settings\\StartPath;WhereBuild10]

    # Help the user find it if we cannot.
    DOC "The ${Xip_DIR_STRING}"
  )
ENDIF(NOT Xip_DIR)

# If Xip was found, load the configuration file to get the rest of the
# settings.
IF(Xip_DIR)
  SET(Xip_FOUND 1)
  INCLUDE(${Xip_DIR}/XipConfig.cmake)

  message("Xip_USE_FILE "${Xip_USE_FILE})
ELSE(Xip_DIR)
  SET(Xip_FOUND 0)
  IF(Xip_FIND_REQUIRED)
    MESSAGE(FATAL_ERROR "Please set Xip_DIR to the ${Xip_DIR_STRING}")
  ENDIF(Xip_FIND_REQUIRED)
ENDIF(Xip_DIR)
