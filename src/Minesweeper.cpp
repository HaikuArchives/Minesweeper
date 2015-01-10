/*
 * Copyright 2013 Tri-Edge AI <triedgeai@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 */

#include "Minesweeper.h"

Minesweeper::Minesweeper()
	:
	BApplication("application/x-vnd.minesweeper")
{
	fWindow = new MinesweeperWindow();
	fWindow->Show();
}


Minesweeper::~Minesweeper()
{

}
