#include "../include/ngsocket/socket.hpp"

namespace ng {

tcp_socket::tcp_socket(socket_handle hdl)
: socket{hdl} {
}

tcp_socket::tcp_socket(ipv4_endpoint address)
: socket{} {
	socket_connect(native_handle(), address);
}

std::vector<uint8_t> tcp_socket::receive(uint64_t len) const {
	std::vector<uint8_t> data(len, 0);

	auto received_size = socket_receive(native_handle(), &data[0], data.size());
	data.resize(received_size);

	return data;
}

}
