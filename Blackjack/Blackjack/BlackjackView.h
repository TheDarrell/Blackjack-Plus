#pragma once
#include"Deck.h"
#include"Hand.h"
#include"BlackjackGame.h"
#include <iostream>
using namespace std;

class BlackjackView
{
	
public:
	//Print out main menu
	static void mainMenu();
	//Print out rules
	static void rules();
	//Print out available options during the game
	static void gameOptions(BlackjackGame, bool canHit, bool canDouble, bool canSplit);
	//Print game state
	static void printGameState(BlackjackGame, bool didSplit1, bool didSplit2);
	//Print results screen
	static void printRoundResults(BlackjackGame, BlackjackGame::RoundResult, bool didSplit1, bool didSplit2);
	//BlackjackView();
	//~BlackjackView();
};

