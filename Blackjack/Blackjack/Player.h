#pragma once
#include"Hand.h"
class Player
{
public:
	Hand playerHand;
	Hand splitHand;
	bool didDoubleDown;
	bool didSplit;
	Player();
	Player(std::string);
	void newHand(Hand);
	void newSplitHand(Hand);
	int getPoints();
	std::string getName();
	void increasePoints();
	void resetDidDoubleDown();
	void resetDidSplit();
	~Player();
private:
	int points;
	std::string name;
};

