#pragma once
#include<string>
#include<map>
class Card
{
	public:
		enum ranks {
			Ace = 1, Two, Three, Four, Five, Six, Seven,
			Eight, Nine, Ten, Jack, Queen, King
		};
		enum suits { Clubs, Spades, Hearts, Diamonds };
		ranks rank;
		suits suit;
		std::map<ranks, std::string> rankNames;
		std::map<suits, std::string> suitNames;
		Card(ranks pRank, suits pSuit);
		std::string toString();
		~Card();
	private:
		void setupMaps();
};

