// Ross Kitcher

#include <iostream>
#include "CBank.h"

using namespace std;

// Constructor to set the member variables.
CBank::CBank() {

	mReserves = 20000; // Set the total amount of cash in circulation at £20,000
	mHasMoney = true;

}

// Function to pay money back to the bank.
// Used for penalties and re-buying mortgaged properties.
void CBank::PayToBank(unique_ptr<CPlayer>& from, int amount) {
	mReserves += amount;
	from->TakeFunds(amount);
}

// Function to pay money from the bank to the player.
// Used for bonuses and the player passing GO.
void CBank::MakeTransaction(unique_ptr<CPlayer>& to, int amount) {

	CheckReserves();

	if (mHasMoney) {
		mReserves -= amount;
		to->AddFunds(amount);
		
	}
	else {
		cout << "The bank has no more money" << endl;
	}

}

// Function to send money from player to player.
// Used for paying rent.
void CBank::MakeTransaction(unique_ptr<CPlayer>& to, unique_ptr<CPlayer>& from, int amount) {
	from->TakeFunds(amount);
	to->AddFunds(amount);
}

// Private function to check the reserves level.
// If there is no more money in circulation, then the bank cannot pay money out to players.
void CBank::CheckReserves() {
	if (mReserves < 0) {
		mHasMoney = false;
	}
	else {
		mHasMoney = true;
	}
}