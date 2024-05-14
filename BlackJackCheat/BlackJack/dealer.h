#pragma once
#include "cards.h"
#include <map>
enum place
{
	START,
	BET,
	MID
};
class dealer
{
public:
	const int DEALER = 0;
	const int USER = 1;
	void game();
	dealer();
	
private:
	card addCard(int person);
	void printCards(int person, bool hidden=true);
	cards _Deck;
	card hiddenCard;
	std::map< int, std::vector<card>> usingCards;
	int options(int place, int balance = 0);
	std::string cardToStrnig(card card);
	void gameSetup();
	int getAction();
	int userInteraction();
	int dealerChoice();
	int getSum(int person);
	int getResult(int dealerSum,int userSum,int betAmount);
};

