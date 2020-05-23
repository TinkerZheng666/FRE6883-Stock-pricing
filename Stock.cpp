//Stock.cpp
#include "Stock.h"
#include <stdio.h>  
#include <stdlib.h> 
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <errno.h>
#include <sstream> // stringstream
#include <typeinfo> // get the data type
#include <regex> // cpp11
#include <map>
#include <iomanip>
#include "OperatorOverloading.h"
using namespace std;

void Stock::PullStockInfo()
{
	cout << endl << "Stock Name:  " << name << endl << "Ticker:  " << ticker << endl <<
		"Releasing Date:  " << date << endl << "Estimated EPS:  " << estimate << endl <<
		"Actual EPS:  " << actual << endl << "Surprise %:  " << surprise << endl <<
		"Stock Group:  " << Group << endl << endl;

	cout << setiosflags(ios::fixed) << setprecision(4);
	cout << setiosflags(ios::right) <<
		setw(12) << "Date" << "|" <<
		setw(12) << "AdjClose" << "|" <<
		setw(12) << "Return" << "|" <<
		setw(12) << "SPY Return" << "|" <<
		setw(12) << "Abnormal Return" << endl;

	for (int i = 0; i < 60; i++)
		cout << setiosflags(ios::right) <<
		setw(12) << ReturnDates.at(i) << "|" <<
		setw(12) << price.at(i) << "|" <<
		setw(12) << StockReturn.at(i) << "|" <<
		setw(12) << SPYReturn.at(i) << "|" <<
		setw(12) << AR.at(i) << endl;
}





map<string, Stock> Stock::getBloomberg(string myFile)
{
	string line;
	map<string, Stock> stock;
	ifstream in(myFile); // read myFile into fstream "in"

	if (in)
	{
		string firstLine;
		getline(in, firstLine); //skip first line
		while (getline(in, line))
		{
			Stock info;
			regex comma(",");
			vector<string> v(sregex_token_iterator(line.begin(), line.end(),
				comma, -1), sregex_token_iterator());  //split using comma
			info.name = v[0];
			info.ticker = v[1];
			//cout << info.ticker << endl;
			info.date = v[2];
			info.actual = stod(v[3]);
			info.estimate = stod(v[4]);
			info.surprise = (info.actual - info.estimate) / info.estimate;
			stock.insert({ v[1], info });
		}
		in.close();
		// code to check the accuracy of the code, you can delete it
		/*auto map_it = stock.cbegin();
		while (map_it != stock.cend())
		{
			Stock c = map_it->second;
			cout << map_it->first << c.getDate() << endl;
			++map_it;
		}
		*/

		return stock;
	}
	else
	{
		cout << "The file" << myFile << "could not open" << endl;
	}
}

string Stock::getDate()
{
	return date;
}

double Stock::getSurprise()
{
	return surprise;
}

void Stock::Setprice(vector<double>& price_)
{
	price.assign(price_.begin(), price_.end());
}

vector<string> Stock::GetStartEndDates(vector<string>& BenchmarkDate)
{
	vector<string>StartEnds;
	auto itr1 = find(BenchmarkDate.begin(), BenchmarkDate.end(), date);
	//cout << "Issue Date:" << date << endl;
	//cout << "Start Date:" << *(itr1 - 30) << endl;
	//cout << "End Date:" << *(itr1 + 30) << endl;
	ReturnDates.assign((itr1 - 29), (itr1 + 31));
	//cout << "Date size: --------------------- " << ReturnDates.size() << endl;//for debug purpose
	StartEnds.push_back(*(itr1 - 30));
	StartEnds.push_back(*(itr1 + 30));
	StartDate = *(itr1 - 29);
	EndDate = *(itr1 + 30);
	return StartEnds;
}

void Stock::SetReturn()
{
	vector<double>price_shift;
	vector<double>price_end;
	//cout << price.size() << endl;
	price_shift.assign(price.begin() + 1, price.end());
	price_end.assign(price.begin(), price.end() - 1);
	//cout << "shift:   " << price_shift.size() << endl;
	//cout << "end:   " << price_end.size() << endl;
	vector<double>vec_return = (price_shift - price_end) / price_end;
	StockReturn.assign(vec_return.begin(), vec_return.end());
}


void Stock::SetAR(ETF& spy)
{
	vector<string> SPY_date = spy.GetDateVector();
	vector<double> SPY_return = spy.GetReturnVector();
	auto itr_date = find(SPY_date.begin(), SPY_date.end(), StartDate);
	auto itr_return = SPY_return.begin() + (itr_date - SPY_date.begin()) - 1;
	SPYReturn.assign(itr_return, itr_return + 60);
	//cout << "AR LEN: " << AR.size() << endl;//for debug purpose
	//cout << "StockR Len: " << StockReturn.size() << endl;//for debug purpose
	AR = StockReturn - SPYReturn;
}
