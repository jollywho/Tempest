#pragma once
#ifndef TIMER_H
#define TIMER_H

class Timer
{
private:
    //The clock time when the timer started
    int mStartTicks;

    //The ticks stored when the timer was paused
    int mPausedTicks;

    //The timer status
    bool mPaused;
    bool mStarted;
    int mIt;

public:
    Timer();
    void Start();
    void Stop();
    void Pause();
    void UnPause();

    int GetTicks();
    void SetTicks(int t);

    bool IsStarted(); 
    bool IsPaused();
};

#endif