#include "PRMalgorithm.h"



PRMalgorithm::PRMalgorithm()
{
}


PRMalgorithm::~PRMalgorithm()
{
}

map<vec3, map<vec3, float, bool(*)(const vec3&, const vec3&)>
	, bool(*)(const vec3&, const vec3&)>* PRMalgorithm::
	GeneratePoints(Stas::MinimapData Map,vec3& Source, vec3& Destination)
{
	srand((uint)time(NULL));
	const int MapScale = 100;
	const int MAX_DISTANCE = 100;
	const int MAX_POINTS = 50;
	int Width, Height;
	u8vec4* MapData = Map.Map;
	Width = Map.Width;
	Height = Map.Height;
	auto vec3Compare = [](const vec3& lhs, const vec3& rhs)->bool {
		if (lhs.x == rhs.x)
		{
			if (lhs.y == rhs.y)
				return lhs.z < rhs.z;
			return lhs.y < rhs.y;
		}
		return lhs.x < rhs.x;
	};
	auto Graph = new map<vec3, map<vec3, float, bool(*)(const vec3&, const vec3&)>
		, bool(*)(const vec3&, const vec3&)>(vec3Compare);
	
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
		(*Graph)[*i] = map<vec3, float, bool(*)(const vec3&, const vec3&)>(vec3Compare);
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
map<vec3, map<vec3, float, bool(*)(const vec3&, const vec3&)>
	, bool(*)(const vec3&, const vec3&)>* PRMalgorithm::
	GeneratePointsSelfFixing(Stas::MinimapData Map, vec3& Source, vec3& Destination)
{
	srand(uint(time(NULL)));
	const int MapScale = 100;
	const int MAX_DISTANCE = 5000;
	const int MAX_POINTS = 40;
	int Width, Height;
	u8vec4* MapData = Map.Map;
	Width = Map.Width;
	Height = Map.Height;
	auto vec3Compare = [](const vec3& lhs, const vec3& rhs)->bool {
		if (lhs.x == rhs.x)
		{
			if (lhs.y == rhs.y)
				return lhs.z < rhs.z;
			return lhs.y < rhs.y;
		}
		return lhs.x < rhs.x;
	};
	auto Graph = new map<vec3, map<vec3, float, bool(*)(const vec3&, const vec3&)>
		, bool(*)(const vec3&, const vec3&)>(vec3Compare);

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
		Points.push_back(vec3((rand() % (2 * MapScale)) - MapScale,
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
		(*Graph)[*i] = map<vec3, float, bool(*)(const vec3&, const vec3&)>(vec3Compare);
	}
	vector<map<vec3, float, bool(*)(const vec3&, const vec3&)>*> Paths(Points.size());




	for (auto i = Points.begin(); i != Points.end(); i++)
	{
		//map<vec3, int, bool(*)(const vec3&, const vec3&)> Paths(Stas::Maths::vec3Compare);
		for (auto j = i + 1; j != Points.end();)
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
	while (true)
	{
		// Create Graph by connections
		vector<pair<vec3, int>> GraphOrderedByConnections;
		// Fill with Graph current connections
		for (auto& v : *Graph)
		{
			GraphOrderedByConnections.push_back(make_pair(v.first, v.second.size()));
		}
		// Order graph by connections
		std::sort(GraphOrderedByConnections.begin(), GraphOrderedByConnections.end(),
			[](const pair<vec3, int>& lhs, const pair<vec3, int>& rhs)->bool {
			return lhs.second < rhs.second;
		});
		int ThreshHold = 0;
		// End Loop
		if (GraphOrderedByConnections.front().second > ThreshHold)
			break;
		for (auto& g : GraphOrderedByConnections)
		{
			if (g.second > ThreshHold)
			{
				break;
			}
			while (g.second <= ThreshHold)
			{
				vec3 FixingPoint;
				// Generate Points
				FixingPoint = vec3((rand() % (2 * MapScale)) - MapScale,
					0, (rand() % (2 * MapScale)) - MapScale);
				vec3 ConvertToMinimapCoords = FixingPoint;
				ConvertToMinimapCoords += float(MapScale);
				ConvertToMinimapCoords /= float(2 * MapScale);
				ConvertToMinimapCoords *= float(Width);
				if (MapData[int(ConvertToMinimapCoords.z)*Width + (int)ConvertToMinimapCoords.x] == u8vec4(115, 77, 38, 255))
				{
					// Point in obstacle, continue the loop as if nothing happened
					continue;
				}
			
				// connect Point to current node
				if (IsPathAvailable(Map, g.first, FixingPoint))
				{
					// Initialize Path with Graph node
					if ((*Graph).find(FixingPoint) == (*Graph).end())
					{
						(*Graph)[FixingPoint] = map<vec3, float, bool(*)(const vec3&, const vec3&)>(vec3Compare);
					}
					(*Graph)[g.first][FixingPoint] = glm::distance(g.first, FixingPoint);
					(*Graph)[FixingPoint][g.first] = glm::distance(g.first, FixingPoint);
					g.second++;
				}
				else continue;
				// Connect Points to the rest of the Graph
				for (auto i = Points.begin(); i != Points.end(); i++)
				{
					if (*i == g.first) continue;
					if (glm::distance(*i, FixingPoint) < MAX_DISTANCE)
					{
						if (IsPathAvailable(Map, *i, FixingPoint))
						{
							(*Graph)[*i][FixingPoint] = glm::distance(*i, FixingPoint);
							(*Graph)[FixingPoint][*i] = glm::distance(*i, FixingPoint);
						}
					}
				}
				Points.push_back(FixingPoint);
				// Assign points from start
			}
		}
	}
/*
	// Addition to PRM
	Order Graph by Edges per Points;
	Threshold = MIN_EDGES;
	do {
		// rand1() : gives random number between 0 and 1
		lambdaGetRandPoint = []()->(x, y) {
			(((2 * rand1()) - 1.0) * MAX_DISTANCE, ((2 * rand1()) - 1.0) * MAX_DISTANCE);
		};
		newPoint = lambdaGetRandPoint;

		while (Map[NewPoint] == obstacle)
			newPoint = lambdaGetRandPoint;
		Points <-newPoint;
	} while (Graph[i].size() < Threshold); // size of edges of point index `i`











										   // Connect Points
	for (i = 0; i < length of Points; i++)
	{
		for (j = i + 1; j < length of Points; j++)
		{
			Graph<-edge(Points[i], Points[j]);
			Graph<-edge(Points[j], Points[i]);
		}
	}
*/
	return Graph;
}
vector<vec3> PRMalgorithm::FoundPath(map<vec3, map<vec3, float, bool(*)(const vec3&, const vec3&)>
	, bool(*)(const vec3&, const vec3&)>* Map, vec3& Source, vec3& Destination)
{
	vector<vec3> Backtrack = Stas::Algorithms::Approximate::PathFinding::Dijkstra(*Map, Source, Destination);
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
			for (int z = (int)Start.z; z < (int)End.z; z++)
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
			for (int z = (int)End.z; z < (int)Start.z; z++)
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
			int Finalz = (int)(M * x) + (int)Start.z;
			int Finalx = x + (int)Start.x;
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
			int Finalz = z + (int)Start.z;
			int Finalx = (int)(M * z) + (int)Start.x;
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