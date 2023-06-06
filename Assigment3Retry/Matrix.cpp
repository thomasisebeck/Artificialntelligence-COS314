#include "Matrix.h"
#include <iostream>
using namespace std;

Matrix::Matrix() {
    this->rows = 0;
    this->cols = 0;
    this->values = {};
}

Matrix::Matrix(int cols_x, int rows_y) {
    this->cols = cols_x;
    this->rows = rows_y;
    this->values = {};
    this->values.resize(cols_x * rows_y, 0.0);

    for (int y = 0; y < rows_y; y++)
        for (int x = 0; x < cols_x; x++)
            get(x, y) = 0;

    ::srand(time(0));
}

double& Matrix::get(int col_x, int row_y) {
    return values[row_y * cols + col_x];
}

Matrix Matrix::mult(Matrix &other) {
    if (this->cols != other.rows)
        throw "mismatch dimensions";

    Matrix out(other.cols, this->rows);

    for (int y = 0; y < out.rows; y++)
        for (int x = 0; x < out.cols; x++) {
            double res = 0;
            for (int k = 0; k < this->cols; k++)
                res += get(k, y) * other.get(x, k);
            out.get(x, y) = res;
        }

    return out;
}

Matrix Matrix::add(Matrix &other) {
    if (this->rows != other.rows || this->cols != other.cols)
        throw "add dimension mismatch";

    Matrix out(this->cols, this->rows);

    for (int row_y = 0; row_y < out.rows; row_y++)
        for (int col_x = 0; col_x < out.cols; col_x++)
            out.get(col_x, row_y) = get(col_x, row_y) + other.get(col_x, row_y);

    return out;
}

Matrix Matrix::multScaler(double value) {

    Matrix out(this->cols, this->rows);
    for (int y = 0; y < out.rows; y++)
        for (int x = 0; x < out.cols; x++)
            out.get(x, y) = get(x, y) * value;

    return out;
}

Matrix Matrix::addScaler(double value) {

    Matrix out(this->cols, this->rows);
    for (int y = 0; y < out.rows; y++)
        for (int x = 0; x < out.cols; x++)
            out.get(x, y) = get(x, y) + value;

    return out;

}

Matrix Matrix::negate() {
    Matrix out(this->cols, this->rows);
    for (int y = 0; y < out.rows; y++)
        for (int x = 0; x < out.cols; x++)
            out.get(x, y) = - get(x, y);

    return out;
}

Matrix Matrix::flipDimensions() {
    Matrix out(this->rows, this->cols);

    for (int y = 0; y < rows; y++)
        for (int x = 0; x < cols; x++)
            out.get(y, x) = get(x, y);

    return out;
}

Matrix Matrix::operation(functionType type) {
    Matrix out(this->cols, this->rows);

    for (int y = 0; y < rows; y++)
        for (int x = 0; x < cols; x++) {
            if (type == RANDOM)
                out.get(x, y) = (double) rand() / RAND_MAX;
            if (type == SIGMOID)
                out.get(x, y) = sigmoid(get(x, y));

        }

    return out;
}

void Matrix::print() {

    for (int y = 0; y < rows; y++)
        for (int x = 0; x < cols; x++) {
            cout << get(x, y) << " ";
        cout << endl;
    }

}

double Matrix::sigmoid(double x) {
    return static_cast<double>(1) / (1 + exp(-x));
}

double Matrix::sigmoidDeriv(double x) {
    //input the result of sigmoid
    return x * (1 - x);
}

