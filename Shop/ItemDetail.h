#pragma once
#ifndef ITEMDETAIL_H
#define ITEMDETAIL_H

#include "Engine/Shared.h"

struct ItemData
{
	std::string id;
	unsigned int atk; 			//000
	unsigned int mag;			//000
	unsigned int hp;			//0000
	unsigned int range;			//000
	unsigned int wind;			//00%
	unsigned int atkSpd;		//00%
	unsigned int price;			//000
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
};
std::istream& operator >> (std::istream& is, ItemData& data);

#endif

