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
}

ItemSelector::~ItemSelector()
{
    printf("ItemSelector Delete\n");
	delete mpTexture;
	delete mpFont;
}

void ItemSelector::Update(Uint32 deltaTicks)
{

}

void ItemSelector::MoveSelector(Node& n, ItemDetail& d)
{
	mSelection = true;
	mPos = n.GetPoint();
	mPos.x += 48;
	mTar = n.ItemName();
	mpDetail = &d.GetData();
	mTitle = mpDetail->full_name;
	mPrice = std::to_string(mpDetail->price);
	mDmg = "+" + std::to_string(mpDetail->atk) + " Attack\n+" + std::to_string(mpDetail->mag) + " Magic";
}

void ItemSelector::Draw(SDL_Surface *pDest)
{
	if (mSelection)
	{
		Shared::DrawSurface(mPos.x, mPos.y, mpTexture->pSurface, pDest);
		mpText->draw(mPos.x, mPos.y, mTitle.c_str());
		mpText->draw(mPos.x + 50, mPos.y + 20, mPrice.c_str());
		mpText->draw(mPos.x, mPos.y + 45, mDmg.c_str());
	}
}