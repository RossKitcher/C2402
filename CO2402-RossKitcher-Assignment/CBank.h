// Ross Kitcher

#pragma once

#include <iostream>
#include "CPlayer.h"

using namespace std;


// Class: Bank
// Purpose: Provides a central place for sending money between players and keeps track of the total money in circulation.
class CBank {

private:

	int mReserves;
	bool mHasMoney;

	void CheckReserves();

public:

	CBank();
	void PayToBank(unique_ptr<CPlayer>& pFrom, int amount);
	void MakeTransaction(unique_ptr<CPlayer>& pTo, int amount);
	void MakeTransaction(unique_ptr<CPlayer>& pTo, unique_ptr<CPlayer>& pFrom, int amount);

};