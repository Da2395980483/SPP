
#ifndef READ_H
#define READ_H

using namespace std;

string insert(string s1, string s2, int n);
vector<string> split(string str, string pattern);
vector<string> split1(string str, string pattern, string pattern1);
vector<double> readN303d(int start, int end, string pattern, string Adress);
vector<double> readO303d(int start, int end, string pattern, string Adress);

#endif
