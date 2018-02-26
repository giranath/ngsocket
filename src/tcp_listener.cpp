#include "../include/ngsocket/socket.hpp"

#include <system_error>
#include <cstring>

namespace ng {

bool tcp_listener::connection::operator==(const connection& other) const {
	return socket == other.socket && endpoint == other.endpoint;
}

bool tcp_listener::connection::operator!=(const connection& other) const {
	return socket != other.socket || endpoint != other.endpoint;
}

tcp_listener::tcp_listener(ipv4_endpoint endpoint){
	socket_bind(native_handle(), endpoint);
	socket_listen(native_handle());
}

tcp_listener::tcp_listener(ipv4_endpoint endpoint, int32_t backlog) {
	socket_bind(native_handle(), endpoint);
	socket_listen(native_handle(), backlog);
}

tcp_listener::connection tcp_listener::wait_for_connection() const {
	ipv4_endpoint client_endpoint;
	socket_handle client_hdl = socket_accept(native_handle(), client_endpoint);

	connection conn;
	conn.socket = std::unique_ptr<tcp_socket>(new tcp_socket{client_hdl});
	conn.endpoint = client_endpoint;

	return conn;
}

}
