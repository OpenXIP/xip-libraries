# declare additional include directories
include_directories(
  ../include
  ../../ofstd/include
  ../../dcmdata/include
  ../../dcmimgle/include
  ../../dcmimage/include
  ../libijg8
  ../libijg12
  ../libijg16
  ${ZLIB_INCDIR}
  ${LIBTIFF_INCDIR}
  ${LIBPNG_INCDIR})

# declare directories containing used libraries
link_directories(
  ${dcmjpeg_BINARY_DIR}
  ${ofstd_BINARY_DIR}
  ${dcmdata_BINARY_DIR}
  ${dcmimgle_BINARY_DIR}
  ${dcmimage_BINARY_DIR}
  ${ZLIB_LIBDIR}
  ${LIBTIFF_LIBDIR}
  ${LIBPNG_LIBDIR})

# declare executables
add_executable(dcmcjpeg dcmcjpeg.cxx)
add_executable(dcmdjpeg dcmdjpeg.cxx)
add_executable(dcmj2pnm dcmj2pnm.cxx)
add_executable(dcmmkdir dcmmkdir.cxx)

# declare installation files
install_targets(${INSTALL_BINDIR} dcmcjpeg)
install_targets(${INSTALL_BINDIR} dcmdjpeg)
install_targets(${INSTALL_BINDIR} dcmj2pnm)
install_targets(${INSTALL_BINDIR} dcmmkdir)

# make sure executables are linked to the corresponding libraries
foreach(PROGRAM dcmcjpeg dcmdjpeg dcmj2pnm dcmmkdir)
  target_link_libraries(${PROGRAM}
	  netapi32
	  wsock32
	  ofstd
	  dcmdata
	  dcmimgle
	  dcmimage
	  dcmjpeg
	  ijg8
	  ijg12
	  ijg16
	  ${ZLIB_LIBS})
endforeach(PROGRAM)

target_link_libraries(dcmj2pnm ${LIBTIFF_LIBS} ${LIBPNG_LIBS})
