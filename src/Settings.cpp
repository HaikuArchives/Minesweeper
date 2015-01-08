/*
 * Copyright 2013 Tri-Edge AI <triedgeai@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 */
 
#include "Settings.h"

#include <stdio.h>

Settings::Settings()
{
  	find_directory(B_USER_SETTINGS_DIRECTORY, &fPath);
	fPath.Append("Minesweeper_settings", true);
}


Settings::~Settings()
{
	
}


void
Settings::Defaults()
{
	Size = SIZE_EXPERT;
	Width = 30;
	Height = 16;
	Mines = 80;
	Options = OPTION_SOUND;
	
	for (uint32 i = 0; i < HIGHSCORE_COUNT; i++) {
		NameArrayBeginner[i] = "-";
		TimeArrayBeginner[i] = ~0;
		
		NameArrayIntermediate[i] = "-";
		TimeArrayIntermediate[i] = ~0;
		
		NameArrayExpert[i] = "-";
		TimeArrayExpert[i] = ~0;
	}
}


void
Settings::Load()
{
	fFile = new BFile(fPath.Path(), B_READ_ONLY);
	
	if (fFile->InitCheck() == B_OK) {
		fFile->Read(&Size, sizeof(Size));
		fFile->Read(&Width, sizeof(Width));
		fFile->Read(&Height, sizeof(Height));
		fFile->Read(&Mines, sizeof(Mines));
		fFile->Read(&Options, sizeof(Options));
		
		for (uint32 i = 0; i < HIGHSCORE_COUNT; i++) {
			uint32 len;
			char buff[64];
			
			fFile->Read(&len, sizeof(len));
			fFile->Read(buff, len); 
			buff[len] = '\0';
			NameArrayBeginner[i] = buff;
			fFile->Read(&TimeArrayBeginner[i], sizeof(TimeArrayBeginner[i]));
			
			fFile->Read(&len, sizeof(len));
			fFile->Read(buff, len); 
			buff[len] = '\0';
			NameArrayIntermediate[i] = buff;
			fFile->Read(&TimeArrayIntermediate[i], sizeof(TimeArrayIntermediate[i]));
			
			fFile->Read(&len, sizeof(len));
			fFile->Read(buff, len); 
			buff[len] = '\0';
			NameArrayExpert[i] = buff;
			fFile->Read(&TimeArrayExpert[i], sizeof(TimeArrayExpert[i]));		
		}
	} else {
		Defaults();	
	}
	
	delete fFile;
}


void
Settings::Save()
{
	fFile = new BFile(fPath.Path(), B_WRITE_ONLY | B_CREATE_FILE);
	
	fFile->Write(&Size, sizeof(Size));
	fFile->Write(&Width, sizeof(Width));
	fFile->Write(&Height, sizeof(Height));
	fFile->Write(&Mines, sizeof(Mines));
	fFile->Write(&Options, sizeof(Options));
	
	for (uint32 i = 0; i < HIGHSCORE_COUNT; i++) {
		uint32 len;
		
		len = NameArrayBeginner[i].Length();
		fFile->Write(&len, sizeof(len));
		fFile->Write(NameArrayBeginner[i].String(), len);
		fFile->Write(&TimeArrayBeginner[i], sizeof(TimeArrayBeginner[i]));	
		
		len = NameArrayIntermediate[i].Length();
		fFile->Write(&len, sizeof(len));
		fFile->Write(NameArrayIntermediate[i].String(), len);
		fFile->Write(&TimeArrayIntermediate[i], sizeof(TimeArrayIntermediate[i]));
		
		len = NameArrayExpert[i].Length();
		fFile->Write(&len, sizeof(len));
		fFile->Write(NameArrayExpert[i].String(), len);
		fFile->Write(&TimeArrayExpert[i], sizeof(TimeArrayExpert[i]));
	}
	
	delete fFile;
}


bool
Settings::IsHighscore(uint32 time) 
{
	if (Size == SIZE_BEGINNER) {
		if (time < TimeArrayBeginner[HIGHSCORE_COUNT - 1]) {
			return true;
		}
	} else if (Size == SIZE_INTERMEDIATE) {
		if (time < TimeArrayIntermediate[HIGHSCORE_COUNT - 1]) {
			return true;
		}
	} else if (Size == SIZE_EXPERT) {
		if (time < TimeArrayExpert[HIGHSCORE_COUNT - 1]) {
			return true;
		}
	}
	
	return false;
}


void
Settings::AddHighscore(BString name, uint32 time)
{
	if (Size == SIZE_BEGINNER) {
		for (int32 i = 0; i < HIGHSCORE_COUNT; i++) {
			if (time < TimeArrayBeginner[i]) {
				for (int32 k = HIGHSCORE_COUNT - 2; k >= i; k--) {
					NameArrayBeginner[k + 1] = NameArrayBeginner[k];
					TimeArrayBeginner[k + 1] = TimeArrayBeginner[k];
				}
				
				NameArrayBeginner[i] = name;
				TimeArrayBeginner[i] = time;
				
				break;
			}
		}
	} else if(Size == SIZE_INTERMEDIATE) {
		for (int32 i = 0; i < HIGHSCORE_COUNT; i++) {
			if (time < TimeArrayIntermediate[i]) {
				for (int32 k = HIGHSCORE_COUNT - 2; k >= i; k--) {
					NameArrayIntermediate[k + 1] = NameArrayIntermediate[k];
					TimeArrayIntermediate[k + 1] = TimeArrayIntermediate[k];
				}
				
				NameArrayIntermediate[i] = name;
				TimeArrayIntermediate[i] = time;
				
				break;
			}
		}
	} else if(Size == SIZE_EXPERT) {
		for (int32 i = 0; i < HIGHSCORE_COUNT; i++) {
			if (time < TimeArrayExpert[i]) {
				for (int32 k = HIGHSCORE_COUNT - 2; k >= i; k--) {
					NameArrayExpert[k + 1] = NameArrayExpert[k];
					TimeArrayExpert[k + 1] = TimeArrayExpert[k];
				}
				
				NameArrayExpert[i] = name;
				TimeArrayExpert[i] = time;
				
				break;
			}
		}
	}
}
