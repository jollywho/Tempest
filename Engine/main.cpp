#include "Engine.h"
#include <stdlib.h>
#include "State/Gamestate.h"
#include "Game/Savescore.h"
 
class CMyEngine: public CEngine
{
public:
	void AdditionalInit ();
	void Think	    ( const int& iElapsedTime );
	void Render	    ( SDL_Surface* pDestSurface );
 
	void KeyUp  	    (const int& iKeyEnum);
	void KeyDown	    (const int& iKeyEnum);
 
	void MouseMoved     (const int& iButton, 
			     const int& iX, 
			     const int& iY, 
			     const int& iRelX, 
		             const int& iRelY);
 
	void MouseButtonUp  (const int& iButton, 
			     const int& iX, 
			     const int& iY, 
			     const int& iRelX, 
		             const int& iRelY);
 
	void MouseButtonDown(const int& iButton, 
			     const int& iX, 
			     const int& iY, 
			     const int& iRelX, 
		             const int& iRelY);
 
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

	Engine.SetTitle( "SDL Testing!" );
	Engine.Start();
 
	Engine.SetTitle( "Quitting..." );
 
	return 0;
}
 
void CMyEngine::AdditionalInit()
{
	ScoreIO::SaveScore::LoadScores();
	ChangeState(Intro);
	// Load up additional data
}
 
void CMyEngine::Think( const int& iElapsedTime )
{
	states.back()->Update(iElapsedTime);
	// Do time-based calculations
}
 
void CMyEngine::Render( SDL_Surface* pDestSurface )
{
	// Display slick graphics on screen
	states.back()->Draw(pDestSurface);
}
 
void CMyEngine::KeyDown(const int& iKeyEnum)
{        
    switch (iKeyEnum)
    {
    case SDLK_LEFT:
		keys.left = true;
		break;
    case SDLK_RIGHT:
		keys.right = true;
		break;
    case SDLK_UP:
		keys.up = true;
		break;
    case SDLK_DOWN:
		keys.down = true;
		break;
	case SDLK_RETURN:
		keys.enter = true;
		break;
	case SDLK_LSHIFT:
		keys.shift = true;
		break;
	case SDLK_z:
		keys.z = true;
		break;
	case SDLK_x:
		keys.x = true;
		break;
    }
	states.back()->CheckKeys(keys);
}
 
 
void CMyEngine::KeyUp(const int& iKeyEnum)
{
	switch (iKeyEnum)
	{
    case SDLK_LEFT:
		keys.left = false;
		break;
    case SDLK_RIGHT:
		keys.right = false;
		break;
    case SDLK_UP:
		keys.up = false;
		break;
    case SDLK_DOWN:
		keys.down = false;
		break;
	case SDLK_RETURN:
		keys.enter = false;
		break;
	case SDLK_LSHIFT:
		keys.shift = false;
		break;
	case SDLK_z:
		keys.z = false;
		break;
	case SDLK_x:
		keys.x = false;
		break;
	}
	states.back()->CheckKeys(keys);
}
 
void CMyEngine::MouseMoved(const int& iButton, 
			   const int& iX, 
			   const int& iY, 
			   const int& iRelX, 
			   const int& iRelY)
{
	// Handle mouse movement
 
	// iX and iY are absolute screen positions
	// iRelX and iRelY are screen position relative to last detected mouse movement
}
 
void CMyEngine::MouseButtonUp(const int& iButton, 
			      const int& iX, 
			      const int& iY, 
			      const int& iRelX, 
			      const int& iRelY)
{
	// Handle mouse button released
}
 
void CMyEngine::MouseButtonDown(const int& iButton, 
				const int& iX, 
				const int& iY, 
				const int& iRelX, 
				const int& iRelY)
{
	// Handle mouse button pressed
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