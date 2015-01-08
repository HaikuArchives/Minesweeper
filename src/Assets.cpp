/*
 * Copyright 2013 Tri-Edge AI <triedgeai@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 */

#include "Assets.h"

_Assets Assets;

void
_Assets::LoadAll()
{
	fResources = be_app->AppResources();
	
	gfx.boom[0] 		= _LoadImage("assets/gfx/boom/0.png");
	gfx.boom[1] 		= _LoadImage("assets/gfx/boom/1.png");
	gfx.boom[2] 		= _LoadImage("assets/gfx/boom/2.png");
	gfx.boom[3] 		= _LoadImage("assets/gfx/boom/3.png");
	gfx.boom[4] 		= _LoadImage("assets/gfx/boom/4.png");
	
	gfx.digits[0] 		= _LoadImage("assets/gfx/digits/0.png");
	gfx.digits[1] 		= _LoadImage("assets/gfx/digits/1.png");
	gfx.digits[2] 		= _LoadImage("assets/gfx/digits/2.png");
	gfx.digits[3]		= _LoadImage("assets/gfx/digits/3.png");
	gfx.digits[4] 		= _LoadImage("assets/gfx/digits/4.png");
	gfx.digits[5] 		= _LoadImage("assets/gfx/digits/5.png");
	gfx.digits[6] 		= _LoadImage("assets/gfx/digits/6.png");
	gfx.digits[7]		= _LoadImage("assets/gfx/digits/7.png");
	gfx.digits[8] 		= _LoadImage("assets/gfx/digits/8.png");
	gfx.digits[9] 		= _LoadImage("assets/gfx/digits/9.png");
	
	gfx.face.defeat 	= _LoadImage("assets/gfx/face/defeat.png");
	gfx.face.happy 		= _LoadImage("assets/gfx/face/happy.png");
	gfx.face.oh 		= _LoadImage("assets/gfx/face/oh.png");
	gfx.face.victory 	= _LoadImage("assets/gfx/face/victory.png");
	
	gfx.signs[0] 		= _LoadImage("assets/gfx/signs/0.png");
	gfx.signs[1] 		= _LoadImage("assets/gfx/signs/1.png");
	gfx.signs[2]		= _LoadImage("assets/gfx/signs/2.png");
	gfx.signs[3] 		= _LoadImage("assets/gfx/signs/3.png");
	gfx.signs[4] 		= _LoadImage("assets/gfx/signs/4.png");
	gfx.signs[5] 		= _LoadImage("assets/gfx/signs/5.png");
	gfx.signs[6] 		= _LoadImage("assets/gfx/signs/6.png");
	gfx.signs[7] 		= _LoadImage("assets/gfx/signs/7.png");
	gfx.signs[8] 		= _LoadImage("assets/gfx/signs/8.png");
	
	gfx.button 			= _LoadImage("assets/gfx/button.png");
	gfx.flag 			= _LoadImage("assets/gfx/flag.png");
	gfx.flagmine		= _LoadImage("assets/gfx/flagmine.png");
	gfx.hover 			= _LoadImage("assets/gfx/hover.png");
	gfx.icon			= _LoadImage("assets/gfx/icon.png");
	gfx.mark 			= _LoadImage("assets/gfx/mark.png");
	gfx.mine 			= _LoadImage("assets/gfx/mine.png");
	gfx.press 			= _LoadImage("assets/gfx/press.png");
	gfx.red 			= _LoadImage("assets/gfx/red.png");
	gfx.redmine 		= _LoadImage("assets/gfx/redmine.png");
	
	sfx.boom			= _LoadSound("assets/sfx/boom.wav");
	sfx.click			= _LoadSound("assets/sfx/click.wav");
	sfx.start			= _LoadSound("assets/sfx/start.wav");
	sfx.victory			= _LoadSound("assets/sfx/victory.wav");
}


BBitmap*
_Assets::_LoadImage(const char* name)
{
	size_t size;
	const void* data = fResources->LoadResource('rGFX', name, &size);
	BMemoryIO stream(data, size);
	
	stream.Seek(0, SEEK_SET);
	
	BBitmap* image = BTranslationUtils::GetBitmap(&stream);
	
	return image;	
}

// Temporary, only while bottom trick is needed.
// --------------------
#include <string>
#include <cstdlib>
#include <errno.h>
using namespace std;
// --------------------

BSimpleGameSound*
_Assets::_LoadSound(const char* name)
{
	// TODO: Find a normal way to load sounds from resources.
	/* size_t size;
	const void* data = fResources->LoadResource('rSFX', name, &size);
	gs_audio_format format;
	
	format.frame_rate = 44100;
	format.channel_count = 1;
	format.format = 0x03;
	format.byte_order = 0;
	format.buffer_size = 0;
	
	BSimpleGameSound* sound = new BSimpleGameSound(data, size, &format);
	
	cout<<sound<<endl;
	cout<<(sound->InitCheck() == B_OK)<<endl;
	
	return sound; */
	
	// Until then:
	
	size_t size;
	const void* data = fResources->LoadResource('rSFX', name, &size);
	
	string path = name;
	string tempname = path.substr(path.rfind('/') + 1);
	
	BFile* soundFile = new BFile(tempname.c_str(), B_WRITE_ONLY | B_CREATE_FILE);
	soundFile->Write(data, size);
	delete soundFile;
	
	BSimpleGameSound* sound = new BSimpleGameSound(tempname.c_str());

	cout<<tempname.c_str()<<endl;
	cout<<remove(tempname.c_str())<<endl;
	cout<<strerror(errno)<<endl;
	
	return sound;
}
