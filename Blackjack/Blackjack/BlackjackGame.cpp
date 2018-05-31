#include "BlackjackGame.h"
#include <iostream>
BlackjackGame::BlackjackGame(bool isAI)
{
	isComp = isAI;
	player1 = Player("Player 1");
	player2 = Player("Player 2");
	deck = Deck();
	deck.shuffleDeck();
	round = 1;
	currentPlayer = player1;
	secondPlayer = player2;
	switchCounter = 0;
}

void BlackjackGame::drawSequence()
{
	Hand h1 = Hand();
	Hand h2 = Hand();
	try
	{
		h1.addCard(deck.draw());
		h2.addCard(deck.draw());
		h1.addCard(deck.draw());
		h2.addCard(deck.draw());
	}
	catch (int e)
	{
		//std::cout << "Excep. Deck size: " << deck.getSize() << std::endl;
	}
	currentPlayer.newHand(h1);
	currentPlayer.newSplitHand(Hand());
	secondPlayer.newHand(h2);
	secondPlayer.newSplitHand(Hand());
}

bool BlackjackGame::executeHit(bool doOrig)
{
	Hand h = Hand();
	if (doOrig)
	{
		currentPlayer.playerHand.addCard(deck.draw());
		h = currentPlayer.playerHand;
	}		
	else
	{
		currentPlayer.splitHand.addCard(deck.draw());
		h = currentPlayer.splitHand;
	}	
	if (h.isBust())
	{
		currentPlayer.resetDidSplit();
		if(!currentPlayer.didSplit)
			switchPlayer();
		return true;
	}
	return false;
}

void BlackjackGame::executeStay()
{
	if (!currentPlayer.didSplit)
		switchPlayer();
	else
		currentPlayer.resetDidSplit();
}

void BlackjackGame::executeSplit()
{
	currentPlayer.newSplitHand(Hand(std::vector<Card> {currentPlayer.playerHand.hand.at(1)}));
	currentPlayer.newHand(Hand(std::vector<Card> {currentPlayer.playerHand.hand.at(0)}));
	currentPlayer.didSplit = true;
}

void BlackjackGame::executeDoubleDown(bool doOrig)
{
	Hand h = Hand();
	if (doOrig)
	{
		currentPlayer.playerHand.addCard(deck.draw());
		h = currentPlayer.playerHand;
	}
	else
	{
		currentPlayer.splitHand.addCard(deck.draw());
		h = currentPlayer.splitHand;
	}
	if (!currentPlayer.didSplit)
	{
		currentPlayer.didDoubleDown = true;
		switchPlayer();
	}
	else
	{
		currentPlayer.didDoubleDown = true;
		currentPlayer.resetDidSplit();
	}
	
}


Player BlackjackGame::gameWinner()
{
	if (isFinsihed())
	{
		if (player1.getPoints() > player2.getPoints())
			return player1;
		else if (player2.getPoints() > player1.getPoints())
			return player2;
		else
			return Player(0);//Signify Tie
	}
	return Player();//Negative id signify invalid
}

bool BlackjackGame::isFinsihed()
{
	return deck.getSize() == 0;
}

Player BlackjackGame::getPlayer1()
{
	return player1;
}

Player BlackjackGame::getPlayer2()
{
	return player2;
}

Player BlackjackGame::getCurrentPlayer()
{
	return currentPlayer;
}

Deck BlackjackGame::getDeck()
{
	return deck;
}

int BlackjackGame::getRound()
{
	return round;
}

int BlackjackGame::getSwitchCounter()
{
	return switchCounter;
}

void BlackjackGame::resetSwitchCounter()
{
	switchCounter = 0;
}

BlackjackGame::RoundResult BlackjackGame::calcWinner()
{
	Hand bestCurrentPlayerHand = Hand();
	Hand bestSecondPlayerHand = Hand();
	RoundResult result;
	result.points1 = 0;
	result.points2 = 0;
	result.player1 = currentPlayer.getName();
	result.player2 = secondPlayer.getName();
	//Player 1's best hand
	if (!currentPlayer.playerHand.isBust() &&
		currentPlayer.playerHand.getValue() >= 
		(currentPlayer.splitHand.getValue() && !currentPlayer.splitHand.isBust()))
	{
		bestCurrentPlayerHand = currentPlayer.playerHand;
	}	
	else if(!currentPlayer.splitHand.isBust())
		bestCurrentPlayerHand = currentPlayer.splitHand;
	//Player 2's best hand
	if (!secondPlayer.playerHand.isBust() &&
		secondPlayer.playerHand.getValue() >= 
		(secondPlayer.splitHand.getValue() && !secondPlayer.splitHand.isBust()))
	{
		bestSecondPlayerHand = secondPlayer.playerHand;
	}	
	else if (!secondPlayer.splitHand.isBust())
		bestSecondPlayerHand = secondPlayer.splitHand;

	//Notes: if both hands are bust or orig hand is bust & no split hand, the best hand will be empty

	//Player 1 Wins
	if (bestCurrentPlayerHand.getValue() > bestSecondPlayerHand.getValue())
	{
		currentPlayer.increasePoints();
		result.points1++;
		if (currentPlayer.didDoubleDown)
		{
			currentPlayer.increasePoints();
			result.points1++;
		}
		if (isFinsihed())
		{
			currentPlayer.increasePoints();
			result.points1++;
		}
		result.winner = currentPlayer.getName();
	}
	//Player 2 Wins
	if (bestSecondPlayerHand.getValue() > bestCurrentPlayerHand.getValue())
	{
		secondPlayer.increasePoints();
		result.points2++;
		if (secondPlayer.didDoubleDown)
		{
			secondPlayer.increasePoints();
			result.points2++;
		}
		if (isFinsihed())
		{
			secondPlayer.increasePoints();
			result.points2++;
		}
		result.winner = secondPlayer.getName();
	}
	//Tie: no points if both players bust
	if (!bestCurrentPlayerHand.isEmpty() && !bestSecondPlayerHand.isEmpty() &&
		bestCurrentPlayerHand.getValue() == bestSecondPlayerHand.getValue())
	{
		currentPlayer.increasePoints();
		secondPlayer.increasePoints();
		result.points1++;
		result.points2++;
		if (currentPlayer.didDoubleDown)
		{
			currentPlayer.increasePoints();
			result.points1++;
		}
		if (secondPlayer.didDoubleDown)
		{
			secondPlayer.increasePoints();
			result.points2++;
		}
		if (isFinsihed())
		{
			currentPlayer.increasePoints();
			secondPlayer.increasePoints();
			result.points1++;
			result.points2++;
		}	
		result.winner = "Tie!";
	}
	//Reset didDoubleDown
	currentPlayer.resetDidDoubleDown();
	secondPlayer.resetDidDoubleDown();

	round++;
	return result;
}

void BlackjackGame::switchPlayer()
{
	if (currentPlayer.getName() == player1.getName())
	{
		player1 = currentPlayer;//Transfer updates to player from current
		player2 = secondPlayer;
		currentPlayer = player2;
		secondPlayer = player1;
	}
	else
	{
		player2 = currentPlayer;//Transfer updates to player from current
		player1 = secondPlayer;
		currentPlayer = player1;
		secondPlayer = player2;
	}
	switchCounter++;
}

/*
Player* BlackjackGame::secondPlayer()
{
	if (currentPlayer.getName() == player1.getName())
		return &player2;
	else
		return &player1;
}
*/

Player BlackjackGame::getSecondPlayer()
{
	return secondPlayer;
}

BlackjackGame::~BlackjackGame()
{
}