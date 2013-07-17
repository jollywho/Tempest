#include "Engine.h"
#include <stdlib.h>
#include "State/Gamestate.h"
#include "Game/Savescore.h"
#include "ResourceLoader.h"
#include "FontResource.h"
#include "SpriteResource.h"
 
class CMyEngine: public CEngine
{
public:
	void AdditionalInit ();
	void Think	    ( const int& rDeltaTime );
	void Render	    ( SDL_Surface* pDest );
 
	void KeyUp  	    (const int& iKeyEnum);
	void KeyDown	    (const int& iKeyEnum);
 
	void WindowInactive();
	void WindowActive();
 
	void End();
};
 
// Entry point
int main(int argc, char* argv[])  // <- this must match exactly, since SDL rewrites it
{
    CMyEngine Engine;
	
	Engine.SetTitle( "Loading..." );
	Engine.Init();

	Engine.SetTitle( "Tempest" );
	Engine.Start();
 
	Engine.SetTitle( "Quitting..." );
 
	return 0;
}
 
void CMyEngine::AdditionalInit()
{
	// Load up additional data2
	ResourceLoader::ReadFile("UI");

	FontResource::AddFont("bobble_red", "bobble_red.png");
	FontResource::AddFont("bobble_green", "bobble_green.png");
	FontResource::AddFont("gold", "GoldMistral.png");

	ScoreIO::SaveScore::LoadScores();
	DoStateChange(State::Intro);
}
 
void CMyEngine::Think( const int& rDeltaTime )
{
	mpStates.back()->Update(rDeltaTime);
}
 
void CMyEngine::Render( SDL_Surface* pDest )
{
	mpStates.back()->Draw(pDest);
}
 
void CMyEngine::KeyDown(const int& rKeyEnum)
{        
    switch (rKeyEnum)
    {
	case SDLK_ESCAPE:
		mKeys.esc = true;
		break;
    case SDLK_LEFT:
		mKeys.left = true;
		break;
    case SDLK_RIGHT:
		mKeys.right = true;
		break;
    case SDLK_UP:
		mKeys.up = true;
		break;
    case SDLK_DOWN:
		mKeys.down = true;
		break;
	case SDLK_RETURN:
		mKeys.enter = true;
		break;
	case SDLK_LSHIFT:
		mKeys.shift = true;
		break;
	case SDLK_z:
		mKeys.z = true;
		break;
	case SDLK_x:
		mKeys.x = true;
		break;
	case SDLK_LCTRL:
		mKeys.ctrl = true;
		break;
	case SDLK_SPACE:
		mKeys.space = true;
		break;
    }
	mpStates.back()->KeyInput(mKeys);
}

void CMyEngine::KeyUp(const int& rKeyEnum)
{
	switch (rKeyEnum)
	{
	case SDLK_ESCAPE:
		mKeys.esc = false;
		break;
    case SDLK_LEFT:
		mKeys.left = false;
		break;
    case SDLK_RIGHT:
		mKeys.right = false;
		break;
    case SDLK_UP:
		mKeys.up = false;
		break;
    case SDLK_DOWN:
		mKeys.down = false;
		break;
	case SDLK_RETURN:
		mKeys.enter = false;
		break;
	case SDLK_LSHIFT:
		mKeys.shift = false;
		break;
	case SDLK_z:
		mKeys.z = false;
		break;
	case SDLK_x:
		mKeys.x = false;
		break;
	case SDLK_LCTRL:
		mKeys.ctrl = false;
		break;
	case SDLK_SPACE:
		mKeys.space = false;
		break;
	}
	mpStates.back()->KeyInput(mKeys);
}
 
void CMyEngine::WindowInactive()
{
	// Pause game
}
 
void CMyEngine::WindowActive()
{
	// Un-pause game
}
 
 
void CMyEngine::End()
{
	// Clean up
}