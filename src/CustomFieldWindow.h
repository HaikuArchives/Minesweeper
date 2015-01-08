/*
 * Copyright 2013 Tri-Edge AI <triedgeai@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 */

#ifndef _CUSTOM_FIELD_WINDOW_H_
#define _CUSTOM_FIELD_WINDOW_H_

#include "defs.h"
#include "MinesweeperWindow.h"

#include <Window.h>
#include <StringView.h>
#include <TextControl.h>
#include <Button.h>
#include <GroupLayoutBuilder.h>
#include <String.h>

#include <stdlib.h>

class MinesweeperWindow;

class CustomFieldWindow : public BWindow
{
public:
	uint32				Width;
	uint32				Height;
	uint32				Mines;
	bool				Result;
	
						CustomFieldWindow(MinesweeperWindow* parent, uint32 width, uint32 height, uint32 mines);
						~CustomFieldWindow();
	
	void				MessageReceived(BMessage* msg);
	
private:
	MinesweeperWindow*	fParent;

	BStringView*		fInfo;
	
	BTextControl*		fWidthControl;
	BStringView*		fWidthError;
	
	BTextControl*		fHeightControl;
	BStringView*		fHeightError;
	
	BTextControl*		fMinesControl;
	BStringView*		fMinesError;
	
	BStringView*		fProtipLabel;
	BStringView*		fProtipContent;
	BStringView*		fProtipContent2;
	
	BButton*			fAcceptButton;
	BButton*			fCancelButton;
	
	bool 				fWantAccept;
	
	bool				_Validate();
};

#endif
