#pragma once
#ifndef MyCurl_h
#define MyCurl_h

#include <map>
#include <string>
#include "Stock.h"
#include "ETF.h"
#include "Stratify.h"
#pragma warning(disable:4996)

using namespace std;

int GetPriceData(map<string, Stock>& StkMap, ETF& Benchmark);
struct MemoryStruct {
	char* memory;
	size_t size;
};
void* myrealloc(void* ptr, size_t size);
size_t write_data2(void* ptr, size_t size, size_t nmemb, void* data);
string getTimeinSeconds(string Time);


#endif // !MyCurl_h

