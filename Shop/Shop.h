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
	NSprite* mpPageleft;
	NSprite* mpPageright;
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
	void KeyInput(const SDL_Event& rEvent);
	void Update(Uint32 delta_ticks);
	void Draw(SDL_Surface *pdest);
	void ReadItemFile();
	void ReadNodeFile();
};
std::istream& operator >> (std::istream& is, NodeData& data);
std::istream& operator >> (std::istream& is, ItemData& data);
std::istream& operator >> (std::istream& is, ItemProperty& data);

#endif

