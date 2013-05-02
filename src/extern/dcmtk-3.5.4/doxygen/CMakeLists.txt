# Modified by Sylvain Jaume <sylvain.jaume@siemens.com> 2008

project(doxygen)

#--------------------------------------------------------------------
# Locate executable for Doxygen support
#
if(DOXYGEN_EXECUTABLE)
  add_custom_target(DOXYGEN ${DOXYGEN_EXECUTABLE} htmldocs.cfg)
endif(DOXYGEN_EXECUTABLE)

#--------------------------------------------------------------------
# Define the installation files
#
file(GLOB_RECURSE HTMLDOCS_FILES htmldocs/*)
install(FILES ${HTMLDOCS_FILES} DESTINATION doc)
