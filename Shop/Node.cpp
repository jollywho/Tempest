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
#include "Node.h"
#include "Shop.h"
#include "Line.h"
#include "Engine/SpriteResource.h"

Node::Node(NodeData data, ItemDetail* item) :
	mData(data),
	mpItem(item)
{
	mEnable = false;
	mBranched = false;
	mClick = false;
	mpBorder = &SpriteResource::RequestTextureResource("Shop", "node");
	mPos = Point((WINDOW_WIDTH/2 - SIZE/2) + mData.col * SIZE,
		(SHOP_OFFSET_Y + SIZE/2) + mData.row * SIZE);
}

Node::~Node()
{
	delete mpBorder;
}

void Node::Update(Uint32 delta_ticks)
{

}
void Node::Draw(SDL_Surface *pdest)
{
	if (mEnable)
	{
		Shared::DrawSurface(mPos.x, mPos.y, mpBorder->pSurface, pdest);
		for (auto it=mPaths.begin(); it != mPaths.end(); ++it)
			(*it)->Draw(pdest);
		mpItem->Draw(pdest, mPos);
	}
}