#pragma once
#include "json.hpp"
#include "GameObject.h"
#include "Effect.h"
#include "AIObjects.h"
#include "Level.h"
#include <string>
#include <vector>

using namespace std;
using namespace nlohmann;


class OfflineDataObject
{
private:
	OfflineDataObject() {
		
	}
	OfflineDataObject(OfflineDataObject const&) = delete;
	void operator=(OfflineDataObject const&) = delete;

	static OfflineDataObject instance;

public:
	~OfflineDataObject() {}
	static OfflineDataObject& Instance()
	{
		static OfflineDataObject instance;
		return instance;
	}

	vector<Effect> Effects;
	vector<vec3>* Path;
	Level level;

	bool RouteChanged = false;
};