# Modified by Sylvain Jaume <sylvain.jaume@siemens.com>

# declare directories containing used libraries
link_directories(
  ${dcmsign_BINARY_DIR}
  ${ofstd_BINARY_DIR}
  ${dcmdata_BINARY_DIR}
  ${ZLIB_LIBDIR}
  ${OPENSSL_LIBDIR})

# declare executables
add_executable(dcmsign dcmsign.cxx)

# declare installation files
install(TARGETS dcmsign DESTINATION ${INSTALL_BINDIR})

# make sure executables are linked to the corresponding libraries
target_link_libraries(dcmsign
  netapi32
  wsock32
  ofstd
  dcmdata
  dcmdsig
  ${ZLIB_LIBS}
  ${OPENSSL_LIBS})
