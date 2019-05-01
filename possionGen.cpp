#include "possionGen.h"


possionGen_t::possionGen_t()
{
	lamda = 16.0;

}

possionGen_t::~possionGen_t()
{


}

void possionGen_t::doOneProcessGen()
{
	auto seed = 1000;
	std::default_random_engine generator(seed);
	std::uniform_real_distribution<float> distribution(0.0,1.0);
		
	{	
		auto t = 0.0;
		auto I = 0u;
		auto T = TOTAL_TIME;
		double deltaT = TOTAL_TIME / TIME_UNIT_NUM;
		double lamda_timeUnit = lamda / deltaT;

		for (auto ii = 0; ii < TIME_UNIT_NUM; ii++)
			eventCntInTimeUnit[ii].clear();
		
		while(1)
		{
			auto u = distribution(generator);
			auto delta_t = -(1.0 / (lamda_timeUnit)) * log(u);
			t = t + delta_t;
			if (t > T) break;
			I++; 			
			uint32_t deltaIdx = floor(t / deltaT);
			//printf("deltaIdx %d %f %f\n", deltaIdx, t,delta_t);
			eventCntInTimeUnit[deltaIdx].push_back(t);
		}		
	}		
}

void possionGen_t::doAnalyze()
{
	std::array<double, BIN_NUM> statisticArray;

	for (auto i = 0; i < BIN_NUM; i++)
		statisticArray[i] = 0;

	auto totalCnt = 0;

	for (auto i = 0; i < TIME_UNIT_NUM; i++)
	{
		auto eventCnt = eventCntInTimeUnit[i].size();
		auto binIdx = eventCnt / BIN_DELTA;
		std::cout << "i " << i << " binIdx " << binIdx << "\n";
		statisticArray[binIdx]++;
	}
	totalCnt = TIME_UNIT_NUM;

	
	std::ofstream fpOut;
	fpOut.open("testPlot");
	double tmpFacot = 1;
	for (auto i = 0; i < BIN_NUM; i++)
	{
		if (i == 0)
			tmpFacot = 1;
		else
			tmpFacot = tmpFacot * i;

		
		auto theoremOut = exp(-1 * lamda) * pow(lamda, i) / tmpFacot;
		auto simOut = statisticArray[i] / TIME_UNIT_NUM;
		//theoremOut = 0;
		std::cout << i << " " << simOut << " " << theoremOut << " power " << pow(lamda, i) << std::endl;
		fpOut << i << " " << simOut << " " << theoremOut << std::endl;
	}
	fpOut.close();
}
