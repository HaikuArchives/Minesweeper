/*
 * Copyright 2013 Tri-Edge AI <triedgeai@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 */

#ifndef _SUBMIT_WINDOW_H_
#define _SUBMIT_WINDOW_H_

#include "defs.h"
#include "MinesweeperWindow.h"

#include <Window.h>
#include <String.h>
#include <StringView.h>
#include <Button.h>
#include <TextControl.h>

class MinesweeperWindow;

class SubmitWindow : public BWindow {
public:
							SubmitWindow(MinesweeperWindow* parent);
							~SubmitWindow();

	void					MessageReceived(BMessage* msg);

	BString					Name;

private:
	bool					_Validate();

	MinesweeperWindow*		fParent;

	BStringView*			fCongratzText;
	BStringView*			fInfoText;

	BTextControl*			fNameControl;
	BStringView*			fNameError;

	BButton*				fSubmitButton;
	BButton*				fCancelButton;
};

#endif
