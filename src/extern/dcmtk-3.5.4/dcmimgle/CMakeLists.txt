# Modified by Sylvain Jaume <sylvain.jaume@siemens.com> 2008

project(dcmimgle)

#--------------------------------------------------------------------
# declare include directories which hold for all subdirectories
#
include_directories(
  ../dcmimgle/include
  ../ofstd/include
  ../dcmdata/include
  ${ZLIB_INCDIR})

#add_subdirectory(apps)
#add_subdirectory(tests)

#--------------------------------------------------------------------
# Define the header files
#
set(HEADERS
  include/dcmtk/dcmimgle/dcmimage.h
  include/dcmtk/dcmimgle/dibaslut.h
  include/dcmtk/dcmimgle/diciefn.h
  include/dcmtk/dcmimgle/dicielut.h
  include/dcmtk/dcmimgle/dicrvfit.h
  include/dcmtk/dcmimgle/didislut.h
  include/dcmtk/dcmimgle/didispfn.h
  include/dcmtk/dcmimgle/didocu.h
  include/dcmtk/dcmimgle/diflipt.h
  include/dcmtk/dcmimgle/digsdfn.h
  include/dcmtk/dcmimgle/digsdlut.h
  include/dcmtk/dcmimgle/diimage.h
  include/dcmtk/dcmimgle/diinpx.h
  include/dcmtk/dcmimgle/diinpxt.h
  include/dcmtk/dcmimgle/diluptab.h
  include/dcmtk/dcmimgle/dimo1img.h
  include/dcmtk/dcmimgle/dimo2img.h
  include/dcmtk/dcmimgle/dimocpt.h
  include/dcmtk/dcmimgle/dimoflt.h
  include/dcmtk/dcmimgle/dimoimg.h
  include/dcmtk/dcmimgle/dimoipxt.h
  include/dcmtk/dcmimgle/dimomod.h
  include/dcmtk/dcmimgle/dimoopx.h
  include/dcmtk/dcmimgle/dimoopxt.h
  include/dcmtk/dcmimgle/dimopx.h
  include/dcmtk/dcmimgle/dimopxt.h
  include/dcmtk/dcmimgle/dimorot.h
  include/dcmtk/dcmimgle/dimosct.h
  include/dcmtk/dcmimgle/diobjcou.h
  include/dcmtk/dcmimgle/diovdat.h
  include/dcmtk/dcmimgle/diovlay.h
  include/dcmtk/dcmimgle/diovlimg.h
  include/dcmtk/dcmimgle/diovpln.h
  include/dcmtk/dcmimgle/dipixel.h
  include/dcmtk/dcmimgle/diplugin.h
  include/dcmtk/dcmimgle/dipxrept.h
  include/dcmtk/dcmimgle/diregbas.h
  include/dcmtk/dcmimgle/dirotat.h
  include/dcmtk/dcmimgle/discalet.h
  include/dcmtk/dcmimgle/displint.h
  include/dcmtk/dcmimgle/ditranst.h
  include/dcmtk/dcmimgle/diutils.h)

#--------------------------------------------------------------------
# Define the source files
#
set(SOURCES
  libsrc/dcmimage.cxx
  libsrc/dibaslut.cxx
  libsrc/diciefn.cxx
  libsrc/dicielut.cxx
  libsrc/didislut.cxx
  libsrc/didispfn.cxx
  libsrc/didocu.cxx
  libsrc/digsdfn.cxx
  libsrc/digsdlut.cxx
  libsrc/diimage.cxx
  libsrc/diinpx.cxx
  libsrc/diluptab.cxx
  libsrc/dimo1img.cxx
  libsrc/dimo2img.cxx
  libsrc/dimoimg.cxx
  libsrc/dimoimg3.cxx
  libsrc/dimoimg4.cxx
  libsrc/dimoimg5.cxx
  libsrc/dimomod.cxx
  libsrc/dimoopx.cxx
  libsrc/dimopx.cxx
  libsrc/diovdat.cxx
  libsrc/diovlay.cxx
  libsrc/diovlimg.cxx
  libsrc/diovpln.cxx
  libsrc/diutils.cxx)

#--------------------------------------------------------------------
# Compile the library
#
add_library(${PROJECT_NAME} STATIC ${SOURCES})

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

#if(WIN32)
#  install(FILES ${LIBRARY_OUTPUT_PATH}/debug/${PROJECT_NAME}${CMAKE_DEBUG_POSTFIX}.pdb
#    DESTINATION bin/debug CONFIGURATIONS Debug)
#endif(WIN32)