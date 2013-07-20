#pragma once
#ifndef NODE_H
#define NODE_H

#include "Engine/Shared.h"
#include <vector>
#include "ItemDetail.h"

class Line;
class ItemDetail;


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
private:
	NodeData mData;
	ItemDetail* mpItem;
	SDL_Surface* mpBorder;
	std::vector<Line*> mPaths;
	bool mEnable;
	Point mPos;
	static const int SIZE = 48;
public:
	Node(NodeData data, ItemDetail* item);
	~Node();
	void Update(Uint32 deltaTicks);
	void Draw(SDL_Surface *pDest);
	void BranchTo(std::string id);
	void SetEnable(bool enable) { mEnable = enable; }
	unsigned int GetPrice() { return mpItem->GetPrice(); }
	Point& GetTPoint() { return Point(mData.row, mData.col); }
	std::vector<std::string>& GetRequirements() { return mData.req; }
};


#endif

