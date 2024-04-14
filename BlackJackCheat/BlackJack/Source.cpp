#include <iostream>
#include "cards.h"

int main()
{
	cards box;
	struct card cardT = box.getCard();
	std::cout << cardT.value << std::endl;
	cardT = box.getCard();
	std::cout << cardT.value << std::endl;
	cardT = box.getCard();
	std::cout << cardT.value << std::endl;
	cardT = box.getCard();
	std::cout << cardT.value << std::endl;
	cardT = box.getCard();
	std::cout << cardT.value << std::endl;
	cardT = box.getCard();
	std::cout << cardT.value << std::endl;
	cardT = box.getCard();
	std::cout << cardT.value << std::endl;
	

	return 1;
}