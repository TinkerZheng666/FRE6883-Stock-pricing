//ETF.cpp
#include "ETF.h";
#include <vector>;
#include <string>;
#include "OperatorOverloading.h"
using namespace std;

const vector<string>& ETF::GetDateVector()
{
	return date;
}

const vector<double>& ETF::GetReturnVector()
{
	return Return;
}

void ETF::SetDate(vector<string>& Date_)
{
	date.assign(Date_.begin(), Date_.end());
}

void ETF::SetPriceReturn(vector<double>& Price_)
{
	price.assign(Price_.begin(), Price_.end());
	vector<double>price_shift;
	vector<double>price_end;
	price_shift.assign(Price_.begin() + 1, Price_.end());
	price_end.assign(Price_.begin(), Price_.end() - 1);
	vector<double>vec_return = (price_shift - price_end) / price_end;
	Return.assign(vec_return.begin(), vec_return.end());
}