SET(INCL
	Renode.h
	Renode
)
#FILE(COPY ${INCL} DESTINATION ${CMAKE_BINARY_DIR}/include FILES_MATCHING PATTERN "*.h")
CONFIGURE_FILE(Renode/Definitions.h.cmake ${CMAKE_BINARY_DIR}/include/Renode/Definitions.h)

