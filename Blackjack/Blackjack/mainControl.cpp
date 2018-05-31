#include"Deck.h"
#include"Card.h"
#include"BlackjackView.h"
#include <iostream>
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>

using namespace std;

std::string getMainMenuInput();
bool executeMainMenu(std::string option);
static inline void trim(std::string &s);
std::string getGameOptionInput(bool canHit, bool canDouble, bool canSplit);
bool executeGameOption(std::string option, BlackjackGame& game, bool doOrig);
void startGame(BlackjackGame game, bool isAI);

int main()
{	
	bool running = true;
	while(running)
		running = executeMainMenu(getMainMenuInput());
}

std::string getMainMenuInput()
{
	bool check = false;
	std::string mainOption = "";
	
	do {
		BlackjackView::mainMenu();
		cin >> mainOption;
		trim(mainOption);
		std::transform(mainOption.begin(), mainOption.end(), mainOption.begin(), ::tolower);
		if (mainOption == "human" || mainOption == "ai" ||
			mainOption == "rules" || mainOption == "quit")
		{
			check = true;
		}
		else
		{
			cin.clear();
			cin.ignore();
			cout << "Input must be human, ai, rules, or quit!" << endl;
		}
	} while (!check);
	return mainOption;
}

bool executeMainMenu(std::string option)
{
	if (option == "human")
	{
		startGame(BlackjackGame(false), false);
	}
	else if (option == "ai")
	{
		cout << "Not implemented yet" << endl;
	}
	else if (option == "rules")
	{
		BlackjackView::rules();
		cout << "\nPress enter to go back!" << endl;
		//std::string stall = "";
		//cin >> stall;
		cin.get();
		cin.get();
	}
	else if (option == "quit")
	{
		cout << "Bye!" << endl;
		return false;
	}
	return true;
}

void startGame(BlackjackGame game, bool isAI)
{
	bool doSurrender = false;
	while (!game.isFinsihed() && !doSurrender)
	{
		game.drawSequence();
		bool didSplit1 = false;
		bool didSplit2 = false;
		bool canDouble = false;
		bool canSplit = false;
		bool canHit = true;
		bool doOrig = true;
		while (game.getSwitchCounter() < 2 && !doSurrender)//Keep going until both players complete their turns
		{
			//Once it sets true, need to keep it true in order to print out split hand
			if (!didSplit1)
				didSplit1 = game.getCurrentPlayer().didSplit;
			if (!didSplit2)
				didSplit2 = game.getSecondPlayer().didSplit;

			//A way for non-split turns to do original hand only &
			//split turns to do original first, then split hand
			if(didSplit1)
				doOrig = game.getCurrentPlayer().didSplit;
			else
				doOrig = !game.getCurrentPlayer().didSplit;

			//Determine to use original hand or split hand
			//doOrig = !game.getCurrentPlayer().didSplit;//Needs rework
			if (doOrig)
			{
				canDouble = game.getCurrentPlayer().playerHand.canDoubleDown();
				canSplit = game.getCurrentPlayer().playerHand.canSplit();
				canHit = !game.isFinsihed() && !game.getCurrentPlayer().playerHand.isBust();
			}
			else
			{
				canDouble = game.getCurrentPlayer().splitHand.canDoubleDown();
				canSplit = game.getCurrentPlayer().splitHand.canSplit();
				canHit = !game.isFinsihed() && !game.getCurrentPlayer().splitHand.isBust();
			}
			BlackjackView::printGameState(game, didSplit1, didSplit2);
			//BlackjackView::gameOptions(canHit, canDouble, canSplit);
			doSurrender = executeGameOption(getGameOptionInput(canHit, canDouble, canSplit), game, doOrig);
		}
		if (!doSurrender)
		{
			game.resetSwitchCounter();
			BlackjackView::printRoundResults(game, game.calcWinner(), didSplit1, didSplit2);
			cout << endl;
		}
		
	}
	cout << "\nGame is finished!"<< endl;
	cout << game.getPlayer1().getName() << " Points: " << game.getPlayer1().getPoints() << endl;
	cout << game.getPlayer2().getName() << " Points: " << game.getPlayer2().getPoints() << endl;
	if(doSurrender)
		cout << "Winner is " << game.getSecondPlayer().getName() << " by forfeit!" << endl;
	else
		cout << "Winner is " << game.gameWinner().getName() << "!" << endl;

}

std::string getGameOptionInput(bool canHit, bool canDouble, bool canSplit)
{
	bool check = false;
	std::string gameOption = "";

	do {
		BlackjackView::gameOptions(canHit, canDouble, canSplit);
		cin >> gameOption;
		trim(gameOption);
		std::transform(gameOption.begin(), gameOption.end(), gameOption.begin(), ::tolower);
		if (gameOption == "stay" || (gameOption == "hit" && canHit) || (gameOption == "split" && canSplit)
			|| (gameOption == "doubledown" && canDouble) || gameOption == "surrender")
		{
			check = true;
		}
		else
		{
			cin.clear();
			cin.ignore();
			std::string valid = "";
			if (canHit)
				valid = valid + ", hit";
			if (canSplit)
				valid = valid + ", split";
			if (canDouble)
				valid = valid + ", doubledown";
			cout << "Input must be stay" << valid << ", or surrender!" << endl;
		}
	} while (!check);
	return gameOption;
}

bool executeGameOption(std::string option, BlackjackGame& game, bool doOrig)
{
	if (option == "stay")
	{
		game.executeStay();
	}
	else if (option == "hit")
	{
		if(game.executeHit(doOrig))
			cout << "BUST!" << endl;
	}
	else if (option == "split")
	{
		game.executeSplit();
	}
	else if (option == "doubledown")
	{
		game.executeDoubleDown(doOrig);
	}
	else if (option == "surrender")
	{
		cout << "You have surrendered!" << endl;
		return true;
	}
	return false;
}

// trim from start (in place)
static inline void ltrim(std::string &s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(),
		std::not1(std::ptr_fun<int, int>(std::isspace))));
}

// trim from end (in place)
static inline void rtrim(std::string &s) {
	s.erase(std::find_if(s.rbegin(), s.rend(),
		std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s) {
	ltrim(s);
	rtrim(s);
}