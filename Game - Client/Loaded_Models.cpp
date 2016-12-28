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
	Models["Land"] = new Model("Map/Land2.dae","Ground");
	Models["Land"]->AddTexture("Texture0", "Map/Grass Tile.jpg");
	Models["Land"]->AddTexture("Texture1", "Map/Mountain Tile.jpg");
	Models["Land"]->AddTexture("Texture2", "Map/MapPath.jpg");
	Models["Land"]->AddTexture("Texture3", "Map/brickwork-texture_converted.jpg");
	//Models["Land"]->AddTexture("Texture3", "Map/TestTile.jpg");
	Models["Land"]->AddTexture("Texture4", "Map/brickwork_normal-map_converted.jpg");
	Models["Land"]->AddTexture("Texture5", "Map/brickwork-bump-map_converted.jpg");

	Models["Collada"] = new Model("Collada/Robot.dae", "");
	Models["Collada"]->AddTexture("Texture0","Katarina/Katarina Glowing.bmp");
	Models["Obstacle"] = new Model("Map/Grass.dae", "");
//	Models["cursor"] = new Model("Map/cursor.dae","");
	//Models2["Lara"]->LoadMesh("Collada/Lara_Croft.dae");


	//Models["Ground"] = new Model("Collada/ArmyPilot.dae");
	//Models["Sky"] = new Model("Collada/ArmyPilot.dae");
	//Models["Grass"] = new Model("Collada/ArmyPilot.dae");

	//Models_Collection["Soldier"] = new Model("Collada/ArmyPilot.dae");

	
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
Model* Loaded_Models::operator[](string i)
{
	return sLoaded_Models[i];
}
//Loader* Loaded_Models::getModelData(const string Model_Code)
//{
//	return sLoaded_Models.getModelData(Model_Code);
//}

void Loaded_ModelsST::initialize_Models()
{
}

Model * Loaded_ModelsST::operator[](string i)
{
	return nullptr;
}
