#pragma once
#include"Player.h"
#include"Deck.h"
class BlackjackGame
{
public:
	
	struct RoundResult {
		std::string winner;
		std::string player1;
		std::string player2;
		int points1;
		int points2;
		Hand hand1;
		Hand hand2;
	};
	
	BlackjackGame(bool);
	void drawSequence();
	bool executeHit(bool);
	void executeStay();
	void executeSplit();
	void executeDoubleDown(bool);
	Player gameWinner();
	RoundResult calcWinner();
	bool isFinsihed();
	Player getPlayer1();
	Player getPlayer2();
	Player getCurrentPlayer();
	Player getSecondPlayer();
	Deck getDeck();
	int getRound();
	int getSwitchCounter();
	void resetSwitchCounter();
	~BlackjackGame();
private:
	Deck deck;
	Player player1;
	Player player2;
	Player currentPlayer;
	Player secondPlayer;
	int round;
	bool isComp;
	int switchCounter;
	
	void switchPlayer();
	
	
};

