#include "Mesh.h"


Mesh::Mesh()
{
}


Mesh::~Mesh()
{
}
Mesh::Mesh(vector<Vertex> vertices, vector<GLuint> indices, vector<Texture> textures)
{
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;


	this->setupMesh();
}
void Mesh::setupMesh()
{
	Vertices_Amount = vertices.size();
	Indices_Amount = indices.size();
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);
	glGenBuffers(1, &this->EBO);

	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

	glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex),
		&this->vertices.front(), GL_STATIC_DRAW);
	/*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint),
	&this->indices[0], GL_STATIC_DRAW);*/

	// Vertex Positions
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Vertex Normals
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(GLvoid*)offsetof(Vertex, Normal));
	glEnableVertexAttribArray(1);
	// Vertex Texture Coords
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(GLvoid*)offsetof(Vertex, TexCoords));
	glEnableVertexAttribArray(2);

	GLuint VBO_bones;
	vector<VertexBoneData> Bones;
	Bones.resize(Vertices_Amount);
	glGenBuffers(1, &VBO_bones);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_bones);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Bones[0]) * Bones.size(), &Bones[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(3);
	glVertexAttribIPointer(3, 4, GL_INT, sizeof(VertexBoneData), (const GLvoid*)0);
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(VertexBoneData), (const GLvoid*)16);
	//GLuint VBO_bones;
	//vector<Skeletal> Bones;
	//Bones.resize(this->Vertices_Amount);
	//glBindBuffer(GL_ARRAY_BUFFER, VBO_bones);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(Bones[0]) * Bones.size(), &Bones[0], GL_STATIC_DRAW);
	//glEnableVertexAttribArray(3);
	//glVertexAttribIPointer(3, 4, GL_INT, sizeof(VertexBoneData), (const GLvoid*)0);
	//glEnableVertexAttribArray(4);
	//glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(VertexBoneData), (const GLvoid*)16);

	glBindVertexArray(0);
	
	/*vertices.clear();
	indices.clear();*/
}
void Mesh::loadMesh()
{

}
void Mesh::VertexBoneData::AddBoneData(uint BoneID, float Weight)
{
	//for (uint i = 0; i < ARRAY_SIZE_IN_ELEMENTS(IDs); i++) {
	//	if (Weights[i] == 0.0) {
	//		IDs[i] = BoneID;
	//		Weights[i] = Weight;
	//		return;
	//	}
	//}

	//// should never get here - more bones than we have space for
	//assert(0);
}
void Mesh::Draw(Shader shader)
{
	GLuint diffuseNr = 1;
	GLuint specularNr = 1;
	for (GLuint i = 0; i < this->textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i); // Activate proper texture unit before binding
										  // Retrieve texture number (the N in diffuse_textureN)
		stringstream ss;
		string number;
		string name = this->textures[i].type;
		if (name == "texture_diffuse")
			ss << diffuseNr++; // Transfer GLuint to stream
		else if (name == "texture_specular")
			ss << specularNr++; // Transfer GLuint to stream
		number = ss.str();

		glUniform1i(glGetUniformLocation(shader.ProgramID, ("material." + name + number).c_str()), i);
		glBindTexture(GL_TEXTURE_2D, this->textures[i].id);
	}
	glActiveTexture(GL_TEXTURE0);

	shader.Use();
	Mouse mouse;
	mat4 ModelMat;
	mat4 ViewMat;
	mat4 PerspectiveMat = glm::perspective(radians(120.0f),
		float(mouse.GetWindowSize().x / mouse.GetWindowSize().y), 1.0f, 1000.0f);
	GLint modelID = glGetUniformLocation(shader.ProgramID, "model");
	GLint viewID = glGetUniformLocation(shader.ProgramID, "view");
	GLint projectionID = glGetUniformLocation(shader.ProgramID, "projection");
	glUniformMatrix4fv(modelID, 1, GL_FALSE, value_ptr(ModelMat));
	glUniformMatrix4fv(viewID, 1, GL_FALSE, value_ptr(ViewMat));
	glUniformMatrix4fv(projectionID, 1, GL_FALSE, value_ptr(PerspectiveMat));

	// Draw mesh
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, this->vertices.size());
	glBindVertexArray(0);
	/*glBindVertexArray(this->VAO);
	glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);*/
}
void Mesh::DrawModel()
{
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, Vertices_Amount);
	glBindVertexArray(0);
}
void Mesh::SignUniforms(vector<string> Name, vector<string> Type
	, vector<void*> Variable, vector<uint> Textures, vector<string> TextureName, Shader & shader)
{
	for (GLuint i = 0; i < Textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, Textures[i]);
	}
	shader.Use();
	for (GLuint i = 0; i < Textures.size(); i++)
	{
		glUniform1i(glGetUniformLocation(shader.ProgramID, TextureName[i].c_str()), i);
	}
	for (GLuint i = 0; i < Name.size(); i++)
	{
		if (!Variable[i]) continue;
		if (Type[i] == "mat4")
		{
			glUniformMatrix4fv(glGetUniformLocation(shader.ProgramID, Name[i].c_str()),
				1, GL_FALSE, value_ptr(*static_cast<mat4*>(Variable[i])));
			continue;
		}
		if (Type[i] == "float")
		{
			glUniform1f(glGetUniformLocation(shader.ProgramID, Name[i].c_str()),
				*static_cast<float*>(Variable[i]));
			continue;
		}
		if (Type[i] == "int")
		{
			glUniform1i(glGetUniformLocation(shader.ProgramID, Name[i].c_str()),
				*static_cast<int*>(Variable[i]));
			continue;
		}
		if (Type[i] == "vec3")
		{
			glUniform3f(glGetUniformLocation(shader.ProgramID, Name[i].c_str()),
				static_cast<vec3*>(Variable[i])->x,
				static_cast<vec3*>(Variable[i])->y,
				static_cast<vec3*>(Variable[i])->z);
			continue;
		}
	}
}