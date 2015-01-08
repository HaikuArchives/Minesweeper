/*
 * Copyright 2013 Tri-Edge AI <triedgeai@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 */
 
#include "SubmitWindow.h"

SubmitWindow::SubmitWindow(MinesweeperWindow* parent)
	:
	BWindow(BRect(100, 100, 400, 250), "Submit Score", B_TITLED_WINDOW, 0)
{
	fParent = parent;
	
	fCongratzText = new BStringView(RECT_0, "fCongratzText", 
		"Congratulations!");
	
	fCongratzText->SetFont(be_bold_font);
	
	fInfoText = new BStringView(RECT_0, "fInfoText", 
		"Input your name to submit your score.");
	
	fNameControl = new BTextControl(RECT_0, "fNameControl", "Name: ",
		"", M(MSG_NAME));
	fNameControl->SetDivider(50);
	fNameControl->TextView()->SetMaxBytes(64);
	
	fNameError = new BStringView(RECT_0, "fNameError", " ");
	fNameError->SetHighColor(ui_color(B_FAILURE_COLOR));
	
	fSubmitButton = new BButton(RECT_0, "fSubmitButton", "Submit", 
		M(MSG_ACCEPT));
	fCancelButton = new BButton(RECT_0, "fCancelButton", "Cancel", 
		M(MSG_CANCEL));
	
	SetLayout(new BGroupLayout(B_VERTICAL));
	
	AddChild(BGroupLayoutBuilder(B_VERTICAL, 0)
		.Add(fCongratzText)
		.Add(fInfoText)
		.AddGlue()
		.Add(fNameControl)
		.Add(fNameError)
		.AddGlue()
		.Add(BGroupLayoutBuilder(B_HORIZONTAL, 0)
			.AddGlue()
			.Add(fSubmitButton)
			.Add(fCancelButton)
		)
		.SetInsets(8, 8, 8, 8)
	);
	
	Show();
}


SubmitWindow::~SubmitWindow()
{
	
}


void
SubmitWindow::MessageReceived(BMessage* msg)
{
	switch (msg->what)
	{
		case MSG_ACCEPT: {
			if(_Validate()) {
				fParent->PostMessage(MSG_SUBMIT);
				PostMessage(B_QUIT_REQUESTED);
			}
			
			break;
		}
		case MSG_CANCEL: {
			PostMessage(B_QUIT_REQUESTED);
			
			break;
		}
		default: {
			BWindow::MessageReceived(msg);
			
			break;	
		}
	}
}


bool
SubmitWindow::_Validate()
{
	Name = fNameControl->Text();
	
	if (Name.Length() < 3) {
		fNameError->SetText("The name must be atleast 3 symbols.");
		return false;
	} else if (Name.Length() >= 32) {
		fNameError->SetText("The name cannot be more than 32 symbols.");
		return false;
	} else {
		fNameError->SetText(" ");
		return true;	
	}
}
