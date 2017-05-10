#include "Layer.h"



Layer::Layer()
{
}


Layer::~Layer()
{
}

void Layer::AddGameObject(GameObject* gameObject)
{
	this->Objects.push_back(gameObject);
}

void Layer::ReloadShaders()
{
	for (auto& o : this->Objects)
	{
		o->ReloadShader();
	}
}

void Layer::ReloadShaders(Shader::ImageType imageType)
{
	for (auto& o : this->Objects)
	{
		o->ReloadShader(imageType);
	}
}

void Layer::ClearLayer()
{
	Objects.clear();
}

void Layer::Draw()
{
	FrameData& frameData = FrameData::Instance();
	Camera& camera = Camera::GetCamera("Main");
	GameObject::SceneData sceneData;

	vec3 Light_Pos = frameData.Light_Pos;
	mat4 Light_Matrix = glm::lookAt(Light_Pos+vec3(1,1,1), vec3(0.0f), vec3(0.0f, 1.0f, 0.0f));
	Light_Matrix = frameData.ProjectionMatrix * Light_Matrix;

	sceneData.ProjectionMatrix = frameData.ProjectionMatrix;
	sceneData.ViewMatrix = frameData.ViewMatrix;
	sceneData.CameraPos = camera.GetCameraPosition();
	sceneData.Light_Matrix = Light_Matrix;
	sceneData.Light_Pos = Light_Pos;
	for (auto& object : Objects)
	{
		object->Draw(sceneData);
	}
}

void Layer::Update()
{
	for (auto it = Objects.begin(); it != Objects.end(); it++)
	{
		if ((*it)->Disabled)
		{
			it = Objects.erase(it);
		}
	}
}

//void Layer::OrderObjects(function<bool(GameObject&, GameObject&)> orderer)
//{
//	sort(this->Objects.begin(), this->Objects.end(), orderer);
//}

Layers::Layers()
{
}

Layers::~Layers()
{
}

void Layers::Draw()
{
	for (auto i : layers)
	{
		i.second->Draw();
	}
}

void Layers::Update()
{
	for (auto i : layers)
	{
		i.second->Update();
	}
}

void Layers::Add(Layer * layer, LayerType type)
{
	this->layers[type] = layer;
}

void Layers::ReloadShaders()
{
	for (auto& l : layers)
	{
		l.second->ReloadShaders();
	}
}

void Layers::ReloadShaders(Shader::ImageType imageType)
{
	for (auto& l : layers)
	{
		l.second->ReloadShaders(imageType);
	}
}

void Layers::Clear()
{
	for (auto layer : layers)
	{
		layer.second->ClearLayer();
		delete layer.second;
	}
}
