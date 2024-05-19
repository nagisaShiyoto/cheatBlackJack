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
	dealer();
	dealer(dealer& deal);//deep copy:)
	dealer operator=(dealer& rhs);
	void gameUser();
	int gameAI();
	
	int dealerChoice(bool print = true);
	int getSum(int person);
	card addCard(int person);

	cards getDeck();
	card gethiddenCard();
	std::map< int, std::vector<card>> getUsingCards();


private:
	
	cards _Deck;
	card hiddenCard;
	std::map< int, std::vector<card>> usingCards;



	int options(int place, int balance = 0);
	std::string cardToStrnig(card card);
	void gameSetup();
	int getAction(bool getAction,float prob);
	int userInteraction(bool getAction = true);
	int getResult(int dealerSum,int userSum,int betAmount);
	void printCards(int person, bool hidden = true);
};

