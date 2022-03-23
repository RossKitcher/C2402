// Ross Kitcher

#pragma once

#include <iostream>
#include "CSquare.h"
#include "CPlayer.h"
#include "CGameManager.h"

using namespace std;

// Class: Bonus (derived)
// Purpose: Gives the pPlayer a random bonus.
class CBonus : public CSquare {

public:
	CBonus(int id, string name) : CSquare(id, name) {};
	int GetBonus(int roll); // returns the owed amount of money from the selected bonus
	void SquareOperation(unique_ptr<CPlayer>& pPlayer);


};