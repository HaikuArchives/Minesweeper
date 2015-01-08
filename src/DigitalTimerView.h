/*
 * Copyright 2013 Tri-Edge AI <triedgeai@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 */
 
#ifndef _DIGITAL_TIMER_VIEW_H_
#define _DIGITAL_TIMER_VIEW_H_

#include "Assets.h"

#include <View.h>
#include <Box.h>

class DigitalTimerView : public BBox
{
public:
							DigitalTimerView(BRect frame, const char* name, 
								uint32 resizingMode);
							~DigitalTimerView();
							
	void					Draw(BRect updateRect);
	void					Set(uint32 value);
								
private:
	uint32					fDigit1;
	uint32					fDigit2;
	uint32					fDigit3;
	
};

#endif
