/*
 * Copyright 2013 Tri-Edge AI <triedgeai@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 */

#include "HighscoreWindow.h"

HighscoreWindow::HighscoreWindow(const Settings* settings)
	:
	BWindow(BRect(100, 100, 500, 700), "Highscores",
		B_TITLED_WINDOW, 0)
{
	fBeginnerText = new BStringView(RECT_0, "fBeginnerText",
		"Beginner");

	fBeginnerText->SetFont(be_bold_font);
	fBeginnerText->SetAlignment(B_ALIGN_CENTER);

	fIntermediateText = new BStringView(RECT_0, "fIntermediateText",
		"Intermediate");

	fIntermediateText->SetFont(be_bold_font);
	fIntermediateText->SetAlignment(B_ALIGN_CENTER);

	fExpertText = new BStringView(RECT_0, "fExpertText",
		"Expert");

	fExpertText->SetFont(be_bold_font);
	fExpertText->SetAlignment(B_ALIGN_CENTER);

	for(uint32 i = 0; i < HIGHSCORE_COUNT; i++) {
		fNameArrayBeginner[i] = new BStringView(RECT_0, "",
			settings->NameArrayBeginner[i]);
		fNameArrayBeginner[i]->SetAlignment(B_ALIGN_LEFT);

		fTimeArrayBeginner[i] = new BStringView(RECT_0, "",
			_TimeString(settings->TimeArrayBeginner[i]));
		fTimeArrayBeginner[i]->SetAlignment(B_ALIGN_RIGHT);

		fNameArrayIntermediate[i] = new BStringView(RECT_0, "",
			settings->NameArrayIntermediate[i]);
		fNameArrayIntermediate[i]->SetAlignment(B_ALIGN_LEFT);

		fTimeArrayIntermediate[i] = new BStringView(RECT_0, "",
			_TimeString(settings->TimeArrayIntermediate[i]));
		fTimeArrayIntermediate[i]->SetAlignment(B_ALIGN_RIGHT);

		fNameArrayExpert[i] = new BStringView(RECT_0, "",
			settings->NameArrayExpert[i]);
		fNameArrayExpert[i]->SetAlignment(B_ALIGN_LEFT);

		fTimeArrayExpert[i] = new BStringView(RECT_0, "",
			_TimeString(settings->TimeArrayExpert[i]));
		fTimeArrayExpert[i]->SetAlignment(B_ALIGN_RIGHT);
	}

	fCloseButton = new BButton(RECT_0, "fCloseButton", "Close",
		M(B_QUIT_REQUESTED));

	SetLayout(new BGroupLayout(B_VERTICAL));

	BGroupLayoutBuilder ExpertGroup(B_VERTICAL, 0);
	BGroupLayoutBuilder IntermediateGroup(B_VERTICAL, 0);
	BGroupLayoutBuilder BeginnerGroup(B_VERTICAL, 0);

	ExpertGroup.Add(fExpertText);
	IntermediateGroup.Add(fIntermediateText);
	BeginnerGroup.Add(fBeginnerText);

	for (uint32 i = 0; i < HIGHSCORE_COUNT; i++) {
		ExpertGroup.Add(BGroupLayoutBuilder(B_HORIZONTAL, 0)
			.Add(fNameArrayExpert[i])
			.Add(fTimeArrayExpert[i])
		);

		IntermediateGroup.Add(BGroupLayoutBuilder(B_HORIZONTAL, 0)
			.Add(fNameArrayIntermediate[i])
			.Add(fTimeArrayIntermediate[i])
		);

		BeginnerGroup.Add(BGroupLayoutBuilder(B_HORIZONTAL, 0)
			.Add(fNameArrayBeginner[i])
			.Add(fTimeArrayBeginner[i])
		);
	}

	AddChild(BGroupLayoutBuilder(B_VERTICAL, 0)
		.Add(ExpertGroup)
		.AddGlue()
		.Add(IntermediateGroup)
		.AddGlue()
		.Add(BeginnerGroup)
		.AddGlue()
		.Add(fCloseButton)
		.SetInsets(8, 8, 8, 8)
	);

	Show();
}


HighscoreWindow::~HighscoreWindow()
{

}


BString
HighscoreWindow::_TimeString(uint32 time)
{
	if (time == ~(uint32)0)
		return "-";
	else
		return BString() << time;
}
