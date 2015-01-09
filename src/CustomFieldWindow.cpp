/*
 * Copyright 2013 Tri-Edge AI <triedgeai@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 */

#include "CustomFieldWindow.h"

CustomFieldWindow::CustomFieldWindow(MinesweeperWindow* parent, uint32 width,
	uint32 height, uint32 mines)
	:
	BWindow(BRect(100, 100, 450, 450), "Custom Field Size", B_TITLED_WINDOW,
		B_NOT_RESIZABLE)
{
	fParent = parent;

	Width = width;
	Height = height;
	Mines = mines;

	fInfo = new BStringView(RECT_0, "fInfo",
		"Input the characteristics of your desired minefield.");

	fWidthControl = new BTextControl(RECT_0, "fWidthControl", "Width:",
		(BString() << Width), M(MSG_WIDTH));
	fWidthControl->SetDivider(50);
	fWidthControl->TextView()->SetMaxBytes(2);

	fWidthError = new BStringView(RECT_0, "fWidthError",
		" ");
	fWidthError->SetHighColor(ui_color(B_FAILURE_COLOR));

	fHeightControl = new BTextControl(RECT_0, "fHeightControl", "Height:",
		(BString() << Height), M(MSG_HEIGHT));
	fHeightControl->SetDivider(50);
	fHeightControl->TextView()->SetMaxBytes(2);

	fHeightError = new BStringView(RECT_0, "fHeightError", " ");
	fHeightError->SetHighColor(ui_color(B_FAILURE_COLOR));

	fMinesControl = new BTextControl(RECT_0, "fMinesControl", "Mines:",
		(BString() << Mines), M(MSG_MINES));
	fMinesControl->SetDivider(50);
	fMinesControl->TextView()->SetMaxBytes(3);

	fMinesError = new BStringView(RECT_0, "fMinesError",
		" ");
	fMinesError->SetHighColor(ui_color(B_FAILURE_COLOR));

	fProtipLabel = new BStringView(RECT_0, "fProtipLabel", "Notice:");
	fProtipLabel->SetFont(be_bold_font);

	fProtipContent = new BStringView(RECT_0, "fProtipContent",
		"Games with custom minefields don't get");
	fProtipContent2 = new BStringView(RECT_0, "fProtipContent2",
		"listed in the highscores.");

	fAcceptButton = new BButton(RECT_0, "fAcceptButton", "Accept",
		M(MSG_ACCEPT));
	fCancelButton = new BButton(RECT_0, "fCancelButton", "Cancel",
		M(MSG_CANCEL));

	SetLayout(new BGroupLayout(B_VERTICAL));

	AddChild(BGroupLayoutBuilder(B_VERTICAL, 0)
			.Add(fInfo)
			.AddGlue()
			.Add(fWidthControl)
			.Add(fWidthError)
			.AddGlue()
			.Add(fHeightControl)
			.Add(fHeightError)
			.AddGlue()
			.Add(fMinesControl)
			.Add(fMinesError)
			.AddGlue()
			.Add(BGroupLayoutBuilder(B_HORIZONTAL, 0)
				.Add(fProtipLabel)
				.Add(fProtipContent)
			)
			.Add(fProtipContent2)
			.AddGlue()
			.Add(BGroupLayoutBuilder(B_HORIZONTAL, 0)
				.AddGlue()
				.Add(fAcceptButton)
				.Add(fCancelButton)
			)
			.SetInsets(8, 8, 8, 8)
	);

	Show();
}


CustomFieldWindow::~CustomFieldWindow()
{

}


void
CustomFieldWindow::MessageReceived(BMessage* msg)
{
	switch (msg->what)
	{
		case MSG_WIDTH:
		case MSG_HEIGHT:
		case MSG_MINES: {
			_Validate();
			break;
		}
		case MSG_ACCEPT: {
			if (_Validate()) {
				Result = true;
				this->PostMessage(B_QUIT_REQUESTED);
				fParent->PostMessage(MSG_CUSTOM_SET);
			}
			return;
		}
		case MSG_CANCEL: {
			Result = false;
			this->PostMessage(B_QUIT_REQUESTED);

			return;
		}
	}
}


bool
CustomFieldWindow::_Validate()
{
	bool isValid = true;

	Width = atoi(fWidthControl->Text());
	Height = atoi(fHeightControl->Text());
	Mines = atoi(fMinesControl->Text());

	if (Width < 0) {
		fWidthError->SetText("Width cannot be negative.");
		isValid = false;
	} else if (Width > 30) {
		fWidthError->SetText("Width must be less than 30.");
		isValid = false;
	} else {
		fWidthError->SetText(" ");
	}

	if (Height < 0) {
		fHeightError->SetText("Height cannot be negative.");
		isValid = false;
	} else if (Height > 30) {
		fHeightError->SetText("Height must be less than 30.");
		isValid = false;
	} else {
		fHeightError->SetText(" ");
	}

	if (Mines < 0) {
		fMinesError->SetText(
			"Why is it called a minefield, if there are no mines?");
		isValid = false;
	} else if (Mines > Width * Height - 1) {
		fMinesError->SetText("There is no space for so much mines.");
		isValid = false;
	} else {
		fMinesError->SetText(" ");
	}

	return isValid;
}
