IVDEPTH = ../../..
include $(IVDEPTH)/make/ivcommondefs

PROGRAM = ivman

CXXFILES = Main.c++ ClassDef.c++ Man.c++ Reader.c++ Writer.c++ BuildIssues.c++

ifeq ($(usingWin32), 1)
LCXXOPTS += -DINVENTOR_IMPORTS

CXXFILES += XGetopt.c++

ifneq (, $(findstring debug, $(LIBTYPE)))
LLDLIBS = -lInventor_d
else
LLDLIBS = -lInventor
endif

else
LLDLIBS = -lInventor
endif

all install: $(PROGRAM)

include $(IVCOMMONRULES)
