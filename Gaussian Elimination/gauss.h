#pragma once
#include <vector>

#ifndef GAUSS_ELIM_H
#define GAUSS_ELIM_H

int ArrayDims(double *arr);
int ArrayDims(double **arr);

class Array2D
{
    public:
        Array2D(int N, int M);

        explicit Array2D(double **arr);
        explicit Array2D(std::vector<std::vector<double>> arr);

        ~Array2D();

        double Det();

        double Index(int I, int J);
        void SetIndex(int I, int J, double value);

        void AddColumn(std::vector<double> column);

        int W() const;
        int H() const;

    private:
        std::vector<std::vector<double>> _core;
};

std::vector<double> Gauss(Array2D A, std::vector<double> b);
#endif
