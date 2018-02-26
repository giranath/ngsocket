#include "../include/ngsocket/resolver.hpp"

namespace ng {

ipv4_address convert_address(sockaddr* addr) {
	sockaddr_in* ip4_addr = reinterpret_cast<sockaddr_in*>(addr);

	if(ip4_addr) {
		return ipv4_address{ntohl(ip4_addr->sin_addr.s_addr)};
	}

	return ipv4_address::NONE;
}

resolve_iterator::resolve_iterator(const std::string& address)
: info{std::make_shared<address_info>(address)}
, current(info->next())
, value{ipv4_address::NONE}{
    if(current != nullptr) {
        value = convert_address(current->ai_addr);
    }
}

resolve_iterator::resolve_iterator()
: info(nullptr)
, current(nullptr) {
}

resolve_iterator& resolve_iterator::operator++() {
	if(info) {
		current = info->next();

        if(current != nullptr) {
            value = convert_address(current->ai_addr);
        }
        else {
            value = ipv4_address::NONE;
        }
	}

	return *this;
}

resolve_iterator resolve_iterator::operator++(int) {
	resolve_iterator c{*this};

	++(*this);

	return c;
}

ipv4_address resolve_iterator::operator*() const {
	return value;
}

const ipv4_address* resolve_iterator::operator->() const {
	return &value;
}

bool resolve_iterator::operator==(const resolve_iterator& other) const {
	return current == other.current;
}

bool resolve_iterator::operator!=(const resolve_iterator& other) const {
	return current != other.current;
}

resolve_iterator resolve(const std::string& address) {
	return resolve_iterator{address};
}

}
