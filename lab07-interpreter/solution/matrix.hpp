#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <vector>
#include <stdexcept>
#include <string>
#include <sstream>
#include <fstream>

struct MatrixExcepion : public std::runtime_error {
    explicit MatrixExcepion(const std::string& msg) : std::runtime_error(msg) {}
};

struct FileFormatException : public MatrixExcepion {
    FileFormatException() : MatrixExcepion("Invalid file format") {}
};

struct FileOpenException : public MatrixExcepion {
    explicit FileOpenException(const std::string& fname) : MatrixExcepion("Unable to open file '" + fname + "'") {}
};

struct DimensionMismatchException: public MatrixExcepion {
    explicit DimensionMismatchException(int lhs, int rhs) : MatrixExcepion("Dimension mismatch: lhs=" + 
    std::to_string(lhs) + ", rhs" + std::to_string(rhs)) {}
};

struct OutOfBoundsException: public MatrixExcepion {
    OutOfBoundsException() : MatrixExcepion("Requested element is out of bounds") {}
};

class Matrix {
public:
    Matrix() noexcept = default;
    Matrix(int rows, int cols);

    void loadFromFile(const std::string& filename);
    void print(std::ostream& os = std::cout) const noexcept;
    int getElement(int row, int col) const;

    Matrix operator+(const Matrix& other) const;
    Matrix operator*(const Matrix& other) const;

    int rows() const noexcept;
    int cols() const noexcept;
    
private:
    std::vector<std::vector<int>> data;
};
#endif