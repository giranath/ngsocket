#include "../include/ngsocket/socket.hpp"

// TODO: Move to platform
#if defined(NG_WINDOWS)
#include <WinSock2.h>
#endif

#include <system_error>

namespace ng {

socket_service::socket_service() {
#if defined(NG_WINDOWS)
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	/* Use the MAKEWORD(lowbyte, highbyte) macro declared in Windef.h */
	wVersionRequested = MAKEWORD(2, 2);

	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) {
		throw std::system_error(WSAGetLastError(), std::system_category(), "can't intialize service");
	}
#endif
}

socket_service::~socket_service() {
#if defined(NG_WINDOWS)
	WSACleanup();
#endif
}

}