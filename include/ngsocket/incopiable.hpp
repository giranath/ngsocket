#ifndef DEF_NGSOCKET_INCOPIABLE_HPP
#define DEF_NGSOCKET_INCOPIABLE_HPP value

namespace ng {

class incopiable {
public:
	incopiable() = default;
	incopiable(const incopiable&) = delete;
	incopiable& operator=(const incopiable&) = delete;
};

}

#endif /* ifndef DEF_NGSOCKET_INCOPIABLE_HPP */
