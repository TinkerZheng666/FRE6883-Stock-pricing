#pragma once
#ifndef ETF_h
#define ETF_h

#include <vector>;
#include <string>;
using namespace std;

class ETF
{
private:
	vector<string> date;
	vector<double> price;
	vector<double> Return;

public:
	const vector<string>& GetDateVector();
	const vector<double>& GetReturnVector();
	void SetDate(vector<string>&);
	void SetPriceReturn(vector<double>&);
};

#endif // !ETF_h
