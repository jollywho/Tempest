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