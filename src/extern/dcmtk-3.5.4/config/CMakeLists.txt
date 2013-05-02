# Modified by Sylvain Jaume <sylvain.jaume@siemens.com> 2008

project(config)

# Install header files
install(FILES
  include/dcmtk/config/osconfig.h
  include/dcmtk/config/cfwin32.h
  DESTINATION include/dcmtk/${PROJECT_NAME})
