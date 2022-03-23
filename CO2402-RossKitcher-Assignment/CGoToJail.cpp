
#include <iostream>
#include "CGoToJail.h"

using namespace std;

// Function to move a player to the Jail square.
void CGoToJail::SquareOperation(unique_ptr<CPlayer>& player)
{

	cout << player->GetName() << " goes to Jail" << endl;
	cout << player->GetName() << " pays " << POUND << mCost << endl;

	player->SetPosition(JAIL_POS);

	CPlayer::STransaction trans;
	trans.to = BANK_ID;
	trans.from = player->GetID();
	trans.amount = mCost;
	
	player->AddTransaction(trans);

}
