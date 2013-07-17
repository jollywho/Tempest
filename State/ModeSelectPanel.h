#pragma once
#ifndef MODESELECTPANEL_H
#define MODESELECTPANEL_H

#include "panel.h"

class NSprite;
class Menu;

class ModeSelectPanel : public Panel
{
public:
    ModeSelectPanel();
	~ModeSelectPanel();

	void KeyInput(const KeyStruct& rKeys);
	void Update(const int& rDeltaTime);
	void Draw(SDL_Surface* pDest);
	void DrawTop(SDL_Surface* pDest);
private:
	Panel* mpPanel;
	SDL_Surface* mpTitle;
	NSprite* mpMode;
	Menu* mpMenu;
	Point mMode;
};
 

#endif
