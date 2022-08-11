// position.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <cassert>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <iomanip>

#include <READ.h>
#include <matrix.h>

//WGS - 84基本参数
const double a = 6378137;
const double f = 1 / 298.257223563;//基准椭球体扁率
const double Omega_e_Dot = 7.2921151467e-5; //地球自转角速度（rad/s）
const double mu = 3.986004418e14;//地球引力常数GM（m^3/s^2）
const double c = 2.99792458e8 ;//真空中的光速（m/s）
//特别说明：没有特别备注的地方角均采用弧度制
const double PI = 3.1415926;



//命名空间
using namespace std;

//对象：卫星，接收机
struct satellite
{
    char name;
    double X;
    double Y;
    double Z;
    //卫星位置计算过程中部分参数
    double A;//轨道长轴半径
    double E;//偏近点角
    int Time;//这里的时间为广播星历的参考时间
    double pseudo;
    satellite():name('G'), X(0), Y(0), Z(0), Time(0), pseudo(0) {}//构造函数
    void disply()
    {
        cout << "satellite name:" << name << endl;
        cout << "X:" <<X<<"  " << "Y:" <<Y << "  " << "Z:" << Z<< endl;
        cout << "pseudo:" << pseudo<<endl;
    }
}; 
satellite s1, s2, s3, s4;
struct receiver
{
    char name[10];
    double X;
    double Y;
    double Z;
    double T;
    void disply()
    {
        cout << "receiver name:" << name << endl;
        cout << "X:" << X << "  " << "Y:" << Y << "  " << "Z:" << Z << "T:" << T << endl;
    }
};
receiver r1={
    "DUAN",
    0,
    0,
    0,
    0
};









int main()
{
    cout.setf(ios::fixed);//控制结果输出位数
    cout.precision(6);
    cout << "程序开始——————————————————————————————————————————";

    //星历数据格式重排
    vector<double> dataN_temp,dataO_temp;
    dataN_temp = readN303d(8, 1575, " ", "D://个人数据//编程//OnePointPostion//HKSL00HKG_R_20220620000_01D_GNtest.20n");
    vector< vector<double> > dataN; //二维动态数组,自定义标准格式的星历数据
    cout << dataN_temp.size()/35 << endl;
    int k = 0;//计数器
    for (int i = 0; i < dataN_temp.size() / 35; i++)
    {
        vector<double> temp;
        for (int j = 0; j < 35; j++)
        {
            k = i * 35 + j;
            temp.push_back(dataN_temp[k]) ;
        }
        dataN.push_back(temp);
    }
    cout <<"总计星历数据量："<<k << endl;
    cout << "星历数据读取完成！总数为：" << dataN_temp.size() / 35 << endl;
    //for (int i = 0; i < dataN_temp.size() / 35; i++)
    //{
    //    nnnnn = Time(dataN[i][1], dataN[i][2], dataN[i][3], dataN[i][4], dataN[i][5], dataN[i][6]);
    //    cout << "time_n" << nnnnn<<endl;
    //    for (int j = 0; j <7; j++)
    //    {
    //        cout << dataN[i][j] << " ";
    //    }
    //    cout << endl;
    //}

    cout << endl;


    //观测值数据格式重排(第一列卫星编号，第二列伪距观测值)
    dataO_temp = readO303d(40287, 40326, " ", "D://个人数据//编程//OnePointPostion//HKSL00HKG_R_20220620000_01D_30S_MO.20o");
    double dataO_time[6];//年月日时分秒
    vector< vector<double> > dataO;
    cout << "观测值数量"<< dataO_temp.size() <<endl;
    for (int i = 0; i < 6; i++)
    {
        dataO_time[i] = dataO_temp[i + 1];
    }
    for (int i = 0; i < (dataO_temp.size() - 9) / 2; i++)
    {
        vector<double> temp;
        for (int j = 0; j < 2; j++)
        {
            temp.push_back(dataO_temp[i*2+j+9]);
        }
        dataO.push_back(temp);
    }
    cout << "该历元数据如下：" << endl;
    for (int i = 0; i < (dataO_temp.size() - 9) / 2; i++)
    {
        cout << dataO[i][0] <<"  " << dataO[i][1] << endl;
    }



    //星历数据与观测值数据的匹配(有问题,仅支持4颗卫星)
    double N[4][35], O[4][2];
    int N_time, O_time;
    double Time(double Y, double M, double D, double H, double m, double s);
    k = 0;//计数器置零
    int k1 = 0;//辅助跳出循环
    O_time = Time(dataO_time[0], dataO_time[1], dataO_time[2], dataO_time[3], dataO_time[4], dataO_time[5]);//历元时刻的GPS秒
    O_time = O_time+18;//跳秒？？，此问题一直没搞懂
    cout << "timeo" << O_time << endl;
    for (int i = 0; i < (dataO_temp.size() - 9) / 2; i++)
    {
        for (int j = 0; j < dataN_temp.size() / 35; j++)
        {
            N_time= Time(dataN[j][1], dataN[j][2], dataN[j][3], dataN[j][4], dataN[j][5], dataN[j][6]);//这个需要跳秒吗？
            if (dataO[i][0] == dataN[j][0]&&abs(O_time- N_time)<=3600)
            {
               
                for (int l = 0; l < 35; l++)
                {
                    N[k][l] = dataN[j][l];
                    

                }
                
                O[k][0] = dataO[i][0];
                O[k][1] = dataO[i][1];
                k++;
                if (k >3)
                {
                   k1 = 1;
                   break;
                }
            }
        }
        if (k1 == 1)
        {
            break;
        }
    }
    if (k < 2)//逻辑还有问题，暂留，只适用于一个历元
    {
        cout << "该历元数据不足，无法进行解算" << endl;
        return 0;
    }
    cout << "匹配出的星历数据如下：" << endl;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 35; j++)
        {
            cout << N[i][j] << " ";
        }
        cout << endl;
    }
    cout << "匹配出的观测值数据如下：" << endl;
    cout << "时间：" ;
    for (int i = 0; i < 6; i++)
    {
        cout << dataO_time[i] << " ";
    }
    cout << endl;
    cout << "观测值如下：" << endl;
    for (int i = 0; i < 4; i++)
    {
        cout<< O[i][0] << " " << O[i][1]<<endl;
    }

    //计算卫星位置
    void satellite_xyz(double* N, double* O, struct satellite& s);  //声明函数
    void Earth_autobiographical_coorection(double Omega, double tsi, struct satellite& s);
    double elevating_angle(struct satellite& s, double X, double Y, double Z);
    double Azimuth(struct satellite& s, double X, double Y, double Z);
    double Satellite_clock_difference(double* N, double* O, struct satellite& s);
    double ionospheric_delay_coorrction(double E, double A, double GPS_time, double X, double Y, double Z);
    double N_temp[35], O_temp[9];
    double Tsi,tsi, tsi1,dtr,dts,Rsi;//概略时刻，直接求得的卫星信号传播时间，由星站件距离求得的卫星信号传播时间，接收机钟差，卫星钟差，几何距离
    double dtrop, EA;//对流层延迟改正，EA代表高度角，利用简化版的Hopfield模型计算
    double dIon, A;     //电离层延迟改正，A代表方位角，dIon代表电离层延迟   
    double remainder[4]; //卫星在观测方程式中的余数项
    double b[4][4];//卫星的方向余弦
    dtr = r1.T;
    for (int ii = 0;; ii++)
    {
        //卫星1
        for (int i = 0; i < 35; i++)//星历数据
        {
            N_temp[i] = N[0][i];
        }
        for (int i = 0; i < 6; i++)//历元时刻
        {
            O_temp[i] = dataO_time[i];
        }
        O_temp[6] = O[0][0];//卫星编号
        O_temp[7] = O[0][1];//伪距
            //计算卫星的信号发射的概略时刻
        O_temp[8] = O_time - O_temp[7] / c;//卫星的信号发送时刻,未加入卫星钟差改正         
        cout << "信号概略发射时刻（未进行卫星钟差改正）" << O_temp[8] << endl;//test
        dts= Satellite_clock_difference(N_temp, O_temp, s1);//计算卫星钟差
        cout << "卫星钟差1:  " <<dts <<endl;//test
        tsi = O_temp[7] / c + dts;//这样实际上卫星在计算卫星钟差时是使用的未经任何改正的概略信号发射时刻
        for (int i = 0;; i++)
        {

            cout << "信号传播时间" <<tsi<< endl;//test
            Tsi = O_time - tsi;
            cout << "信号概略发射时刻" <<Tsi<< endl;//test
            O_temp[8] = Tsi;//卫星的信号发送时刻
            dts = Satellite_clock_difference(N_temp, O_temp, s1);//计算卫星钟差
            cout << "卫星钟差2:  " << dts << endl;//test
            satellite_xyz(N_temp, O_temp, s1);//卫星在Tsi时刻的位置。  数组做函数参数，实际上是在传递数组首位元素地址的指针
            s1.disply();//test

            Earth_autobiographical_coorection(Omega_e_Dot, tsi, s1);//卫星在地球自传改正后的位置
            Rsi = sqrt((s1.X - r1.X) * (s1.X - r1.X) + (s1.Y - r1.Y) * (s1.Y - r1.Y) + (s1.Z - r1.Z) * (s1.Z - r1.Z));//卫星与测站间的几何距离
            tsi1 = Rsi / c;
            cout << "信号传播时间验证测试：" << tsi1 << "  " << tsi << endl;
            if (abs(tsi1 - tsi) < 0.0000001)
            {
                break;
            }
            tsi = tsi1;
        }
        b[0][0] = (r1.X - s1.X) / Rsi;
        b[0][1] = (r1.Y - s1.Y) / Rsi;
        b[0][2] = (r1.Z - s1.Z) / Rsi;
        b[0][3] = 1;
            //对流层延迟改正，EA代表高度角，利用简化版的Hopfield模型计算
        EA=elevating_angle(s1, -2393382.4157,5393861.1745,2412592.4105);
        dtrop = 2.47 / (sin(EA) + 0.0121);
        cout << "高度角为：" << EA << "  对流层延迟为：" << dtrop << endl;

            //电离层延迟改正,GPS_time是用O_temp[8]吗？
        A=Azimuth(s1, -2393382.4157, 5393861.1745, 2412592.4105);
        dIon = ionospheric_delay_coorrction(EA, A, O_temp[8], -2393382.4157, 5393861.1745, 2412592.4105);
        cout<< "电离层延迟为：" << dIon << endl;

        remainder[0] = O_temp[7] - r1.T - Rsi + c * dts - dtrop-dIon;//到底需不需要减接收机钟差，师兄给的文档不减，自己找的文档要减
        s1.disply();

        //卫星2
        for (int i = 0; i < 35; i++)//星历数据
        {
            N_temp[i] = N[1][i];
        }
        for (int i = 0; i < 6; i++)//历元时刻
        {
            O_temp[i] = dataO_time[i];
        }
        O_temp[6] = O[1][0];//卫星编号
        O_temp[7] = O[1][1];//伪距
            //计算卫星的信号发射的概略时刻
        O_temp[8] = O_time - O_temp[7] / c;//卫星的信号发送时刻,未加入卫星钟差改正                   
        dts = Satellite_clock_difference(N_temp, O_temp, s2);//计算卫星钟差
        tsi = O_temp[7] / c + dts;//这样实际上卫星在计算卫星钟差时是使用的未经任何改正的概略信号发射时刻
        for (int i = 0;; i++)
        {

            Tsi = O_time - tsi;
            O_temp[8] = Tsi;//卫星的信号发送时刻
            dts = Satellite_clock_difference(N_temp, O_temp, s2);//计算卫星钟差
            satellite_xyz(N_temp, O_temp, s2);//卫星在Tsi时刻的位置。  数组做函数参数，实际上是在传递数组首位元素地址的指针
            Earth_autobiographical_coorection(Omega_e_Dot, tsi, s2);//卫星在地球自传改正后的位置
            Rsi = sqrt((s2.X - r1.X) * (s2.X - r1.X) + (s2.Y - r1.Y) * (s2.Y - r1.Y) + (s2.Z - r1.Z) * (s2.Z - r1.Z));//卫星与测站间的几何距离
            tsi1 = Rsi / c;
            if (abs(tsi1 - tsi) < 0.0000001)
            {
                break;
            }
            tsi = tsi1;
        }
        b[1][0] = (r1.X - s2.X) / Rsi;
        b[1][1] = (r1.Y - s2.Y) / Rsi;
        b[1][2] = (r1.Z - s2.Z) / Rsi;
        b[1][3] = 1;
            //对流层延迟改正，EA代表高度角，利用简化版的Hopfield模型计算
        EA = elevating_angle(s2, -2393382.4157, 5393861.1745, 2412592.4105);
        dtrop = 2.47 / (sin(EA) + 0.0121);
        cout << "高度角为：" << EA << "  对流层延迟为：" << dtrop << endl;

        //电离层延迟改正,GPS_time是用O_temp[8]吗？
        A = Azimuth(s2, -2393382.4157, 5393861.1745, 2412592.4105);
        dIon = ionospheric_delay_coorrction(EA, A, O_temp[8], -2393382.4157, 5393861.1745, 2412592.4105);
        cout << "电离层延迟为：" << dIon << endl;

        remainder[1] = O_temp[7] - r1.T - Rsi + c * dts - dtrop - dIon;
        s2.disply();

        //卫星3
        for (int i = 0; i < 35; i++)//星历数据
        {
            N_temp[i] = N[2][i];
        }
        for (int i = 0; i < 6; i++)//历元时刻
        {
            O_temp[i] = dataO_time[i];
        }
        O_temp[6] = O[2][0];//卫星编号
        O_temp[7] = O[2][1];//伪距
            //计算卫星的信号发射的概略时刻
        O_temp[8] = O_time - O_temp[7] / c;//卫星的信号发送时刻,未加入卫星钟差改正                   
        dts = Satellite_clock_difference(N_temp, O_temp, s3);//计算卫星钟差
        tsi = O_temp[7] / c + dts;//这样实际上卫星在计算卫星钟差时是使用的未经任何改正的概略信号发射时刻
        for (int i = 0;; i++)
        {

            Tsi = O_time - tsi;
            O_temp[8] = Tsi;//卫星的信号发送时刻
            dts = Satellite_clock_difference(N_temp, O_temp, s3);//计算卫星钟差
            satellite_xyz(N_temp, O_temp, s3);//卫星在Tsi时刻的位置。  数组做函数参数，实际上是在传递数组首位元素地址的指针
            Earth_autobiographical_coorection(Omega_e_Dot, tsi, s3);//卫星在地球自传改正后的位置
            Rsi = sqrt((s3.X - r1.X) * (s3.X - r1.X) + (s3.Y - r1.Y) * (s3.Y - r1.Y) + (s3.Z - r1.Z) * (s3.Z - r1.Z));//卫星与测站间的几何距离
            tsi1 = Rsi / c;
            if (abs(tsi1 - tsi) < 0.0000001)
            {
                break;
            }
            tsi = tsi1;
        }
        b[2][0] = (r1.X - s3.X) / Rsi;
        b[2][1] = (r1.Y - s3.Y) / Rsi;
        b[2][2] = (r1.Z - s3.Z) / Rsi;
        b[2][3] = 1;
            //对流层延迟改正，EA代表高度角，利用简化版的Hopfield模型计算
        EA = elevating_angle(s3, -2393382.4157, 5393861.1745, 2412592.4105);
        dtrop = 2.47 / (sin(EA) + 0.0121);
        cout << "高度角为：" << EA << "  对流层延迟为：" << dtrop << endl;

        //电离层延迟改正,GPS_time是用O_temp[8]吗？
        A = Azimuth(s3, -2393382.4157, 5393861.1745, 2412592.4105);
        dIon = ionospheric_delay_coorrction(EA, A, O_temp[8], -2393382.4157, 5393861.1745, 2412592.4105);
        cout << "电离层延迟为：" << dIon << endl;

        remainder[2] = O_temp[7] - r1.T - Rsi + c * dts - dtrop - dIon;
        s3.disply();

        //卫星4
        for (int i = 0; i < 35; i++)//星历数据
        {
            N_temp[i] = N[3][i];
        }
        for (int i = 0; i < 6; i++)//历元时刻
        {
            O_temp[i] = dataO_time[i];
        }
        O_temp[6] = O[3][0];//卫星编号
        O_temp[7] = O[3][1];//伪距
            //计算卫星的信号发射的概略时刻
        O_temp[8] = O_time - O_temp[7] / c;//卫星的信号发送时刻,未加入卫星钟差改正                   
        dts = Satellite_clock_difference(N_temp, O_temp, s4);//计算卫星钟差
        tsi = O_temp[7] / c + dts;//这样实际上卫星在计算卫星钟差时是使用的未经任何改正的概略信号发射时刻
        for (int i = 0;; i++)
        {

            Tsi = O_time - tsi;
            O_temp[8] = Tsi;//卫星的信号发送时刻
            dts = Satellite_clock_difference(N_temp, O_temp, s4);//计算卫星钟差
            satellite_xyz(N_temp, O_temp, s4);//卫星在Tsi时刻的位置。  数组做函数参数，实际上是在传递数组首位元素地址的指针
            Earth_autobiographical_coorection(Omega_e_Dot, tsi, s4);//卫星在地球自传改正后的位置
            Rsi = sqrt((s4.X - r1.X) * (s4.X - r1.X) + (s4.Y - r1.Y) * (s4.Y - r1.Y) + (s4.Z - r1.Z) * (s4.Z - r1.Z));//卫星与测站间的几何距离
            tsi1 = Rsi / c;
            if (abs(tsi1 - tsi) < 0.0000001)
            {
                break;
            }
            tsi = tsi1;
        }
        b[3][0] = (r1.X - s4.X) / Rsi;
        b[3][1] = (r1.Y - s4.Y) / Rsi;
        b[3][2] = (r1.Z - s4.Z) / Rsi;
        b[3][3] = 1;
            //对流层延迟改正，EA代表高度角，利用简化版的Hopfield模型计算
        EA = elevating_angle(s4, -2393382.4157, 5393861.1745, 2412592.4105);
        dtrop = 2.47 / (sin(EA) + 0.0121);
        cout << "高度角为：" << EA << "  对流层延迟为：" << dtrop << endl;

        //电离层延迟改正,GPS_time是用O_temp[8]吗？
        A = Azimuth(s4, -2393382.4157, 5393861.1745, 2412592.4105);
        dIon = ionospheric_delay_coorrction(EA, A, O_temp[8], -2393382.4157, 5393861.1745, 2412592.4105);
        cout << "电离层延迟为：" << dIon << endl;

        remainder[3] = O_temp[7] - r1.T - Rsi + c * dts - dtrop - dIon;
        s4.disply();































        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                cout << b[i][j] << " ";
            }
            cout << endl;
        }
        for (int i = 0; i < 4; i++)
        {
            cout << remainder[i] << " ";
        }
        cout << endl;
        double p[4];
        for (int i = 0; i < 4; i++)
        {
            p[i] = 1;
        }
        //double


        //平差计算
        //double** x, ** BT, ** Nbb, ** nNbb, ** w, ** V, ** VT, ** VTP, ** PVV, ** V1, ** BTP, ** pczL, ** pczX, ** GCzuc, ** GCzuc1;
        double** x, ** BT, ** Nbb, ** w, ** BTP, ** pczX;
        int row1 = 4, col1 = 4, row2 = 4, col2 = 4, row3 = 4, col3 = 1;
        ofstream outfile("Result.txt", ios::app);
        //输入B
        double** B = new double* [row1];
        for (int i = 0; i < row1; i++)
        {
            B[i] = new double[col1];
        }
        for (int i = 0; i < row1; i++)
        {
            for (int j = 0; j < col1; j++)
            {
                B[i][j] = b[i][j];
            }
        }
        cout << "B矩阵为" << endl;
        output(B, row1, col1);
        //B=input(row1,col1);

        //输入P
        double** P = new double* [row2];
        for (int i = 0; i < row2; i++)
        {
            P[i] = new double[col2];
        }
        for (int i = 0; i < row2; i++)
        {
            for (int j = 0; j < col2; j++)
            {
                if (i == j)
                {
                    P[i][j] = p[i];
                }
                else
                {
                    P[i][j] = 0;
                }
            }
        }
        cout << "P矩阵为" << endl;
        output(P, row2, col2);
        //P=inputq(row2,col2);

        //输入L
        double** L = new double* [row3];
        for (int i = 0; i < row3; i++)
        {
            L[i] = new double[col3];
        }
        for (int i = 0; i < row3; i++)
        {
            for (int j = 0; j < col3; j++)//(L矩阵一定是个列向量，所以col3一定只能为1)
            {
                L[i][j] = remainder[i];
            }
        }
        cout << "L矩阵为" << endl;
        output(L, row3, col3);
        //L=input(row3,col3);

        //输入参数估值
        double** pczX1 = new double* [row3];
        for (int i = 0; i < row3; i++)
        {
            pczX1[i] = new double[col3];
        }
        pczX1[0][0] = r1.X; pczX1[1][0] = r1.Y; pczX1[2][0] = r1.Z; pczX1[3][0] = r1.T;


        BT = MatrixTransposition(B, row1, col1);
        BTP = MatrixMult(BT, P, col1, row1, row2, col2);
        Nbb = MatrixMult(BTP, B, col1, col2, row1, col1);
        cout << "矩阵Nbb为；" << endl;
        output(Nbb, col1, col1);

        w = MatrixMult(BTP, L, col1, col2, row3, col3);
        Nbb = Gauss(Nbb, col1);
        x = MatrixMult(Nbb, w, col1, col1, col1, col3);
        cout << "参数改正数x为；" << endl;
        output(x, col1, col3);

        pczX = MatrixAdd(pczX1, x, col1, col3);
        cout << "参数平差值为；" << endl;
        output(pczX, col1, col3);

        delete x;
        delete BT;
        delete[] B;
        delete[] P;
        delete[] L;
        delete Nbb;
        delete w;
        delete BTP;

        if (abs(r1.X- pczX[0][0])<0.1&& abs(r1.Y - pczX[1][0]) < 0.1&& abs(r1.Z - pczX[2][0]) < 0.1 && abs(r1.T - pczX[3][0]) < 0.1)  
        {
            break;
        }
        r1.X = pczX[0][0]; r1.Y = pczX[1][0]; r1.Z = pczX[2][0]; r1.T = pczX[3][0];

    }












    //    //卫星2
    //for (int i = 0; i < 36; i++)
    //{
    //    N_temp[i] = N[1][i];
    //}
    //for (int i = 0; i < 6; i++)
    //{
    //    O_temp[i] = dataO_time[i];
    //}
    //O_temp[6] = O[1][0];
    //O_temp[7] = O[1][1];
    //satellite_xyz(N_temp, O_temp, s2);//数组做函数参数，实际上是在传递数组首位元素地址的指针
    //          //卫星3
    //for (int i = 0; i < 36; i++)
    //{
    //    N_temp[i] = N[2][i];
    //}
    //for (int i = 0; i < 6; i++)
    //{
    //    O_temp[i] = dataO_time[i];
    //}
    //O_temp[6] = O[2][0];
    //O_temp[7] = O[2][1];
    //satellite_xyz(N_temp, O_temp, s3);//数组做函数参数，实际上是在传递数组首位元素地址的指针
    //              //卫星4
    //for (int i = 0; i < 36; i++)
    //{
    //    N_temp[i] = N[3][i];
    //}
    //for (int i = 0; i < 6; i++)
    //{
    //    O_temp[i] = dataO_time[i];
    //}
    //O_temp[6] = O[3][0];
    //O_temp[7] = O[3][1];
    //satellite_xyz(N_temp, O_temp, s4);//数组做函数参数，实际上是在传递数组首位元素地址的指针

  





    //double iiiii;
    //iiiii = Time(2022, 7,3, 17, 9, 46);
    //cout << "当前GPS秒为：" << iiiii << endl;
    system("pause");
    return 0;
}






//子函数  平差已验证

/*空间直角坐标转大地坐标 WGS-84*/ //已验证,输出为角度制
bool XYZToBLH(double X, double Y, double Z, double BLH[])
{
    //椭球参数,默认WGS84椭球
    double a = 6378137.000;
    double e2 = 0.00669437999013;

    double N = 0.0;
    double B, L, H;
    double deltaZ = 0.0;
    //初始化deltaZ
    deltaZ = e2 * Z;
    //中间变量temp
    double temp1 = 0.0;
    double temp2 = 0.0;

    L = atan2(Y, X);

    //迭代法1：用B来决定是否继续迭代
    ///*do{
    //	B=atan((Z+deltaZ)/sqrt(X*X+Y*Y));
    //	temp1= (Z+deltaZ)/sqrt(X*X+Y*Y+(Z+deltaZ)*(Z+deltaZ));
    //	temp2= sin(B);
    //	N= a/(sqrt(1-e2*sin(B)*sin(B)));
    //	deltaZ= N*e2*sin(B);
    //}while(fabs(temp1-temp2)>0.00001);*/

    //迭代法2:用deltaZ来决定是否继续迭代
    do {
        deltaZ = temp1;
        B = atan((Z + deltaZ) / sqrt(X * X + Y * Y));
        N = a / (sqrt(1 - e2 * sin(B) * sin(B)));
        temp1 = N * e2 * sin(B);
    } while (fabs(temp1 - deltaZ) > 0.00000001);

    H = sqrt(X * X + Y * Y + (Z + deltaZ) * (Z + deltaZ)) - N;

    BLH[0] = 180 * B / PI;
    BLH[1] = 180 * L / PI;
    BLH[2] = H;

    return true;
}

/*大地坐标转空间直角坐标 WGS-84*/ //已验证,输入为角度制
bool BLHToXYZ(double BLH[], double XYZ[])
{
    //椭球参数,默认WGS84椭球
    double a = 6378137.000;
    double e2 = 0.00669437999013;

    double N = 0.0;
    double B, L, H, X, Y, Z;
    //将纬度B，经度L的单位由度转换为弧度
    B = PI * BLH[0] / 180;
    L = PI * BLH[1] / 180;
    H = BLH[2];

    N = a / sqrt(1 - e2 * (sin(B) * sin(B)));
    X = (N + H) * cos(B) * cos(L);
    Y = (N + H) * cos(B) * sin(L);
    Z = (N * (1 - e2) + H) * sin(B);

    XYZ[0] = X;
    XYZ[1] = Y;
    XYZ[2] = Z;

    return true;
}

/*GPS周秒计算*/   //已验证
double Time(double Y, double M, double D, double H, double m, double s)
{   
     /*
    参数Y：年
    参数M：月
    参数D：日
    参数H：时
    参数m：分
    参数s：秒
    */
    double y, m0;
    double JD;//儒略日
    double GPS_week, GPS_second;
    if (M <= 2)
    {
        y = Y - 1;
        m0 = M + 12;
    }
    else
    {
        y = Y;
        m0 = M;
    }
    JD = floor(365.25 * y) + floor(30.6001 * (m0 + 1)) + D + (H+m/60+s/3600) / 24 + 1720981.5;//通用时转换到儒略日
    GPS_week = floor((JD - 2444244.5)/ 7);
    GPS_second = (JD - 2444244.5) * 3600 * 24 - GPS_week * 3600 * 24 * 7;


    
    return GPS_second;

}

/*卫星位置计算  卫星在地心坐标系下的坐标*/
void satellite_xyz(double *N, double *O, struct satellite &s)//数组做函数参数，实际上是在传递数组首位元素地址的指针
{
    /*
    参数*N：星历数据（数组）
    参数*O：观测值数据（数组）
    参数&s：卫星坐标
    */
    //计算轨道长半轴
    double A;
    A = N[17] * N[17];
    s.A = A;
    //计算卫星运动的平均角速度n
    double n;
    n = sqrt(mu/ (A * A * A)) + N[12];
    cout << "卫星运动的平均角速度n=" << n << endl;
    //计算观测瞬间卫星的平近点角M, t为观测瞬间GPS周内的秒数
    double t,tk;
    double M;
    //double Time(double Y, double M, double D, double H);
    //t = Time(O[1], O[2], O[3], O[4]);
    t = O[8];
    tk = t - N[18];
    if (tk > 302400)
    {
        tk = tk - 604800;
    }
    if (tk < -302400)
    {
        tk = tk + 604800;
    }
    M = N[13] + n * (tk);
    cout << "平近点角M=" << M << endl;
    double E_temp = M;
    double E;
    for (int i = 0;; i++)
    {
        E = M +N[15] * sin(E_temp);
        if (abs(E_temp - E) < 0.000000000001)
        {
            break;
        }
        E_temp = E;
    }
    s.E = E;
    cout << "偏近点角E=" << E << endl;
    //计算真近点角f(要分别讨论在不同象限中的情况)
    double f,cosf,sinf;
    //f = atan((sqrt(1 - N[15] * N[15]) * sin(E)) / (cos(E) - N[15]));  //这样需讨论象限问题，用atan2则将结果限制在了 -PI~PI
    
    cosf = (cos(E) - N[15]) / (1- N[15]* cos(E));
    sinf = (sqrt(1 - N[15] * N[15]) * sin(E)) / (1 - N[15] * cos(E));
    f = atan2(sinf,cosf);

    cout << "真近点角f=" << f << endl;

    //计算升交角距u1
    double u1;
    u1 = f + N[24];
    cout << "升交角距u1=" << f << endl;
    //计算摄动改正项d_u, d_r, d_i
    double d_u, d_r, d_i;
    d_u = N[14] * cos(2 * u1) + N[16] * sin(2 * u1);
    d_r = N[23] * cos(2 * u1) + N[11] * sin(2 * u1);
    d_i = N[19] * cos(2 * u1) + N[21] * sin(2 * u1);
    //进行摄动改正
    double u, r, i;
    u = u1 + d_u;
    r = A * (1 - N[15] * cos(E)) + d_r;
    i = N[22] + d_i + N[26] * tk;
    //计算卫星在轨道面坐标系中的位置
    double x, y;
    x = r * cos(u);
    y = r * sin(u);
    //计算观测瞬间升交点的经度L, GAST(week)为观测瞬间所在周的开始时刻（星期日0时）的格林尼治恒星时
    double L;
    L = N[20] + (N[25] - Omega_e_Dot) * t - N[25] * N[18];
    //计算卫星在瞬时地球坐标系中的位置
    s.X = x * cos(L) - y * cos(i) * sin(L);
    s.Y = x * sin(L) + y * cos(i) * cos(L);
    s.Z = y * sin(i);
   /* cout <<"卫星坐标：" << s.X << " " << s.Y << " " << s.Z << endl;*/
}

/*卫星高度角计算*/  //输出高度角为弧度制    方位角和距离的计算方法与高度角类似
double elevating_angle(struct satellite& s, double X, double Y, double Z)
{
    double Xs, Ys, Zs, Xp, Yp, Zp;
    double delta_X, delta_Y, delta_Z;
    double N, E, U, B, L, H, r, EA;
    Xs = s.X;
    Ys = s.Y;
    Zs = s.Z;
    Xp = X;
    Yp = Y;
    Zp = Z;
    double BLH[3];
    XYZToBLH(X, Y, Z, BLH);//计算出的经纬度为角度制  ,以接收机位置为坐标原点建立站心平面直角坐标系
    B = BLH[0] * PI / 180; L = BLH[1] * PI / 180; H = BLH[2] * PI / 180;//角度制转弧度制
    cout << "B: " << BLH[0] << " L: " << BLH[1] << " H: " << BLH[2] << endl;
    delta_X = Xs - Xp;
    delta_Y = Ys - Yp;
    delta_Z = Zs - Zp;
    N = -sin(B) * cos(L) * delta_X - sin(B) * sin(L) * delta_Y + cos(B) * delta_Z;
    E = -sin(L) * delta_X + cos(L) * delta_Y;
    U = cos(B) * cos(L) * delta_X + cos(B) * sin(L) * delta_Y + sin(B) * delta_Z;
    r = sqrt(N * N + E * E + U * U);
    EA = asin(U / r);
    return EA;
}

/*卫星方位角计算*/  //输出方位角为弧度制    高度角和距离的计算方法与高度角类似
double Azimuth(struct satellite& s, double X, double Y, double Z)
{
    double Xs, Ys, Zs, Xp, Yp, Zp;
    double delta_X, delta_Y, delta_Z;
    double N, E, U, B, L, H, A;
    Xs = s.X;
    Ys = s.Y;
    Zs = s.Z;
    Xp = X;
    Yp = Y;
    Zp = Z;
    double BLH[3];
    XYZToBLH(X, Y, Z, BLH);//计算出的经纬度为角度制  ,以接收机位置为坐标原点建立站心平面直角坐标系
    B = BLH[0] * PI / 180; L = BLH[1] * PI / 180; H = BLH[2] * PI / 180;//角度制转弧度制
    cout << "B: " << BLH[0] << " L: " << BLH[1] << " H: " << BLH[2] << endl;//test
    delta_X = Xs - Xp;
    delta_Y = Ys - Yp;
    delta_Z = Zs - Zp;
    N = -sin(B) * cos(L) * delta_X - sin(B) * sin(L) * delta_Y + cos(B) * delta_Z;
    E = -sin(L) * delta_X + cos(L) * delta_Y;
    U = cos(B) * cos(L) * delta_X + cos(B) * sin(L) * delta_Y + sin(B) * delta_Z;
    A = atan(E / N);// 想想E/N结果是不是弧度？
    return A;
}

/*地球自传改正*/ 
void Earth_autobiographical_coorection(double Omega, double tsi,struct satellite& s)
{
    /*
    参数Omega：地球自传角速度
    参数tsi：卫星信号传播时间
    参数&s：卫星坐标
    */
    double Xs, Ys, Zs, Coor_Xs, Coor_Ys, Coor_Zs,temp;
    Xs = s.X;
    Ys = s.Y;
    Zs = s.Z;
    temp = Omega * tsi;

    //Coor_Xs = Xs + Ys * temp;
    //Coor_Ys = - Xs * temp + Ys;
    //Coor_Zs = Zs;

    Coor_Xs = Xs * cos(temp) + Ys * sin(temp);
    Coor_Ys = 0 - Xs * sin(temp) + Ys * cos(temp);
    Coor_Zs = Zs;

    s.X = Coor_Xs;
    s.Y = Coor_Ys;
    s.Z = Coor_Zs;
    cout << "地球自传改正完成！" << endl;
}

/*计算卫星钟差*/
double Satellite_clock_difference(double* N, double* O, struct satellite& s)
{
    /*
    参数*N：星历数据（数组）
    参数*O：观测值数据（数组）
    参数&s：卫星坐标
    */
    double tc;						//输入时间和钟差参考时间的差
    double TOC;                     //卫星钟的参考时刻
    double deltaTr;					//相对论效应改正
    double F;

    double E = 0;					//偏近点角
    double E_temp;                  //偏近点角迭代求解过程中的临时
    double tk;						//输入时间和星历参考时间的差

    double satclkerr;				//卫星钟钟差

    //计算轨道长半轴
    double A;
    A = N[17] * N[17];
    s.A = A;
    //计算卫星运动的平均角速度n
    double n;
    n = sqrt(mu / (A * A * A)) + N[12];
    //计算观测瞬间卫星的平近点角M, t为观测瞬间GPS周内的秒数
    double t;
    double M;
    t = O[8];
    tk = t - N[18];
    if (tk > 302400)
    {
        tk = tk - 604800;
    }
    if (tk < -302400)
    {
        tk = tk + 604800;
    }
    cout << "tk" << tk << endl;
    M = N[13] + n * (tk);
    cout << "平近点角M=" << M << endl;
    E_temp = M;
    for (int i = 0;; i++)
    {
        E = M + N[15] * sin(E_temp);
        if (abs(E_temp - E) < 0.000000000001)
        {
            break;
        }
        E_temp = E;
    }
    s.E = E;
    cout << "偏近点角E=" << E << endl;

       
   
    TOC= Time(N[1], N[2], N[3], N[4], N[5], N[6]);
    tc = t - TOC;                                        //tc类似前面的tk（区别在于减toc还是toe）,此处是在外部对观测值的GPS周内秒进行了调整，与PDF上的算例调整位置不同
    if (tc > 302400)
    {
        tc = tc - 604800;
    }
    if (tc < -302400)
    {
        tc = tc + 604800;
    }
    cout << "tc" << tc << endl;
    F = ((-2) * sqrt(1.0 * mu)) / (c * c);
    deltaTr = F * N[15] * sqrt(A) * sin(E);
    satclkerr = N[7] + N[8] * tc + N[9] * tc * tc + deltaTr - N[32];  //* sqrt(s4.A)* sin(s4.E)
    return satclkerr;
}

/*计算电离层延迟*/ 
double ionospheric_delay_coorrction(double E,double A,double GPS_time, double X, double Y, double Z)
{
    double alpha[4],beta[4];
                        //由广播星历给出的电离层改正系数
    double fai;         //地心角
    double B, B1, B2;   //近似地理纬度，穿刺点地理纬度,穿刺点地磁纬度
    double L, L1;       //近似地理经度，穿刺点地理经度
    double t;           //穿刺点地方时
    double F;           //投影系数
    double dIon;        //电离层延迟

    alpha[0] = 2.0489e-08; alpha[1] = 0.0000e+00; alpha[2] = -1.1921e-07; alpha[3] = 5.9605e-08;
    beta[0] = 1.2288e+05;  beta[1] = -1.6384e+04; beta[2] = -2.6214e+05;  beta[3] = 6.5536e+04;

    //计算地心角
    fai = 0.00137 / (E + 0.11) - 0.022;
    //计算穿刺点地理纬度
    double BLH[3];
    XYZToBLH(X, Y, Z, BLH);//计算出的经纬度为角度制  ,以接收机位置为坐标原点建立站心平面直角坐标系
    B = BLH[0] * PI / 180; L = BLH[1] * PI / 180;//角度制转弧度制
    B1 = B + fai * cos(A);
    if (B1 > 0.416)
    {
        B1 = 0.416;
    }
    if (B1 < -0.416)
    {
        B1 = -0.416;
    }
    //计算穿刺点地理经度
    L1 = L + (fai * sin(A)) / cos(B1);
    //计算穿刺点地磁纬度
    B2 = B1 + 0.064 * cos(L1 - 1.617);
    //计算穿刺点地方时
    t = 43200 * L1 + GPS_time;
    if (t > 86400)
    {
        t = t - 86400;
    }
    if (t < 0)
    {
        t = t + 86400;
    }
    //计算投影系数
    F = 1.0 + 16.0 * (0.53 - E) * (0.53 - E) * (0.53 - E);
    //计算电离层延迟
    double x,temp1, temp2;
    temp1= temp2 = 0;
    for (int i = 0; i < 4; i++)
    {
        temp1 = temp1 + beta[i] * pow(B2, i);
        temp2 = temp2 + alpha[i] * pow(B2, i);
    }
    x = (2.0 * PI * (t - 50400)) /temp1;
    dIon = F * (5.0e-09 + temp2*(1- pow(x, 2)/2.0+ pow(x, 4)/24.0));

    return dIon;
}













