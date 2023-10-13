//
// Created by zihan on 2022-10-04.
//
#include "matrix.hpp"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


Matrix::Matrix() {
    rowCount = 1, columnCount = 1;
    r = new double*[1];
    for (int i = 0; i < rowCount; i++)
    {
        r[i] = new double[columnCount];
    }
    for (int i = 0; i < rowCount; i++)
    {
        for (int j = 0; j < columnCount; j++)
        {
            r[i][j] = 0.0;
        }
    }
}

Matrix::Matrix(int n)
{
    assert(n > 0);
    rowCount = n, columnCount = n;
    r = new double*[rowCount];
    for (int i = 0; i < rowCount; i++)
    {
        r[i] = new double[columnCount];
    }
    for (int i = 0; i < rowCount * columnCount; i++)
    {
        r[i / columnCount][i % columnCount] = 0.0;
    }
}

Matrix::Matrix(const Matrix& m) {
    rowCount = m.GetRowCount();
    columnCount = m.GetColumnCount();
    r = new double*[rowCount];
    for (int i = 0; i < rowCount; i++)
    {
        r[i] = new double[columnCount];
    }
    for (int i = 0; i < rowCount * columnCount; i++)
    {
        r[i / columnCount][i % columnCount] = m.r[i / columnCount][i % columnCount];
    }
}
Matrix::Matrix(int row, int column) {
    assert(row > 0 && column > 0);
    rowCount = row, columnCount = column;
    r = new double*[rowCount];
    for (int i = 0; i < rowCount; i++)
    {
        r[i] = new double[columnCount];
    }
    for (int i = 0; i < rowCount * columnCount; i++)
    {
        r[i / columnCount][i % columnCount] = 0;
    }
}
Matrix::Matrix(double *arrData){
    int dataNum;
    int row;
    dataNum=ReadFile(arrData);

    row=(int) sqrt(dataNum);
    assert(row*row==dataNum);
    rowCount = row, columnCount = row;
    r = new double*[rowCount];
    for (int i = 0; i < rowCount; i++)
    {
        r[i] = new double[columnCount];
    }
    for (int i = 0; i < rowCount * columnCount; i++)
    {
        r[i / columnCount][i % columnCount] = *(arrData+i);
    }
}

Matrix::Matrix(int row, int column, double value) {
    assert(row > 0 && column > 0);
    rowCount = row, columnCount = column;
    r = new double*[rowCount];
    for (int i = 0; i < rowCount; i++)
    {
        r[i] = new double[columnCount];
    }
    for (int i = 0; i < rowCount * columnCount; i++)
    {
        r[i / columnCount][i % columnCount] = value;
    }
}
void Matrix::setValue(int row, int column, double value)
{
    assert(row > 0 && column > 0);
    r[row][column]=value;
}

double Matrix::getValue(int row, int column)
{
    assert(row > 0 && column > 0);
    return r[row][column];
}

void Matrix::clear()
{
    for (int i = 0; i < rowCount; i++)
    {
        for (int j = 0; j < columnCount; j++)
        {
            r[i][j] = 0.0;
        }
    }
}

int Matrix::GetRowCount() const { return rowCount; }
int Matrix::GetColumnCount() const { return columnCount; }


Matrix::~Matrix() {
    for (int i = 0; i < rowCount; i++)
    {
        delete[] r[i];
    }
    delete[] r;
}

void Matrix::GetSMatrix(){
    const double p=0.85;
    double rj[100];
    Matrix s;
    fill(rj,rj+rowCount,0);
    for(int i=0;i<rowCount;i++){
        for(int j=0;j<columnCount;j++){
            rj[j]=rj[j]+r[i][j];

        }
    }
    for(int i=0;i<rowCount;i++){
        for(int j=0;j<columnCount;j++){
            if(rj[j]!=0) {
                r[i][j]=r[i][j]/rj[j]*p;
            }
            else{
                r[i][j]=1.0/rowCount*p;
            }
        }
    }
}
void Matrix::GetQMatrix() {
    for(int i=0;i<rowCount;i++){
        for(int j=0;j<columnCount;j++){
            r[i][j]=(1-0.85)*1/rowCount;
        }
    }
}
void Matrix::GetRank(){
    for(int i=0;i<rowCount;i++){
        r[i][0]=1;
    }
}

Matrix Matrix::operator=(const Matrix& m)
{
    for (int i = 0; i < rowCount; i++)
    {
        delete[] r[i];
    }
    delete[] r;
    rowCount = m.GetRowCount();
    columnCount = m.GetColumnCount();
    r = new double*[rowCount];
    for (int i = 0; i < rowCount; i++)
    {
        r[i] = new double[columnCount];
    }
    for (int i = 0; i < rowCount * columnCount; i++)
    {
        r[i/ columnCount][i%columnCount] = m.r[i / columnCount][i%columnCount];
    }
    return *this;
}


bool Matrix::operator==(Matrix& y) {
    bool flag = true;
    double tolerance = 0.001;
    if(rowCount!=y.GetRowCount()) return false;
    if(columnCount!=y.GetColumnCount()) return false;
    for (int i = 0; (i < rowCount && (flag)); i++)
    {
        for (int j = 0; (j < columnCount && (flag)); j++)
        {
            if(fabs(r[i][j]-y.r[i][j]) < tolerance ){
                flag = true;
            } else{
                flag = false;
            }
        }
    }
    return flag;
}

bool Matrix::operator!=(Matrix& z) {
    return !operator==(z);
}

Matrix &Matrix::operator*=(const Matrix& m) {
    Matrix temp(rowCount, m.columnCount);
    for (int i = 0; i < temp.rowCount; i++)
    {
        for (int j = 0; j < temp.columnCount; j++)
        {
            for (int k = 0; k < columnCount; k++)
            {
                temp.r[i][j] += (r[i][k] * m.r[k][j]);
            }
        }
    }
    *this = temp;
    return *this;
}

Matrix &Matrix::operator+=(const Matrix& m){
    for (int i = 0; i < rowCount; i++)
    {
        for (int j = 0; j < columnCount; j++)
        {
            r[i][j] = r[i][j] + m.r[i][j];
        }
    }
    return *this;
}

Matrix &Matrix::operator-=(const Matrix& mb){
    for (int i = 0; i < rowCount; i++)
    {
        for (int j = 0; j < columnCount; j++)
        {
            r[i][j] = r[i][j] - mb.r[i][j];
        }
    }
    return *this;
}

Matrix Matrix::operator*(const Matrix& m) const{
    Matrix temp(rowCount, m.columnCount);
    for (int i = 0; i < rowCount; i++)
    {
        for (int j = 0; j < m.columnCount; j++)
        {
            for (int k = 0; k < columnCount; k++)
            {
                temp.r[i][j] += (r[i][k] * m.r[k][j]);
            }
        }
    }
    return temp;
}

Matrix Matrix::operator-(const Matrix& m) const{
    Matrix temp(rowCount, columnCount);
    for (int i = 0; i < rowCount; i++)
    {
        for (int j = 0; j < columnCount; j++)
        {
            for (int k = 0; k < columnCount; k++)
            {
                temp.r[i][j] = (r[i][j] - m.r[i][j]);
            }
        }
    }
    return temp;
}

Matrix Matrix::operator+(const Matrix& m) const{
    Matrix temp(rowCount, columnCount);
    for (int i = 0; i < rowCount; i++)
    {
        for (int j = 0; j < columnCount; j++)
        {
            for (int k = 0; k < columnCount; k++)
            {
                temp.r[i][j] += (r[i][j] + m.r[i][j]);
            }
        }
    }
    return temp;
}

//postfix++
Matrix Matrix::operator++(int ) {
    Matrix old=*this;
    for (int i = 0; i < rowCount; i++)
    {
        for (int j = 0; j < columnCount; j++)
        {
            r[i][j] = r[i][j] + 1;
        }
    }
    return old;
}

//prefix++
Matrix Matrix::operator++(){
    for (int i = 0; i < rowCount; i++)
    {
        for (int j = 0; j < columnCount; j++)
        {
            r[i][j] = r[i][j] + 1;
        }
    }
    return *this;
}

//postfix++
Matrix Matrix::operator--(int ) {
    Matrix old=*this;
    for (int i = 0; i < rowCount; i++)
    {
        for (int j = 0; j < columnCount; j++)
        {
            r[i][j] = r[i][j] - 1;
        }
    }
    return old;
}

//prefix++
Matrix Matrix::operator--(){
    for (int i = 0; i < rowCount; i++)
    {
        for (int j = 0; j < columnCount; j++)
        {
            r[i][j] = r[i][j] - 1;
        }
    }
    return *this;
}

void Matrix::PrintMatrix() const{
    for (int i = 0; i < rowCount; i++)
    {
        for (int j = 0; j < columnCount; j++)
        {
            cout << r[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}
void Matrix::ShowRank() const{
    char Word[26]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    cout<<setprecision(4);
    for(int i=0;i<rowCount;i++){
        cout<<"Page "<<Word[i]<<": "<<(r[i][0]/rowCount)*100<<"%"<<endl;
    }
}
int ReadFile(double* dataArr) {
    ifstream inFile;
    //int col=0;
    //int row=0;

    int TotalData=0;

    inFile.open("../connectivity.txt");
    if (!inFile){
        cout<<"Unable to open file!"<<endl;
        exit(1);
    }

    double d;

    while(inFile>>d)
    {
        *dataArr=d;

        dataArr++;
        TotalData++;

    }
    inFile.close();

//    row=(int) sqrt(TotalData);

    return TotalData;
}
