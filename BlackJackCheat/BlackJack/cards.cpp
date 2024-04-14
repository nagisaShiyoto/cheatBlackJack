#include "cards.h"
int cards::MAX_VALUE = 13;
int cards::SIGN_NUM = 4;
cards::cards()
{
	createNewDeck();
}

void cards::createNewDeck()
{
	for (int i = SPADE; i <= DIMOND; i++)
	{
		struct card card;
		card.type = i;
		for (int j = 1; j <= cards::MAX_VALUE; j++)
		{
			card.value = j;
			this->cardsDeck.push_back(card);
		}
	}
}

struct card cards::getCard()
{
	struct card randCard;
	if (this->cardsDeck.size() > 0)
	{
		int num = rand() % this->cardsDeck.size();
		std::cout << num<<std::endl;
		randCard = this->cardsDeck[num];
		this->cardsDeck.erase(this->cardsDeck.begin() + num);
		return randCard;
	}
	else
	{
		throw std::exception("box is empty");
		//it wont get to here but okey
		randCard.type = -1;
		randCard.value = -1;
		return randCard;
	}
}
