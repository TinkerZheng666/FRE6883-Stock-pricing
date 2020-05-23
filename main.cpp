//main.cpp
#include <time.h>
#include <iostream>
#include <map>
#include "Stock.h"
#include "OperatorOverloading.h"
#include "ETF.h"
#include "Stratify.h"
#include "MyCurl.h"
#include <iomanip>
#include <time.h>


using namespace std;



void plotResults(stratify& Beat_, stratify& Meet_, stratify& Miss_) {


	vector<double> Beat_CAAR = Beat_.Get_Aver_CAAR();
	vector<double> Meet_CAAR = Meet_.Get_Aver_CAAR();
	vector<double> Miss_CAAR = Miss_.Get_Aver_CAAR();
	//cout << "Debug: "<<Beat_CAAR.size() << endl;

	double* xData = (double*)malloc(60 * sizeof(double));
	double* yData1 = (double*)malloc(60 * sizeof(double));
	double* yData2 = (double*)malloc(60 * sizeof(double));
	double* yData3 = (double*)malloc(60 * sizeof(double));
	for (int i = 0; i <= 59; i++) {
		xData[i] = double(i);
		yData1[i] = Beat_CAAR.at(i);
		yData2[i] = Meet_CAAR.at(i);
		yData3[i] = Miss_CAAR.at(i);
	}

	FILE* gnuplotPipe, * tempDataFile;
	const char* BeatData = "Beat Group";
	const char* MeetData = "Meet Group";
	const char* MissData = "Miss Group";
	double x1, y1, x2, y2, x3, y3;

	gnuplotPipe = _popen("C:\\LIN\\NYU\\6883CPP\\Package\\gnuplot\\bin\\gnuplot", "w");// Gnuplot path in Windows 
	if (gnuplotPipe) {
		fprintf(gnuplotPipe, "plot \"%s\" with lines, \"%s\" with lines, \"%s\" with lines\n",
			BeatData, MeetData, MissData);
		fflush(gnuplotPipe);

		tempDataFile = fopen(BeatData, "w");
		for (int i = 0; i <= 59; i++) {
			x1 = xData[i];
			y1 = yData1[i];
			fprintf(tempDataFile, "%lf %lf\n", x1, y1);
		}
		fclose(tempDataFile);

		tempDataFile = fopen(MeetData, "w");
		for (int i = 0; i <= 59; i++) {
			x2 = xData[i];
			y2 = yData2[i];
			fprintf(tempDataFile, "%lf %lf\n", x2, y2);
		}
		fclose(tempDataFile);

		tempDataFile = fopen(MissData, "w");
		for (int i = 0; i <= 59; i++) {
			x3 = xData[i];
			y3 = yData3[i];
			fprintf(tempDataFile, "%lf %lf\n", x3, y3);
		}
		fclose(tempDataFile);
		//cannot write following codes if you use this function in the loop
		/*
		remove(BeatData);
		remove(MeetData);
		remove(MissData);
		*/
		//fprintf(gnuplotPipe, "exit \n");
		cout << "Successfully printed." << endl;
	}
	else {
		printf("gnuplot not found...");
	}
}


int main()
{
	// clock_t object for yiming
	clock_t t0 = clock();
	// Stock object for retrieving data
	Stock WebCrawler;
	// ETF object for storing S&P 500 data
	ETF SPY500;
	// map object for storing Stock objects
	map<string, Stock> stock_map;
	// stratify objects for storing group information
	stratify Beat, Meet, Miss;
	// char: user's choice
	char Response;
	// bool: whether to exit the program
	bool Quit = false;
	// bool: whether data have been retrieved and calculated
	bool PrepareData = false;
	// bool: whether it is the first time to run the while loop
	bool FirstLoop = true;
	// string: storing the user's string-type input
	string StrInput;


	while (!Quit)
	{
		cout << "#---------------------------------------------------------------#" << endl;
		cout << "                                                                " << endl;
		cout << "                            Menu                                " << endl;
		cout << "                                                                " << endl;
		if (FirstLoop)
		{
			cout << "                     Proudly Presented by                       " << endl;
			cout << "               Zhibai Luo, Zicheng He, Yulin Wu                 " << endl;
			cout << "                  Tianzi Zheng, Xiangjun Kong                   " << endl;
			cout << "                                                                " << endl;
			FirstLoop = false;
		}
		cout << "#---------------------------------------------------------------#" << endl;
		cout << "Please choose one from the following five options" << endl;
		cout << " 1) Retrieve historical price data for all stocks" << endl;
		cout << " 2) Pull information of one stock" << endl;
		cout << " 3) Show AAR, AAR-SD, CAAR and CAAR-SD of one group" << endl;
		cout << " 4) Show the CAAR graph of all 3 groups" << endl;
		cout << " 5) Exit the program" << endl;
		cout << "Please enter 1, 2, 3, 4 or 5:  ";
		cin >> Response;
		cout << endl;
		switch (Response)
		{
		case '1':
			if (PrepareData) { cout << "Historical price data for all stocks retrieved." << endl << endl << endl << endl; break; }
			cout << "Retrieving historical price data for all stocks:" << endl;
			t0 = clock();
			stock_map = WebCrawler.getBloomberg("C:\\Users\\WilliamNG\\Desktop\\2019Q1_new.csv");
			GetPriceData(stock_map, SPY500);
			cout << "Historical price data for all stocks retrieved; time used: " << setprecision(3) <<
				(clock() - t0) * 1.0 / CLOCKS_PER_SEC / 60.0 << " min" << endl << endl;
			t0 = clock();
			Stratify_Calculate_Bootstrap(stock_map, SPY500, Beat, Meet, Miss);
			cout << "AAR and CAAR of all 3 groups calculated; time used: " << setprecision(3) <<
				(clock() - t0) * 1.0 / CLOCKS_PER_SEC / 60.0 << " min" << endl << endl << endl << endl;
			PrepareData = true;
			break;
		case '2':
			if (!PrepareData) { cout << "Please first retrieve historical price data." << endl << endl << endl << endl; break; }
			cout << "Pull information of one stock:" << endl << "Please enter the ticker:  ";
			cin >> StrInput;
			if (stock_map.count(StrInput) > 0)
				stock_map[StrInput].PullStockInfo();
			else
				cout << "Invalid Input: Please re-enter your choice." << endl;
			cout << endl << endl << endl;
			break;

		case '3':
			if (!PrepareData) { cout << "Please first retrieve historical price data." << endl << endl << endl << endl; break; }
			cout << "Show AAR, AAR-SD, CAAR and CAAR-SD of one group:" << endl << "Please enter Beat, Meet or Miss: ";
			cin >> StrInput;
			if (StrInput == "Beat")
				Beat.PullGroupInfo();
			else if (StrInput == "Meet")
				Meet.PullGroupInfo();
			else if (StrInput == "Miss")
				Miss.PullGroupInfo();
			else
				cout << "Invalid Input: Please re-enter your choice." << endl;
			cout << endl << endl << endl;
			break;

		case '4':
			if (!PrepareData) { cout << "Please first retrieve historical price data." << endl << endl << endl << endl; break; }
			cout << "Show the CAAR graph of all 3 groups:" << endl << endl;
			plotResults(Beat, Meet, Miss);
			cout << endl << endl << endl;
			break;

		case '5':
			cout << "Exit the program:" << endl;
			cout << "#---------------------------------------------------------------#" << endl;
			cout << "                                                                " << endl;
			cout << "                         Exiting......                         " << endl;
			cout << "                                                                " << endl;
			cout << "                     Proudly Presented by                       " << endl;
			cout << "               Zhibai Luo, Zicheng He, Yulin Wu                 " << endl;
			cout << "                  Tianzi Zheng, Xiangjun Kong                   " << endl;
			cout << "                                                                " << endl;
			cout << "#---------------------------------------------------------------#" << endl;
			Quit = true;
			break;

		default:
			cout << "Invalid Input: Please re-enter your choice." << endl << endl << endl << endl;
			cin.clear();
			cin.sync();
			break;
		}

	}

	system("pause");
	return 0;
}
