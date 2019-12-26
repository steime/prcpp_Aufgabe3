#pragma once
#include <array>
#include "Expression.hpp"

using namespace std;

template<typename T, size_t S> class Vector : public array<T, S>{
public:
	Vector(const std::initializer_list<T>& data) {
		size_t s = __min(data.size(), S);
		auto it = data.begin();
		for (size_t i = 0; i < s; i++) this->at(i) = *it++;
	}

	Vector() {
		array<T, S> at;
	}

	friend ostream& operator<<(ostream& os, const Vector& s) {
		os << "{";
		for (size_t i = 0; i < s.size(); ++i) {
			os << s[i];
			if (i != s.size() - 1) {
				os << ", ";
			}
		}
		os << "}";
		return os;
	}	

	template<typename Left, typename Op, typename Right> 
	Vector& operator=(Expression<Left, Op, Right>& exp) {
		size_t s = __min(exp.size(), S);
		for (size_t i = 0; i < s; i++) this->at(i) = exp[i];
		return (*this);
	}

	template<typename T> 
	bool operator==(const T v) const {
		bool res = v.size() == this->size();
		for (size_t i = 0; i < v.size(); ++i) {
			if (v[i] != (*this)[i]) res = false;
		}
		return res;
	}


};;