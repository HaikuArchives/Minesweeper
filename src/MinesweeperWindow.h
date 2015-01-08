/*
 * Copyright 2013 Tri-Edge AI <triedgeai@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 */
 
#ifndef _MINESWEEPER_WINDOW_H_
#define _MINESWEEPER_WINDOW_H_

#include "defs.h"
#include "Settings.h"
#include "CustomFieldWindow.h"
#include "MinefieldView.h"
#include "ImageButton.h"
#include "DigitalTimerView.h"
#include "SubmitWindow.h"
#include "AboutWindow.h"
#include "HighscoreWindow.h"

#include <Application.h>
#include <Window.h>
#include <Alert.h>
#include <Menu.h>
#include <MenuBar.h>
#include <MenuItem.h>
#include <Messenger.h>
#include <Message.h>
#include <Box.h>
#include <app/MessageRunner.h>

class CustomFieldWindow;
class SubmitWindow;
class MinefieldView;

class MinesweeperWindow : public BWindow
{
public:
	ImageButton*			FaceButton;
	DigitalTimerView*		MineCounter;
	DigitalTimerView*		TimeCounter;
	
							MinesweeperWindow();
							~MinesweeperWindow();
					
	void					MessageReceived(BMessage* msg);
	bool					QuitRequested();
	
private:
	Settings				fSettings;
	
	bigtime_t				fTimeStart;
	bigtime_t				fTimeNow;
	uint32					fTimeScore;
	
	BView*					fBackView;
	
	BMenuBar* 				fMenu;
	
	BMenu*	 				fGameMenu;
	BMenuItem* 				fNewItem;
	BMenuItem* 				fHighscoreItem;
	
	BMenu* 					fSizeMenu;
	BMenuItem*				fBeginnerItem;
	BMenuItem*				fIntermediateItem;
	BMenuItem*				fExpertItem;
	BMenuItem*				fCustomItem;
	
	BMenuItem*				fSoundItem;
	BMenuItem* 				fQuitItem;
	
	BMenu*	 				fHelpMenu;
	BMenuItem* 				fAboutItem;
	
	BBox*					fControlBox;
	BBox*					fFieldBox;
	CustomFieldWindow*		fCustomFieldWindow;
	SubmitWindow*			fSubmitWindow;
	
	MinefieldView*			fMinefield;
	
	bool					fIsResizing;
	
	float					fCurrentWidth;
	float					fCurrentHeight;
	
	float					fTargetWidth;
	float					fTargetHeight;
	
	void					_GracefulResize(uint32 newWidth, uint32 newHeight);
};

#endif
