/*
 * Copyright 2013 Tri-Edge AI <triedgeai@gmail.com>
 * Copyright 2015 Josef Gajdusek <atx@atx.name>
 * All rights reserved. Distributed under the terms of the MIT license.
 */

#include "DigitalTimerView.h"

#include <View.h>

DigitalTimerView::DigitalTimerView(BRect frame, const char* name,
	uint32 resizingMode, uint32 ndigits)
	:
	BView(frame, name, resizingMode, B_WILL_DRAW),
	fNDigits(ndigits)
{
	rgb_color black = {0, 0, 0, 255};
	SetViewColor(black);

	fDigits = new uint32[fNDigits];
	fViews = new BView*[fNDigits];

	BGroupLayout* group = new BGroupLayout(B_HORIZONTAL, 0);
	SetLayout(group);
	for (uint32 i = 0; i < fNDigits; i++) {
		fDigits[i] = 0;
		fViews[i] = new BView(NULL, 0);
		group->AddView(fViews[i]);
	}

	SetExplicitSize(BSize(13 * fNDigits, 23));
}


DigitalTimerView::~DigitalTimerView()
{

}


void
DigitalTimerView::AttachedToWindow()
{
	_UpdateBitmap();
}


void
DigitalTimerView::Set(uint32 value)
{
	if (fValue == value)
		return;

	for (uint32 i = 0; i < fNDigits; i++) {
		fDigits[i] = value % 10;
		value /= 10;
	}

	if (Window())
		_UpdateBitmap();
}


void
DigitalTimerView::_UpdateBitmap()
{
	for (uint32 i = 0; i < fNDigits; i++)
		fViews[i]->SetViewBitmap(Assets.gfx.digits[fDigits[fNDigits - i - 1]]);
}
