project(basicviewer)

cmake_minimum_required(VERSION 2.6)

# Disable deprecation warnings for standard C functions.
if(CMAKE_COMPILER_2005)
  add_definitions(-D_CRT_SECURE_NO_DEPRECATE -D_CRT_NONSTDC_NO_DEPRECATE)
endif(CMAKE_COMPILER_2005)

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  add_definitions(-DDARWIN)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

find_package(OpenGL REQUIRED)

#--------------------------------------------------------------------
# Set preprocessor definition for SbSystem.h to indicate whether 
# to use the debug postfix
#
if(DEBUG_POSTFIX)
	add_definitions(-D_DEBUG_POSTFIX)
endif(DEBUG_POSTFIX)

##############
# Qt SECTION #
##############

find_package(Qt4 REQUIRED)

set(QT_DONT_USE_QTCORE FALSE)
set(QT_DONT_USE_QTGUI FALSE)
set(QT_USE_QT3SUPPORT FALSE)
set(QT_USE_QTASSISTANT FALSE)
set(QT_USE_QTDESIGNER FALSE)
set(QT_USE_QTMOTIF FALSE)
set(QT_USE_QTMAIN FALSE)
set(QT_USE_QTNETWORK FALSE)
set(QT_USE_QTNSPLUGIN FALSE)
set(QT_USE_QTOPENGL TRUE)
set(QT_USE_QTSQL FALSE)
set(QT_USE_QTXML TRUE)
set(QT_USE_QTSVG FALSE)
set(QT_USE_QTTEST FALSE)
set(QT_USE_QTUITOOLS FALSE)
set(QT_USE_QTDBUS FALSE)
set(QT_USE_QTSCRIPT FALSE)
set(QT_USE_QTASSISTANTCLIENT FALSE)
set(QT_USE_QTHELP FALSE)
set(QT_USE_QTWEBKIT FALSE)
set(QT_USE_QTXMLPATTERNS FALSE)
set(QT_USE_PHONON FALSE)
	
include(${QT_USE_FILE})

include_directories(
	${QT_INCLUDE_DIR}
	include
	${XIP_SOURCE_DIR}/src/database/core
)

link_directories(
	${QT_LIBRARY_DIR}
	)

add_definitions(
	-DUNICODE
	-DQT_SVG_LIB
	-DQT_XML_LIB
	-DQT_CORE_LIB
	-DQT_OPENGL_LIB
	-DQT_GUI_LIB
	-DQT_DLL
	-DQT_LARGEFILE_SUPPORT
	-DQT_THREAD_SUPPORT)

set(UI_FILES
    src/ui/OuterForm.ui
    src/ui/MainForm.ui
    src/ui/PresetMixerForm.ui
    src/ui/DicomForm.ui)

source_group("Form Files" FILES ${UI_FILES})

qt4_wrap_ui(XIP_UI_HDRS ${UI_FILES})

set(HEADER_FILES
    src/definitions.h
    src/IvFileLoader.h
    src/QExtLibraryLoaderStandalone.h
    src/QXipIvGLWidget.h
    src/QXipIvWidget.h
    src/OuterForm.h
    src/MainForm.h
    src/SoRefXipLut.h
    src/SoRefXipExaminer.h
    src/SoRefXipMprExaminer.h
    src/SoRefXipWindowLevelManip.h
    src/SoRefXipViewportGroup.h
    src/SoRefXipLoadDicom.h
    src/SoRefXipSlicer.h
    src/SoRefXipTexture.h
    src/SoRefXipGetDicomString.h
    src/ColorPickButton.h
    src/ViewerCore.h
    src/SidebarButton.h
    src/SoSFEnumExtended.h
    src/PresetButton.h
    src/XipPreset.h
    src/PresetMixerForm.h
    src/PresetSlot.h
    src/DicomForm.h)

source_group("Header Files" FILES ${HEADER_FILES})

set(SOURCE_FILES
    src/IvFileLoader.cpp
    src/main.cpp
    src/QExtLibraryLoaderStandalone.cpp
    src/QXipIvGLWidget.cpp
    src/QXipIvWidget.cpp
    src/OuterForm.cpp
    src/MainForm.cpp
    src/SoRefXipLut.cpp
    src/SoRefXipExaminer.cpp
    src/SoRefXipMprExaminer.cpp
    src/SoRefXipWindowLevelManip.cpp
    src/SoRefXipViewportGroup.cpp
    src/SoRefXipLoadDicom.cpp
    src/SoRefXipSlicer.cpp
    src/SoRefXipTexture.cpp
    src/SoRefXipGetDicomString.cpp
    src/ColorPickButton.cpp
    src/ViewerCore.cpp
    src/SidebarButton.cpp
    src/PresetButton.cpp
    src/PresetMixerForm.cpp
    src/PresetSlot.cpp
    src/DicomForm.cpp)

set(XIP_MOC_HDRS
    src/QXipIvGLWidget.h
    src/QXipIvWidget.h
    src/OuterForm.h
    src/MainForm.h
    src/ColorPickButton.h
    src/SidebarButton.h
    src/PresetButton.h
    src/PresetMixerForm.h
    src/PresetSlot.h
    src/DicomForm.h)

qt4_wrap_cpp(XIP_MOC_FILES ${XIP_MOC_HDRS})

qt4_add_resources(XIP_QT_RCCS src/qrc/basicviewer.qrc)

source_group("MOC Files" FILES ${XIP_MOC_FILES})

# Define the include directories
#
include_directories(${PROJECT_BINARY_DIR})

################
# APPLICATIONS #
################

# Creation of a Win32 application
if(WIN32)
  add_executable(basicviewer WIN32
	${XIP_UI_HDRS} 
	${SOURCE_FILES} 
	${HEADER_FILES}
    ${XIP_MOC_FILES} 
    ${XIP_QT_RCCS}
    src/rc/basicviewer.rc)
endif(WIN32)

###########
# LINKING #
###########

if(WIN32)
  target_link_libraries(basicviewer
    ${XIP_LIBRARIES}
    optimized qtmain
		debug qtmaind
    optimized QtGui4
		debug QtGuid4
    optimized QtOpenGL4
		debug QtOpenGLd4
    optimized QtCore4
		debug QtCored4
    optimized QtXml4
        debug QtXmld4
)
endif(WIN32)

install(TARGETS basicviewer
  RUNTIME DESTINATION bin/release CONFIGURATIONS Release
  ARCHIVE DESTINATION lib/release CONFIGURATIONS Release
  LIBRARY DESTINATION lib/release CONFIGURATIONS Release
  BUNDLE  DESTINATION lib/release CONFIGURATIONS Release)
  
  install(TARGETS basicviewer
  RUNTIME DESTINATION bin/debug CONFIGURATIONS Debug
  ARCHIVE DESTINATION lib/debug CONFIGURATIONS Debug
  LIBRARY DESTINATION lib/debug CONFIGURATIONS Debug
  BUNDLE  DESTINATION lib/debug CONFIGURATIONS Debug)
