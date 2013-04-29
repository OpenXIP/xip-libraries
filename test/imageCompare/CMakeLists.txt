# Sylvain Jaume 2007

project(imageCompare)

#--------------------------------------------------------------------
# Include directories
#
include_directories(../../include)

if(HAS_VTK)
  include_directories(${VTK_INCLUDE_DIRS})
endif(HAS_VTK)

#--------------------------------------------------------------------
# Link directories
#
if(HAS_VTK)
  link_directories(${VTK_DIR}/..)
endif(HAS_VTK)

#--------------------------------------------------------------------
# Compile executables
#
add_executable(fileCompare fileCompare.cpp)
add_executable(smartFileCompare smartFileCompare.cpp)

if(HAS_VTK)
  add_executable(color-utils color-utils.cpp)
endif(HAS_VTK)

#--------------------------------------------------------------------
# Link executable
#
if(HAS_VTK)
  target_link_libraries(color-utils
    vtkFiltering
    vtkIO
    vtkImaging)
endif(HAS_VTK)
