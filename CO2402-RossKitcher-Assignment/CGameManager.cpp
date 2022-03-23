#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>
#include "CGameManager.h"

using namespace std;

// Constuctor
CGameManager::CGameManager() {

	// Seed for the random number generator.
	srand(47);

	mBank = make_unique<CBank>(); // Instantiate the bank.
	mRoundCount = 20; // Set the mac amount of rounds.

	// For each player in mPlayerNames.
	int id = 1;
	for (string name : mPlayerNames) {

		unique_ptr<CPlayer> player = make_unique<CPlayer>(name, id); // Instantiate a new player.
		mBank->MakeTransaction(player, STARTING_CASH); // Give the player their starting money.

		// Push the new player to the mPlayers vector.
		mPlayers.push_back( move(player) );
		id++;
	}

}

// Function to read in the config text file and extract information.
void CGameManager::InitialiseBoard(string filepath) {

	// Initialise an fstream object to read input from the text file.
	fstream gameConfig;
	gameConfig.open(filepath, ios::in);

	string line;

	// loop through each line in the text file.
	while (getline(gameConfig, line)) {

		// convert char to int.
		// As zero is the first number represented in the ASCII table, the difference between the two equals the correct decimal number.
		int id = (int)line[0] - '0';

		vector<string> configData; // vector to hold a list of any amount of config values found.

		string temp; // temp string, used to build a full word/number from the input text file.

		// for each character in a line from the text file.
		// starting at 2 as the first two char's are not needed.
		for (size_t i = 2; i < line.length(); i++) {

			// if the char is a space, push the created string to the vector and reset the string.
			// if not, add the char to the string.
			if (line[i] == ' ') {
				configData.push_back(temp);
				temp = "";
			}
			else {
				temp += line[i];
			}
		}

		// push the string to the vector one final time, this is due to the final temp string not being pushed inside the for loop.
		configData.push_back(temp);

		string fullName = "";
		int increment = 0;

		unique_ptr<CSquare> currentSquare = nullptr;

		// If the square is a property.
		if (id == 1) {

			// Check for edge case of a property's name featuring only one word.
			if (configData[0] == "Friargate") {
				fullName = configData[0];
				increment += 1;
			}
			else {
				fullName = configData[0] + " " + configData[1];
				increment += 2;
			}

			// Extract the cost, rent, and group using an incrementing index.
			int cost = stoi(configData[increment]);
			int rent = stoi(configData[increment + 1]);
			int group = stoi(configData[increment + 2]);
			
			// Instantiate the property.
			currentSquare = make_unique<CProperty>(id, fullName, cost, rent, group);

			// If this is the first occurrence of a color group.
			if (mColorGroups.find(group) == mColorGroups.end()) {
				mColorGroups[group] = 1;
			}
			// If this is not the first occurence.
			else {
				mColorGroups[group] += 1;
			}

		}
		// If the square is not a property.
		else {

			// Extract the name of the square.
			for (size_t index = 0; index < configData.size(); index++) {

				fullName += configData[index];

				if (index < configData.size() - 1) {
					fullName += " ";
				}

			}

			// Depending on the id of the square, instatiate the relevant square type.
			if (id == 3) {
				currentSquare = make_unique<CStation>(id, fullName, 200, 10); // Instantiate a Station square.
			}
			else if (id == 4) {
				currentSquare = make_unique<CBonus>(id, fullName); // Instantiate a Bonus square.
			}
			else if (id == 5) {
				currentSquare = make_unique<CPenalty>(id, fullName); // Instantiate a Penalty square.

			}
			else if (id == 6) {
				currentSquare = make_unique<CJail>(id, fullName); // Instantiate a Jail square.

			}
			else if (id == 7) {
				currentSquare = make_unique<CGoToJail>(id, fullName); // Instantiate a GoToJail square.

			}
			else if (id == 8) {
				currentSquare = make_unique<CFreeParking>(id, fullName); // Instantiate a FreeParking square.

			}
			else {
				currentSquare = make_unique<CSquare>(id, fullName); // Instantiate a standard square (used for the GO square).

			}

		}


		// Push the square to the vector of squares.
		mBoard.push_back(move(currentSquare));

	}

	gameConfig.close();
}

// Main function to run the simulation.
// This handles the main operation of the game.
void CGameManager::RunSimulation() {
	
	// Repeat for the amount of maximum rounds (20).
	for (int i = 0; i < mRoundCount; i++) {

		cout << "ROUND " << i+1 << endl;
		cout << "=========" << endl;

		int bankruptcyCount = 0;
		
		// Each player takes their turn.
		for (unique_ptr<CPlayer>& player : mPlayers) {			

			// If a player is bankrupt, skip their turn.
			if (player->GetBankruptcyStatus()) {
				bankruptcyCount++;
				continue;
			}

			int roll = Random(); // Roll the dice.
			string pName = player->GetName(); // Get the player's name.

			// Move position of the player, if they pass GO, true is returned.
			bool passGo = player->MovePosition(roll);

			// Get the name and type of the square the player has landed on.
			string sName = mBoard[player->GetPosition()]->GetName();
			int sType = mBoard[player->GetPosition()]->GetType();

			cout << pName << " rolls " << roll << endl;
			cout << pName << " lands on " << sName << endl;

			// If the player passes GO.
			if (passGo) {

				// Pay out £200.
				mBank->MakeTransaction(player, BONUS_ON_GO);
				cout << pName << " passes GO and collects " << POUND << BONUS_ON_GO << endl;

			}

			// Call the function 'SquareOperation', this will have a different definition depending on the type of object.
			mBoard[player->GetPosition()]->SquareOperation(player);

			FulfillTransactions(player); // Pay out any pending transactions.
			
			// if the player is bankrupt at the end of their turn, then start mortgaging properties until they are no longer bankrupt.
			if (player->GetFunds() < 0) {

				player->MortgageProperties();
				FulfillTransactions(player);


				// If the player has no more properties to mortgage and their balance is still below zero.
				if (!player->HasPropertiesToMortgage() && player->GetFunds() < 0) {

					// declare bankruptcy
					player->DeclareBankruptcy();

					cout << pName << " has declared bankruptcy" << endl;

				}

			}
			// If the player has money and owns mortgaged properties.
			else if (player->GetDebt() && player->GetFunds() > player->GetCheapestMortgagedProperty() ) {

				player->PayMortgage();
				FulfillTransactions(player);

			}

			// Check if a player now owns all of a color group.
			player->CheckColorGroups(mColorGroups);

			cout << pName << " has " << POUND << player->GetFunds() << endl;
			cout << endl;

		}

		// If most of the players are bankrupt, exit the for loop and end the game.
		// I.e. for a two player game, if one player is bankrupt.
		// For a four player game, if three players are bankrupt.
		if (bankruptcyCount >= (int)(mPlayers.size() * 0.75)) {
			break;
		}
	}

	cout << "Game Over" << endl;

	// Display all player's name and total money.
	for (auto& player : mPlayers) {
		cout << player->GetName() << " has " << POUND << player->GetFunds() << endl;
	}

	// Declare a winner.
	string winner = GetWinner();
	cout << winner << " wins." << endl;

}

// Function to determine the winner of a game.
string CGameManager::GetWinner() {

	// Use max_element with a lambda function to compare the funds of each player.
	auto it = max_element(mPlayers.begin(), mPlayers.end(), [](const unique_ptr<CPlayer>& left, const unique_ptr<CPlayer>& right) {

		return left->GetFunds() < right->GetFunds();
		
		});

	return (*it)->GetName();
}

// Function to fulfill pending transactions.
// This is used as a Player does not have access to the Bank, so any transactions requested on the Player are stored for this function to fulfill them.
void CGameManager::FulfillTransactions(unique_ptr<CPlayer>& currentPlayer)
{

	// Fulfill all pending transactions
	for (CPlayer::STransaction trans : currentPlayer->GetTransactions()) {

		// If amount is -1, then the correct rent value for the given property should be acquired.
		if (trans.amount == -1) {

			trans.amount = mPlayers[trans.to - 1]->GetRentByName(trans.propName);

		}

		// If the player is sending money to the bank.
		if (trans.to == BANK_ID) {

			mBank->PayToBank(currentPlayer, trans.amount);

		}
		// If the player is receiving money from the bank.
		else if (trans.from == BANK_ID) {

			mBank->MakeTransaction(currentPlayer, trans.amount);

		}
		// If the player is sending money to another player.
		else {

			// find_if is used with a lambda function to return an iterator to the unique pointer of a player. 
			auto playerIter = find_if(mPlayers.begin(), mPlayers.end(), [&trans](auto& testPlayer) {
				return (testPlayer->GetID() == trans.to);
				});

			mBank->MakeTransaction(*playerIter, currentPlayer, trans.amount);

		}

	}

}


// Function to return a random number between 1 and 6.
// Source:
//	- https://www.geeksforgeeks.org/stdmt19937-class-in-cpp/
//  - https://www.cplusplus.com/reference/random/random_device/
//  - https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
// This is used instead of the provided random number generator as the seed produced from the time is the same for multiple players when executed quickly.
int CGameManager::Random() {

	/*
	random_device device; // Class to generate random numbers from hardware, if available.
	mt19937 range(device()); // Uses the Mersenne Twister algorithm seeded with device().
	uniform_int_distribution<mt19937::result_type> distribution(1, 6); // Creates integer distribution between 1 and 6.

	return distribution(range); // Transforms the random int generated by range into an integer that lies inside the distribution. Returns the result.
	*/

	return static_cast<int>(static_cast<double> (rand()) / (RAND_MAX + 1) * 6.0f + 1);
}
