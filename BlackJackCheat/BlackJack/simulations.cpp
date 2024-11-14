#include "simulations.h"
#define LIMIT 21
simulations::simulations(int amountOfRuns)
{
	this->amountOfRuns = amountOfRuns;
	this->sumAvg = 0;
}

float simulations::getBestMove(dealer Alldealer)
{
	this->sumAvg = 0;
	dealer currDealer = Alldealer;
	for (int i = 0; i < this->amountOfRuns; i++)
	{
		this->runSimulation(currDealer);
		currDealer = Alldealer;
	}
	return (this->sumAvg / float(this->amountOfRuns));
}

void simulations::runSimulation(dealer dealer)
//will run one simulation and adds the amount of turn if neccery
//innput:manager of the simulation
//output:none
{
	int sumUser = 0;
	int counter = this->getHighestSumCards(dealer,&sumUser);
	/*int sumDealer = dealer.dealerChoice(false);
	if (sumUser >= sumDealer||sumDealer>LIMIT)
	{
		this->sumAvg += counter;
	}*///why does it matter if he won? it matters he will get the higher card, right?
	this->sumAvg += counter;
}

int simulations::getHighestSumCards(dealer dealer,int* sumUser)
//counts the highest amount of time the user can get a card without loosing
//input:dealer-the manager for our simulation
//output:the amount of time he got a card,the sum of the cards:)
{
	card removedCard;
	int sum = dealer.getSum(dealer.USER);
	int counter = -1;
	*sumUser = sum;
	while (sum <= LIMIT)
	{
		counter++;
		removedCard=dealer.addCard(dealer.USER);
		sum = dealer.getSum(dealer.USER);
		if (sum <= LIMIT)
		{
			*sumUser = sum;
		}
	}
	return counter;
}
