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
public:
	Node(NodeData data, ItemDetail* item);
	~Node();
	void Update(Uint32 deltaTicks);
	void Draw(SDL_Surface *pDest);
	void SetEnable(bool enable) { mEnable = enable; }
	void Click(bool state) { mClick = state; }
	unsigned int GetPrice() { return mpItem->GetPrice(); }
	void SetPaths(std::vector<Line*>& lines) { mPaths = lines; }
	Point& GetTPoint() { return Point(mData.col, mData.row); }
	Point& GetPoint() { return mPos; }
	bool HasBranched() { return mBranched; }
	bool IsClick() { return mClick; }
	bool IsEnabled() { return mEnable; }
	std::vector<std::string>& GetRequirements() { return mData.req; }
	std::vector<std::string>& GetBuilds() { return mData.build; }
	std::string ItemName() { return mpItem->GetName(); }
};


#endif

