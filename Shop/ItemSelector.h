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
#ifndef ITEMSELECTOR_H
#define ITEMSELECTOR_H

#include "Engine/Shared.h"

struct TextureInfo;
class Node;
class NFont;
class ItemDetail;
struct ItemData;

class ItemSelector
{
public:
    ItemSelector();
    ~ItemSelector();  
    void Update(Uint32 delta_ticks);
    void Draw(SDL_Surface *pdest);
	void MoveSelector(Node& n, ItemDetail& d);
	void Reset() {mSelection = false;}
	void Insufficient() {mInsufficient = true;}

	std::string Branch() {return mTar;}
	ItemSelector AddItem(int x, int y, char* msg);
private:
	bool mSelection;
	bool mInsufficient;
	SDL_Rect mPropBox;
	TextureInfo* mpTexture;
	TextureInfo* mpFont;
	Point mPos;
	std::string mTar;
	NFont* mpText;
	std::string mInsf;
	std::string mTitle;
	std::string mPrice;
	std::string mDmg;
	ItemData* mpDetail;
};

#endif