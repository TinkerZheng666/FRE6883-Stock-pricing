#pragma once
#ifndef OperatorOverloading_h
#define OperatorOverloading_h

#include <vector>;
using namespace std;

vector<double> operator+(const vector<double>& v1, const vector<double>& v2);
vector<double> operator-(const vector<double>& v1, const vector<double>& v2);
vector<double> operator*(const double& a, const vector<double>& v);
vector<double> operator/(const vector<double>& v1, const vector<double>& v2);
vector<double> pow(const vector<double>& v, const double& a);

#endif // !OperatorOverloading_h

