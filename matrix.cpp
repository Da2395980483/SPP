#include<iostream>
#include<math.h>
#include <fstream>
#include <stdlib.h>
#include <iomanip>
#include <matrix.h>
using namespace std;
double** MatrixFH(double** matrix1, int row, int col)//���ź���
{
    double** p = new double* [row];
    for (int i = 0; i < row; i++)
    {
        p[i] = new double[col];
    }
    p = matrix1;
    double** o = new double* [row];
    for (int i = 0; i < row; i++)
    {
        o[i] = new double[col];
    }

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            o[i][j] = 0 - p[i][j];
        }
    }
    return o;
}
double** MatrixTransposition(double** matrix, int row, int col)
{
    double** p = new double* [row];
    for (int i = 0; i < row; i++)
    {
        p[i] = new double[col];
    }
    p = matrix;
    double** q = new double* [col];
    for (int i = 0; i < col; i++)
    {
        q[i] = new double[row];
    }
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
        {
            q[j][i] = p[i][j];
        }
    return q;
}
double** MatrixAdd(double** matrix1, double** matrix2, int row, int col)
{
    double** p = new double* [row];
    for (int i = 0; i < row; i++)
    {
        p[i] = new double[col];
    }
    p = matrix1;
    double** q = new double* [row];
    for (int i = 0; i < row; i++)
    {
        q[i] = new double[col];
    }
    q = matrix2;
    double** o = new double* [row];
    for (int i = 0; i < row; i++)
    {
        o[i] = new double[col];
    }
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            o[i][j] = p[i][j] + q[i][j];
        }
    }
    return o;
}
double** MatrixAdd1(double** matrix1, double** matrix2, int row, int col)//�˴�������ֵ�ĵ�λ�������
{
    double** p = new double* [row];
    for (int i = 0; i < row; i++)
    {
        p[i] = new double[col];
    }
    p = matrix1;
    double** q = new double* [row];
    for (int i = 0; i < row; i++)
    {
        q[i] = new double[col];
    }
    q = matrix2;
    double** o = new double* [row];
    for (int i = 0; i < row; i++)
    {
        o[i] = new double[col];
    }
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            o[i][j] = p[i][j] + q[i][j] / 1000;
        }
    }
    return o;
}
double** MatrixMult(double** matrix1, double** matrix2, int row1, int col1, int row2, int col2)
{
    double** p = new double* [row1];
    for (int i = 0; i < row1; i++)
    {
        p[i] = new double[col1];
    }
    p = matrix1;

    double** q = new double* [row2];
    for (int i = 0; i < row2; i++)
    {
        q[i] = new double[col2];
    }
    q = matrix2;

    double** o = new double* [row1];
    for (int i = 0; i < row1; i++)
    {
        o[i] = new double[col2];
    }
    for (int i = 0; i < row1; i++)
    {
        for (int j = 0; j < col2; j++)
        {
            o[i][j] = 0;
            for (int k = 0; k < col1; k++)
            {
                o[i][j] += p[i][k] * q[k][j];
            }
        }
    }
    return o;
}
double** Gauss(double** Naa, int row)
{
    int i, j, k;
    double** ma = new double* [1];
    for (int i = 0; i < 1; i++)
    {
        ma[i] = new double[1];
    }
    ma[0][0] = 0;
    double** temp = new double* [1];
    for (int i = 0; i < 1; i++)
    {
        temp[i] = new double[1];
    }
    temp[0][0] = 0;
    //��A����������ʱ����t[R][R]��
    double** t = new double* [row];   //��ʱ����
    for (int i = 0; i < row; i++)
    {
        t[i] = new double[row];
    }

    for (int i = 0; i < row; i++)

    {

        for (j = 0; j < row; j++)

        {

            t[i][j] = Naa[i][j];

        }

    }

    //��ʼ��B����Ϊ��λ��
    double** B = new double* [row];
    for (int i = 0; i < row; i++)
    {
        B[i] = new double[row];
    }
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < row; j++)
        {
            B[i][j] = (i == j) ? (double)1 : 0;
        }
    }

    for (i = 0; i < row; i++)
    {
        //Ѱ����Ԫ
        ma[0][0] = t[i][i];
        k = i;
        for (j = i + 1; j < row; j++)
        {
            if (fabs(t[j][i]) > fabs(ma[0][0]))
            {
                ma[0][0] = t[j][i];

                k = j;
            }
        }
        //�����Ԫ�����в��ǵ�i�У������н���
        if (k != i)
        {
            for (j = 0; j < row; j++)
            {
                temp[0][0] = t[i][j];
                t[i][j] = t[k][j];
                t[k][j] = temp[0][0];
                //B���潻��
                temp[0][0] = B[i][j];
                B[i][j] = B[k][j];
                B[k][j] = temp[0][0];
            }
        }
        //�ж���Ԫ�Ƿ�Ϊ0, ����, �����A�������Ⱦ���,�����������
        if (t[i][i] == 0)
        {
            cout << "There is no inverse matrix!";
            return 0;
        }
        //��ȥA�ĵ�i�г�ȥi������ĸ���Ԫ��
        temp[0][0] = t[i][i];
        for (j = 0; j < row; j++)
        {
            t[i][j] = t[i][j] / (temp[0][0]);        //���Խ����ϵ�Ԫ�ر�Ϊ1
            B[i][j] = B[i][j] / (temp[0][0]);        //�������
        }
        for (j = 0; j < row; j++)        //��0��->��n��
        {
            if (j != i)                //���ǵ�i��
            {
                temp[0][0] = t[j][i];
                for (k = 0; k < row; k++)        //��j��Ԫ�� - i��Ԫ��*j��i��Ԫ��
                {
                    t[j][k] = t[j][k] - (t[i][k] * (temp[0][0]));
                    B[j][k] = B[j][k] - (B[i][k] * (temp[0][0]));
                }
            }
        }
    }
    return B;
}
void output(double** matrix, int row, int col)
{
    double** p = new double* [row];
    for (int i = 0; i < row; i++)
    {
        p[i] = new double[col];
    }
    p = matrix;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            cout << p[i][j] << "  ";
        }
        cout << endl;
    }
}
double** inputq(int row, int col)
{
    double** matrix = new double* [row];
    for (int i = 0; i < row; i++)
    {
        matrix[i] = new double[col];
    }
    cout << "���������" << endl;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            matrix[i][j] = 0;
        }
    }
    for (int i = 0; i < row; i++)
    {
        cin >> matrix[i][i];
    }
    return matrix;
}
double** input(int row, int col)
{
    double** matrix = new double* [row];
    for (int i = 0; i < row; i++)
    {
        matrix[i] = new double[col];
    }
    cout << "���������" << endl;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            cin >> matrix[i][j];
        }
    }
    return matrix;
}
