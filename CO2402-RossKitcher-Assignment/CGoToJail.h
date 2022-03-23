// Ross Kitcher

#pragma once

#include <iostream>
#include "CSquare.h"

using namespace std;

const int JAIL_POS = 6;

// Class: GoToJail (derived)
// Purpose: Sends the pPlayer to Jail when they land here.
class CGoToJail : public CSquare {

private:
	int mCost = 50;
public:
	CGoToJail(int id, string name) : CSquare(id, name) {};

	void SquareOperation(unique_ptr<CPlayer>& pPlayer);
};