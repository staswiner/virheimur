#include "Minimap.h"



Minimap::Minimap()
{
}


Minimap::~Minimap()
{
}

void Minimap::Initialize()
{
	srand((uint)time(NULL));

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
void Minimap::UpdateMap()
{
	if (MinimapFrameData)
	{
		SOIL_free_image_data(reinterpret_cast<GLubyte*>(MinimapFrameData));
	}
	MinimapFrameData = this->GetImageData("Minimap/Minimap.png", Width, Height);
	for (auto vertex : dynamic_cast<Ground_Collision*>(ModelsCollection::Instance()["Land"]->meshes[0].mCollision)->GetVertices())
	{
		if (dot(vertex.Normal, vec3(0, 1, 0)) < 0.8f)
		{
			this->DrawDotStatic(vertex.Position, vec3(115, 77, 38));
		}
	}
	memcpy(NewImageData, MinimapFrameData, Width*Height * sizeof(u8vec4));

}
void Minimap::DrawMinimap()
{
	//Mouse& mouse = Mouse::Instanace();

	//Position = vec2(mouse.GetWindowSize().x - 300, 0);
	///*for (auto &i : CharactersPositions)
	//{
	//	Character.Draw(Position + i, Position+vec2(i.x + 20, i.y + 20));
	//}*/
	//
	//if (Data.RouteChanged)
	//{
	//	memcpy(NewImageData, MinimapFrameData, Width*Height * sizeof(u8vec4));
	//	Data.RouteChanged = false;
	//	if (Data.Graph)
	//	{
	//		for (auto i : *Data.Graph)
	//		{
	//			for (auto j : i.second)
	//			{
	//				DrawLine(j.first, i.first, u8vec3(255, 255, 255));
	//			}
	//		}
	//		for (auto i : *Data.Graph)
	//		{		
	//			DrawDotEdge(i.first, u8vec3(0, 0, 1));
	//		}
	//	}
	//	if (Data.Path && Data.Path->size() > 0)
	//	{
	//		for (auto i = (*Data.Path).begin(); i != Data.Path->end() - 1; i++)
	//		{
	//			DrawLine(*i, *(i + 1), u8vec3(255, 0, 0));
	//		}
	//	}
	//}
	//MinimapFrame.ReloadTexture(NewImageData, Width, Height);
	//MinimapFrame.Draw(Position, Position + vec2(300, 300));

}

u8vec4 * Minimap::GetMinimapData(int& Width, int& Height)
{
	Width = this->Width;
	Height = this->Height;
	return MinimapFrameData;
}

void Minimap::DrawLine(vec3 Start, vec3 End, u8vec3 Color)
{
	Start += 100;
	Start /= 200;
	Start *= Width;
	End += 100;
	End /= 200;
	End *= Width;
	if (End.x < Start.x)
	{
		vec3 c = End; End = Start; Start = c;
	}
	float M;

	if (End.x - Start.x == 0)
	{
		if (End.x == Start.x)
		{
			if (Start.z < End.z)
			{
				for (int z = (int)Start.z; z < (int)End.z; z++)
				{
					NewImageData[int(z)*Width + int(End.x) - 1] = u8vec4(Color, 255);
				}
			}
			else
			{
				for (int z = (int)End.z; z < (int)Start.z; z++)
				{
					NewImageData[int(z)*Width + int(End.x) - 1] = u8vec4(Color, 255);
				}
			}
		}
	}
	else if (((M = (End.z - Start.z) / (End.x - Start.x)) < 1 ) && M >= -1)
	{
		for (int x = 0; x < (End.x-Start.x); x++)
		{
			int Finalz = int(M * x) + (int)Start.z;
			int Finalx = x + (int)Start.x;
			if (Finalz > 300 || Finalx > 300 || Finalx < 0 || Finalz < 0)
			{
				return;
			}
			NewImageData[Finalz*Width + Finalx - 1] = u8vec4(Color, 255);
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
			int Finalz = z + (int)Start.z;
			int Finalx = int(M * z) + (int)Start.x;
			if (Finalz > 300 || Finalx > 300 || Finalx < 0 || Finalz < 0)
			{
				return;
			}
			NewImageData[Finalz*Width + Finalx - 1] = u8vec4(Color, 255);
		}
	}
	
}
void Minimap::DrawDot(vec3 Point, u8vec3 Color)
{
	Point += 100;
	Point /= 200;
	Point *= Width;

	NewImageData[int(Point.z)*Width + int(Point.x) - 1] = u8vec4(Color, 255);

	/*if (Point.x < Width - 3 and Point.z < Height - 3)
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				NewImageData[(int(Point.z + i)*Width + (Point.x + j))] = u8vec4(Color, 255);
			}
		}
	}*/
}
void Minimap::DrawDotStatic(vec3 Point, u8vec3 Color)
{
	Point += 100;
	Point /= 200;
	Point *= Width;


	MinimapFrameData[int(Point.z)*Width + int(Point.x) - 1] = u8vec4(Color, 255);

	if (Point.x < Width - 3 and Point.z < Height - 3)
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				MinimapFrameData[(int)((Point.z + i)*Width + (Point.x + j)) - 1] = u8vec4(Color, 255);
			}
		}
	}
}
void Minimap::DrawDotEdge(vec3 Point, u8vec3 Color)
{
	Point += 100;
	Point /= 200;
	Point *= Width;


	NewImageData[int(Point.z)*Width + int(Point.x) - 1] = u8vec4(Color, 255);

	if (Point.x < Width - 3 and Point.z < Height - 3)
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				NewImageData[(int)(int(Point.z + i)*Width + int(Point.x + j)) - 1] = u8vec4(Color, 255);
			}
		}
	}
}
