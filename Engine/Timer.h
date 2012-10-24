#pragma once
#ifndef TIMER_H
#define TIMER_H
//The timer
class Timer
{
private:
    //The clock time when the timer started
    int startTicks;

    //The ticks stored when the timer was paused
    int pausedTicks;

    //The timer status
    bool paused;
    bool started;
    int it;

public:
    //Initializes variables
    Timer();
    bool m_delete;
    //The various clock actions
    void start();
    void stop();
    void pause();
    void unpause();

    //Gets the timer's time
    int get_ticks();
    void set_ticks(int t);

    //Checks the status of the timer
    bool is_started();
    bool is_paused();
};

#endif