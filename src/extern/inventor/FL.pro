TEMPLATE = lib

TARGET = FL

CONFIG += staticlib exceptions thread
CONFIG += freetype

DESTDIR    = libFL
DLLDESTDIR = libFL

!win32::OBJECTS_DIR = obj

win32::DEFINES += WIN32 INVENTOR_EXPORTS __SGIOIV_BUILD_DLL
win32::DEFINES -= UNICODE
unix::!macx::DEFINES += IVPREFIX="/*_*/"

debug::DEFINES += DEBUG

# include settings of required libraries
include( $(MEVIS_THIRDPARTY_LIB)/make/thirdpartyPackages.pro )

# libFL    
INCLUDEPATH += \
    libFL/ang \
    libFL/src

# libFL    
HEADERS += \
    libFL/ang/fl.h \
    libFL/ang/flendian.h \
    libFL/ang/flfreetype.h \
    libFL/src/flclient.h

SOURCES += \
    libFL/ang/fl.c \
    libFL/ang/flclient.c \
    libFL/ang/flfreetype.c
