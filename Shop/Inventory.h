#pragma once
#ifndef INVENTORY_H
#define INVENTORY_H

#include "Engine/Shared.h"
#include <map>

class ItemDetail;

class Inventory
{
private:
	static std::map<int, ItemDetail*> mItems;
public:
	static std::map<int, ItemDetail*>& Items() { return mItems; }

};


#endif