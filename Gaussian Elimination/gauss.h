#pragma once
#include <vector>

#ifndef GAUSS_ELIM_H
#define GAUSS_ELIM_H

#define LinArr std::vector //This name is too long for me

/// Hi, %username%.
/// This is extendable header for Gaussian Elimination algorythm
/// Hacktoberfest 2018!

/// Performance tests:
/// 1) Running time:
/// TODO: Update info

// Thank you, Bjarne Stroustrup, for not defining function of array size in STD!
int ArraySize(double *arr);
int ArraySize(double **arr);

// More comfortable representation of 2D array
class Matrix2D
{
public:
	Matrix2D(int N, int M);// Initialize null-matrix by factor NxM

	// (0, ..., 0)
	// (0, ..., 0) } N
	// (0, ..., 0)
	//      M

	explicit Matrix2D(double **DinArr);// Initialize matrix by dynamic array
	explicit Matrix2D(LinArr<LinArr<double>> DinArr); // Initialize matrix by vector list

	~Matrix2D();

	double Determinant(); // Recurent formula, based on minors

	Matrix2D Transpose();
	void TransposeSelf();

	Matrix2D Inverse();
	void InverseSelf();

	double Index(int I, int J); // Get value stored in (I, J)
	void SetIndex(int I, int J, double value);

	void AddRow(LinArr<double> row);
	void AddColumn(LinArr<double> column);

	int Width() const;
	int Height() const;

	int Rang(); // Max ammount of non-null minors in matrix. Helps to identify ammount of solutions in system
private:
	LinArr<LinArr<double>> _matrixVals;
};

LinArr<double> GaussianElimination(Matrix2D A, LinArr<double> b);
#endif
