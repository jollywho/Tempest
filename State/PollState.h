#pragma once
#ifndef POLLSTATE_H
#define POLLSTATE_H

#include "gamestate.h"
#include "Engine/Timer.h"
#include <sstream>

class FontInfo;
class NSprite;

class CPollState : public CGameState
{
public:
	void Init();
	void Cleanup();

	void Pause();
	void Resume();

	void KeyInput(const KeyStruct& rKeys);
	void Update(const int& rDeltaTime);
	void Draw(SDL_Surface* pDest);

	static CPollState* Instance() {
		return &mIntroState;
	}
protected:
	CPollState() { }
	struct Tally
	{
		bool visible;
		int value;
		int count;
		int total;
		Point countPoint;
		Point totalPoint;
		std::stringstream countStr;
		std::stringstream totalStr;
	};
	bool TickCounter(Tally& rItem, int counterType, int countLeft);
	void Reset(Tally& rItem);
private:
	static CPollState mIntroState;
	FontInfo* mpFont;
	SDL_Surface* mpBackground;
	int mAlpha;
	Timer mFadeTimer;
	Point banner_middle_pos;
	Point banner_left_pos;
	Point banner_right_pos;

	SDL_Surface* banner_middle;
	SDL_Surface* banner_side;
	float banner_speed;
	bool mExit; 
	bool mEnter; 
	bool mFadeout;
	bool mReady;
	bool mSkip;

	/* Totals */
	Tally mGem;
	Tally mCoin;
	Tally mQuartz;

	/* Sprites */
	NSprite* mpGem;
	NSprite* mpCoin;
	NSprite* mpQuartz;
	NSprite* mpReady;

	/*
	todo:
	1) Increment counter by 10/5/1
	2) Increase score by value
	3) Decrease interface count by counter
	*/
};

#endif