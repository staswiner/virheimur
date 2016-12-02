#include "Loading_Screen.h"



Loading_Screen::Loading_Screen(vec2 WindowSize, HDC r_HDC)
{
	Orthographic_Projection = glm::ortho((float)0.0f, (float)WindowSize.x, (float)0.0f, (float)WindowSize.y, (float)-1.0f, (float)1.0f);																									  //this->Load_VAO();
	this->Load_Loading_Animation();
	this->m_HDC = r_HDC;
}

Loading_Screen::~Loading_Screen()
{

}

void Loading_Screen::Draw_Loading_Screen()
{
	ShaderBuilder::LoadShader(shader)->Add_texture("ourTexture", Texture[0]);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, Vertices_Amount);
	glBindVertexArray(0);
}
void Loading_Screen::Load_Loading_Animation()
{
	// texture
	glGenTextures(1, Texture);
	for (int i = 0; i < 1; i++)
	{
		//bind as 2d texture
		glBindTexture(GL_TEXTURE_2D, Texture[i]);
		// Set our texture parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// Set texture filtering
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// Load, create texture and generate mipmaps
		int width, height;
		unsigned char* image;
		ostringstream oss;
		oss << i;
		image = SOIL_load_image(string(string("Loading Screen/Loading Screen2.jpg")).c_str(), &width, &height, 0, SOIL_LOAD_AUTO);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		//	SOIL_free_image_data(image);
		//}

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glGenerateMipmap(GL_TEXTURE_2D);

		SOIL_free_image_data(image);
		glEnable(GL_TEXTURE_2D);
		//unbind texture 2d
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	Load_VAO();
	shader = Shader("Loading_Screen Vertex Shader.glsl", "Loading_Screen Fragment Shader.glsl");
}
void Loading_Screen::Load_VAO()
{
	vertices.push_back(vec2(-1, -1));
	vertices.push_back(vec2(1, -1));
	vertices.push_back(vec2(-1, 1));

	vertices.push_back(vec2(1, 1));
	vertices.push_back(vec2(1, -1));
	vertices.push_back(vec2( -1, 1));


	VAO; VBO; 
	// generate buffers
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// bind arrays
	glBindVertexArray(VAO);
	// bind vertices
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec2), &vertices.front(), GL_STATIC_DRAW);

	// vertices
	/// Position attribute
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vec2), BUFFER_OFFSET(0));
	glEnableVertexAttribArray(0);

	// Unbind VAO
	glBindVertexArray(0);

	// free memory
	Vertices_Amount = vertices.size() * 3;
	vertices.clear();
}

void Loading_Screen::OpenAVI(string FileName)
{
	//TCHAR title[100];

	////Open AVIfile library
	//AVIFileInit();

	//// Opens The AVI Stream
	//if (AVIStreamOpenFromFile(&pavi, FileName.c_str(), streamtypeVIDEO, 0, OF_READ, NULL) != 0)
	//{
	//	// An Error Occurred Opening The Stream
	//	MessageBox(HWND_DESKTOP, "Failed To Open The AVI Stream", "Error", MB_OK | MB_ICONEXCLAMATION);
	//}
}
