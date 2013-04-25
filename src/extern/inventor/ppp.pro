TEMPLATE = app

TARGET = ppp

DESTDIR = tools/ppp

macx::CONFIG -= app_bundle

!win32::OBJECTS_DIR = obj

QMAKE_EXT_CPP += .c++

# postprocessing flags
MSVC_KEEP_DESTDIR = 1

win32::QMAKE_CXXFLAGS += /TP

win32::DEFINES += WIN32 INVENTOR_EXPORTS __SGIOIV_BUILD_DLL
win32::DEFINES -= UNICODE

unix:!macx:QMAKE_CFLAGS += -idirafter lib/mevis/include
unix:!macx:QMAKE_CXXFLAGS += -idirafter lib/mevis/include
unix::DEFINES += NDEBUG

# include settings of required libraries
include( $(MEVIS_THIRDPARTY_LIB)/make/thirdpartyPackages.pro )

# make sure there is no debug postfix on the target
TARGET = ppp

INCLUDEPATH += \
    lib/database/include \
    lib/interaction/include \
    lib/nodekits/include \
    lib/mevis/include

win32::CONFIG += console

SOURCES += \
    tools/ppp/ppp.c++
