#pragma once
#ifndef INVENTORY_H
#define INVENTORY_H

#include "Engine/Shared.h"
#include <map>

class ItemDetail;
struct TextureInfo;

class Inventory
{
private:
	static std::map<int, ItemDetail*> mItems;
	static const int INV_SIZE = 4;
	Point mpPoints[INV_SIZE];
	static int mMoney;
public:
	Inventory();
	~Inventory();
	static bool AddItem(ItemDetail& d);
	static int& GetMoney() { return mMoney; }
	static bool SpendMoney(int price)
		{ if (mMoney >= price) { mMoney -= price; return true; } else { return false; }}
	static std::map<int, ItemDetail*>& Items() { return mItems; }
	void Update(Uint32 deltaTicks);
	void Draw(SDL_Surface *pDest);
};


#endif