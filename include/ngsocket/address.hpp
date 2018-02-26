#ifndef DEF_NGSOCKET_ADDRESS_HPP
#define DEF_NGSOCKET_ADDRESS_HPP

#include <cstdint>
#include <string>

namespace ng {

class ipv4_address {
	uint32_t value;

public:
	ipv4_address();
	ipv4_address(const std::string& str);
	ipv4_address(uint8_t a, uint8_t b, uint8_t c, uint8_t d);
	ipv4_address(uint32_t address);

	std::string to_string() const;
	uint32_t to_integer() const;

	bool operator==(const ipv4_address& other) const;
	bool operator!=(const ipv4_address& other) const;

	static const ipv4_address NONE;
	static const ipv4_address ANY;
	static const ipv4_address LOCALHOST;
	static const ipv4_address BROADCAST;
};

}

#endif /* ifndef DEF_NGSOCKET_ADDRESS_HPP */
