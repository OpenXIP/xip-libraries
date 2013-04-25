IVDEPTH = ..
include $(IVDEPTH)/make/ivcommondefs

ifeq ($(usingWin32), 1)
ARCHIVE = libimage.lib
else
ARCHIVE = libimage.a
endif

CFILES = \
	close.c \
	filbuf.c \
	flsbuf.c \
	name.c \
	open.c \
	pix.c \
	rdwr.c \
	rle.c \
	row.c

all install: all_ivbin

include $(IVCOMMONRULES)
