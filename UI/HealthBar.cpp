#include "HealthBar.h"
#include "Engine/SpriteResource.h"
#include "NSprite.h"

HealthBar::HealthBar(std::string id_t, std::string id_s, Point& p, bool draw_border)
{
	mBorder = draw_border;
	mpBorder = &SpriteResource::RequestTextureResource("UI", id_t);
	mpInfo = &SpriteResource::RequestResource("UI", id_s);
	mpMarker = new NSprite(0,0, &SpriteResource::RequestResource("UI", "marker"));
	//mpExplosion = new NSprite(0,0, &SpriteResource::RequestResource("UI", "ui_explosion"), false, false);
	mVal = 0; mClip = 1; mRecRate = 0; mDir = 1;
	p.x == 0 ? p.x = mpBorder->width : 0;
	mPos.x = p.x - mpBorder->width;
	mPos.y = p.y - mpBorder->height;
	mClipTimer.Start();
}
HealthBar::~HealthBar() 
{

}

void HealthBar::Update()
{
	if (mClipTimer.GetTicks() > mpInfo->interval)
	{ 
		if (mClip > 0 && mClip < mpInfo->maxClips-1)
			mClip+=mDir;
		else {
			mDir *= -1; mClip+=mDir; }
		mClipTimer.Start();
	}
	mpMarker->SetPos(Point(mPos.x, mPos.y));
	mpMarker->Update();
}

void HealthBar::Draw(SDL_Surface *pDest) 
{
	Shared::DrawSurface(mPos.x, mPos.y, mpInfo->pSurface, pDest, &mpInfo->pClips[mClip]);
	if (mBorder)
		Shared::DrawSurface(mPos.x, mPos.y, mpBorder->pSurface, pDest);
	
	//mpMarker->Draw(mpBorder->pSurface);
}
