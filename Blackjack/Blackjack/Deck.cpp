#include "Deck.h"
#include <iostream>
#include <random>
#include <algorithm>
#include <string>
#include <chrono>
//std::vector<Card> Deck::deck = {};
Deck::Deck()
{
	for (int i = 0; i < 52; i++)
	{
		int rank = (i / 4) + 1;
		int suit = i % 4;
		deck.push_back(Card(static_cast<Card::ranks>(rank),
			static_cast<Card::suits>(suit)));
	}
	seed = std::chrono::system_clock::now().time_since_epoch().count();
}

Deck::Deck(std::vector<Card> pDeck)
{
	deck = pDeck;
}

/*
Deck Deck::createEmptyDeck()
{
	std::vector<Card> empty{};
	deck = empty;
	return Deck(deck);
}
*/
int Deck::getSize()
{
	return deck.size();
}

Card Deck::draw()
{
	if (deck.size() == 0)
	{
		throw 100;//Random exception
	}
	else
	{
		Card c = deck.back();
		deck.pop_back();
		return c;
	}
	
}

void Deck::shuffleDeck()
{
	std::shuffle(deck.begin(), deck.end(), std::default_random_engine(seed));
}

Deck::~Deck()
{
}
