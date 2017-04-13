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
	static Time Instance;
	float FrameMS;
	double NewFrameMS;
	double PreviousFrameMS = 0;
public:
	~Time();
	static Time& GetST()
	{
		static Time Instance;
		return Instance;
	}
	static double Now();
	void CalculateFrame();
	float Frame();
};

