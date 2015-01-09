/*
 * Copyright 2013 Tri-Edge AI <triedgeai@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 */

#ifndef _ANIMATED_SPRITE_H_
#define _ANIMATED_SPRITE_H_

#include <Bitmap.h>

class AnimatedSprite
{
public:
	BPoint						Point;

								AnimatedSprite(BPoint point, BBitmap** frames,
									uint32 n, bigtime_t time);
								~AnimatedSprite();
	BBitmap*					GetFrame(bigtime_t dt);

private:
	BBitmap**					fFrames;
	uint32						fN;
	uint32						fAt;
	bigtime_t					fTime;
	bigtime_t					fTimeTotal;
	bigtime_t					fTimeWait;
};

#endif
