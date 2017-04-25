#include "Effect.h"


Effect::Effect(string Name, milliseconds Duration,vec3 Position)
{
	this->EffectModel = ModelsCollection::Instance()[Name];
	this->Duration = Duration;
	this->StartTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
	this->ModelMatrix = glm::translate(mat4(), Position);
}

Effect::~Effect()
{
}

void Effect::Draw()
{
	this->EffectModel->Draw();
}

bool Effect::CheckStatus()
{
	return (duration_cast<milliseconds>(system_clock::now().time_since_epoch())-this->StartTime) > this->Duration;
}
