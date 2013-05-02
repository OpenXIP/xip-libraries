
Project(ticpp)

add_definitions(-D"TIXML_USE_TICPP")

set(SOURCES
	ticpp.cpp
	tinystr.cpp
	tinyxml.cpp
	tinyxmlerror.cpp
	tinyxmlparser.cpp
)

add_library(ticpp STATIC ${SOURCES})
