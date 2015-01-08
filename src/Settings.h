/*
 * Copyright 2013 Tri-Edge AI <triedgeai@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 */

#ifndef _SETTINGS_H_
#define _SETTINGS_H_

#include <Directory.h>
#include <FindDirectory.h>
#include <Path.h>
#include <File.h>
#include <String.h>

#define SIZE_BEGINNER			1
#define SIZE_INTERMEDIATE		2
#define SIZE_EXPERT				3
#define SIZE_CUSTOM				4

#define OPTION_SOUND			1
#define OPTION_RESERVED			2

#define HIGHSCORE_COUNT			10

class Settings
{
public:
	uint8 					Size;
	uint8 					Width;
	uint8 					Height;
	uint16 					Mines;
	uint8					Options;
	
	BString					NameArrayBeginner[HIGHSCORE_COUNT];
	uint32					TimeArrayBeginner[HIGHSCORE_COUNT];
	
	BString					NameArrayIntermediate[HIGHSCORE_COUNT];
	uint32					TimeArrayIntermediate[HIGHSCORE_COUNT];
	
	BString					NameArrayExpert[HIGHSCORE_COUNT];
	uint32					TimeArrayExpert[HIGHSCORE_COUNT];
	
	void					Defaults();
	void					Load();
	void					Save();
	
							Settings();
							~Settings();
	
	bool					IsHighscore(uint32 time);
	void					AddHighscore(BString name, uint32 time);
	
private:
	BPath					fPath;
	BFile*					fFile;
};

#endif
