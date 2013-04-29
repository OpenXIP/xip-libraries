# Sylvain Jaume 2008

project(common)

#--------------------------------------------------------------------
# Source files
#
set(SOURCES
  XipException.cpp)

#--------------------------------------------------------------------
# Define compiler flags
#
if(WIN32)
  add_definitions(-DXIPIVCOMMON_EXPORTS)
else(WIN32)
  add_definitions(-DHAVE_CONFIG_H)
endif(WIN32)

#--------------------------------------------------------------------
# Compile library
#
add_library(xipcommon SHARED ${SOURCES})

#--------------------------------------------------------------------
# Install library
#
install(TARGETS xipcommon
  RUNTIME DESTINATION bin/debug CONFIGURATIONS Debug
  ARCHIVE DESTINATION lib/debug CONFIGURATIONS Debug
  LIBRARY DESTINATION lib/debug CONFIGURATIONS Debug)

install(TARGETS xipcommon
  RUNTIME DESTINATION bin/release CONFIGURATIONS Release
  ARCHIVE DESTINATION lib/release CONFIGURATIONS Release
  LIBRARY DESTINATION lib/release CONFIGURATIONS Release)

if(WIN32)
  install(FILES ${LIBRARY_OUTPUT_PATH}/debug/xipcommon.pdb
    DESTINATION bin/debug CONFIGURATIONS Debug)
endif(WIN32)
