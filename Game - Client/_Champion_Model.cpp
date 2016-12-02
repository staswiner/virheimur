#include "_Champion_Model.h"



KatarinaModel::KatarinaModel()
	:m_GForce(9.98f/100.0f),
	Obj_Bmp_Loader(/*"Katarina/Katarina.obj"*/"LowPoly/tree.obj", "Katarina/Katarina Glowing.bmp", "Katarina/katarina_base_normal.png")
{
	Recover_Explosion();
}
KatarinaModel::~KatarinaModel()
{

}
void KatarinaModel::DrawModel(mat4& PerspectiveMat, mat4& ViewMat, mat4& ModelMat, GLuint shadowMap, mat4& LightView, Shader* a_Shader, uint)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, shadowMap);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, Shine);

	//use program
	//glUseProgram(programID);
	Shader *l_Shader;
	if (a_Shader == NULL)
		l_Shader = &shader;
	else
		l_Shader = a_Shader;
	l_Shader->Use();
	// uniform textures
	glUniform1i(glGetUniformLocation(l_Shader->ProgramID, "ourTexture"), 0);
	glUniform1i(glGetUniformLocation(l_Shader->ProgramID, "ourShadow"), 1);
	glUniform1i(glGetUniformLocation(l_Shader->ProgramID, "ourShine"), 2);

	
	glUniform1f(glGetUniformLocation(l_Shader->ProgramID, "GravityHeight"), m_GPosition / 100.0f);
	glUniform1f(glGetUniformLocation(l_Shader->ProgramID, "time"), m_Time /20.0f);
	// uniform matrixes
	glUniformMatrix4fv(glGetUniformLocation(l_Shader->ProgramID, "model")
		, 1, GL_FALSE, value_ptr(ModelMat));
	glUniformMatrix4fv(glGetUniformLocation(l_Shader->ProgramID, "view")
		, 1, GL_FALSE, value_ptr(ViewMat));
	glUniformMatrix4fv(glGetUniformLocation(l_Shader->ProgramID, "projection")
		, 1, GL_FALSE, value_ptr(PerspectiveMat));
	mat4 WorldSpace = PerspectiveMat * ViewMat * ModelMat;
	glUniformMatrix4fv(glGetUniformLocation(l_Shader->ProgramID, "worldSpace")
		, 1, GL_FALSE, value_ptr(WorldSpace));
	glUniformMatrix4fv(glGetUniformLocation(l_Shader->ProgramID, "lightSpaceMatrix")
		, 1, GL_FALSE, glm::value_ptr(LightView));
	Camera camera;

	// uniform variables
	glUniform1f(glGetUniformLocation(l_Shader->ProgramID, "AmbientStrength"), 1.0f);
	glUniform3f(glGetUniformLocation(l_Shader->ProgramID, "lightPos"), 0.0f, 20.0f, 0.0f);
	glUniform3fv(glGetUniformLocation(l_Shader->ProgramID, "cameraPos"), 1, glm::value_ptr(camera.GetCameraPosition()));




	// Draw container
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, Vertices_Amount);
	glBindVertexArray(0);
}
void KatarinaModel::DrawModelGaussic(mat4& PerspectiveMat, mat4& ViewMat, mat4& ModelMat, Shader& shader)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, Shine);

	shader.Use();
	// uniform textures
	glUniform1i(glGetUniformLocation(shader.ProgramID, "ourTexture"), 0);
	glUniform1i(glGetUniformLocation(shader.ProgramID, "ourShadow"), 1);
	glUniform1i(glGetUniformLocation(shader.ProgramID, "ourShine"), 2);
										 
										 
	glUniform1f(glGetUniformLocation(shader.ProgramID, "GravityHeight"), m_GPosition / 100.0f);
	glUniform1f(glGetUniformLocation(shader.ProgramID, "time"), m_Time / 20.0f);
	// uniform matrixes
	glUniformMatrix4fv(glGetUniformLocation(shader.ProgramID, "model"), 1, GL_FALSE, value_ptr(ModelMat));
	glUniformMatrix4fv(glGetUniformLocation(shader.ProgramID, "view"), 1, GL_FALSE, value_ptr(ViewMat));
	glUniformMatrix4fv(glGetUniformLocation(shader.ProgramID, "projection"), 1, GL_FALSE, value_ptr(PerspectiveMat));
	mat4 WorldSpace = PerspectiveMat * ViewMat * ModelMat;
	glUniformMatrix4fv(glGetUniformLocation(shader.ProgramID, "worldSpace"), 1, GL_FALSE, value_ptr(WorldSpace));
	Camera camera;

	// uniform variables
	glUniform1f(glGetUniformLocation(shader.ProgramID, "AmbientStrength"), 1.0f);
	glUniform3f(glGetUniformLocation(shader.ProgramID, "lightPos"), 0.0f, 20.0f, 0.0f);
	glUniform3fv(glGetUniformLocation(shader.ProgramID, "cameraPos"), 1, glm::value_ptr(camera.GetCameraPosition()));




	// Draw container
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, Vertices_Amount);
	glBindVertexArray(0);
}
void KatarinaModel::Explode()
{
	m_Time++;
	m_GSpeed += m_GForce;
	m_GPosition += m_GSpeed;
}
void KatarinaModel::Recover_Explosion()
{
	m_Time = 0.0f;
	m_GSpeed = 0.0f;
	m_GPosition = 0.0f;
}