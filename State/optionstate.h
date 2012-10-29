#pragma once
#ifndef OPTIONSTATE_H
#define OPTIONSTATE_H

#include "Gamestate.h"
#include <sstream>

struct SpriteInfo;
class NFont;
class Menu;

class COptionState : public CGameState
{
public:
	void Init();
	void Cleanup();

	void Pause(){}
	void Resume(){}
	void Back(){}

	void KeyInput(const KeyStruct& rKeys);
	void Update(const int& rDeltaTime);
	void Draw(SDL_Surface* pDest);

	static COptionState* Instance() {
		return &mOptionState;
	}
protected:
	COptionState() { }

private:
	static COptionState mOptionState;
	static const int FRAME_WIDTH = 256;
	static const int FRAME_HEIGHT = 20;
	static const int SELECTOR_WIDTH = 18;
	static const int SELECTOR_HEIGHT = 32;

	NFont* mpFont;
	Menu* mpMenu;
	
	SDL_Surface* mpFontSurface;
	SDL_Surface* mpSelector;
	SDL_Surface* mpFrame;

	int mAlignX;
	Point mSfxFrame;
	Point mSfxSelector;
	Point mBgmFrame;
	Point mBgmSelector;
};

#endif