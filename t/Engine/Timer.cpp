#include "Timer.h"
#include <SDL.h>

//game timer
Timer::Timer()
{
    //initialize the variables
    mStartTicks = 0;
    mPausedTicks = 0;
    mPaused = false;
    mStarted = false;
}

void Timer::Start()
{
    //Start the timer
    mStarted = true;

    //Unpause the timer
    mPaused = false;

    //Get the current clock time
    mStartTicks = SDL_GetTicks();
}

void Timer::Stop()
{
    //Stop the timer
    mStarted = false;

    //Unpause the timer
    mPaused = false;
}

void Timer::Pause()
{
    //If the timer is running and isn't already paused
    if( ( mStarted == true ) && ( mPaused == false ) )
    {
        //Pause the timer
        mPaused = true;
        
        //Calculate the paused ticks
        mPausedTicks = SDL_GetTicks() - mStartTicks;
    }
}

void Timer::UnPause()
{
    //If the timer is paused
    if( mPaused == true )
    {
        //Unpause the timer
        mPaused = false;

        //Reset the starting ticks
        mStartTicks = SDL_GetTicks() - mPausedTicks;
        //Reset the paused ticks
        mPausedTicks = 0;
    }
}

int Timer::GetTicks()
{
    //If the timer is running
    if( mStarted == true )
    {
        //If the timer is paused
        if( mPaused == true )
        {
            //Return the number of ticks when the timer was paused
            return mPausedTicks;
        }
        else
        {
            //Return the current time minus the start time
            return SDL_GetTicks() - mStartTicks;
        }
    }

    //If the timer isn't running
    return 0;
}

void Timer::SetTicks(int t)
{
    mStartTicks = t;
}

bool Timer::IsStarted()
{
    return mStarted;
}

bool Timer::IsPaused()
{
    return mPaused;
}