#pragma once
#ifndef OPTIONPANEL_H
#define OPTIONPANEL_H

#include "panel.h"

struct SpriteInfo;
class NFont;
class Menu;

class OptionPanel : public Panel
{
public:
	OptionPanel();
	~OptionPanel();

	void KeyInput(const KeyStruct& rKeys);
	void Update(const int& rDeltaTime);
	void Draw(SDL_Surface* pDest);
private:
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