/*
 * Copyright 2013 Tri-Edge AI <triedgeai@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 */
 
#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite(BPoint point, BBitmap** frames, uint32 n, 
	bigtime_t time)
{
	Point = point - BPoint(frames[0]->Bounds().RightBottom().x / 2, 
		frames[0]->Bounds().RightBottom().y / 2);
	
	fFrames = frames;
	fN = n;
	fAt = 0;
	fTime = 0;
	fTimeTotal = time;
	fTimeWait = time / fN;
}

AnimatedSprite::~AnimatedSprite()
{
	
}

BBitmap*
AnimatedSprite::GetFrame(bigtime_t dt)
{
	fTime += dt;

	if (fAt >= fN)
		return NULL;
	
	BBitmap* frame = fFrames[fAt];
	
	while (fTime > fTimeWait) {
		fTime -= fTimeWait;
		fAt++;
	}
	
	return frame;
}

