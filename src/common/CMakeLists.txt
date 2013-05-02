# Copyright Siemens Corporate Research Inc. 2007
# Author Sylvain Jaume <sylvain.jaume@siemens.com>

project(common)

#--------------------------------------------------------------------
# Define the header files
#
set(HEADERS
  ../../include/xip/common/XipCommon.h
  ../../include/xip/common/XipException.h
  ../../include/xip/common/XipDebug.h
  ../../include/xip/common/XipLog.h
  ../../include/xip/common/XipTimer.h
)

#--------------------------------------------------------------------
# Define the source files
#
set(SOURCES
  XipException.cpp
  XipDebug.cpp
  XipLog.cpp
  XipTimer.cpp
)

#--------------------------------------------------------------------
# Define the compiler flags
#
if(WIN32)
  add_definitions(-DXIPCOMMON_EXPORTS)
else(WIN32)
  add_definitions(-DHAVE_CONFIG_H)
endif(WIN32)

#--------------------------------------------------------------------
# Compile the library
#
if(BUILD_SHARED_LIBS)
  add_library(xipcommon SHARED ${HEADERS} ${SOURCES})
else(BUILD_SHARED_LIBS)
  add_library(xipcommon STATIC ${HEADERS} ${SOURCES})
endif(BUILD_SHARED_LIBS)

set_target_properties(xipcommon
  PROPERTIES VERSION ${XIP_VERSION_STRING}
  SOVERSION ${XIP_VERSION_STRING})

#--------------------------------------------------------------------
# Link the library
#
target_link_libraries(xipcommon
	${INVENTOR_LIBRARY})

# add_dependencies(xipcommon xipinv240)


#--------------------------------------------------------------------
# Install the library
#
install(TARGETS xipcommon
  RUNTIME DESTINATION bin/release CONFIGURATIONS Release
  ARCHIVE DESTINATION lib/release CONFIGURATIONS Release
  LIBRARY DESTINATION lib/release CONFIGURATIONS Release
  BUNDLE  DESTINATION lib/release CONFIGURATIONS Release)

install(TARGETS xipcommon
  RUNTIME DESTINATION bin/debug   CONFIGURATIONS Debug
  ARCHIVE DESTINATION lib/debug   CONFIGURATIONS Debug
  LIBRARY DESTINATION lib/debug   CONFIGURATIONS Debug
  BUNDLE  DESTINATION lib/debug   CONFIGURATIONS Debug)

if(WIN32)
  install(FILES ${LIBRARY_OUTPUT_PATH}/debug/xipcommon${CMAKE_DEBUG_POSTFIX}.pdb
    DESTINATION bin/debug CONFIGURATIONS Debug)
endif(WIN32)
