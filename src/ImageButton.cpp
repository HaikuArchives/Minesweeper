/*
 * Copyright 2013 Tri-Edge AI <triedgeai@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 */

#include "ImageButton.h"

ImageButton::ImageButton(BRect frame, const char* name, BBitmap* image, 
	BMessage* message, uint32 resizingMode)
	:
	BButton(frame, name, "", message, resizingMode)
{
	fImage = image;
	
	SetDrawingMode(B_OP_ALPHA);
}


ImageButton::~ImageButton()
{
	
}


void
ImageButton::Draw(BRect updateRect)
{
	BButton::Draw(updateRect);
	DrawBitmap(fImage, BPoint(0, 0));
}


void
ImageButton::SetBitmap(BBitmap* image)
{
	fImage = image;
	Invalidate();
}
