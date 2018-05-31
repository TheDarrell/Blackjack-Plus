#include "Hand.h"
#include <algorithm> 


Hand::Hand()
{
	hand = std::vector<Card>{};
}

Hand::Hand(std::vector<Card> pHand)
{
	hand = pHand;
}

void Hand::addCard(Card newCard)
{
	hand.push_back(newCard);
}

int Hand::getValue()
{
	int value = 0;
	int altValue = 0;
	int counter = 0;
	for (Card c : hand)
	{
		if (c.rank == Card::Ace)
			counter++;
		if (c.rank > 10)
			value = value + 10;//All face cards are worth 10
		else
			value = value + c.rank;
	}
	if(value < 21)//Ace can be worth 1 or 11
	{
		for (int i = 0; i < counter && value < 21; i++)
		{
			value += 10;
		}
		if (value > 21)
			value -= 10;
	}
	return value;
}

bool Hand::isBust()
{
	return getValue() > 21;
}

bool Hand::canSplit()
{
	return hand.size() == 2 && 
		hand.at(0).rank == hand.at(1).rank;
}

bool Hand::canDoubleDown()
{
	return hand.size() == 2 &&
		getValue() >= 9 && getValue() <= 11;
}

bool Hand::isEmpty()
{
	return hand.size() == 0;
}


std::string Hand::toString()
{
	std::string s = "";
	bool first = true;
	for (Card c : hand)
	{
		if (first)
		{
			s = s + c.toString();
			first = false;
		}
		else
			s = s + ", " + c.toString();
	}
	return s;
}


Hand::~Hand()
{
}
