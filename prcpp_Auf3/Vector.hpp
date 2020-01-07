#pragma once
#include <array>
#include "Expression.hpp"

using namespace std;

template<typename T, size_t S> 
class Vector : public array<T, S>{
public:
	Vector(const std::initializer_list<T>& data) {
		size_t s = __min(data.size(), S);
		auto it = data.begin();
		for (size_t i = 0; i < s; i++) this->at(i) = *it++;
	}

	Vector() = default;

	template<typename Left, typename Op, typename Right> 
	Vector& operator=(Expression<Left, Op, Right>& exp) {
		size_t s = __min(exp.size(), S);
		for (size_t i = 0; i < s; i++) this->at(i) = exp[i];
		return (*this);
	}

	template<typename T> 
	bool operator==(const T vec) const {
		bool res = vec.size() == this->size();
		for (size_t i = 0; i < vec.size(); ++i) {
			if (vec[i] != (*this)[i]) res = false;
		}
		return res;
	}

	friend ostream& operator<<(ostream& os, const Vector& vec) {
		os << "{";
		for (size_t i = 0; i < vec.size(); ++i) {
			os << vec[i];
			if (i != vec.size() - 1) {
				os << ", ";
			}
		}
		os << "}";
		return os;
	}

};;