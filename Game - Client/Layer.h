#pragma once
#include "GameObject.h"
#include "FrameData.h"
#include "Camera.h"
#include <vector>
#include <stack>
#include <map>

using namespace std;
class Layers;
enum class LayerType
{
	Outline,
	FinalObject,
	Transparent
};
class Layer
{
public:
	Layer();
	~Layer();
	friend Layers;
	void AddGameObject(GameObject*);
private:
	void Draw();
	//void OrderObjects(function<bool(GameObject&, GameObject&)> orderer);
	vector<GameObject*> Objects;
	LayerType type;
};



class Layers
{
public:

	Layers();
	~Layers();	
	void Draw();
	void Add(Layer*, LayerType);

	
private: 
	map<LayerType, Layer*> layers;
};