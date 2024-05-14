#include "dealer.h"
#include <string>
#define LIMIT 21
void dealer::game()
/*
playing the game
input:none
output:none
*/
{
	int money = 100;
	int bettingAmount = 0;
	bool con = this->options(START,money);
	int userSum = 0;
	int dealerSum = 0;
	while (con&&money>0)
	{
		bettingAmount = this->options(BET);
		this->gameSetup();
		userSum=this->userInteraction();
		dealerSum = this->dealerChoice();
		money += this->getResult(dealerSum, userSum, bettingAmount);
		this->usingCards.clear();
		con = this->options(START,money);
	}
	if (money > 0)
	{
		std::cout << "come again:)" << std::endl;
	}
	else
	{
		std::cout << "better luck next time:\\" << std::endl;
	}
}

dealer::dealer():_Deck()
{
}

card dealer::addCard(int person)
{
//adding cards to the wanted person
//input:the person (dealer/user)
//output:none
	card card = this->_Deck.getCard();
	this->usingCards[person].push_back(card);
	return card;
}

void dealer::printCards(int person,bool hidden)
{
//printing the cards of the wanted person
//input:the person (dealer/user),and if to show the other dealer card
//output:none
	if (person == DEALER)
	{
		std::cout << "delers cards" << std::endl;
	}
	else
	{
		std::cout << "user cards" << std::endl;
	}
	std::cout << "--------------------------------------------------------------"<<std::endl;
	std::vector<card> cardsP = this->usingCards[person];
	for (auto it = cardsP.begin(); it != cardsP.end(); it++)
	{
		std::cout << this->cardToStrnig(*it)<<std::endl;
	}
	if (person == DEALER&&!hidden)
	{
		std::cout << this->cardToStrnig(this->hiddenCard) << std::endl;
	}
	std::cout << "--------------------------------------------------------------" << std::endl;
}

int dealer::options(int Place,int balance)
//printing the first msgs to user
//input: place- the place in the game to give the right msg
//output: the user chioce
{
	int choice = 0;
	switch (Place)
	{
	case START:
		if (balance > 0)
		{
			std::cout << "current balance: " << balance << std::endl;
			std::cout << "do u want to play?" << std::endl;
			std::cout << "1-yes 0-no" << std::endl;
			std::cin >> choice;
		}
		break;
	case BET:
		std::cout << "how much would you like to bet?" << std::endl;
		std::cin >> choice;
		break;
	default:
		throw std::exception("there isnt any place");
		break;
	}
	return choice;
}

std::string dealer::cardToStrnig(card card)
{
//turn the card info to text
//input:card info
//output: the card info in string
	std::string cardInfo = "";
	//adds the valued Text
	switch (card.value)
	{
	case JACK:
		cardInfo += "JACK";
		break;
	case KING:
		cardInfo += "KING";
		break;
	case QUEIN:
		cardInfo += "QUEIN";
		break;
	default:
		cardInfo += std::to_string( card.value);
		break;
	}
	cardInfo += " ";
	//adds the type in text
	switch (card.type)
	{
	case HEART:
		cardInfo += "HEART";
		break;
	case SPADE:
		cardInfo += "SPADE";
		break;
	case CLUB:
		cardInfo += "CLUB";
		break;
	case DIMOND:
		cardInfo += "DIMOND";
		break;
	default:
		throw std::exception("not a type");
		break;
	}
	return cardInfo;

}

void dealer::gameSetup()
{
//create the start of the game 
//input:none
//output:none
	this->addCard(DEALER);
	this->addCard(USER);
	this->hiddenCard = this->_Deck.getCard();//the dealer hidden card:)
	this->addCard(USER);

}

int dealer::getAction()
{
//print the options and get the player action
//inoput:none
//output:the user choosen action
	int option = 0;
	this->printCards(DEALER);
	std::cout << "one card ankown:(" << std::endl;
	this->printCards(USER);
	std::cout << "what would you like to do?" << std::endl;
	std::cout << "1- get another card" << std::endl;
	std::cout << "2- stay" << std::endl;
	std::cin >> option;
	return option;
}

int dealer::userInteraction()
//speak with the user and ask him what he want to do until he stay\bust
//input:none
//output:the sum of his cards
{
	int const GET_CARD = 1;
	int const STAY = 2;
	bool stay = false;
	bool bust = false;
	int option = 0;
	int sum=this->getSum(USER);
	while (!stay && !bust)
	{
		option = this->getAction();
		if (option == GET_CARD)
		{
			this->addCard(USER);
			sum = this->getSum(USER);
			if (sum > LIMIT)
			{
				this->printCards(USER);
				bust = true;
			}
		}
		else if (option == STAY)
		{
			stay = true;
		}
	}
	
	return sum;
}
int dealer::dealerChoice()
//dealer choosing the cards(by the blackjack rules)
//input:none
//output: the last sum
{
	int const DEALER_LOWEST_SUM = 17;
	int sum = this->getSum(DEALER);
	while (sum < DEALER_LOWEST_SUM)
	{
		this->addCard(DEALER);
		sum = this->getSum(DEALER);
	}
	this->printCards(DEALER,false);

	return sum;
}
int addSumCard(card it, int* aceCounter)
//get the card value
//input:the card, counter of aces to add
//output: the value
{
	int const VALUE_LIMIT = 10;
	int const ACE_VALUE = 1;
	int toAdd = 0;
	if (it.value == ACE_VALUE)
	{
		(*aceCounter)++;
		toAdd++;//ace value is atleast 1
	}
	if (it.value > VALUE_LIMIT)
	{
		toAdd += VALUE_LIMIT;
	}
	else
	{
		toAdd += it.value;
	}
	return toAdd;
}
int dealer::getSum(int person)
//return the biggest sum(until 21)
//input:the person for the num
//output:none
{
	int const VALUE_LIMIT = 10;
	int const ACE_VALUE = 1;
	int sum = 0;
	int aceCounter = 0;
	std::vector<card> wantedCards = this->usingCards[person];
	for (auto it = wantedCards.begin(); it != wantedCards.end(); it++)
	{
		sum += addSumCard(*it, &aceCounter);
	}
	if (person == DEALER)
	{
		sum += addSumCard(this->hiddenCard, &aceCounter);
	}
	//adds the aces to the highest possible
	for (int i = 0; i < aceCounter&&sum<=(LIMIT-VALUE_LIMIT); i++)
	{
		sum += VALUE_LIMIT;
	}
	return sum;
}

int dealer::getResult(int dealerSum, int userSum,int betAmaount)
//get the sums and responde to the rusalt of the game
//input:dealer's and user's sums,and the bet
//output:the amount of money given to user(minus is taking)
{
	if (userSum > LIMIT)
	{
		return -betAmaount;
	}
	else if(userSum==LIMIT)
	{
		return 2.5 * betAmaount;
	}
	else if(dealerSum>LIMIT|| dealerSum < userSum)
	{
		return 2 * betAmaount;
	}
	else
	{
		return -betAmaount;
	}
	return 0;
}
