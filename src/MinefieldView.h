/*
 * Copyright 2013 Tri-Edge AI <triedgeai@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 */

#ifndef _MINEFIELD_VIEW_H_
#define _MINEFIELD_VIEW_H_

#include "defs.h"
#include "Assets.h"
#include "AnimatedSprite.h"
#include "MinesweeperWindow.h"
#include "Audio.h"

#include <View.h>
#include <SimpleGameSound.h>

#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>
using namespace std;

#define	TILE_0				0
#define TILE_1				1
#define	TILE_2				2
#define TILE_3				4
#define TILE_5				5
#define TILE_6				7
#define	TILE_8				8
#define TILE_MINE			9

#define TILE_STATE_NORMAL	0
#define TILE_STATE_OPEN		1
#define TILE_STATE_FLAG		2
#define TILE_STATE_MARK		4

class MinesweeperWindow;

class MinefieldView : public BView
{
public:
	bool					GameOver;
	bool					Victory;
	
							MinefieldView(MinesweeperWindow* parent, 
								uint32 width, uint32 height, uint32 mines);
							~MinefieldView();
					
	void 					ResizeTo(uint32 width, uint32 height, uint32 mines);
	void					Clear();
	void					Populate();
	
	void					Draw(BRect updateRect);
	
	void					MouseMoved(BPoint point, uint32 transit, const BMessage* msg);
	void					MouseDown(BPoint point);
	void					MouseUp(BPoint point);
	
private:
	MinesweeperWindow*		fParent;
	
	uint32 					fWidth;
	uint32 					fHeight;
	uint32 					fMines;
	
	uint32					fMinesHypothetical;
	uint32					fCoveredTiles;
					
	uint32 					fField[30][30];
	uint32					fFieldState[30][30];
	bool					fFirstClick;
	
	uint32					fMouseX;
	uint32					fMouseY;
	uint32					fMouseButtons;
	
	vector<AnimatedSprite*>	fExplosionList;
	uint32					fMinesExploded;
	float					fExplosionRange;
	float					fExplosionOriginX;
	float					fExplosionOriginY;
	
	bigtime_t				fTimeLast;
	bigtime_t				fTimeNow;
	bigtime_t				fTimeDelta;
	
	void					_IncrementTile(uint32 x, uint32 y);
	void					_ToggleState(uint32 x, uint32 y);
	void					_OpenRecursive(uint32 x, uint32 y);
	void					_ChainExplosion();
	void					_FlagTheRest();
};

#endif
