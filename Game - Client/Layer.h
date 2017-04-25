#pragma once
#include "GameObject.h"
#include "FrameData.h"
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
	void AddGameObject();
private:
	void Draw();
	void OrderObjects(function<bool(GameObject)> orderer);
	vector<GameObject*> Objects;
	Layers::LayerType type;
};



class Layers
{
public:
	enum class LayerType
	{
		Outline,
		FinalObject,
		Transparent
	};
	Layers();
	~Layers();	
	void Draw();
	void Add(Layer*, LayerType);

	
private: 
	map<LayerType, Layer*> layers;
};