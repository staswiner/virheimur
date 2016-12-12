#pragma once
#include "Model.h"
class Grass
{
public:
	Grass();
	~Grass();
	void Initialize();
	void Draw(vector<mat4>& ModelMatrices);
	vector<vector<int>> MapData;
	vector<mat4> ObstaclesMat;
	Model model;
private:
	float m_Time;
	float m_GSpeed;
	float m_GPosition;
	unsigned int m_time;
	unsigned int m_StartTime;
	unsigned int m_Number_Of_Instances;
};

