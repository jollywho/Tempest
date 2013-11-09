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
#include "Inventory.h"
#include "ItemDetail.h"
#include "Engine/SpriteResource.h"

std::map<int, ItemDetail*> Inventory::mItems;
int Inventory::mMoney;

Inventory::Inventory()
{
	/*
	Point origin = Point(WINDOW_WIDTH/2 - mpItem->width/2, 
		WINDOW_HEIGHT - mpBorder->height);

	for (int i=0; i< INV_SIZE; ++i)
		mpPoints[i] = Point(origin.x + (mpItem->width * i), origin.y);

	*/
}

Inventory::~Inventory()
{
	//delete mpItem;
}

bool Inventory::AddItem(ItemDetail& d)
{
	auto it = mItems.end();
	if (it->first < INV_SIZE) {
		mItems.insert(std::make_pair(it->first+1, new ItemDetail(d)));
		return true;
		}
	else
		return false;
}

void Inventory::Update(Uint32 delta_ticks)
{
	
}

void Inventory::Draw(SDL_Surface *pdest)
{
	int i = 0;
	for (auto it = mItems.begin(); it != mItems.end(); ++it, ++i)
	{
		it->second->Draw(pdest, mpPoints[i]);
	}
}