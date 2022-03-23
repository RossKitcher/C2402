// Ross Kitcher
//

#include "CGameManager.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <cstdio>


int main()
{
	{

		// Initialise the GameManager class.
		unique_ptr<CGameManager> game = make_unique<CGameManager>();

		game->InitialiseBoard("C:\\files\\monopolish.txt");

		// Run the simulation.
		game->RunSimulation();
	}
	

	_CrtDumpMemoryLeaks();
}

