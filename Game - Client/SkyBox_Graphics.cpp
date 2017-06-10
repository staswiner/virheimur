#include "SkyBox_Graphics.h"


SkyBox_Graphics::SkyBox_Graphics()
{
	/*-SkyCube Setup-*/

	GLfloat skyboxVerticestemp[] = {
		// Positions  
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f,  1.0f
	};
	for (int i = 0; i < sizeof(skyboxVerticestemp) / sizeof(GLfloat); i++)
	{
		skyboxVertices.push_back(skyboxVerticestemp[i]);
	}
	for (unsigned int i = 0; i < skyboxVertices.size(); i++)
	{
		skyboxIndices.push_back(i);
	}
}
/*
``Overload to Inittexture in Loader Class``
*/
void SkyBox_Graphics::InitTexture()
{
	vector<string> textures_faces;
	textures_faces.push_back("SkyBox/peaks_rt.bmp");//right
	textures_faces.push_back("SkyBox/peaks_lf.bmp");//left
	textures_faces.push_back("SkyBox/peaks_up.bmp");//up
	textures_faces.push_back("SkyBox/peaks_dn.bmp");//down
	textures_faces.push_back("SkyBox/peaks_bk.bmp");//back
	textures_faces.push_back("SkyBox/peaks_ft.bmp");//front
	/* Loading Skybox */
	LoadFaces(textures_faces);
	LoadVAO();
	shader = Shader::At("Skybox");
}
void SkyBox_Graphics::ReloadTexture()
{
	shader.Reload();
}
void SkyBox_Graphics::LoadFaces(vector<string> faces)
{
	glGenTextures(1, &texture);

	int width, height;
	unsigned char* image;

	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
	for (GLuint i = 0; i < faces.size(); i++)
	{
		image = SOIL_load_image(faces[i].c_str(), &width, &height, 0, SOIL_LOAD_RGB);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		SOIL_free_image_data(image);
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}
SkyBox_Graphics::~SkyBox_Graphics()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteTextures(1, &texture);
}
void SkyBox_Graphics::LoadVAO()
{
	VAO; VBO;//GLuint skyboxVAO, skyboxVBO;
	// generate buffers
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// bind arrays
	glBindVertexArray(VAO);
	// bind vertices
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, skyboxVertices.size() * sizeof(GLfloat), &skyboxVertices.front(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), BUFFER_OFFSET(0));
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	skyboxVertices.clear();
}
void SkyBox_Graphics::DrawModel()
{
	mat4 ViewMatrix = Camera::GetCamera(Camera::eCamera::Current).ViewMatrix;
	ViewMatrix = glm::mat4(glm::mat3(ViewMatrix));	// Remove any translation component of the view matrix
	mat4 ProjectionMatrix = Camera::GetCamera(Camera::eCamera::Current).ProjectionMatrix;

	glDepthMask(GL_FALSE);// Remember to turn depth writing off

	ShaderBuilder::LoadShader(this->shader)->
		Add_mat4("projection", ProjectionMatrix).
		Add_mat4("view", ViewMatrix).
		Add_int("skybox", 0);
	// skybox cube
	glBindVertexArray(VAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glDepthMask(GL_TRUE);
}


