#include "Timer.h"

void TimerActivate(Timer *timer) {
    timer->active = true;
    timer->startTime = GetTime();
}

void TimerInit(Timer *timer, int duration, bool repeat, bool autostart, void (*func)(void *), void *args) {
    timer->duration = duration;
    timer->startTime = 0;
    timer->active = false;
    timer->repeat = repeat;
    timer->autoStart = autostart;
    timer->func = func;
    timer->args = args;

    if (timer->autoStart) {
        TimerActivate(timer);
    }
}

void TimerDeactivate(Timer *timer) {
    timer->active = false;
    timer->startTime = 0;
    if (timer->repeat) {
        TimerActivate(timer);
    }
}

void TimerUpdate(Timer *timer) {
    if (timer->active) {
        if (GetTime() - timer->startTime >= timer->duration) {
            if (timer->func && timer->startTime != 0) {
                timer->func(timer->args);
            }
            TimerDeactivate(timer);
        }
    }
}