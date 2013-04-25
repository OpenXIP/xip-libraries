IVDEPTH = ../../../..
include $(IVDEPTH)/make/ivcommondefs

HDRSUBDIR =

HEADERS = \
	SoCatch.h \
	SoInventor.h \
	SoMeVis.h \
	SoTrace.h

HEADERS_SUBDIRS = \
	elements \
	fields \
	nodes \
	system

all:

install: install_ivheaders
	$(HEADERS_SUBDIRS_MAKERULE)

COMMONPREF = xxx
$(COMMONTARGS): %: $(COMMONPREF)%
	$(HEADERS_SUBDIRS_MAKERULE)

include $(IVCOMMONRULES)
