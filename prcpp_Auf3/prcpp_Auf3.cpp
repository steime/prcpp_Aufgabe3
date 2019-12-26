#include "Vector.hpp"
#include "Expression.hpp"
#include <iostream>

int main()
{
	Vector<float, 4> A({ 1, 2, 3, 4 });
	Vector<float, 4> B({ 2, 1, 0, 1 });
	Vector<float, 4> D;
	auto e = (A - B) * (A + B);
	D = e;
	cout << D << endl; // [-3,3,9,15]
	B = { 3, 0, 2, 5 };
	cout << e << endl; // [-8,4,5,-9]
	B = { 4, 3, 3, -2 };
	cout << e[1] << endl; // -5

	/*
	Vector<double, 5> A({ 1, 2, 3, 4, 5 });
	Vector<double, 5> B({ 1, 4, 9, 16, 25 });
	Vector<double, 5> C;

	cout << (A + B) << endl;

	//auto e = 2.0 * A;

	cout << A << endl;
	cout << C << endl;
	*/

}
