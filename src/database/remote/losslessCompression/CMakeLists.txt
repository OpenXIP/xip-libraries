# Sylvain Jaume 2007

project(losslessCompression)

#--------------------------------------------------------------------
# Source files.
#
set(SOURCES
  cpuID.cpp
  huffmanCoder.cpp
  rleCoder.cpp)

#--------------------------------------------------------------------
# Definitions.
#
if(WIN32)
  add_definitions(-DXIPIVREMOTE_EXPORTS)
else(WIN32)
  add_definitions(-DHAVE_CONFIG_H)
endif(WIN32)

#--------------------------------------------------------------------
# Library creation.
#
add_library(losslessCompression STATIC ${SOURCES})

#--------------------------------------------------------------------
# Install.
#
install(TARGETS losslessCompression
  ARCHIVE DESTINATION lib/debug CONFIGURATIONS Debug)

install(TARGETS losslessCompression
  ARCHIVE DESTINATION lib/release CONFIGURATIONS Release)
