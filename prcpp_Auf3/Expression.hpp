#pragma once
#include <iostream>
#include "Expression.hpp"

using namespace std;

struct Add {
	template<typename T> static T apply(T l, T r) {
		return l + r;
	}
};

template<typename Left, typename Right>
Expression<Left, Add, Right> operator+(const Left& l, const Right& r) {
	return Expression<Left, Add, Right>(l, r);
}

struct Subtract {
	template<typename T> static T apply(T l, T r) {
		return l - r;
	}
};

template<typename Left, typename Right>
Expression<Left, Subtract, Right> operator-(const Left& l, const Right& r) {
	return Expression<Left, Subtract, Right>(l, r);
}

struct Multiply {
	template<typename T> static T apply(T l, T r) {
		return l * r;
	}
};

template<typename Left, typename Right>
Expression<Left, Multiply, Right> operator*(const Left& l, const Right& r) {
	return Expression<Left, Multiply, Right>(l, r);
}

struct Divide {
	template<typename T> static T apply(T l, T r) {
		return l / r;
	}
};

template<typename Left, typename Right>
Expression<Left, Divide, Right> operator/(const Left& l, const Right& r) {
	return Expression<Left, Divide, Right>(l, r);
}

template<typename Left, typename Op, typename Right> 
class Expression {
		const Left& m_left;
		const Right& m_right;

	public:
		typedef typename Left::value_type value_type;

		Expression(const Left& l, const Right& r) : m_left{ l }, m_right{ r } {}

		size_t size() const { 
			return m_left.size(); 
		}

		value_type operator[](size_t i) const {
			return Op::template apply<value_type>(m_left[i], m_right[i]);
		}

		template<typename E> bool operator==(const E v) const {
			bool res = v.size() == this->size();
			for (size_t i = 0; i < v.size(); ++i) {
				if (v[i] != (*this)[i]) res = false;
			}
			return res;
		}


		friend ostream& operator<<(ostream& os, const Expression& s) {
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
};

template<typename Op, typename Right> 
class Expression<double, Op, Right> {
	const double& m_left;
	const Right& m_right;
public:
	typedef typename Right::value_type value_type;
	Expression(const double& l, const Right& r) : m_left{ l }, m_right{ r } {}
	size_t size() const { return m_right.size(); }

	value_type operator[](size_t i) const {
		return Op::template apply<value_type>(m_left, m_right[i]);
	}

	template<typename E> bool operator==(const E v) const {
		bool res = v.size() == this->size();
		for (size_t i = 0; i < v.size(); ++i) {
			if (v[i] != (*this)[i]) res = false;
		}
		return res;
	}

	friend ostream& operator<<(ostream& os, const Expression& s) {
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

};

template<typename Left, typename Op> 
class Expression<Left, Op, double> {
	const Left& m_left;
	const double& m_right;
public:
	typedef typename Left::value_type value_type;
	Expression(const Left& l, const double& r) : m_left{ l }, m_right{ r } {}
	size_t size() const { return m_left.size(); }

	value_type operator[](size_t i) const {
		return Op::template apply<value_type>(m_left[i], m_right);
	}

	template<typename E> bool operator==(const E v) const {
		bool res = v.size() == this->size();
		for (size_t i = 0; i < v.size(); ++i) {
			if (v[i] != (*this)[i]) res = false;
		}
		return res;
	}

	friend ostream& operator<<(ostream& os, const Expression& s) {
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


};

