#include "SeaAnimated.h"



SeaAnimated::SeaAnimated()
{
}


SeaAnimated::~SeaAnimated()
{
}

void SeaAnimated::Initialize()
{
	vector<Stas::Vertex> Vertices;
	Stas::Vertex vertex;
	vertex.Position = vec3(0);
	Vertices.push_back(vertex);
	Mesh mesh;
	mesh.LoadCustom(Vertices);
	this->model = Model(mesh);
}

void SeaAnimated::Draw(vector<mat4>& ModelMatrices)
{
	glEnable(GL_BLEND);
	glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	this->model.DrawInstanced(ModelMatrices);
	glDisable(GL_BLEND);
}
