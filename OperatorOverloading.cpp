//OperatorOverloading.cpp
#include "OperatorOverloading.h";
#include <vector>;
using namespace std;

vector<double> operator+(const vector<double>& v1, const vector<double>& v2)
{
	int dimension = v1.size();
	vector<double> w(dimension);
	for (int j = 0; j < dimension; j++)
	{
		w[j] = v1[j] + v2[j];
	}
	return w;
}
//operator overloading: -
vector<double> operator-(const vector<double>& v1, const vector<double>& v2)
{
	int dimension = v1.size();
	vector<double> w(dimension);
	for (int j = 0; j < dimension; j++)
	{
		w[j] = v1[j] - v2[j];
	}
	return w;
}
//operator overloading: *
vector<double> operator*(const double& a, const vector<double>& v)
{
	int dimension = v.size();
	vector<double> w(dimension);
	for (int j = 0; j < dimension; j++)
	{
		w[j] = a * v[j];
	}
	return w;
}
//operator overloading: /
vector<double> operator/(const vector<double>& v1, const vector<double>& v2)
{
	int dimension = v1.size();
	vector<double> w(dimension);
	for (int j = 0; j < dimension; j++)
	{
		w[j] = v1[j] / v2[j];
	}
	return w;
}
//operator overloading: pow
vector<double> pow(const vector<double>& v, const double& a)
{
	int dimension = v.size();
	vector<double> w(dimension);
	for (int j = 0; j < dimension; j++)
	{
		w[j] = pow(v[j], a);
	}
	return w;
}