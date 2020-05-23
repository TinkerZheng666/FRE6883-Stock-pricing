//Stratify.cpp
#include "Stratify.h";
#include "Stock.h";
#include <iostream>;
#include <iomanip>;
#include <numeric>;
#include "OperatorOverloading.h";
#include <algorithm>

void stratify::PullGroupInfo()
{
	cout << endl << "AAR, AAR-SD, CAAR and CAAR-SD of " << group_name << " group :" << endl << endl;

	cout << setiosflags(ios::fixed) << setprecision(4);
	cout << setiosflags(ios::right) <<
		setw(10) << "Date" << "|" <<
		setw(10) << "AAR" << "|" <<
		setw(10) << "AAR-SD" << "|" <<
		setw(10) << "CAAR" << "|" <<
		setw(10) << "CAAR-SD" << endl;

	for (int i = -29; i <= 30; i++)
		cout << setiosflags(ios::right) <<
		setw(10) << i << "|" <<
		setw(10) << Aver_AAR.at(i + 29) << "|" <<
		setw(10) << Sd_AAR.at(i + 29) << "|" <<
		setw(10) << Aver_CAAR.at(i + 29) << "|" <<
		setw(10) << Sd_CAAR.at(i + 29) << endl;

}









vector<double> stratify::Get_Aver_CAAR()
{
	return Aver_CAAR;
}


stratify::stratify(vector<Stock*>& vstock_, string group_name_)
{
	vstock = vstock_;
	group_name = group_name_;
	group_size = vstock.size();
	srand((unsigned int)time(NULL));
}


vector<double> stratify::OneSample()
{
	vector<double> AAR = vector<double>(60, 0.0);

	for (int i = 0; i < 30; i++)
	{
		int id = rand() % group_size; //random int between 0 and (group_size-1)
		AAR = (i / (i + 1.0)) * AAR + (1 / (i + 1.0)) * ((vstock.at(id))->getAR());
	}
	return AAR;
}

void stratify::BootStrap()
{
	for (int k = 0; k < 30; k++)
	{
		vector<double> AAR = OneSample();
		// CAAR is the cumulative sum of AAR
		vector<double> CAAR(60, 0.0);
		partial_sum(AAR.begin(), AAR.end(), CAAR.begin());
		// step by step calculation for mean/variance
		Aver_AAR = (k / (k + 1.0)) * Aver_AAR + (1 / (k + 1.0)) * AAR;
		Aver_CAAR = (k / (k + 1.0)) * Aver_CAAR + (1 / (k + 1.0)) * CAAR;
		Sd_AAR = (k / (k + 1.0)) * Sd_AAR + (1 / (k + 1.0)) * pow(AAR, 2.0);
		Sd_CAAR = (k / (k + 1.0)) * Sd_CAAR + (1 / (k + 1.0)) * pow(CAAR, 2.0);
	}
	// final step calculation for standard deviation
	Sd_AAR = pow(Sd_AAR - pow(Aver_AAR, 2.0), 0.5);
	Sd_CAAR = pow(Sd_CAAR - pow(Aver_CAAR, 2.0), 0.5);

}

bool cmp_by_value(Stock*& lhs, Stock*& rhs)
{
	return lhs->getSurprise() < rhs->getSurprise();
}

void Stratify_Calculate_Bootstrap(map<string, Stock>& stock_map_, ETF& spy,
	stratify& Beat, stratify& Meet, stratify& Miss)
{
	vector<Stock*> BeatList, MeetList, MissList;
	vector<Stock*> stocklist;
	for (auto it = stock_map_.begin(); it != stock_map_.end(); it++)
	{
		/*
		int temp = it->second.getPrice().size();
		if (temp != 61)
		{
			cout << "Debug: wrong price vector size" << endl;
			cout << it->first << "   " << temp << endl;
		}
		*/
		stocklist.push_back(&(it->second));
	}

	sort(stocklist.begin(), stocklist.end(), cmp_by_value);

	//int StockNum = stocklist.size();
	int itcount = 0;
	for (auto it = stocklist.begin(); it != stocklist.end(); it++, itcount++)
	{
		if (itcount < 109) //(StockNum / 3)
		{
			MissList.push_back(*it);
			(*it)->SetGroup("Miss");

		}
		else if (itcount < 261) //(2 * StockNum / 3)
		{
			MeetList.push_back(*it);
			(*it)->SetGroup("Meet");
		}
		else
		{
			BeatList.push_back(*it);
			(*it)->SetGroup("Beat");
		}
		(*it)->SetReturn();
		(*it)->SetAR(spy);
	}
	Beat = stratify(BeatList, "Beat");
	Meet = stratify(MeetList, "Meet");
	Miss = stratify(MissList, "Miss");

	Beat.BootStrap();
	Meet.BootStrap();
	Miss.BootStrap();
}