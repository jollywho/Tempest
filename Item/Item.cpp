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
#include "Item.h"
#include "Engine/SpriteResource.h"
#include "State/playstate.h"
#include "UI/Interface.h"
#include "Game/Camera.h"
#include "Player/Player.h"

SDL_Surface* Item::smpPickupFrameInfo;

Item::Item(int x, int y, int value, char* id)
{
	mpInfo = &SpriteResource::RequestResource("Item", id);
    mDelete = false; pickedup = false; received = false;
    val = 25; mClip = 0;
	mX = x - mpInfo->width / 2;
    mY = y - mpInfo->height / 2 - Camera::Instance()->CameraY2();
    mOffset.x = mX;
    mOffset.y = mY;
    mOffset.w = mpInfo->width;
    mOffset.h = mpInfo->height;
	mClipTimer.Start();
	mDurationTimer.Start();
}

Item::~Item() {}

void Item::SetBonus(int val)
{
	
}

void Item::Init()
{
	printf("Item initialize!\n");

	smpPickupFrameInfo = Shared::LoadImage("Image/Item/Receive_Frame.png");
}

void Item::Cleanup()
{
	printf("Item CleanUp!\n");
	SDL_FreeSurface(smpPickupFrameInfo);
}

void Item::CheckCollision()
{
	if (CPlayState::Instance()->mpPlayer->IsExploding())
		return;
    SDL_Rect playerbox = CPlayState::Instance()->mpPlayer->GetOuterBounds().rect;
    int dx = (playerbox.x + playerbox.w / 2) - (mOffset.x - Camera::Instance()->CameraX()  + mOffset.w / 2);
    int dy;
	if (mAir) { dy = (playerbox.y + playerbox.h / 2) - (mOffset.y + mOffset.h / 2);}
	else { dy = (playerbox.y + playerbox.h / 2) - (mOffset.y - Camera::Instance()->CameraY2() + mOffset.h / 2);}
    int radii = playerbox.w / 2 + mOffset.w / 4;
    if ((dx * dx)  + (dy * dy) < radii * radii) 
    {
        pickedup = true;
		if (playerbox.x + playerbox.w / 2 < + GAME_BANNER_WIDTH + GAMESCREEN_WIDTH / 2) mSpawnSide = 1;
		else mSpawnSide = -1;
    }
}

bool Item::CheckOffscreen(double x, double y, double h)
{
	if(y > GAME_BOUNDS_HEIGHT || x - Camera::Instance()->CameraX() < 0 || x - Camera::Instance()->CameraX() > GAME_LEVEL_WIDTH)
		return true;
	else
		return false;
}

void Item::CheckWallCollision(double w, double h)
{
	if (mX < GAME_BANNER_WIDTH)
		xvel *= -1; mX = GAME_BANNER_WIDTH;
	if (mX + w > GAME_LEVEL_WIDTH)
		xvel *= -1; mX = GAME_LEVEL_WIDTH - w;
	if (mY < 0)
		yvel *= -1; mY = 0;
	if (mY + h > GAME_UI_BOTTOM)
		yvel *= -1; mY = GAME_UI_BOTTOM - h;
}