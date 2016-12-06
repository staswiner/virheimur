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

	const int MAX_DISTANCE = 50;
	const int MAX_POINTS = 400;
	for (int i = 0; i < MAX_POINTS; i++)
	{
		Points.push_back(vec3((rand() % 2000) - 1000, 
			(rand() % 2000) - 1000, (rand() % 2000) - 1000));
	}
	for (auto i = Points.begin(); i != Points.end(); i++)
	{
		(*Map)[*i] = map<vec3, int, bool(*)(const vec3&, const vec3&)>(Stas::Maths::vec3Compare);
	}
	/*******************/
	std::sort(Points.begin(), Points.end(), SortByX);
	for (auto i = Points.begin(); i != Points.end(); i++)
	{
		map<vec3, int, bool(*)(const vec3&, const vec3&)> Paths(Stas::Maths::vec3Compare);
		for (auto j = i + 1; j != Points.end();)
		{
			if (abs(i->x - j->x) < MAX_DISTANCE)
			{
				(*Map)[*i][*j] = glm::distance(*i, *j);
				(*Map)[*j][*i] = glm::distance(*i, *j);
				j++;
			}
			else
			{
				break;
			}
		}
	}
	std::sort(Points.begin(), Points.end(), SortByZ);
	for (auto i = Points.begin(); i != Points.end(); i++)
	{
		map<vec3, int, bool(*)(const vec3&, const vec3&)> Paths(Stas::Maths::vec3Compare);
		for (auto j = i + 1; j != Points.end();)
		{
			if (abs(i->z - j->z) < MAX_DISTANCE)
			{
				(*Map)[*i][*j] = glm::distance(*i, *j);
				(*Map)[*j][*i] = glm::distance(*i, *j);
				j++;
			}
			else
			{
				break;
			}
		}
	}
	
	/***********/
	//vector<map<vec3, int, bool(*)(const vec3&, const vec3&)>*> Paths(Points.size());
	//
	//
	//
	//
	//for (auto i = Points.begin(); i != Points.end(); i++)
	//{
	//	//map<vec3, int, bool(*)(const vec3&, const vec3&)> Paths(Stas::Maths::vec3Compare);
	//	for (auto j = i+1; j != Points.end();)
	//	{
	//		if (glm::distance(*i, *j) < MAX_DISTANCE)
	//		{
	//			(*Map)[*i][*j] = glm::distance(*i, *j);
	//			(*Map)[*j][*i] = glm::distance(*i, *j);
	//		//	j = Points.erase(j);
	//			j++;
	//		}
	//		else
	//		{
	//			j++;
	//		}
	//	}
	//}
	return Map;
}

vector<vec3>* PRMalgorithm::FoundPath(map<vec3, map<vec3, int, bool(*)(const vec3&, const vec3&)>
	, bool(*)(const vec3&, const vec3&)>* Map, vec3& Source, vec3& Destination)
{
	vector<vec3>* Backtrack = Stas::Maths::Astar(*Map, Source, Destination);
	return Backtrack;
}
