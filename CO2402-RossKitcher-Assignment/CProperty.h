// Ross Kitcher

#pragma once

#include <iostream>
#include "CSquare.h"

using namespace std;

// Class: CProperty (derived)
// Purpose: When a pPlayer lands here, they can either buy the property or pay rent to the owner.
class CProperty : public CSquare {
private:

	int mCost;
	int mRent;
	int mGroup;
	int mOwnerID;

public:
	CProperty(int id, string name, int cost, int rent, int group);

	void SquareOperation(unique_ptr<CPlayer>& pPlayer);

};
