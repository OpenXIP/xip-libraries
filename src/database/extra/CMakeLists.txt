# Copyright Siemens Corporate Research Inc. 2007
# Author Sylvain Jaume <sylvain.jaume@siemens.com>

project(extra)

#--------------------------------------------------------------------
# Define the header files
#
set(HEADERS
  ../../../include/xip/inventor/extra/xipivextra.h
  ../../../include/xip/inventor/extra/SoSFDouble.h
  ../../../include/xip/inventor/extra/SoMFDouble.h
#  SoDoubleCalculator.h
)

#--------------------------------------------------------------------
# Define the source files
#
set(SOURCES
  SoSFDouble.cpp
  SoMFDouble.cpp
#  SoDoubleCalculator.cpp
  init.cpp)

#--------------------------------------------------------------------
# Define the compiler flags
#
if(WIN32)
  add_definitions(-DXIPIVEXTRA_EXPORTS)
else(WIN32)
  add_definitions(-DHAVE_CONFIG_H)
endif(WIN32)

#--------------------------------------------------------------------
# Define the include directories
#
include_directories(
    ../../extern/inventor/lib/database/src/so/engines)

if(UNIX)
  include_directories(
    ${PROJECT_BINARY_DIR} # for generated config.h
    ${OIV_PATH}/include/
    ../../../include
    /usr/include 
    /usr/include/libxml2/) 
endif(UNIX)

#--------------------------------------------------------------------
# Compile the library
#
if(BUILD_SHARED_LIBS)
  add_library(xipivextra SHARED ${HEADERS} ${SOURCES})
else(BUILD_SHARED_LIBS)
  add_library(xipivextra STATIC ${HEADERS} ${SOURCES})
endif(BUILD_SHARED_LIBS)

set_target_properties(xipivextra
  PROPERTIES VERSION ${XIP_VERSION_STRING}
  SOVERSION ${XIP_VERSION_STRING})

#--------------------------------------------------------------------
# Link the library
#
target_link_libraries(xipivextra
  ${XIP_COMMON_LIBRARY}
  ${INVENTOR_LIBRARY}
  ${OPENGL_LIBRARIES}
  ${GLEW_LIBRARIES}
)

add_dependencies(xipivextra xipcommon)
  
#--------------------------------------------------------------------
# Install the library
#
install(TARGETS xipivextra
  RUNTIME DESTINATION bin/release CONFIGURATIONS Release
  ARCHIVE DESTINATION lib/release CONFIGURATIONS Release
  LIBRARY DESTINATION lib/release CONFIGURATIONS Release
  BUNDLE  DESTINATION lib/release CONFIGURATIONS Release)

install(TARGETS xipivextra
  RUNTIME DESTINATION bin/debug   CONFIGURATIONS Debug
  ARCHIVE DESTINATION lib/debug   CONFIGURATIONS Debug
  LIBRARY DESTINATION lib/debug   CONFIGURATIONS Debug
  BUNDLE  DESTINATION lib/debug   CONFIGURATIONS Debug)

if(WIN32)
  install(FILES ${LIBRARY_OUTPUT_PATH}/debug/xipivextra${CMAKE_DEBUG_POSTFIX}.pdb
    DESTINATION bin/debug CONFIGURATIONS Debug)
endif(WIN32)
