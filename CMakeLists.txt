# Sylvain Jaume 2007

project(XIP)
cmake_minimum_required(VERSION 2.6)

#--------------------------------------------------------------------
# Testing configuration
#
option(BUILD_TESTING "Create the testing framework" OFF)
mark_as_advanced(BUILD_TESTING)

if(BUILD_TESTING)
  enable_testing()
endif(BUILD_TESTING)

include(Dart)
mark_as_advanced(DART_ROOT)

#--------------------------------------------------------------------
# Set build type to Release
#
mark_as_advanced(CMAKE_BUILD_TYPE
  CMAKE_CONFIGURATION_TYPES
  CMAKE_OSX_ARCHITECTURES
  CMAKE_OSX_SYSROOT)

if(NOT WIN32 AND NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING
  "Choose the type of build, options are: Debug Release 
  RelWithDebInfo MinSizeRel." FORCE)
endif(NOT WIN32 AND NOT CMAKE_BUILD_TYPE)

#--------------------------------------------------------------------
# Set up CPack support, to be able to distribute XIP binary packages.
# It will be particulary useful to distributed prebuilt XIP witk
# extended languages support enable. An even minor version number
# corresponds to releases.
#
include(InstallRequiredSystemLibraries)

set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "eXtensible Imaging Platorm")
set(CPACK_PACKAGE_VENDOR "Siemens Corporate Research Inc.")

set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE.txt")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE.txt")

set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "1")
set(CPACK_PACKAGE_VERSION_PATCH "0")

set(XIP_VERSION_STRING ${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH})

set(CPACK_PACKAGE_INSTALL_DIRECTORY
  "xip-${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}")
set(CPACK_SOURCE_PACKAGE_FILE_NAME "xip-${XIP_VERSION_STRING}-src"
  CACHE INTERNAL "compressed file containing all source code")

set(CPACK_PACKAGE_DESCRIPTION_FILE ${CMAKE_CURRENT_SOURCE_DIR}/README.txt)

if(WIN32)
  string(REGEX REPLACE "/" "\\\\\\\\" CPACK_PACKAGE_ICON
    "${CMAKE_CURRENT_SOURCE_DIR}/doc/xip_logo.bmp")

  set(CPACK_NSIS_DISPLAY_NAME "${CPACK_PACKAGE_INSTALL_DIRECTORY}")
  set(CPACK_NSIS_HELP_LINK "https://collab01a.scr.siemens.com/xipwiki/")
  set(CPACK_NSIS_URL_INFO_ABOUT "http://www.openxip.org")
  set(CPACK_NSIS_CONTACT "sylvain.jaume@siemens.com")
endif(WIN32)

if(WIN32)
  set(CPACK_GENERATOR NSIS)
  set(CPACK_SOURCE_GENERATOR NSIS)
endif(WIN32)

if(APPLE)
  set(CPACK_GENERATOR PackageMaker)
  set(CPACK_SOURCE_GENERATOR TZ)
endif(APPLE)

if(UNIX AND NOT APPLE)
  set(CPACK_GENERATOR TZ)
  set(CPACK_SOURCE_GENERATOR TZ)
endif(UNIX AND NOT APPLE)

# The following components are regex's to match anywhere (unless anchored)
# in absolute path + filename to find files or directories to be excluded
# from source tarball.
set(CPACK_SOURCE_IGNORE_FILES
  "~$"
  "\\\\.svn$"
  "^${PROJECT_SOURCE_DIR}.*/.svn/")

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
# Rules to configure the Doxygen documentation
#
configure_file(${XIP_SOURCE_DIR}/build/doxygen.config.in
               ${XIP_BINARY_DIR}/doxygen.config)

configure_file(${XIP_SOURCE_DIR}/build/doxygen.pl.in
               ${XIP_BINARY_DIR}/doxygen.pl)

configure_file(${XIP_SOURCE_DIR}/build/Doxyfile.in
               ${XIP_BINARY_DIR}/Doxyfile)

#--------------------------------------------------------------------
# Options to build with third party libraries.
#
option(HAS_DCMTK "Build the DICOM module. Requires the external library
  DCMTK found in the xipext zip file." ON)

option(HAS_ITK "Build the ITK module. Requires the external libraries
  the Insight Toolkit found in the xipext zip file." ON)

option(HAS_VTK "Build the VTK module. Requires the external libraries of
  the Visualization Toolkit found in the xipext zip file." ON)

mark_as_advanced(CMAKE_INSTALL_PREFIX
  HAS_DCMTK
  HAS_ITK
  HAS_VTK)

#--------------------------------------------------------------------
# Options to build OpenInventor
#
option(BUILD_INVENTOR "Build the Open Inventor library" ON)
mark_as_advanced(BUILD_INVENTOR)

#--------------------------------------------------------------------
# Generate the Doxygen documentation
#
option(BUILD_DOCUMENTATION "Generate the Doxygen documentation" OFF)
mark_as_advanced(BUILD_DOCUMENTATION)

if(BUILD_DOCUMENTATION)
  find_package(Doxygen)
endif(BUILD_DOCUMENTATION)

#--------------------------------------------------------------------
# Find external libraries
#
if(NOT BUILD_INVENTOR)
  find_path(OIV_PATH bin/xipinv240.dll
    ../xipext-win32-vs8/inventor
    ../xipext-mac-xcode/inventor
    ../xipext-linux-gcc/inventor
    "Directory where Open Inventor is installed")
endif(NOT BUILD_INVENTOR)

#--------------------------------------------------------------------
# Find VTK libraries
#
if(HAS_VTK)

  find_package(VTK)

  if(VTK)
    include(${VTK_USE_FILE})
  else(VTK)
    find_path(VTK_DIR VTKConfig.cmake
      ${XIP_SOURCE_DIR}/../xipext-win32-vs8/lib/vtk-5.0
      ${XIP_SOURCE_DIR}/../xipext-mac-xcode/lib/vtk-5.0
      ${XIP_SOURCE_DIR}/../xipext-linux-gcc/lib/vtk-5.0
      "Directory where VTK is installed")
  endif(VTK)

  mark_as_advanced(
    VTK_GLEXT_FILE
    VTK_GLXEXT_FILE
    VTK_WGLEXT_FILE)

endif(HAS_VTK)

#--------------------------------------------------------------------
# Output directories
#
if(NOT EXECUTABLE_OUTPUT_PATH)
  set(EXECUTABLE_OUTPUT_PATH ${XIP_BINARY_DIR}/bin CACHE PATH
    "Single output directory for building all executables.")
endif(NOT EXECUTABLE_OUTPUT_PATH)

if(NOT LIBRARY_OUTPUT_PATH)
  set(LIBRARY_OUTPUT_PATH ${XIP_BINARY_DIR}/bin CACHE PATH
    "Single output directory for building all libraries.")
endif(NOT LIBRARY_OUTPUT_PATH)

mark_as_advanced(EXECUTABLE_OUTPUT_PATH LIBRARY_OUTPUT_PATH)

#--------------------------------------------------------------------
# Define compiler flags
#
if(WIN32)
  add_definitions(-DXIPCOMMON_EXPORTS) # for XIPException.h
endif(WIN32)

#--------------------------------------------------------------------
# Disable deprecation warnings for standard C functions
#
if(UNIX AND NOT APPLE)
  add_definitions(-DGL_EXT_timer_query)
endif(UNIX AND NOT APPLE)

if(CMAKE_COMPILER_2005)
  add_definitions(-D_CRT_SECURE_NO_DEPRECATE -D_CRT_NONSTDC_NO_DEPRECATE)
endif(CMAKE_COMPILER_2005)

#--------------------------------------------------------------------
# Find the xipbuilder executable, required for testing.
#
if(BUILD_TESTING)
  find_file(XIP_BUILDER_DEBUG xipbuilder.exe
    "C:/Program Files/XIP/Debug")
  find_file(XIP_BUILDER_RELEASE xipbuilder.exe
    "C:/Program Files/XIP/release")
  mark_as_advanced(XIP_BUILDER_DEBUG XIP_BUILDER_RELEASE)
endif(BUILD_TESTING)

#--------------------------------------------------------------------
# Include directories
#
include_directories(include)

if(OIV_PATH)
  include_directories(${OIV_PATH}/include)
endif(OIV_PATH)

#--------------------------------------------------------------------
# Link directories
#
link_directories(
  ${LIBRARY_OUTPUT_PATH}
  .) # Put "." in the rpath of all XIP shared libraries.

if(XIPEXT)
  link_directories(${XIPEXT}/inventor/lib)
endif(XIPEXT)

#--------------------------------------------------------------------
# Build projects inside subdirectories
#
add_subdirectory(src)
add_subdirectory(test)

#--------------------------------------------------------------------
# Install the xipbuilder executable
#
if(XIP_BUILDER_DEBUG)
  install(FILES ${XIP_BUILDER_DEBUG}
    DESTINATION bin/debug CONFIGURATIONS Debug)
endif(XIP_BUILDER_DEBUG)

if(XIP_BUILDER_RELEASE)
  install(FILES ${XIP_BUILDER_RELEASE}
    DESTINATION bin/release CONFIGURATIONS Release)
endif(XIP_BUILDER_RELEASE)

#--------------------------------------------------------------------
# Copy Qt files to the install directory
#
option(INSTALL_QT "Copy Qt files to the install directory" OFF)
mark_as_advanced(INSTALL_QT)

if(INSTALL_QT)
  find_package(Qt4)
  if(QT4_FOUND)
    install(FILES
      ${QT_INCLUDE_DIR}/../bin/QtCore4.dll
      ${QT_INCLUDE_DIR}/../bin/QtGui4.dll
      ${QT_INCLUDE_DIR}/../bin/QtOpenGL4.dll
      ${QT_INCLUDE_DIR}/../bin/QtSvg4.dll
      ${QT_INCLUDE_DIR}/../bin/QtXml4.dll
      ${QT_INCLUDE_DIR}/../bin/QtScript4.dll
      DESTINATION bin/release
      CONFIGURATIONS Release)

    install(FILES
      ${QT_INCLUDE_DIR}/../bin/QtCored4.dll
      ${QT_INCLUDE_DIR}/../bin/QtGuid4.dll
      ${QT_INCLUDE_DIR}/../bin/QtOpenGLd4.dll
      ${QT_INCLUDE_DIR}/../bin/QtSvgd4.dll
      ${QT_INCLUDE_DIR}/../bin/QtXmld4.dll
      ${QT_INCLUDE_DIR}/../bin/QtScriptd4.dll
      ${QT_INCLUDE_DIR}/../bin/QtCored4.pdb
      ${QT_INCLUDE_DIR}/../bin/QtGuid4.pdb
      ${QT_INCLUDE_DIR}/../bin/QtOpenGLd4.pdb
      ${QT_INCLUDE_DIR}/../bin/QtSvgd4.pdb
      ${QT_INCLUDE_DIR}/../bin/QtXmld4.pdb
      ${QT_INCLUDE_DIR}/../bin/QtScriptd4.pdb
      DESTINATION bin/debug
      CONFIGURATIONS Debug)

  endif(QT4_FOUND)
endif(INSTALL_QT)

#--------------------------------------------------------------------
# Install header files located in include directory
#
file(GLOB_RECURSE FILES_IN_DIRECTORY RELATIVE ${XIP_SOURCE_DIR} include/*.h)

foreach(HEADER_FILE ${FILES_IN_DIRECTORY})

  get_filename_component(INSTALL_PATH ${HEADER_FILE} PATH)
  install(FILES ${HEADER_FILE} DESTINATION ${INSTALL_PATH})

endforeach(HEADER_FILE ${FILES_IN_DIRECTORY})

#--------------------------------------------------------------------
# Install header files located in src/extern/inventor/lib/
#
file(GLOB_RECURSE FILES_IN_DIRECTORY RELATIVE
  ${XIP_SOURCE_DIR}/src/extern/inventor/lib/ src/extern/inventor/lib/*.h)

foreach(HEADER_FILE ${FILES_IN_DIRECTORY})

  get_filename_component(INSTALL_PATH ${HEADER_FILE} PATH)

  if(${INSTALL_PATH} MATCHES "src")
  else(${INSTALL_PATH} MATCHES "src")

    string(REGEX REPLACE "database/"    "" INSTALL_PATH ${INSTALL_PATH})
    string(REGEX REPLACE "interaction/" "" INSTALL_PATH ${INSTALL_PATH})
    string(REGEX REPLACE "mevis/"       "" INSTALL_PATH ${INSTALL_PATH})
    string(REGEX REPLACE "nodekits/"    "" INSTALL_PATH ${INSTALL_PATH})
    string(REGEX REPLACE "xip/"         "" INSTALL_PATH ${INSTALL_PATH})

    install(FILES src/extern/inventor/lib/${HEADER_FILE}
      DESTINATION ${INSTALL_PATH})
  endif(${INSTALL_PATH} MATCHES "src")
 
endforeach(HEADER_FILE ${FILES_IN_DIRECTORY})

#--------------------------------------------------------------------
# RAD examples
#
set(EXAMPLES
"examples/core/display_raw_image.rad"
"examples/core/two_viewports.rad"
"examples/coregl/FboManagement/FboAdvancedMedical.rad"
"examples/coregl/FboManagement/FboSimpleMedical.rad"
"examples/coregl/offscreenRenderer/xip_offline.rad"
"examples/coregl/shader/shader.rad"
"examples/coregl/ShaderManagement/ShaderManagerMedical.rad"
"examples/dicom/display_dicom_image.rad"
"examples/dicom/display_dicom_images.rad"
"examples/dicom/GetDicomString.rad"
"examples/dicom/load_presentationstate.rad"
"examples/dicom/save_presentationstate.rad"
"examples/inventor/cone1.rad"
"examples/inventor/cone2.rad"
"examples/inventor/cone3.rad"
"examples/itk/Casting, Intensity Mapping/CastImageFilter.rad"
"examples/itk/Casting, Intensity Mapping/IntensityWindowingImageFilter.rad"
"examples/itk/Casting, Intensity Mapping/RelabelComponentImageFilter.rad"
"examples/itk/Casting, Intensity Mapping/RescaleIntensityImageFilter.rad"
"examples/itk/Distance Map/ApproximateSignedDistanceMapImageFilter.rad"
"examples/itk/Distance Map/DanielssonDistanceMapImageFilter.rad"
"examples/itk/Distance Map/SignedDanielIssonDistanceMapImageFilter.rad"
"examples/itk/Edge Detection/CannyEdgeDetectionImageFilters.rad"
"examples/itk/Edge Detection/SimpleContourExtractorImageFilter.rad"
"examples/itk/Edge Detection/ZeroCrossingBasedEdgeDetectionImageFilter.rad"
"examples/itk/Functor Filters/Binary Functor Filters/AbsoluteValueDifferenceImageFilter.rad"
"examples/itk/Functor Filters/Binary Functor Filters/AddImageFilter.rad"
"examples/itk/Functor Filters/Binary Functor Filters/Binary Images Filters/AndImageFilter.rad"
"examples/itk/Functor Filters/Binary Functor Filters/Binary Images Filters/NotImageFilter.rad"
"examples/itk/Functor Filters/Binary Functor Filters/Binary Images Filters/OrImageFilter.rad"
"examples/itk/Functor Filters/Binary Functor Filters/Binary Images Filters/XorImageFilter.rad"
"examples/itk/Functor Filters/Binary Functor Filters/ConstrainedValueAdditionImageFilter.rad"
"examples/itk/Functor Filters/Binary Functor Filters/ConstrainedValueDifferenceImageFilter.rad"
"examples/itk/Functor Filters/Binary Functor Filters/DifferenceImageFilter.rad"
"examples/itk/Functor Filters/Binary Functor Filters/DivideImageFilter.rad"
"examples/itk/Functor Filters/Binary Functor Filters/InterpolateImageFilter.rad"
"examples/itk/Functor Filters/Binary Functor Filters/MaskImageFilter.rad"
"examples/itk/Functor Filters/Binary Functor Filters/MaskNegatedImageFilter.rad"
"examples/itk/Functor Filters/Binary Functor Filters/MaximumImageFilter.rad"
"examples/itk/Functor Filters/Binary Functor Filters/MultiplyImageFilter.rad"
"examples/itk/Functor Filters/Binary Functor Filters/SquaredDifferenceImageFilter.rad"
"examples/itk/Functor Filters/Binary Functor Filters/SubtractImageFilter.rad"
"examples/itk/Functor Filters/Ternay Functor Filters/TernaryAddImageFilter.rad"
"examples/itk/Functor Filters/Ternay Functor Filters/TernaryMagnitudeImageFilter.rad"
"examples/itk/Functor Filters/Ternay Functor Filters/TernaryMagnitudeSquaredImageFilter.rad"
"examples/itk/Functor Filters/Unary Functor Filters/Atan2ImageFilter.rad"
"examples/itk/Functor Filters/Unary Functor Filters/BSpline Filters/BSplineDecompositionImageFilter.rad"
"examples/itk/Functor Filters/Unary Functor Filters/BSpline Filters/BSplineDownsampleImageFilter.rad"
"examples/itk/Functor Filters/Unary Functor Filters/BSpline Filters/BSplineUpsampleImageFilter.rad"
"examples/itk/Functor Filters/Unary Functor Filters/ExpNegativeImageFilter.rad"
"examples/itk/Functor Filters/Unary Functor Filters/GetAverageSliceImageFilter.rad"
"examples/itk/Functor Filters/Unary Functor Filters/Log10ImageFilter.rad"
"examples/itk/Functor Filters/Unary Functor Filters/LogImageFilter.rad"
"examples/itk/Functor Filters/Unary Functor Filters/NormalizeImageFilter.rad"
"examples/itk/Functor Filters/Unary Functor Filters/NotImageFilter.rad"
"examples/itk/Functor Filters/Unary Functor Filters/SigmoidImageFilter.rad"
"examples/itk/Functor Filters/Unary Functor Filters/SinImageFilter.rad"
"examples/itk/Functor Filters/Unary Functor Filters/SqrtImageFilter.rad"
"examples/itk/Functor Filters/Unary Functor Filters/SquareImageFilter.rad"
"examples/itk/Functor Filters/Unary Functor Filters/TanImageFilter.rad"
"examples/itk/Functor Filters/Unary Functor Filters/TrigoImageFilters.rad"
"examples/itk/Geometric Transformations/CheckerBoardImageFilter.rad"
"examples/itk/Geometric Transformations/CropImageFilter.rad"
"examples/itk/Geometric Transformations/ExtractImageFilter.rad"
"examples/itk/Geometric Transformations/FlipImageFilter.rad"
"examples/itk/Geometric Transformations/MultiResolutionPyramidImageFilter.rad"
"examples/itk/Geometric Transformations/NonThreadedShrinkImageFilter.rad"
"examples/itk/Geometric Transformations/Padding Image Filters/ConstantPadImageFilter.rad"
"examples/itk/Geometric Transformations/Padding Image Filters/MirrorPadImageFilter.rad"
"examples/itk/Geometric Transformations/Padding Image Filters/PadImageFilters.rad"
"examples/itk/Geometric Transformations/Padding Image Filters/WrapPadImageFilter.rad"
"examples/itk/Geometric Transformations/PasteImageFilter.rad"
"examples/itk/Geometric Transformations/PermuteAxesImageFilter.rad"
"examples/itk/Geometric Transformations/ReflectImageFilter.rad"
"examples/itk/Geometric Transformations/RegionOfInterestImageFilter.rad"
"examples/itk/Geometric Transformations/ShiftScaleImageFilter.rad"
"examples/itk/Geometric Transformations/ShrinkImageFilter.rad"
"examples/itk/Geometric Transformations/TileImageFilter.rad"
"examples/itk/Neighborhood Filters/BlackTopHatImageFilter.rad"
"examples/itk/Neighborhood Filters/ConnectedComponentImageFilter.rad"
"examples/itk/Neighborhood Filters/HardConnectedImageFilter.rad"
"examples/itk/Neighborhood Filters/MeanImageFilter.rad"
"examples/itk/Neighborhood Filters/MedianImageFilter.rad"
"examples/itk/Neighborhood Filters/Morphology Image Filters/BinaryMedianImageFilter.rad"
"examples/itk/Neighborhood Filters/Morphology Image Filters/BinaryPrunningImageFilter.rad"
"examples/itk/Neighborhood Filters/Morphology Image Filters/BinaryThinningImageFilter.rad"
"examples/itk/Neighborhood Filters/Morphology Image Filters/MaskNeighborhoodOperatorImageFilter.rad"
"examples/itk/Neighborhood Filters/Morphology Image Filters/NeighborhoodOperatorImageFilter.rad"
"examples/itk/Neighborhood Filters/Voting Filters/VotingBinaryHoleFillingImageFilter.rad"
"examples/itk/Neighborhood Filters/Voting Filters/VotingBinaryImageFilter.rad"
"examples/itk/Neighborhood Filters/Voting Filters/VotingBinaryIterativeHoleFillingImageFilter.rad"
"examples/itk/Neighborhood Filters/WhiteTopHatImageFilter.rad"
"examples/itk/Neighborhood Filters/ZeroCrossingImageFilter.rad"
"examples/itk/Reading and Writing/ImageFileReader.rad"
"examples/itk/Reading and Writing/ImageFileWriter.rad"
"examples/itk/Reading and Writing/ImportImageFilter.rad"
"examples/itk/Registration/2DRigidRegistration.rad"
"examples/itk/Segmentation/Level sets/CannySegmentationLevelSetImageFilter.rad"
"examples/itk/Segmentation/StapleImageFilter.rad"
"examples/itk/Smoothing, Derivatve Filters/AntiAliasBinaryFilter.rad"
"examples/itk/Smoothing, Derivatve Filters/BinaryMagnitudeImageFilter.rad"
"examples/itk/Smoothing, Derivatve Filters/BinaryMinMaxCurvatureFlowImageFilter.rad"
"examples/itk/Smoothing, Derivatve Filters/BinomialBlurImageFilter.rad"
"examples/itk/Smoothing, Derivatve Filters/BSplineSmoothing.rad"
"examples/itk/Smoothing, Derivatve Filters/CurvatureFlowImageFilter.rad"
"examples/itk/Smoothing, Derivatve Filters/DerivativeImageFilter.rad"
"examples/itk/Smoothing, Derivatve Filters/DiscreteGaussianImageFilter.rad"
"examples/itk/Smoothing, Derivatve Filters/GradientMagnitudeImageFilter.rad"
"examples/itk/Smoothing, Derivatve Filters/GradientMagnitudeRecursiveGaussianImageFilter.rad"
"examples/itk/Smoothing, Derivatve Filters/LaplacianImageFilter.rad"
"examples/itk/Smoothing, Derivatve Filters/LaplacianRecursiveGaussianImageFilter.rad"
"examples/itk/Smoothing, Derivatve Filters/LaplacianSharpeningImageFilter.rad"
"examples/itk/Smoothing, Derivatve Filters/MinMaxCurvatureFlowImageFilter.rad"
"examples/itk/Smoothing, Derivatve Filters/NoiseImageFilter.rad"
"examples/itk/Smoothing, Derivatve Filters/RecursiveGaussianImageFilter.rad"
"examples/itk/Smoothing, Derivatve Filters/SmoothingRecursiveGaussianImageFilter.rad"
"examples/itk/Statistics, Informations Filters/StatisticsImageFilter.rad"
"examples/itk/Threshold/BinaryThresholdImageFilter.rad"
"examples/itk/Threshold/DoubleThresholdImageFilter.rad"
"examples/remote/client.rad"
"examples/remote/mpr.rad"
"examples/remote/mpr1.rad"
"examples/remote/mprclient.rad"
"examples/remote/MPRRenderer.rad"
"examples/remote/MultiViewer.rad"
"examples/remote/offline_renderer.rad"
"examples/remote/render.rad"
"examples/remote/Server.rad"
"examples/renderer/MPR/mpr.rad"
"examples/renderer/MPR/mpr_loadraw.rad"
"examples/renderer/MPR/mpr_loadraw_multiple.rad"
"examples/renderer/MPR/simple_mpr.rad"
"examples/renderer/slicer/dicomSlicer.rad"
"examples/renderer/slicer/slicer.rad"
"examples/renderer/slicer/slicerWithLut.rad"
"examples/renderer/slicer/slicerWithLutShaded.rad"
"examples/vtk/Converters/XIPImageToVtk.rad"
"examples/vtk/DICOM/VolumeRendering.rad"
"examples/vtk/Tutorial/ConeSource.rad"
"examples/vtk/VisualizationAlgorithms/ClipCow.rad"
"examples/vtk/VisualizationAlgorithms/officeTube.rad"
"examples/vtk/VolumeRendering/PseudoVolumeRendering.rad"
"examples/vtk/VolumeRendering/SimpleRayCast.rad"
"examples/vtk/VolumeRendering/SimpleTextureMap2D.rad"
"examples/vtk/VolumeRendering/VolumeRendering.rad")

#--------------------------------------------------------------------
# XIP examples
#
set(EXAMPLES ${EXAMPLES}
"examples/coregl/TransparentGeometry/transparent_geometry_none.xip"
"examples/coregl/TransparentGeometry/transparent_geometry_pingpong.xip"
"examples/coregl/TransparentGeometry/transparent_geometry_texture3D.xip"
"examples/itk/Casting, Intensity Mapping/AdaptiveHistogramEqualizationImageFilter.xip"
"examples/itk/Casting, Intensity Mapping/HistogramMatchingImageFilter.xip"
"examples/itk/Functor Filters/Binary Functor Filters/WeightedAddImageFilter.xip"
"examples/itk/Functor Filters/Unary Functor Filters/AccumulateImageFilter.xip"
"examples/itk/Functor Filters/Unary Functor Filters/AcosImageFilter.xip"
"examples/itk/Functor Filters/Unary Functor Filters/AsinImageFilter.xip"
"examples/itk/Functor Filters/Unary Functor Filters/AtanImageFilter.xip"
"examples/itk/Functor Filters/Unary Functor Filters/BoundedReciprocalImageFilter.xip"
"examples/itk/Functor Filters/Unary Functor Filters/CosImageFilter.xip"
"examples/itk/Functor Filters/Unary Functor Filters/ExpImageFilter.xip"
"examples/itk/Functor Filters/Unary Functor Filters/HConcaveImageFilter.xip"
"examples/itk/Functor Filters/Unary Functor Filters/HConvexImageFilter.xip"
"examples/itk/Functor Filters/Unary Functor Filters/HMaximalImageFilter.xip"
"examples/itk/Functor Filters/Unary Functor Filters/HMinimalImageFilter.xip"
"examples/itk/PointSet/BinaryMaskToNarrowBandPointSetFilter.xip"
"examples/itk/Segmentation/Level sets/ShapeDetectionLevelSetImageFilter.xip"
"examples/itk/Segmentation/Region Growth/CollidingFrontsImageFilter.xip"
"examples/itk/Segmentation/Region Growth/ConfidenceConnectedImageFilter.xip"
"examples/itk/Segmentation/Region Growth/ConnectedThresholdImageFilter.xip"
"examples/itk/Segmentation/Region Growth/IsolatedConnectedImageFilters.xip"
"examples/itk/Segmentation/Watershed/IsolatedWatershedImageFilter.xip"
"examples/overlay/all_shapes.xip"
"examples/overlay/display_text.xip"
"examples/overlay/lutcolorbar.xip"
"examples/overlay/measurements.xip"
"examples/overlay/overlay_color.xip"
"examples/overlay/overlay_drawstyle.xip"
"examples/overlay/overlay_manager.xip"
"examples/overlay/overlay_manipulation.xip"
"examples/overlay/overlay_menu.xip"
"examples/overlay/overlay_multi_label_search.xip"
"examples/overlay/overlay_reading_saving.xip"
"examples/overlay/overlay_search_contour.xip"
"examples/overlay/overlay_set_properties.xip"
"examples/overlay/plotting_1.xip"
"examples/overlay/plotting_2.xip"
"examples/overlay/plotting_3.xip"
"examples/overlay/plotting_4.xip"
"examples/overlay/plotting_5.xip"
"examples/overlay/shape_measurements.xip"
"examples/remote/client.xip"
"examples/remote/render.xip"
"examples/renderer/MPR/CPUmpr.xip"
"examples/renderer/slicer/dicomSlicer.xip"
"examples/tftk/EditorNetwork.xip"
"examples/tftk/NoHistNode.xip"
"examples/tftk/rebuiltAfterhist.xip"
"examples/tftk/TEST.xip"
"examples/tftk/TF-1D-2DHist.xip"
"examples/tftk/TF-1D-2DVolRender.xip"
"examples/tftk/TF-1D-2DVolRender2.xip"
"examples/tftk/TF-1D-2DVolRenderDualCT.xip"
"examples/tftk/TF-1D-2DVolRenderDualCT2.xip"
"examples/tftk/TF-1D-2DVolRenderDualCTHist.xip"
"examples/tftk/TF-1D-2DVolRenderDualCTHist2.xip"
"examples/tftk/TF-1D-2DVolRenderDualCTHist3.xip"
"examples/tftk/TF-1D-2DVolRenderDualCTHist4.xip"
"examples/tftk/TF-1D-2DVolRenderDualCTHist5.xip"
"examples/tftk/TF-1D-2DVolRenderDualCTHist6.xip"
"examples/tftk/TF-1D-2DVolRenderDualCTHist7.xip"
"examples/tftk/TF-1D-2DVolRenderDualCTHist8.xip"
"examples/tftk/TF-1D-2DVolRenderDualCTHist9.xip"
"examples/tftk/TF-1D-2DVolRenderDualCTWorkingVolume.xip"
"examples/tftk/TFeditorTesting.xip"
"examples/tftk/TFHistTesting1.xip"
"examples/tftk/TFHistTesting12.xip"
"examples/tftk/ttt.xip"
"examples/tftk/tttt.xip"
"examples/vtk/VisualizationAlgorithms/appendpolydata.xip"
"examples/vtk/VisualizationAlgorithms/arrowsource.xip"
"examples/vtk/VisualizationAlgorithms/axes.xip"
"examples/vtk/VisualizationAlgorithms/butterflysubdivisionfilter.xip"
"examples/vtk/VisualizationAlgorithms/cubesource.xip"
"examples/vtk/VisualizationAlgorithms/decimatepro.xip"
"examples/vtk/VisualizationAlgorithms/delaunay2d.xip"
"examples/vtk/VisualizationAlgorithms/disksource.xip"
"examples/vtk/VisualizationAlgorithms/earthsource.xip"
"examples/vtk/VisualizationAlgorithms/glyph3d.xip"
"examples/vtk/VisualizationAlgorithms/imageactor.xip"
"examples/vtk/VisualizationAlgorithms/imagemarchingcubes.xip"
"examples/vtk/VisualizationAlgorithms/lodactor.xip"
"examples/vtk/VisualizationAlgorithms/tubefilter.xip")

#--------------------------------------------------------------------
# GLSL files
#
set(GLSL_FILES
examples/coregl/FboManagement/shaders/color_fp.glsl
examples/coregl/FboManagement/shaders/color_vp.glsl
examples/coregl/FboManagement/shaders/mask_fp.glsl
examples/coregl/FboManagement/shaders/mask_vp.glsl
examples/coregl/FboManagement/shaders/slicer_fp.glsl
examples/coregl/FboManagement/shaders/slicer_vp.glsl
examples/coregl/FboManagement/shaders/tex_fp.glsl
examples/coregl/FboManagement/shaders/tex_vp.glsl
examples/coregl/ShaderManagement/shaders/slicer1_fp.glsl
examples/coregl/ShaderManagement/shaders/slicer2_fp.glsl
examples/coregl/ShaderManagement/shaders/slicer3_fp.glsl
examples/coregl/ShaderManagement/shaders/slicer_vp.glsl
examples/coregl/TransparentGeometry/shaders/composite_frag.glsl
examples/coregl/TransparentGeometry/shaders/composite_texture3D_frag.glsl
examples/coregl/TransparentGeometry/shaders/transparent_geometry_frag.glsl
examples/coregl/TransparentGeometry/shaders/transparent_geometry_texture3D_frag.glsl
examples/remote/mpr_fp.glsl
examples/remote/mpr_vp.glsl
examples/remote/shade_tf_fp.glsl
examples/remote/simpleLut_tf_fp.glsl
examples/remote/simple_tf_fp.glsl
examples/remote/simple_vp.glsl
examples/renderer/MPR/mpr_fp.glsl
examples/renderer/MPR/mpr_vp.glsl
examples/renderer/MPR/slicerfp.glsl
examples/renderer/slicer/noshading_tf_fp.glsl
examples/renderer/slicer/shade_tf_fp.glsl
examples/renderer/slicer/simpleLut_tf_fp.glsl
examples/renderer/slicer/simple_tf_fp.glsl
examples/renderer/slicer/simple_vp.glsl
examples/tftk/shaders/generateHist_fp.glsl
examples/tftk/shaders/generateHist_vp.glsl
examples/tftk/shaders/shade_tf_fp.glsl
examples/tftk/shaders/showTF_fp.glsl
examples/tftk/shaders/showTF_vp.glsl
examples/tftk/shaders/simple_vp.glsl
examples/tftk/shaders/slicer_tf1D_fp.glsl
examples/tftk/shaders/slicer_tf2D_fp.glsl
examples/tftk/shaders/test_fp.glsl
examples/tftk/shaders/test_vp.glsl)

#--------------------------------------------------------------------
# Copy the examples to the install directory
#
foreach(EXAMPLE ${EXAMPLES} ${GLSL_FILES})
  get_filename_component(INSTALL_PATH ${EXAMPLE} PATH)
  install(FILES ${EXAMPLE} DESTINATION ${INSTALL_PATH})
endforeach(EXAMPLE ${EXAMPLES} ${GLSL_FILES})

#--------------------------------------------------------------------
# Install the documentation
#
install(FILES
  doc/XIPOverview.ppt
  doc/XIPStarterGuide.doc
  doc/xip_logo.png
  doc/xipbuilder_logo.png
  DESTINATION doc)

#--------------------------------------------------------------------
# XIP Library
#

# Create the file for the built version of XIP
configure_file(
  "${PROJECT_SOURCE_DIR}/XIPConfig.cmake.in"
  "${PROJECT_BINARY_DIR}/XIPConfig.cmake")

# Create the file for the installed version of XIP
configure_file(
  "${PROJECT_SOURCE_DIR}/XIPConfig.cmake.in"
  "${PROJECT_BINARY_DIR}/InstallFiles/XIPConfig.cmake")

# Create the file describing how to link to XIP
configure_file(
  ${XIP_SOURCE_DIR}/XIPConfig.cmake.in
  ${XIP_BINARY_DIR}/XIPConfig.cmake
  @ONLY)

configure_file(
  ${XIP_SOURCE_DIR}/UseXIP.cmake.in
  ${XIP_BINARY_DIR}/UseXIP.cmake
  @ONLY)

# Export the build settings and library dependencies
include(CMakeExportBuildSettings)

cmake_export_build_settings(${XIP_BINARY_DIR}/XIPBuildSettings.cmake)

export_library_dependencies(${XIP_BINARY_DIR}/XIPLibraryDepends.cmake)

# Install the packaging files for use by find_package(XIP)
install(FILES
  ${XIP_BINARY_DIR}/UseXIP.cmake
  ${XIP_BINARY_DIR}/XIPConfig.cmake
  ${XIP_BINARY_DIR}/XIPBuildSettings.cmake
  ${XIP_BINARY_DIR}/XIPLibraryDepends.cmake
  DESTINATION lib)

#--------------------------------------------------------------------
# Write config.xml
#
file(WRITE ${XIP_BINARY_DIR}/config/config.xml
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
      <setting key=\"XIPHOME\" >../..</setting>
      <setting key=\"PATH\" path append|prepend>$XIPHOME/xipext/vtk/bin</setting>
  </section>
</XMLConfig>")

#--------------------------------------------------------------------
# Write extensions.xml
#
file(WRITE ${XIP_BINARY_DIR}/config/extensions.xml
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
file(WRITE ${XIP_BINARY_DIR}/config/favorites.xml
"<XMLConfig>
  <section name="favorites" />
</XMLConfig>")

#--------------------------------------------------------------------
# Write help.xml
#
file(WRITE ${XIP_BINARY_DIR}/config/help.xml
"<XMLConfig>
  <section name=\"references\" >
    <setting key=\"^SoItk[A-Z]\">http://www.itk.org/Doxygen/html/classitk_1_1HELPID(5).html</setting>
    <setting key=\"^So[A-Z]\">https://collab01a.scr.siemens.com/xipwiki/index.php/HELPID()</setting>
    <setting key=\":help\">https://collab01a.scr.siemens.com/xipwiki/index.php/XIPBuilder</setting>
    <setting key=\".\">http://techpubs.sgi.com/library/tpl/cgi-bin/getdoc.cgi?coll=0650&amp;db=man&amp;fname=/usr/share/catman/p_man/cat3/Inventor_c/SoHELPID().z</setting>
  </section>
</XMLConfig>")

#--------------------------------------------------------------------
# Install config files for XIPBuilder
#
install(FILES
  ${XIP_BINARY_DIR}/config/config.xml
  ${XIP_BINARY_DIR}/config/extensions.xml
  ${XIP_BINARY_DIR}/config/favorites.xml
  ${XIP_BINARY_DIR}/config/help.xml
  DESTINATION config)

#--------------------------------------------------------------------
# Testing
#
if(BUILD_TESTING)
set(TESTING_DIR ${XIP_BINARY_DIR}/Testing/Temporary)

foreach(EXAMPLE ${EXAMPLES})
  get_filename_component(SHORT_FILENAME ${EXAMPLE} NAME_WE)

  set(TESTED_SCREENSHOT ${TESTING_DIR}/${SHORT_FILENAME}.png)
  set(DIFFERENCE_IMAGE ${TESTING_DIR}/${SHORT_FILENAME}_diff.png)
  set(FILE_COMPARE_XML ${TESTING_DIR}/${SHORT_FILENAME}.xml)
  set(RENDER_FILE ${TESTING_DIR}/${SHORT_FILENAME}.txt)

  set(EXPECTED_SCREENSHOT
	 ${XIP_SOURCE_DIR}/test/expected/${SHORT_FILENAME}.png)
  set(EXPECTED_ACCURACY
	  ${XIP_SOURCE_DIR}/test/expected/${SHORT_FILENAME}.txt)

  if(EXISTS ${EXPECTED_SCREENSHOT})
    file(WRITE ${RENDER_FILE}
	    "render(256,256,\"" ${TESTED_SCREENSHOT} "\");")
    add_test(${SHORT_FILENAME}Screenshot
      ${XIP_BUILDER_RELEASE} ${EXAMPLE} /config=${XIP_BINARY_DIR}/config
      /cmd=${RENDER_FILE})
#ADD_TEST(${SHORT_FILENAME}FileCompare
#${EXECUTABLE_OUTPUT_PATH}/fileCompare ${TESTED_SCREENSHOT}
#${EXPECTED_SCREENSHOT} ${FILE_COMPARE_XML})
#ADD_TEST(${SHORT_FILENAME}SmartFileCompare
#${EXECUTABLE_OUTPUT_PATH}/smartFileCompare ${TESTED_SCREENSHOT}
#${EXPECTED_SCREENSHOT})

    add_test(${SHORT_FILENAME}ColorUtils
      ${EXECUTABLE_OUTPUT_PATH}/color-utils ${TESTED_SCREENSHOT}
      ${EXPECTED_SCREENSHOT} ${DIFFERENCE_IMAGE} ${FILE_COMPARE_XML}
      ${EXPECTED_ACCURACY})
  endif(EXISTS ${EXPECTED_SCREENSHOT})

endforeach(EXAMPLE ${EXAMPLES})

    #add_test(${SHORT_FILENAME}Dummy
    #  ${EXECUTABLE_OUTPUT_PATH}/dummy ${TESTED_SCREENSHOT}
    #  -T ${XIP_BINARY_DIR}/Testing/Temporary
    #  -V ${EXPECTED_SCREENSHOT})

endif(BUILD_TESTING)
