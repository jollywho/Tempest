#include "Player.h"
#include "Engine/SpriteResource.h"
#include "UI/NSprite.h"
#include "State/playstate.h"
#include "Weapon/MType.h"
#include "Game/GameScore.h"
#include "Engine/SFX.h"

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
	mpDash = new NSprite(0,0, &SpriteResource::RequestResource("Player", "dash"), true);

	mSpeed = SPEED_NORMAL;
    mov = 0; mKForce = 0;
	left = 0; right = 0; up = 0; down = 0;
	mShift = false; mAttack = false; mBomb = false;
	mExplode = false; mInvuln = false; mDash = false;
	mDashReq = false; mSlash = false;

	mX = WINDOW_WIDTH/2 - ANGEL_SIZE/2;
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
	if (rKeys.ctrl)  mDashReq = true;
	else mDashReq = false;
	if (rKeys.space) mSlash = true;
	else mSlash = false;
}

void Player::HandleMovement(const int& rDeltaTime)
{
    float vx = left + right; float vy = up + down;
    float length = sqrtf((vx * vx) + (vy * vy));

    if (vy == 0 && vx == 0 && mSpeed > 200) 
		mSpeed-=rDeltaTime/2.f;
    else if ((vy != 0 || vx != 0) && mSpeed < SPEED_NORMAL) 
		mSpeed+=rDeltaTime/2.f;

	if (mDashReq)
	{
		if (!mDash)
		{
			Knockback(vx,vy,320);
			SFX::PlaySoundResource("dash");
			mpDash->Reset();
			mDashReq = false;
			mDash = true;
			mSpeed = 1000;
		}
	}
    if (length>0.0f)
    {
        vx/=length;
        vy/=length;
    }
    if (mKnockbackTimer.IsStarted()) 
    {
        vx = mKx; 
        vy = mKy; 
        if (mKnockbackTimer.GetTicks() > mKForce) {
            mKnockbackTimer.Stop(); mKForce = 0; mSpeed = 200; }
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
		mspWpn->MinorAttack(CPlayState::Instance()->pl_bulletlist);
	}
	else
		mspWpn->StopAttack();

	if (mSlash) 
	{ 
		mspWpn->MajorAttack(CPlayState::Instance()->pl_bulletlist);
		mSlash = false; 
	}

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
	mSpeed = SPEED_RECOVERY;
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
	mpDash->Update();

	HandleMovement(rDeltaTime);

	if (mpDash->IsDone()) mDash = false;
	Point center_point = Point(mX + ANGEL_SIZE/2, mY + ANGEL_SIZE/2);
	Point boost_point = Point(mX + ANGEL_SIZE/2, mY + ANGEL_SIZE);
	mpAngel->SetPos(center_point);
	mpBooster->SetPos(boost_point);
	mpWings->SetPos(center_point);
	mpZone->SetPos(center_point);
	mpHitbox->SetPos(center_point);
	mpDash->SetPos(boost_point);

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

	if (mDash)
		mpDash->Draw(pDest);
	if (mInvuln)
		mpWings->Draw(pDest);
}

HitBox& Player::GetBounds()
{
    return mpHitbox->GetBounds();
}

HitBox& Player::GetOuterBounds()
{
	return mpAngel->GetBounds();
}

Point Player::GetCenter()
{
	return Point(mX + ANGEL_SIZE/2, mY + ANGEL_SIZE/2);
}

void Player::TakeHit()
{
	if (!mInvuln && !mExplode)
	{
		if (!mspWpn->TakeHit())
		{
			KeyInput(KeyStruct());
			mExplode = true;
			mpExplosion->Reset();
			mpExplosion->SetPos(Point(mX + ANGEL_SIZE/2, mY + ANGEL_SIZE/2));
			mspBomb->BulletWipe();
			GameScore::Instance()->DecreaseLives();
		}
	}
}

void Player::Knockback(float xv, float yv, int force)
{
	if (mShift || mDashReq)
	{
		mKForce += force;
		xv == 0 ? mKx = 0 : mKx = xv/abs(xv);
		yv == 0 ? mKy = 0 : mKy = yv/abs(yv);
		mKnockbackTimer.Start();
	}
}

bool Player::IsBombActive()
{
	return mspBomb->IsActive();
}