#include "stdafx.h"
#include <math.h>
#include <malloc.h>

#include "gauss.h"

int ArraySize(double **arr) {
	return _msize(arr) / sizeof(arr[0]);
}

int ArraySize(double *arr) {
	return _msize(arr) / sizeof(arr[0]);
}

Matrix2D::Matrix2D(int N, int M)
{
	_matrixVals.clear();
	LinArr<double> rowVal;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
			rowVal.push_back(0);
		_matrixVals.push_back(rowVal);
		rowVal.clear();
	}
}

Matrix2D::Matrix2D(double **DinArr)
{
	_matrixVals.clear();
	LinArr<double> rowVal;
	for (int i = 0; i < ArraySize(DinArr); i++)
	{
		for (int j = 0; j < ArraySize(DinArr[i]); j++)
			rowVal.push_back(DinArr[i][j]);
		_matrixVals.push_back(rowVal);
		rowVal.clear();
	}
}

Matrix2D::Matrix2D(LinArr<LinArr<double>> DinArr)
{ _matrixVals = DinArr; }

Matrix2D::~Matrix2D()
{
	for (int i = 0; i < _matrixVals.size(); i++)
		_matrixVals[i].clear();
	_matrixVals.clear();
}

int Matrix2D::Width() const
{
	if (_matrixVals.size() == 0) return 0;
	else return _matrixVals[0].size();
}

int Matrix2D::Height() const
{
	return _matrixVals.size();
}

double Matrix2D::Index(int I, int J)
{ return _matrixVals[I][J]; }

void Matrix2D::SetIndex(int I, int J, double value)
{
	_matrixVals[I][J] = value;
}

void Matrix2D::AddRow(LinArr<double> row)
{
	while (row.size() < _matrixVals[0].size())
		row.push_back(0);
	_matrixVals.push_back(row);
}

void Matrix2D::AddColumn(LinArr<double> column)
{
	while (column.size() < _matrixVals.size())
		column.push_back(0);

	for (int i = 0; i < _matrixVals.size(); i++)
		_matrixVals[i].push_back(column[i]);
}

double Matrix2D::Determinant()
{
	switch (_matrixVals.size())
	{
		case 0: return 0;
		case 1: return _matrixVals[0][0];
		case 2: return _matrixVals[0][0] * _matrixVals[1][1] - _matrixVals[1][0] * _matrixVals[0][1];
		default:
		{
			double determinant = 0;

			for (int i = 0; i < (int)_matrixVals.size(); i++)
			{
				LinArr<LinArr<double>> minor = _matrixVals;
				minor.erase(minor.begin());

				for (int j = 0; j < (int)minor.size(); j++)
					minor[j].erase(minor[j].begin() + i);

				Matrix2D matr(minor);

				determinant += std::pow(-1, 2 + i) * _matrixVals[0][i] * matr.Determinant();

				minor.clear();
			}

			return determinant;
		}
	}
}

LinArr<double> GaussianElimination(Matrix2D A, LinArr<double> b)
{
	LinArr<double> X = {};
	/* If determinant is 0, there is no possible solutions, according to Rouche–Capelli theorem*/
	if (A.Determinant() == 0)
		return X;
	else
	{
		for (int i = 0; i < b.size(); i++)
			X.push_back(0);

		A.AddColumn(b);
		b.~vector();

		// Straight way
		double token = 1;
		for (int i = 0; i < A.Height(); i++)
		{
			token = A.Index(i, i); // Token gets value for dividing next row of A

			for (int j = A.Height(); j >= i; j--)
				A.SetIndex(i, j, A.Index(i, j) / token);

			for (int j = i + 1; j < A.Height(); j++)
			{
				token = A.Index(j, i); // Token gets value for subtracting previuos value
				for (int k = A.Height(); k >= i; k--)
					A.SetIndex(j, k, A.Index(j, k) - token * A.Index(i, k));
			}
		}

		// Reverse way
		X[A.Height() - 1] = A.Index(A.Height() - 1, A.Width() - 1);
		for (int i = A.Height() - 2; i >= 0; i--)
		{
			X[i] = A.Index(i , A.Height());
			for (int j = i + 1; j < A.Height(); j++) X[i] -= A.Index(i, j) * X[j];
		}
	}
	
	for (int i = 0; i < (int)(X.size() / 2); i++)
	{
		double swapValue = X[i];
		X[i] = X[X.size() - 1 - i];
		X[X.size() - 1 - i] = swapValue;
	}

	return X;
}
