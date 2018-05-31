#include "BlackjackView.h"

void BlackjackView::mainMenu()
{
	cout << "\nWelcome to Blackjack Plus!" << endl;
	cout << "Main Menu" << endl;
	cout << "----------" << endl;
	cout << "1. Play against human (Human)" << endl;
	cout << "2. Play against A.I. (AI)" << endl;
	cout << "3. Rules" << endl;
	cout << "4. Quit" << endl;
}

void BlackjackView::rules()
{
	cout << "\nRules of Blackjack Plus" << endl;
	cout << "------------------------" << endl;
	cout << "\nGoal:" << endl;
		cout << "\tThe goal is to get as close to 21 as possible, without going over 21 (bust)." << endl;
		cout << "\tWhichever player is closer to 21 without going bust gets 1 point for the round. Both" << endl;
		cout << "\tplayers get points if there is a tie. Game keeps going until there are no more" << endl;
		cout << "\tcards left in the deck. Whoever wins the last round gets a bonus point. Player with the " << endl;
		cout << "\tmost points win the game." << endl;

	cout << "\nGame Flow:" << endl;
		cout << "\tGame starts with each player given 2 cards. If the deck only has 1 card left, the" << endl;
		cout << "\tfirst player in that turn automatically wins." << endl;

		cout << "\n\tAfter the cards are dealt, the first player can choose to draw more cards (hit)" << endl;
		cout << "\tor not (stay)." << endl;
			cout << "\t\tChoosing hit draws a card from a deck & the player has the choice to hit or stay" << endl;
			cout << "\t\tuntil they stay. Choosing stay goes to the next player's turn or goes to current" << endl;
			cout << "\t\tplayer's next hand if split." << endl;

			cout << "\n\t\tThe player has the option to double down if the original 2 cards equal" << endl;
			cout << "\t\tto 9, 10, or 11. If the player chooses this, the player can only draw 1 card and if they" << endl;
			cout << "\t\twin or tie the round, they get 2 points." << endl;

			cout << "\n\t\tThe player has the option to split if the original 2 cards are a pair." << endl;
			cout << "\t\tEach card counts as a separate hand and can hit or stay individually. Only 1 of them" << endl;
			cout << "\t\thas to win or tie to get 1 point for the round." << endl;
		cout << "\n\tCalculates who win in the round after both players complete their actions." << endl;
}

void BlackjackView::gameOptions(bool canHit, bool canDouble, bool canSplit)
{
	int counter = 2;
	cout << "\nWhat to do?" << endl;
	cout << "1. Stay" << endl;
	if (canHit)
	{
		cout << counter << ". Hit" << endl;
		counter++;
	}
	else if (canDouble)
	{
		cout << counter << ". Double Down" << endl;
		counter++;
	}	
	if (canSplit)
		cout << counter << ". Split" << endl;
	cout << counter << ". Surrender" << endl;
}

void BlackjackView::printGameState(BlackjackGame game, bool didSplit1, bool didSplit2)
{
	cout << "-----------------------------------------" << endl;
	cout << "Round " << game.getRound() << " - " << game.getCurrentPlayer().getName() << " Turn" << endl;
	cout << "-----------------------------------------" << endl;
	cout << "Deck Size: " << game.getDeck().getSize() << endl;
	cout << game.getCurrentPlayer().getName() << " Points: " << game.getCurrentPlayer().getPoints() << endl;
	cout << game.getSecondPlayer().getName() << " Points: " << game.getSecondPlayer().getPoints() << endl;
	cout << "-----------------------------------------" << endl;
	cout << game.getCurrentPlayer().getName() << " Hand: " << game.getCurrentPlayer().playerHand.toString() 
		<< " Value: " << game.getCurrentPlayer().playerHand.getValue() << endl;
	if(didSplit1)//This variable is needed since player.didSplit will reset after completing one hand
		cout << game.getCurrentPlayer().getName() << " Split Hand: " << game.getCurrentPlayer().splitHand.toString()
			<< " Value: " << game.getCurrentPlayer().splitHand.getValue() << endl;
	cout << game.getSecondPlayer().getName() << " Hand: " << game.getSecondPlayer().playerHand.toString() 
		<< " Value: " << game.getSecondPlayer().playerHand.getValue() << endl;
	if (didSplit2)//Same as above
		cout << game.getSecondPlayer().getName() << " Split Hand: " << game.getSecondPlayer().splitHand.toString() 
		<< " Value: " << game.getSecondPlayer().splitHand.getValue() << endl;
	cout << "-----------------------------------------" << endl;
}

void BlackjackView::printRoundResults(BlackjackGame game, BlackjackGame::RoundResult result, bool didSplit1, bool didSplit2)
{
	cout << "-----------------------------------------" << endl;
	cout << "Round " << game.getRound() << " End!"<< endl;
	cout << "-----------------------------------------" << endl;
	cout << game.getCurrentPlayer().getName() << " Hand: " << game.getCurrentPlayer().playerHand.toString()
		<< " Value: " << game.getCurrentPlayer().playerHand.getValue() << endl;
	if (didSplit1)//This variable is needed since player.didSplit will reset after completing one hand
		cout << game.getCurrentPlayer().getName() << " Split Hand: " << game.getCurrentPlayer().splitHand.toString()
		<< " Value: " << game.getCurrentPlayer().splitHand.getValue() << endl;
	cout << game.getSecondPlayer().getName() << " Hand: " << game.getSecondPlayer().playerHand.toString()
		<< " Value: " << game.getSecondPlayer().playerHand.getValue() << endl;
	if (didSplit2)//Same as above
		cout << game.getSecondPlayer().getName() << " Split Hand: " << game.getSecondPlayer().splitHand.toString()
		<< " Value: " << game.getSecondPlayer().splitHand.getValue() << endl;
	cout << "-----------------------------------------" << endl;
	cout << "Winner: " << result.winner << endl;
	cout << result.player1 << " Points: " << result.points1 << endl;
	cout << result.player2 << " Points: " << result.points2 << endl;
	cout << "-----------------------------------------" << endl;
}

//BlackjackView::BlackjackView()
//{
//}
