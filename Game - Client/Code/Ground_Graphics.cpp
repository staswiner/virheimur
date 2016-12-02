#include "Ground_Graphics.h"



Ground::Ground()
	:Obj_Bmp_Loader(/*"Map/GameGround.obj"*/"LowPoly/tree.obj", "Map/spaceTile.jpg")
{
}
Ground::~Ground()
{

}
//void Ground::DrawModel(mat4& PerspectiveMat, mat4& ViewMat, mat4& ModelMat, GLuint shadowMap, mat4& LightView, Shader* a_Shader)
//{
//	
//	// Bind Textures using texture units
//	//glActiveTexture(GL_TEXTURE0);
//
//	/*glActiveTexture(GL_TEXTURE1);
//	glBindTexture(GL_TEXTURE_2D, shadowMap);*/
//	Obj_Bmp_Loader::DrawModel(PerspectiveMat, ViewMat, ModelMat, shadowMap, LightView, a_Shader);
//}
void Ground::InitTexture()
{
	// Setting Grass Texture
	BMP_NAME = "Map/Grass Tile.jpg";
	// texture
	glGenTextures(1, &GrassTexture);
	//bind as 2d texture
	glBindTexture(GL_TEXTURE_2D, GrassTexture);
	// Set our texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//// Set texture filtering
	{
		int width, height;
		unsigned char* image = SOIL_load_image(BMP_NAME.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
		string error = SOIL_last_result();
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glGenerateMipmap(GL_TEXTURE_2D);
		//glGenerateTextureMipmap(texture);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		//glGenerateMipmap(GL_TEXTURE_2D);
		SOIL_free_image_data(image);
		glEnable(GL_TEXTURE_2D);
		//unbind texture 2d
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	// Set MountainTexture
	BMP_NAME = "Map/Mountain Tile.jpg";
	// texture
	glGenTextures(1, &MountainTexture);
	//bind as 2d texture
	glBindTexture(GL_TEXTURE_2D, MountainTexture);
	// Set our texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//// Set texture filtering
	{
		int width, height;
		unsigned char* image = SOIL_load_image(BMP_NAME.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glGenerateMipmap(GL_TEXTURE_2D);
		//glGenerateTextureMipmap(texture);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		//glGenerateMipmap(GL_TEXTURE_2D);
		SOIL_free_image_data(image);
		glEnable(GL_TEXTURE_2D);
		//unbind texture 2d
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	CreateHeightMap();

	LoadVAO();
	shader = Shader(vShader.c_str(), fShader.c_str());
}
void Ground::CreateHeightMap()
{
	for each (Mesh::Vertex v in vertices)
	{
		// rounded up values
		int x = (v.Position.x >= 0.0) ? ((int)(v.Position.x + 0.5f)) : ((int)(v.Position.x + 0.5f)) - 1;
		int z = (v.Position.z >= 0.0) ? ((int)(v.Position.z + 0.5f)) : ((int)(v.Position.z + 0.5f)) - 1;
		MappedVertices.insert(std::pair<pair<int, int>, float>
			(pair<int, int>(x, z), v.Position.y));
	}
}
void Ground::DrawModel(mat4& PerspectiveMat, mat4& ViewMat, mat4& ModelMat, GLuint shadowMap, mat4& LightView, Shader* a_Shader, uint)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, GrassTexture);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, MountainTexture);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, shadowMap);
	//use program
	//glUseProgram(programID);
	Shader *l_Shader;
	if (a_Shader == NULL)
		l_Shader = &shader;
	else
		l_Shader = a_Shader;
	l_Shader->Use();
	// uniform textures
	glUniform1i(glGetUniformLocation(l_Shader->ProgramID, "GrassTexture"), 0);
	glUniform1i(glGetUniformLocation(l_Shader->ProgramID, "MountainTexture"), 1);
	glUniform1i(glGetUniformLocation(l_Shader->ProgramID, "shadowMap"), 2);
	// uniform matrixes
	glUniformMatrix4fv(glGetUniformLocation(l_Shader->ProgramID, "model"), 1, GL_FALSE, value_ptr(ModelMat));
	glUniformMatrix4fv(glGetUniformLocation(l_Shader->ProgramID, "view"), 1, GL_FALSE, value_ptr(ViewMat));
	glUniformMatrix4fv(glGetUniformLocation(l_Shader->ProgramID, "projection"), 1, GL_FALSE, value_ptr(PerspectiveMat));
	mat4 WorldSpace = PerspectiveMat * ViewMat * ModelMat;
	glUniformMatrix4fv(glGetUniformLocation(l_Shader->ProgramID, "worldSpace"), 1, GL_FALSE, value_ptr(WorldSpace));
	glUniformMatrix4fv(glGetUniformLocation(l_Shader->ProgramID, "lightSpaceMatrix"), 1, GL_FALSE, glm::value_ptr(LightView));
	Camera camera;

	// uniform variables
	glUniform1f(glGetUniformLocation(l_Shader->ProgramID, "AmbientStrength"), 0.0f);
	glUniform3f(glGetUniformLocation(l_Shader->ProgramID, "lightPos"), 0.0f, 20.0f, 0.0f);
	glUniform3fv(glGetUniformLocation(l_Shader->ProgramID, "cameraPos"), 1, glm::value_ptr(camera.GetCameraPosition()));




	// Draw container
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, Vertices_Amount);
	glBindVertexArray(0);

}