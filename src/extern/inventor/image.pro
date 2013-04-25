TEMPLATE = lib

TARGET = image

CONFIG += staticlib exceptions thread

DESTDIR    = libimage
DLLDESTDIR = libimage

!win32::OBJECTS_DIR = obj

win32::DEFINES += WIN32 INVENTOR_EXPORTS __SGIOIV_BUILD_DLL
win32::DEFINES -= UNICODE

debug::DEFINES += DEBUG

# include settings of required libraries
include( $(MEVIS_THIRDPARTY_LIB)/make/thirdpartyPackages.pro )

# libimage
HEADERS += \
    libimage/image.h

SOURCES += \
    libimage/close.c \
    libimage/filbuf.c \
    libimage/flsbuf.c \
    libimage/name.c \
    libimage/open.c \
    libimage/pix.c \
    libimage/rdwr.c \
    libimage/rle.c \
    libimage/row.c
