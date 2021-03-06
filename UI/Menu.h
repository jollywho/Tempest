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
��*  Kevin Vollmer <works.kvollmer@gmail.com>
*
*/
#ifndef MENU_H
#define MENU_H

#include "Engine/Shared.h"
#include "SDL_ttf.h"
#include <vector>

struct SpriteInfo;
class MenuItem;

class Menu
{
public:
    Menu();
    ~Menu();
    void AddItem(int x, int y, char* msg);
    void Update(Uint32 delta_ticks, int mAlpha);
    void Draw(SDL_Surface *pdest);
	void Reset();
	void Select();
	void MoveIndex(int direction);
	void Menu::SetIndex(int index);

	int GetIndex() {return mSelectedindex;}
	int Count() {return mMaxItems;}
	Point GetFontSize(char& msg);
private:
    std::vector<MenuItem*> menuList;
    int mMaxItems;
    Point mSelector;
	TTF_Font* mpFont;
	int mSelectedindex;
	SpriteInfo* mpInfo;
	Timer mClipTimer;
	int mClip;
	bool mClick;
	void MoveSelector(SDL_Rect& bounds);
};

#endif