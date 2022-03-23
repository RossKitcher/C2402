// Ross Kitcher

#pragma once

#include "CProperty.h"

using namespace std;

// Constructor to set the member variables.
CProperty::CProperty(int id, string name, int cost, int rent, int group) : CSquare(id, name) {
	mCost = cost;
	mRent = rent;
	mGroup = group;
	mOwnerID = 0;
}


// Function to buy or pay rent when a player lands here.
void CProperty::SquareOperation(unique_ptr<CPlayer>& player)
{
	int playerID = player->GetID();
	string playerName = player->GetName();

	// If this property is already owned by another player.
	if (mOwnerID != 0 && mOwnerID != playerID) {
		
		// Create transaction.
		CPlayer::STransaction trans;
		trans.to = mOwnerID;
		trans.from = playerID;

		// -1 is used as the current rent value for the property is stored on a different instance of Player that only GameManager has access to.
		// The real rent value will be applied when the transaction is processed.
		trans.amount = -1;
		trans.propName = GetName();

		player->AddTransaction(trans);

		cout << playerName << " pays " << POUND << mRent << endl;

	}
	// If the property is not already owned.
	else if (mOwnerID != playerID) {

		// If the player can afford it.
		if (player->GetFunds() > 0) {

			// Create a SProperty object to store the associated attributes with the Player.
			CPlayer::SProperty prop;
			prop.name = GetName();
			prop.cost = mCost;
			prop.rent = mRent;
			prop.originalRent = mRent;
			prop.group = mGroup;
			prop.isMortgaged = false;
			prop.isStation = false;

			// Set member variables to indicate ownership.
			mOwnerID = playerID;

			// Create transaction.
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
