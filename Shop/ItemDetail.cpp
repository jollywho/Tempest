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
#include "ItemDetail.h"

ItemDetail::ItemDetail(ItemData data) :
	mData(data)
{
	std::string path = "Image/Shop/";
	path = path + data.id + ".png";
	mpIcon = IMG_Load(path.c_str());
}

ItemDetail::~ItemDetail()
{
	SDL_FreeSurface(mpIcon);
}

void ItemDetail::Draw(SDL_Surface *pdest, Point& p)
{
	Shared::DrawSurface(p.x + 6, p.y + 5, mpIcon, pdest);
}