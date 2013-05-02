# Modified by Sylvain Jaume <sylvain.jaume@siemens.com> 2008

project(dcmpstat)

#--------------------------------------------------------------------
# declare include directories which hold for all subdirectories
#
include_directories(
  include
  ../ofstd/include
  ../dcmdata/include
  ../dcmnet/include
  ../dcmimgle/include
  ../dcmqrdb/include
  ../dcmsr/include
  ../dcmsign/include
  ../dcmtls/include
  ${ZLIB_INCDIR} ${OPENSSL_INCDIR})

#add_subdirectory(apps)
#add_subdirectory(tests)

#--------------------------------------------------------------------
# Define the header files
#
set(HEADERS
  include/dcmtk/dcmpstat/dcmpstat.h
  include/dcmtk/dcmpstat/dvcache.h
  include/dcmtk/dcmpstat/dviface.h
  include/dcmtk/dcmpstat/dvpsab.h
  include/dcmtk/dcmpstat/dvpsabl.h
  include/dcmtk/dcmpstat/dvpsal.h
  include/dcmtk/dcmpstat/dvpsall.h
  include/dcmtk/dcmpstat/dvpscf.h
  include/dcmtk/dcmpstat/dvpscu.h
  include/dcmtk/dcmpstat/dvpscul.h
  include/dcmtk/dcmpstat/dvpsda.h
  include/dcmtk/dcmpstat/dvpsdal.h
  include/dcmtk/dcmpstat/dvpsdef.h
  include/dcmtk/dcmpstat/dvpsfs.h
  include/dcmtk/dcmpstat/dvpsga.h
  include/dcmtk/dcmpstat/dvpsgal.h
  include/dcmtk/dcmpstat/dvpsgl.h
  include/dcmtk/dcmpstat/dvpsgll.h
  include/dcmtk/dcmpstat/dvpsgr.h
  include/dcmtk/dcmpstat/dvpsgrl.h
  include/dcmtk/dcmpstat/dvpshlp.h
  include/dcmtk/dcmpstat/dvpsib.h
  include/dcmtk/dcmpstat/dvpsibl.h
  include/dcmtk/dcmpstat/dvpsmsg.h
  include/dcmtk/dcmpstat/dvpsov.h
  include/dcmtk/dcmpstat/dvpsovl.h
  include/dcmtk/dcmpstat/dvpspl.h
  include/dcmtk/dcmpstat/dvpspll.h
  include/dcmtk/dcmpstat/dvpspr.h
  include/dcmtk/dcmpstat/dvpsprt.h
  include/dcmtk/dcmpstat/dvpsri.h
  include/dcmtk/dcmpstat/dvpsril.h
  include/dcmtk/dcmpstat/dvpsrs.h
  include/dcmtk/dcmpstat/dvpsrsl.h
  include/dcmtk/dcmpstat/dvpssp.h
  include/dcmtk/dcmpstat/dvpsspl.h
  include/dcmtk/dcmpstat/dvpssv.h
  include/dcmtk/dcmpstat/dvpssvl.h
  include/dcmtk/dcmpstat/dvpstat.h
  include/dcmtk/dcmpstat/dvpstx.h
  include/dcmtk/dcmpstat/dvpstxl.h
  include/dcmtk/dcmpstat/dvpstyp.h
  include/dcmtk/dcmpstat/dvpsvl.h
  include/dcmtk/dcmpstat/dvpsvll.h
  include/dcmtk/dcmpstat/dvpsvw.h
  include/dcmtk/dcmpstat/dvpsvwl.h
  include/dcmtk/dcmpstat/dvsighdl.h)

#--------------------------------------------------------------------
# Define the source files
#
set(SOURCES
  libsrc/dcmpstat.cxx
  libsrc/dviface.cxx
  libsrc/dvpsab.cxx
  libsrc/dvpsabl.cxx
  libsrc/dvpsal.cxx
  libsrc/dvpsall.cxx
  libsrc/dvpscf.cxx
  libsrc/dvpscu.cxx
  libsrc/dvpscul.cxx
  libsrc/dvpsda.cxx
  libsrc/dvpsdal.cxx
  libsrc/dvpsfs.cxx
  libsrc/dvpsga.cxx
  libsrc/dvpsgal.cxx
  libsrc/dvpsgl.cxx
  libsrc/dvpsgll.cxx
  libsrc/dvpsgr.cxx
  libsrc/dvpsgrl.cxx
  libsrc/dvpshlp.cxx
  libsrc/dvpsib.cxx
  libsrc/dvpsibl.cxx
  libsrc/dvpsmsg.cxx
  libsrc/dvpsov.cxx
  libsrc/dvpsovl.cxx
  libsrc/dvpspl.cxx
  libsrc/dvpspl2.cxx
  libsrc/dvpspll.cxx
  libsrc/dvpspr.cxx
  libsrc/dvpsprt.cxx
  libsrc/dvpsri.cxx
  libsrc/dvpsril.cxx
  libsrc/dvpsrs.cxx
  libsrc/dvpsrsl.cxx
  libsrc/dvpssp.cxx
  libsrc/dvpsspl.cxx
  libsrc/dvpssv.cxx
  libsrc/dvpssvl.cxx
  libsrc/dvpstat.cxx
  libsrc/dvpstx.cxx
  libsrc/dvpstxl.cxx
  libsrc/dvpsvl.cxx
  libsrc/dvpsvll.cxx
  libsrc/dvpsvw.cxx
  libsrc/dvpsvwl.cxx
  libsrc/dvsighdl.cxx)				

#--------------------------------------------------------------------
# Compile the library
#
add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCES})

#--------------------------------------------------------------------
# Install the header files
#
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

#--------------------------------------------------------------------
# Install the config files
#
install(FILES etc/dcmpstat.cfg etc/printers.cfg DESTINATION doc)

#if(WIN32)
#  install(FILES ${LIBRARY_OUTPUT_PATH}/debug/${PROJECT_NAME}${CMAKE_DEBUG_POSTFIX}.pdb
#    DESTINATION bin/debug CONFIGURATIONS Debug)
#endif(WIN32)