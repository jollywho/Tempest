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
#ifndef ITEMDETAIL_H
#define ITEMDETAIL_H

#include "Engine/Shared.h"
#include <vector>

struct ItemProperty
{
	std::string name;
	unsigned int value;
};

struct ItemData
{
	std::string id;
	std::string full_name;
	int price;
	std::vector<ItemProperty> properties;
};

class ItemDetail
{
private:
	ItemData mData;
	SDL_Surface* mpIcon;
public:
	ItemDetail(ItemData data);
	~ItemDetail();
	void Update(Uint32 delta_ticks);
	void Draw(SDL_Surface *pdest, Point& p);

	std::string& GetName() {return mData.id;}
	unsigned int GetPrice() {return mData.price;}
	ItemData& GetData() {return mData;}
};

#endif

