#pragma once
#include "GLM_Headers.h"
using namespace glm;
class Default
{
private:
	Default();
	Default(Default const&) = delete;
	void operator=(Default const&) = delete;
	static Default instance;
public:
	~Default();
	static Default& Instance()
	{
		static Default instance;
		return instance;
	}

	mat4 BlenderConversion;
	mat4 BlenderConversionCenter;
	double PI = 3.14159265358979323419716f;
};

