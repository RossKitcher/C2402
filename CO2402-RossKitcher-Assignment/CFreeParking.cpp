// Ross Kitcher

#include <iostream>
#include "CFreeParking.h"

using namespace std;

// Function to output a message when a player lands here.
void CFreeParking::SquareOperation(unique_ptr<CPlayer>& player)
{

	cout << player->GetName() << " is resting" << endl;

}
