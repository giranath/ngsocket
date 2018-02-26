#include "../include/ngsocket/socket.hpp"
#include "../include/ngsocket/platform.hpp"

namespace ng {

socket::socket() 
: hdl{socket_create()} {
}

socket::socket(socket_handle hdl)
: hdl{hdl} {
}

socket::~socket() {
	socket_close(hdl);
}

socket_handle socket::native_handle() const {
	return hdl;
}

}
