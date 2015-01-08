/*
 * Copyright 2013 Tri-Edge AI <triedgeai@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 */

#ifndef _MINESWEEPER_H_
#define _MINESWEEPER_H_

#include "MinesweeperWindow.h"

#include <Application.h>

class Minesweeper : public BApplication
{
public:
							Minesweeper();
							~Minesweeper();

private:
	MinesweeperWindow* 		fWindow;
};

#endif
