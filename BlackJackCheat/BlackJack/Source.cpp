#include <iostream>
#include "cards.h"
#include "dealer.h"
int main()
{
	std::vector<int> results;
	dealer manager;
	for (int i = 0; i < 10; i++)
	{
		results.push_back(manager.gameAI());
	}
	for (int i = 0; i < 10; i++)
	{
		std::cout << results[i] << std::endl;
	}
	return 0;
}