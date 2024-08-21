#pragma once
#include <vector>
#include <cmath>
#include "sharedTypes.h"

class Matrix {
public:
    std::vector<double> values;
    int rows;
    int cols;
    double sigmoid(double x);
    double sigmoidDeriv(double x);
public:
    Matrix();
    Matrix(int cols_x, int rows_y);
    double& get(int col_x, int row_y);
    Matrix mult(Matrix& other);
    Matrix add(Matrix &other, bool& converged);
    Matrix multScaler(double value);
    Matrix elementWiseMultipy(Matrix& other);
    Matrix addScaler(double value);
    Matrix negate();
    Matrix flipDimensions();
    Matrix operation(functionType type);
    void print();
};