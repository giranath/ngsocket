#include "../include/ngsocket/address.hpp"

#include <cstring>

#if defined(NG_WINDOWS)
#include <WinSock2.h>
#else
#include <arpa/inet.h>
#endif

namespace ng {

namespace {
uint32_t resolve(const std::string& str) {
	uint32_t address = INADDR_NONE;

	if(str == "255.255.255.255") {
		address = INADDR_BROADCAST;
	}
	else if(str == "0.0.0.0") {
		address = INADDR_ANY;
	}
	else {
		address  = inet_addr(str.c_str());
	}

	return address;
}
}

ipv4_address::ipv4_address()
: value{INADDR_NONE} {
}

ipv4_address::ipv4_address(const std::string& str)
: value{resolve(str)} {
}

ipv4_address::ipv4_address(uint8_t a, uint8_t b, uint8_t c, uint8_t d)
: value{htonl((a << 24) | (b << 16) | (c << 8) | d)}{
}

ipv4_address::ipv4_address(uint32_t raw)
: value{htonl(raw)} {
}

std::string ipv4_address::to_string() const {
	in_addr addr;
	addr.s_addr = value;

	return inet_ntoa(addr);
}

uint32_t ipv4_address::to_integer() const {
	return ntohl(value);
}

bool ipv4_address::operator==(const ipv4_address& other) const {
	return value == other.value;
}

bool ipv4_address::operator!=(const ipv4_address& other) const {
	return value != other.value;
}


const ipv4_address ipv4_address::NONE(INADDR_NONE);
const ipv4_address ipv4_address::ANY(INADDR_ANY);
const ipv4_address ipv4_address::LOCALHOST(127, 0, 0, 1);
const ipv4_address ipv4_address::BROADCAST(INADDR_BROADCAST);

}
