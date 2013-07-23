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
	
	void Update(Uint32 deltaTicks);
	void Draw(SDL_Surface *pDest, Point& p);
	std::string& GetName() { return mData.id; }
	unsigned int GetPrice() { return mData.price; }
	ItemData& GetData() { return mData; }
};

#endif

