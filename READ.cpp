#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <cassert>
#include <sstream>
#include <algorithm>
#include <READ.h>
using namespace std;



//���ַ���ָ��λ�ò����Ӵ���vector������Ӧ�ĺ���
string insert(string s1, string s2, int n)
{
    int len1 = s1.length();
    int len2 = s2.length();
    if (len1 < n)
    {
        cout << "����ʧ�ܣ�����λ�ó����ַ������ȣ�" << endl;
        return s1;
    }
    string result;
    for (int i = 0; i < n; i++)
    {
        result = result + s1[i];
    }
    for (int i = 0; i < len2; i++)
    {
        result = result + s2[i];
    }
    for (int i = n; i < len1; i++)
    {
        result = result + s1[i];
    }

    return result;
}

// �ַ����ָ��
// PS: ����"-"�ָ�,Ĭ��"e-"Ϊ��ѧ��������ʽ�����ָ�
// 
//�ַ����ָ��(��һ�ַ��ŷָ�,��֧�ֿ�ѧ������)
//����1 ���ָ���ַ���  ����2 �ָ�ı�־����ո񡢶��ŵȣ�
vector<string> split(string str, string pattern)
{
    string::size_type pos;
    vector<string> result;

    str += pattern;//��չ�ַ����Է������
    int size = str.size();

    for (int i = 0; i < size; i++)
    {
        pos = str.find(pattern, i);
        if (pos < size && (str.substr(i, 1) != pattern))//�ų��������Ⱥ������ָ��ַ������
        {
            std::string s = str.substr(i, pos - i);
            result.push_back(s);
            i = pos + pattern.size() - 1;
        }
    }
    return result;
}
//�ַ����ָ��1(�ո�ָ�,֧�ֿ�ѧ������,�������ǰ�油�ո�)
//����1 ���ָ���ַ���  ����2 �ָ�ı�־���ո񣬶��ţ� ����2 �ָ�ı�־��+ - �ȵȣ�
vector<string> split1(string str, string pattern, string pattern1)
{
    string::size_type pos;
    vector<string> result;
    string str1;
    str += pattern;//��չ�ַ����Է������

    if (str.substr(0, 1) == pattern1)
    {
        str = str.insert(0, pattern);
    }
    int size1 = str.size();
    for (int j = 1; j < size1; j++)
    {
        if (str.substr(j, 1) == pattern1 && str.substr(j-1, 1) != "e") //һ����Ҫ��ӿո�ĵط����࣬һ�㲻�����
        {
            str = str.insert(j, pattern);
            size1 = size1 + 1;
            j = j + 1;//���ﲻ��1�൱����Զ�ڸ���ǰ��ӿո���������ѭ��
        }
    }
    //cout << "����1��" << str.size() <<"  "<< str.max_size()- str. capacity() << endl;
    //cout << "����2��" << str1.size() << "  " << str1.max_size() - str.capacity() << endl;
    //cout << "����3��"<<str << endl;

    int size2 = str.size();

    for (int i = 0; i < size2; i++)
    {
        pos = str.find(pattern, i);
        if (pos < size2 && (str.substr(i, 1) != pattern))//�ų��������Ⱥ������ָ��ַ������
        {
            std::string s = str.substr(i, pos - i);
            result.push_back(s);
            i = pos + pattern.size() - 1;
        }
    }
    return result;
}
////�ַ����ָ����غ���(�����ַ��ŷָpattern2�̶�Ϊ"-")  PS��δ�ɹ�ʵ��
//vector<string> split(string str, string pattern1, string pattern2)
//{
//    string::size_type pos1;
//    string::size_type pos11; //pos11�����ж��Ƿ���Ҫ���ηָ�
//    string::size_type pos2;//�����ַָ���ţ���" "��"-"����ʽ��ͬ
//    vector<string> result;
//    str += pattern1;//��չ�ַ����Է������
//    int size1 = str.size();
//
//    for (int i = 0; i < size1; i++)
//    {
//        pos1 = str.find(pattern1, i);
//        pos11 = str.find(pattern2, i);
//        if (pos1 < size1 && (str.substr(i, 1) != pattern1))//�ų��������Ⱥ������ָ��ַ������
//        {
//            std::string s1 = str.substr(i, pos1 - i);
//
//            if (pos11 < pos1&&pos11!=0)//�ڷָ��1�ָ�õ����Ӵ����Էָ��2���зָ�,��������һ���ַ�Ϊ"-"�����
//            {
//                if (str.substr(pos11 - 1, 1) != "e")
//                {
//                    s1 += pattern2;//��չ�ַ����Է������
//                    int size2 = s1.size();
//
//
//
//                    for (int j = 1; j < size2; j++)
//                    {
//                        pos2 = s1.find(pattern2, j);
//                        if (pos2 < size2 && s1.substr(pos2 - 1, 1) != "e")//�ų��������ȺͿ�ѧ�����������
//                        {
//                            std::string s2 = s1.substr(j-1, pos2 - j+1);
//                            result.push_back(s2);
//                            j = pos2 + pattern2.size();
//                        }
//                    }
//                    i = pos1  + pattern1.size() - 1;//ע���������ѭ��ǰ��s1��������չ
//                }
//            }
// 
//            result.push_back(s1);
//            i = pos1 + pattern1.size() - 1;
//
//
//   
//
//
//        }
//    }
//
//    return result;
//}


vector<double> readN303d(int start, int end, string pattern, string Adress)//��ȡ�㲥�����ļ�
{
    //start:   ��ȡ��ʼ��
    //end;     ��ȡ������
    //Adress:  �ļ���ַ
    //pattern: �ָ��־���ţ�������-��
    //PS:      �ڶ�ȡʱ��ʵ��ÿһ�а��Ŷ���һ�飬ֻ����ת��������ʱֻ��������Ҫ�Ĳ���

    string filename = Adress;
    ifstream ifile(filename.c_str());

    vector<double> data;
    double temp; //�ַ���ת���ֹ����е���ʱ����
    string s;
    vector<string> s1; //vector����������һ��ͨ���±�ֱ�ӷ��ʣ�����ò�Ҫ�������δ֪����
    int k = 1;//�м�����
    if (ifile.is_open())
    {
        while (getline(ifile, s))
        {
            s1 = split1(s, pattern, "-");  //ע����ʱ��ָ����Ϊת���ַ��������\ 
            if (k >= start)//ת��������ʱ����ͷ�ļ�,���ڹ㲥���������Ǳ��ת������ʱ����0����Ϊ����ĸ��
            {
                for (int i = 0; i < s1.size(); i++)
                {
                    /*cout << s1[i] << endl;*/
                    if (s1[i] == "G01")
                    {
                        s1[i] = "101";
                    }
                    if (s1[i] == "G02")
                    {
                        s1[i] = "102";
                    }
                    if (s1[i] == "G03")
                    {
                        s1[i] = "103";
                    }
                    if (s1[i] == "G04")
                    {
                        s1[i] = "104";
                    }
                    if (s1[i] == "G05")
                    {
                        s1[i] = "105";
                    }
                    if (s1[i] == "G06")
                    {
                        s1[i] = "106";
                    }
                    if (s1[i] == "G07")
                    {
                        s1[i] = "107";
                    }
                    if (s1[i] == "G08")
                    {
                        s1[i] = "108";
                    }
                    if (s1[i] == "G09")
                    {
                        s1[i] = "109";
                    }
                    if (s1[i] == "G10")
                    {
                        s1[i] = "110";
                    }
                    if (s1[i] == "G11")
                    {
                        s1[i] = "111";
                    }
                    if (s1[i] == "G12")
                    {
                        s1[i] = "112";
                    }
                    if (s1[i] == "G13")
                    {
                        s1[i] = "113";
                    }
                    if (s1[i] == "G14")
                    {
                        s1[i] = "114";
                    }
                    if (s1[i] == "G15")
                    {
                        s1[i] = "115";
                    }
                    if (s1[i] == "G16")
                    {
                        s1[i] = "116";
                    }
                    if (s1[i] == "G17")
                    {
                        s1[i] = "117";
                    }
                    if (s1[i] == "G18")
                    {
                        s1[i] = "118";
                    }
                    if (s1[i] == "G19")
                    {
                        s1[i] = "119";
                    }
                    if (s1[i] == "G20")
                    {
                        s1[i] = "120";
                    }
                    if (s1[i] == "G21")
                    {
                        s1[i] = "121";
                    }
                    if (s1[i] == "G22")
                    {
                        s1[i] = "122";
                    }
                    if (s1[i] == "G23")
                    {
                        s1[i] = "123";
                    }
                    if (s1[i] == "G24")
                    {
                        s1[i] = "124";
                    }
                    if (s1[i] == "G25")
                    {
                        s1[i] = "125";
                    }
                    if (s1[i] == "G26")
                    {
                        s1[i] = "126";
                    }
                    if (s1[i] == "G27")
                    {
                        s1[i] = "127";
                    }
                    if (s1[i] == "G28")
                    {
                        s1[i] = "128";
                    }
                    if (s1[i] == "G29")
                    {
                        s1[i] = "129";
                    }
                    if (s1[i] == "G30")
                    {
                        s1[i] = "130";
                    }
                    if (s1[i] == "G31")
                    {
                        s1[i] = "131";
                    }
                    if (s1[i] == "G32")
                    {
                        s1[i] = "132";
                    }
                    if (s1[i] == "G33")
                    {
                        s1[i] = "133";
                    }
                    if (s1[i] == "G34")
                    {
                        s1[i] = "134";
                    }
                    if (s1[i] == "G35")
                    {
                        s1[i] = "135";
                    }
                    if (s1[i] == "G36")
                    {
                        s1[i] = "136";
                    }

                    stringstream ss;
                    ss << s1[i];
                    ss >> temp;
                    data.push_back(temp);

                }
            }
            k = k + 1;
            if (k > end)
            {
                break;
            }
        }
    }
    ifile.close();

    cout << "��ȡ�ɹ�" << endl;
    return data;
}

vector<double> readN302(int start, int end, string pattern, string Adress)//��ȡ�㲥�����ļ�
{
    //start:   ��ȡ��ʼ��
    //end;     ��ȡ������
    //Adress:  �ļ���ַ
    //pattern: �ָ��־���ţ�������-��
    //PS:      �ڶ�ȡʱ��ʵ��ÿһ�а��Ŷ���һ�飬ֻ����ת��������ʱֻ��������Ҫ�Ĳ���

    string filename = Adress;
    ifstream ifile(filename.c_str());

    vector<double> data;
    double temp; //�ַ���ת���ֹ����е���ʱ����
    string s;
    vector<string> s1; //vector����������һ��ͨ���±�ֱ�ӷ��ʣ�����ò�Ҫ�������δ֪����
    int k = 1;//�м�����
    if (ifile.is_open())
    {
        while (getline(ifile, s))
        {
            //replace(s.begin(), s.end(), 'D', 'e');//��D�滻��e
            s1 = split1(s, pattern, "-");  //ע����ʱ��ָ����Ϊת���ַ��������\ 
            if (k >= start)//ת��������ʱ����ͷ�ļ�,���ڹ㲥���������Ǳ��ת������ʱ����0����Ϊ����ĸ��
            {
                for (int i = 0; i < s1.size(); i++)
                {
                    /*cout << s1[i] << endl;*/
                    if (s1[i] == "G01")
                    {
                        s1[i] = "101";
                    }
                    if (s1[i] == "G02")
                    {
                        s1[i] = "102";
                    }
                    if (s1[i] == "G03")
                    {
                        s1[i] = "103";
                    }
                    if (s1[i] == "G04")
                    {
                        s1[i] = "104";
                    }
                    if (s1[i] == "G05")
                    {
                        s1[i] = "105";
                    }
                    if (s1[i] == "G06")
                    {
                        s1[i] = "106";
                    }
                    if (s1[i] == "G07")
                    {
                        s1[i] = "107";
                    }
                    if (s1[i] == "G08")
                    {
                        s1[i] = "108";
                    }
                    if (s1[i] == "G09")
                    {
                        s1[i] = "109";
                    }
                    if (s1[i] == "G10")
                    {
                        s1[i] = "110";
                    }
                    if (s1[i] == "G11")
                    {
                        s1[i] = "111";
                    }
                    if (s1[i] == "G12")
                    {
                        s1[i] = "112";
                    }
                    if (s1[i] == "G13")
                    {
                        s1[i] = "113";
                    }
                    if (s1[i] == "G14")
                    {
                        s1[i] = "114";
                    }
                    if (s1[i] == "G15")
                    {
                        s1[i] = "115";
                    }
                    if (s1[i] == "G16")
                    {
                        s1[i] = "116";
                    }
                    if (s1[i] == "G17")
                    {
                        s1[i] = "117";
                    }
                    if (s1[i] == "G18")
                    {
                        s1[i] = "118";
                    }
                    if (s1[i] == "G19")
                    {
                        s1[i] = "119";
                    }
                    if (s1[i] == "G20")
                    {
                        s1[i] = "120";
                    }
                    if (s1[i] == "G21")
                    {
                        s1[i] = "121";
                    }
                    if (s1[i] == "G22")
                    {
                        s1[i] = "122";
                    }
                    if (s1[i] == "G23")
                    {
                        s1[i] = "123";
                    }
                    if (s1[i] == "G24")
                    {
                        s1[i] = "124";
                    }
                    if (s1[i] == "G25")
                    {
                        s1[i] = "125";
                    }
                    if (s1[i] == "G26")
                    {
                        s1[i] = "126";
                    }
                    if (s1[i] == "G27")
                    {
                        s1[i] = "127";
                    }
                    if (s1[i] == "G28")
                    {
                        s1[i] = "128";
                    }
                    if (s1[i] == "G29")
                    {
                        s1[i] = "129";
                    }
                    if (s1[i] == "G30")
                    {
                        s1[i] = "130";
                    }
                    if (s1[i] == "G31")
                    {
                        s1[i] = "131";
                    }
                    if (s1[i] == "G32")
                    {
                        s1[i] = "132";
                    }
                    if (s1[i] == "G33")
                    {
                        s1[i] = "133";
                    }
                    if (s1[i] == "G34")
                    {
                        s1[i] = "134";
                    }
                    if (s1[i] == "G35")
                    {
                        s1[i] = "135";
                    }
                    if (s1[i] == "G36")
                    {
                        s1[i] = "136";
                    }

                    stringstream ss;
                    ss << s1[i];
                    ss >> temp;
                    data.push_back(temp);

                }
            }
            k = k + 1;
            if (k > end)
            {
                break;
            }
        }
    }
    ifile.close();

    cout << "��ȡ�ɹ�" << endl;
    return data;
}

vector<double> readO303d(int start, int end, string pattern, string Adress)//��ȡ�۲�ֵ�ļ�  
{
    //start:   ��ȡ��ʼ��
    //end;     ��ȡ������
    //Adress:  �ļ���ַ
    //pattern: �ָ��־���ţ�������-��
    //PS:      �ڶ�ȡʱ��ʵ��ÿһ�а��Ŷ���һ�飬ֻ����ת��������ʱֻ��������Ҫ�Ĳ���
    //          һ��ֻ�ܶ�ȡһ����Ԫ

    string filename = Adress;
    ifstream ifile(filename.c_str());

    vector<double> data;
    double temp; //�ַ���ת���ֹ����е���ʱ����
    string s;
    vector<string> s1; //vector����������һ��ͨ���±�ֱ�ӷ��ʣ�����ò�Ҫ�������δ֪����
    int k = 1;//�м�����
    if (ifile.is_open())
    {
        while (getline(ifile, s))
        {
            s1 = split1(s, pattern, "-");  //ע����ʱ��ָ����Ϊת���ַ��������\ 

            if (k == start)   //һ��Ҫע�� = �� == ������
            {

                for (int i = 0; i < 9; i++)
                {

                    stringstream ss;
                    ss << s1[i];
                    ss >> temp;
                    data.push_back(temp);

                }
            }

            if (k >start)//ת��������ʱ����ͷ�ļ��͵�һ�У����Ǳ��ת������ʱ����0����Ϊ����ĸ��
            {

                for (int i = 0; i < 2; i++)
                {
                    if (s1[i] == "G01")
                    {
                        s1[i] = "101";
                    }
                    if (s1[i] == "G02")
                    {
                        s1[i] = "102";
                    }
                    if (s1[i] == "G03")
                    {
                        s1[i] = "103";
                    }
                    if (s1[i] == "G04")
                    {
                        s1[i] = "104";
                    }
                    if (s1[i] == "G05")
                    {
                        s1[i] = "105";
                    }
                    if (s1[i] == "G06")
                    {
                        s1[i] = "106";
                    }
                    if (s1[i] == "G07")
                    {
                        s1[i] = "107";
                    }
                    if (s1[i] == "G08")
                    {
                        s1[i] = "108";
                    }
                    if (s1[i] == "G09")
                    {
                        s1[i] = "109";
                    }
                    if (s1[i] == "G10")
                    {
                        s1[i] = "110";
                    }
                    if (s1[i] == "G11")
                    {
                        s1[i] = "111";
                    }
                    if (s1[i] == "G12")
                    {
                        s1[i] = "112";
                    }
                    if (s1[i] == "G13")
                    {
                        s1[i] = "113";
                    }
                    if (s1[i] == "G14")
                    {
                        s1[i] = "114";
                    }
                    if (s1[i] == "G15")
                    {
                        s1[i] = "115";
                    }
                    if (s1[i] == "G16")
                    {
                        s1[i] = "116";
                    }
                    if (s1[i] == "G17")
                    {
                        s1[i] = "117";
                    }
                    if (s1[i] == "G18")
                    {
                        s1[i] = "118";
                    }
                    if (s1[i] == "G19")
                    {
                        s1[i] = "119";
                    }
                    if (s1[i] == "G20")
                    {
                        s1[i] = "120";
                    }
                    if (s1[i] == "G21")
                    {
                        s1[i] = "121";
                    }
                    if (s1[i] == "G22")
                    {
                        s1[i] = "122";
                    }
                    if (s1[i] == "G23")
                    {
                        s1[i] = "123";
                    }
                    if (s1[i] == "G24")
                    {
                        s1[i] = "124";
                    }
                    if (s1[i] == "G25")
                    {
                        s1[i] = "125";
                    }
                    if (s1[i] == "G26")
                    {
                        s1[i] = "126";
                    }
                    if (s1[i] == "G27")
                    {
                        s1[i] = "127";
                    }
                    if (s1[i] == "G28")
                    {
                        s1[i] = "128";
                    }
                    if (s1[i] == "G29")
                    {
                        s1[i] = "129";
                    }
                    if (s1[i] == "G30")
                    {
                        s1[i] = "130";
                    }
                    if (s1[i] == "G31")
                    {
                        s1[i] = "131";
                    }
                    if (s1[i] == "G32")
                    {
                        s1[i] = "132";
                    }
                    if (s1[i] == "G33")
                    {
                        s1[i] = "133";
                    }
                    if (s1[i] == "G34")
                    {
                        s1[i] = "134";
                    }
                    if (s1[i] == "G35")
                    {
                        s1[i] = "135";
                    }
                    if (s1[i] == "G36")
                    {
                        s1[i] = "136";
                    }

                    if (s1[i] == "R01")
                    {
                        s1[i] = "201";
                    }
                    if (s1[i] == "R02")
                    {
                        s1[i] = "202";
                    }
                    if (s1[i] == "R03")
                    {
                        s1[i] = "203";
                    }
                    if (s1[i] == "R04")
                    {
                        s1[i] = "204";
                    }
                    if (s1[i] == "R05")
                    {
                        s1[i] = "205";
                    }
                    if (s1[i] == "R06")
                    {
                        s1[i] = "206";
                    }
                    if (s1[i] == "R07")
                    {
                        s1[i] = "207";
                    }
                    if (s1[i] == "R08")
                    {
                        s1[i] = "208";
                    }
                    if (s1[i] == "R09")
                    {
                        s1[i] = "209";
                    }
                    if (s1[i] == "R10")
                    {
                        s1[i] = "210";
                    }
                    if (s1[i] == "R11")
                    {
                        s1[i] = "211";
                    }
                    if (s1[i] == "R12")
                    {
                        s1[i] = "212";
                    }
                    if (s1[i] == "R13")
                    {
                        s1[i] = "213";
                    }
                    if (s1[i] == "R14")
                    {
                        s1[i] = "214";
                    }
                    if (s1[i] == "R15")
                    {
                        s1[i] = "215";
                    }
                    if (s1[i] == "R16")
                    {
                        s1[i] = "216";
                    }
                    if (s1[i] == "R17")
                    {
                        s1[i] = "217";
                    }
                    if (s1[i] == "R18")
                    {
                        s1[i] = "218";
                    }
                    if (s1[i] == "R19")
                    {
                        s1[i] = "219";
                    }
                    if (s1[i] == "R20")
                    {
                        s1[i] = "220";
                    }
                    if (s1[i] == "R21")
                    {
                        s1[i] = "221";
                    }
                    if (s1[i] == "R22")
                    {
                        s1[i] = "222";
                    }
                    if (s1[i] == "R23")
                    {
                        s1[i] = "223";
                    }
                    if (s1[i] == "R24")
                    {
                        s1[i] = "224";
                    }
                    if (s1[i] == "R25")
                    {
                        s1[i] = "225";
                    }
                    if (s1[i] == "R26")
                    {
                        s1[i] = "226";
                    }
                    if (s1[i] == "R27")
                    {
                        s1[i] = "227";
                    }
                    if (s1[i] == "R28")
                    {
                        s1[i] = "228";
                    }
                    if (s1[i] == "R29")
                    {
                        s1[i] = "229";
                    }
                    if (s1[i] == "R30")
                    {
                        s1[i] = "230";
                    }
                    if (s1[i] == "R31")
                    {
                        s1[i] = "231";
                    }
                    if (s1[i] == "R32")
                    {
                        s1[i] = "232";
                    }
                    if (s1[i] == "R33")
                    {
                        s1[i] = "233";
                    }
                    if (s1[i] == "R34")
                    {
                        s1[i] = "234";
                    }
                    if (s1[i] == "R35")
                    {
                        s1[i] = "235";
                    }
                    if (s1[i] == "R36")
                    {
                        s1[i] = "236";
                    }

                    if (s1[i] == "C01")
                    {
                        s1[i] = "301";
                    }
                    if (s1[i] == "C02")
                    {
                        s1[i] = "302";
                    }
                    if (s1[i] == "C03")
                    {
                        s1[i] = "303";
                    }
                    if (s1[i] == "C04")
                    {
                        s1[i] = "304";
                    }
                    if (s1[i] == "C05")
                    {
                        s1[i] = "305";
                    }
                    if (s1[i] == "C06")
                    {
                        s1[i] = "306";
                    }
                    if (s1[i] == "C07")
                    {
                        s1[i] = "307";
                    }
                    if (s1[i] == "C08")
                    {
                        s1[i] = "308";
                    }
                    if (s1[i] == "C09")
                    {
                        s1[i] = "309";
                    }
                    if (s1[i] == "C10")
                    {
                        s1[i] = "310";
                    }
                    if (s1[i] == "C11")
                    {
                        s1[i] = "311";
                    }
                    if (s1[i] == "C12")
                    {
                        s1[i] = "312";
                    }
                    if (s1[i] == "C13")
                    {
                        s1[i] = "313";
                    }
                    if (s1[i] == "C14")
                    {
                        s1[i] = "314";
                    }
                    if (s1[i] == "C15")
                    {
                        s1[i] = "315";
                    }
                    if (s1[i] == "C16")
                    {
                        s1[i] = "316";
                    }
                    if (s1[i] == "C17")
                    {
                        s1[i] = "317";
                    }
                    if (s1[i] == "C18")
                    {
                        s1[i] = "318";
                    }
                    if (s1[i] == "C19")
                    {
                        s1[i] = "319";
                    }
                    if (s1[i] == "C20")
                    {
                        s1[i] = "320";
                    }
                    if (s1[i] == "C21")
                    {
                        s1[i] = "321";
                    }
                    if (s1[i] == "C22")
                    {
                        s1[i] = "322";
                    }
                    if (s1[i] == "C23")
                    {
                        s1[i] = "323";
                    }
                    if (s1[i] == "C24")
                    {
                        s1[i] = "324";
                    }
                    if (s1[i] == "C25")
                    {
                        s1[i] = "325";
                    }
                    if (s1[i] == "C26")
                    {
                        s1[i] = "326";
                    }
                    if (s1[i] == "C27")
                    {
                        s1[i] = "327";
                    }
                    if (s1[i] == "C28")
                    {
                        s1[i] = "328";
                    }
                    if (s1[i] == "C29")
                    {
                        s1[i] = "329";
                    }
                    if (s1[i] == "C30")
                    {
                        s1[i] = "330";
                    }
                    if (s1[i] == "C31")
                    {
                        s1[i] = "331";
                    }
                    if (s1[i] == "C32")
                    {
                        s1[i] = "332";
                    }
                    if (s1[i] == "C33")
                    {
                        s1[i] = "333";
                    }
                    if (s1[i] == "C34")
                    {
                        s1[i] = "334";
                    }
                    if (s1[i] == "C35")
                    {
                        s1[i] = "335";
                    }
                    if (s1[i] == "C36")
                    {
                        s1[i] = "336";
                    }

                    if (s1[i] == "E01")
                    {
                        s1[i] = "401";
                    }
                    if (s1[i] == "E02")
                    {
                        s1[i] = "402";
                    }
                    if (s1[i] == "E03")
                    {
                        s1[i] = "403";
                    }
                    if (s1[i] == "E04")
                    {
                        s1[i] = "404";
                    }
                    if (s1[i] == "E05")
                    {
                        s1[i] = "405";
                    }
                    if (s1[i] == "E06")
                    {
                        s1[i] = "406";
                    }
                    if (s1[i] == "E07")
                    {
                        s1[i] = "407";
                    }
                    if (s1[i] == "E08")
                    {
                        s1[i] = "408";
                    }
                    if (s1[i] == "E09")
                    {
                        s1[i] = "409";
                    }
                    if (s1[i] == "E10")
                    {
                        s1[i] = "410";
                    }
                    if (s1[i] == "E11")
                    {
                        s1[i] = "411";
                    }
                    if (s1[i] == "E12")
                    {
                        s1[i] = "412";
                    }
                    if (s1[i] == "E13")
                    {
                        s1[i] = "413";
                    }
                    if (s1[i] == "E14")
                    {
                        s1[i] = "414";
                    }
                    if (s1[i] == "E15")
                    {
                        s1[i] = "415";
                    }
                    if (s1[i] == "E16")
                    {
                        s1[i] = "416";
                    }
                    if (s1[i] == "E17")
                    {
                        s1[i] = "417";
                    }
                    if (s1[i] == "E18")
                    {
                        s1[i] = "418";
                    }
                    if (s1[i] == "E19")
                    {
                        s1[i] = "419";
                    }
                    if (s1[i] == "E20")
                    {
                        s1[i] = "420";
                    }
                    if (s1[i] == "E21")
                    {
                        s1[i] = "421";
                    }
                    if (s1[i] == "E22")
                    {
                        s1[i] = "422";
                    }
                    if (s1[i] == "E23")
                    {
                        s1[i] = "423";
                    }
                    if (s1[i] == "E24")
                    {
                        s1[i] = "424";
                    }
                    if (s1[i] == "E25")
                    {
                        s1[i] = "425";
                    }
                    if (s1[i] == "E26")
                    {
                        s1[i] = "426";
                    }
                    if (s1[i] == "E27")
                    {
                        s1[i] = "427";
                    }
                    if (s1[i] == "E28")
                    {
                        s1[i] = "428";
                    }
                    if (s1[i] == "E29")
                    {
                        s1[i] = "429";
                    }
                    if (s1[i] == "E30")
                    {
                        s1[i] = "430";
                    }
                    if (s1[i] == "E31")
                    {
                        s1[i] = "431";
                    }
                    if (s1[i] == "E32")
                    {
                        s1[i] = "432";
                    }
                    if (s1[i] == "E33")
                    {
                        s1[i] = "433";
                    }
                    if (s1[i] == "E34")
                    {
                        s1[i] = "434";
                    }
                    if (s1[i] == "E35")
                    {
                        s1[i] = "435";
                    }
                    if (s1[i] == "E36")
                    {
                        s1[i] = "436";
                    }

                    stringstream ss;
                    ss << s1[i];
                    ss >> temp;
                    data.push_back(temp);

                }
            }
            k = k + 1;
            if (k > end)
            {
                break;
            }
        }
    }
    ifile.close();

    cout << "��ȡ�ɹ�" << endl;
    return data;
}

vector<double> readO302(int start, int end, string pattern, string Adress)//��ȡ�۲�ֵ�ļ�  
{
    //start:   ��ȡ��ʼ��
    //end;     ��ȡ������
    //Adress:  �ļ���ַ
    //pattern: �ָ��־���ţ�������-��
    //PS:      �ڶ�ȡʱ��ʵ��ÿһ�а��Ŷ���һ�飬ֻ����ת��������ʱֻ��������Ҫ�Ĳ���
    //          һ��ֻ�ܶ�ȡһ����Ԫ

    string filename = Adress;
    ifstream ifile(filename.c_str());

    vector<double> data;
    double temp; //�ַ���ת���ֹ����е���ʱ����
    string s;
    vector<string> s1; //vector����������һ��ͨ���±�ֱ�ӷ��ʣ�����ò�Ҫ�������δ֪����
    int k = 1;//�м�����
    if (ifile.is_open())
    {
        while (getline(ifile, s))
        {
            s1 = split1(s, pattern, "-");  //ע����ʱ��ָ����Ϊת���ַ��������\ 

            if (k == start)   //һ��Ҫע�� = �� == ������
            {

                for (int i = 0; i < 9; i++)
                {

                    stringstream ss;
                    ss << s1[i];
                    ss >> temp;
                    data.push_back(temp);

                }
            }

            if (k > start)//ת��������ʱ����ͷ�ļ��͵�һ�У����Ǳ��ת������ʱ����0����Ϊ����ĸ��
            {

                for (int i = 0; i < 2; i++)
                {
                    if (s1[i] == "G01")
                    {
                        s1[i] = "101";
                    }
                    if (s1[i] == "G02")
                    {
                        s1[i] = "102";
                    }
                    if (s1[i] == "G03")
                    {
                        s1[i] = "103";
                    }
                    if (s1[i] == "G04")
                    {
                        s1[i] = "104";
                    }
                    if (s1[i] == "G05")
                    {
                        s1[i] = "105";
                    }
                    if (s1[i] == "G06")
                    {
                        s1[i] = "106";
                    }
                    if (s1[i] == "G07")
                    {
                        s1[i] = "107";
                    }
                    if (s1[i] == "G08")
                    {
                        s1[i] = "108";
                    }
                    if (s1[i] == "G09")
                    {
                        s1[i] = "109";
                    }
                    if (s1[i] == "G10")
                    {
                        s1[i] = "110";
                    }
                    if (s1[i] == "G11")
                    {
                        s1[i] = "111";
                    }
                    if (s1[i] == "G12")
                    {
                        s1[i] = "112";
                    }
                    if (s1[i] == "G13")
                    {
                        s1[i] = "113";
                    }
                    if (s1[i] == "G14")
                    {
                        s1[i] = "114";
                    }
                    if (s1[i] == "G15")
                    {
                        s1[i] = "115";
                    }
                    if (s1[i] == "G16")
                    {
                        s1[i] = "116";
                    }
                    if (s1[i] == "G17")
                    {
                        s1[i] = "117";
                    }
                    if (s1[i] == "G18")
                    {
                        s1[i] = "118";
                    }
                    if (s1[i] == "G19")
                    {
                        s1[i] = "119";
                    }
                    if (s1[i] == "G20")
                    {
                        s1[i] = "120";
                    }
                    if (s1[i] == "G21")
                    {
                        s1[i] = "121";
                    }
                    if (s1[i] == "G22")
                    {
                        s1[i] = "122";
                    }
                    if (s1[i] == "G23")
                    {
                        s1[i] = "123";
                    }
                    if (s1[i] == "G24")
                    {
                        s1[i] = "124";
                    }
                    if (s1[i] == "G25")
                    {
                        s1[i] = "125";
                    }
                    if (s1[i] == "G26")
                    {
                        s1[i] = "126";
                    }
                    if (s1[i] == "G27")
                    {
                        s1[i] = "127";
                    }
                    if (s1[i] == "G28")
                    {
                        s1[i] = "128";
                    }
                    if (s1[i] == "G29")
                    {
                        s1[i] = "129";
                    }
                    if (s1[i] == "G30")
                    {
                        s1[i] = "130";
                    }
                    if (s1[i] == "G31")
                    {
                        s1[i] = "131";
                    }
                    if (s1[i] == "G32")
                    {
                        s1[i] = "132";
                    }
                    if (s1[i] == "G33")
                    {
                        s1[i] = "133";
                    }
                    if (s1[i] == "G34")
                    {
                        s1[i] = "134";
                    }
                    if (s1[i] == "G35")
                    {
                        s1[i] = "135";
                    }
                    if (s1[i] == "G36")
                    {
                        s1[i] = "136";
                    }

                    if (s1[i] == "R01")
                    {
                        s1[i] = "201";
                    }
                    if (s1[i] == "R02")
                    {
                        s1[i] = "202";
                    }
                    if (s1[i] == "R03")
                    {
                        s1[i] = "203";
                    }
                    if (s1[i] == "R04")
                    {
                        s1[i] = "204";
                    }
                    if (s1[i] == "R05")
                    {
                        s1[i] = "205";
                    }
                    if (s1[i] == "R06")
                    {
                        s1[i] = "206";
                    }
                    if (s1[i] == "R07")
                    {
                        s1[i] = "207";
                    }
                    if (s1[i] == "R08")
                    {
                        s1[i] = "208";
                    }
                    if (s1[i] == "R09")
                    {
                        s1[i] = "209";
                    }
                    if (s1[i] == "R10")
                    {
                        s1[i] = "210";
                    }
                    if (s1[i] == "R11")
                    {
                        s1[i] = "211";
                    }
                    if (s1[i] == "R12")
                    {
                        s1[i] = "212";
                    }
                    if (s1[i] == "R13")
                    {
                        s1[i] = "213";
                    }
                    if (s1[i] == "R14")
                    {
                        s1[i] = "214";
                    }
                    if (s1[i] == "R15")
                    {
                        s1[i] = "215";
                    }
                    if (s1[i] == "R16")
                    {
                        s1[i] = "216";
                    }
                    if (s1[i] == "R17")
                    {
                        s1[i] = "217";
                    }
                    if (s1[i] == "R18")
                    {
                        s1[i] = "218";
                    }
                    if (s1[i] == "R19")
                    {
                        s1[i] = "219";
                    }
                    if (s1[i] == "R20")
                    {
                        s1[i] = "220";
                    }
                    if (s1[i] == "R21")
                    {
                        s1[i] = "221";
                    }
                    if (s1[i] == "R22")
                    {
                        s1[i] = "222";
                    }
                    if (s1[i] == "R23")
                    {
                        s1[i] = "223";
                    }
                    if (s1[i] == "R24")
                    {
                        s1[i] = "224";
                    }
                    if (s1[i] == "R25")
                    {
                        s1[i] = "225";
                    }
                    if (s1[i] == "R26")
                    {
                        s1[i] = "226";
                    }
                    if (s1[i] == "R27")
                    {
                        s1[i] = "227";
                    }
                    if (s1[i] == "R28")
                    {
                        s1[i] = "228";
                    }
                    if (s1[i] == "R29")
                    {
                        s1[i] = "229";
                    }
                    if (s1[i] == "R30")
                    {
                        s1[i] = "230";
                    }
                    if (s1[i] == "R31")
                    {
                        s1[i] = "231";
                    }
                    if (s1[i] == "R32")
                    {
                        s1[i] = "232";
                    }
                    if (s1[i] == "R33")
                    {
                        s1[i] = "233";
                    }
                    if (s1[i] == "R34")
                    {
                        s1[i] = "234";
                    }
                    if (s1[i] == "R35")
                    {
                        s1[i] = "235";
                    }
                    if (s1[i] == "R36")
                    {
                        s1[i] = "236";
                    }

                    if (s1[i] == "C01")
                    {
                        s1[i] = "301";
                    }
                    if (s1[i] == "C02")
                    {
                        s1[i] = "302";
                    }
                    if (s1[i] == "C03")
                    {
                        s1[i] = "303";
                    }
                    if (s1[i] == "C04")
                    {
                        s1[i] = "304";
                    }
                    if (s1[i] == "C05")
                    {
                        s1[i] = "305";
                    }
                    if (s1[i] == "C06")
                    {
                        s1[i] = "306";
                    }
                    if (s1[i] == "C07")
                    {
                        s1[i] = "307";
                    }
                    if (s1[i] == "C08")
                    {
                        s1[i] = "308";
                    }
                    if (s1[i] == "C09")
                    {
                        s1[i] = "309";
                    }
                    if (s1[i] == "C10")
                    {
                        s1[i] = "310";
                    }
                    if (s1[i] == "C11")
                    {
                        s1[i] = "311";
                    }
                    if (s1[i] == "C12")
                    {
                        s1[i] = "312";
                    }
                    if (s1[i] == "C13")
                    {
                        s1[i] = "313";
                    }
                    if (s1[i] == "C14")
                    {
                        s1[i] = "314";
                    }
                    if (s1[i] == "C15")
                    {
                        s1[i] = "315";
                    }
                    if (s1[i] == "C16")
                    {
                        s1[i] = "316";
                    }
                    if (s1[i] == "C17")
                    {
                        s1[i] = "317";
                    }
                    if (s1[i] == "C18")
                    {
                        s1[i] = "318";
                    }
                    if (s1[i] == "C19")
                    {
                        s1[i] = "319";
                    }
                    if (s1[i] == "C20")
                    {
                        s1[i] = "320";
                    }
                    if (s1[i] == "C21")
                    {
                        s1[i] = "321";
                    }
                    if (s1[i] == "C22")
                    {
                        s1[i] = "322";
                    }
                    if (s1[i] == "C23")
                    {
                        s1[i] = "323";
                    }
                    if (s1[i] == "C24")
                    {
                        s1[i] = "324";
                    }
                    if (s1[i] == "C25")
                    {
                        s1[i] = "325";
                    }
                    if (s1[i] == "C26")
                    {
                        s1[i] = "326";
                    }
                    if (s1[i] == "C27")
                    {
                        s1[i] = "327";
                    }
                    if (s1[i] == "C28")
                    {
                        s1[i] = "328";
                    }
                    if (s1[i] == "C29")
                    {
                        s1[i] = "329";
                    }
                    if (s1[i] == "C30")
                    {
                        s1[i] = "330";
                    }
                    if (s1[i] == "C31")
                    {
                        s1[i] = "331";
                    }
                    if (s1[i] == "C32")
                    {
                        s1[i] = "332";
                    }
                    if (s1[i] == "C33")
                    {
                        s1[i] = "333";
                    }
                    if (s1[i] == "C34")
                    {
                        s1[i] = "334";
                    }
                    if (s1[i] == "C35")
                    {
                        s1[i] = "335";
                    }
                    if (s1[i] == "C36")
                    {
                        s1[i] = "336";
                    }

                    if (s1[i] == "E01")
                    {
                        s1[i] = "401";
                    }
                    if (s1[i] == "E02")
                    {
                        s1[i] = "402";
                    }
                    if (s1[i] == "E03")
                    {
                        s1[i] = "403";
                    }
                    if (s1[i] == "E04")
                    {
                        s1[i] = "404";
                    }
                    if (s1[i] == "E05")
                    {
                        s1[i] = "405";
                    }
                    if (s1[i] == "E06")
                    {
                        s1[i] = "406";
                    }
                    if (s1[i] == "E07")
                    {
                        s1[i] = "407";
                    }
                    if (s1[i] == "E08")
                    {
                        s1[i] = "408";
                    }
                    if (s1[i] == "E09")
                    {
                        s1[i] = "409";
                    }
                    if (s1[i] == "E10")
                    {
                        s1[i] = "410";
                    }
                    if (s1[i] == "E11")
                    {
                        s1[i] = "411";
                    }
                    if (s1[i] == "E12")
                    {
                        s1[i] = "412";
                    }
                    if (s1[i] == "E13")
                    {
                        s1[i] = "413";
                    }
                    if (s1[i] == "E14")
                    {
                        s1[i] = "414";
                    }
                    if (s1[i] == "E15")
                    {
                        s1[i] = "415";
                    }
                    if (s1[i] == "E16")
                    {
                        s1[i] = "416";
                    }
                    if (s1[i] == "E17")
                    {
                        s1[i] = "417";
                    }
                    if (s1[i] == "E18")
                    {
                        s1[i] = "418";
                    }
                    if (s1[i] == "E19")
                    {
                        s1[i] = "419";
                    }
                    if (s1[i] == "E20")
                    {
                        s1[i] = "420";
                    }
                    if (s1[i] == "E21")
                    {
                        s1[i] = "421";
                    }
                    if (s1[i] == "E22")
                    {
                        s1[i] = "422";
                    }
                    if (s1[i] == "E23")
                    {
                        s1[i] = "423";
                    }
                    if (s1[i] == "E24")
                    {
                        s1[i] = "424";
                    }
                    if (s1[i] == "E25")
                    {
                        s1[i] = "425";
                    }
                    if (s1[i] == "E26")
                    {
                        s1[i] = "426";
                    }
                    if (s1[i] == "E27")
                    {
                        s1[i] = "427";
                    }
                    if (s1[i] == "E28")
                    {
                        s1[i] = "428";
                    }
                    if (s1[i] == "E29")
                    {
                        s1[i] = "429";
                    }
                    if (s1[i] == "E30")
                    {
                        s1[i] = "430";
                    }
                    if (s1[i] == "E31")
                    {
                        s1[i] = "431";
                    }
                    if (s1[i] == "E32")
                    {
                        s1[i] = "432";
                    }
                    if (s1[i] == "E33")
                    {
                        s1[i] = "433";
                    }
                    if (s1[i] == "E34")
                    {
                        s1[i] = "434";
                    }
                    if (s1[i] == "E35")
                    {
                        s1[i] = "435";
                    }
                    if (s1[i] == "E36")
                    {
                        s1[i] = "436";
                    }

                    stringstream ss;
                    ss << s1[i];
                    ss >> temp;
                    data.push_back(temp);

                }
            }
            k = k + 1;
            if (k > end)
            {
                break;
            }
        }
    }
    ifile.close();

    cout << "��ȡ�ɹ�" << endl;
    return data;
}
