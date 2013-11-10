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
#include "ItemSelector.h"
#include <locale>
#include "Engine/SpriteResource.h"
#include "Node.h"
#include "ItemDetail.h"
#include "Engine/NFont.h"

ItemSelector::ItemSelector()
{
	printf("ItemSelector Create\n");
	mpTexture = &SpriteResource::RequestTextureResource("Shop", "detail");
	mpFont = &SpriteResource::RequestTextureResource("Shop", "blue_font");
	mpText = new NFont(SDL_GetVideoSurface(), mpFont->pSurface);
	mInsf = "I f\nn u\ns n\nu d\nf s\nf\ni\nc\ni\ne\nn\nt";
	mPropBox.x = 0; mPropBox.y = 0;
	mPropBox.w = mpTexture->width; mPropBox.h = mpTexture->height / 2;
}

ItemSelector::~ItemSelector()
{
    printf("ItemSelector Delete\n");
	delete mpTexture;
	delete mpFont;
}

void ItemSelector::Update(Uint32 delta_ticks)
{

}

void ItemSelector::MoveSelector(Node& n, ItemDetail& d)
{
	mSelection = true;
	mInsufficient = false;
	mPos = n.GetPoint();
	mPos.x += 48;
	mTar = n.ItemName();
	mpDetail = &d.GetData();
	mTitle = mpDetail->full_name;
	mPrice = std::to_string(mpDetail->price);
	mDmg = ""; mPropBox.h = mpTexture->height / 2;
	for (auto it = d.GetData().properties.begin(); it != d.GetData().properties.end(); ++it) {
		mDmg += "+" + std::to_string(it->value) + it->name + "\n";
		mPropBox.h += mpFont->height;
		}
}

void ItemSelector::Draw(SDL_Surface *pdest)
{
	if (mSelection)
	{
		Shared::DrawSurface(mPos.x, mPos.y, mpTexture->pSurface, pdest,
			&mPropBox);
		mpText->draw(mPos.x, mPos.y, mTitle.c_str());
		mpText->draw(mPos.x + 50, mPos.y + 20, mPrice.c_str());
		mpText->draw(mPos.x, mPos.y + 45, mDmg.c_str());
		if (mInsufficient)
			mpText->draw(mPos.x + 150, mPos.y, mInsf.c_str());
	}
}