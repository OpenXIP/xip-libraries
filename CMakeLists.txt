# Sylvain Jaume 2007

project(Xip)
cmake_minimum_required(VERSION 2.6)

#--------------------------------------------------------------------
# Testing configuration.
#
option(BUILD_TESTING "Create the testing framework" OFF)
if(BUILD_TESTING)
  enable_testing()
endif(BUILD_TESTING)

include(Dart)
mark_as_advanced(DART_ROOT)

#--------------------------------------------------------------------
# Xip version number.  An even minor number corresponds to releases.
#
set(Xip_VERSION_MAJOR "0")
set(Xip_VERSION_MINOR "1")
set(Xip_VERSION_PATCH "0")

# Version string should not include patch level.  The major.minor is
# enough to distinguish available features of the toolkit.
set(Xip_VERSION_STRING "${Xip_VERSION_MAJOR}.${Xip_VERSION_MINOR}")

#--------------------------------------------------------------------
# Set up CPack support, to be able to distribute Xip binary packages. It will
# be particulary useful to distributed prebuilt Xip witk extended languages
# support enable
#
include(InstallRequiredSystemLibraries)
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "eXtensible Imaging Platorm")
set(CPACK_PACKAGE_VENDOR "Siemens Corporate Research")
set(CPACK_PACKAGE_VERSION_MAJOR "${Xip_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${Xip_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${Xip_VERSION_PATCH}")
set(CPACK_PACKAGE_INSTALL_DIRECTORY
  "xip-${Xip_VERSION_MAJOR}.${Xip_VERSION_MINOR}")
set(CPACK_RESOURCE_FILE_LICENSE ${Xip_SOURCE_DIR}/LICENSE.txt)

set(CPACK_PACKAGE_DESCRIPTION_FILE ${CMAKE_CURRENT_SOURCE_DIR}/README.txt)
set(CPACK_GENERATOR ZIP)
set(CPACK_SOURCE_PACKAGE_FILE_NAME
  "xip-src-${Xip_VERSION_MAJOR}.${Xip_VERSION_MINOR}" CACHE INTERNAL
  "zip file basename")
set(CPACK_SOURCE_GENERATOR ZIP)

# The following components are regex's to match anywhere (unless anchored)
# in absolute path + filename to find files or directories to be excluded
# from source tarball.
set(CPACK_SOURCE_IGNORE_FILES
  "~$"
  "\\\\.svn$"
  "^${PROJECT_SOURCE_DIR}.*/.svn/")
#message("CPACK_SOURCE_IGNORE_FILES = ${CPACK_SOURCE_IGNORE_FILES}")

include(CPack)

#--------------------------------------------------------------------
# If CMake is the version we're expecting, don't show the
# CMAKE_BACKWARDS_COMPATIBILITY option. If the version is higher than the
# minimal version required, then show the backward compatibility option.
#
if("${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}" MATCHES "^2\\.6$")
  mark_as_advanced(FORCE CMAKE_BACKWARDS_COMPATIBILITY)
else("${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}" MATCHES "^2\\.6$")
  mark_as_advanced(CLEAR CMAKE_BACKWARDS_COMPATIBILITY)
endif("${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}" MATCHES "^2\\.6$")

#--------------------------------------------------------------------
# Doxygen configuration rules.
#
configure_file(${Xip_SOURCE_DIR}/build/doxygen.config.in
               ${Xip_BINARY_DIR}/doxygen.config)

configure_file(${Xip_SOURCE_DIR}/build/doxygen.pl.in
               ${Xip_BINARY_DIR}/doxygen.pl)

configure_file(${Xip_SOURCE_DIR}/build/Doxyfile.in
               ${Xip_BINARY_DIR}/Doxyfile)

#--------------------------------------------------------------------
# Options to build with third party libraries.
#
if(WIN32)
  option(HAS_DCMTK "Compile with the DICOM library DCMTK" ON)
  option(HAS_ITK   "Compile with the Insight Toolkit" ON)
  option(HAS_VTK   "Compile with the Visualization Toolkit" ON)
else(WIN32)
  option(HAS_DCMTK "Compile with the DICOM library DCMTK" OFF)
  option(HAS_ITK   "Compile with the Insight Toolkit" OFF)
  option(HAS_VTK   "Compile with the Visualization Toolkit" OFF)
endif(WIN32)

mark_as_advanced(CMAKE_INSTALL_PREFIX)

mark_as_advanced(VTK_GLEXT_FILE)
mark_as_advanced(VTK_GLXEXT_FILE)
mark_as_advanced(VTK_WGLEXT_FILE)

#--------------------------------------------------------------------
# Find xipext directory
#
find_path(XIPEXT inventor/bin/xipinv240.dll ${Xip_SOURCE_DIR}/../xipext
	"Directory where Xip external libraries are located")

find_path(OIV_PATH bin/xipinv240.dll ${XIPEXT}/inventor
  "Directory of installed OpenInventor")

if(HAS_ITK)
  find_path(ITK_PATH bin/ITKCommon.dll ${XIPEXT}/itk
    "Directory of installed ITK")
endif(HAS_ITK)

if(HAS_VTK)
  find_path(VTK_PATH bin/vtkCommon.dll ${XIPEXT}/vtk
    "Directory of installed VTK")
endif(HAS_VTK)

#--------------------------------------------------------------------
# Options to build OpenInventor.
#
option(BUILD_INVENTOR "Build the OpenInventor library" ON)

#--------------------------------------------------------------------
# Output directories.
#
if(NOT EXECUTABLE_OUTPUT_PATH)
  set(EXECUTABLE_OUTPUT_PATH ${Xip_BINARY_DIR}/out CACHE PATH
    "Single output directory for building all executables.")
endif(NOT EXECUTABLE_OUTPUT_PATH)

if(NOT LIBRARY_OUTPUT_PATH)
  set(LIBRARY_OUTPUT_PATH ${Xip_BINARY_DIR}/out CACHE PATH
    "Single output directory for building all libraries.")
endif(NOT LIBRARY_OUTPUT_PATH)

mark_as_advanced(EXECUTABLE_OUTPUT_PATH LIBRARY_OUTPUT_PATH)

#--------------------------------------------------------------------
# Definitions.
#
if(WIN32)
  add_definitions(-DXIPCOMMON_EXPORTS) # for XipException.h
endif(WIN32)

#--------------------------------------------------------------------
# Disable deprecation warnings for standard C functions.
#
if(CMAKE_COMPILER_2005)
  add_definitions(-D_CRT_SECURE_NO_DEPRECATE -D_CRT_NONSTDC_NO_DEPRECATE)
endif(CMAKE_COMPILER_2005)

#--------------------------------------------------------------------
# Find xipbuilder executable, required for testing.
#
if(BUILD_TESTING)
  find_path(XipBUILDER xipbuilder.exe
    ${Xip_SOURCE_DIR}/../xipbuilder-release/release)
endif(BUILD_TESTING)

#--------------------------------------------------------------------
# Include directories.
#
include_directories(
  ${Xip_SOURCE_DIR}/include
  ${OIV_PATH}/include)

#--------------------------------------------------------------------
# Link directories.
#
link_directories(
  ${Xip_BINARY_DIR}/out
  ${XIPEXT}/inventor/lib
  .) # Put "." in the rpath of all Xip shared libraries.

#--------------------------------------------------------------------
# Examples dir for testing.
#
set(EXAMPLES_DIR ${Xip_SOURCE_DIR}/examples)

#--------------------------------------------------------------------
# Subdirectories.
#
add_subdirectory(src)
add_subdirectory(test)

#--------------------------------------------------------------------
# Install libraries and header files.
#
file(GLOB_RECURSE FILES_IN_INCLUDE_DIR include *.h)

foreach(HEADER_FILE ${FILES_IN_INCLUDE_DIR})
  if(${HEADER_FILE} MATCHES "h$")

    #
    # Install include directory
    #
    if(${HEADER_FILE} MATCHES "${Xip_SOURCE_DIR}/include")
      string(REGEX REPLACE "${Xip_SOURCE_DIR}/" ""
        INSTALL_PATH ${HEADER_FILE})
      get_filename_component(INSTALL_PATH ${INSTALL_PATH} PATH)
      if(HEADER_FILE MATCHES "[^src]")
        install(FILES ${HEADER_FILE} DESTINATION ${INSTALL_PATH})
      endif(HEADER_FILE MATCHES "[^src]")
    endif(${HEADER_FILE} MATCHES "${Xip_SOURCE_DIR}/include")

    #
    # Install src/extern/inventor/lib/database
    #
    if(${HEADER_FILE} MATCHES
      "${Xip_SOURCE_DIR}/src/extern/inventor/lib/database/include")
      string(REGEX REPLACE
	"${Xip_SOURCE_DIR}/src/extern/inventor/lib/database/" ""
       	INSTALL_PATH ${HEADER_FILE})
      get_filename_component(INSTALL_PATH ${INSTALL_PATH} PATH)
      if(HEADER_FILE MATCHES "[^src]")
        install(FILES ${HEADER_FILE} DESTINATION ${INSTALL_PATH})
      endif(HEADER_FILE MATCHES "[^src]")
    endif(${HEADER_FILE} MATCHES
      "${Xip_SOURCE_DIR}/src/extern/inventor/lib/database/include")

    #
    # Install src/extern/inventor/lib/mevis
    #
    if(${HEADER_FILE} MATCHES
      "${Xip_SOURCE_DIR}/src/extern/inventor/lib/mevis/include")
      string(REGEX REPLACE "${Xip_SOURCE_DIR}/src/extern/inventor/lib/mevis/"
        "" INSTALL_PATH ${HEADER_FILE})
      get_filename_component(INSTALL_PATH ${INSTALL_PATH} PATH)
      if(HEADER_FILE MATCHES "[^src]")
        install(FILES ${HEADER_FILE} DESTINATION ${INSTALL_PATH})
      endif(HEADER_FILE MATCHES "[^src]")
    endif(${HEADER_FILE} MATCHES
      "${Xip_SOURCE_DIR}/src/extern/inventor/lib/mevis/include")

  endif(${HEADER_FILE} MATCHES "h$")
endforeach(HEADER_FILE ${FILES_IN_INCLUDE_DIR})

get_target_property(Xip_LIBRARY Xip LOCATION)

set(Xip_INCLUDE ${Xip_BINARY_DIR}/include)

# get the filename of the library for the built version of Xip
#get_filename_component(Xip_INSTALL_LIBRARY Xip_LIBRARY_NAME)

# add the install path to the library name
set(Xip_LIBRARY
  ${CMAKE_INSTALL_PREFIX}/lib/${Xip_INSTALL_LIBRARY})

set(Xip_INCLUDE ${CMAKE_INSTALL_PREFIX}/include)

# configure the file for the built version of Xip
configure_file(
  "${PROJECT_SOURCE_DIR}/XipConfig.cmake.in"
  "${PROJECT_BINARY_DIR}/XipConfig.cmake")

# configure the file for the installed version of Xip
configure_file(
  "${PROJECT_SOURCE_DIR}/XipConfig.cmake.in"
  "${PROJECT_BINARY_DIR}/InstallFiles/XipConfig.cmake")

# Configure the file describing how to use Xip
configure_file(
  ${Xip_SOURCE_DIR}/XipConfig.cmake.in
  ${Xip_BINARY_DIR}/XipConfig.cmake
  @ONLY)

configure_file(
  ${Xip_SOURCE_DIR}/UseXip.cmake.in
  ${Xip_BINARY_DIR}/UseXip.cmake
  @ONLY)

# Export the build settings and library dependencies
include(CMakeExportBuildSettings)

cmake_export_build_settings(${Xip_BINARY_DIR}/XipBuildSettings.cmake)

export_library_dependencies(${Xip_BINARY_DIR}/XipLibraryDepends.cmake)

# Install the packaging files for use by find_package(Xip)
install(FILES
  ${Xip_BINARY_DIR}/UseXip.cmake
  ${Xip_BINARY_DIR}/XipConfig.cmake
  ${Xip_BINARY_DIR}/XipBuildSettings.cmake
  ${Xip_BINARY_DIR}/XipLibraryDepends.cmake
  DESTINATION lib)

#--------------------------------------------------------------------
# Write config.xml
#
file(WRITE ${Xip_BINARY_DIR}/config/config.xml
"<XMLConfig>
    <section name=\"General\" >
        <setting key=\"x\" >-3</setting>
        <setting key=\"y\" >-3</setting>
        <setting key=\"width\" >1036</setting>
        <setting key=\"height\" >780</setting>
        <setting key=\"status\" >normal</setting>
        <setting key=\"html\" >enabled</setting>
    </section>
    <section name=\"RenderArea\" >
        <setting key=\"indirect\" >0</setting>
    </section>
    <section name=\"HtmlExport\" >
        <setting key=\"imageSize\" >1024</setting>
        <setting key=\"hideFields\" >0</setting>
        <setting key=\"hideTypeReferences\" >0</setting>
    </section>
    <section name=\"Recent Scene Graphs\" />

    <section name=\"Environment\">
      <setting key=\"XipHOME\" >../..</setting>
      <setting key=\"PATH\" path append|prepend>$XipHOME/xipext/vtk/bin</setting>
  </section>
</XMLConfig>")

#--------------------------------------------------------------------
# Write extensions.xml
#
file(WRITE ${Xip_BINARY_DIR}/config/extensions.xml
"<XMLConfig>
    <section name=\"libraries\" >
        <setting key=\"library\">xipivcore</setting>
        <setting key=\"library\">xipivcoregl</setting>
        <setting key=\"library\">xipivdicom</setting>
        <setting key=\"library\">xipivoverlay</setting>
        <setting key=\"library\">xipivrenderer</setting>
        <setting key=\"library\">xipivitk</setting>
        <setting key=\"library\">xipivvtk</setting>
        <setting key=\"library\">xipivremote</setting>
    </section>
    <section name=\"templates\" >
        <setting key=\"directory\">../templates</setting>
    </section>
</XMLConfig>")

#--------------------------------------------------------------------
# Write favorites.xml
#
file(WRITE ${Xip_BINARY_DIR}/config/favorites.xml
"<XMLConfig>
  <section name="favorites" />
</XMLConfig>")

#--------------------------------------------------------------------
# Write help.xml
#
file(WRITE ${Xip_BINARY_DIR}/config/help.xml
"<XMLConfig>
  <section name=\"references\" >
    <setting key=\"^SoItk[A-Z]\">http://www.itk.org/Doxygen/html/classitk_1_1HELPID(5).html</setting>
    <setting key=\"^So[A-Z]\">https://collab01a.scr.siemens.com/xipwiki/index.php/HELPID()</setting>
    <setting key=\":help\">https://collab01a.scr.siemens.com/xipwiki/index.php/XipBuilder</setting>
    <setting key=\".\">http://techpubs.sgi.com/library/tpl/cgi-bin/getdoc.cgi?coll=0650&amp;db=man&amp;fname=/usr/share/catman/p_man/cat3/Inventor_c/SoHELPID().z</setting>
  </section>
</XMLConfig>")

#--------------------------------------------------------------------
# Install config files for XipBuilder
#
install(FILES
  ${Xip_BINARY_DIR}/config/config.xml
  ${Xip_BINARY_DIR}/config/extensions.xml
  ${Xip_BINARY_DIR}/config/favorites.xml
  ${Xip_BINARY_DIR}/config/help.xml
  DESTINATION config)

#--------------------------------------------------------------------
# Testing
#
if(BUILD_TESTING)
set(TESTING_DIR ${Xip_BINARY_DIR}/Testing/Temporary)

file(GLOB_RECURSE RAD_EXAMPLES ${EXAMPLES_DIR} *.rad)
file(GLOB_RECURSE Xip_EXAMPLES ${EXAMPLES_DIR} *.xip)

foreach(EXAMPLE ${RAD_EXAMPLES})
  get_filename_component(SHORT_FILENAME ${EXAMPLE} NAME_WE)

  set(TESTED_SCREENSHOT ${TESTING_DIR}/${SHORT_FILENAME}.png)
  set(DIFFERENCE_IMAGE ${TESTING_DIR}/${SHORT_FILENAME}_diff.png)
  set(FILE_COMPARE_XML ${TESTING_DIR}/${SHORT_FILENAME}.xml)
  set(RENDER_FILE ${TESTING_DIR}/${SHORT_FILENAME}.txt)

  set(EXPECTED_SCREENSHOT ${Xip_SOURCE_DIR}/test/expected/${SHORT_FILENAME}.png)
  set(EXPECTED_ACCURACY ${Xip_SOURCE_DIR}/test/expected/${SHORT_FILENAME}.txt)

  if(EXISTS ${EXPECTED_SCREENSHOT})
    file(WRITE ${RENDER_FILE} "render(256,256,\"" ${TESTED_SCREENSHOT} "\");")
    add_test(${SHORT_FILENAME}Screenshot
      ${XipBUILDER}/xipbuilder.exe ${EXAMPLE} /config=${Xip_BINARY_DIR}/config /cmd=${RENDER_FILE})
#ADD_TEST(${SHORT_FILENAME}FileCompare
#${EXECUTABLE_OUTPUT_PATH}/fileCompare ${TESTED_SCREENSHOT} ${EXPECTED_SCREENSHOT} ${FILE_COMPARE_XML})
#ADD_TEST(${SHORT_FILENAME}SmartFileCompare
#${EXECUTABLE_OUTPUT_PATH}/smartFileCompare ${TESTED_SCREENSHOT} ${EXPECTED_SCREENSHOT})

    add_test(${SHORT_FILENAME}ColorUtils
      ${EXECUTABLE_OUTPUT_PATH}/color-utils ${TESTED_SCREENSHOT}
      ${EXPECTED_SCREENSHOT} ${DIFFERENCE_IMAGE} ${FILE_COMPARE_XML}
      ${EXPECTED_ACCURACY})
  endif(EXISTS ${EXPECTED_SCREENSHOT})

endforeach(EXAMPLE ${RAD_EXAMPLES})

foreach(EXAMPLE ${Xip_EXAMPLES})
  get_filename_component(SHORT_FILENAME ${EXAMPLE} NAME_WE)

  set(TESTED_SCREENSHOT ${TESTING_DIR}/${SHORT_FILENAME}Xip.png)
  set(DIFFERENCE_IMAGE ${TESTING_DIR}/${SHORT_FILENAME}_diff.png)
  set(FILE_COMPARE_XML ${TESTING_DIR}/${SHORT_FILENAME}Xip.xml)
  set(RENDER_FILE ${TESTING_DIR}/${SHORT_FILENAME}Xip.txt)

  set(EXPECTED_SCREENSHOT ${Xip_SOURCE_DIR}/test/expected/${SHORT_FILENAME}.png)
  set(EXPECTED_ACCURACY ${Xip_SOURCE_DIR}/test/expected/${SHORT_FILENAME}.txt)

  if(EXISTS ${EXPECTED_SCREENSHOT})
    file(WRITE ${RENDER_FILE} "render(256,256,\"" ${TESTED_SCREENSHOT} "\");")
    add_test(${SHORT_FILENAME}XipScreenshot
      ${XipBUILDER}/xipbuilder.exe ${EXAMPLE} /config=${Xip_BINARY_DIR}/config
      /cmd=${RENDER_FILE})
    add_test(${SHORT_FILENAME}XipColorUtils
      ${EXECUTABLE_OUTPUT_PATH}/color-utils ${TESTED_SCREENSHOT}
      ${EXPECTED_SCREENSHOT} ${DIFFERENCE_IMAGE} ${FILE_COMPARE_XML}
      ${EXPECTED_ACCURACY})
    #add_test(${SHORT_FILENAME}Dummy
    #  ${EXECUTABLE_OUTPUT_PATH}/dummy ${TESTED_SCREENSHOT}
    #  -T ${Xip_BINARY_DIR}/Testing/Temporary
    #  -V ${EXPECTED_SCREENSHOT})
  endif(EXISTS ${EXPECTED_SCREENSHOT})

endforeach(EXAMPLE ${Xip_EXAMPLES})

endif(BUILD_TESTING)
