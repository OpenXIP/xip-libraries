IVDEPTH = ../../..
include $(IVDEPTH)/make/ivcommondefs

HDRSUBDIR = ../

ifeq ($(usingWin32), 1)
HEADERS += \
	SoWinEnterScope.h \
	SoWinLeaveScope.h \
	inttypes.h
endif

HEADERS_SUBDIRS = Inventor

all:

install: install_ivheaders
	$(HEADERS_SUBDIRS_MAKERULE)

COMMONPREF = xxx
$(COMMONTARGS): %: $(COMMONPREF)%
	$(HEADERS_SUBDIRS_MAKERULE)

include $(IVCOMMONRULES)
