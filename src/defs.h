/*
 * Copyright 2013 Tri-Edge AI <triedgeai@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 */

#ifndef _DEFS_H_
#define _DEFS_H_

#define RECT_0				BRect(0, 0, 0, 0)

#define MSG_TICK			'mTIK'
#define MSG_NEW				'mNEW'
#define MSG_HIGHSCORE		'mHSC'
#define MSG_SIZE			'mSIZ'
#define MSG_BEGINNER		'mBGR'
#define MSG_INTERMEDIATE	'mINR'
#define MSG_EXPERT			'mEXR'
#define MSG_CUSTOM			'mCSM'
#define MSG_CUSTOM_SET		'mCSS'
#define MSG_SOUND			'mSND'
#define MSG_QUIT			'mQUT'
#define MSG_HOWTOPLAY		'mHTP'
#define MSG_ABOUT			'mABT'
#define MSG_ACCEPT			'mACC'
#define MSG_CANCEL			'mCNL'
#define MSG_WIDTH			'mWDT'
#define MSG_HEIGHT			'mHGT'
#define MSG_MINES			'mMNS'
#define MSG_SHOW			'mSHW'
#define MSG_FACE			'mFAC'
#define MSG_VICTORY			'mVIC'
#define MSG_NAME			'mNAM'
#define MSG_SUBMIT			'mSBM'

#define M(x)				new BMessage(x)

#endif
