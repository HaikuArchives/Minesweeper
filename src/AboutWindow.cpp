/*
 * Copyright 2013 Tri-Edge AI <triedgeai@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 */
 
#include "AboutWindow.h"

AboutWindow::AboutWindow()
	:
	BWindow(BRect(200, 200, 600, 280), "About", B_FLOATING_WINDOW,
		B_NOT_RESIZABLE)
{
	fIcon = new MinesweeperIconView();
	
	fTitleText = new BStringView(RECT_0, "fTitleText", 
		"Haiku Minesweeper v1.0");
		
	fTitleText->SetFont(be_bold_font);
		
	fCreatorText = new BStringView(RECT_0, "fCreatorText",
		"Created by Tri-Edge AI <triedgeai@gmail.com>");
	
	SetLayout(new BGroupLayout(B_HORIZONTAL));
	
	AddChild(BGroupLayoutBuilder(B_HORIZONTAL, 0)
		.Add(fIcon)
		.AddGlue()
		.Add(BGroupLayoutBuilder(B_VERTICAL, 8)
			.AddGlue()
			.Add(fTitleText)
			.Add(fCreatorText)
			.AddGlue()
		)
		.SetInsets(8, 8, 8, 8)
	);
	
	Show();
}

AboutWindow::~AboutWindow()
{
	
}
