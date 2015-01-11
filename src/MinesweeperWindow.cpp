/*
 * Copyright 2013 Tri-Edge AI <triedgeai@gmail.com>
 * Copyright 2015 Josef Gajdusek <atx@atx.name>
 * All rights reserved. Distributed under the terms of the MIT license.
 */

#include "MinesweeperWindow.h"

MinesweeperWindow::MinesweeperWindow()
	:
	BWindow(BRect(100, 100, 200, 200), "Minesweeper", B_TITLED_WINDOW,
		B_NOT_RESIZABLE)
{
	Assets.LoadAll();

	fBackView = new BView(BRect(0, 0, 100, 100), "fBackView", B_FOLLOW_ALL, 0);
	fBackView->SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));

	fMenu = new BMenuBar(RECT_0, "fMenu", B_FOLLOW_LEFT_RIGHT, B_ITEMS_IN_ROW, true);

	fGameMenu = new BMenu("Game", B_ITEMS_IN_COLUMN);
	fNewItem = new BMenuItem("New", M(MSG_NEW), 'N');
	fHighscoreItem = new BMenuItem("Highscore", M(MSG_HIGHSCORE));

	fSizeMenu = new BMenu("Size", B_ITEMS_IN_COLUMN);
	fBeginnerItem = new BMenuItem("Beginner (9x9, 10 mines)", M(MSG_BEGINNER));
	fIntermediateItem = new BMenuItem("Intermediate (16x16, 40 mines)", M(MSG_INTERMEDIATE));
	fExpertItem = new BMenuItem("Expert (30x16, 80 mines)", M(MSG_EXPERT));
	fCustomItem	= new BMenuItem("Custom", M(MSG_CUSTOM));

	fSoundItem = new BMenuItem("Sound", M(MSG_SOUND));
	fQuitItem = new BMenuItem("Quit", M(MSG_QUIT), 'Q');

	fHelpMenu = new BMenu("Help", B_ITEMS_IN_COLUMN);
	fAboutItem = new BMenuItem("About", M(MSG_ABOUT));

	FaceButton = new ImageButton(BRect(50 - 16, 0, 50 + 16, 32), "fFaceButton",
		Assets.gfx.face.happy, M(MSG_FACE), B_FOLLOW_H_CENTER);

	MineCounter = new DigitalTimerView(BRect(4, 4, 40, 26), "fMineCounter",
		B_FOLLOW_LEFT);

	TimeCounter = new DigitalTimerView(BRect(100 - 48, 4, 88, 26),
		"fTimeCounter", B_FOLLOW_RIGHT);

	fSettings.Load();

	if (fSettings.Size == SIZE_BEGINNER)
		fBeginnerItem->SetMarked(true);
	else if (fSettings.Size == SIZE_INTERMEDIATE)
		fIntermediateItem->SetMarked(true);
	else if (fSettings.Size == SIZE_EXPERT)
		fExpertItem->SetMarked(true);
	else if (fSettings.Size == SIZE_CUSTOM)
		fCustomItem->SetMarked(true);

	if (fSettings.Options & OPTION_SOUND == OPTION_SOUND) {
		fSoundItem->SetMarked(true);
		Audio.SetEnabled(true);
	} else {
		fSoundItem->SetMarked(false);
		Audio.SetEnabled(false);
	}

	AddChild(fBackView);

	fBackView->AddChild(fMenu);
	{
		fMenu->AddItem(fGameMenu);
		{
			fGameMenu->AddItem(fNewItem);
			fGameMenu->AddSeparatorItem();
			fGameMenu->AddItem(fHighscoreItem);
			fGameMenu->AddSeparatorItem();

			fGameMenu->AddItem(fSizeMenu);
			{
				fSizeMenu->AddItem(fBeginnerItem);
				fSizeMenu->AddItem(fIntermediateItem);
				fSizeMenu->AddItem(fExpertItem);
				fSizeMenu->AddSeparatorItem();
				fSizeMenu->AddItem(fCustomItem);
			}

			fGameMenu->AddItem(fSoundItem);
			fGameMenu->AddSeparatorItem();
			fGameMenu->AddItem(fQuitItem);
		}

		fMenu->AddItem(fHelpMenu);
		{
			fHelpMenu->AddItem(fAboutItem);
		}
	}

	fControlBox = new BBox(BRect(3, 24, 100 - 3, 24 + 32), "fControlBox",
		B_FOLLOW_LEFT_RIGHT, B_WILL_DRAW,
		B_FANCY_BORDER);

	fControlBox->AddChild(FaceButton);
	fControlBox->AddChild(MineCounter);
	fControlBox->AddChild(TimeCounter);

	fFieldBox = new BBox(BRect(3, 24 + 32 + 3, 100 - 3, 100 - 3), "fFieldBox",
		B_FOLLOW_ALL, B_WILL_DRAW | B_FRAME_EVENTS, B_FANCY_BORDER);

	fMinefield = new MinefieldView(this, fSettings.Width, fSettings.Height,
		fSettings.Mines);

	fFieldBox->AddChild(fMinefield);

	fBackView->AddChild(fControlBox);
	fBackView->AddChild(fFieldBox);

	fControlBox->SetResizingMode(B_FOLLOW_LEFT_RIGHT);

	fIsResizing = false;
	fCurrentWidth = 0.0f;
	fCurrentHeight = 0.0f;

	_GracefulResize(24 * fSettings.Width + 12, 24 * fSettings.Height + 32 + 36);

	fTimeStart = system_time();

	BMessageRunner::StartSending(this, new BMessage(MSG_TICK), 50 * 1000,
		INT_MAX);
		// 20 FPS
}


MinesweeperWindow::~MinesweeperWindow()
{

}


void
MinesweeperWindow::MessageReceived(BMessage* msg)
{
	switch (msg->what) {
		case MSG_TICK: {
			if (fIsResizing) {
				float dw = fTargetWidth - fCurrentWidth;
				float dh = fTargetHeight - fCurrentHeight;

				if (dw * dw + dh * dh < 1.0f) {
					fCurrentWidth = fTargetWidth;
					fCurrentHeight = fTargetHeight;
					fIsResizing = false;
				} else {
					fCurrentWidth += dw * 0.5f;
					fCurrentHeight += dh * 0.5f;
				}

				ResizeTo((int)fCurrentWidth, (int)fCurrentHeight);
			}

			if (!fMinefield->GameOver && !fMinefield->Victory) {
				fTimeNow = system_time();
				fTimeScore = (fTimeNow - fTimeStart) / (1000 * 1000);
				TimeCounter->Set(fTimeScore);
			}

			break;
		}
		case MSG_VICTORY: {
			if (fSettings.IsHighscore(fTimeScore)) {
				fSubmitWindow = new SubmitWindow(this);
			}

			break;
		}
		case MSG_SUBMIT: {
			fSettings.AddHighscore(fSubmitWindow->Name, fTimeScore);
			fSettings.Save();

			break;
		}
		case MSG_FACE: {
			fMinefield->Clear();
			fTimeStart = system_time();

			break;
		}
		case MSG_NEW: {
			fMinefield->Clear();
			fTimeStart = system_time();

			break;
		}
		case MSG_HIGHSCORE: {
			new HighscoreWindow(&fSettings);

			break;
		}
		case MSG_BEGINNER: {
			fBeginnerItem->SetMarked(true);
			fIntermediateItem->SetMarked(false);
			fExpertItem->SetMarked(false);
			fCustomItem->SetMarked(false);

			fSettings.Size = SIZE_BEGINNER;
			fSettings.Width = 9;
			fSettings.Height = 9;
			fSettings.Mines = 10;

			fSettings.Save();

			fMinefield->ResizeTo(fSettings.Width, fSettings.Height, fSettings.Mines);
			_GracefulResize(24 * fSettings.Width + 12, 24 * fSettings.Height + 32 + 38);

			fTimeStart = system_time();

			break;
		}
		case MSG_INTERMEDIATE: {
			fBeginnerItem->SetMarked(false);
			fIntermediateItem->SetMarked(true);
			fExpertItem->SetMarked(false);
			fCustomItem->SetMarked(false);

			fSettings.Size = SIZE_INTERMEDIATE;
			fSettings.Width = 16;
			fSettings.Height = 16;
			fSettings.Mines = 40;

			fSettings.Save();

			fMinefield->ResizeTo(fSettings.Width, fSettings.Height, fSettings.Mines);
			_GracefulResize(24 * fSettings.Width + 12, 24 * fSettings.Height + 32 + 38);

			fTimeStart = system_time();

			break;
		}
		case MSG_EXPERT: {
			fBeginnerItem->SetMarked(false);
			fIntermediateItem->SetMarked(false);
			fExpertItem->SetMarked(true);
			fCustomItem->SetMarked(false);

			fSettings.Size = SIZE_EXPERT;
			fSettings.Width = 30;
			fSettings.Height = 16;
			fSettings.Mines = 80;

			fSettings.Save();

			fMinefield->ResizeTo(fSettings.Width, fSettings.Height, fSettings.Mines);
			_GracefulResize(24 * fSettings.Width + 12, 24 * fSettings.Height + 32 + 38);

			fTimeStart = system_time();

			break;
		}
		case MSG_CUSTOM: {
			fCustomFieldWindow = new CustomFieldWindow(this, fSettings.Width, 
				fSettings.Height, fSettings.Mines);

			break;
		}
		case MSG_CUSTOM_SET: {
			fBeginnerItem->SetMarked(false);
			fIntermediateItem->SetMarked(false);
			fExpertItem->SetMarked(false);
			fCustomItem->SetMarked(true);

			fSettings.Size = SIZE_CUSTOM;

			fSettings.Width = fCustomFieldWindow->Width;
			fSettings.Height = fCustomFieldWindow->Height;
			fSettings.Mines = fCustomFieldWindow->Mines;

			fSettings.Save();

			fMinefield->ResizeTo(fSettings.Width, fSettings.Height, fSettings.Mines);
			_GracefulResize(24 * fSettings.Width + 12, 24 * fSettings.Height + 32 + 38);

			fTimeStart = system_time();

			break;
		}
		case MSG_SOUND: {
			if (fSettings.Options & OPTION_SOUND == OPTION_SOUND) {
				fSoundItem->SetMarked(false);
				Audio.SetEnabled(false);
				fSettings.Options &= ~OPTION_SOUND;
			} else {
				fSoundItem->SetMarked(true);
				Audio.SetEnabled(true);
				fSettings.Options |= OPTION_SOUND;
			}

			fSettings.Save();

			break;
		}
		case MSG_QUIT: {
			be_app->PostMessage(B_QUIT_REQUESTED);

			break;
		}
		case MSG_ABOUT: {
			new AboutWindow();
		}
		default: {
			BWindow::MessageReceived(msg);

			break;
		}
	}
}


bool
MinesweeperWindow::QuitRequested()
{
	BAlert* alert = new BAlert("Quit?", "Are you sure you want to quit?",
		"Quit", "Cancel", NULL, B_WIDTH_AS_USUAL, B_EVEN_SPACING, 
		B_WARNING_ALERT);
		
	int32 result = alert->Go();
		
	if (result == 1) {
		return false;
	} else {
		be_app->PostMessage(B_QUIT_REQUESTED);
		return true;
	}
}


void
MinesweeperWindow::_GracefulResize(uint32 newWidth, uint32 newHeight)
{
	fIsResizing = true;
	fTargetWidth = (float)newWidth;
	fTargetHeight = (float)newHeight;	
}
