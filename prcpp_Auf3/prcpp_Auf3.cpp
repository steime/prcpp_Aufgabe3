#include "Vector.hpp"
#include "Expression.hpp"
#include <iostream>

int main()
{
	Vector<double, 5> A({ 1, 2, 3, 4, 5 });
	Vector<double, 5> B({ 1, 4, 9, 16, 25 });
	Vector<double, 5> C;

	cout << (A + B) << endl;

	//auto e = 2.0 * A;

	cout << A << endl;
	cout << C << endl;


}
