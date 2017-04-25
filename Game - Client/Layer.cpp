#include "Layer.h"



Layer::Layer()
{
}


Layer::~Layer()
{
}

void Layer::Draw()
{
	FrameData& frameData = FrameData::Instance();
	mat4 WVM;
	mat4 ModelMatrix;
	mat4 ViewMatrix = frameData.ViewMatrix;
	mat4 ProjectionMatrix = frameData.ProjectionMatrix;

	for (auto i : Objects)
	{
		ModelMatrix = i->unit_Data.GetModelMatrix();
		WVM = ProjectionMatrix * ViewMatrix *  Default::Instance().BlenderConversion;
		ShaderBuilder::LoadShader(Shader::At(""))->
			Add_mat4("WVM", WVM);
		i->Draw();
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

void Layers::Add(Layer * layer, LayerType type)
{
	this->layers[type] = layer;
}
