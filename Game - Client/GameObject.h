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
#include "Music.h"
#include "reactphysics3d.h"
using namespace nlohmann;
using namespace chrono;
using namespace glm;
using namespace std;
enum class ScriptState
{
	Done,
	OnGoing,
	Error
};
template<typename T> class Script;
template<typename Ret, typename... Args>
class Script<Ret(Args...)>
{
public:
	Ret operator()(Args... args)
	{
		if (script == nullptr) return static_cast<Ret>(0);
		return script(args...);
	}
	//bool Run(Args... args) { return script(std::forward<Args...>(args)); };
	void* GetMemoryData(string VarName) {
		if (MemoryBlock.find(VarName) == MemoryBlock.end())
		{
			return nullptr;
		}
		else
		{
			float number = *reinterpret_cast<float*>(MemoryBlock[VarName]);
			return MemoryBlock[VarName];
		}
	}
	void SetMemoryData(string VarName, void* data, size_t s) {
		float number = *reinterpret_cast<float*>(data);
		void * AllocationData = malloc(sizeof(s));
		memcpy(AllocationData, data, s);
		number = *reinterpret_cast<float*>(AllocationData);
		void * ptr = MemoryBlock[VarName];
		if (MemoryBlock.find(VarName) != MemoryBlock.end())
		{

			//float number = *reinterpret_cast<float*>(MemoryBlock[VarName]);
			MemoryBlock.erase(VarName);
		}
		MemoryBlock[VarName] = AllocationData;
	}
	void ResetMemoryData() {
		MemoryBlock.clear();
	}
	void Create(std::function<Ret(Args...)> script) {
		this->Clear();
		this->script = script;
	}
	void Clear() { this->script = nullptr; MemoryBlock.clear(); }
	function<Ret(Args...)> script;
private:
	map<string, void*> MemoryBlock;
	map<string, string> MemoryTypeTable;
};
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
		vec3 Position, PrevPosition;
		vec3 Velocity; // Direction * Value
		vec3 Acceleration; // Direction * Value

		vec3 SurfaceNormal = vec3(0,1,0);
		vec3 Rotation;

		bool HasPhysics;
		vec3 TotalForceVector;
		vec3 FrictionVector;
		vec3 MomentumVelocity;
		vector<vec3> ForceVectors;
		vector<vec3> InputForceVectors;
		float bounceFactor = 0.0f;
		vector<vec3> Path;
		vec3 Destination;
		bool PathChanged = false;
		milliseconds StartPointTime;
		Model* Model_Data;
		Shader* MainShader;
		unsigned int action;
	};
	struct SceneData {
		mat4 ProjectionMatrix;
		mat4 ViewMatrix;
		vec3 CameraPos;
		mat4 Light_Matrix;
		vec3 Light_Pos;
	};
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
	string Name;
	Stats stats;
	Unit_Data unit_Data;
	bool Disabled = false;
	movements movement = movements::Ground;
	controls control = controls::Manual;

	GameObject();
	GameObject(Unit_Data, string Username);
	~GameObject();
	Unit_Data& GetUnitData();
	virtual void Draw(SceneData& sceneData) = 0;
	virtual void ReloadShader() = 0;
	virtual void ReloadShader(Shader::ImageType) = 0;
	void DrawShadow(mat4 & ProjectionMatrix, mat4 & ViewMatrix);
	void DrawOutline(mat4 & ProjectionMatrix, mat4 & ViewMatrix, vec3 Color);
	void DrawUI(mat4& Projection, mat4& View);
	void LoadInterface();
	void UpdateUnitData(Unit_Data uData);
	void CreateShader(Shader::ImageType imageType);
	json GetJson();
	json GetStructureJson();

	
	// AI preparations
	Script<ScriptState(GameObject&)> script;

	// Collision library
	rp3d::CollisionBody* collisionBody;
	void CreateCollisionBody(rp3d::CollisionWorld& world);
	void UpdateCollisionBody(rp3d::CollisionWorld& world);
	map<string, Music*> Soundtracks;

private:
	UIElement* UIroot;
	int Type;
};

typedef GameObject::Unit_Data Unit_Data;

class SimpleObject : public GameObject
{
public:
	SimpleObject()
	{
	}
	~SimpleObject()
	{
	}

	void Draw(SceneData& sceneData);
	void ReloadShader();
	void ReloadShader(Shader::ImageType);

private:

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
	void ReloadShader(Shader::ImageType) { exception("Illegal function use"); }
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
	void ReloadShader(Shader::ImageType) { exception("Illegal function use"); }
private:
	ImageLoader* image;
	Shader* shader;
};

class Normals : public GameObject
{
public:
	static Normals& Instance()
	{
		static Normals instance;
		return instance;
	}
	void Draw();
	void Draw(SceneData&) {}
	void ReloadShader();
	void ReloadShader(Shader::ImageType) { exception("Illegal function use"); }
	vector<vec3> Vertices;
	~Normals();
private:
	static Normals instance;
	Normals();
	GLuint VAO;
	GLuint VBO[5];
		
};
