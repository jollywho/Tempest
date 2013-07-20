#include "ItemDetail.h"

ItemDetail::ItemDetail(ItemData data) :
	mData(data)
{
	std::string path = "Image/Shop/";
	path = path + data.id + ".png";
	mpIcon = IMG_Load(path.c_str());
}

ItemDetail::~ItemDetail()
{
	SDL_FreeSurface(mpIcon);
}

void ItemDetail::Draw(SDL_Surface *pDest, Point& p)
{
	Shared::DrawSurface(p.x + 5, p.y + 5, mpIcon, pDest);
}