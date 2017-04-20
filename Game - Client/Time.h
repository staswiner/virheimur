#pragma once
#include <chrono>
using namespace std;
using namespace std::chrono;

class Time
{
private:
	Time();
	Time(Time&) = delete;
	void operator=(Time&) = delete;
	static Time instance;
	float FrameMS;
	double NewFrameMS;
	double PreviousFrameMS = 0;
public:
	~Time();
	static Time& Instance()
	{
		static Time instance;
		return instance;
	}
	static double Now();
	void CalculateFrame();
	float Frame();
};

