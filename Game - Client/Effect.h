#pragma once
#include "Loaded_Models.h"
#include <chrono>
using namespace std::chrono;
class Effect
{
public:
	Effect(string Name, milliseconds Duration,vec3 Position);
	~Effect();
	void Draw();
	bool CheckStatus();
	mat4 ModelMatrix;
	Model* EffectModel;
private:
	milliseconds StartTime;
	milliseconds Duration;
};

