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
	float time = Time::Instance().Frame();
	int fps = 1000.0f / time;
	Text& text = Text::getInstance();
	text.RenderText("[fps : " + to_string(fps) + "]", 20, 50,0.0f, 20.0f);
}
