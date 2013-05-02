# Modified by Sylvain Jaume <sylvain.jaume@siemens.com> 2008

project(dcmdata)

#--------------------------------------------------------------------
# Define the include directories
#
include_directories(
  include
  ../ofstd/include
  ${ZLIB_INCDIR})

#add_subdirectory(apps)
#add_subdirectory(docs)

#--------------------------------------------------------------------
# Define the header files
#
set(HEADERS
  include/dcmtk/dcmdata/cmdlnarg.h
  include/dcmtk/dcmdata/dcbytstr.h
  include/dcmtk/dcmdata/dcchrstr.h
  include/dcmtk/dcmdata/dccodec.h
  include/dcmtk/dcmdata/dcdatset.h
  include/dcmtk/dcmdata/dcddirif.h
  include/dcmtk/dcmdata/dcdebug.h
  include/dcmtk/dcmdata/dcdefine.h
  include/dcmtk/dcmdata/dcdeftag.h
  include/dcmtk/dcmdata/dcdicdir.h
  include/dcmtk/dcmdata/dcdicent.h
  include/dcmtk/dcmdata/dcdict.h
  include/dcmtk/dcmdata/dcdirrec.h
  include/dcmtk/dcmdata/dcelem.h
  include/dcmtk/dcmdata/dcerror.h
  include/dcmtk/dcmdata/dcfilefo.h
  include/dcmtk/dcmdata/dchashdi.h
  include/dcmtk/dcmdata/dcistrma.h
  include/dcmtk/dcmdata/dcistrmb.h
  include/dcmtk/dcmdata/dcistrmf.h
  include/dcmtk/dcmdata/dcistrmz.h
  include/dcmtk/dcmdata/dcitem.h
  include/dcmtk/dcmdata/dclist.h
  include/dcmtk/dcmdata/dcmetinf.h
  include/dcmtk/dcmdata/dcobject.h
  include/dcmtk/dcmdata/dcofsetl.h
  include/dcmtk/dcmdata/dcostrma.h
  include/dcmtk/dcmdata/dcostrmb.h
  include/dcmtk/dcmdata/dcostrmf.h
  include/dcmtk/dcmdata/dcostrmz.h
  include/dcmtk/dcmdata/dcovlay.h
  include/dcmtk/dcmdata/dcpcache.h
  include/dcmtk/dcmdata/dcpixel.h
  include/dcmtk/dcmdata/dcpixseq.h
  include/dcmtk/dcmdata/dcpxitem.h
  include/dcmtk/dcmdata/dcrleccd.h
  include/dcmtk/dcmdata/dcrlecce.h
  include/dcmtk/dcmdata/dcrlecp.h
  include/dcmtk/dcmdata/dcrledec.h
  include/dcmtk/dcmdata/dcrledrg.h
  include/dcmtk/dcmdata/dcrleenc.h
  include/dcmtk/dcmdata/dcrleerg.h
  include/dcmtk/dcmdata/dcrlerp.h
  include/dcmtk/dcmdata/dcsequen.h
  include/dcmtk/dcmdata/dcstack.h
  include/dcmtk/dcmdata/dcswap.h
  include/dcmtk/dcmdata/dctag.h
  include/dcmtk/dcmdata/dctagkey.h
  include/dcmtk/dcmdata/dctk.h
  include/dcmtk/dcmdata/dctypes.h
  include/dcmtk/dcmdata/dcuid.h
  include/dcmtk/dcmdata/dcvm.h
  include/dcmtk/dcmdata/dcvr.h
  include/dcmtk/dcmdata/dcvrae.h
  include/dcmtk/dcmdata/dcvras.h
  include/dcmtk/dcmdata/dcvrat.h
  include/dcmtk/dcmdata/dcvrcs.h
  include/dcmtk/dcmdata/dcvrda.h
  include/dcmtk/dcmdata/dcvrds.h
  include/dcmtk/dcmdata/dcvrdt.h
  include/dcmtk/dcmdata/dcvrfd.h
  include/dcmtk/dcmdata/dcvrfl.h
  include/dcmtk/dcmdata/dcvris.h
  include/dcmtk/dcmdata/dcvrlo.h
  include/dcmtk/dcmdata/dcvrlt.h
  include/dcmtk/dcmdata/dcvrobow.h
  include/dcmtk/dcmdata/dcvrof.h
  include/dcmtk/dcmdata/dcvrpn.h
  include/dcmtk/dcmdata/dcvrpobw.h
  include/dcmtk/dcmdata/dcvrsh.h
  include/dcmtk/dcmdata/dcvrsl.h
  include/dcmtk/dcmdata/dcvrss.h
  include/dcmtk/dcmdata/dcvrst.h
  include/dcmtk/dcmdata/dcvrtm.h
  include/dcmtk/dcmdata/dcvrui.h
  include/dcmtk/dcmdata/dcvrul.h
  include/dcmtk/dcmdata/dcvrulup.h
  include/dcmtk/dcmdata/dcvrus.h
  include/dcmtk/dcmdata/dcvrut.h
  include/dcmtk/dcmdata/dcxfer.h)

#--------------------------------------------------------------------
# Define the source files
#
set(SOURCES
  libsrc/cmdlnarg.cxx
  libsrc/dcbytstr.cxx
  libsrc/dcchrstr.cxx
  libsrc/dccodec.cxx
  libsrc/dcdatset.cxx
  libsrc/dcddirif.cxx
  libsrc/dcdebug.cxx
  libsrc/dcdicdir.cxx
  libsrc/dcdicent.cxx
  libsrc/dcdict.cxx
  libsrc/dcdictbi.cxx
  libsrc/dcdictzz.cxx
  libsrc/dcdirrec.cxx
  libsrc/dcelem.cxx
  libsrc/dcerror.cxx
  libsrc/dcfilefo.cxx
  libsrc/dchashdi.cxx
  libsrc/dcistrma.cxx
  libsrc/dcistrmb.cxx
  libsrc/dcistrmf.cxx
  libsrc/dcistrmz.cxx
  libsrc/dcitem.cxx
  libsrc/dclist.cxx
  libsrc/dcmetinf.cxx
  libsrc/dcobject.cxx
  libsrc/dcostrma.cxx
  libsrc/dcostrmb.cxx
  libsrc/dcostrmf.cxx
  libsrc/dcostrmz.cxx
  libsrc/dcpcache.cxx
  libsrc/dcpixel.cxx
  libsrc/dcpixseq.cxx
  libsrc/dcpxitem.cxx
  libsrc/dcrleccd.cxx
  libsrc/dcrlecce.cxx
  libsrc/dcrlecp.cxx
  libsrc/dcrledrg.cxx
  libsrc/dcrleerg.cxx
  libsrc/dcrlerp.cxx
  libsrc/dcsequen.cxx
  libsrc/dcstack.cxx
  libsrc/dcswap.cxx
  libsrc/dctag.cxx
  libsrc/dctagkey.cxx
  libsrc/dctypes.cxx
  libsrc/dcuid.cxx
  libsrc/dcvm.cxx
  libsrc/dcvr.cxx
  libsrc/dcvrae.cxx
  libsrc/dcvras.cxx
  libsrc/dcvrat.cxx
  libsrc/dcvrcs.cxx
  libsrc/dcvrda.cxx
  libsrc/dcvrds.cxx
  libsrc/dcvrdt.cxx
  libsrc/dcvrfd.cxx
  libsrc/dcvrfl.cxx
  libsrc/dcvris.cxx
  libsrc/dcvrlo.cxx
  libsrc/dcvrlt.cxx
  libsrc/dcvrobow.cxx
  libsrc/dcvrof.cxx
  libsrc/dcvrpn.cxx
  libsrc/dcvrpobw.cxx
  libsrc/dcvrsh.cxx
  libsrc/dcvrsl.cxx
  libsrc/dcvrss.cxx
  libsrc/dcvrst.cxx
  libsrc/dcvrtm.cxx
  libsrc/dcvrui.cxx
  libsrc/dcvrul.cxx
  libsrc/dcvrulup.cxx
  libsrc/dcvrus.cxx
  libsrc/dcvrut.cxx
  libsrc/dcxfer.cxx
  libsrc/mkdeftag.cxx
  libsrc/mkdictbi.cxx)

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
