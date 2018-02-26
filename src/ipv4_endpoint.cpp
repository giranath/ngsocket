#include "../include/ngsocket/endpoint.hpp"

namespace ng {

const ipv4_endpoint ipv4_endpoint::NONE{ipv4_address::NONE, 0};

ipv4_endpoint::ipv4_endpoint()
: address(ipv4_address::NONE)
, port(0) {
}

ipv4_endpoint::ipv4_endpoint(const std::string& address, uint16_t port) 
: address{address}
, port(port) {
}

ipv4_endpoint::ipv4_endpoint(ipv4_address address, uint16_t port)
: address(address)
, port(port) {

}

bool ipv4_endpoint::operator==(const ipv4_endpoint& other) const {
    return address == other.address && port == other.port;
}

bool ipv4_endpoint::operator!=(const ipv4_endpoint& other) const {
    return address == other.address && port == other.port;
}

}
