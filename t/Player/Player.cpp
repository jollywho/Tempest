#include "Player.h"
#include "Engine/SpriteResource.h"
#include "UI/NSprite.h"
#include "State/playstate.h"
#include "Weapon/MType.h"
#include "Game/GameScore.h"

Bomb* Player::mspBomb;
Weapon* Player::mspWpn;

Player::Player() 
{
	printf("Player Created\n");

	mpAngel = new NSprite(0,0, &SpriteResource::RequestResource("Player", "angel"));
	mpHitbox = new NSprite(0,0, &SpriteResource::RequestResource("Player", "hitbox"));
	mpBooster = new NSprite(0,0, &SpriteResource::RequestResource("Player", "booster"));
	mpZone = new NSprite(0,0, &SpriteResource::RequestResource("Player", "zone"));
	mpExplosion = new NSprite(0,0, &SpriteResource::RequestResource("Player", "player_explosion"), true);
	mpWings = new NSprite(0,0, &SpriteResource::RequestResource("Player", "invuln_wings"));

	mSpeed = SPEED_NORMAL;
    mov = 0;
	left = 0; right = 0; up = 0; down = 0;
	mShift = false; mAttack = false; mBomb = false;
	mExplode = false; mInvuln = false;

	mX = WINDOW_WIDTH/2;
	SetWeaponType(M_type);
}

void Player::Spawn()
{
	mInvuln = true;
	mLocked = true;
    mY = GAME_BOUNDS_HEIGHT + 200;
	mspWpn->ResetPos(mX + ANGEL_SIZE/2, mY);
	mInvulnTimer.Start();
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
	if (mKnockbackTimer.IsStarted()) 
	{
		vx = mKx; 
		vy = mKy; 
		if (mKnockbackTimer.GetTicks() > mKForce) {
			mKnockbackTimer.Stop(); }
	}
	mX += (vx * mSpeed) * (rDeltaTime/1000.f);
	mY += (vy * mSpeed) * (rDeltaTime/1000.f);

	if (!mLocked && !mExplode)
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

	if (mBomb && !mspBomb->IsActive()) 
	{
		if (GameScore::Instance()->DecreaseBombups())
		{
			mspBomb->Start(mX + ANGEL_SIZE/2, mY);
			mInvuln = true;
			mInvulnTimer.Start();
		}
		//else play fail.wav
	}

	mspWpn->Update(rDeltaTime);
	mspBomb->Update(rDeltaTime);
}

void Player::UpdateExploding(const int& rDeltaTime)
{
	mpExplosion->Update();
	if (mpExplosion->IsDone())
	{
		mExplode = false;
		Spawn();
	}
}

void Player::UpdateLocked(const int& rDeltaTime)
{
	mSpeed = SPEED_SLOW;
	up = -1;
	if (mY < GAME_UI_BOTTOM)
	{
		mLocked = false;
		up = 0;
	}
}

void Player::Update(const int& rDeltaTime)
{
	if (mExplode)
		UpdateExploding(rDeltaTime);
	if (mLocked)
		UpdateLocked(rDeltaTime);
	if (mInvulnTimer.GetTicks() > INVULN_DURATION)
		mInvuln = false;

	mpAngel->Update();
	mpBooster->Update();
	mpHitbox->Update();
	mpZone->Update();
	mpWings->Update();

	HandleMovement(rDeltaTime);

	FPoint center_point = FPoint(mX + ANGEL_SIZE/2, mY + ANGEL_SIZE/2);
	FPoint hit_point = FPoint(mX + ANGEL_SIZE/2, mY + HITBOX_SIZE*1.5);
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

Rect& Player::GetBounds()
{
    return mpHitbox->Bounds();
}

Rect& Player::GetOuterBounds()
{
	return mpAngel->Bounds();
}

Point Player::GetCenter()
{
	return Point(mX + ANGEL_SIZE/2, mY + ANGEL_SIZE/2);
}

void Player::TakeHit()
{
	if (!mInvuln && !mExplode)
	{
		KeyInput(KeyStruct());
		mExplode = true;
		mpExplosion->Reset();
		mpExplosion->SetPos(FPoint(mX + ANGEL_SIZE/2, mY + ANGEL_SIZE/2));
		mspBomb->BulletWipe();
		GameScore::Instance()->DecreaseLives();
	}
}

void Player::Knockback(float xv, float yv, int force)
{
	if (mShift)
	{
		mKx = xv; mKy = yv; mKForce = force;
		mKnockbackTimer.Start();
	}
}

bool Player::IsBombActive()
{
	return mspBomb->IsActive();
}