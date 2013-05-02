# Copyright Siemens Corporate Research 2008
# Author Sylvain Jaume

project(FL)

#--------------------------------------------------------------------
# Find external Freetype package
#
if(UNIX)
  find_package(Freetype)

  #really? why does this belong in the UNIX section...???
  if(NOT FREETYPE_FOUND)
    find_library(FREETYPE_LIBRARY freetype
      "C:\\Program Files\\GnuWin32\\lib")
    find_path(FREETYPE_INCLUDE_DIR_ft2build ft2build.h
      "C:\\Program Files\\GnuWin32\\include")
    find_path(FREETYPE_INCLUDE_DIR_freetype2 "freetype/freetype.h"
      "C:\\Program Files\\GnuWin32\\include\\freetype2")

    set(FREETYPE_INCLUDE_DIRS ${FREETYPE_INCLUDE_DIR_ft2build}
      ${FREETYPE_INCLUDE_DIR_freetype2})
    set(FREETYPE_LIBRARIES ${FREETYPE_LIBRARY})
  endif(NOT FREETYPE_FOUND)
endif(UNIX)

#--------------------------------------------------------------------
# Define compiler flags
#
if(WIN32)
  add_definitions(-DWIN32 -DINVENTOR_EXPORTS -D__SGIOIV_BUILD_DLL
    -D_CRT_SECURE_NO_WARNINGS)
else(WIN32)
  add_definitions(-DIVPREFIX="/*_*/")
endif(WIN32)

#--------------------------------------------------------------------
# Include directories
#
include_directories(
  ang
  src)

if(WIN32)
  include_directories(../../freetype-2.2.1/include)
else(WIN32)
  include_directories(${FREETYPE_INCLUDE_DIRS})
endif(WIN32)

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  #SET(GUI_TYPE MACOSX_BUNDLE)
  include_directories(/Developer/Headers/FlatCarbon)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

#--------------------------------------------------------------------
# Header files
#
set(HEADERS
  ang/fl.h
  ang/flendian.h
  ang/flfreetype.h
  src/flclient.h)

#--------------------------------------------------------------------
# Source files
#
set(SOURCES
  ang/fl.c
  ang/flclient.c
  ang/flfreetype.c)

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  #set(GUI_TYPE MACOSX_BUNDLE)
  find_library(CARBON_LIBRARY Carbon)
  find_library(APP_SERVICES_LIBRARY ApplicationServices)
  mark_as_advanced(CARBON_LIBRARY)
  mark_as_advanced(APP_SERVICES_LIBRARY)
  set(EXTRA_LIBS ${CARBON_LIBRARY} ${APP_SERVICES_LIBRARY})
endif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

#--------------------------------------------------------------------
# Create library
#
if(WIN32)
add_library(FL STATIC ${HEADERS} ${SOURCES})
else(WIN32)
add_library(FL SHARED ${HEADERS} ${SOURCES})
endif(WIN32)
#--------------------------------------------------------------------
# Link library
#
target_link_libraries(FL ${FREETYPE_LIBRARIES} ${EXTRA_LIBS})
