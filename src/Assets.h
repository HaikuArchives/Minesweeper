/*
 * Copyright 2013 Tri-Edge AI <triedgeai@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 */

#ifndef _ASSETS_H_
#define _ASSETS_H_

#include <Application.h>
#include <Bitmap.h>
#include <SimpleGameSound.h>
#include <TranslationUtils.h>
#include <TranslatorFormats.h>
#include <Resources.h>

class _Assets
{
public:
	struct
	{
		BBitmap* boom[5];
		BBitmap* digits	[10];
		
		struct
		{
			BBitmap* defeat;
			BBitmap* happy;
			BBitmap* oh;
			BBitmap* victory;	
		} face;
		
		BBitmap* signs	[9];
		
		BBitmap* button;
		BBitmap* flag;
		BBitmap* flagmine;
		BBitmap* hover;
		BBitmap* icon;
		BBitmap* mark;
		BBitmap* mine;
		BBitmap* press;
		BBitmap* red;
		BBitmap* redmine;
	} gfx;
	
	struct
	{
		BSimpleGameSound* boom;
		BSimpleGameSound* click;
		BSimpleGameSound* start;
		BSimpleGameSound* victory;
	} sfx;
	
	void LoadAll();
	
private:
	BResources* fResources;

	BBitmap* _LoadImage(const char* name);
	BSimpleGameSound* _LoadSound(const char* name);
};

extern _Assets Assets;

#endif
