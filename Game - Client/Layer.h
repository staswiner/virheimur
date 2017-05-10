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
	void ReloadShaders();
	void ReloadShaders(Shader::ImageType);
	void ClearLayer();

private:
	void Draw();
	void Update();
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
	void Update();
	void Add(Layer*, LayerType);
	void ReloadShaders();
	void ReloadShaders(Shader::ImageType);
	void Clear();
private: 
	map<LayerType, Layer*> layers;
};