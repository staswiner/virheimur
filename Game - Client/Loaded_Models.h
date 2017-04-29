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

class Effects2DCollection {
private:
	Effects2DCollection();
	Effects2DCollection(Effects2DCollection const&) = delete;
	void operator=(Effects2DCollection const&) = delete;

	map<string, Model*> Models;
	static Effects2DCollection instance;

public:
	static Effects2DCollection& Instance()
	{
		static Effects2DCollection instance;
		return instance;
	}
	~Effects2DCollection() {}

	Model* operator[](string i);

};
