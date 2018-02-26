#include "../include/ngsocket/platform.hpp"

#include <system_error>
#include <cstring>

#if defined(NG_WINDOWS)
using socklen_handle = int;
#define GET_ERROR WSAGetLastError()
#define CLOSE_SOCKET closesocket
#else
// on Unix
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <unistd.h>
using socklen_handle = socklen_t;
#define GET_ERROR errno
#define CLOSE_SOCKET close
#endif

namespace ng {

socket_handle socket_create() {
	socket_handle hdl = ::socket(AF_INET, SOCK_STREAM, 0);

	if(hdl == -1) {
		throw std::system_error{GET_ERROR, std::system_category(), "socket_create"};
	}

	return hdl;
}

void socket_connect(socket_handle hdl, ipv4_endpoint address) {
	sockaddr_in addr;
	std::memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(address.port);
	addr.sin_addr.s_addr = htonl(address.address.to_integer());

	if(::connect(hdl, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) == INVALID_SOCKET) {
		throw std::system_error{GET_ERROR, std::system_category(), "socket_connect"};
	}
}

socket_handle socket_accept(socket_handle hdl, ipv4_endpoint& out_address) {
	sockaddr_in address;
	socklen_handle len = sizeof(address);

	int fd = ::accept(hdl, reinterpret_cast<sockaddr*>(&address), &len);
	if(fd == INVALID_SOCKET) {
		throw std::system_error{GET_ERROR, std::system_category(), "socket_accept"};
	}

	out_address.port = ntohs(address.sin_port);
	out_address.address = ipv4_address{ntohl(address.sin_addr.s_addr)};

	return fd;
}

void socket_bind(socket_handle hdl, ipv4_endpoint endpoint) {
	sockaddr_in bound_address;
	std::memset(&bound_address, 0, sizeof(bound_address));
	bound_address.sin_family = AF_INET;
	bound_address.sin_port = htons(endpoint.port);
	bound_address.sin_addr.s_addr = htonl(endpoint.address.to_integer());

	if(::bind(hdl, reinterpret_cast<sockaddr*>(&bound_address), sizeof(bound_address)) == -1) {
		throw std::system_error{GET_ERROR, std::system_category(), "socket_bind"};
	}

}

void socket_listen(socket_handle hdl) {
	socket_listen(hdl, SOMAXCONN);
}

void socket_listen(socket_handle hdl, int32_t backlog) {
	if(::listen(hdl, backlog) == -1) {
		throw std::system_error{GET_ERROR, std::system_category(), "socket_listen"};
	}
}

void socket_close(socket_handle hdl) {
	if (::CLOSE_SOCKET(hdl) == -1) {
		throw std::system_error(GET_ERROR, std::system_category(), "socket_close");
	}
}

int64_t socket_receive(socket_handle hdl, uint8_t* dest_buffer, uint64_t buffer_len) {
	auto r = ::recv(hdl, reinterpret_cast<char*>(dest_buffer), buffer_len, 0);

	if(r < 0) {
		throw std::system_error(GET_ERROR, std::system_category(), "socket_receive");
	}

	return static_cast<int64_t>(r);
}

int64_t socket_send(socket_handle hdl, const uint8_t* buffer, uint64_t len) {
	auto s = ::send(hdl, reinterpret_cast<const char*>(buffer), len, 0);

	if(s < 0) {
		throw std::system_error(GET_ERROR, std::system_category(), "socket_receive");
	}

	return static_cast<int64_t>(s);
}

void socket_set_option(socket_handle hdl, int optname, const void* value, std::size_t len) {
	if(::setsockopt(hdl, SOL_SOCKET, optname, reinterpret_cast<const char*>(value), len) < 0) {
		throw std::system_error(GET_ERROR, std::system_category(), "socket_set_option");
	}
}

}
