#include "../include/ngsocket/socket.hpp"

#include <algorithm>

#if defined(NG_WINDOWS)
#undef max
#else
#include <sys/select.h>
#endif

namespace ng {

struct socket_acceptor::impl {
	fd_set all;
	fd_set ready;

	int max;
	int count;
};

socket_acceptor::socket_acceptor()
: pimpl{std::make_unique<impl>()} {
	clear();
}

socket_acceptor::~socket_acceptor() {

}

void socket_acceptor::add(const socket& s) const {
	auto hdl = s.native_handle();
#if defined(NG_WINDOWS)
#else
	pimpl->max = std::max(pimpl->max, hdl);
#endif

	FD_SET(hdl, &pimpl->all);
}

void socket_acceptor::remove(const socket& s) const {
	auto hdl = s.native_handle();

	FD_CLR(hdl, &pimpl->all);
	FD_CLR(hdl, &pimpl->ready);
}

void socket_acceptor::clear() const {
	FD_ZERO(&pimpl->all);
	FD_ZERO(&pimpl->ready);

	pimpl->max = 0;
	pimpl->count = 0;
}

bool socket_acceptor::is_ready(const socket& s) const {
	return FD_ISSET(s.native_handle(), &pimpl->ready) != 0;
}

bool socket_acceptor::wait(uint64_t timeout) const {
	timeval time;
	time.tv_sec = static_cast<long>(timeout / 1'000'000);
	time.tv_usec = static_cast<long>(timeout % 1'000'000);

	pimpl->ready = pimpl->all;

	int count = ::select(pimpl->max + 1, &pimpl->ready, nullptr, nullptr, &time);

	return count > 0;
}


}
