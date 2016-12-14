#pragma once
#include <vector>
#include <map>
#include "Models_Header.h"
#include "ExistingMesh.h"
using namespace std;
class staticLoaded_Models
{
public:
	staticLoaded_Models();
	~staticLoaded_Models();
	void initialize_Models();
	Model* operator[](string i);
	//Loader* getModelData(const string Model_Code);
	//Model* GetModelData(const string Model_Code);
	enum Models_Names { e_KatarinaModel, e_MinionModel, e_MapModel, e_SkyBox, e_2D_IMAGE, e_Soldier };
private:
	//map<string,Loader*> Models_Collection;
	map<string, Model*> Models;
	map<string, SkinnedMesh*> Models2;


};

class Loaded_Models
{
public:
	Loaded_Models();
	~Loaded_Models();
	void initialize_Models();
	Model* operator[](string i);
	//Loader* getModelData(const string Model_Code);
	enum Models_Names { e_KatarinaModel, e_MinionModel, e_MapModel, e_SkyBox, e_2D_IMAGE };
public:
	static staticLoaded_Models sLoaded_Models;

	
};


class Loaded_ModelsST
{
public:
	static Loaded_ModelsST& getInstance()
	{
		static Loaded_ModelsST Instance;
		return Instance;
	}
	Loaded_ModelsST(Loaded_ModelsST const&) = delete;
	void operator=(Loaded_ModelsST const&) = delete;
private:
	Loaded_ModelsST() {}
	~Loaded_ModelsST(){}
	void initialize_Models();
	Model* operator[](string i);
	//Loader* getModelData(const string Model_Code);
	enum Models_Names { e_KatarinaModel, e_MinionModel, e_MapModel, e_SkyBox, e_2D_IMAGE };
public:
	static Loaded_ModelsST Instance;


};
