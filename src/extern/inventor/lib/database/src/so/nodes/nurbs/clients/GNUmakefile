IVDEPTH = ../../../../../../..
include $(IVDEPTH)/make/ivcommondefs

LCXXINCS += -I../head
LCXXDEFS += -DLIBRARYBUILD
LCXXDEFS += -D_WINDOWS

CXXFILES = nurbsClient.c++

all install: $(OBJECTS)

include $(IVCOMMONRULES)
