#pragma once
#include "raylib.h"

typedef struct Timer {
    int duration;
    double startTime;
    bool active;
    bool repeat;
    bool autoStart;
    void (*func)(void *);
    void *args;
} Timer;

void TimerActivate(Timer *timer); // Activate the timer

void TimerInit(Timer *timer, int duration, bool repeat, bool autostart, void (*func)(void *), void *args); // Initialize the timer

void TimerDeactivate(Timer *timer); // Deactivate the timer

void TimerUpdate(Timer *timer); // Update the timer, Ran once a frame