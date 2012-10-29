#include "Player.h"
#include "Engine/SpriteResource.h"
#include "State/playstate.h"
#include "Weapon/MType.h"

Bomb* Player::mspBomb;
Weapon* Player::mspWpn;

void Player::ReSpawn()
{
	//todo: invuln wings
	//todo: spawn offscreen and move upward
	mExplode = false;
}

Player::Player() 
{
	printf("Player Created\n");
	SpriteResource::AddResource("Player", "Angel.png", 64, 64, 120, 4);
	SpriteResource::AddResource("Player", "Hitbox.png", 20, 20, 60, 8);
	SpriteResource::AddResource("Player", "Booster.png", 38, 38, 60, 5);
	SpriteResource::AddResource("Player", "Zone.png", 120, 120, 60, 4);

	mpAngel = &SpriteResource::RequestResource("Player", "Angel.png");
	mpHitbox = &SpriteResource::RequestResource("Player", "Hitbox.png");
	mpBooster = &SpriteResource::RequestResource("Player", "Booster.png");
	mpZone = &SpriteResource::RequestResource("Player", "Zone.png");

	mClip = 0; mZoneClip = 0; mHitboxClip = 0; mBoosterClip = 0;

	mSpeed = SPEED_NORMAL;
    mov = 0;
	left = 0; right = 0; up = 0; down = 0;
	mShift = false; mAttack = false; mBomb = false;
    mZoneTimer.Start();
    mHitboxTimer.Start();
    mBoosterTimer.Start();
	mClipTimer.Start();

    mX = GAME_LEVEL_WIDTH/2 + 192/2;
    mY = GAME_BOUNDS_HEIGHT/2 + 192/4;

	SetWeaponType(M_type);

	ReSpawn();
}

void Player::SetWeaponType(WeaponType type)
{
	if (type == M_type)mspWpn = new MType();

	mspBomb = new Bomb();
}

void Player::WeaponLevelUp()
{
	mspWpn->LevelUp();
}

Player::~Player()
{
	printf("Player Deleted\n");
	SpriteResource::ClearResourceDir("Player");
}

void Player::KeyInput(const KeyStruct& rKeys)
{
	if (rKeys.up) up = -1;
	else up = 0;
	if (rKeys.down) down = 1;
	else down = 0;
	if (rKeys.left) left = -1;
	else left = 0;
	if (rKeys.right) right = 1;
	else right = 0;
	if (rKeys.shift) mShift = true;
	else mShift = false;
	if (rKeys.z) mAttack = true;
	else mAttack = false;
	if (rKeys.x) mBomb = true;
	else mBomb = false;
}

void Player::HandleMovement(const int& rDeltaTime)
{
	if (mShift && mSpeed > SPEED_SLOW) mSpeed-=rDeltaTime;
	if (!mShift && mSpeed < SPEED_NORMAL) mSpeed+=rDeltaTime;

	float vx = left + right; float vy = up + down;
	float length = sqrtf((vx * vx) + (vy * vy));
	if (length>0.0f)
	{
		vx=(left+right)/length;
		vy=(up+down)/length;
	}
	mX += (vx * mSpeed) * (rDeltaTime/1000.f);
	mY += (vy * mSpeed) * (rDeltaTime/1000.f);

	if (mX < GAME_BANNER_WIDTH) mX = GAME_BANNER_WIDTH;
	if (mX + mpAngel->width > GAME_BOUNDS_WIDTH) mX = GAME_BOUNDS_WIDTH - mpAngel->width;
	if (mY < GAME_UI_TOP) mY = GAME_UI_TOP;
	if (mY + mpAngel->height > GAME_UI_BOTTOM) mY = GAME_UI_BOTTOM - mpAngel->height;
}

void Player::HandleAttacks(const int& rDeltaTime)
{
	mspWpn->SetPos(mX + mpAngel->width/2, mY, 0);
	if (mAttack)
	{
		if (mShift)	mspWpn->MajorAttack(CPlayState::Instance()->pl_bulletlist);
		else		mspWpn->MinorAttack(CPlayState::Instance()->pl_bulletlist);
	}
	else
		mspWpn->StopAttack();

	if (mShift)mspWpn->Shift();
	else mspWpn->Unshift();

	if (mBomb && !mspBomb->IsActive()) mspBomb->Start(mX + mpAngel->width/2, mY);

	mspWpn->Update(rDeltaTime);
	mspBomb->Update(rDeltaTime);
}

void Player::Update(const int& rDeltaTime)
{
	Shared::CheckClip(mClipTimer, mClip, mpAngel->interval, mpAngel->maxClips, 0);
	Shared::CheckClip(mBoosterTimer, mBoosterClip, mpBooster->interval, mpBooster->maxClips, 0);
	Shared::CheckClip(mHitboxTimer, mHitboxClip, mpHitbox->interval, mpHitbox->maxClips, 0);
	Shared::CheckClip(mZoneTimer, mZoneClip, mpZone->interval, mpZone->maxClips, 0);


	HandleMovement(rDeltaTime);
	mBooster.x = mX + mpAngel->width/2 - mpBooster->width/2;
	mBooster.y = mY + mpAngel->height - mpBooster->height/2;
	mHitbox.x = mX + mpAngel->width/2 - mpHitbox->width/2;
	mHitbox.y = mY + mpAngel->height - mpHitbox->height*2;
	mZone.x = mX + mpAngel->width/2 - mpZone->width/2;
	mZone.y = mY + mpAngel->height/2 - mpZone->height/2;

	HandleAttacks(rDeltaTime);
}

void Player::Draw(SDL_Surface *pDest)
{
	//move to separate function for draw order?
	if (mShift)
		Shared::DrawSurface(mZone.x, mZone.y, mpZone->pSurface, pDest, &mpZone->pClips[mZoneClip]);
	mspWpn->Draw(pDest);
	mspBomb->Draw(pDest);
	Shared::DrawSurface(mBooster.x, mBooster.y, mpBooster->pSurface, pDest, &mpBooster->pClips[mBoosterClip]);
	Shared::DrawSurface(mX, mY, mpAngel->pSurface, pDest, &mpAngel->pClips[mClip]);
	Shared::DrawSurface(mHitbox.x, mHitbox.y, mpHitbox->pSurface, pDest, &mpHitbox->pClips[mHitboxClip]);
}

SDL_Rect Player::GetBounds()
{
	SDL_Rect temp = {mHitbox.x, mHitbox.y, mpHitbox->width, mpHitbox->height};
    return temp;
}

SDL_Rect Player::GetOuterBounds()
{
	SDL_Rect temp = {mX, mY, mpAngel->width, mpAngel->height};
    return temp;
}

Point Player::GetCenter()
{
	return Point(mX + mpAngel->width/2, mY + mpAngel->height/2);
}

void Player::TakeHit()
{
	//todo: die animation and respawn timer
}

bool Player::IsBombActive()
{
	return mspBomb->IsActive();
}