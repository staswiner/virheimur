#pragma once
#include "Time.h"
#include "Text.h"
#include "Shader.h"
class FPS
{
public:
	FPS();
	~FPS();
	void CountFrame(Shader&);
private:
	int counter;
	time_t m_time;
	int fps;
};

