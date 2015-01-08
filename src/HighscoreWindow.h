/*
 * Copyright 2013 Tri-Edge AI <triedgeai@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 */

#ifndef _HIGHSCORE_WINDOW_H_
#define _HIGHSCORE_WINDOW_H_

#include "defs.h"
#include "Settings.h"

#include <Window.h>
#include <View.h>
#include <StringView.h>
#include <GroupLayoutBuilder.h>
#include <Button.h>

class HighscoreWindow : public BWindow
{
public:
							HighscoreWindow(const Settings* settings);
							~HighscoreWindow();
private:
	BStringView*			fBeginnerText;
	BStringView*			fNameArrayBeginner[10];
	BStringView*			fTimeArrayBeginner[10];
	
	BStringView*			fIntermediateText;
	BStringView*			fNameArrayIntermediate[10];
	BStringView*			fTimeArrayIntermediate[10];
	
	BStringView*			fExpertText;
	BStringView*			fNameArrayExpert[10];
	BStringView*			fTimeArrayExpert[10];
	
	BButton*				fCloseButton;
	
	BString					_TimeString(uint32 time);
};

#endif
