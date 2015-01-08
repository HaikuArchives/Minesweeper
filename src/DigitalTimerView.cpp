/*
 * Copyright 2013 Tri-Edge AI <triedgeai@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 */

#include "DigitalTimerView.h"

#include <View.h>

DigitalTimerView::DigitalTimerView(BRect frame, const char* name, 
	uint32 resizingMode)
	:
	BBox(frame, name, resizingMode, B_WILL_DRAW, B_FANCY_BORDER)
{
	fDigit1 = 0;
	fDigit2 = 0;
	fDigit3 = 0;
	
	SetDrawingMode(B_OP_ALPHA);
}


DigitalTimerView::~DigitalTimerView()
{
	
}


void
DigitalTimerView::Draw(BRect updateRect)
{
	BBox::Draw(updateRect);
	
	DrawBitmap(Assets.gfx.digits[fDigit3], BPoint(0, 0));
	DrawBitmap(Assets.gfx.digits[fDigit2], BPoint(12, 0));
	DrawBitmap(Assets.gfx.digits[fDigit1], BPoint(24, 0));
}


void
DigitalTimerView::Set(uint32 value)
{
	if (value > 999) {
		fDigit1 = 0;
		fDigit2 = 0;
		fDigit3 = 0;
	} else {
		fDigit1 = value % 10;
		value /= 10;
		fDigit2 = value % 10;
		value /= 10;
		fDigit3 = value % 10;
	}
	
	Invalidate();
}
