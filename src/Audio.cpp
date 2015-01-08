/*
 * Copyright 2013 Tri-Edge AI <triedgeai@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 */

#include "Audio.h"

_Audio Audio;

_Audio::_Audio()
{
	for (uint32 i = 0; i < AUDIO_POOL_SIZE; i++) {
		fPool[i].origin = NULL;
		fPool[i].sound = NULL;
	}
	
	fEnabled = true;
}


_Audio::~_Audio()
{
	
}


void
_Audio::SetEnabled(bool b)
{
	fEnabled = b;	
}


void
_Audio::PlaySound(BGameSound* sound)
{	
	if (!fEnabled)
		return;
		
	// TODO: Resolve why Clone() returns unplayable sounds.
	
	//sound = _CloneSound((BSimpleGameSound*)sound);
	sound->StartPlaying();
	
	//sound->StartPlaying();
		// This works.
		
	//sound->Clone()->StartPlaying();
		// This does not.

	/*for (uint32 i = 0; i < AUDIO_POOL_SIZE; i++) {
		if (fPool[i].origin == NULL) {
			fPool[i].origin = sound;
			fPool[i].sound = sound->Clone();
			fPool[i].sound->StartPlaying();
			break;
		} else if (fPool[i].origin == sound && !fPool[i].sound->IsPlaying()) {
			fPool[i].sound->StartPlaying();
			break;
		}
	}*/
}
