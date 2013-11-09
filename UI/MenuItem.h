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
#ifndef MENUITEM_H
#define MENUITEM_H

#include "SDL_ttf.h"
#include "Engine/Timer.h"

class MenuItem
{
private:
	TTF_Font* mpFont;
    SDL_Surface* mpOuterSurface;
    SDL_Surface* mpInnerSurface;
    SDL_Rect mOffset;
    Timer mClipTimer;
    bool selected;
    int prev;
    char* text;
public:
    int index;
    explicit MenuItem(int indx, int x, int y, char& msg, TTF_Font& font);
    ~MenuItem();
    void Move(float x, float y);
    void Update(Uint32 delta_ticks, int mAlpha, int indx);
    void Draw(SDL_Surface *pdest);
    void DrawSurface( int x, int y, SDL_Surface* pSource, SDL_Surface* pdest, SDL_Rect* pClip );
    SDL_Rect GetBounds() { return mOffset; }
};



#endif