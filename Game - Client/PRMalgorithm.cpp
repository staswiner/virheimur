#include "PRMalgorithm.h"



PRMalgorithm::PRMalgorithm()
{
}


PRMalgorithm::~PRMalgorithm()
{
}

bool SortByX(const vec3& lhs, const vec3& rhs)
{
	return lhs.x < rhs.x;
}
bool SortByZ(const vec3& lhs, const vec3& rhs)
{
	return lhs.z < rhs.z;
}


map<vec3, map<vec3, int, bool(*)(const vec3&, const vec3&)>
	, bool(*)(const vec3&, const vec3&)>* PRMalgorithm::
	GeneratePoints(Stas::MinimapData Map,vec3& Source, vec3& Destination)
{
	srand(time(NULL));
	const int MapScale = 100;
	const int MAX_DISTANCE = 50;
	const int MAX_POINTS = 200;
	int Width, Height;
	u8vec4* MapData = Map.Map;
	Width = Map.Width;
	Height = Map.Height;
	auto Graph = new map<vec3, map<vec3, int, bool(*)(const vec3&, const vec3&)>
		, bool(*)(const vec3&, const vec3&)>(Stas::Maths::vec3Compare);
	
	vector<vec3> Points;
	Points.push_back(Source);
	Points.push_back(Destination);
	vec3 ConvertToMinimapCoords = Points.back();
	ConvertToMinimapCoords += float(MapScale);
	ConvertToMinimapCoords /= float(2 * MapScale);
	ConvertToMinimapCoords *= float(Width);
	if (MapData[int(ConvertToMinimapCoords.z)*Width + (int)ConvertToMinimapCoords.x] == u8vec4(115, 77, 38, 255))
	{
		Points.pop_back();
	}

	for (int i = 0; i < MAX_POINTS; i++)
	{
		Points.push_back(vec3((rand() % (2 * MapScale) ) - MapScale,
			0, (rand() % (2 * MapScale)) - MapScale));
		vec3 ConvertToMinimapCoords = Points.back();
		ConvertToMinimapCoords += float(MapScale);
		ConvertToMinimapCoords /= float(2 * MapScale);
		ConvertToMinimapCoords *= float(Width);
		if (MapData[int(ConvertToMinimapCoords.z)*Width + (int)ConvertToMinimapCoords.x] == u8vec4(115, 77, 38, 255))
		{
			Points.pop_back();
			i--;
		}
	}
	for (auto i = Points.begin(); i != Points.end(); i++)
	{
		(*Graph)[*i] = map<vec3, int, bool(*)(const vec3&, const vec3&)>(Stas::Maths::vec3Compare);
	}
	/*******************/
	//std::sort(Points.begin(), Points.end(), SortByX);
	//for (auto i = Points.begin(); i != Points.end(); i++)
	//{
	//	map<vec3, int, bool(*)(const vec3&, const vec3&)> Paths(Stas::Maths::vec3Compare);
	//	for (auto j = i + 1; j != Points.end();)
	//	{
	//		if (abs(i->x - j->x) < MAX_DISTANCE)
	//		{
	//			(*Graph)[*i][*j] = glm::distance(*i, *j);
	//			(*Graph)[*j][*i] = glm::distance(*i, *j);
	//			j++;
	//		}
	//		else
	//		{
	//			break;
	//		}
	//	}
	//}
	//std::sort(Points.begin(), Points.end(), SortByZ);
	//for (auto i = Points.begin(); i != Points.end(); i++)
	//{
	//	map<vec3, int, bool(*)(const vec3&, const vec3&)> Paths(Stas::Maths::vec3Compare);
	//	for (auto j = i + 1; j != Points.end();)
	//	{
	//		if (abs(i->z - j->z) < MAX_DISTANCE)
	//		{
	//			(*Graph)[*i][*j] = glm::distance(*i, *j);
	//			(*Graph)[*j][*i] = glm::distance(*i, *j);
	//			j++;
	//		}
	//		else
	//		{
	//			break;
	//		}
	//	}
	//}
	//
	/***********/
	vector<map<vec3, int, bool(*)(const vec3&, const vec3&)>*> Paths(Points.size());
	
	
	
	
	for (auto i = Points.begin(); i != Points.end(); i++)
	{
		//map<vec3, int, bool(*)(const vec3&, const vec3&)> Paths(Stas::Maths::vec3Compare);
		for (auto j = i+1; j != Points.end();)
		{
			if (glm::distance(*i, *j) < MAX_DISTANCE)
			{
				if (IsPathAvailable(Map, *i, *j))
				{
					(*Graph)[*i][*j] = glm::distance(*i, *j);
					(*Graph)[*j][*i] = glm::distance(*i, *j);
				}
				
			//	j = Points.erase(j);
				j++;
			}
			else
			{
				j++;
			}
		}
	}
	return Graph;
}

vector<vec3> PRMalgorithm::FoundPath(map<vec3, map<vec3, int, bool(*)(const vec3&, const vec3&)>
	, bool(*)(const vec3&, const vec3&)>* Map, vec3& Source, vec3& Destination)
{
	vector<vec3> Backtrack = Stas::Maths::Dijkstra(*Map, Source, Destination);
	return Backtrack;
}

bool PRMalgorithm::IsPathAvailable(Stas::MinimapData Map,vec3 Start, vec3 End)
{
	u8vec3 Color(115, 77, 38);
	int Width = Map.Width;
	int Height = Map.Height;
	Start += 100.0f;
	Start /= 200.0f;
	Start *= Width;
	End += 100.0f;
	End /= 200.0f;
	End *= Width;

	if (End.x < Start.x)
	{
		vec3 c = End; End = Start; Start = c;
	}
	float M;
	if (End.x == Start.x)
	{
		if (Start.z < End.z)
		{
			for (int z = Start.z; z < End.z; z++)
			{
				if (Map.Map[z*Width + int(Start.x) - 1] == u8vec4(Color, 255)) {
					return false;
				}
			}
		}
		else
		{
			/*if (End.z < Start.z)
			{
				vec3 c = End; End = Start; Start = c;
			}*/
			for (int z = End.z; z < Start.z; z++)
			{
				if (Map.Map[z*Width + int(Start.x) - 1] == u8vec4(Color, 255)) {
					return false;
				}
			}
		}
	}
	else if (((M = (End.z - Start.z) / (End.x - Start.x)) < 1) && M >= -1)
	{
		for (int x = 0; x < (End.x - Start.x); x++)
		{
			int Finalz = M * x + Start.z;
			int Finalx = x + Start.x;
			if (Finalz > 300 || Finalx > 300 || Finalx < 0 || Finalz < 0)
			{
				return false;
			}
			if (Map.Map[Finalz*Width + Finalx - 1] == u8vec4(Color, 255)) {
				return false;
			}
		}
	}
	else
	{
		M = 1.0f / M;
		if (End.z < Start.z)
		{
			vec3 c = End; End = Start; Start = c;
		}
		for (int z = 0; z < (End.z - Start.z); z++)
		{
			int Finalz = z + Start.z;
			int Finalx = M * z + Start.x;
			if (Finalz > 300 || Finalx > 300 || Finalx < 0 || Finalz < 0)
			{
				return false;
			}
			if (Map.Map[Finalz*Width + Finalx - 1] == u8vec4(Color, 255)) {
				return false;
			}
		}
	}
	return true;
}