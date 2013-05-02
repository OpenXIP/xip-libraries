#--------------------------------------------------------------------
# Define the header files
#
set(HEADERS
  mdfconen.h
  mdfdsman.h
  ../include/dcmtk/dcmdata/cmdlnarg.h
  ../include/dcmtk/dcmdata/dcbytstr.h
  ../include/dcmtk/dcmdata/dcchrstr.h
  ../include/dcmtk/dcmdata/dccodec.h
  ../include/dcmtk/dcmdata/dcdatset.h
  ../include/dcmtk/dcmdata/dcddirif.h
  ../include/dcmtk/dcmdata/dcdebug.h
  ../include/dcmtk/dcmdata/dcdefine.h
  ../include/dcmtk/dcmdata/dcdeftag.h
  ../include/dcmtk/dcmdata/dcdicdir.h
  ../include/dcmtk/dcmdata/dcdicent.h
  ../include/dcmtk/dcmdata/dcdict.h
  ../include/dcmtk/dcmdata/dcdirrec.h
  ../include/dcmtk/dcmdata/dcelem.h
  ../include/dcmtk/dcmdata/dcerror.h
  ../include/dcmtk/dcmdata/dcfilefo.h
  ../include/dcmtk/dcmdata/dchashdi.h
  ../include/dcmtk/dcmdata/dcistrma.h
  ../include/dcmtk/dcmdata/dcistrmb.h
  ../include/dcmtk/dcmdata/dcistrmf.h
  ../include/dcmtk/dcmdata/dcistrmz.h
  ../include/dcmtk/dcmdata/dcitem.h
  ../include/dcmtk/dcmdata/dclist.h
  ../include/dcmtk/dcmdata/dcmetinf.h
  ../include/dcmtk/dcmdata/dcobject.h
  ../include/dcmtk/dcmdata/dcofsetl.h
  ../include/dcmtk/dcmdata/dcostrma.h
  ../include/dcmtk/dcmdata/dcostrmb.h
  ../include/dcmtk/dcmdata/dcostrmf.h
  ../include/dcmtk/dcmdata/dcostrmz.h
  ../include/dcmtk/dcmdata/dcovlay.h
  ../include/dcmtk/dcmdata/dcpcache.h
  ../include/dcmtk/dcmdata/dcpixel.h
  ../include/dcmtk/dcmdata/dcpixseq.h
  ../include/dcmtk/dcmdata/dcpxitem.h
  ../include/dcmtk/dcmdata/dcrleccd.h
  ../include/dcmtk/dcmdata/dcrlecce.h
  ../include/dcmtk/dcmdata/dcrlecp.h
  ../include/dcmtk/dcmdata/dcrledec.h
  ../include/dcmtk/dcmdata/dcrledrg.h
  ../include/dcmtk/dcmdata/dcrleenc.h
  ../include/dcmtk/dcmdata/dcrleerg.h
  ../include/dcmtk/dcmdata/dcrlerp.h
  ../include/dcmtk/dcmdata/dcsequen.h
  ../include/dcmtk/dcmdata/dcstack.h
  ../include/dcmtk/dcmdata/dcswap.h
  ../include/dcmtk/dcmdata/dctag.h
  ../include/dcmtk/dcmdata/dctagkey.h
  ../include/dcmtk/dcmdata/dctk.h
  ../include/dcmtk/dcmdata/dctypes.h
  ../include/dcmtk/dcmdata/dcuid.h
  ../include/dcmtk/dcmdata/dcvm.h
  ../include/dcmtk/dcmdata/dcvr.h
  ../include/dcmtk/dcmdata/dcvrae.h
  ../include/dcmtk/dcmdata/dcvras.h
  ../include/dcmtk/dcmdata/dcvrat.h
  ../include/dcmtk/dcmdata/dcvrcs.h
  ../include/dcmtk/dcmdata/dcvrda.h
  ../include/dcmtk/dcmdata/dcvrds.h
  ../include/dcmtk/dcmdata/dcvrdt.h
  ../include/dcmtk/dcmdata/dcvrfd.h
  ../include/dcmtk/dcmdata/dcvrfl.h
  ../include/dcmtk/dcmdata/dcvris.h
  ../include/dcmtk/dcmdata/dcvrlo.h
  ../include/dcmtk/dcmdata/dcvrlt.h
  ../include/dcmtk/dcmdata/dcvrobow.h
  ../include/dcmtk/dcmdata/dcvrof.h
  ../include/dcmtk/dcmdata/dcvrpn.h
  ../include/dcmtk/dcmdata/dcvrpobw.h
  ../include/dcmtk/dcmdata/dcvrsh.h
  ../include/dcmtk/dcmdata/dcvrsl.h
  ../include/dcmtk/dcmdata/dcvrss.h
  ../include/dcmtk/dcmdata/dcvrst.h
  ../include/dcmtk/dcmdata/dcvrtm.h
  ../include/dcmtk/dcmdata/dcvrui.h
  ../include/dcmtk/dcmdata/dcvrul.h
  ../include/dcmtk/dcmdata/dcvrulup.h
  ../include/dcmtk/dcmdata/dcvrus.h
  ../include/dcmtk/dcmdata/dcvrut.h
  ../include/dcmtk/dcmdata/dcxfer.h)	

#--------------------------------------------------------------------
# Define the include directories
#
include_directories(${LIBXML_INCDIR})

#--------------------------------------------------------------------
# Define the link directories
#
link_directories(
  ${dcmdata_BINARY_DIR}
  ${ofstd_BINARY_DIR}
  ${ZLIB_LIBDIR}
  ${LIBXML_LIBDIR})

#--------------------------------------------------------------------
# Compile the executables
#
foreach(PROGRAM
  dcm2xml
  dcmconv
  dcmcrle
  dcmdrle
  dcmdump
  dcmftest
  dcmgpdir
  dump2dcm
  xml2dcm
  pdf2dcm)
  add_executable(${PROGRAM} ${PROGRAM}.cxx)
endforeach(PROGRAM)

add_executable(dcmodify
  dcmodify.cxx
  mdfconen.cxx
  mdfdsman.cxx)

#--------------------------------------------------------------------
# Install the executables
#
foreach(PROGRAM
  dcm2xml
  dcmconv
  dcmcrle
  dcmdrle
  dcmdump
  dcmftest
  dcmgpdir
  dcmodify
  dump2dcm
  xml2dcm
  pdf2dcm)
  install(TARGETS ${PROGRAM} DESTINATION ${INSTALL_BINDIR})
endforeach(PROGRAM)

install(FILES dumppat.txt DESTINATION ${INSTALL_DATDIR})
install(FILES dcm2xml.dtd DESTINATION ${INSTALL_LIBDIR})

#--------------------------------------------------------------------
# Link the libraries
#
foreach(PROGRAM
  dcm2xml
  dcmconv
  dcmcrle
  dcmdrle
  dcmdump
  dcmgpdir
  dcmodify
  dump2dcm
  xml2dcm
  pdf2dcm)

  target_link_libraries(${PROGRAM}
    netapi32
    wsock32
    ofstd
    dcmdata
    ${ZLIB_LIBS})
endforeach(PROGRAM)

target_link_libraries(dcmftest ofstd ${ZLIB_LIBS})
target_link_libraries(xml2dcm ${LIBXML_LIBS})
