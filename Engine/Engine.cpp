#include "Engine.h"
#include "SDL_ttf.h"
#include "Engine/SFX.h"
#include <windows.h> // For the WaitMessage() function.
#include "State/Gamestate.h"
#include "State/Introstate.h"
#include "State/Playstate.h"
#include "State/Pollstate.h"
#include "State/Scorestate.h"
 
KeyStruct default_keys = { false, false, false, false, false, false, false, false };

/** Default constructor. **/
CEngine::CEngine()
{
	m_iWidth		= 800;
	m_iHeight		= 600;
	m_czTitle		= 0;
 
	m_pScreen		= 0;

 
	m_bMinimized		= false;

	keys = default_keys;
	menustate = NULL;
}
 
/** Destructor. **/
CEngine::~CEngine()
{
	SDL_Quit();
}
 
/** Sets the height and width of the window.
	@param iWidth The width of the window
	@param iHeight The height of the window
**/
void CEngine::SetSize(const int& iWidth, const int& iHeight)
{
	SDL_WM_SetIcon(IMG_Load("icon.png"), NULL);

	m_iWidth  = iWidth;
	m_iHeight = iHeight;
	m_pScreen = SDL_SetVideoMode( iWidth, iHeight, 0, SDL_SWSURFACE| SDL_DOUBLEBUF );
}
 
/** Initialize SDL, the window and the additional data. **/
void CEngine::Init()
{
	// Register SDL_Quit to be called at exit; makes sure things are cleaned up when we quit.
	atexit( SDL_Quit );
 
	// Initialize SDL's subsystems - in this case, only video.
	if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ) 
	{
		fprintf( stderr, "Unable to init SDL: %s\n", SDL_GetError() );
		exit( 1 );
	}
 
	// Attempt to create a window with the specified height and width.
	SetSize( m_iWidth, m_iHeight );
 
	// If we fail, return error.
	if ( m_pScreen == NULL ) 
	{
		fprintf( stderr, "Unable to set up video: %s\n", SDL_GetError() );
		exit( 1 );
	}
	if (TTF_Init() < 0)
	{
		fprintf( stderr, "Unable to init TTF: %s\n", SDL_GetError() );
		exit( 1 );
	}
	SFX::Init_SFX();
 
	AdditionalInit();
}

CGameState* CEngine::GetStateInstance(State id)
{
	printf("--STATE CHANGE--\n");
	switch(id)
	{
		case Intro:
			return CIntroState::Instance();
			break;
		case Play:
			return CPlayState::Instance();
			break;
		case Poll:
			return CPollState::Instance();
			break;
		case Score:
			return CScoreState::Instance();
			break;
		default:
			return CIntroState::Instance();
			break;
	}
}

void CEngine::ChangeState(State id) 
{
	// cleanup all states
	for (auto it = states.begin(); it != states.end();) {
		(*it)->Cleanup();
		it = states.erase(it);
	}

	// store and init the new state
	states.push_back(GetStateInstance(id));
	states.back()->Init();
}

void CEngine::PushState(State id)
{
	// store and init the new state
	states.push_back(GetStateInstance(id));
    states.back()->Init();
}

void CEngine::PopState()
{
    // cleanup the current state
    if ( !states.empty() ) {
        states.back()->Cleanup();
        states.pop_back();
    }

    // resume previous state
    if ( !states.empty() ) {
        states.back()->Resume();
    }
}

void CEngine::PushMenu(State id)
{
	//create top level menu state
	menustate = GetStateInstance(id);
	menustate->Init();
}

void CEngine::PopMenu()
{
	 menustate->Cleanup(); 
	 menustate = NULL; 
	 states.back()->Return();
}

void CEngine::DoRequests()
{
	if (states.back()->StateRequired())
		ChangeState(states.back()->GetState());

	if (states.back()->PushRequired())
	{
		PushState(states.back()->GetState());
		states.back()->ClearRequest();
	}
	if (states.back()->PopRequired())
	{
		PopState();
		states.back()->ClearRequest();
	}
	if (states.back()->MenuPush())
	{
		PushMenu(states.back()->GetState());
		states.back()->ClearRequest();
	}

	if (menustate != NULL) { 
		if (menustate->MenuPop()) { PopMenu(); } }
}
 
/** The main loop. **/
void CEngine::Start()
{
	m_bQuit = false;
 
	prevTime = 0;
	prevTime = SDL_GetTicks();
	
	// Main loop: loop forever.
	while ( !m_bQuit )
	{
		// Handle mouse and keyboard input
		HandleInput();
		
		if ( m_bMinimized ) {
			// Release some system resources if the app. is minimized.
			WaitMessage(); // pause the application until focus in regained
		} 
		else 
		{
			DoThink();
			DoRequests();
			DoRender();

			Uint32 currTime = SDL_GetTicks();
			Uint32 timeElapsed = currTime - prevTime;
			if(timeElapsed < 15)
			{
				// Not enough time has elapsed. Let's limit the frame rate
				SDL_Delay(15 - timeElapsed);
				currTime = SDL_GetTicks();
				timeElapsed = currTime - prevTime;
			}
			prevTime = currTime;
		}
	}
	End();
}
 
/** Handles all controller inputs.
	@remark This function is called once per frame.
**/
void CEngine::HandleInput()
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
			m_bQuit = true;
			break;
 
		case SDL_MOUSEMOTION:
			MouseMoved(
				event.button.button, 
				event.motion.x, 
				event.motion.y, 
				event.motion.xrel, 
				event.motion.yrel);
			break;
 
		case SDL_MOUSEBUTTONUP:
			MouseButtonUp(
				event.button.button, 
				event.motion.x, 
				event.motion.y, 
				event.motion.xrel, 
				event.motion.yrel);
			break;
 
		case SDL_MOUSEBUTTONDOWN:
			MouseButtonDown(
				event.button.button, 
				event.motion.x, 
				event.motion.y, 
				event.motion.xrel, 
				event.motion.yrel);
			break;
 
		case SDL_ACTIVEEVENT:
			if ( event.active.state & SDL_APPACTIVE ) {
				if ( event.active.gain ) {
					m_bMinimized = false;
					WindowActive();
				} else {
					m_bMinimized = true;
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
	Think( delta.get_ticks() );
	delta.start();
}
 
/** Handles the rendering and FPS calculations. **/
void CEngine::DoRender()
{
	//SDL_FillRect( m_pScreen, 0, SDL_MapRGB( m_pScreen->format, 0, 0, 0 ) );

	Render( GetSurface() );
 
	// Tell SDL to update the whole gScreen
	SDL_Flip( m_pScreen );
}
 
/** Sets the title of the window 
	@param czTitle A character array that contains the text that the window title should be set to.
**/
void CEngine::SetTitle(const char* czTitle)
{
	m_czTitle = czTitle;
	SDL_WM_SetCaption( czTitle, 0 );
}
 
/** Retrieve the title of the application window.
	@return The last set windows title as a character array.
	@remark Only the last set title is returned. If another application has changed the window title, then that title won't be returned.
**/
const char* CEngine::GetTitle()
{
	return m_czTitle;
}
 
/** Retrieve the main screen surface.
	@return A pointer to the SDL_Surface surface
	@remark The surface is not validated internally.
**/
SDL_Surface* CEngine::GetSurface()
{ 
	return m_pScreen;
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