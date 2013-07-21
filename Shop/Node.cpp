#include "Node.h"
#include "Shop.h"
#include "Line.h"

Node::Node(NodeData data, ItemDetail* item) :
	mData(data),
	mpItem(item)
{
	mEnable = false;
	mpBorder = IMG_Load("Image/Shop/node.png");
	mPos = Point((WINDOW_WIDTH/2 - SIZE/2) + mData.col * SIZE,
		(SHOP_OFFSET_Y + SIZE/2) + mData.row * SIZE);
}

Node::~Node()
{
	SDL_FreeSurface(mpBorder);
}

void Node::Update(Uint32 deltaTicks)
{

}
void Node::Draw(SDL_Surface *pDest)
{
	if (mEnable)
	{
	Shared::DrawSurface(mPos.x, mPos.y, mpBorder, pDest);
	for (auto it=mPaths.begin(); it != mPaths.end(); ++it)
		(*it)->Draw(pDest);
	mpItem->Draw(pDest, mPos);
	}
}