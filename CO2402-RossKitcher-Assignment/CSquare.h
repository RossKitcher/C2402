// Ross Kitcher

#pragma once

#include <iostream>
#include "CBank.h"
#include "CPlayer.h"


using namespace std;

const unsigned char POUND = 156; // Set constant for the pound sign.

// Class: CSquare (base)
// Purpose: Provides declarations of shared functionality between all types of squares.
class CSquare {
private:

	int mType;
	string mName;

public:

	CSquare(int id, string name);

	int GetType();
	void SetName(string name);
	string GetName(); // returns the name

	// Virtual function to be inherited by all derived classes, this provides the base operations for each square when a pPlayer lands here.
	virtual void SquareOperation(unique_ptr<CPlayer>& pPlayer) {};

};