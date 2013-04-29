# Sylvain Jaume 2007

project(stream)

#--------------------------------------------------------------------
# Source files
#
set(SOURCES
  XipRequestManager.cpp
  XipStream.cpp)

#--------------------------------------------------------------------
# Define compiler flags
#
if(WIN32)
  add_definitions(-DXIPIVREMOTE_EXPORTS)
else(WIN32)
  add_definitions(-DHAVE_CONFIG_H)
endif(WIN32)

#--------------------------------------------------------------------
# Compile library
#
add_library(stream STATIC ${SOURCES})

#--------------------------------------------------------------------
# Install library
#
if(FALSE)
install(TARGETS stream
  ARCHIVE DESTINATION lib/debug CONFIGURATIONS Debug)

install(TARGETS stream
  ARCHIVE DESTINATION lib/release CONFIGURATIONS Release)
endif(FALSE)
