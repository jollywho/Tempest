/* Tempest - C++ Danmakufu Game for SDL
*
*  Copyright (C) 2013 Kevin Vollmer.
*  
*  This program is free software; you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation; either version 2 of the License, or
*  (at your option) any later version.
*  
*  This program is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*  
*  You should have received a copy of the GNU General Public License along
*  with this program; if not, write to the Free Software Foundation, Inc.,
*  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*  
ÅÅ*  Kevin Vollmer <works.kvollmer@gmail.com>
*
*/
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
	void KeyInput(const SDL_Event& rEvent);
	void Update(const int& rDeltaTime);
	void Draw(SDL_Surface* pdest);
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