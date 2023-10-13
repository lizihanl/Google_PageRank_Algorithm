//
// Created by zihan on 2022-10-04.
//

#ifndef LAB1TEMPLATE_MATRIX_HPP
#define LAB1TEMPLATE_MATRIX_HPP


#include <string>
#include <cassert>
#include <iostream>
#include <typeinfo>
#include <math.h>
using namespace std;


int ReadFile(double *);
class Matrix
{
private:
    double** r;
    int rowCount, columnCount;

public:
    Matrix();
    Matrix(int n);
    Matrix(int row, int column);
    Matrix(double *);
    void setValue(int row, int column, double value);
    double getValue(int row, int column);
    void clear();
    Matrix(int row, int column, double value);
    Matrix(const Matrix& m);
    int GetRowCount() const;
    int GetColumnCount() const;
    void PrintMatrix() const;
    void ShowRank() const;
    ~Matrix();
    Matrix operator=(const Matrix&);
    Matrix &operator*=(const Matrix& m);
    Matrix &operator+=(const Matrix& m);
    Matrix &operator-=(const Matrix& m);
    Matrix operator*(const Matrix&)const;
    Matrix operator+(const Matrix&)const;
    Matrix operator-(const Matrix&)const;
    Matrix operator++(int );//postfix
    Matrix operator++();//prefix
    Matrix operator--(int );//postfix
    Matrix operator--();//prefix
    bool operator==(Matrix& y);
    bool operator!=(Matrix& z);
    void GetSMatrix();
    void GetQMatrix();
    void GetRank();
};


#endif //LAB1TEMPLATE_MATRIX_HPP
