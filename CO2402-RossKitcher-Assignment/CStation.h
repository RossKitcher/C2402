// Ross Kitcher

#pragma once

#include <iostream>
#include "CSquare.h"

using namespace std;

// Class: Station (derived)
// Purpose: When a pPlayer lands here, they can buy the station or pay for a ticket to the owner.
class CStation : public CSquare {
private:
	int mCost;
	int mRent;

	int mOwnerID;

public:
	CStation(int id, string name, int cost, int rent);

	void SquareOperation(unique_ptr<CPlayer>& pPlayer);

};