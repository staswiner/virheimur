#pragma once
#include "ImageLoader.h"
class Inventory 
{
public:
	Inventory();
	~Inventory();
	void Draw_Interface(int x = 100, int y = 20);
private:
	void Load_VAO();
	void Load_Interface();

	Shader shader;
	GLuint VAO, VBO, Texture;
	vector<vec2> vertices;
	ImageLoader InventoryGraphics;
	unsigned int Vertices_Amount;
};

