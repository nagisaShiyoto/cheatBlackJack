#include "dealer.h"
#include "simulations.h"
#include <string>
#define LIMIT 21
#define TO_PRECENT 100

void dealer::gameUser()
/*
user playing the game
input:none
output:none
*/
{
	int money = 100;
	int bettingAmount = 0;
	bool con = this->options(START, money);
	int userSum = 0;
	int dealerSum = 0;
	while (con && money > 0)
	{
		bettingAmount = this->options(BET);
		this->gameSetup();
		userSum = this->userInteraction();
		dealerSum = this->dealerChoice();
		money += this->getResult(dealerSum, userSum, bettingAmount);
		this->usingCards.clear();
		con = this->options(START, money);
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



int dealer::gameAI()
/*
algorythem playing the game
input:none
output:none
*/
{
	int highestMoney = 100;
	int money = 100;
	int bettingAmount = 50;
	bool con = true;
	int userSum = 0;
	int dealerSum = 0;
	while (con&&money>0)
	{
		this->gameSetup();
		userSum=this->userInteraction(false);
		dealerSum = this->dealerChoice();
		money += this->getResult(dealerSum, userSum, bettingAmount);
		if (money > highestMoney)
		{
			highestMoney = money;
		}
		this->usingCards.clear();
		std::cout << "---------------------------------------------------" << std::endl;
		std::cout << money << std::endl;
		std::cout << "---------------------------------------------------" << std::endl;
	}
	if (money > 0)
	{
		std::cout << "come again:)" << std::endl;
	}
	else
	{
		std::cout << "better luck next time:\\" << std::endl;
	}
	std::cout << "highest money: " << highestMoney << std::endl;
	return highestMoney;
}




dealer::dealer():_Deck()
{
}
dealer::dealer(dealer& deal)
{
	this->hiddenCard = deal.gethiddenCard();
	this->_Deck = deal.getDeck();
	this->usingCards = deal.getUsingCards();
}

dealer dealer::operator=(dealer& rhs)
{
	dealer copy(rhs);
	return copy;
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
int dealer::getAction(bool getAction, float prob)
{
//print the options and get the player action
//inoput:getACtion-if the user want the algo to choose for him,
//		prob-the probabality you should take another card
//output:the user choosen action
	float const MIN_ADD_CARD = 0.5;
	int option = 0;
	int const GET_CARD = 1;
	int const STAY = 2;
	this->printCards(DEALER);
	std::cout << "one card ankown:(" << std::endl;
	this->printCards(USER);
	if (getAction)
	{
		std::cout << "what would you like to do?" << std::endl;
		std::cout << "1- get another card" << std::endl;
		std::cout << "2- stay" << std::endl;
		std::cin >> option;
	}
	else if(prob>=MIN_ADD_CARD)
	{
		option = GET_CARD;
	}
	else
	{
		option = STAY;
	}

	return option;
}
int dealer::userInteraction(bool getAction)
//speak with the user and ask him what he want to do until he stay\bust
//input:none
//output:the sum of his cards
{
	float const MIN_ADD_CARD = 0.5;
	int const SIM_NUM = 10000;
	int const GET_CARD = 1;
	int const STAY = 2;
	bool stay = false;
	bool bust = false;
	int option = 0;
	int sum=this->getSum(USER);
	simulations sim(SIM_NUM);
	float amountOfTries = 0;
	while (!stay && !bust)
	{
		amountOfTries = sim.getBestMove(*this);
		std::cout << "the probabilty you can draw another card is: " <<
			amountOfTries* TO_PRECENT <<"%" << std::endl;
		option=this->getAction(getAction, amountOfTries);
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
int dealer::dealerChoice(bool print)
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
	if (print)
	{
		this->printCards(DEALER, false);
	}

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


cards dealer::getDeck()
{
	return this->_Deck;
}
card dealer::gethiddenCard()
{
	return this->hiddenCard;
}
std::map<int, std::vector<card>> dealer::getUsingCards()
{
	return this->usingCards;
}









