/*
 * Copyright 2013 Tri-Edge AI <triedgeai@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 */

#include "Minesweeper.h"
#include "MinesweeperWindow.h"

int
main()
{
	srand(time(NULL));
	
	Minesweeper* app = new Minesweeper();
	
	app->Run();
	
	return 0;
}
