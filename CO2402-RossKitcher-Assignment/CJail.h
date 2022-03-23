// Ross Kitcher

#pragma once

#include <iostream>
#include "CSquare.h"

using namespace std;

// Class: Jail (derived)
// Purpose: Outputs a message when a pPlayer lands here.
class CJail : public CSquare {

public:
	CJail(int id, string name) : CSquare(id, name) {};
	void SquareOperation(unique_ptr<CPlayer>& pPlayer);

};