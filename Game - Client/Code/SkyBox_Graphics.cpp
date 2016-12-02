#include "SkyBox_Graphics.h"


unsigned int SkyBox::TimePassed = 0;
SkyBox::SkyBox()
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

	//skyboxShader = Shader("SkyBox Vertex Shader.glsl", "SkyBox Fragment Shader.glsl");
	//programID = Loader::LoadShaders("SkyBox Vertex Shader.glsl", "SkyBox Fragment Shader.glsl");
	vShader = "SkyBox Vertex Shader.glsl";
	fShader = "SkyBox Fragment Shader.glsl";
}
/*
``Overload to Inittexture in Loader Class``
*/
void SkyBox::InitTexture()
{
	vector<string> textures_faces;
	textures_faces.push_back("SkyBox/hills_rt.bmp");//right
	textures_faces.push_back("SkyBox/hills_lf.bmp");//left
	textures_faces.push_back("SkyBox/hills_up.bmp");//up
	textures_faces.push_back("SkyBox/hills_dn.bmp");//down
	textures_faces.push_back("SkyBox/hills_bk.bmp");//back
	textures_faces.push_back("SkyBox/hills_ft.bmp");//front
	/* Loading Skybox */
	LoadFaces(textures_faces);
	LoadVAO();
	shader = Shader::At("Skybox");
}
void SkyBox::LoadFaces(vector<string> faces)
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
SkyBox::~SkyBox()
{

}
void SkyBox::LoadVAO()
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
void SkyBox::DrawModel(mat4& PerspectiveMat, mat4& ViewMat, mat4& ModelMat, GLuint, mat4&, Shader*, uint)
{
	glDepthMask(GL_FALSE);// Remember to turn depth writing off
	shader.Use();
	glm::mat4 view = glm::mat4(glm::mat3(ViewMat));	// Remove any translation component of the view matrix
	CalculateDelta();
	float Color_Time = float(TimePassed) / 500.0f;
	Color_Time = sin(radians(90.0f) * Color_Time);
	Color_Time += 2.0f;
	Color_Time *= 2;
	//	glm::mat4 projection = PerspectiveMat;

	glUniformMatrix4fv(glGetUniformLocation(shader.ProgramID, "model"), 1, GL_FALSE, glm::value_ptr(ModelMat));
	glUniformMatrix4fv(glGetUniformLocation(shader.ProgramID, "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(shader.ProgramID, "projection"), 1, GL_FALSE, glm::value_ptr(PerspectiveMat));
	// skybox cube
	glBindVertexArray(VAO);
	glActiveTexture(GL_TEXTURE0);
	glUniform1f(glGetUniformLocation(shader.ProgramID, "colorvar"), Color_Time);
	glUniform1i(glGetUniformLocation(shader.ProgramID, "skybox"), 0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glDepthMask(GL_TRUE);
}


void SkyBox::CalculateDelta()
{
	int NewTime = glutGet(GLUT_ELAPSED_TIME); //1000, 1050
	static int Time = NewTime;
	int loopNumber = 20;
	TimePassed += (NewTime - Time) / 2;
	Time = NewTime; // 1000
	TimePassed %= 2000;
}


