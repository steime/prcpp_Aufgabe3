#pragma once
#include <iostream>

using namespace std;

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

	template<typename E> bool operator==(const E vec) const {
		bool res = vec.size() == this->size();
		for (size_t i = 0; i < vec.size(); ++i) {
			if (vec[i] != (*this)[i]) res = false;
		}
		return res;
	}


	friend ostream& operator<<(ostream& os, const Expression& exp) {
		os << "{";
		for (size_t i = 0; i < exp.size(); ++i) {
			os << exp[i];
			if (i != exp.size() - 1) {
				os << ", ";
			}
		}
		os << "}";
		return os;
	}
};
// Specialized Template
template<typename Op, typename Right>
class Expression<typename Right::value_type, Op, Right> {
	using type = typename Right::value_type;
	const type& m_left;
	const Right& m_right;
public:
	typedef typename Right::value_type value_type;
	
	Expression(const double& l, const Right& r) : m_left{ l }, m_right{ r } {}

	size_t size() const { 
		return m_right.size(); 
	}

	value_type operator[](size_t i) const {
		return Op::template apply<value_type>(m_left, m_right[i]);
	}

	template<typename E> bool operator==(const E vec) const {
		bool res = vec.size() == this->size();
		for (size_t i = 0; i < vec.size(); ++i) {
			if (vec[i] != (*this)[i]) res = false;
		}
		return res;
	}

	friend ostream& operator<<(ostream& os, const Expression& exp) {
		os << "{";
		for (size_t i = 0; i < exp.size(); ++i) {
			os << exp[i];
			if (i != exp.size() - 1) {
				os << ", ";
			}
		}
		os << "}";
		return os;
	}

};

template<typename Left, typename Op> 
class Expression<Left, Op, typename Left::value_type> {
	using type = typename Left::value_type;
	const Left& m_left;
	const type& m_right;
public:
	typedef typename Left::value_type value_type;

	Expression(const Left& l, const double& r) : m_left{ l }, m_right{ r } {}

	size_t size() const { 
		return m_left.size(); 
	}

	value_type operator[](size_t i) const {
		return Op::template apply<value_type>(m_left[i], m_right);
	}

	template<typename E> bool operator==(const E vec) const {
		bool res = vec.size() == this->size();
		for (size_t i = 0; i < vec.size(); ++i) {
			if (vec[i] != (*this)[i]) res = false;
		}
		return res;
	}

	friend ostream& operator<<(ostream& os, const Expression& exp) {
		os << "{";
		for (size_t i = 0; i < exp.size(); ++i) {
			os << exp[i];
			if (i != exp.size() - 1) {
				os << ", ";
			}
		}
		os << "}";
		return os;
	}


};

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
