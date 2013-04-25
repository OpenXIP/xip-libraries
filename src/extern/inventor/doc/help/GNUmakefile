IVDEPTH = ../..
include $(IVDEPTH)/make/ivcommondefs

all:

ifeq ($(usingWin32), 1)
install:

else
install:
	mkdir -p $(IVHELPDIR)/Inventor
	for h in *.help; do $(INSTALL) -m 644 $$h $(IVHELPDIR)/Inventor; done
endif

include $(IVCOMMONRULES)
