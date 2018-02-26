#ifndef DEF_NGSOCKET_RESOLVER_HPP
#define DEF_NGSOCKET_RESOLVER_HPP

#include "endpoint.hpp"

#include <string>
#include <memory>

// TODO: Move in platform
#if defined(NG_WINDOWS)
#include <WinSock2.h>
#else
#include <netdb.h>
#endif

namespace ng {

class address_info {
	addrinfo* result;
	addrinfo* it;
	bool first;
public:
	address_info(const std::string& name);
	~address_info();

	/// NOTE: Will loop
	addrinfo* next();
};

class resolve_iterator {
	std::shared_ptr<address_info> info;
	addrinfo* current;
	ipv4_address value;

	resolve_iterator(const std::string& address);

	friend resolve_iterator resolve(const std::string& address);
public:
	resolve_iterator();

	resolve_iterator& operator++();
	resolve_iterator operator++(int);

	ipv4_address operator*() const;
	const ipv4_address* operator->() const;

	bool operator==(const resolve_iterator& other) const;
	bool operator!=(const resolve_iterator& other) const;
};

resolve_iterator resolve(const std::string& address);

}

#endif
