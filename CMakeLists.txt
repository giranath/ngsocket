cmake_minimum_required(VERSION 3.9)

project(ngsocket VERSION 1.0.0 DESCRIPTION "A C++ cross-platform socket library")

set(CMAKE_CXX_STANDARD 14)

configure_file("${CMAKE_SOURCE_DIR}/ngsocket-config-version.cmake.in"
		"${CMAKE_SOURCE_DIR}/ngsocket-config-version.cmake"
		@ONLY)

if(WIN32)
	add_definitions(-DNG_WINDOWS)
	set(PLATFORM_LIBRARIES wsock32 ws2_32)
else()
	set(PLATFORM_LIBRARIES)
endif()

add_library(ngsocket
	src/platform.cpp
	src/socket_service.cpp
	src/ipv4_address.cpp
	src/ipv4_endpoint.cpp
	src/address_info.cpp
	src/resolver_iterator.cpp
	src/socket.cpp
	src/tcp_socket.cpp
	src/tcp_listener.cpp
	src/socket_acceptor.cpp
	)
set_target_properties(ngsocket PROPERTIES VERSION ${PROJECT_VERSION}
		                                  SOVERSION ${PROJECT_VERSION})
install(TARGETS ngsocket
		EXPORT ngsocket-targets
		RUNTIME DESTINATION bin
		COMPONENT libraries
		LIBRARY DESTINATION lib/ngsocket
		COMPONENT libraries
		ARCHIVE DESTINATION lib/ngsocket
		COMPONENT libraries)
install(DIRECTORY include/
		DESTINATION include
		COMPONENT headers)
install(EXPORT ngsocket-targets
		DESTINATION lib/ngsocket
		COMPONENT cmake)
install(FILES ngsocket-config.cmake ngsocket-config-version.cmake.in
		DESTINATION lib/ngsocket
		COMPONENT cmake)