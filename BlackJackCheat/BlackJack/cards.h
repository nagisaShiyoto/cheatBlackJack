#pragma once
#include <vector>
#include <iostream>
#include <cstdlib>
enum types
{
	SPADE = 1,
	HEART,
	CLUB,
	DIMOND
};
struct card
{
	int value;
	int type;

};
class cards
{
public:
	static int MAX_VALUE;
	static int SIGN_NUM;
	cards();
	void createNewDeck();
	struct card getCard();
private:
	std::vector<struct card> cardsDeck;
};

