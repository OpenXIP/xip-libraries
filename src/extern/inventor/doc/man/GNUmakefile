IVDEPTH = ../..
include $(IVDEPTH)/make/ivcommondefs

ifeq ($(usingWin32), 1)
SUBDIRS = tools ivman man3
else
SUBDIRS = tools ivman man1 man3
endif

all install:
	$(SUBDIRS_MAKERULE)

COMMONPREF = xxx
$(COMMONTARGS): %: $(COMMONPREF)%
	$(SUBDIRS_MAKERULE)

include $(IVCOMMONRULES)
