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

Timer::Timer()
{
    mStartTicks = 0;
    mPausedTicks = 0;
    mPaused = false;
    mStarted = false;
}

void Timer::Start()
{
    mStarted = true;
    mPaused = false;
    mStartTicks = SDL_GetTicks();
}

void Timer::Stop()
{
    mStarted = false;
    mPaused = false;
}

void Timer::Pause()
{
    if((mStarted == true) && (mPaused == false))
    {
        mPaused = true;
        mPausedTicks = SDL_GetTicks() - mStartTicks;
    }
}

void Timer::UnPause()
{
    if(mPaused == true)
    {
        mPaused = false;
        mStartTicks = SDL_GetTicks() - mPausedTicks;
        mPausedTicks = 0;
    }
}

int Timer::GetTicks()
{
    if(mStarted == true)
    {
        if(mPaused == true)
        {
            return mPausedTicks;
        }
        else
        {
            return SDL_GetTicks() - mStartTicks;
        }
    }
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