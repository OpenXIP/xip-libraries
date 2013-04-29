# Sylvain Jaume 2007

project(Xip)
cmake_minimum_required(VERSION 2.6)

#--------------------------------------------------------------------
# Testing configuration.
#
option(BUILD_TESTING "Create the testing framework" OFF)
mark_as_advanced(BUILD_TESTING)

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
# Set up CPack support, to be able to distribute Xip binary packages.
# It will be particulary useful to distributed prebuilt Xip witk extended
# languages support enable.
#
include(InstallRequiredSystemLibraries)
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "eXtensible Imaging Platorm")
set(CPACK_PACKAGE_VENDOR "Siemens Corporate Research")
set(CPACK_PACKAGE_VERSION_MAJOR "${Xip_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${Xip_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${Xip_VERSION_PATCH}")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "xip-${Xip_VERSION_STRING}")
set(CPACK_RESOURCE_FILE_LICENSE ${Xip_SOURCE_DIR}/LICENSE.txt)
set(CPACK_PACKAGE_DESCRIPTION_FILE ${CMAKE_CURRENT_SOURCE_DIR}/README.txt)
set(CPACK_SOURCE_PACKAGE_FILE_NAME "xip-${Xip_VERSION_STRING}-src"
  CACHE INTERNAL "compressed file containing all source code")
if(WIN32)
  set(CPACK_GENERATOR NSIS)
  set(CPACK_SOURCE_GENERATOR NSIS)
else(WIN32)
  set(CPACK_GENERATOR TZ)
  set(CPACK_SOURCE_GENERATOR TZ)
endif(WIN32)

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
option(HAS_DCMTK "Compile with the DICOM library DCMTK" ON)
option(HAS_VTK   "Compile with the Visualization Toolkit" ON)

if(WIN32)
  option(HAS_ITK "Compile with the Insight Toolkit" ON)
else(WIN32)
  option(HAS_ITK "Compile with the Insight Toolkit" OFF)
endif(WIN32)

mark_as_advanced(CMAKE_INSTALL_PREFIX)

#--------------------------------------------------------------------
# DCMTK variables
#
if(UNIX AND HAS_DCMTK)
  set(DCMTK_config_INCLUDE_DIR /usr/local/dicom/include/dcmtk/config)
  set(DCMTK_dcmdata_INCLUDE_DIR /usr/local/dicom/include/dcmtk/dcmdata)
  set(DCMTK_dcmimgle_INCLUDE_DIR /usr/local/dicom/include/dcmtk/dcmimgle)
  set(DCMTK_ofstd_INCLUDE_DIR /usr/local/dicom/include/dcmtk/ofstd)
  find_library(DCMTK_dcmdata_LIBRARY dcmdata /usr/local/dicom/lib)
  find_library(DCMTK_dcmimgle_LIBRARY dcmimgle /usr/local/dicom/lib)
  find_library(DCMTK_dcmnet_LIBRARY dcmnet /usr/local/dicom/lib)
  find_library(DCMTK_imagedb_LIBRARY dcmimage /usr/local/dicom/lib)
  find_library(DCMTK_ofstd_LIBRARY ofstd /usr/local/dicom/lib)
endif(UNIX AND HAS_DCMTK)

#--------------------------------------------------------------------
# VTK variables
#
mark_as_advanced(VTK_GLEXT_FILE)
mark_as_advanced(VTK_GLXEXT_FILE)
mark_as_advanced(VTK_WGLEXT_FILE)

#--------------------------------------------------------------------
# Options to build OpenInventor.
#
option(BUILD_INVENTOR "Build the Open Inventor library" ON)

#--------------------------------------------------------------------
# Generate the Doxygen documentation
#
option(BUILD_DOCUMENTATION "Generate the Doxygen documentation" OFF)
mark_as_advanced(BUILD_DOCUMENTATION)
if(BUILD_DOCUMENTATION)
  find_package(Doxygen)
endif(BUILD_DOCUMENTATION)

#--------------------------------------------------------------------
# Find xipext directory
#
if(WIN32)
  if(HAS_DCMTK OR HAS_ITK OR HAS_VTK)
    find_path(XIPEXT inventor/bin/xipinv240.dll ${Xip_SOURCE_DIR}/../xipext
      "Directory where Xip external libraries are installed")
  endif(HAS_DCMTK OR HAS_ITK OR HAS_VTK)
endif(WIN32)

if(NOT BUILD_INVENTOR)
  find_path(OIV_PATH bin/xipinv240.dll ${XIPEXT}/inventor
    "Directory where Open Inventor is installed")
endif(NOT BUILD_INVENTOR)

if(WIN32 AND HAS_ITK)
  find_path(ITK_PATH include/InsightToolkit/itkConfigure.h ${XIPEXT}/itk
    "Directory where ITK is installed")
endif(WIN32 AND HAS_ITK)

if(WIN32 AND HAS_VTK)
  find_path(VTK_PATH bin/vtkCommon.dll ${XIPEXT}/vtk
    "Directory where VTK is installed")
endif(WIN32 AND HAS_VTK)

#--------------------------------------------------------------------
# Output directories.
#
if(NOT EXECUTABLE_OUTPUT_PATH)
  set(EXECUTABLE_OUTPUT_PATH ${Xip_BINARY_DIR}/bin CACHE PATH
    "Single output directory for building all executables.")
endif(NOT EXECUTABLE_OUTPUT_PATH)

if(NOT LIBRARY_OUTPUT_PATH)
  set(LIBRARY_OUTPUT_PATH ${Xip_BINARY_DIR}/bin CACHE PATH
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
if(UNIX)
  add_definitions(-Wno-deprecated)
endif(UNIX)

if(CMAKE_COMPILER_2005)
  add_definitions(-D_CRT_SECURE_NO_DEPRECATE -D_CRT_NONSTDC_NO_DEPRECATE)
endif(CMAKE_COMPILER_2005)

#--------------------------------------------------------------------
# Find the xipbuilder executable, required for testing.
#
if(BUILD_TESTING)
  find_file(XIP_BUILDER_DEBUG xipbuilder.exe
    "C:/Program Files/Xip/Debug")
  find_file(XIP_BUILDER_RELEASE xipbuilder.exe
    "C:/Program Files/Xip/release")
  mark_as_advanced(XIP_BUILDER_DEBUG XIP_BUILDER_RELEASE)
endif(BUILD_TESTING)

#--------------------------------------------------------------------
# Include directories.
#
include_directories(include)

if(OIV_PATH)
  include_directories(${OIV_PATH}/include)
endif(OIV_PATH)

#--------------------------------------------------------------------
# Link directories.
#
link_directories(
  ${LIBRARY_OUTPUT_PATH}
  .) # Put "." in the rpath of all Xip shared libraries.

if(XIPEXT)
  link_directories(${XIPEXT}/inventor/lib)
endif(XIPEXT)

#--------------------------------------------------------------------
# Enter subdirectories
#
add_subdirectory(src)
add_subdirectory(test)

#--------------------------------------------------------------------
# Copy xipbuilder to the install directory
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
# Install libraries and header files.
#
file(GLOB_RECURSE FILES_IN_DIRECTORY include *.h)

foreach(HEADER_FILE ${FILES_IN_DIRECTORY})
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
      string(REGEX REPLACE
	"${Xip_SOURCE_DIR}/src/extern/inventor/lib/mevis/"
        "" INSTALL_PATH ${HEADER_FILE})
      get_filename_component(INSTALL_PATH ${INSTALL_PATH} PATH)
      if(HEADER_FILE MATCHES "[^src]")
        install(FILES ${HEADER_FILE} DESTINATION ${INSTALL_PATH})
      endif(HEADER_FILE MATCHES "[^src]")
    endif(${HEADER_FILE} MATCHES
      "${Xip_SOURCE_DIR}/src/extern/inventor/lib/mevis/include")

  endif(${HEADER_FILE} MATCHES "h$")
endforeach(HEADER_FILE ${FILES_IN_DIRECTORY})

#--------------------------------------------------------------------
# Rad examples
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
"examples/vtk/Converters/XipImageToVtk.rad"
"examples/vtk/DICOM/VolumeRendering.rad"
"examples/vtk/Tutorial/ConeSource.rad"
"examples/vtk/VisualizationAlgorithms/ClipCow.rad"
"examples/vtk/VisualizationAlgorithms/officeTube.rad"
"examples/vtk/VolumeRendering/PseudoVolumeRendering.rad"
"examples/vtk/VolumeRendering/SimpleRayCast.rad"
"examples/vtk/VolumeRendering/SimpleTextureMap2D.rad"
"examples/vtk/VolumeRendering/VolumeRendering.rad")

#--------------------------------------------------------------------
# Xip examples
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
  doc/XipOverview.ppt
  doc/XipStarterGuide.doc
  doc/xip_logo.png
  doc/xipbuilder_logo.png
  DESTINATION doc)

#--------------------------------------------------------------------
# Xip Library
#
#get_target_property(Xip_LIBRARY Xip LOCATION)

# add the install path to the library name
#set(Xip_LIBRARY
#  ${CMAKE_INSTALL_PREFIX}/lib/${Xip_INSTALL_LIBRARY})

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

foreach(EXAMPLE ${EXAMPLES})
  get_filename_component(SHORT_FILENAME ${EXAMPLE} NAME_WE)

  set(TESTED_SCREENSHOT ${TESTING_DIR}/${SHORT_FILENAME}.png)
  set(DIFFERENCE_IMAGE ${TESTING_DIR}/${SHORT_FILENAME}_diff.png)
  set(FILE_COMPARE_XML ${TESTING_DIR}/${SHORT_FILENAME}.xml)
  set(RENDER_FILE ${TESTING_DIR}/${SHORT_FILENAME}.txt)

  set(EXPECTED_SCREENSHOT
	 ${Xip_SOURCE_DIR}/test/expected/${SHORT_FILENAME}.png)
  set(EXPECTED_ACCURACY
	  ${Xip_SOURCE_DIR}/test/expected/${SHORT_FILENAME}.txt)

  if(EXISTS ${EXPECTED_SCREENSHOT})
    file(WRITE ${RENDER_FILE}
	    "render(256,256,\"" ${TESTED_SCREENSHOT} "\");")
    add_test(${SHORT_FILENAME}Screenshot
      ${XIP_BUILDER_RELEASE} ${EXAMPLE} /config=${Xip_BINARY_DIR}/config
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
    #  -T ${Xip_BINARY_DIR}/Testing/Temporary
    #  -V ${EXPECTED_SCREENSHOT})

endif(BUILD_TESTING)
