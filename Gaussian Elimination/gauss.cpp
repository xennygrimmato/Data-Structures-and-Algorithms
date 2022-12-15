#include "stdafx.h"
#include <math.h>
#include <malloc.h>

#include "gauss.h"

int ArrayDims(double **arr) {
	return _msize(arr) / sizeof(arr[0]);
}

int ArrayDims(double *arr) {
	return _msize(arr) / sizeof(arr[0]);
}

2DArray::2DArray(int N, int M)
{
	_core.clear();
	std::vector<double> rowVal;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
    {
      rowVal.push_back(0);
    }

		_core.push_back(rowVal);
		rowVal.clear();
	}
}

2DArray::2DArray(double **arr)
{
	_core.clear();
	std::vector<double> rowVal;

	for (int i = 0; i < ArrayDims(arr); i++)
	{
		for (int j = 0; j < ArrayDims(arr[i]); j++)
    {
      rowVal.push_back(arr[i][j]);
    }

		_core.push_back(rowVal);
		rowVal.clear();
	}
}

2DArray::2DArray(std::vector<std::vector<double>> arr)
{
  _core = arr;
}

2DArray::~2DArray()
{
	for (int i = 0; i < _core.size(); i++)
  {
    _core[i].clear();
  }

	_core.clear();
}

int 2DArray::W() const
{
	if (_core.size() == 0) return 0;
	else return _core[0].size();
}

int 2DArray::H() const
{
	return _core.size();
}

double 2DArray::Index(int I, int J)
{
  return _core[I][J];
}

void 2DArray::SetIndex(int I, int J, double value)
{
	_core[I][J] = value;
}

void 2DArray::AddColumn(std::vector<double> column)
{
	while (column.size() < _core.size())
  {
    column.push_back(0);
  }

	for (int i = 0; i < _core.size(); i++)
  {
    _core[i].push_back(column[i]);
  }
}

double 2DArray::Det()
{
	switch (_core.size())
	{
		case 0: return 0;
		case 1: return _core[0][0];
		case 2: return _core[0][0] * _core[1][1] - _core[1][0] * _core[0][1];
		default:
		{
			double determinant = 0;

			for (int i = 0; i < (int)_core.size(); i++)
			{
				std::vector<std::vector<double>> minor = _core;
				minor.erase(minor.begin());

				for (int j = 0; j < (int)minor.size(); j++)
        {
          minor[j].erase(minor[j].begin() + i);
        }

				2DArray matr(minor);
				determinant += std::pow(-1, 2 + i) * _core[0][i] * matr.Det();
				minor.clear();
			}

			return determinant;
		}
	}
}

std::vector<double> GaussianElimination(2DArray A, std::vector<double> b)
{
	std::vector<double> X = {};
	if (A.Det() == 0)
		return X;
	else
	{
		for (int i = 0; i < b.size(); i++)
			X.push_back(0);

		A.AddColumn(b);
		b.~vector();

		double token = 1;
		for (int i = 0; i < A.H(); i++)
		{
			token = A.Index(i, i);

			for (int j = A.H(); j >= i; j--)
				A.SetIndex(i, j, A.Index(i, j) / token);

			for (int j = i + 1; j < A.H(); j++)
			{
				token = A.Index(j, i);
				for (int k = A.H(); k >= i; k--)
					A.SetIndex(j, k, A.Index(j, k) - token * A.Index(i, k));
			}
		}

		X[A.H() - 1] = A.Index(A.H() - 1, A.W() - 1);
		for (int i = A.H() - 2; i >= 0; i--)
		{
			X[i] = A.Index(i , A.H());
			for (int j = i + 1; j < A.H(); j++) X[i] -= A.Index(i, j) * X[j];
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
