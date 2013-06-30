#pragma once
#ifndef ENGINE_H
#define ENGINE_H
 
#include "Engine/Shared.h"
#include <vector>

class CGameState;

namespace States
{
	enum State
	{
		Intro,
		Play,
		Poll,
		Name,
		Pause,
		Continue,
		Gameover,
	};
}
typedef States::State State;

/** The base engine class. **/
class CEngine 
{
private:
 
	/** Window width **/
	int mWidth;
	/** Window height **/
	int mHeight;
 
	/** Has quit been called? **/
	bool mQuit;
 
	/** The title of the window **/
	const char* mpTitle;
 
	/** Screen surface **/
	SDL_Surface* mpScreen;
 
	/** Is the window minimized? **/
	bool mMinimized;

	Uint32 mPrevTime;
	Timer mDelta;

protected:
	void DoInput();
	void DoThink();
	void DoRender();
	void DoRequest();
 
	void DoStateChange(States::State id);
	void DoStatePush(States::State id);
	void DoStatePop();
	
	void SetSize(const int& rWidth, const int& rHeight);

	std::vector<CGameState*> mpStates;
	KeyStruct mKeys;
public:
	CEngine();
	virtual ~CEngine();
 
	void Init();
	void Start();
 
	/** OVERLOADED - Data that should be initialized when the application starts. **/
	virtual void AdditionalInit	() {}
 
	/** OVERLOADED - All the games calculation and updating. 
		@param deltaTime The time in milliseconds elapsed since the function was called last.
	**/
	virtual void Think		( const int& rDeltaTime ) {}
	/** OVERLOADED - All the games rendering. 
		@param pDestSurface The main screen surface.
	**/
	virtual void Render		( SDL_Surface* pDest ) {}
 
	/** OVERLOADED - Allocated data that should be cleaned up. **/
	virtual void End		() {}
 
	/** OVERLOADED - Window is active again. **/
	virtual void WindowActive	() {}
 
	/** OVERLOADED - Window is inactive. **/
	virtual void WindowInactive	() {}
 
 
	/** OVERLOADED - Keyboard key has been released.
		@param iKeyEnum The key number.
	**/
	virtual void KeyUp		(const int& rKeyEnum) {}
 
	/** OVERLOADED - Keyboard key has been pressed.
		@param iKeyEnum The key number.
	**/
	virtual void KeyDown		(const int& rKeyEnum) {}
 
	void		SetTitle	(const char* pTitle);
	const char* 	GetTitle	();
 
	SDL_Surface* 	GetSurface	();
	CGameState*		StateInstance(State id);
	int 		GetFPS		();
};
 
#endif // ENGINE_H