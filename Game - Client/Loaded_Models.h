#pragma once
#include <stdexcept>
#include <vector>
#include <map>
#include "Models_Header.h"
#include "ExistingMesh.h"
using namespace std;


class ModelsCollection
{
public:
	static ModelsCollection& getInstance()
	{
		static ModelsCollection Instance;
		return Instance;
	}
	ModelsCollection(ModelsCollection const&) = delete;
	void operator=(ModelsCollection const&) = delete;
	~ModelsCollection(){}

	Model* operator[](string i);
private:
	ModelsCollection();
	//Loader* getModelData(const string Model_Code);
	map<string, Model*> Models;

public:
	static ModelsCollection Instance;


};
