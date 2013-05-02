# Modified by Sylvain Jaume <sylvain.jaume@siemens.com> 2008

project(zlib)

#--------------------------------------------------------------------
# Define include directories
#
include_directories(BEFORE ${PROJECT_SOURCE_DIR}
  ${PROJECT_BINARY_DIR})

#--------------------------------------------------------------------
# Define header files
#
set(HEADERS
  crc32.h
  deflate.h
  inffast.h
  inffixed.h
  inflate.h
  inftrees.h
  trees.h
  vtk_zlib_mangle.h
  zconf.h
  zlib.h
  zutil.h)

#--------------------------------------------------------------------
# Define the source files
#
set(SOURCES
  adler32.c
  compress.c
  crc32.c
  deflate.c
  gzio.c
  inffast.c
  inflate.c
  inftrees.c
  trees.c
  uncompr.c
  zutil.c)

#--------------------------------------------------------------------
# for windows add the .def and .rc files to the source list
# if building shared libs
#
if(WIN32)
  if(BUILD_SHARED_LIBS)
    set(ZLIB_DLL 1)
    if(NOT UNIX)
      if(NOT BORLAND)
        if(NOT MINGW)
          set(SOURCES ${SOURCES} zlib.def zlib.rc)
        endif(NOT MINGW)
      endif(NOT BORLAND)
    endif(NOT UNIX)
  endif(BUILD_SHARED_LIBS)
endif(WIN32)

#--------------------------------------------------------------------
# Create configuration header file
#
configure_file(${PROJECT_SOURCE_DIR}/zlibDllConfig.h.in
  ${PROJECT_BINARY_DIR}/zlibDllConfig.h)

#--------------------------------------------------------------------
# Compile the library
#
add_library(zlib STATIC ${HEADERS} ${SOURCES})

set_target_properties(zlib
  PROPERTIES VERSION 1.2 SOVERSION 1.2)

#--------------------------------------------------------------------
# Install the library
#
install(TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION bin/release CONFIGURATIONS Release
  LIBRARY DESTINATION lib/release CONFIGURATIONS Release
  ARCHIVE DESTINATION lib/release CONFIGURATIONS Release
  BUNDLE  DESTINATION lib/release CONFIGURATIONS Release)

install(TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION bin/debug CONFIGURATIONS Debug
  LIBRARY DESTINATION lib/debug CONFIGURATIONS Debug
  ARCHIVE DESTINATION lib/debug CONFIGURATIONS Debug
	BUNDLE  DESTINATION lib/debug CONFIGURATIONS Debug)

if(WIN32)
  install(FILES ${LIBRARY_OUTPUT_PATH}/debug/${PROJECT_NAME}${CMAKE_DEBUG_POSTFIX}.pdb
    DESTINATION bin/debug CONFIGURATIONS Debug)
endif(WIN32)

#--------------------------------------------------------------------
# Install header files
#
install(FILES
  zlib.h
  zconf.h
  vtk_zlib_mangle.h
  ${PROJECT_BINARY_DIR}/zlibDllConfig.h
  DESTINATION include/${PROJECT_NAME}
  COMPONENT Development)
