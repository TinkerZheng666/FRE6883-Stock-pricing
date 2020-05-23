#pragma once
#ifndef Stratify_h
#define Stratify_h

#include <vector>;
#include "Stock.h";
using namespace std;

class stratify
{
private:
	vector<double> Aver_AAR = vector<double>(60, 0.0);
	vector<double> Sd_AAR = vector<double>(60, 0.0);
	vector<double> Aver_CAAR = vector<double>(60, 0.0);
	vector<double> Sd_CAAR = vector<double>(60, 0.0);
	vector<Stock*> vstock; //vector of Stock*
	int group_size;
	string group_name;
public:
	stratify(vector<Stock*>& vstock_, string group_name_); //constructor
	stratify() {}; // default constructor
	vector<double> OneSample(); //generate one bootstrap-sample
	void BootStrap(); //call function-OneSample 30 times
	vector<double> Get_Aver_CAAR();
	void PullGroupInfo();
};
bool cmp_by_value(Stock*& lhs, Stock*& rhs);
void Stratify_Calculate_Bootstrap(map<string, Stock>& stock_map_, ETF& spy, stratify& Beat, stratify& Meet, stratify& Miss);
#endif // !Stratify_h

