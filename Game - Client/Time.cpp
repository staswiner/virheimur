#include "Time.h"



Time::Time()
{
}


Time::~Time()
{
}

double Time::Now()
{
	milliseconds currTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
	return currTime.count();
}

void Time::CalculateFrame()
{
	NewFrameMS = Time::Now();
	this->FrameMS = NewFrameMS - PreviousFrameMS;
	PreviousFrameMS = NewFrameMS;
}

float Time::Frame()
{
	return this->FrameMS;
}
