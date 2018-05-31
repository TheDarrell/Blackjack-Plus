#include "Player.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


Player::Player()
{
	didDoubleDown = false;
	didSplit = false;
	points = 0;
	name = "BLANK";
	playerHand = {};
	splitHand = {};
}

Player::Player(std::string pName)
{
	didDoubleDown = false;
	didSplit = false;
	points = 0;
	name = pName;
	playerHand = {};
	splitHand = {};
}

void Player::newHand(Hand pHand)
{
	playerHand = pHand;
}

void Player::newSplitHand(Hand pHand)
{
	splitHand = pHand;
}

int Player::getPoints()
{
	return points;
}

std::string Player::getName()
{
	return name;
}

void Player::increasePoints()
{
	points++;
}

void Player::resetDidDoubleDown()
{
	didDoubleDown = false;
}

void Player::resetDidSplit()
{
	didSplit = false;
}

Player::~Player()
{
}
