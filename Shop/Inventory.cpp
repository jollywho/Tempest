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

void Inventory::Update(Uint32 deltaTicks)
{
	
}

void Inventory::Draw(SDL_Surface *pDest)
{
	int i = 0;
	for (auto it = mItems.begin(); it != mItems.end(); ++it, ++i)
	{
		it->second->Draw(pDest, mpPoints[i]);
	}
}