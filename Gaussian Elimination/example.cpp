#include "stdafx.h"
#include <iostream>
#include <conio.h>

#include "gauss.h"

using namespace std;

int example()
{
	LinArr<LinArr<double>> vals2 = { { 12, 2 },
	{ 2, 0 } };

	LinArr<LinArr<double>> vals3 = { { 12, 0, 0 },
	{ 0, 1, 0 },
	{ 0, 0, 1 } };

	LinArr<LinArr<double>> a3trivial = { { 1, 2, 3 },
	{ 4, 5, 6 },
	{ 7, 8, 9 } };

	LinArr<LinArr<double>> a3 = { { 12, -12, 4 },
	{ 2, 3, 44 },
	{ 12, 3, -1 } };

	LinArr<double> b3 = { -1, 2, 3 };

	LinArr<LinArr<double>> vals4 = { { 12.23, 0.4, 3, -1 },
	{ 1, 1.23, 2, 0.11 },
	{ 5.12, 0.65, 1, 0 },
	{ 0, 0, 0, 1.12 } };

	LinArr<double> b4 = { -1.76, 2.23, -3.5, 4.5 };

	Matrix2D mtrx({ { 12, 2 },
					{ 2, 0 } });

	Matrix2D matrix2d(vals3);

	LinArr<double> result = GaussianElimination(Matrix2D(a3), b3);
	result = GaussianElimination(Matrix2D(vals4), b4);

	for (auto& element : result)
		cout << element << endl;

	_getch();
	return 0;
}