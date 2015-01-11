/*
 * Copyright 2013 Tri-Edge AI <triedgeai@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 */

#ifndef _ABOUT_WINDOW_H_
#define _ABOUT_WINDOW_H_

#include "defs.h"
#include "MinesweeperIconView.h"

#include <Window.h>
#include <StringView.h>
#include <Button.h>
#include <GroupLayoutBuilder.h>

class AboutWindow : public BWindow
{
public:
							AboutWindow();
							~AboutWindow();
private:
	MinesweeperIconView*	fIcon;
	BStringView*			fTitleText;
	BStringView*			fCreatorText;
	BStringView*			fArtistText;
	BButton*				fOKButton;
};

#endif
