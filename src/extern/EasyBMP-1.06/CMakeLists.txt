# Copyright Siemens Corporate Research Inc. 2008
# Author Sylvain Jaume <sylvain.jaume@siemens.com>

project(EasyBMP)

#--------------------------------------------------------------------
# Define the header files
#
set(HEADERS
  EasyBMP.h
  EasyBMP_BMP.h
  EasyBMP_DataStructures.h
  EasyBMP_VariousBMPutilities.h)

#--------------------------------------------------------------------
# Define the source files
#
set(SOURCES
  EasyBMP.cpp)

#--------------------------------------------------------------------
# Compile the library
#
add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCES})

#--------------------------------------------------------------------
# Install the header files
#
foreach(MYFILE ${HEADERS})
  install(FILES ${MYFILE} DESTINATION include/${PROJECT_NAME})
endforeach(MYFILE ${HEADERS})

#--------------------------------------------------------------------
# Install the library
#
install(TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION bin/release CONFIGURATIONS Release
  LIBRARY DESTINATION lib/release CONFIGURATIONS Release
  ARCHIVE DESTINATION lib/release CONFIGURATIONS Release
  BUNDLE  DESTINATION lib/release CONFIGURATIONS Release)

install(TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION bin/debug CONFIGURATIONS Debug
  LIBRARY DESTINATION lib/debug CONFIGURATIONS Debug
  ARCHIVE DESTINATION lib/debug CONFIGURATIONS Debug
	BUNDLE  DESTINATION lib/debug CONFIGURATIONS Debug)

if(WIN32)
  install(FILES ${LIBRARY_OUTPUT_PATH}/debug/${PROJECT_NAME}d.pdb
    DESTINATION bin/debug CONFIGURATIONS Debug)
endif(WIN32)
