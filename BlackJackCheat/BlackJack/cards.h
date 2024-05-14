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
enum ROYALTY
{
	JACK = 11,
	QUEIN,
	KING
};
typedef struct card
{
	int value;
	int type;

}card;
class cards
{
public:
	static int MAX_VALUE;
	static int SIGN_NUM;
	cards();
	void createNewDeck();
	card getCard();
private:
	std::vector<card> _cardsDeck;
};

