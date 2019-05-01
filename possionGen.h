#pragma once

#include <cstdint>
#include <iostream>
#include <fstream>
#include <random>
#include <ctime>
#include <queue>
#include <list>
#include <array>

#define TOTAL_TIME 1000.0
#define TIME_UNIT_NUM 400
#define BIN_NUM 40
#define BIN_DELTA 1

class possionGen_t
{
public:
	possionGen_t();
	~possionGen_t();
	void doOneProcessGen();
	void doAnalyze();

private:
	double lamda;	
	std::vector<double> eventCntInTimeUnit[TIME_UNIT_NUM];
};