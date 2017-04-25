#include "Loaded_Models.h"


ModelsCollection::ModelsCollection()
{
	//Models_Collection["Katarina"] = new KatarinaModel;
	//Models_Collection["Ground"] = new Ground;
	//Models_Collection["Sky"] = new SkyBox;
	//Models_Collection["Grass"] = new Grass(5);

	//Models["Lara"] = new Model("Collada/CartoonTree.dae");
	Models["Land"] = new Model("Map/Land2.dae", "Ground");
	Models["Land"]->AddTexture("Texture0", "Map/Grass/grass01_converted.jpg");
	Models["Land"]->AddTexture("Texture1", "Map/Brick/Mountain Tile.jpg");
	Models["Land"]->AddTexture("Texture2", "Map/MapPath.jpg");
	Models["Land"]->AddTexture("Texture3", "Map/Brick/brickwork-texture_converted.jpg");

	Models["Land"]->AddTexture("Texture4", "Map/Brick/brickwork_normal-map_converted.jpg");
	Models["Land"]->AddTexture("Texture5", "Map/Brick/brickwork-bump-water.jpg");
	Models["Land"]->AddTexture("Texture6", "Map/Brick/brickwork-bump-map_converted.jpg");
	Models["Land"]->AddTexture("Texture7", "Map/Grass/grass01_n_converted.jpg");
	Models["Land"]->AddTexture("Texture8", "Map/Grass/grass01_h_converted.jpg");

	Models["Water"] = new Model("Map/Sea.dae", "");
	Models["Water"]->AddTexture("Texture0", "Map/Water/waterDUDV.jpg");
	Models["Water"]->AddTexture("Texture1", "Map/Water/waterNormals.jpg");
	Models["Water"]->AddTexture("Texture2", "Map/Default Normal Map.jpg");

	Models["Collada"] = new Model("Collada/MineSweaper.dae", "");
	Models["Collada"]->AddTexture("Texture[0]", "Katarina/Katarina Glowing.bmp");
	Models["Collada"]->AddTexture("NormalMap[0]", "Katarina/katarina_base_normal.png");

	Models["Shop"] = new Model("Map/Shop.dae", "");
	Models["Shop"]->AddTexture("Texture[0]", "Katarina/Katarina Glowing.bmp");
	Models["Shop"]->AddTexture("NormalMap[0]", "Katarina/katarina_base_normal.png");

	Models["Sphere"] = new Model("Collada/sphere.dae", "");
	Models["Sphere"]->AddTexture("Texture[0]", "Katarina/Katarina Glowing.bmp");
	Models["Sphere"]->AddTexture("NormalMap[0]", "Katarina/katarina_base_normal.png");


	Models["Obstacle"] = new Model("Map/Grass.dae", "");
	Models["House"] = new Model("Collada/House.dae", "");
	//Models["House"]->AddTexture("Texture[0]", "Textures/196.jpg");
	//Models["House"]->AddTexture("NormalMap[0]", "Textures/196_norm.jpg");
	Models["House"]->AddTexture("Texture[0]", "Map/HeightMap/bricks2.jpg");
	Models["House"]->AddTexture("NormalMap[0]", "Map/HeightMap/bricks2_normal.jpg");
	Models["House"]->AddTexture("Dispose", "Map/HeightMap/bricks2_disp.jpg");

	Models["House1"] = new Model("Collada/Small_Building_1.dae", "");
	Models["House1"]->AddTexture("Texture[0]", "Collada/textures/Col Klein Haus_C.jpg");
	Models["House1"]->AddTexture("NormalMap[0]", "Collada/textures/Col Klein Haus_N.jpg");

	Models["Grass"] = new Model("Map/3DGrass.dae", "");
	Models["Grass"]->AddTexture("Texture[0]", "Map/3DGrass.png");
	Models["Grass"]->AddTexture("NormalMap[0]", "Textures/basicNormal.jpg");

	Models["Mine"] = new Model("Collada/Mine.dae", "");
	Models["Mine"]->AddTexture("Texture[0]", "Katarina/Katarina Glowing.bmp");
	Models["Mine"]->AddTexture("NormalMap[0]", "Katarina/katarina_base_normal.png");


	//	Models["cursor"] = new Model("Map/cursor.dae","");
	//Models2["Lara"]->LoadMesh("Collada/Lara_Croft.dae");


	//Models["Ground"] = new Model("Collada/ArmyPilot.dae");
	//Models["Sky"] = new Model("Collada/ArmyPilot.dae");
	//Models["Grass"] = new Model("Collada/ArmyPilot.dae");

	//Models_Collection["Soldier"] = new Model("Collada/ArmyPilot.dae");

}

Model * ModelsCollection::operator[](string i)
{
	if (Models.find(i) == Models.end())
	{
		throw invalid_argument("Model Name Does Not Exist");
	}
	return this->Models[i];
}
