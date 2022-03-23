// Ross Kitcher

#pragma once

#include <iostream>
#include "CSquare.h"

using namespace std;

// Class: FreeParking (derived)
// Purpose: Outputs a message when a pPlayer lands here.
class CFreeParking : public CSquare {

public:
	CFreeParking(int id, string name) : CSquare(id, name) {};

	void SquareOperation(unique_ptr<CPlayer>& pPlayer);

};