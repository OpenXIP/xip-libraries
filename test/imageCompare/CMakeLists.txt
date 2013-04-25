# Sylvain Jaume 2007

project(imageCompare)

include_directories(${Xip_SOURCE_DIR}/include)

add_executable(fileCompare fileCompare.cpp)
add_executable(smartFileCompare smartFileCompare.cpp)

if(HAS_VTK)

  include_directories(${XIPEXT}/vtk/include/vtk-5.0)

  link_directories(${XIPEXT}/vtk/lib)

  add_executable(color-utils color-utils.cpp)
  #add_executable(dummy dummy.cpp)

  target_link_libraries(color-utils
    vtkCommon
    vtkDICOMParser
    vtkexoIIc
    vtkexpat
    vtkFiltering
    vtkfreetype
    vtkftgl
    vtkGenericFiltering
    vtkGraphics
    vtkHybrid
    vtkIO
    vtkImaging
    vtkjpeg
    vtkNetCDF
    vtkRendering
    vtkpng)

#target_link_libraries(dummy
#   vtkCommon)

else(HAS_VTK)
  message("Warning: HAS_VTK is OFF. Tests cannot be built.")
endif(HAS_VTK)
