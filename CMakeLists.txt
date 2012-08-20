CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(renode)

INCLUDE(CheckIncludeFiles)
INCLUDE(CheckFunctionExists)
INCLUDE(CheckSymbolExists)

IF(WIN32)
	CHECK_SYMBOL_EXISTS(IPPROTO_SCTP "winsock2.h" RENODE_HAVE_SCTP)
	# See thread http://www.mail-archive.com/cmake@cmake.org/msg13547.html
	# This is likely going to be the same problem and will require a custom link test
	CHECK_FUNCTION_EXISTS(CreateIoCompletionPort RENODE_HAVE_W32IOCP)
ELSE()
	CHECK_INCLUDE_FILES(sys/epoll.h RENODE_HAVE_EPOLL)
	IF(RENODE_HAVE_EPOLL)
		# We want to ignore implementations prior to kernel 2.6.27 as
		# they're a bit buggy and the API wasn't fully established
		CHECK_FUNCTION_EXISTS(epoll_create1 RENODE_HAVE_EPOLL)	
	ENDIF()
	CHECK_INCLUDE_FILES(netinet/sctp.h RENODE_HAVE_SCTP)
ENDIF()



IF(NOT RENODE_HAVE_EPOLL)
	SET(RENODE_HAVE_EPOLL 0)
ENDIF()
IF(NOT RENODE_HAVE_KPOLL)
	SET(RENODE_HAVE_KPOLL 0)
ENDIF()
IF(NOT RENODE_HAVE_W32IOCP)
	SET(RENODE_HAVE_W32IOCP 0)
ENDIF()

IF(NOT RENODE_HAVE_SCTP)
	IF(CMAKE_SYSTEM_NAME MATCHES "Linux")
		MESSAGE("!! If you would like to build SCTP support in, you must install lksctp-tools-devel")
		MESSAGE("!! yum: yum -y install lksctp-tools-devel")
		MESSAGE("!! apt: apt-get -y install lksctp-tools-devel")
		MESSAGE("!! yast: yast -i lksctp-tools-devel")
	ENDIF()
	SET(RENODE_HAVE_SCTP 0)
ENDIF()

IF(NOT RENODE_BUILD_TYPE)
	SET(RENODE_BUILD_TYPE "Release")
ENDIF()

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
#TODO: Dynamically change to lib64 as needed... or maybe just on target
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
SET(ARCHIVE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

SET(CMAKE_CXX_FLAGS "-std=c++11")
IF (RENODE_BUILD_TYPE MATCHES "Debug")
	SET(CMAKE_CXX_FLAGS_DEBUG "-O0 -Wall -ggdb")
ELSEIF (RENODE_BUILD_TYPE MATCHES "RelWithDebInfo")
	SET(CMAKE_CXX_FLAGS_DEBUG "-O3 -ggdb")
ELSEIF (RENODE_BUILD_TYPE MATCHES "MinSizeRel")
	SET(CMAKE_CXX_FLAGS_DEBUG "-Os")
ELSE()
	SET(RENODE_BUILD_TYPE "Release")
	SET(CMAKE_CXX_FLAGS_RELEASE "-O3")
ENDIF()
SET(CMAKE_BUILD_TYPE ${RENODE_BUILD_TYPE})


MESSAGE("** Configured for ${CMAKE_BUILD_TYPE}")

ADD_SUBDIRECTORY(src)

