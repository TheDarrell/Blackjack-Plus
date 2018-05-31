#include"Deck.h"
#include"Card.h"
#include"BlackjackView.h"
#include <iostream>
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>

using namespace std;

string getMainMenuInput();
bool executeMainMenu(std::string option);
string removeSpaces(string);
string getGameOptionInput(BlackjackGame game,bool canHit, bool canDouble, bool canSplit);
bool executeGameOption(string option, BlackjackGame& game, bool doOrig);
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
	string mainOption = "";
	
	do {
		BlackjackView::mainMenu();
		cin >> mainOption;
		mainOption = removeSpaces(mainOption);
		transform(mainOption.begin(), mainOption.end(), mainOption.begin(), tolower);
		if (mainOption == "human" || mainOption == "ai" ||
			mainOption == "rules" || mainOption == "quit")
		{
			check = true;
		}
		else
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
		bool didSplitCurrent = false;
		bool didSplitSecond = false;
		bool canDouble = false;
		bool canSplit = false;
		bool canHit = true;
		bool doOrig = true;
		while (game.getSwitchCounter() < 2 && !doSurrender)//Keep going until both players complete their turns
		{
			//Once it sets true, need to keep it true in order to print out split hand
			if (!didSplitCurrent)
				didSplitCurrent = game.getCurrentPlayer().didSplit;
			if (!didSplitSecond)
				didSplitSecond = game.getSecondPlayer().didSplit;

			//A way for non-split turns to do original hand only &
			//split turns to do original first, then split hand
			if(didSplitCurrent)
				doOrig = game.getCurrentPlayer().didSplit;
			else
				doOrig = !game.getCurrentPlayer().didSplit;

			//Determine to use original hand or split hand
			if (doOrig)
			{
				canDouble = game.getCurrentPlayer().playerHand.canDoubleDown();
				if (didSplitCurrent)//If split occurs, don't let the same player split again
					canSplit = false;
				else
					canSplit = game.getCurrentPlayer().playerHand.canSplit();
				canHit = !game.isFinsihed() && !game.getCurrentPlayer().playerHand.isBust();
			}
			else
			{
				canDouble = game.getCurrentPlayer().splitHand.canDoubleDown();
				if (didSplitCurrent)//If split occurs, don't let the same player split again
					canSplit = false;
				else
					canSplit = game.getCurrentPlayer().splitHand.canSplit();
				canHit = !game.isFinsihed() && !game.getCurrentPlayer().splitHand.isBust();
			}
			BlackjackView::printGameState(game, didSplitCurrent, didSplitSecond);
			int switchCheck = game.getSwitchCounter();
			doSurrender = executeGameOption(getGameOptionInput(game, canHit, canDouble, canSplit), game, doOrig);
			if (switchCheck != game.getSwitchCounter())//if Switching occurs, also switch the values for didSplit
			{
				bool temp = didSplitCurrent;
				didSplitCurrent = didSplitSecond;
				didSplitSecond = temp;
			}

		}
		if (!doSurrender)
		{
			game.switchPlayer(); //Each player take turns going first
			game.resetSwitchCounter();
			BlackjackView::printRoundResults(game, game.calcWinner(), didSplitCurrent, didSplitSecond);
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

std::string getGameOptionInput(BlackjackGame game, bool canHit, bool canDouble, bool canSplit)
{
	bool check = false;
	string gameOption = "";

	do {
		BlackjackView::gameOptions(game, canHit, canDouble, canSplit);
		cin >> gameOption;
		gameOption = removeSpaces(gameOption);
		transform(gameOption.begin(), gameOption.end(), gameOption.begin(), tolower);
		if (gameOption == "stay" || (gameOption == "hit" && canHit) || (gameOption == "split" && canSplit)
			|| (gameOption == "doubledown" && canDouble) || gameOption == "surrender")
		{
			check = true;
		}
		else
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			string valid = "";
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

bool executeGameOption(string option, BlackjackGame& game, bool doOrig)
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

// Function to remove all spaces from a given string
string removeSpaces(string str)
{
	str.erase(remove(str.begin(), str.end(), ' '), str.end());
	return str;
}