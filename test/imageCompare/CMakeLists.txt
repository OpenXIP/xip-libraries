# Copyright Siemens Corporate Research Inc. 2007
# Author Sylvain Jaume

project(imageCompare)

#--------------------------------------------------------------------
# moved from the main CMake file
# 
include(${VTK_USE_FILE})


#--------------------------------------------------------------------
# Include directories
#
include_directories(../../include)

if(HAS_VTK)
  if(VTK_DIR-NOTFOUND)
    message(FATAL_ERROR "ERROR: VTK not found")
  endif(VTK_DIR-NOTFOUND)
  include_directories(${VTK_INCLUDE_DIRS})
endif(HAS_VTK)

#--------------------------------------------------------------------
# Define the link directories
#
link_directories(${VTK_LIBRARY_DIRS})

#--------------------------------------------------------------------
# Compile the executables
#
add_executable(fileCompare fileCompare.cpp)
add_executable(smartFileCompare smartFileCompare.cpp)

if(HAS_VTK)
  add_executable(regressionTest regressionTest.cpp)
endif(HAS_VTK)

#--------------------------------------------------------------------
# Link executable
#
if(HAS_VTK)
  target_link_libraries(regressionTest ${VTK_LIBRARIES})
endif(HAS_VTK)
