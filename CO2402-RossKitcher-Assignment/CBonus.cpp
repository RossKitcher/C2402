// Ross Kitcher

#include <iostream>
#include "CBonus.h"

using namespace std;

// Function to get a random bonus, output a message and return the amount earned.
int CBonus::GetBonus(int roll) {
	
	switch (roll) {
	case 1:
		cout << "Find some money. Gain " << POUND << "20" << endl;
		return 20;
	case 2:
		cout << "Win a coding competition. Gain " << POUND << "50" << endl;
		return 50; 
	case 3:
		cout << "Receive a rent rebate. Gain " << POUND << "100" << endl;
		return 100;
	case 4:
		cout << "Win the lottery. Gain " << POUND << "150" << endl;
		return 150; 
	case 5:
		cout << "Sell your iPad. Gain " << POUND << "200" << endl;
		return 200;
	case 6:
		cout << "It's your birthday. Gain " << POUND << "300" << endl;
		return 300;
	default:
		return 0;

	}

}

// When a player lands here, a random bonus is given to them.
void CBonus::SquareOperation(unique_ptr<CPlayer>& player)
{
	int amount = GetBonus(CGameManager::Random());

	CPlayer::STransaction trans;
	trans.from = BANK_ID;
	trans.to = player->GetID();
	trans.amount = amount;

	player->AddTransaction(trans);

}
