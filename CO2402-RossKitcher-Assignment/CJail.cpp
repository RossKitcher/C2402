// Ross Kitcher

#include <iostream>
#include "CJail.h"

using namespace std;

// Function to output a message when the player lands here.
void CJail::SquareOperation(unique_ptr<CPlayer>& player)
{

	cout << player->GetName() << " is just visiting" << endl;

}
