# Sylvain Jaume 2007

project(jpegWrapper)

#--------------------------------------------------------------------
# Source files
#
set(SOURCES
  bufferImage.cpp
  bufferImageCod.cpp
  bufferImageJpeg.cpp
  memoryObj.cpp)

#--------------------------------------------------------------------
# Definitions
#
add_definitions(-D_LIB -D__DISABLE_WARNING -DXMD_H)

if(WIN32)
  add_definitions(-DWIN32)
endif(WIN32)

#--------------------------------------------------------------------
# Include directories
#
include_directories(../../../extern/jpeg-6b)

#--------------------------------------------------------------------
# Compile library
#
add_library(jpegWrapper STATIC ${SOURCES})

#--------------------------------------------------------------------
# Install library
#
if(FALSE)
install(TARGETS jpegWrapper
  ARCHIVE DESTINATION lib/debug CONFIGURATIONS Debug)

install(TARGETS jpegWrapper
  ARCHIVE DESTINATION lib/release CONFIGURATIONS Release)
endif(FALSE)
