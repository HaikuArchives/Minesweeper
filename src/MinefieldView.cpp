/*
 * Copyright 2013 Tri-Edge AI <triedgeai@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 */

#include "MinefieldView.h"

MinefieldView::MinefieldView(MinesweeperWindow* parent, uint32 width,
	uint32 height, uint32 mines)
	:
	BView(BRect(3, 3, width * 24 + 3, height * 24 + 3), "MinefieldView",
		B_FOLLOW_NONE, B_WILL_DRAW)
{
	fParent = parent;

	fWidth = width;
	fHeight = height;
	fMines = mines;

	SetDrawingMode(B_OP_ALPHA);

	Clear();
}


MinefieldView::~MinefieldView()
{

}


void
MinefieldView::ResizeTo(uint32 width, uint32 height, uint32 mines)
{
	BView::ResizeTo(width * 24, height * 24);
	fWidth = width;
	fHeight = height;
	fMines = mines;

	Clear();
}


void
MinefieldView::Clear()
{
	for (uint32 i = 0; i < fExplosionList.size(); i++)
		delete fExplosionList[i];

	fExplosionList.clear();

	for (uint32 y = 0; y < fHeight; y++)
		for (uint32 x = 0; x < fWidth; x++) {
			fField[x][y] = 0;
			fFieldState[x][y] = TILE_STATE_NORMAL;
		}

	fFirstClick = true;

	GameOver = false;
	Victory = false;

	fMinesHypothetical = fMines;
	fCoveredTiles = fWidth * fHeight;

	fParent->MineCounter->Set(fMinesHypothetical);
	fParent->TimeCounter->Set(0);

	fParent->FaceButton->SetBitmap(Assets.gfx.face.happy);

	Audio.PlaySound(Assets.sfx.start);

	Invalidate();
}


void
MinefieldView::Populate()
{
	vector<BPoint> tilePool;

	for (uint32 y = 0; y < fHeight; y++)
		for (uint32 x = 0; x < fWidth; x++)
			if (fFieldState[x][y] != TILE_STATE_OPEN)
				tilePool.push_back(BPoint(x, y));

	for(uint32 i = 0; i < fMines; i++) {
		uint32 ix = rand() % tilePool.size();
		uint32 x = (uint32)tilePool[ix].x;
		uint32 y = (uint32)tilePool[ix].y;

		fField[x][y] = TILE_MINE;

		tilePool.erase(tilePool.begin() + ix);

		_IncrementTile(x - 1,	y - 1);
		_IncrementTile(x,		y - 1);
		_IncrementTile(x + 1,	y - 1);
		_IncrementTile(x - 1,	y);
		_IncrementTile(x + 1,	y);
		_IncrementTile(x - 1,	y + 1);
		_IncrementTile(x,		y + 1);
		_IncrementTile(x + 1,	y + 1);
	}

	Invalidate();
}


void
MinefieldView::Draw(BRect updateRect)
{
	fTimeLast = fTimeNow;
	fTimeNow = system_time();
	fTimeDelta = fTimeNow - fTimeLast;

	BPoint point(0, 0);

	for (uint32 y = 0; y < fHeight; y++) {
		point.x = 0;

		for (uint32 x = 0; x < fWidth; x++) {
			if (fFieldState[x][y] == TILE_STATE_FLAG) {
				if ((GameOver || Victory) && fField[x][y] == TILE_MINE)
					DrawBitmap(Assets.gfx.flagmine, point);
				else
					DrawBitmap(Assets.gfx.flag, point);
			} else if (fFieldState[x][y] == TILE_STATE_MARK)
				DrawBitmap(Assets.gfx.mark, point);
			else if (fFieldState[x][y] == TILE_STATE_OPEN) {
				if (fField[x][y] == TILE_MINE)
					DrawBitmap(Assets.gfx.redmine, point);
				else if (x == fExplosionOriginX && y == fExplosionOriginY
					&& GameOver)
					DrawBitmap(Assets.gfx.red, point);
				else
					DrawBitmap(Assets.gfx.signs[fField[x][y]], point);
			} else if (GameOver && fField[x][y] == TILE_MINE)
				DrawBitmap(Assets.gfx.mine, point);
			else
				DrawBitmap(Assets.gfx.button, point);

			point.x += 24;
		}

		point.y += 24;
	}

	if (!GameOver) {
		if (!Victory) {
			if (fMouseButtons)
				DrawBitmap(Assets.gfx.press, BPoint(fMouseX * 24, fMouseY * 24));
			else
				DrawBitmap(Assets.gfx.hover, BPoint(fMouseX * 24, fMouseY * 24));
		}
	} else {
		bool shouldInvalidate = fExplosionList.size() > 0;

		for (uint32 i = 0; i < fExplosionList.size(); i++) {
			BBitmap* frame = fExplosionList[i]->GetFrame(fTimeDelta);

			if (frame != NULL)
				DrawBitmap(frame, fExplosionList[i]->Point);
			else {
				delete frame;
				fExplosionList.erase(fExplosionList.begin() + i);
				i--;
			}
		}

		if (fMinesExploded < fMines || shouldInvalidate) {
			_ChainExplosion();

			snooze(50 * 1000);
			Invalidate();
		}
	}
}


void
MinefieldView::MouseMoved(BPoint point, uint32 transit, const BMessage* msg)
{
	uint32 newMouseX = (uint32)point.x / 24;
	uint32 newMouseY = (uint32)point.y / 24;

	if (newMouseX != fMouseX || newMouseY != fMouseY) {
		fMouseX = (uint32)point.x / 24;
		fMouseY = (uint32)point.y / 24;

		Invalidate();
	}
}


void
MinefieldView::MouseDown(BPoint point)
{
	if (!GameOver && !Victory) {
		fMouseX = (uint32)point.x / 24;
		fMouseY = (uint32)point.y / 24;
		GetMouse(&point, &fMouseButtons);

		if (fMouseButtons & B_PRIMARY_MOUSE_BUTTON == B_PRIMARY_MOUSE_BUTTON)
			fParent->FaceButton->SetBitmap(Assets.gfx.face.oh);

		Invalidate();
	}
}


void
MinefieldView::MouseUp(BPoint point)
{
	if(!GameOver && !Victory) {
		uint32 x = (uint32)point.x / 24;
		uint32 y = (uint32)point.y / 24;

		if (fMouseButtons & B_PRIMARY_MOUSE_BUTTON == B_PRIMARY_MOUSE_BUTTON) {
			Audio.PlaySound(Assets.sfx.click);
			_OpenRecursive(x, y);

			if (GameOver)
				fParent->FaceButton->SetBitmap(Assets.gfx.face.defeat);
			else if (Victory) {
				Audio.PlaySound(Assets.sfx.victory);
				fParent->FaceButton->SetBitmap(Assets.gfx.face.victory);
				fParent->PostMessage(MSG_VICTORY);
				_FlagTheRest();
			} else
				fParent->FaceButton->SetBitmap(Assets.gfx.face.happy);
		} else {
			if (fFieldState[x][y] == TILE_STATE_NORMAL) {
				fFieldState[x][y] = TILE_STATE_FLAG;
				fMinesHypothetical--;
				fParent->MineCounter->Set(fMinesHypothetical);
			} else if (fFieldState[x][y] == TILE_STATE_FLAG) {
				fFieldState[x][y] = TILE_STATE_MARK;
				fMinesHypothetical++;
				fParent->MineCounter->Set(fMinesHypothetical);
			} else if (fFieldState[x][y] == TILE_STATE_MARK)
				fFieldState[x][y] = TILE_STATE_NORMAL;
		}
	}

	Invalidate();
}


void
MinefieldView::_IncrementTile(uint32 x, uint32 y)
{
	if (x >= fWidth || y >= fHeight)
		return;

	if (fField[x][y] == TILE_MINE)
		return;

	fField[x][y]++;
}


void
MinefieldView::_OpenRecursive(uint32 x, uint32 y)
{
	if(x >= fWidth || y >= fHeight)
		return;

	if (fFieldState[x][y] == TILE_STATE_OPEN ||
		fFieldState[x][y] == TILE_STATE_FLAG)
		return;

	fFieldState[x][y] = TILE_STATE_OPEN;

	if (fFirstClick) {
		fFirstClick = false;
		Populate();
	}

	if(fField[x][y] == TILE_MINE) {
		GameOver = true;
		fMinesExploded = 0;
		fExplosionRange = -1.0f;
		fExplosionOriginX = x;
		fExplosionOriginY = y;
	} else {
		fCoveredTiles--;

		if (fCoveredTiles <= fMines) {
			Victory = true;
		} else if (fField[x][y] == 0) {
			_OpenRecursive(x - 1,	y - 1);
			_OpenRecursive(x,		y - 1);
			_OpenRecursive(x + 1,	y - 1);
			_OpenRecursive(x - 1,	y);
			_OpenRecursive(x + 1,	y);
			_OpenRecursive(x - 1,	y + 1);
			_OpenRecursive(x,		y + 1);
			_OpenRecursive(x + 1,	y + 1);
		}
	}
}


void
MinefieldView::_ChainExplosion()
{
	float dx;
	float dy;
	float d2;

	fExplosionRange += 0.1f;

	if (fExplosionRange <= 0.0f)
		return;

	for (uint32 y = 0; y < fHeight; y++) {
		for (uint32 x = 0; x < fWidth; x++) {
			if (fField[x][y] == TILE_MINE) {
				dx = (float)x - fExplosionOriginX;
				dy = (float)y - fExplosionOriginY;
				d2 = dx * dx + dy * dy;

				if (d2 < fExplosionRange * fExplosionRange) {
					fField[x][y] = 0;
					fMinesExploded++;
					fExplosionList.push_back(
							new AnimatedSprite(
								BPoint(x * 24 + 12, y * 24 + 12),
								Assets.gfx.boom, 5, 500 * (1000)));
					Audio.PlaySound(Assets.sfx.boom);
				}
			}
		}
	}
}


void
MinefieldView::_FlagTheRest()
{
	for (uint32 y = 0; y < fHeight; y++)
		for (uint32 x = 0; x < fWidth; x++)
			if (fFieldState[x][y] == TILE_STATE_NORMAL)
				fFieldState[x][y] = TILE_STATE_FLAG;
}
