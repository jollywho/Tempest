#include "Player.h"
#include "Engine/SpriteResource.h"
#include "UI/NSprite.h"
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
	SpriteResource::AddResource("Player", "angel.png", 64, 64, 120, 4);
	SpriteResource::AddResource("Player", "hitbox.png", 20, 20, 60, 8);
	SpriteResource::AddResource("Player", "booster.png", 38, 38, 60, 5);
	SpriteResource::AddResource("Player", "zone.png", 120, 120, 60, 4);
	SpriteResource::AddResource("Player", "player_explosion.png", 96, 96, 60, 20);
	SpriteResource::AddResource("Player", "invuln_wings.png", 91, 187, 60, 9);

	mpAngel = new NSprite(0,0, &SpriteResource::RequestResource("Player", "angel.png"));
	mpHitbox = new NSprite(0,0, &SpriteResource::RequestResource("Player", "hitbox.png"));
	mpBooster = new NSprite(0,0, &SpriteResource::RequestResource("Player", "booster.png"));
	mpZone = new NSprite(0,0, &SpriteResource::RequestResource("Player", "zone.png"));
	mpExplosion = new NSprite(0,0, &SpriteResource::RequestResource("Player", "player_explosion.png"), true);
	mpWings = new NSprite(0,0, &SpriteResource::RequestResource("Player", "invuln_wings.png"));

	mSpeed = SPEED_NORMAL;
    mov = 0;
	left = 0; right = 0; up = 0; down = 0;
	mShift = false; mAttack = false; mBomb = false;
	mExplode = false; mInvuln = false; mLocked = false;

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
	if (mExplode || mLocked) return;
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

	if (!mLocked)
	{
		if (mX < GAME_BANNER_WIDTH) mX = GAME_BANNER_WIDTH;
		if (mX + ANGEL_SIZE > GAME_BOUNDS_WIDTH) mX = GAME_BOUNDS_WIDTH - ANGEL_SIZE;
		if (mY < GAME_UI_TOP) mY = GAME_UI_TOP;
		if (mY + ANGEL_SIZE > GAME_UI_BOTTOM) mY = GAME_UI_BOTTOM - ANGEL_SIZE;
	}
}

void Player::HandleAttacks(const int& rDeltaTime)
{
	mspWpn->SetPos(mX + ANGEL_SIZE/2, mY, 0);
	if (mAttack)
	{
		if (mShift)	mspWpn->MajorAttack(CPlayState::Instance()->pl_bulletlist);
		else		mspWpn->MinorAttack(CPlayState::Instance()->pl_bulletlist);
	}
	else
		mspWpn->StopAttack();

	if (mShift)mspWpn->Shift();
	else mspWpn->Unshift();

	if (mBomb && !mspBomb->IsActive()) mspBomb->Start(mX + ANGEL_SIZE/2, mY);

	mspWpn->Update(rDeltaTime);
	mspBomb->Update(rDeltaTime);
}

void Player::UpdateExploding(const int& rDeltaTime)
{
	mpExplosion->Update();
	if (mpExplosion->IsDone())
	{
		mExplode = false;
		mInvuln = true;
		mLocked = true;
		mX = GAME_LEVEL_WIDTH/2;
		mY = GAME_BOUNDS_HEIGHT + 100;
	}
}

void Player::UpdateLocked(const int& rDeltaTime)
{
	mpWings->Update();
}

void Player::Update(const int& rDeltaTime)
{
	if (mExplode)
		UpdateExploding(rDeltaTime);
	if (mLocked)
		UpdateLocked(rDeltaTime);

	mpAngel->Update();
	mpBooster->Update();
	mpHitbox->Update();
	mpZone->Update();

	HandleMovement(rDeltaTime);

	FPoint center_point = FPoint(mX + ANGEL_SIZE/2, mY + ANGEL_SIZE/2);
	FPoint hit_point = FPoint(mX + ANGEL_SIZE, mY + ANGEL_SIZE*2);
	mpAngel->SetPos(center_point);
	mpBooster->SetPos(center_point);
	mpWings->SetPos(center_point);
	mpZone->SetPos(center_point);
	mpHitbox->SetPos(hit_point);

	HandleAttacks(rDeltaTime);
}

void Player::Draw(SDL_Surface *pDest)
{
	if (mExplode)
	{
		mpExplosion->Draw(pDest);
		return;
	}

	if (mShift)
		mpZone->Draw(pDest);
	mspWpn->Draw(pDest);
	mspBomb->Draw(pDest);
	mpBooster->Draw(pDest);
	mpAngel->Draw(pDest);
	mpHitbox->Draw(pDest);

	if (mInvuln)
		mpWings->Draw(pDest);
}

SDL_Rect Player::GetBounds()
{
	SDL_Rect temp = {mX, mY, HITBOX_SIZE, HITBOX_SIZE};
    return temp;
}

SDL_Rect Player::GetOuterBounds()
{
	SDL_Rect temp = {mX, mY, ANGEL_SIZE, ANGEL_SIZE};
    return temp;
}

Point Player::GetCenter()
{
	return Point(mX + ANGEL_SIZE/2, mY + ANGEL_SIZE/2);
}

void Player::TakeHit()
{
	if (!mInvuln)
	{
		mExplode = true;
		mpExplosion->Reset();
		mpExplosion->SetPos(FPoint(mX + ANGEL_SIZE/2, mY + ANGEL_SIZE/2));
	}
}

bool Player::IsBombActive()
{
	return mspBomb->IsActive();
}