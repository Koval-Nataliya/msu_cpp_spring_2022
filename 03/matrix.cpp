#include <iostream>
#include "matrix.hpp"

void Matrix::ProxyRow::setDataSize(size_t n){
    data_ = new int32_t[n]();
    columnSize = n;
}

int32_t& Matrix::ProxyRow::operator[](size_t j) {
	if(j >= columnSize)
        throw std::out_of_range("");
	return data_[j];
}

Matrix::ProxyRow::~ProxyRow(){
    delete[] data_;
}

Matrix::Matrix(size_t m, size_t n){
    rowSize = m;
    columnSize = n;

    rows_ = new ProxyRow[m];
    for(size_t i = 0; i < m; ++i)
        rows_[i].setDataSize(n);
}

size_t Matrix::getRowSize() const {
    return rowSize;
}

size_t Matrix::getColumnSize() const {
    return columnSize;
}

void  Matrix::operator*=(int32_t c){
    for(size_t i = 0; i < rowSize; ++i)
        for(size_t j = 0; j < columnSize; ++j)
            rows_[i][j] *= c;
}

Matrix::ProxyRow& Matrix::operator[](size_t i) {
    if(i >= rowSize)
        throw std::out_of_range("");
    return rows_[i];
}

int32_t Matrix::getValue(size_t i, size_t j) const {
    if(i >= rowSize || j >= columnSize)
	    throw std::out_of_range("");
    return rows_[i][j];
}

Matrix::~Matrix(){
    delete[] rows_;
}

bool Matrix::operator== (const Matrix &matrix2){
    size_t m = rowSize, n = columnSize;

    if(m != matrix2.getRowSize() || n != matrix2.getColumnSize())
        return false;

    bool f = true;

    for(size_t i = 0; f && i < m; ++i)
        for(size_t j = 0; f && j < n; ++j)
            f = getValue(i, j) == matrix2.getValue(i, j);

    return f;
}

bool Matrix::operator!= (const Matrix &matrix2){
    return !(*this == matrix2);
}

Matrix Matrix::operator+(const Matrix &matrix2){
    size_t m = rowSize, n = columnSize;

    if(m != matrix2.getRowSize() || n != matrix2.getColumnSize())
        throw std::out_of_range("");

    Matrix ans(m, n);

    for(size_t i = 0; i < m; ++i)
        for(size_t j = 0; j < n; ++j)
            ans[i][j] = getValue(i, j) + matrix2.getValue(i, j);

    return ans;
}

std::ostream& operator<< (std::ostream &out, const Matrix &matrix) {
    size_t m = matrix.getRowSize(), n = matrix.getColumnSize();

    for(size_t i = 0; i < m; ++i, out << std::endl)
            for(size_t j = 0; j < n; ++j)
                out << matrix.getValue(i, j) << " ";

    return out;
}
