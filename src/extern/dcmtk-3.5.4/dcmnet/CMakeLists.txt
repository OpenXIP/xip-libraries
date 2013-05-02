# Modified by Sylvain Jaume <sylvain.jaume@siemens.com> 2008

project(dcmnet)

# declare include directories which hold for all subdirectories
include_directories(
  include
  ../ofstd/include
  ../dcmdata/include
  ${ZLIB_INCDIR})

#--------------------------------------------------------------------
# Recurse into subdirectories
#
add_subdirectory(etc)
#add_subdirectory(apps)
#add_subdirectory(docs)

#--------------------------------------------------------------------
# Define the headers
#
set(HEADERS
  include/dcmtk/dcmnet/assoc.h
  include/dcmtk/dcmnet/cond.h
  include/dcmtk/dcmnet/dcasccff.h
  include/dcmtk/dcmnet/dcasccfg.h
  include/dcmtk/dcmnet/dccfenmp.h
  include/dcmtk/dcmnet/dccfpcmp.h
  include/dcmtk/dcmnet/dccfprmp.h
  include/dcmtk/dcmnet/dccfrsmp.h
  include/dcmtk/dcmnet/dccftsmp.h
  include/dcmtk/dcmnet/dccfuidh.h
  include/dcmtk/dcmnet/dcmlayer.h
  include/dcmtk/dcmnet/dcmsmap.h
  include/dcmtk/dcmnet/dcmtrans.h
  include/dcmtk/dcmnet/dcompat.h
  include/dcmtk/dcmnet/dicom.h
  include/dcmtk/dcmnet/dimse.h
  include/dcmtk/dcmnet/diutil.h
  include/dcmtk/dcmnet/dul.h
  include/dcmtk/dcmnet/extneg.h
  include/dcmtk/dcmnet/lst.h)

#--------------------------------------------------------------------
# Define some additional header files
#
set(EXTRA_HEADERS
  dimcmd.h
  dulfsm.h
  dulpriv.h
  dulstruc.h)

#--------------------------------------------------------------------
# Define the source files
#
set(SOURCES
  libsrc/assoc.cxx
  libsrc/cond.cxx
  libsrc/dcasccff.cxx
  libsrc/dcasccfg.cxx
  libsrc/dccfenmp.cxx
  libsrc/dccfpcmp.cxx
  libsrc/dccfprmp.cxx
  libsrc/dccfrsmp.cxx
  libsrc/dccftsmp.cxx
  libsrc/dccfuidh.cxx
  libsrc/dcmlayer.cxx
  libsrc/dcmtrans.cxx
  libsrc/dcompat.cxx
  libsrc/dimcancl.cxx
  libsrc/dimcmd.cxx
  libsrc/dimdump.cxx
  libsrc/dimecho.cxx
  libsrc/dimfind.cxx
  libsrc/dimget.cxx
  libsrc/dimmove.cxx
  libsrc/dimse.cxx
  libsrc/dimstore.cxx
  dilibsrc/util.cxx
  libsrc/dul.cxx
  libsrc/dulconst.cxx
  libsrc/dulextra.cxx
  libsrc/dulfsm.cxx
  libsrc/dulparse.cxx
  libsrc/dulpres.cxx
  libsrc/extneg.cxx
  libsrc/lst.cxx)				

#--------------------------------------------------------------------
# Compile the library
#
add_library(${PROJECT_NAME} STATIC ${HEADERS} ${EXTRA_HEADERS}
  ${SOURCES})

install(FILES ${HEADERS}
  DESTINATION include/dcmtk/${PROJECT_NAME})

#--------------------------------------------------------------------
# Install the library
#
install(TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION bin/release CONFIGURATIONS Release
	ARCHIVE DESTINATION lib/release CONFIGURATIONS Release
  LIBRARY DESTINATION lib/release CONFIGURATIONS Release
  BUNDLE  DESTINATION lib/release CONFIGURATIONS Release)

install(TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION bin/debug CONFIGURATIONS Debug
  ARCHIVE DESTINATION lib/debug CONFIGURATIONS Debug
  LIBRARY DESTINATION lib/debug CONFIGURATIONS Debug
  BUNDLE  DESTINATION lib/debug CONFIGURATIONS Debug)

#if(WIN32)
#  install(FILES ${LIBRARY_OUTPUT_PATH}/debug/${PROJECT_NAME}${CMAKE_DEBUG_POSTFIX}.pdb
#    DESTINATION bin/debug CONFIGURATIONS Debug)
#endif(WIN32)