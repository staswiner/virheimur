#pragma once
#include <functional>
#include <chrono>
#include "json.hpp"
#include "UIElement.h"
#include "FrameData.h"
#include "glm\glm\vec3.hpp"
#include "Model.h"
#include "Loaded_Models.h"
#include "Default.h"
#include "glm/glm/gtc/quaternion.hpp"
#include "Camera.h"
using namespace nlohmann;
using namespace chrono;
using namespace glm;
using namespace std;

class GameObject
{
public:
	struct Stats{
		uint Level;
		uint Exp;
		uint MaxHp;
		uint Hp;
		uint Mp;
		uint MovementSpeed = 10;
		uint Gold;
	};

	class Unit_Data
	{
	public:
		Unit_Data();
		~Unit_Data();
		mat4 GetModelMatrix();
		void RotateByNormal(vec3 NormalAngles);
		// When destination is chosen, StartPointTime is updated with the action time. 
		// Later Calculates the route based on this factor and walking speed
	public:
		vec3 StartPoint;
		vec3 Position;
		vec3 Velocity; // Direction * Value
		vec3 Acceleration; // Direction * Value

		vec3 SurfaceNormal = vec3(0,1,0);
		vec3 Rotation;

		bool HasPhysics;
		vec3 TotalForceVector;
		vec3 FrictionVector;
		vec3 MomentumVelocity;
		vector<vec3> ForceVectors;
		float bounceFactor = 0.9f;
		vector<vec3> Path;
		vec3 Destination;
		bool PathChanged = false;
		milliseconds StartPointTime;
		Model* Model_Data;
		unsigned int action;
	};
	struct SceneData {
		mat4 ProjectionMatrix;
		mat4 ViewMatrix;
		vec3 CameraPos;
		mat4 Light_Matrix;
		vec3 Light_Pos;
	};
	GameObject();
	GameObject(Unit_Data, string Username);
	~GameObject();
	Unit_Data& GetUnitData();
	virtual void Draw(SceneData& sceneData);
	void DrawShadow(mat4 & ProjectionMatrix, mat4 & ViewMatrix);
	void DrawOutline(mat4 & ProjectionMatrix, mat4 & ViewMatrix, vec3 Color);
	void DrawUI(mat4& Projection, mat4& View);
	void LoadInterface();
	void UpdateUnitData(Unit_Data uData);
	virtual void ReloadShader();
	virtual void ReloadShader(Shader::ImageType);
	json GetJson();
	json GetStructureJson();
	Stats stats;
	milliseconds TimeDelta;
	Unit_Data unit_Data;
	// Controls
	enum class controls
	{
		Manual,
		Direct,
		Script,
		Mouse
	}; 
	enum class movements
	{
		Ground,
		Plane, 
		Aero
	};
	movements movement = movements::Ground;
	controls control = controls::Manual;
	
	// AI preparations
	function<void(GameObject&)> script;
	void* GetMemoryData(string VarName);
	void SetMemoryData(string VarName, void* data, size_t);
	bool disablePathing = false;
	// TO remove variable
	bool PathingStarted = false;
	bool LongPath = true;
	// Collision library
	rp3d::CollisionBody* collisionBody;
	void CreateCollisionBody(rp3d::CollisionWorld& world);
	void UpdateCollisionBody(rp3d::CollisionWorld& world);

private:
	map<string, void*> MemoryBlock;
	map<string, string> MemoryTypeTable;
	string IpAddress;
	UIElement* UIroot;
	int Type;
};

typedef GameObject::Unit_Data Unit_Data;

class PlayerRepository
{
public:
	PlayerRepository() {}
	~PlayerRepository() { Players.clear(); }
	GameObject*& operator[](string Key);
	GameObject* operator[](string Key) const;
	void Erase(string Key);
	map<string, GameObject*>::iterator begin();
	map<string, GameObject*>::iterator end();
	void clear();

private:
	mutable map<string, GameObject*> Players;
};

class Player : public GameObject
{

};

class Ground : public GameObject
{

};

class SkyBox : public GameObject
{
public:
	SkyBox() {}
	~SkyBox() {}

	void Initialize() {
		this->DrawObject.InitTexture();
	}
	void Draw(SceneData& sceneData) {
		this->DrawObject.DrawModel();
	}
	void ReloadShader();
private:
	SkyBox_Graphics DrawObject;
};

class Effect2D : public GameObject {
public:
	enum class ModelType
	{
		Square,
		Cylinder,
		Cone
	};
	Effect2D(string ImagePath);
	Effect2D();
	~Effect2D();

	void Draw(SceneData& sceneData);
	void ReloadShader();
private:
	ImageLoader* image;
	Shader* shader;
};