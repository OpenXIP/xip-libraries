IVDEPTH = ../..
include $(IVDEPTH)/make/ivcommondefs

PROGRAM = ppp

CXXFILES = ppp.c++


ifeq ($(usingWin32), 1)
# LLDOPTS += /FORCE:UNRESOLVED
else
LLDLIBS = -lm
endif


all install: $(PROGRAM)

include $(IVCOMMONRULES)
