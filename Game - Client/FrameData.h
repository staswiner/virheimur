#pragma once
#include "string.h"
#include "Graphics_Header.h"
using namespace std;
using namespace glm;
class FrameData
{
private:
	FrameData();
	FrameData(FrameData const&) = delete;
	void operator=(FrameData const&) = delete;
	static FrameData instance;
public:
	~FrameData();
	static FrameData& Instance()
	{
		static FrameData instance;
		return instance;
	}
	mat4 ViewMatrix;
	mat4 ProjectionMatrix;
};

