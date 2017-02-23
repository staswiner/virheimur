#pragma once
#include "ImageLoader.h"
#include "GlobalDataObject.h"
#include <vector>
#include <stdlib.h>
class Minimap : public ImageLoader
{
public:
	Minimap();
	~Minimap();
	void Initialize();
	void UpdateMap();
	void DrawMinimap(GDO&);
	u8vec4* GetMinimapData(int& Width, int& Height);
private:
	void DrawCharacter() {}
	void DrawLine(vec3 Start, vec3 End,u8vec3 Color);
	void DrawDot(vec3 Point, u8vec3 Color);
	void DrawDotStatic(vec3 Point, u8vec3 Color);
	void DrawDotEdge(vec3 Point, u8vec3 Color);
	u8vec4* MinimapFrameData;
	u8vec4* NewImageData;
	vec2 Position;
	int Width, Height;
	int counter = 0;
	int customTexture;
	GLuint MinimapFrameID;
	GLuint CharacterID;

	ImageLoader Character;
	ImageLoader MinimapFrame;
	// temp
	vector<vec2> CharactersPositions;
	map<vec3, map<vec3, int, bool(*)(const vec3&, const vec3&)>
		, bool(*)(const vec3&, const vec3&)>* Map;
};

