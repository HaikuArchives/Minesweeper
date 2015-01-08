/*
 * Copyright 2013 Tri-Edge AI <triedgeai@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 */
 
#ifndef _AUDIO_H_
#define _AUDIO_H_

#define AUDIO_POOL_SIZE	64

#include <SimpleGameSound.h>

class _Audio
{
public:
							_Audio();
							~_Audio();
							
	void					SetEnabled(bool b);
	
	void					PlaySound(BGameSound* sound);

private:
	bool					fEnabled;
	
	struct
	{
		BGameSound*	 		origin;
		BGameSound* 		sound;
	} fPool[AUDIO_POOL_SIZE];

};

extern _Audio Audio;

#endif
