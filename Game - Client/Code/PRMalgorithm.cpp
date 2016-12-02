#include "PRMalgorithm.h"



PRMalgorithm::PRMalgorithm()
{
}


PRMalgorithm::~PRMalgorithm()
{
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
	const int MAX_DISTANCE = 500;
	const int MAX_POINTS = 200;
	for (int i = 0; i < MAX_POINTS; i++)
	{
		Points.push_back(vec3((rand() % 2000) - 1000, 
			(rand() % 2000) - 1000, (rand() % 2000) - 1000));
	}
	for (auto i = Points.begin(); i!= Points.end(); i++)
	{
		map<vec3, int, bool(*)(const vec3&, const vec3&)> Paths(Stas::Maths::vec3Compare);
		for (auto j = i; j!=Points.end(); j++)
		{
			if (glm::distance(*i, *j) < MAX_DISTANCE)
				(Paths)[*j] = glm::distance(*i, *j);
		}
		for (auto j = i; j!=Points.begin(); j--)
		{
			if (glm::distance(*i, *j) < MAX_DISTANCE)
				(Paths)[*j] = glm::distance(*i, *j);
		}
		(*Map)[*i] = Paths;
	}

	return Map;
}

vector<vec3>* PRMalgorithm::FoundPath(map<vec3, map<vec3, int, bool(*)(const vec3&, const vec3&)>
	, bool(*)(const vec3&, const vec3&)>* Map, vec3& Source, vec3& Destination)
{
	vector<vec3>* Backtrack = Stas::Maths::Dijkstra(*Map, Source, Destination);
	return Backtrack;
}
