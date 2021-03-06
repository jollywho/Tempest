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
��*  Kevin Vollmer <works.kvollmer@gmail.com>
*
*/
#pragma once
#ifndef NODE_H
#define NODE_H

#include "Engine/Shared.h"
#include <vector>
#include "ItemDetail.h"

class Line;
class ItemDetail;
struct TextureInfo;

struct NodeData
{
	int page;
	std::string id;
	int row;
	int col;
	int price;
	std::vector<std::string> req;
	std::vector<std::string> build;
};

class Node
{
public:
	Node(NodeData data, ItemDetail* item);
	~Node();
	void Update(Uint32 delta_ticks);
	void Draw(SDL_Surface *pdest);
	void SetEnable(bool enable) { mEnable = enable;}
	void Click(bool state) { mClick = state;}
	void SetPaths(std::vector<Line*>& lines) { mPaths = lines;}

	unsigned int GetPrice() {return mpItem->GetPrice();}
	Point& GetTPoint() {return Point(mData.col, mData.row);}
	Point& GetPoint() {return mPos;}
	bool HasBranched() {return mBranched;}
	bool IsClick() {return mClick;}
	bool IsEnabled() {return mEnable;}
	std::vector<std::string>& GetRequirements() {return mData.req;}
	std::vector<std::string>& GetBuilds() {return mData.build;}
	std::string ItemName() {return mpItem->GetName();}
private:
	NodeData mData;
	ItemDetail* mpItem;
	TextureInfo* mpBorder;
	std::vector<Line*> mPaths;
	bool mEnable;
	bool mBranched;
	bool mClick;
	Point mPos;
	static const int SIZE = 48;
};

#endif

