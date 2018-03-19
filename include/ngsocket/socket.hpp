#ifndef DEF_NGSOCKET_SOCKET_HPP
#define DEF_NGSOCKET_SOCKET_HPP

#include "platform.hpp"
#include "incopiable.hpp"
#include "address.hpp"
#include "endpoint.hpp"
#include "options.hpp"

#include <cstdint>
#include <memory>
#include <vector>
#include <algorithm>
#include <chrono>

namespace ng {

struct socket_service : public incopiable {
	socket_service();
	socket_service(socket_service&&) = delete;
	socket_service& operator=(socket_service&&) = delete;
	~socket_service();
};

class socket : public incopiable {
	socket_handle hdl;

public:
	socket();
	socket(socket_handle hdl);

	virtual ~socket();

	socket_handle native_handle() const;

	template<typename OPTION>
	void set_option(const OPTION& opt) {
		static_assert(is_option<OPTION>::VALUE, "you must specify a valid option");

		socket_set_option(hdl, OPTION::NAME, reinterpret_cast<const void*>(&opt.value), sizeof(opt.value));
	}
};

class tcp_listener;

class tcp_socket : public socket {
	friend tcp_listener;
	tcp_socket(socket_handle hdl);

public:
	tcp_socket(ipv4_endpoint endpoint);

	std::vector<uint8_t> receive(uint64_t len) const;

	template<typename DATA, typename ITERATOR = typename DATA::const_iterator>
	ITERATOR send(const DATA& data) const {
		return send(std::begin(data), std::end(data));
	}

	template<typename ITERATOR>
	ITERATOR send(ITERATOR begin, ITERATOR end) const {
		std::vector<uint8_t> data;

		for(auto it = begin; it != end; ++it) {
			uint8_t byte = *it;

			data.push_back(byte);
		}

		return std::next(begin, socket_send(native_handle(), &data[0], data.size()));
	}

	template<typename INSERT_ITERATOR>
	INSERT_ITERATOR receive(uint64_t len, INSERT_ITERATOR back) const {
		auto data = receive(len);

		return std::copy(std::begin(data), std::end(data), back);
	}
};

class tcp_listener : public socket {
public:
    struct connection {
        std::unique_ptr<tcp_socket> socket;
        ipv4_endpoint endpoint;

		bool operator==(const connection& other) const;
		bool operator!=(const connection& other) const;
    };

	tcp_listener(ipv4_endpoint endpoint);
	tcp_listener(ipv4_endpoint endpoint, int32_t backlog);

	connection wait_for_connection() const;
};

class socket_acceptor : public incopiable {
private:
	struct impl;
	std::unique_ptr<impl> pimpl;

	bool wait(uint64_t timeout) const;
public:
	socket_acceptor();
	~socket_acceptor();

	void add(const socket& s) const;
	void remove(const socket& s) const;
	void clear() const;

	bool is_ready(const socket& s) const;

	template<typename rep, typename period>
	bool wait(std::chrono::duration<rep, period> t) {
		auto d = std::chrono::duration_cast<std::chrono::microseconds>(t);
		return wait(d.count());
	}

	bool wait();

    bool poll();

};

}

#endif /* DEF_NGSOCKET_SOCKET_HPP */
