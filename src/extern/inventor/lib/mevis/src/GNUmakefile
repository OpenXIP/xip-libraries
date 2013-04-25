IVDEPTH = ../../..
include $(IVDEPTH)/make/ivcommondefs

CXXFILES =  \
	SoCatch.c++ \
	SoMeVis.c++ \
	SoTrace.c++

ifeq ($(usingWin32), 1)
CXXFILES +=  \
	utf8_filesupport_win32.c++
endif

SUBDIRS = elements fields nodes

all install: $(OBJECTS)
	$(SUBDIRS_MAKERULE)

COMMONPREF = xxx
$(COMMONTARGS): %: $(COMMONPREF)%
	$(SUBDIRS_MAKERULE)

include $(IVCOMMONRULES)
