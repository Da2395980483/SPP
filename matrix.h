#ifndef matrix_H
#define matrix_H

using namespace std;

double** MatrixFH(double** matrix1, int row, int col);//反号函数
double** MatrixTransposition(double** matrix, int row, int col);
double** MatrixAdd(double** matrix1, double** matrix2, int row, int col);
double** MatrixAdd1(double** matrix1, double** matrix2, int row, int col);// 此处将改正值的单位变回了米
double** MatrixMult(double** matrix1, double** matrix2, int row1, int col1, int row2, int col2);
double** Gauss(double** Naa, int row);
void output(double** matrix, int row, int col);
double** inputq(int row, int col);
double** input(int row, int col);

#endif