#include "FPS.h"



FPS::FPS()
{
	int counter = 0;
	time_t m_time = 0;
	int fps = 0;
}


FPS::~FPS()
{
}

void FPS::CountFrame(Shader& shader)
{
	counter++;
	time_t newTime = time(NULL);
	if (m_time != newTime)
	{
		m_time = newTime;
		fps = counter;
		counter = 0;
	}
	Text& text = Text::getInstance();
	text.RenderText("[fps : " + to_string(fps) + "]", 20, 50,0.0f, 20.0f);
}
