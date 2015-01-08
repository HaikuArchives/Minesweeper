/*
 * Copyright 2013 Tri-Edge AI <triedgeai@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 */

#include "MinesweeperIconView.h"

MinesweeperIconView::MinesweeperIconView()
	:
	BView(BRect(0, 0, 64, 64), "MinesweeperIcon", B_FOLLOW_NONE,
		B_WILL_DRAW)
{
	SetDrawingMode(B_OP_ALPHA);
	SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));
}


MinesweeperIconView::~MinesweeperIconView()
{
	
}


void
MinesweeperIconView::Draw(BRect updateRect)
{
	DrawBitmap(Assets.gfx.icon, BPoint(0, 0));	
}
