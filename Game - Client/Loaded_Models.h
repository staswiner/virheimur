#pragma once
#include <stdexcept>
#include <vector>
#include <map>
#include "Models_Header.h"
#include "ExistingMesh.h"
using namespace std;


class ModelsCollection
{
private:
	ModelsCollection();
	ModelsCollection(ModelsCollection const&) = delete;
	void operator=(ModelsCollection const&) = delete;

	map<string, Model*> Models;
	static ModelsCollection instance;

public:
	static ModelsCollection& Instance()
	{
		static ModelsCollection instance;
		return instance;
	}
	~ModelsCollection(){}

	Model* operator[](string i);


};
