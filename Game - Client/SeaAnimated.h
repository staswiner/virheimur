#pragma once
#include "Model.h"

class SeaAnimated
{
public:
	SeaAnimated();
	~SeaAnimated();
	void Initialize();
	void Draw(vector<mat4>& ModelMatrices);
	vector<vector<int>> MapData;
	vector<mat4> ObstaclesMat;

private:
	Model model;

};

