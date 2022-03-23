// Ross Kitcher

#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <random>
#include "CPlayer.h"
#include "CSquare.h"
#include "CProperty.h"
#include "CStation.h"
#include "CJail.h"
#include "CGoToJail.h"
#include "CFreeParking.h"
#include "CBonus.h"
#include "CPenalty.h"
#include "CBank.h"

using namespace std;

const int STARTING_CASH = 1500;
const int BONUS_ON_GO = 200;

// Class: GameManager
// Purpose: A manager class used to operate and store information about the game in progress.
class CGameManager {
public:

	CGameManager();
	void InitialiseBoard(string filepath); // reads the config file and initialises the game
	void RunSimulation(); // simulates the main function of the game
	static int Random(); // returns a random number between 1 and 6

private:
	// typedef's for more readable data structures
	typedef vector<unique_ptr<CSquare>> GameBoard;
	typedef vector<unique_ptr<CPlayer>> Players;
	typedef map<int, int> ColorGroups;

	unique_ptr<CBank> mBank;
	int mRoundCount;
	GameBoard mBoard;
	Players mPlayers;
	ColorGroups mColorGroups;

	string mPlayerNames[4] = { "Hamster", "Pumpkin", "Dog", "Jaguar" };
	
	string GetWinner();
	void FulfillTransactions(unique_ptr<CPlayer>& pCurrentPlayer);

};