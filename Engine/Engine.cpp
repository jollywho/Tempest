#include "Engine.h"
#include "SDL_ttf.h"
#include "Engine/SFX.h"
#include <windows.h> // For the WaitMessage() function.
#include "State/GameState.h"
#include "State/IntroState.h"
#include "State/PlayState.h"
#include "State/PollState.h"
#include "State/PauseState.h"
#include "State/ContinueState.h"
#include "State/ShopState.h"

/** Default constructor. **/
CEngine::CEngine()
{
	mWidth		= WINDOW_WIDTH;
	mHeight		= WINDOW_HEIGHT;
	mpTitle		= 0;
 
	mpScreen		= 0;

	mMinimized		= false;
}
 
/** Destructor. **/
CEngine::~CEngine()
{
	SDL_Quit();
}
 
/** Sets the height and width of the window.
	@param rWidth The width of the window
	@param rHeight The height of the window
**/
void CEngine::SetSize(const int& rWidth, const int& rHeight)
{
	SDL_WM_SetIcon(IMG_Load("icon.png"), NULL);

	mWidth  = rWidth;
	mHeight = rHeight;
	mpScreen = SDL_SetVideoMode( rWidth, rHeight, 0, SDL_SWSURFACE| SDL_DOUBLEBUF );
}
 
/** initialize SDL, the window and the additional data. **/
void CEngine::Init()
{
	// Register SDL_Quit to be called at exit; makes sure things are cleaned up when we quit.
	atexit( SDL_Quit );
 
	// initialize SDL's subsystems - in this case, only video.
	SDL_putenv("SDL_VIDEO_CENTERED=center");
	if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ) 
	{
		fprintf( stderr, "Unable to initialize SDL: %s\n", SDL_GetError() );
		exit( 1 );
	}
 
	// Attempt to create a window with the specified height and width.
	SetSize( mWidth, mHeight );
 
	// If we fail, return error.
	if ( mpScreen == NULL ) 
	{
		fprintf( stderr, "Unable to set up video: %s\n", SDL_GetError() );
		exit( 1 );
	}
	if (TTF_Init() < 0)
	{
		fprintf( stderr, "Unable to initialize TTF: %s\n", SDL_GetError() );
		exit( 1 );
	}

	SFX::Init();
	SDL_ShowCursor(0);
	AdditionalInit();
}

CGameState* CEngine::StateInstance(State id)
{
	printf("--STATE CHANGE--\n");
	mKeys = KeyStruct();
	switch(id)
	{
		case State::Intro:
			return CIntroState::Instance();
			break;
		case State::Play:
			return CPlayState::Instance();
			break;
		case State::Poll:
			return CPollState::Instance();
			break;
		case State::Pause:
			return CPauseState::Instance();
			break;
		case State::Shop:
			return CShopState::Instance();
			break;
		case State::Continue:
			return CContinueState::Instance();
			break;
		default:
			return CIntroState::Instance();
			break;
	}
}

void CEngine::DoStateChange(States::State id) 
{
	// cleanup all states
	for (auto it = mpStates.begin(); it != mpStates.end();) {

		(*it)->Cleanup();
		it = mpStates.erase(it);
	}

	// store and initialize the new state
	mpStates.push_back(StateInstance(id));
	mpStates.back()->Init();
}

void CEngine::DoStatePush(States::State id)
{
	// store and initialize the new state
	mpStates.push_back(StateInstance(id));
    mpStates.back()->Init();
}

void CEngine::DoStatePop()
{
    // cleanup the current state
    if ( !mpStates.empty() ) {
        mpStates.back()->Cleanup();
        mpStates.pop_back();
    }

    // resume previous state
    if ( !mpStates.empty() ) {
        mpStates.back()->Resume();
    }
}

void CEngine::DoRequest()
{
	if (mpStates.back()->IsStateChange())
		DoStateChange(mpStates.back()->RequestedState());

	if (mpStates.back()->IsStatePush())
	{
		DoStatePush(mpStates.back()->RequestedState());
	}
	if (mpStates.back()->IsStatePop())
	{
		DoStatePop();
	}

	mpStates.back()->ClearRequest();
}
 
/** The main loop. **/
void CEngine::Start()
{
	mQuit = false;
 
	mPrevTime = 0;
	mPrevTime = SDL_GetTicks();
	
	// Main loop: loop forever.
	while ( !mQuit )
	{
		// Handle mouse and keyboard input
		DoInput();
		
		if ( mMinimized ) {
			// Release some system resources if the app. is minimized.
			WaitMessage(); // pause the application until focus in regained
		}
		else 
		{
			DoThink();
			DoRequest();
			DoRender();

			Uint32 curr_time = SDL_GetTicks();
			Uint32 elapsed_time = curr_time - mPrevTime;
			if(elapsed_time < 15)
			{
				// Not enough time has elapsed. Let's limit the frame rate
				SDL_Delay(15 - elapsed_time);
				curr_time = SDL_GetTicks();
				elapsed_time = curr_time - mPrevTime;
			}
			mPrevTime = curr_time;
		}
	}
	End();
}
 
/** Handles all controller inputs.
	@remark This function is called once per frame.
**/
void CEngine::DoInput()
{
	// Poll for events, and handle the ones we care about.
	SDL_Event event;
	while ( SDL_PollEvent( &event ) ) 
	{
		switch ( event.type ) 
		{
		case SDL_KEYDOWN:
 
			KeyDown( event.key.keysym.sym );
			break;
 
		case SDL_KEYUP:
			KeyUp( event.key.keysym.sym );
			break;
 
		case SDL_QUIT:
			mQuit = true;
			break;
 
		case SDL_ACTIVEEVENT:
			if ( event.active.state & SDL_APPACTIVE ) {
				if ( event.active.gain ) {
					mMinimized = false;
					WindowActive();
				} else {
					mMinimized = true;
					WindowInactive();
				}
			}
			break;
		} // switch
	} // while (handling input)
}
 
/** Handles the updating routine. **/
void CEngine::DoThink() 
{
	Think( mDelta.GetTicks() );
	mDelta.Start();
}
 
/** Handles the rendering and FPS calculations. **/
void CEngine::DoRender()
{
	//SDL_FillRect( m_screen, 0, SDL_MapRGB( m_screen->format, 0, 0, 0 ) );

	Render( GetSurface() );
 
	// Tell SDL to update the whole gScreen
	SDL_Flip( mpScreen );
}
 
/** Sets the title of the window 
	@param czTitle A character array that contains the text that the window title should be set to.
**/
void CEngine::SetTitle(const char* pTitle)
{
	mpTitle = pTitle;
	SDL_WM_SetCaption( pTitle, 0 );
}
 
/** Retrieve the title of the application window.
	@return The last set windows title as a character array.
	@remark Only the last set title is returned. If another application has changed the window title, then that title won't be returned.
**/
const char* CEngine::GetTitle()
{
	return mpTitle;
}
 
/** Retrieve the main screen surface.
	@return A pointer to the SDL_Surface surface
	@remark The surface is not validated internally.
**/
SDL_Surface* CEngine::GetSurface()
{ 
	return mpScreen;
}
 
/** Get the current FPS.
	@return The number of drawn frames in the last second.
	@remark The FPS is only updated once each second.
**/
int CEngine::GetFPS()
{
	return 0;
	//return m_iCurrentFPS;
}