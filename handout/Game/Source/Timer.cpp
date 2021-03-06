// ----------------------------------------------------
// Fast timer with milisecons precision
// ----------------------------------------------------

#include "Timer.h"
#include "SDL\include\SDL_timer.h"

// they are simple, one line each!
	
Timer::Timer()
{
	Start();
}

void Timer::Start()
{
	startTime = SDL_GetTicks();
}

void Timer::Stop()
{
	counter += ReadSec();
}

uint32 Timer::Read() const
{
	return SDL_GetTicks() - startTime;
}

float Timer::ReadSec() const
{
	return float(SDL_GetTicks() - startTime) / 1000.0f;
}

float Timer::ReadCombat() const
{
	return ReadSec() + counter;
}

bool Timer::Check(float interval)
{
	if (Read() > interval)return true;
	return false;
}

