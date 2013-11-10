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
	void Think(const int& rDeltaTime);
	void Render(SDL_Surface* pdest);
 
	void KeyUp(const int& iKeyEnum);
	void KeyDown(const int& iKeyEnum);
	void MouseDown(const int& rKeyEnum);
	void MouseUp(const int& rKeyEnum);
	void MouseMove(const int& rMotionX, const int& rMotionY);
 
	void WindowInactive();
	void WindowActive();
	void End();
};
 
// Entry point
int main(int argc, char* argv[])  // <- this must match exactly, since SDL rewrites it
{
    CMyEngine Engine;
	
	Engine.SetTitle("Loading...");
	Engine.Init();

	Engine.SetTitle("Tempest");
	Engine.Start();
 
	Engine.SetTitle("Quitting...");
 
	return 0;
}
 
void CMyEngine::AdditionalInit()
{
	ResourceLoader::ReadFile("UI");
	ResourceLoader::ReadFile("Font");

	ScoreIO::SaveScore::LoadScores();
	DoStateChange(State::INTRO);
}
 
void CMyEngine::Think(const int& rDeltaTime)
{
	mpStates.back()->Update(rDeltaTime);
}
 
void CMyEngine::Render(SDL_Surface* pdest)
{
	mpStates.back()->Draw(pdest);
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