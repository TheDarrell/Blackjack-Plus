#pragma once
#include"Card.h"
#include<vector>
class Hand
{
public:
	std::vector<Card> hand;
	Hand();
	Hand(std::vector<Card>);
	void addCard(Card);
	int getValue();
	bool isBust();
	bool canSplit();
	bool canDoubleDown();
	bool isEmpty();
	std::string toString();
	~Hand();
};

