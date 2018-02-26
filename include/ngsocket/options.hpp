#ifndef DEF_NGSOCKET_OPTIONS_HPP
#define DEF_NGSOCKET_OPTIONS_HPP

#include "platform.hpp"

#if defined(NG_WINDOWS)
#include <WinSock2.h>
#else
#include <sys/socket.h>
#endif

namespace ng {

template<typename T>
struct is_option {
	static const bool VALUE = false;
};

namespace option {

struct reuse_address {
	static const int NAME = SO_REUSEADDR;
	int value;

	reuse_address(bool value)
	: value(value) {
	}
};

struct reuse_port {
#if defined(NG_WINDOWS)
	static const int NAME = SO_REUSEADDR;
#else
	static const int NAME = SO_REUSEPORT;
#endif
	int value;

	reuse_port(bool value)
	: value(value) {
	}
};

}

template<>
struct is_option<option::reuse_address> {
	static const bool VALUE = true;
};

template<>
struct is_option<option::reuse_port> {
	static const bool VALUE = true;
};

}


#endif
