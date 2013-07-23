#pragma once
#ifndef SHOP_H
#define SHOP_H

#include "Engine/Shared.h"
#include <map>
#include <vector>

class Node;
class ItemSelector;
struct NodeData;
struct ItemData;
struct ItemProperty;
class ItemDetail;
class NSprite;

class Shop
{
private:
	std::map<std::pair<int, std::string>, Node*> mTree;
	std::map<std::string, ItemDetail*> mItems;
	ItemSelector* mpSelector;
	int mPage;
	bool mClick; bool mDClick;
	const int MAX_PAGES;
	Timer mClickTimer;
	Point mHover;
	NSprite* mpPageLeft;
	NSprite* mpPageRight;
public:
	Shop(Point& s, Point& e);
	~Shop(){};
	
	Node& FindItem(std::string id);
	ItemDetail& FindDetail(std::string id);
	std::vector<Node*> GetBranches(std::vector<std::string> builds);
	void Purchase(Node& d);
	int ItemCost(Node& n, int money);
	bool IsCollision(Point& p);
	bool IsCollisionR(HitBox& p);
	void ChangePage(int dir);
	void Purchase(std::string id);
	void BranchTo(std::string id);
	void KeyInput(const KeyStruct& rKeys);
	void Update(Uint32 deltaTicks);
	void Draw(SDL_Surface *pDest);
	void ReadItemFile();
	void ReadNodeFile();
};
std::istream& operator >> (std::istream& is, NodeData& data);
std::istream& operator >> (std::istream& is, ItemData& data);
std::istream& operator >> (std::istream& is, ItemProperty& data);

#endif

