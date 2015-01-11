/*
 * Copyright 2013 Tri-Edge AI <triedgeai@gmail.com>
 * Copyright 2015 Josef Gajdusek <atx@atx.name>
 * All rights reserved. Distributed under the terms of the MIT license.
 */
 
#ifndef _DIGITAL_TIMER_VIEW_H_
#define _DIGITAL_TIMER_VIEW_H_

#include "Assets.h"

#include <View.h>
#include <Box.h>
#include <Bitmap.h>
#include <GroupLayout.h>

class DigitalTimerView : public BView {
public:
							DigitalTimerView(BRect frame, const char* name,
								uint32 resizingMode, uint32 ndigits=3);
							~DigitalTimerView();

	void					AttachedToWindow();
	void					Set(uint32 value);

private:
	void					_UpdateBitmap();

	uint32					fNDigits;
	uint32					fValue;
	BView**					fViews;
	uint32*					fDigits;
};

#endif
