SET(SRC
	Globals.cpp
	Poller.cpp
)

ADD_LIBRARY(renode SHARED ${SRC})
ADD_DEPENDENCIES(renode ${CMAKE_BINARY_DIR}/include/Renode/Definitions.h)

