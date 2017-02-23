#pragma once
#include "Maths.h"
#include "Minimap.h"
#include <stdlib.h>
#include <time.h>
class PRMalgorithm
{
public:
	PRMalgorithm();
	~PRMalgorithm();
	map<vec3, map<vec3, int, bool(*)(const vec3&, const vec3&)>
		, bool(*)(const vec3&, const vec3&)>* GeneratePoints(Stas::MinimapData Map,vec3& Source, vec3& Destination);
	map<vec3, map<vec3, int, bool(*)(const vec3&, const vec3&)>, bool(*)(const vec3&, const vec3&)>* GeneratePointsSelfFixing(Stas::MinimapData Map, vec3 & Source, vec3 & Destination);
	vector<vec3> FoundPath(map<vec3, map<vec3, int, bool(*)(const vec3&, const vec3&)>
		, bool(*)(const vec3&, const vec3&)>*, vec3& Source, vec3& Destination);
	bool IsPathAvailable(Stas::MinimapData Map, vec3 s, vec3 e);
};

