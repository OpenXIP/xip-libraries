IVDEPTH = ../..
include $(IVDEPTH)/make/ivcommondefs

ifeq ($(usingWin32), 1)
ARCHIVE = libFL.lib
else
ARCHIVE = libFL.a
endif

CFILES = fl.c flclient.c flfreetype.c

FREETYPEINCDIR=../../../freetype-2.2.1/include

ifeq ($(usingWin32), 1)
LCINCS += -I$(FREETYPEINCDIR)

all install: flclient.h all_ivbin

# copy file; cl.exe doesn't recognize file if it's linked in CYGWIN
flclient.h: ../src/flclient.h
	if [ ! -f flclient.h ]; then cp -f ../src/flclient.h .; fi
else
LCINCS += -I/usr/include/freetype2

all install: link all_ivbin

link:
	if [ ! -L flclient.h ]; then ln -s ../src/flclient.h .; fi
endif


include $(IVCOMMONRULES)
