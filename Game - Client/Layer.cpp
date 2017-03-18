#include "Layer.h"



Layer::Layer()
{
}


Layer::~Layer()
{
}

void Layer::Draw()
{
	for (auto i : Objects)
	{
		i->Draw();
	}
}

Layers::Layers()
{
}

Layers::~Layers()
{
}

void Layers::Draw()
{
	for (auto i : Repository)
	{
		i.second.Draw();
	}
}
