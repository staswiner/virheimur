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
	GeneratePoints(vec3& Source, vec3& Destination)
{
	srand(time(NULL));
	auto Map = new map<vec3, map<vec3, int, bool(*)(const vec3&, const vec3&)>
		, bool(*)(const vec3&, const vec3&)>(Stas::Maths::vec3Compare);
	vector<vec3> Points;
	Points.push_back(Source);
	Points.push_back(Destination);

	const int MAX_DISTANCE = 400;
	const int MAX_POINTS = 200;
	for (int i = 0; i < MAX_POINTS; i++)
	{
		Points.push_back(vec3((rand() % 2000) - 1000, 
			(rand() % 2000) - 1000, (rand() % 2000) - 1000));
	}
	//vector<vec3> PointsZ(PointsX);
	//std::sort(PointsX.begin(), PointsX.end(), SortByX);
	//std::sort(PointsZ.begin(), PointsZ.end(), SortByZ);
	//for (auto i = PointsX.begin(); i!= PointsX.end(); i++)
	//{
	//	map<vec3, int, bool(*)(const vec3&, const vec3&)> Paths(Stas::Maths::vec3Compare);
	//	for (auto j = i; j!=PointsZ.end(); j++)
	//	{
	//		if (glm::distance(*i, *j) < MAX_DISTANCE)
	//			(Paths)[*j] = glm::distance(*i, *j);
	//		else
	//			break;
	//	}
	//	for (auto j = i; j!=PointsZ.begin(); j--)
	//	{
	//		if (glm::distance(*i, *j) < MAX_DISTANCE)
	//			(Paths)[*j] = glm::distance(*i, *j);
	//		else
	//			break;
	//	}
	//	(*Map)[*i] = Paths;
	//}
	vector<map<vec3, int, bool(*)(const vec3&, const vec3&)>*> Paths(Points.size());
	for (auto i = Points.begin(); i != Points.end(); i++)
	{
		(*Map)[*i] = map<vec3, int, bool(*)(const vec3&, const vec3&)>(Stas::Maths::vec3Compare);
	}
	for (auto i = Points.begin(); i != Points.end(); i++)
	{
		//map<vec3, int, bool(*)(const vec3&, const vec3&)> Paths(Stas::Maths::vec3Compare);
		for (auto j = i+1; j != Points.end();)
		{
			if (glm::distance(*i, *j) < MAX_DISTANCE)
			{
				(*Map)[*i][*j] = glm::distance(*i, *j);
				(*Map)[*j][*i] = glm::distance(*i, *j);
			//	j = Points.erase(j);
				j++;
			}
			else
			{
				j++;
			}
		}
	}
	return Map;
}

vector<vec3>* PRMalgorithm::FoundPath(map<vec3, map<vec3, int, bool(*)(const vec3&, const vec3&)>
	, bool(*)(const vec3&, const vec3&)>* Map, vec3& Source, vec3& Destination)
{
	vector<vec3>* Backtrack = Stas::Maths::Dijkstra(*Map, Source, Destination);
	return Backtrack;
}
