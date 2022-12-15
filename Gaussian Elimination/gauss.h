#pragma once
#include <vector>

#ifndef GAUSS_ELIM_H
#define GAUSS_ELIM_H

int ArrayDims(double *arr);
int ArrayDims(double **arr);

class 2DArray
{
public:
  2DArray(int N, int M);

  explicit 2DArray(double **arr);
  explicit 2DArray(std::vector<std::vector<double>> arr);

  ~2DArray();

  double Det();

  2DArray T();
  void TSelf();

  2DArray Inv();
  void InvSelf();

  double Index(int I, int J);
  void SetIndex(int I, int J, double value);

  void AddRow(std::vector<double> row);
  void AddColumn(std::vector<double> column);

  int W() const;
  int H() const;

  int Rank();

private:
	std::vector<std::vector<double>> _core;
};

std::vector<double> Gauss(2DArray A, std::vector<double> b);
#endif
