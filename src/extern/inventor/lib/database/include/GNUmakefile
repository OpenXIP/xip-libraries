IVDEPTH = ../../..
include $(IVDEPTH)/make/ivcommondefs

HDRSUBDIR = ../

HEADERS = \
	SoDebug.h \
	SoUnknownEngine.h \
	SoUnknownNode.h

HEADERS_SUBDIRS = Inventor

all:

install: install_ivheaders
	$(HEADERS_SUBDIRS_MAKERULE)

COMMONPREF = xxx
$(COMMONTARGS): %: $(COMMONPREF)%
	$(HEADERS_SUBDIRS_MAKERULE)

include $(IVCOMMONRULES)
