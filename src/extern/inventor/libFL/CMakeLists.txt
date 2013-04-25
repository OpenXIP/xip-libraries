# Sylvain Jaume 2008
project(FL)

if(WIN32)
  add_definitions(-DWIN32 -DINVENTOR_EXPORTS -D__SGIOIV_BUILD_DLL
    -D_CRT_SECURE_NO_WARNINGS)
else(WIN32)
  add_definitions(-DIVPREFIX="/*_*/")
  find_package(Freetype)

  if(NOT FREETYPE_FOUND)
    find_library(FREETYPE_LIBRARY freetype "C:\\Program Files\\GnuWin32\\lib")
    find_path(FREETYPE_INCLUDE_DIR_ft2build ft2build.h
	  "C:\\Program Files\\GnuWin32\\include")
    find_path(FREETYPE_INCLUDE_DIR_freetype2 "freetype/freetype.h"
	  "C:\\Program Files\\GnuWin32\\include\\freetype2")
    set(FREETYPE_INCLUDE_DIRS ${FREETYPE_INCLUDE_DIR_ft2build}
	  ${FREETYPE_INCLUDE_DIR_freetype2})
    set(FREETYPE_LIBRARIES ${FREETYPE_LIBRARY})
  endif(NOT FREETYPE_FOUND)

endif(WIN32)

include_directories(
  ang
  src)

if(WIN32)
  include_directories(../../freetype-2.2.1/include)
else(WIN32)
  include_directories(${FREETYPE_INCLUDE_DIRS})
endif(WIN32)

set(HEADERS
  ang/fl.h
  ang/flendian.h
  ang/flfreetype.h
  src/flclient.h)

set(SOURCES
  ang/fl.c
  ang/flclient.c
  ang/flfreetype.c)

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  #SET(GUI_TYPE MACOSX_BUNDLE)
  INCLUDE_DIRECTORIES(/Developer/Headers/FlatCarbon)
  FIND_LIBRARY(CARBON_LIBRARY Carbon)
  FIND_LIBRARY(APP_SERVICES_LIBRARY ApplicationServices)
  MARK_AS_ADVANCED(CARBON_LIBRARY)
  MARK_AS_ADVANCED(APP_SERVICES_LIBRARY)
  SET(EXTRA_LIBS ${CARBON_LIBRARY} ${APP_SERVICES_LIBRARY})
endif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

add_library(FL STATIC ${HEADERS} ${SOURCES})

if(WIN32)
  target_link_libraries(FL freetype)
else(WIN32)
  target_link_libraries(FL ${FREETYPE_LIBRARIES} ${EXTRA_LIBS})
endif(WIN32)
