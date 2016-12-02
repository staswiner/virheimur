#include "Loader.h"



//vector<bool>   Loader::isFileLoaded(4, false);



Loader::Loader(string OBJ_NAME, string BMP_NAME)
	:OBJ_NAME(OBJ_NAME), BMP_NAME(BMP_NAME)
{
	if (OBJ_NAME == "" && BMP_NAME == "")
	{
		MessageBoxA(0, "OBJ_BMP has been initialized on its own", "", MB_ICONERROR);
		exit(1);
	}
	//VBO = 0;
}
Loader::Loader(string OBJ_NAME, string BMP_NAME, string SHINE_NAME)
	:OBJ_NAME(OBJ_NAME), BMP_NAME(BMP_NAME), SHINE_NAME(SHINE_NAME)
{
	if (OBJ_NAME == "" && BMP_NAME == "")
	{
		MessageBoxA(0, "OBJ_BMP has been initialized on its own", "", MB_ICONERROR);
		exit(1);
	}
	//VBO = 0;
}
GLuint Loader::Setup_Program()
{
	return GLuint();
}
Loader::~Loader(void)
{
	vertices.clear();
}

void Loader::LoadScene()
{
	ModelData = new Model((GLchar*)OBJ_NAME.c_str());
	for each(Mesh mesh in ModelData->meshes)
	{
		vertices = mesh.vertices; // todo: fix that shit, too much copy
		indices = mesh.indices;
		VAO = mesh.VAO;
		VBO = mesh.VBO;
		EBO = mesh.EBO;
	}
	delete ModelData;
}
/*
Loads AABB ( axis aligned boundry box )
*/
void Loader::LoadModelBox()
{
	vec3 Max(0, 0, 0);
	vec3 Min(0, 0, 0);
	for (uint i = 0; i < vertices.size(); i++)
	{
		if (vertices[i].Position.x > vertices[(uint)Max.x].Position.x)
			Max.x = (float)i;

		if (vertices[i].Position.y > vertices[(uint)Max.y].Position.y)
			Max.y = (float)i;

		if (vertices[i].Position.z > vertices[(uint)Max.z].Position.z)
			Max.z = (float)i;

		if (vertices[i].Position.x < vertices[(uint)Min.x].Position.x)
			Min.x = (float)i;

		if (vertices[i].Position.y < vertices[(uint)Min.y].Position.y)
			Min.y = (float)i;

		if (vertices[i].Position.z < vertices[(uint)Min.z].Position.z)
			Min.z = (float)i;
	}
	verticesSimplified.push_back(vertices[(uint)Max.x]);
	verticesSimplified.push_back(vertices[(uint)Max.y]);
	verticesSimplified.push_back(vertices[(uint)Max.z]);
	verticesSimplified.push_back(vertices[(uint)Min.x]);
	verticesSimplified.push_back(vertices[(uint)Min.y]);
	verticesSimplified.push_back(vertices[(uint)Min.z]);

	verticesBox.push_back(vec3(vertices[(uint)Max.x].Position.x, vertices[(uint)Max.y].Position.y, vertices[(uint)Max.z].Position.z));
	verticesBox.push_back(vec3(vertices[(uint)Max.x].Position.x, vertices[(uint)Max.y].Position.y, vertices[(uint)Min.z].Position.z));
	verticesBox.push_back(vec3(vertices[(uint)Max.x].Position.x, vertices[(uint)Min.y].Position.y, vertices[(uint)Max.z].Position.z));
	verticesBox.push_back(vec3(vertices[(uint)Max.x].Position.x, vertices[(uint)Min.y].Position.y, vertices[(uint)Min.z].Position.z));

	verticesBox.push_back(vec3(vertices[(uint)Min.x].Position.x, vertices[(uint)Max.y].Position.y, vertices[(uint)Max.z].Position.z));
	verticesBox.push_back(vec3(vertices[(uint)Min.x].Position.x, vertices[(uint)Max.y].Position.y, vertices[(uint)Min.z].Position.z));
	verticesBox.push_back(vec3(vertices[(uint)Min.x].Position.x, vertices[(uint)Min.y].Position.y, vertices[(uint)Max.z].Position.z));
	verticesBox.push_back(vec3(vertices[(uint)Min.x].Position.x, vertices[(uint)Min.y].Position.y, vertices[(uint)Min.z].Position.z));

	verticesBox.push_back(vec3(vertices[(uint)Max.x].Position.x, vertices[(uint)Max.y].Position.y, vertices[(uint)Max.z].Position.z));
	verticesBox.push_back(vec3(vertices[(uint)Max.x].Position.x, vertices[(uint)Min.y].Position.y, vertices[(uint)Max.z].Position.z));
	verticesBox.push_back(vec3(vertices[(uint)Max.x].Position.x, vertices[(uint)Max.y].Position.y, vertices[(uint)Min.z].Position.z));
	verticesBox.push_back(vec3(vertices[(uint)Max.x].Position.x, vertices[(uint)Min.y].Position.y, vertices[(uint)Min.z].Position.z));
								
	verticesBox.push_back(vec3(vertices[(uint)Min.x].Position.x, vertices[(uint)Max.y].Position.y, vertices[(uint)Max.z].Position.z));
	verticesBox.push_back(vec3(vertices[(uint)Min.x].Position.x, vertices[(uint)Min.y].Position.y, vertices[(uint)Max.z].Position.z));
	verticesBox.push_back(vec3(vertices[(uint)Min.x].Position.x, vertices[(uint)Max.y].Position.y, vertices[(uint)Min.z].Position.z));
	verticesBox.push_back(vec3(vertices[(uint)Min.x].Position.x, vertices[(uint)Min.y].Position.y, vertices[(uint)Min.z].Position.z));

	verticesBox.push_back(vec3(vertices[(uint)Max.x].Position.x, vertices[(uint)Max.y].Position.y, vertices[(uint)Max.z].Position.z));
	verticesBox.push_back(vec3(vertices[(uint)Min.x].Position.x, vertices[(uint)Max.y].Position.y, vertices[(uint)Max.z].Position.z));
	verticesBox.push_back(vec3(vertices[(uint)Max.x].Position.x, vertices[(uint)Min.y].Position.y, vertices[(uint)Max.z].Position.z));
	verticesBox.push_back(vec3(vertices[(uint)Min.x].Position.x, vertices[(uint)Min.y].Position.y, vertices[(uint)Max.z].Position.z));
							
	verticesBox.push_back(vec3(vertices[(uint)Max.x].Position.x, vertices[(uint)Max.y].Position.y, vertices[(uint)Min.z].Position.z));
	verticesBox.push_back(vec3(vertices[(uint)Min.x].Position.x, vertices[(uint)Max.y].Position.y, vertices[(uint)Min.z].Position.z));
	verticesBox.push_back(vec3(vertices[(uint)Max.x].Position.x, vertices[(uint)Min.y].Position.y, vertices[(uint)Min.z].Position.z));
	verticesBox.push_back(vec3(vertices[(uint)Min.x].Position.x, vertices[(uint)Min.y].Position.y, vertices[(uint)Min.z].Position.z));
	//vertices.clear();
	//vertices = verticesSimplified;
}
void Loader::InitTexture()
{
	// texture
	glGenTextures(1, &texture);
	//bind as 2d texture
	glBindTexture(GL_TEXTURE_2D, texture);
	// Set our texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//// Set texture filtering
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//// 
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	// Load, create texture and generate mipmaps
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

	if (SHINE_NAME != "")
	{
		// texture
		glGenTextures(1, &Shine);
		//bind as 2d texture
		glBindTexture(GL_TEXTURE_2D, Shine);
		// Set our texture parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		int width, height;

		unsigned char* image = SOIL_load_image(SHINE_NAME.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glGenerateMipmap(GL_TEXTURE_2D);

		SOIL_free_image_data(image);
		glEnable(GL_TEXTURE_2D);
		//unbind texture 2d
		glBindTexture(GL_TEXTURE_2D, 0);
	}


	LoadVAO();

}

void Loader::LoadVAO()
{
	VAO; VBO; EBO; 
	// generate buffers
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// bind arrays
	glBindVertexArray(VAO);
	// bind vertices
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Mesh::Vertex), &vertices.front(), GL_STATIC_DRAW);
	// bind indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices.front(), GL_STATIC_DRAW);
	// vertices
	/// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Mesh::Vertex), BUFFER_OFFSET(0));
	glEnableVertexAttribArray(0);
	/// Normals attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Mesh::Vertex), BUFFER_OFFSET(sizeof(vec3)));
	glEnableVertexAttribArray(1);
	/// texture coordinates attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Mesh::Vertex), BUFFER_OFFSET(sizeof(vec3) * 2));
	glEnableVertexAttribArray(2);
	// Unbind VAO
	glBindVertexArray(0);

	// free memory
	Vertices_Amount = vertices.size();
	Indices_Amount = indices.size();
	vertices.clear();
	indices.clear();
}
/***OBJ,BMP files***/
void Obj_Bmp_Loader::DrawModel1(mat4& PerspectiveMat, mat4& ViewMat, mat4& ModelMat, GLuint shadowMap, mat4& LightView, Shader* a_Shader)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glActiveTexture(GL_TEXTURE1);
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
	glUniform1i(glGetUniformLocation(l_Shader->ProgramID, "ourTexture"), 0);
	glUniform1i(glGetUniformLocation(l_Shader->ProgramID, "shadowMap"), 1);
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
void Obj_Bmp_Loader::LoadScene()
{
	ModelData = new Model((GLchar*)OBJ_NAME.c_str());
	for each(Mesh mesh in ModelData->meshes)
	{
		vertices = mesh.vertices; // todo: fix that shit, too much copy
		indices = mesh.indices;
		VAO = mesh.VAO;
		VBO = mesh.VBO;
		EBO = mesh.EBO;
		Vertices_Amount = vertices.size();
	}
	delete ModelData;
}

void Obj_Bmp_Loader::DrawModel(mat4& PerspectiveMat, mat4& ViewMat, mat4& ModelMat, Shader& shader)
{
																		
	shader.Use();																
	//apply shaders
	GLint modelID = glGetUniformLocation(shader.ProgramID, "model");
	GLint viewID = glGetUniformLocation(shader.ProgramID, "view");
	GLint projectionID = glGetUniformLocation(shader.ProgramID, "projection");
	glUniformMatrix4fv(modelID, 1, GL_FALSE, value_ptr(ModelMat));
	glUniformMatrix4fv(viewID, 1, GL_FALSE, value_ptr(ViewMat));
	glUniformMatrix4fv(projectionID, 1, GL_FALSE, value_ptr(PerspectiveMat));

	// Draw container
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, Vertices_Amount);
	glBindVertexArray(0);

}
void Loader::DrawModel()
{
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, Vertices_Amount);
	glBindVertexArray(0);
}

void Loader::DrawModelGaussic(mat4& PerspectiveMat, mat4& ViewMat, mat4& ModelMat, Shader& shader)
{
	shader.Use();
	//apply shaders
	GLint modelID = glGetUniformLocation(shader.ProgramID, "model");
	GLint viewID = glGetUniformLocation(shader.ProgramID, "view");
	GLint projectionID = glGetUniformLocation(shader.ProgramID, "projection");
	glUniformMatrix4fv(modelID, 1, GL_FALSE, value_ptr(ModelMat));
	glUniformMatrix4fv(viewID, 1, GL_FALSE, value_ptr(ViewMat));
	glUniformMatrix4fv(projectionID, 1, GL_FALSE, value_ptr(PerspectiveMat));

	// Draw container
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, Vertices_Amount);
	glBindVertexArray(0);
}