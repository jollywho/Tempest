#include "Node.h"

Node::Node(NodeData data, ItemDetail* item) :
	mData(data),
	mpItem(item)
{
	mpBorder = IMG_Load("Image/Shop/node.png");
	mPos = Point((WINDOW_WIDTH/2 - SIZE/2) + mData.row * SIZE,
		(SHOP_OFFSET_Y + SIZE/2) + mData.col * SIZE);
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
	Shared::DrawSurface(mPos.x, mPos.y, mpBorder, pDest);
	mpItem->Draw(pDest, mPos);
}

void Node::BranchTo(std::string id)
{

}

