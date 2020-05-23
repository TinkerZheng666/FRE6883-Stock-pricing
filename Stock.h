#pragma once
#ifndef  Stock_h
#define Stock_h
#include <vector>;
#include <map>;
#include "ETF.h"
// class stock is used to store the info of any sp500 stocks
class Stock {
private:
	string name;
	string ticker;
	string date; //releasing date
	double actual;
	double estimate;
	double surprise;
	vector<double> price;
	vector<double> AR;
	vector<double> StockReturn;
	vector<double> SPYReturn;
	vector<string> ReturnDates;
	string StartDate;
	string EndDate;
	string Group;
public:
	map<string, Stock> getBloomberg(string myFile);
	void PullStockInfo();
	string getDate();
	double getSurprise();
	void Setprice(vector<double>&);
	void SetReturn();
	vector<string> GetStartEndDates(vector<string>&);
	vector<double> getAR()
	{
		return AR;
	}
	void SetAR(ETF& spy);
	void SetGroup(string str_) { Group = str_; }
	vector<double> getPrice() { return price; }
};

#endif //  Stock_h
