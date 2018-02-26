#include "../include/ngsocket/resolver.hpp"

#include <system_error>

#if defined(NG_WINDOWS)
#include <WinSock2.h>
#include <ws2tcpip.h>
#define GET_ERROR WSAGetLastError()
#else
#define GET_ERROR errno
#endif

namespace ng {

address_info::address_info(const std::string& name)
: result(nullptr)
, it(nullptr) {
	if(getaddrinfo(name.c_str(), nullptr, nullptr, &result) != 0) {
		throw std::system_error{GET_ERROR, std::system_category()};
	}
}

address_info::~address_info() {
	freeaddrinfo(result);
}

addrinfo* address_info::next() {
	if(it == nullptr) {
		it = result;
	}
	else {
		it = it->ai_next;
	}

	return it;
}

}
