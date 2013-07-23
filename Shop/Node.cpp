#include "Node.h"
#include "Shop.h"
#include "Line.h"
#include "Engine/SpriteResource.h"

Node::Node(NodeData data, ItemDetail* item) :
	mData(data),
	mpItem(item)
{
	mEnable = false;
	mBranched = false;
	mClick = false;
	mpBorder = &SpriteResource::RequestTextureResource("Shop", "node");
	mPos = Point((WINDOW_WIDTH/2 - SIZE/2) + mData.col * SIZE,
		(SHOP_OFFSET_Y + SIZE/2) + mData.row * SIZE);
}

Node::~Node()
{
	delete mpBorder;
}

void Node::Update(Uint32 deltaTicks)
{

}
void Node::Draw(SDL_Surface *pDest)
{
	if (mEnable)
	{
		Shared::DrawSurface(mPos.x, mPos.y, mpBorder->pSurface, pDest);
		for (auto it=mPaths.begin(); it != mPaths.end(); ++it)
			(*it)->Draw(pDest);
		mpItem->Draw(pDest, mPos);
	}
}