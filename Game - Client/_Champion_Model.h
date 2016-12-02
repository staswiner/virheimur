#pragma once
#include "Loader.h"
class KatarinaModel : public Obj_Bmp_Loader
{
public:
	KatarinaModel();
	~KatarinaModel();
	virtual void DrawModel(mat4&, mat4&, mat4&, GLuint, mat4& LightView, Shader*, unsigned int);
	virtual void DrawModelGaussic(mat4& PerspectiveMat, mat4& ViewMat, mat4& ModelMat, Shader& shader);
	void Explode();
	void Recover_Explosion();
private:
	float m_Time;
	const float m_GForce;
	float m_GSpeed;
	float m_GPosition;
};

