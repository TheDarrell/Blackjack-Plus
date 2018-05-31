#include "Card.h"



Card::Card(ranks pRank, suits pSuit)
{
	rank = pRank;
	suit = pSuit;
}

std::string Card::toString()
{
	if (rankNames.empty())
		setupMaps();
	return rankNames[rank] + " of " + suitNames[suit];
}

Card::~Card()
{
}

void Card::setupMaps()
{
	rankNames[Ace] = "Ace";
	rankNames[Two] = "Two";
	rankNames[Three] = "Three";
	rankNames[Four] = "Four";
	rankNames[Five] = "Five";
	rankNames[Six] = "Six";
	rankNames[Seven] = "Seven";
	rankNames[Eight] = "Eight";
	rankNames[Nine] = "Nine";
	rankNames[Ten] = "Ten";
	rankNames[Jack] = "Jack";
	rankNames[Queen] = "Queen";
	rankNames[King] = "King";

	suitNames[Clubs] = "Clubs";
	suitNames[Spades] = "Spades";
	suitNames[Hearts] = "Hearts";
	suitNames[Diamonds] = "Diamonds";
}
