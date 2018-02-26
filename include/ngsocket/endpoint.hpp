#ifndef DEF_NGSOCKET_ENDPOINT_HPP
#define DEF_NGSOCKET_ENDPOINT_HPP

#include "address.hpp"

#include <cstdint>
#include <string>

namespace ng {

struct ipv4_endpoint {
	uint16_t port;
	ipv4_address address;

	ipv4_endpoint();
	ipv4_endpoint(const std::string& address, uint16_t port);
	ipv4_endpoint(ipv4_address address, uint16_t port);

	bool operator==(const ipv4_endpoint& other) const;
	bool operator!=(const ipv4_endpoint& other) const;

	static const ipv4_endpoint NONE;
};

}

#endif /* ifndef DEF_NGSOCKET_ENDPOINT_HPP */
