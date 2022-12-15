#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <vector>

#include "gauss.h"


using namespace std;

int example()
{
	std::vector<std::vector<double>> vals2 = { { 12, 2 },
	{ 2, 0 } };

	std::vector<std::vector<double>> vals3 = { { 12, 0, 0 },
	{ 0, 1, 0 },
	{ 0, 0, 1 } };

	std::vector<std::vector<double>> a3trivial = { { 1, 2, 3 },
	{ 4, 5, 6 },
	{ 7, 8, 9 } };

	std::vector<std::vector<double>> a3 = { { 12, -12, 4 },
	{ 2, 3, 44 },
	{ 12, 3, -1 } };

	std::vector<double> b3 = { -1, 2, 3 };

	std::vector<std::vector<double>> vals4 = { { 12.23, 0.4, 3, -1 },
	{ 1, 1.23, 2, 0.11 },
	{ 5.12, 0.65, 1, 0 },
	{ 0, 0, 0, 1.12 } };

	std::vector<double> b4 = { -1.76, 2.23, -3.5, 4.5 };

	2DArray mtrx({ { 12, 2 },
					{ 2, 0 } });

	2DArray matrix2d(vals3);

	std::vector<double> result = GaussianElimination(2DArray(a3), b3);
	result = GaussianElimination(2DArray(vals4), b4);

	for (auto& element : result)
		cout << element << endl;

	_getch();
	return 0;
}
