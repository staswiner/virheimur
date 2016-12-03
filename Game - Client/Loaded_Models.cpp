#include "Loaded_Models.h"



staticLoaded_Models::staticLoaded_Models()
{
//	initialize_Models();
	//	enum Models_Names { e_KatarinaModel, e_MinionModel , e_MapModel, e_SkyBox, e_2D_IMAGE };
}


staticLoaded_Models::~staticLoaded_Models()
{
}
void staticLoaded_Models::initialize_Models()
{
	//Models_Collection["Katarina"] = new KatarinaModel;
	//Models_Collection["Ground"] = new Ground;
	//Models_Collection["Sky"] = new SkyBox;
	//Models_Collection["Grass"] = new Grass(5);
	
	//Models["Lara"] = new Model("Collada/CartoonTree.dae");
	Models["Collada"] = new Model("Collada/astroBoy_walk_Maya.dae");
	//Models2["Lara"]->LoadMesh("Collada/Lara_Croft.dae");


	//Models["Ground"] = new Model("Collada/ArmyPilot.dae");
	//Models["Sky"] = new Model("Collada/ArmyPilot.dae");
	//Models["Grass"] = new Model("Collada/ArmyPilot.dae");

	//Models_Collection["Soldier"] = new Model("Collada/ArmyPilot.dae");

	
}
/*
``Bind Models to Graphic Card`` (in main thread)
*/
void staticLoaded_Models::Bind_Texture_To_Models()
{
	// not working
	//for each (pair<string,Model*> model in Models)
	//{
	//	model.second->InitTexture();
	////	Loader::LoadShaders(model->vShader.c_str(), model->fShader.c_str());
	//}
}
//Loader* staticLoaded_Models::getModelData(const string Model_Code)
//{
//	return Models_Collection[Model_Code];
//}
Model* staticLoaded_Models::operator[](string i)
{
	if (Models.find(i) == Models.end())
		return nullptr;
	return Models[i];
}
/**Static Class Cover for Loaded Models**/
staticLoaded_Models Loaded_Models::sLoaded_Models;
Loaded_Models::Loaded_Models()
{

}
Loaded_Models::~Loaded_Models()
{

}
void Loaded_Models::initialize_Models()
{
	sLoaded_Models.initialize_Models();
}
void Loaded_Models::Bind_Texture_To_Models()
{
	sLoaded_Models.Bind_Texture_To_Models();
}
Model* Loaded_Models::operator[](string i)
{
	return sLoaded_Models[i];
}
//Loader* Loaded_Models::getModelData(const string Model_Code)
//{
//	return sLoaded_Models.getModelData(Model_Code);
//}