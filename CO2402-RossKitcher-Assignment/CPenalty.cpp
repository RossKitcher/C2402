// Ross Kitcher

#include <iostream>
#include "CPenalty.h"

using namespace std;


// Function to output a message to the user and return an amount of money to be charged.
int CPenalty::GetPenalty(int roll) {

	switch (roll) {
	case 1:
		cout << "Buy a coffee in Starbucks. Lose " << POUND << "20" << endl;
		return 20;
	case 2:
		cout << "Pay your broadband bill. Lose " << POUND << "50" << endl;
		return 50;
	case 3:
		cout << "Visit the SU shop for food. Lose " << POUND << "100" << endl;
		return 100;
	case 4:
		cout << "Buy an assignment solution. Lose " << POUND << "150" << endl;
		return 150;
	case 5:
		cout << "Go for a romantic meal. Lose " << POUND << "200" << endl;
		return 200;
	case 6:
		cout << "Pay for some university fees. Lose " << POUND << "300" << endl;
		return 300;
	default:
		return 0;

	}
}

// When the player lands here, a random penalty is received.
void CPenalty::SquareOperation(unique_ptr<CPlayer>& player)
{
	int amount = GetPenalty(CGameManager::Random());

	CPlayer::STransaction trans;
	trans.to = BANK_ID;
	trans.from = player->GetID();
	trans.amount = amount;

	player->AddTransaction(trans);

}
