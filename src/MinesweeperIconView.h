/*
 * Copyright 2013 Tri-Edge AI <triedgeai@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 */

#include "Assets.h"

#include <View.h>

#ifndef _MINESWEEPER_ICON_VIEW_H_
#define _MINESWEEPER_ICON_VIEW_H_

class MinesweeperIconView : public BView
{
public:
							MinesweeperIconView();
							~MinesweeperIconView();

	void					Draw(BRect updateRect);

private:

};

#endif
