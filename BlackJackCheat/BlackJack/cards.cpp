#include "cards.h"
int cards::MAX_VALUE = 13;
int cards::SIGN_NUM = 4;
cards::cards()
{
	/*
	create the cardDeck
	input:none
	output:none
	*/
	srand(time(0));
	createNewDeck();
}

void cards::createNewDeck()
{
	/*
	fill the cards' vector with all the needed cards
	input:none
	output:none
	*/
	for (int i = SPADE; i <= DIMOND; i++)
	{
		card card;
		card.type = i;
		for (int j = 1; j <= cards::MAX_VALUE; j++)
		{
			card.value = j;
			this->_cardsDeck.push_back(card);
		}
	}
}

card cards::getCard()
{
	/*
	gets random card from the deck and remove him afterwards
	input:none
	output: the random card
	*/
	card randCard;
	if (this->_cardsDeck.size() > 0)//check if there is any cards in deck
	{
		int num = rand() % this->_cardsDeck.size();//gets random place
		randCard = this->_cardsDeck[num];//get card
		this->_cardsDeck.erase(this->_cardsDeck.begin() + num);//remove card
		return randCard;
	}
	else
	{
		this->createNewDeck();
		//throw std::exception("box is empty");
		//it wont get to here but okey
		//randCard.type = -1;
		//randCard.value = -1;
		return this->getCard();
	}
}
