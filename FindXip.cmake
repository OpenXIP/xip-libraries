# - Find an XIP installation or build tree.

# When XIP is found, the XIPConfig.cmake file is sourced to setup the
# location and configuration of XIP.  Please read this file, or
# XIPConfig.cmake.in from the XIP source tree for the full list of
# definitions.  Of particular interest is XIP_USE_FILE, a CMake source file
# that can be included to set the include directories, library directories,
# and preprocessor macros.  In addition to the variables read from
# XIPConfig.cmake, this find module also defines
#  XIP_DIR  - The directory containing XIPConfig.cmake.  
#             This is either the root of the build tree, 
#             or the lib/InsightToolkit directory.  
#             This is the only cache entry.
#   
#  XIP_FOUND - Whether XIP was found.  If this is true, 
#              XIP_DIR is okay.
#
#  USE_XIP_FILE - The full path to the UseXIP.cmake file.  
#                 This is provided for backward 
#                 compatability.  Use XIP_USE_FILE
#                 instead.


SET(XIP_DIR_STRING "directory containing XIPConfig.cmake.  This is either the root of the build tree, or PREFIX/lib/XIP for an installation.")

# Search only if the location is not already known.
IF(NOT XIP_DIR)
  # Get the system search path as a list.
  IF(UNIX)
    STRING(REGEX MATCHALL "[^:]+" XIP_DIR_SEARCH1 "$ENV{PATH}")
  ELSE(UNIX)
    STRING(REGEX REPLACE "\\\\" "/" XIP_DIR_SEARCH1 "$ENV{PATH}")
  ENDIF(UNIX)
  STRING(REGEX REPLACE "/;" ";" XIP_DIR_SEARCH2 ${XIP_DIR_SEARCH1})

  # Construct a set of paths relative to the system search path.
  SET(XIP_DIR_SEARCH "")
  FOREACH(dir ${XIP_DIR_SEARCH2})
    SET(XIP_DIR_SEARCH ${XIP_DIR_SEARCH} "${dir}/../lib/XIP")
  ENDFOREACH(dir)

  #
  # Look for an installation or build tree.
  #
  FIND_PATH(XIP_DIR XIPConfig.cmake
    # Look for an environment variable XIP_DIR.
    $ENV{XIP_DIR}

    # Look in places relative to the system executable search path.
    ${XIP_DIR_SEARCH}

    # Look in standard UNIX install locations.
    /usr/local/lib/XIP
    /usr/lib/XIP

    # Read from the CMakeSetup registry entries.  It is likely that
    # XIP will have been recently built.
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
    DOC "The ${XIP_DIR_STRING}"
  )
ENDIF(NOT XIP_DIR)

# If XIP was found, load the configuration file to get the rest of the
# settings.
IF(XIP_DIR)
  SET(XIP_FOUND 1)
  INCLUDE(${XIP_DIR}/XIPConfig.cmake)

  message("XIP_USE_FILE "${XIP_USE_FILE})
ELSE(XIP_DIR)
  SET(XIP_FOUND 0)
  IF(XIP_FIND_REQUIRED)
    MESSAGE(FATAL_ERROR "Please set XIP_DIR to the ${XIP_DIR_STRING}")
  ENDIF(XIP_FIND_REQUIRED)
ENDIF(XIP_DIR)
