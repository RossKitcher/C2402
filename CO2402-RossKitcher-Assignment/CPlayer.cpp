// Ross Kitcher

#include <iostream>
#include <random>
#include "CPlayer.h"

using namespace std;

const unsigned char POUND = 156;

// Constructor to initialise member variables.
CPlayer::CPlayer(string name, int id) {

	mName = name;
	mID = id;
	mPosition = 0;
	mInDebt = false;
	mIsBankrupt = false;

}

// Getter for mName.
string CPlayer::GetName() {
	return mName;
}

int CPlayer::GetID()
{
	return mID;
}

// Getter for mPosition.
int CPlayer::GetPosition() {
	return mPosition;
}

// Function to move the player, if the player passes GO, return true.
bool CPlayer::MovePosition(int pos) {

	mPosition += pos;

	if (mPosition > 25) {

		mPosition = mPosition % 26;
		return true;

	}

	return false;

}

// Setter for mPosition.
void CPlayer::SetPosition(int pos) {
	mPosition = pos;
}

// Add funds to a player's money total.
void CPlayer::AddFunds(int amount) {
	mMoney += amount;
}

// Remove funds from a player's money total.
void CPlayer::TakeFunds(int amount) {
	mMoney -= amount;
}

// Getter for mMoney.
int CPlayer::GetFunds() {
	return mMoney;
}

// Increment the counter for a player's color groups total.
void CPlayer::AddColorGroup(int color) {

	if (mColorGroupCount.find(color) == mColorGroupCount.end()) {
		mColorGroupCount[color] = 1;
	}
	else {
		mColorGroupCount[color] += 1;
	}

}

// Return the count for a particular color group.
int CPlayer::GetColorGroup(int color) {
	return mColorGroupCount[color];
}

// Getter for mInDebt.
bool CPlayer::GetDebt() {

	return mInDebt;

}

// Setter for mInDebt.
void CPlayer::SetDebtStatus(bool status) {
	mInDebt = status;
}

// Function to declare bankruptcy of a player.
void CPlayer::DeclareBankruptcy()
{

	mIsBankrupt = true;

	// Set rent of all player's properties to 0 as this player is no longer in the game.
	for (SProperty& prop : mProperties) {
		prop.rent = 0;
	}

}


// Getter for mIsBankrupt
bool CPlayer::GetBankruptcyStatus() {
	return mIsBankrupt;
}

// Function to push a transaction onto the vector.
void CPlayer::AddTransaction(STransaction trans)
{

	mTransactions.push_back(trans);

}

// Function to receive a player's transactions, when called, the vector is cleared.
CPlayer::Transactions CPlayer::GetTransactions()
{
	Transactions copy = mTransactions;
	mTransactions.clear();
	return copy;
}

// Add a property to a player's property vector.
void CPlayer::AddProperty(SProperty prop)
{

	AddColorGroup(prop.group); // Update the player's color group counter.
	mProperties.push_back(prop);

}

// Function to mortgage properties until they are no longer in debt.
void CPlayer::MortgageProperties()
{

	// Sort the properties to cheapest first.
	sort(mProperties.begin(), mProperties.end());

	int tempFunds = mMoney; // Copy the player's money total.

	int propIndex = 0;
	// Iterate until the player's funds rise above zero or the player no longer has any properties to mortgage.
	while (tempFunds < 0 && HasPropertiesToMortgage()) {

		// If the given property is not already mortgaged and is not a station.
		if (!(mProperties[propIndex].isMortgaged) && !(mProperties[propIndex].isStation)) {

			// Create a transaction.
			STransaction trans;
			trans.to = mID;
			trans.from = BANK_ID;
			trans.amount = mProperties[propIndex].cost;
			mTransactions.push_back(trans);

			// Change properties of the property.
			mProperties[propIndex].isMortgaged = true;
			mProperties[propIndex].rent = 0;

			mInDebt = true; // Set the player's debt status.

			tempFunds += mProperties[propIndex].cost; // Update the player's temporary fund counter.

			cout << mName << " mortgages " << mProperties[propIndex].name << " for " << POUND << mProperties[propIndex].cost << endl;

		}

		propIndex++;

	}

}

// Function to determine if a player has properties to mortgage.
bool CPlayer::HasPropertiesToMortgage() {

	for (SProperty prop : mProperties) {

		if (!prop.isMortgaged && !prop.isStation) {
			return true;
		}

	}

	return false;

}

// Function to return the cost of the cheapest property that has been mortgaged.
// If no mortgaged properties are found, -1 is returned.
int CPlayer::GetCheapestMortgagedProperty()
{
	
	// create new vector to hold only mortgaged properties
	Properties mortgagedProps;

	for (SProperty prop : mProperties) {

		if (prop.isMortgaged) {

			mortgagedProps.push_back(prop);

		}

	}

	// get the cheapest property from this new vector
	auto propIter = min_element(mortgagedProps.begin(), mortgagedProps.end(), [](const SProperty& left, const SProperty& right) {
		return (left.cost < right.cost);
		});

	if (propIter == mortgagedProps.end()) {
		return -1;
	}
	else {
		return propIter->cost;
	}


}

int CPlayer::GetRentByName(string name)
{

	for (auto prop : mProperties) {
		if (name == prop.name) {
			return prop.rent;
		}
	}

	return 0;

}

// Function to continually pay off mortgages until the player can no longer afford to do so or until the player runs out of mortgaged properties.
void CPlayer::PayMortgage()
{

	// create new vector to hold only mortgaged properties
	Properties mortgagedProps;

	for (SProperty& prop : mProperties) {

		if (prop.isMortgaged) {

			mortgagedProps.push_back(prop);

		}

	}

	// Sort properties to cheapest first
	sort(mortgagedProps.begin(), mortgagedProps.end());

	int tempFunds = mMoney;

	// Iterate through each mortgaged property.
	auto propIter = mortgagedProps.begin();
	for (propIter; propIter != mortgagedProps.end(); ++propIter) {

		// If player can afford to buy back the property.
		if (tempFunds > propIter->cost) {

			auto propToBuy = find_if(mProperties.begin(), mProperties.end(), [&](const SProperty& prop) {
				return (propIter->name == prop.name);
				});

			// Create a transaction.
			STransaction trans;
			trans.to = BANK_ID;
			trans.from = mID;
			trans.amount = propToBuy->cost;
			mTransactions.push_back(trans);

			// Update the property's attributes.
			propToBuy->isMortgaged = false;
			propToBuy->rent = propToBuy->originalRent;

			tempFunds -= propToBuy->cost; // Update the temporary fund counter.

			cout << mName << " repays " << POUND <<  propToBuy->cost << " on " << propToBuy->name << endl;

		}

	}

	// If all mortgaged properties have been bought, they are no longer in debt
	if (GetCheapestMortgagedProperty() == -1) {
		mInDebt = false;
	}

}

// Function to determine if a player owns a complete color set.
void CPlayer::CheckColorGroups(ColorGroups maxColorGroups)
{

	// For each key/value pair in the map.
	for (auto mapIter = maxColorGroups.begin(); mapIter != maxColorGroups.end(); ++mapIter) {

		int key = mapIter->first;
		int maxAmount = mapIter->second;

		// If the player owns all properties of a given group.
		if (mColorGroupCount[key] == maxAmount) {

			// Double the rent of all properties of the given group.
			for (SProperty& prop : mProperties) {
				if (prop.group == key) {
					prop.rent = prop.originalRent * 2;
				}
			}

		}

	}

}

