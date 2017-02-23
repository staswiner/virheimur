#include "Player.h"


Player::Player()
{
	this->stats.MovementSpeed = 100;
	this->stats.Hp = 500;
	this->stats.MaxHp = 1000;
	LoadInterface(); 
}

Player::Player(Unit_Data unit_Data,string Username)
{
	this->unit_Data = unit_Data;
	this->Username = Username;
	this->stats.MovementSpeed = 100;
	this->stats.Hp = 500;
	this->stats.MaxHp = 1000;
	LoadInterface();
}


Player::~Player()
{
	UIroot->Destroy();
}

Unit_Data& Player::GetUnitData()
{
	return this->unit_Data;
}

void Player::Draw(mat4& ProjectionMatrix, mat4& ViewMatrix)
{
	Mouse mouse;
	// Model
	Unit_Data& ud = this->unit_Data;
	vec3 position = ud.GetPosition();
	Loaded_Models loaded_Models;
#pragma region Mathematics
	mat4 ModelMatrix;
	ModelMatrix = glm::translate(ModelMatrix, position);
	ModelMatrix = glm::rotate(ModelMatrix, ud.Rotation.y, vec3(0, 1, 0));
	mat4 WVM = ProjectionMatrix * ViewMatrix * ModelMatrix;
#pragma endregion Mathematics
	ShaderBuilder::LoadShader(Shader::At("Animation"))->
		Add_mat4("WVM", WVM).
		Add_bool("isAnimated", true).
		Add_float("Texelation", 1.0f).
		Add_textures(loaded_Models["Collada"]->Textures);
	loaded_Models["Collada"]->Draw();

}
void Player::DrawShadow(mat4& ProjectionMatrix, mat4& ViewMatrix)
{
	Mouse mouse;
	// Model
	Unit_Data& ud = this->unit_Data;
	vec3 position = ud.GetPosition();
	Loaded_Models loaded_Models;
#pragma region Mathematics
	mat4 ModelMatrix;
	ModelMatrix = glm::translate(ModelMatrix, position);
	ModelMatrix = glm::rotate(ModelMatrix, ud.Rotation.y, vec3(0, 1, 0));
	mat4 WVM = ProjectionMatrix * ViewMatrix * ModelMatrix;
#pragma endregion Mathematics
	ShaderBuilder::GetCurrentProgram()->
		Add_mat4("WVM", WVM).
		Add_bool("isAnimated", true).
		Add_float("Texelation", 1.0f).
		Add_textures(loaded_Models["Collada"]->Textures);
	loaded_Models["Collada"]->Draw();

}
void Player::DrawOutline(mat4& ProjectionMatrix, mat4& ViewMatrix, vec3 Color)
{
	Mouse mouse;
	// Model
	Unit_Data& ud = this->unit_Data;
	vec3 position = ud.GetPosition();
	Loaded_Models loaded_Models;
#pragma region Mathematics
	mat4 ModelMatrix;
	ModelMatrix = glm::translate(ModelMatrix, position);
	ModelMatrix = glm::rotate(ModelMatrix, ud.Rotation.y, vec3(0, 1, 0));
	ModelMatrix = glm::scale(ModelMatrix, vec3(1.03f));
	mat4 WVM = ProjectionMatrix * ViewMatrix * ModelMatrix;
#pragma endregion Mathematics
	ShaderBuilder::LoadShader(Shader::At("Color"))->
		Add_mat4("WVM", WVM).
		Add_bool("isAnimated", true).
		Add_vec3("Color", Color);
	loaded_Models["Collada"]->Draw();

}

void Player::DrawUI(mat4 & ProjectionMatrix, mat4 & ViewMatrix)
{
#pragma region Declarations
	Mouse mouse;
	mat4 ModelMatrix;
	Unit_Data& ud = this->unit_Data;
	vec3 position = ud.GetPosition();
#pragma endregion Declarations
	ModelMatrix = glm::translate(ModelMatrix, position);
	ModelMatrix = glm::rotate(ModelMatrix, ud.Rotation.y, vec3(0, 1, 0));
	mat4 WVM = ProjectionMatrix * ViewMatrix * ModelMatrix;
	// HP bar
	float x = mouse.GetWindowSize().x / 2.0f;
	float y = mouse.GetWindowSize().y / 2.0f;
	vec4 TextPosition = WVM * vec4(0, 0, 0, 1);
	TextPosition /= TextPosition.w;
	vec2 TextCoords = vec2(TextPosition.x * x + x, -TextPosition.y * y + y);
	UIElement* EmptyHPBar = UIroot->GetUIElement("EmptyHPBar");
	UIElement* FullHPBar = UIroot->GetUIElement("FullHPBar");
	EmptyHPBar->TopLeft = TextCoords + vec2(-30, -30);
	EmptyHPBar->SetByTrueSize();

	FullHPBar->TopLeft = TextCoords + vec2(-29, -29);
	FullHPBar->BotRight = vec2(FullHPBar->TopLeft.x + (this->stats.Hp)/float(this->stats.MaxHp)*FullHPBar->TrueSize.x
		,FullHPBar->TopLeft.y+FullHPBar->TrueSize.y);

	UIroot->Draw();

}

void Player::LoadInterface()
{
	vec2 Position;
	UIroot = new UIElement("Root", "");

	UIElement* EmptyHPBar = new UIElement("EmptyHPBar", "Interface/EmptyHPBar.png");
	Position = vec2(10, 80);
	EmptyHPBar->TopLeft = Position;
	EmptyHPBar->SetByTrueSize(Position);
	UIroot->AppendChild(EmptyHPBar);

	UIElement* FullHPBar = new UIElement("FullHPBar", "Interface/FullHPBar.png");
	Position = vec2(10, 80);
	FullHPBar->TopLeft = Position;
	FullHPBar->SetByTrueSize(Position);
	UIroot->AppendChild(FullHPBar);


}

void Player::UpdateUnitData(Unit_Data uData)
{
	this->unit_Data.SetDestination(uData.GetPosition());
}

json Player::GetJson()
{
	json JPlayer;
	JPlayer["x"] = this->unit_Data.StartPoint.x;
	JPlayer["y"] = this->unit_Data.StartPoint.y;
	JPlayer["z"] = this->unit_Data.StartPoint.z;
	JPlayer["Destx"] = this->unit_Data.Destination.x;
	JPlayer["Desty"] = this->unit_Data.Destination.y;
	JPlayer["Destz"] = this->unit_Data.Destination.z;
	for (int i = 0; i < this->unit_Data.Path.size(); i++)
	{
		JPlayer["Path"][i]["x"] = this->unit_Data.Path[i].x;
		JPlayer["Path"][i]["y"] = this->unit_Data.Path[i].y;
		JPlayer["Path"][i]["z"] = this->unit_Data.Path[i].z;
	}
	//JPlayer["Path"] = this->unit_Data.Path;
	//JPlayer["Hp"] = this->stats.Hp;
	//JPlayer["MaxHp"] = this->stats.MaxHp;
	JPlayer["StartTime"] = this->unit_Data.StartPointTime.count();
	JPlayer["IpAddress"] = this->IpAddress;
	JPlayer["Username"] = this->Username;
	return JPlayer;
}

int Player::GetType()
{
	return this->Type;
}

Player *& PlayerRepository::operator[](string Key)
{
	if (this->Players.find(Key) == this->Players.end())
	{
		this->Players[Key] = new Player();
		return this->Players[Key];
	}
	else
	{
		return this->Players[Key];
	}
}

Player * PlayerRepository::operator[](string Key) const
{
	if (this->Players.find(Key) == this->Players.end())
	{
		this->Players[Key] = new Player();
		return this->Players[Key];
	}
	else
	{
		return this->Players[Key];
	}
}

void PlayerRepository::Erase(string Key)
{
	this->Players.erase(Key);
}

map<string, Player*>::iterator PlayerRepository::begin()
{
	return this->Players.begin();
}

map<string, Player*>::iterator PlayerRepository::end()
{
	return this->Players.end();
}

void PlayerRepository::clear()
{
	for (auto p : Players)
	{
		delete p.second;
	}
	Players.clear();
}
