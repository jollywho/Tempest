#ifndef ITEMSELECTOR_H
#define ITEMSELECTOR_H

#include "Engine/Shared.h"

struct TextureInfo;
class Node;
class NFont;
class ItemDetail;
struct ItemData;

class ItemSelector
{
private:
	bool mSelection;
	bool mInsufficient;
	SDL_Rect mPropBox;
	TextureInfo* mpTexture;
	TextureInfo* mpFont;
	Point mPos;
	std::string mTar;
	NFont* mpText;
	std::string mInsf;
	std::string mTitle;
	std::string mPrice;
	std::string mDmg;
	ItemData* mpDetail;
public:
    ItemSelector();
    ~ItemSelector();
    ItemSelector AddItem(int x, int y, char* msg);
    void Update(Uint32 deltaTicks);
    void Draw(SDL_Surface *pDest);
	void MoveSelector(Node& n, ItemDetail& d);
	void Reset() { mSelection = false; }
	void Insufficient() { mInsufficient = true; }
	std::string Branch() { return mTar; }
};
 


#endif