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
	static FrameData Instance;
public:
	~FrameData();
	static FrameData& GetInstance()
	{
		static FrameData Instance;
		return Instance;
	}
	mat4 ViewMatrix;
	mat4 ProjectionMatrix;
};

