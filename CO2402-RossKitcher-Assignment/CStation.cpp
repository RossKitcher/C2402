// Ross Kitcher

#include <iostream>
#include "CStation.h"

using namespace std;

// Constructor to set the member variables.
CStation::CStation(int id, string name, int cost, int rent) : CSquare(id, name)
{

	mCost = cost;
	mRent = rent;
	mOwnerID = 0;

}

// Function to buy or pay rent when a player lands here.
void CStation::SquareOperation(unique_ptr<CPlayer>& player) {

	int playerID = player->GetID();
	string playerName = player->GetName();

	// If the station is already owned by another player.
	if (mOwnerID != 0 && mOwnerID != playerID) {

		// Create transaction.
		CPlayer::STransaction trans;
		trans.to = mOwnerID;
		trans.from = playerID;
		trans.amount = mRent;

		player->AddTransaction(trans);

		cout << playerName << " pays " << POUND << "10 for ticket" << endl;

	}
	// If the station is not owned by another player.
	else if (mOwnerID != playerID) {

		// If the player can afford it.
		if (player->GetFunds() > 0) {

			// Create a property object to store the Station's attributes with the player.
			CPlayer::SProperty prop;
			prop.name = GetName();
			prop.cost = mCost;
			prop.rent = mRent;
			prop.group = -1; // -1 is used as a Station does not belong to any Color group.
			prop.isMortgaged = false;
			prop.isStation = true;

			// Set member variables to indicate ownership.
			mOwnerID = playerID;

			// Create a transaction.
			CPlayer::STransaction trans;
			trans.to = BANK_ID;
			trans.from = playerID;
			trans.amount = mCost;

			player->AddProperty(prop);
			player->AddTransaction(trans);

			cout << playerName << " buys " << GetName() << " for " << POUND << mCost << endl;

		}

	}
}