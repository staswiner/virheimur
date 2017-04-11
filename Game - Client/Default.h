#pragma once
#include "GLM_Headers.h"
using namespace glm;
class Default
{
private:
	Default();
	Default(Default const&) = delete;
	void operator=(Default const&) = delete;
	static Default Instance;
public:
	~Default();
	static Default& GetInstance()
	{
		static Default Instance;
		return Instance;
	}
	mat4 BlenderConversion;
	mat4 BlenderConversionCenter;
};

