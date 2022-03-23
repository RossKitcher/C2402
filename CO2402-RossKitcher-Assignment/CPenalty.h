// Ross Kitcher

#pragma once

#include <iostream>
#include "CSquare.h"
#include "CGameManager.h"
#include <vector>

using namespace std;

// Class: Penalty (derived)
// Purpose: Gives the pPlayer a random penalty when they land here.
class CPenalty : public CSquare {

public:
	CPenalty(int id, string name) : CSquare(id, name) {};
	int GetPenalty(int roll);
	void SquareOperation(unique_ptr<CPlayer>& pPlayer);

};