#pragma once
#include "Model.h"
#include <vector>
#include <stack>
#include <map>

using namespace std;
class Layers;
class Layer
{
public:
	Layer();
	~Layer();
	friend Layers;
private:
	void Draw();
	vector<Model*> Objects;
};


enum class LayerType
{
	Outline,
	FinalObject
};

class Layers
{
public:
	Layers();
	~Layers();	
	void Draw();

	
private: 
	map<int, Layer> Repository;
};