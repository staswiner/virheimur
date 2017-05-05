#pragma once
#include "Graphics_Header.h"
#include "Mouse.h"
#include "glm\glm\vec2.hpp"
#include "glm\glm\vec3.hpp"
#include "glm\glm\vec4.hpp"
#include "ShaderBuilder.h"

#include <string>
#include <vector>
#define BUFFER_OFFSET(i) ((char *)NULL + (i))

using namespace std;
using namespace glm;
class ImageLoader
{
public:
	ImageLoader();
	~ImageLoader();
	virtual void Initialize(string Filename);
	void LoadVAO();
	int LoadTexture(string Filename);
	int LoadTexture(u8vec4* ColorData, int Width, int Height);
	u8vec4* GetImageData(string Filename, int & Width, int & Height);
	void ReloadTexture(u8vec4* ColorData, int Width, int Height);
	void ReloadTexture(string Filename);
	void Draw(vec2 TopLeft, vec2 BotRight);
	void DrawImagePart(vec2 TopLeft, vec2 BotRight, vec2 ImageTrueSize,
		vec2 CropTopLeft, vec2 CropBotRight);
	vec2 GetTrueSize() { return this->TrueSize; }
	GLuint VAO, VBO, MyTexture;
private:
	struct Vertices {
		vec2 vertices;
		vec2 uvs;
	};
	vector<Vertices> vertices;
	unsigned int Vertices_Amount;
	vec2 TrueSize;
};

