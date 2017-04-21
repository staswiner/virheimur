#include "Inventory.h"



Inventory::Inventory()
{
	this->InventoryGraphics.LoadTexture("Items/Inventory.jpg");
	this->InventoryGraphics.LoadVAO();
}


Inventory::~Inventory()
{
}
void Inventory::Draw_Interface(int x, int y)
{
	InventoryGraphics.Draw(vec2(0,0),vec2(x,y));
	/* Mouse& mouse = Mouse::Instanace();
	vec2 OpenGLCoords((x / mouse.GetWindowSize().x) * 2 - 1, -((y / mouse.GetWindowSize().y) * 2 - 1));
	vec3 InventoryWindowSize(0.25f, 0.25f, 0.25f);
	mat4 Model;
	Model = translate(Model, vec3(OpenGLCoords, 1.0f));
	Model = scale(Model, InventoryWindowSize);


	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Texture);
	glUseProgram(shader.ProgramID);
	glUniform1i(glGetUniformLocation(shader.ProgramID, "ourTexture"), 0);
	glUniformMatrix4fv(glGetUniformLocation(shader.ProgramID, "model"), 1, GL_FALSE, value_ptr(Model));
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, Vertices_Amount);
	glBindVertexArray(0);

	glEnable(GL_DEPTH_TEST);*/
}
void Inventory::Load_VAO()
{
	vertices.push_back(vec2(-1, -1));
	vertices.push_back(vec2(1, -1));
	vertices.push_back(vec2(-1, 1));

	vertices.push_back(vec2(1, 1));
	vertices.push_back(vec2(1, -1));
	vertices.push_back(vec2(-1, 1));


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
void Inventory::Load_Interface()
{
	// texture
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glGenTextures(1, &Texture);
	for (int i = 0; i < 1; i++)
	{
		//bind as 2d texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Texture);
		//// Set our texture parameters
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// Set texture filtering
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// Load, create texture and generate mipmaps
		int width, height;
		unsigned char* image;
		ostringstream oss;
		oss << i;
		image = SOIL_load_image(string(string("Items/Inventory.jpg")).c_str(), &width, &height, 0, SOIL_LOAD_AUTO);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		//	SOIL_free_image_data(image);
		//}

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glGenerateMipmap(GL_TEXTURE_2D);

		SOIL_free_image_data(image);
		//glEnable(GL_TEXTURE_2D);
		//unbind texture 2d
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	Load_VAO();
	shader = Shader("Interface Vertex Shader.glsl", "Interface Fragment Shader.glsl");
}
