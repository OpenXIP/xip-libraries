# Modified by Sylvain Jaume <sylvain.jaume@siemens.com> 2008

project(dcmtk)

# check for Windows operating system
#if(NOT WIN32)
#  message(FATAL_ERROR "Please use GNU autoconf for Unix systems.")
#endif(NOT WIN32)

#--------------------------------------------------------------------
# CMake-specific settings
set(CMAKE_USE_RELATIVE_PATHS    ON)
set(CMAKE_SUPPRESS_REGENERATION ON)

mark_as_advanced(FORCE EXECUTABLE_OUTPUT_PATH LIBRARY_OUTPUT_PATH)

#--------------------------------------------------------------------
# shared libraries (option not yet available)
set(WITH_SHARED_LIBS OFF)
set(BUILD_SHARED_LIBS ${WITH_SHARED_LIBS})

#--------------------------------------------------------------------
# doxygen support
find_program(DOXYGEN_EXECUTABLE "doxygen")
mark_as_advanced(DOXYGEN_EXECUTABLE)

#--------------------------------------------------------------------
# libxml support
option(WITH_LIBXML "Build with libxml support." OFF)
find_path(WITH_LIBXMLINC "include/libxml/parser.h"
  "${dcmtk_SOURCE_DIR}/../libxml2-2.6.26")
mark_as_advanced(WITH_LIBXML WITH_LIBXMLINC)

#--------------------------------------------------------------------
# libpng support
option(WITH_LIBPNG "Build with libpng support." ON)
find_path(WITH_LIBPNGINC "include/png.h"
       "${dcmtk_SOURCE_DIR}/../libpng-1.2.8")
mark_as_advanced(WITH_LIBPNG WITH_LIBPNGINC)

#--------------------------------------------------------------------
# libtiff support
option(WITH_LIBTIFF "Build with libtiff support." ON)
find_path(WITH_LIBTIFFINC "include/tiff.h"
  "${dcmtk_SOURCE_DIR}/../tiff-3.7.4")
mark_as_advanced(WITH_LIBTIFF WITH_LIBTIFFINC)

#--------------------------------------------------------------------
# openssl support
option(WITH_OPENSSL "Build with openssl support." OFF)
find_path(WITH_OPENSSLINC "include/openssl/ssl.h"
  "${dcmtk_SOURCE_DIR}/../openssl-0.9.8a")
mark_as_advanced(WITH_OPENSSL WITH_OPENSSLINC)

#--------------------------------------------------------------------
# zlib support
option(WITH_ZLIB "Build with zlib support." ON)
find_path(WITH_ZLIBINC "include/zlib.h"
  "${dcmtk_SOURCE_DIR}/../zlib-1.2.3")
mark_as_advanced(WITH_ZLIB WITH_ZLIBINC)

#--------------------------------------------------------------------
# set project wide flags for compiler and linker
#

#--------------------------------------------------------------------
# settings for Microsoft Visual C
#
if(CMAKE_C_COMPILER MATCHES cl)
  if(NOT WITH_SHARED_LIBS)
    if(CMAKE_GENERATOR STREQUAL "Visual Studio 6")
      set(CMAKE_C_FLAGS "/nologo /W3 /GX /Gy /YX")
      set(CMAKE_C_FLAGS_DEBUG "/MDd /Z7 /Od")
      set(CMAKE_C_FLAGS_RELEASE "/MD /O2")
      set(CMAKE_C_FLAGS_MINSIZEREL "/MD /O2")
      set(CMAKE_C_FLAGS_RELWITHDEBINFO "/MDd /Z7 /Od")
    endif(CMAKE_GENERATOR STREQUAL "Visual Studio 6")
    if(CMAKE_GENERATOR STREQUAL "Visual Studio 7" OR
       CMAKE_GENERATOR STREQUAL "Visual Studio 7 .NET 2003")
      set(CMAKE_C_FLAGS "/nologo /W3 /Gy")
      set(CMAKE_C_FLAGS_DEBUG "/MDd /Z7 /Od")
      set(CMAKE_C_FLAGS_RELEASE "/MD /O2")
      set(CMAKE_C_FLAGS_MINSIZEREL "/MD /O2")
      set(CMAKE_C_FLAGS_RELWITHDEBINFO "/MDd /Z7 /Od")
    endif(CMAKE_GENERATOR STREQUAL "Visual Studio 7" OR
	  CMAKE_GENERATOR STREQUAL "Visual Studio 7 .NET 2003")
    if(CMAKE_GENERATOR STREQUAL "Visual Studio 8 2005")
      set(CMAKE_C_FLAGS "/nologo /W3 /Gy")
      set(CMAKE_C_FLAGS_DEBUG "/MDd /Z7 /Od")
      set(CMAKE_C_FLAGS_RELEASE "/MD /O2")
      set(CMAKE_C_FLAGS_MINSIZEREL "/MD /O2")
      set(CMAKE_C_FLAGS_RELWITHDEBINFO "/MDd /Z7 /Od")
    endif(CMAKE_GENERATOR STREQUAL "Visual Studio 8 2005")
  endif(NOT WITH_SHARED_LIBS)
endif(CMAKE_C_COMPILER MATCHES cl)

#--------------------------------------------------------------------
# settings for Microsoft Visual C++
#
if(CMAKE_CXX_COMPILER MATCHES cl)
  if(NOT WITH_SHARED_LIBS)
    if(CMAKE_GENERATOR STREQUAL "Visual Studio 6")
      set(CMAKE_CXX_FLAGS "/nologo /W3 /GX /Gy /YX")
      set(CMAKE_CXX_FLAGS_DEBUG "/MDd /Z7 /Od")
      set(CMAKE_CXX_FLAGS_RELEASE "/MD /O2")
      set(CMAKE_CXX_FLAGS_MINSIZEREL "/MD /O2")
      set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "/MDd /Z7 /Od")
    endif(CMAKE_GENERATOR STREQUAL "Visual Studio 6")
    if(CMAKE_GENERATOR STREQUAL "Visual Studio 7" OR
       CMAKE_GENERATOR STREQUAL "Visual Studio 7 .NET 2003")
      set(CMAKE_CXX_FLAGS "/nologo /W3 /Gy")
      set(CMAKE_CXX_FLAGS_DEBUG "/MDd /Z7 /Od")
      set(CMAKE_CXX_FLAGS_RELEASE "/MD /O2")
      set(CMAKE_CXX_FLAGS_MINSIZEREL "/MD /O2")
      set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "/MDd /Z7 /Od")
    endif(CMAKE_GENERATOR STREQUAL "Visual Studio 7" OR
	  CMAKE_GENERATOR STREQUAL "Visual Studio 7 .NET 2003")
    if(CMAKE_GENERATOR STREQUAL "Visual Studio 8 2005")
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /nologo /Gy")
      set(CMAKE_CXX_FLAGS_DEBUG "/MDd /Z7 /Od")
      set(CMAKE_CXX_FLAGS_RELEASE "/MD /O2")
      set(CMAKE_CXX_FLAGS_MINSIZEREL "/MD /O2")
      set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "/MDd /Z7 /Od")
    endif(CMAKE_GENERATOR STREQUAL "Visual Studio 8 2005")
  endif(NOT WITH_SHARED_LIBS)
endif(CMAKE_CXX_COMPILER MATCHES cl)

#--------------------------------------------------------------------
# settings for Borland C++
#
if(CMAKE_CXX_COMPILER MATCHES bcc32)
  # further settings required?
  set(CMAKE_STANDARD_LIBRARIES "import32.lib cw32mt.lib")
endif(CMAKE_CXX_COMPILER MATCHES bcc32)

#--------------------------------------------------------------------
# set general compiler flags
# add_definitions(-D_REENTRANT)

#--------------------------------------------------------------------
# libxml support
#
if(WITH_LIBXML AND WITH_LIBXMLINC)
  add_definitions(-DWITH_LIBXML)
  set(LIBXML_INCDIR ${WITH_LIBXMLINC}/include)
  set(LIBXML_LIBDIR ${WITH_LIBXMLINC}/lib)
  set(LIBXML_LIBS debug libxml2_d optimized libxml2_o debug iconv_d
    optimized iconv_o)
endif(WITH_LIBXML AND WITH_LIBXMLINC)

#--------------------------------------------------------------------
# libpng support
#
if(WITH_LIBPNG AND WITH_LIBPNGINC)
  add_definitions(-DWITH_LIBPNG)
  set(LIBPNG_INCDIR ${WITH_LIBPNGINC}/include)
  set(LIBPNG_LIBDIR ${WITH_LIBPNGINC}/lib)
  set(LIBPNG_LIBS debug libpng_d optimized libpng_o)
endif(WITH_LIBPNG AND WITH_LIBPNGINC)

#--------------------------------------------------------------------
# libtiff support
#
if(WITH_LIBTIFF AND WITH_LIBTIFFINC)
  add_definitions(-DWITH_LIBTIFF)
  set(LIBTIFF_INCDIR ${WITH_LIBTIFFINC}/include)
  set(LIBTIFF_LIBDIR ${WITH_LIBTIFFINC}/lib)
  set(LIBTIFF_LIBS debug libtiff_d optimized libtiff_o)
endif(WITH_LIBTIFF AND WITH_LIBTIFFINC)

#--------------------------------------------------------------------
# openssl support
#
if(WITH_OPENSSL AND WITH_OPENSSLINC)
  add_definitions(-DWITH_OPENSSL)
  set(OPENSSL_BINDIR ${WITH_OPENSSLINC}/bin)
  set(OPENSSL_INCDIR ${WITH_OPENSSLINC}/include)
  set(OPENSSL_LIBDIR ${WITH_OPENSSLINC}/lib)
  set(OPENSSL_LIBS debug dcmtkssl_d.lib optimized dcmtkssl_o.lib
    debug dcmtkeay_d.lib optimized dcmtkeay_o.lib)
endif(WITH_OPENSSL AND WITH_OPENSSLINC)

#--------------------------------------------------------------------
# zlib support
#
if(WITH_ZLIB AND WITH_ZLIBINC)
  add_definitions(-DWITH_ZLIB)
  set(ZLIB_INCDIR ${WITH_ZLIBINC}/include)
  set(ZLIB_LIBDIR ${WITH_ZLIBINC}/lib)
  set(ZLIB_LIBS debug zlib_d optimized zlib_o)
endif(WITH_ZLIB AND WITH_ZLIBINC)

#--------------------------------------------------------------------
# Install files
#
install(FILES COPYRIGHT FAQ HISTORY DESTINATION doc)

#--------------------------------------------------------------------
# Define the include directories
#
include_directories(config/include)

#--------------------------------------------------------------------
# Recurse into subdirectories
#
add_subdirectory(config)
add_subdirectory(ofstd)
add_subdirectory(dcmdata)
#add_subdirectory(dcmtls)
#add_subdirectory(dcmnet)
#add_subdirectory(dcmqrdb)
add_subdirectory(dcmimgle)
add_subdirectory(dcmimage)
add_subdirectory(dcmjpeg)
#add_subdirectory(dcmsign)
#add_subdirectory(dcmsr)
add_subdirectory(dcmpstat)
#add_subdirectory(dcmwlm)
#add_subdirectory(doxygen)
