#pragma once
#include "Text.h"
#include "Shader.h"
#include "glm\glm\vec3.hpp"
#include "ShaderBuilder.h"
#include "ImageLoader.h"
#include <algorithm>

class ChampionChat
{
public:
	ChampionChat(Shader& shader);
	~ChampionChat();
	void CreateChatbox();
	void Draw(string a_Text, mat4& projection, mat4& view, mat4& model);
	void Draw2D(string a_Text, mat4& projection, mat4& view, mat4& model);

private: 
	Shader& shader;
	vector<ImageLoader*> ChatFrames;
};

