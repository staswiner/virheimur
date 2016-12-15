#include "Grass.h"

Grass::Grass()
{
}

Grass::~Grass()
{
}

void Grass::Initialize()
{
	vector<Stas::Vertex> Vertices;
	Stas::Vertex vertex;
	for (int i = 0; i < 1; i++)
	{
		vertex.Position = vec3(rand()%2?i:-i, 0, rand() % 2 ? i : -i);
		vertex.Position *= 2;
		Vertices.push_back(vertex);
	}
	Mesh mesh;
	mesh.LoadCustom(Vertices);
	this->model = Model(mesh);
	model.AddTexture("Fractal", "Map/CircleArea.jpg");
	model.AddTexture("CoverPicture", "Map/Grass2.jpg");
	//model.AddTexture("CoverPicture","Map/RussiaFlag.jpg");
	//MapData = Model::LoadBufferFromImage("Map/Fractal.jpg");
}

void Grass::Draw(vector<mat4>& ModelMatrices)
{
	glEnable(GL_BLEND);
	this->model.DrawInstanced(ModelMatrices);
	glDisable(GL_BLEND);
}
