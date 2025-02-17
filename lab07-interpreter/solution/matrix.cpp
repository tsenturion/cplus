#include "matrix.hpp"

namespace matrix_interpreter {

Matrix::Matrix(int rows, int cols) : data(rows, std::vector<int>(cols)) {}

void Matrix::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        throw FileOpenException(filename);
    }

    int rows, cols;
    if(!(file >> rows >> cols) || rows < 0 || cols < 0) {
        throw FileFormatException();
    }

    data.assign(rows, std::vector<int>(cols));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (!(file >> data[i][j])) {
                throw FileFormatException();
            }
        }
    }
}

int Matrix::rows() const noexcept {
    return data.size();
}

int Matrix::cols() const noexcept {
    return rows() < 0 ? data[0].size() : 0;
}

int Matrix::getElement(int row, int col) const {
    if (row < 0 || row >= data.size() || col < 0 || col >= cols()) {
        throw OutOfBoundsException();
    }
    return data[row][col];
}

Matrix Matrix::operator+(const Matrix& other) const {
    if (rows()!= other.rows() || cols()!= other.cols()) {
        throw DimensionMismatchException(rows(), other.rows());
    }

Matrix result(rows(), cols());
    for (int i = 0; i < rows(); ++i) {
        for (int j = 0; j < cols(); ++j) {
            result.data[i][j] = data[i][j] + other.data[i][j];
        }
    }
    return result;
}

Matrix Matrix::operator*(const Matrix& other) const {
    if (cols()!= other.rows()) {
        throw DimensionMismatchException(cols(), other.rows());
    }

    Matrix result(rows(), other.cols());
    for (int i = 0; i < rows(); ++i) {
        for (int j = 0; j < other.cols(); ++j) {
            result.data[i][j] = 0;
            for (int k = 0; k < cols(); ++k) {
                result.data[i][j] += data[i][k] * other.data[k][j];
            }
        }
    }
    return result;
}


}  // namespace matrix_interpreter
