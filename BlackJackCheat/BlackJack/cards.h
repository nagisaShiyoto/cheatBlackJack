#pragma once
#include <vector>
#include <iostream>
class cards
{
public:
	static int MAX_VALUE;
	static int SIGN_NUM;
	cards();
private:
	std::vector<int> cardsDeck;
};

