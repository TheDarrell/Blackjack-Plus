#pragma once
#include"Card.h"
#include<vector>

class Deck
{
	public:
		Deck();
		Deck(std::vector<Card>);
		//static Deck createEmptyDeck();
		int getSize();
		Card draw();
		void shuffleDeck();
		~Deck();
	private:
		std::vector<Card> deck;
		unsigned seed;
};

