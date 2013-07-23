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
	mPropBox.w = mpTexture->width; mPropBox.h = mpTexture->height/2;
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
	mInsufficient = false;
	mPos = n.GetPoint();
	mPos.x += 48;
	mTar = n.ItemName();
	mpDetail = &d.GetData();
	mTitle = mpDetail->full_name;
	mPrice = std::to_string(mpDetail->price);
	mDmg = ""; mPropBox.h = mpTexture->height/2;
	for (auto it = d.GetData().properties.begin(); it != d.GetData().properties.end(); ++it) {
		mDmg += "+" + std::to_string(it->value) + it->name + "\n";
		mPropBox.h += mpFont->height;
		}
}

void ItemSelector::Draw(SDL_Surface *pDest)
{
	if (mSelection)
	{
		Shared::DrawSurface(mPos.x, mPos.y, mpTexture->pSurface, pDest,
			&mPropBox);
		mpText->draw(mPos.x, mPos.y, mTitle.c_str());
		mpText->draw(mPos.x + 50, mPos.y + 20, mPrice.c_str());
		mpText->draw(mPos.x, mPos.y + 45, mDmg.c_str());
		if (mInsufficient)
			mpText->draw(mPos.x + 150, mPos.y, mInsf.c_str());
	}
}