#pragma once
#ifndef SHOP_H
#define SHOP_H

#include "Engine/Shared.h"
#include <map>

class Node;
class ItemSelector;
struct NodeData;
struct ItemData;
class ItemDetail;

class Shop
{
private:
	std::map<std::pair<int, std::string>, Node*> mTree;
	std::map<std::string, ItemDetail*> mItems;
	ItemSelector* mpSelector;
	int mPage;
public:
	Shop();
	~Shop(){};
	
	Node& FindItem(std::string id);
	bool CanPurchase(std::string id);
	
	void Purchase(std::string id);
	
	void KeyInput(const KeyStruct& rKeys);
	void Update(Uint32 deltaTicks);
	void Draw(SDL_Surface *pDest);
	void ReadItemFile();
	void ReadNodeFile();
};
std::istream& operator >> (std::istream& is, NodeData& data);
std::istream& operator >> (std::istream& is, ItemData& data);

#endif

