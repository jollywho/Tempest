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
#ifndef INVENTORY_H
#define INVENTORY_H

#include "Engine/Shared.h"
#include <map>

class ItemDetail;
struct TextureInfo;

class Inventory
{
public:
	Inventory();
	~Inventory();
	void Update(Uint32 delta_ticks);
	void Draw(SDL_Surface *pdest);

	static bool SpendMoney(int price)
	{
			if (mMoney >= price) 
			{
				mMoney -= price;
				return true;}
			else 
				return false;
	}
	static bool AddItem(ItemDetail& d);
	static int& GetMoney() {return mMoney;}
	static std::map<int, ItemDetail*>& Items() {return mItems;}
private:
	static std::map<int, ItemDetail*> mItems;
	static const int INV_SIZE = 4;
	Point mpPoints[INV_SIZE];
	static int mMoney;
};


#endif