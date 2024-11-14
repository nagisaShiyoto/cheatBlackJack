#pragma once
#include "dealer.h"
class simulations
{
public:
	simulations(int amountOfRuns);
	float getBestMove(dealer dealer);
private:
	int sumAvg;
	int amountOfRuns;
	void runSimulation(dealer dealer);
	int getHighestSumCards(dealer dealer, int* sumUser);
};

