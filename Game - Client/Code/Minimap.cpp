#include "Minimap.h"



Minimap::Minimap()
{
}


Minimap::~Minimap()
{
}

void Minimap::Initialize()
{
	srand(time(NULL));

	MinimapFrameData = this->GetImageData("Minimap/Minimap.png",Width,Height);
	MinimapFrame.Initialize("Minimap/Minimap.png");

	NewImageData = new u8vec4[Width*Height];
	// Character
	Character.Initialize("Minimap/Character.png");
	CharactersPositions.resize(30);
	for(auto &i:CharactersPositions)
	{ 
		i = vec2(rand() % 270, rand() % 270);
	}
}

void Minimap::DrawMinimap(GDO & Data)
{
	Mouse mouse;
	Position = vec2(mouse.GetWindowSize().x - 300, 0);
	MinimapFrame.Draw(Position,Position+vec2(300,300));
	/*for (auto &i : CharactersPositions)
	{
		Character.Draw(Position + i, Position+vec2(i.x + 20, i.y + 20));
	}*/
	
	if (Data.RouteChanged)
	{
		memcpy(NewImageData, MinimapFrameData, Width*Height * sizeof(u8vec4));
		Data.RouteChanged = false;
		for (auto i : *Data.Map)
		{
			for (auto j : i.second)
			{
				DrawLine(j.first, i.first, u8vec3(255,255,255));
			}
		}
		if (Data.Path)
		{
			for (auto i = (*Data.Path).begin(); i != Data.Path->end() - 1; i++)
			{
				DrawLine(*i, *(i + 1), u8vec3(255, 0, 0));
			}
		}
	}
	MinimapFrame.ReloadTexture(NewImageData, Width, Height);
}

void Minimap::DrawLine(vec3 Start, vec3 End, u8vec3 Color)
{
	Start += 1000;
	Start /= 2000;
	Start *= Width;
	End += 1000;
	End /= 2000;
	End *= Width;
	if (End.x < Start.x)
	{
		vec3 c = End; End = Start; Start = c;
	}
	float M;
	if (End.x - Start.x == 0)
	{
		for (int z = Start.z; z < End.z; z++)
		{
			NewImageData[int(z)*Width + int(End.x)] = u8vec4(Color, 255);
		}
	}
	else if (((M = (End.z - Start.z) / (End.x - Start.x)) < 1 ) && M >= -1)
	{
		for (int x = 0; x < (End.x-Start.x); x++)
		{
			int Finalz = M * x + Start.z;
			int Finalx = x + Start.x;
			if (Finalz > 300 || Finalx > 300 || Finalx < 0 || Finalz < 0)
			{
				return;
			}
			NewImageData[Finalz*Width + Finalx] = u8vec4(Color, 255);
		}
	}
	else
	{
		M = 1.0f / M;
		if (End.z < Start.z)
		{
			vec3 c = End; End = Start; Start = c;
		}
		for (int z = 0; z < (End.z-Start.z); z++)
		{
			int Finalz = z + Start.z;
			int Finalx = M * z + Start.x;
			if (Finalz > 300 || Finalx > 300 || Finalx < 0 || Finalz < 0)
			{
				return;
			}
			NewImageData[Finalz*Width + Finalx] = u8vec4(Color, 255);
		}
	}
	
}
