# ---------------- ivfix profile -------------------
# Last changed by $Author: tboskamp $
# $Id: eatDicom.pro 52964 2007-03-27 12:24:14Z tboskamp $
# $Source$
# --------------------------------------------------

TEMPLATE = app

TARGET = ivfix

DESTDIR = $(MEVIS_THIRDPARTY_LIB)/bin

MSVC_KEEP_DESTDIR = 1

# set high warn level (warn 4 on MSCV)
# WARN = HIGH

# add used packages here (see mevisPackages.pro for packages):
CONFIG += console inventor
macx:CONFIG -= app_bundle

QMAKE_EXT_CPP += .c++

win32::QMAKE_CXXFLAGS += /TP

win32::DEFINES += WIN32
win32::DEFINES -= UNICODE

unix:!macx:QMAKE_CFLAGS   += -idirafter $(MEVIS_THIRDPARTY_LIB)/Inventor/inventor/lib/mevis/include
unix:!macx:QMAKE_CXXFLAGS += -idirafter $(MEVIS_THIRDPARTY_LIB)/Inventor/inventor/lib/mevis/include

# include settings of required libraries
include( $(MEVIS_THIRDPARTY_LIB)/make/thirdpartyPackages.pro )

HEADERS += \
  IfAssert.h \
  IfBuilder.h \
  IfCollector.h \
  IfCondenser.h \
  IfFixer.h \
  IfFlattener.h \
  IfHasher.h \
  IfHolder.h \
  IfMerger.h \
  IfReplacer.h \
  IfReporter.h \
  IfShape.h \
  IfShapeList.h \
  IfSorter.h \
  IfStripper.h \
  IfTypes.h \
  IfWeeder.h

SOURCES += \
  IfBuilder.c++ \
  IfCollector.c++ \
  IfCondenser.c++ \
  IfFixer.c++ \
  IfFlattener.c++ \
  IfHasher.c++ \
  IfHolder.c++ \
  IfMerger.c++ \
  IfReplacer.c++ \
  IfReporter.c++ \
  IfShape.c++ \
  IfShapeList.c++ \
  IfSorter.c++ \
  IfStripper.c++ \
  IfTypes.c++ \
  IfWeeder.c++ \
  ivfix.c++
