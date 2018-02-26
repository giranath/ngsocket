#ifndef DEF_NGSOCKET_PLATFORM_HPP
#define DEF_NGSOCKET_PLATFORM_HPP

#include "endpoint.hpp"

#if defined(NG_WINDOWS)
#include <winsock2.h>
#endif

#include <cstdint>

namespace ng {

#if defined(NG_WINDOWS)
	using socket_handle = SOCKET;
	//const socket_handle INVALID_SOCKET = 0;
#else
	using socket_handle = int;
	const socket_handle INVALID_SOCKET = -1;
#endif

socket_handle socket_create();
socket_handle socket_accept(socket_handle hdl, ipv4_endpoint& out_address);
void socket_connect(socket_handle hdl, ipv4_endpoint address);
void socket_bind(socket_handle hdl, ipv4_endpoint endpoint);
void socket_listen(socket_handle hdl);
void socket_listen(socket_handle hdl, int32_t backlog);
void socket_close(socket_handle hdl);

int64_t socket_receive(socket_handle hdl, uint8_t* dest_buffer, uint64_t buffer_len);
int64_t socket_send(socket_handle hdl, const uint8_t* buffer, uint64_t len);

void socket_set_option(socket_handle hdl, int optname, const void* value, std::size_t len);
}

#endif /* ifndef DEF_NGSOCKET_PLATFORM_HPP */
