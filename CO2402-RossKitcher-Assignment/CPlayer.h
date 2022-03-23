// Ross Kitcher

#pragma once

#include <iostream>
#include <map>
#include <vector>

using namespace std;

const int BANK_ID = 0;

// Class: Player
// Purpose: Stores information about a player including money, position on board, and owned/mortgaged properties.
class CPlayer {

public:

	// struct to hold all attributes about a player's owned property
	struct SProperty {
		string name = "";
		int cost = 0;
		int rent = 0;
		int originalRent = 0;
		int group = 0;
		bool isMortgaged = false;
		bool isStation = false;

		// overloaded operator to compare structs by cost
		bool operator < (const SProperty& right) const {

			return (cost < right.cost);

		}

	};

	// struct to hold attributes relevant for a pending transaction
	struct STransaction {
		int to = 0;
		int from = 0;
		int amount = 0;

		// SProperty name value used only when when paying rent.
		// Used to identify the property to get the correct rent value.
		string propName = "";
	};

	// typedef's for more readable data structures
	typedef map<int, int> ColorGroups;
	typedef vector<SProperty> Properties;
	typedef vector<STransaction> Transactions;

	CPlayer(string name, int id);

	int GetPosition(); // returns the player position
	string GetName(); // returns the player name
	int GetID(); // returns the player's ID
	int GetFunds(); // returns the player's funds
	Transactions GetTransactions(); // returns a vector of transactions
	int GetColorGroup(int color); // returns the amount of properties a player owns for the given color group
	int GetCheapestMortgagedProperty(); // returns the cost of the cheapest mortgaged property
	int GetRentByName(string name); // returns a property's rent from the given property name
	bool GetDebt(); // returns true if the player is in debt
	bool GetBankruptcyStatus(); // returns true if the player is bankrupt

	void SetPosition(int pos);
	void SetDebtStatus(bool status);

	bool MovePosition(int pos); // returns true if the player has passed GO
	void AddFunds(int amount);
	void TakeFunds(int amount);
	void AddColorGroup(int color);
	void DeclareBankruptcy();
	void AddTransaction(STransaction trans);
	void AddProperty(SProperty prop);
	void MortgageProperties();
	bool HasPropertiesToMortgage(); // returns true if the player has properties available to mortgage
	void PayMortgage();
	void CheckColorGroups(ColorGroups maxColorGroups);


private:

	int mMoney;
	string mName;
	int mPosition;
	bool mInDebt;
	bool mIsBankrupt;
	int mID;

	ColorGroups mColorGroupCount;
	Properties mProperties;
	Transactions mTransactions;

};