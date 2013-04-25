# Sylvain Jaume 2007

project(database)

#--------------------------------------------------------------------
# Link directories.
#
link_directories(${Xip_BINARY_DIR}/out)

#--------------------------------------------------------------------
# Subdirectories.
#
add_subdirectory(core)
add_subdirectory(coregl)
add_subdirectory(renderer)

if(WIN32)
  add_subdirectory(remote) # FIXME: issues with ppc architecture
endif(WIN32)

if(HAS_DCMTK)
  add_subdirectory(dicom)
  add_subdirectory(overlay)
endif(HAS_DCMTK)

if(HAS_ITK)
  add_subdirectory(itk)
endif(HAS_ITK)

if(HAS_VTK)
  add_subdirectory(vtk)
endif(HAS_VTK)
