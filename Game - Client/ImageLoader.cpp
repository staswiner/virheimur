#include "ImageLoader.h"



ImageLoader::ImageLoader()
{
}


ImageLoader::~ImageLoader()
{
	glDeleteTextures(1, &this->MyTexture);
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
}

void ImageLoader::Initialize(string Filename)
{
	LoadTexture(Filename);
	LoadVAO();
}

void ImageLoader::LoadVAO()
{
	vertices.push_back({ vec2(-1, 0), vec2(0, 0) });//|34-|
	vertices.push_back({ vec2(0, 0),vec2(1, 0) });		//|12-|
	vertices.push_back({ vec2(-1, 1),vec2(0, 1) });	//|---|

	vertices.push_back({ vec2(0, 1),vec2(1, 1) });
	vertices.push_back({ vec2(0, 0),vec2(1, 0) }); // 2
	vertices.push_back({ vec2(-1, 1),vec2(0, 1) }); // 3

	// generate buffers
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// bind arrays
	glBindVertexArray(VAO);
	// bind vertices
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertices), &vertices.front(), GL_STATIC_DRAW);

	// vertices
	/// Position attribute
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertices), BUFFER_OFFSET(0));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertices), BUFFER_OFFSET(sizeof(vec2)));
	glEnableVertexAttribArray(1);

	// Unbind VAO
	glBindVertexArray(0);

	// free memory
	Vertices_Amount = vertices.size() * 3;
	vertices.clear();
}
/*
Loads Texture to the GPU memory, returns TextureID handle
*/
int ImageLoader::LoadTexture(string Filename)
{
	GLuint Texture = 0;
	// texture
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glGenTextures(1, &Texture);
	//bind as 2d texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Texture);
	// Set our texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Load, create texture and generate mipmaps
	int Width, Height;
	unsigned char* image;
	// "Loading Screen/UI.jpg"
	image = SOIL_load_image(Filename.c_str(), &Width, &Height, 0, SOIL_LOAD_AUTO);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	this->TrueSize = vec2(Width, Height);
	//	SOIL_free_image_data(image);
	//}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);

	SOIL_free_image_data(image);
	//glEnable(GL_TEXTURE_2D);
	//unbind texture 2d
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	MyTexture = Texture;
	GLuint result = glGetError();
	return Texture;

}
/*
Loads Texture Data to the GPU memory, returns TextureID handle
*/
int ImageLoader::LoadTexture(u8vec4* ColorData,int Width, int Height)
{
	this->TrueSize = vec2(Width, Height);

	GLuint Texture;
	// texture
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glGenTextures(1, &Texture);
	//bind as 2d texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Texture);
	// Set our texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Load, create texture and generate mipmaps
	/*unsigned char* image = new unsigned char[Width*Height*4];
	int i = 0;
	for each(vec4 c in ColorData)
	{
		image[i+0] = c.r;
		image[i+1] = c.g;
		image[i+2] = c.b;
		image[i+3] = c.a;
		i+=4;
	}*/
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, ColorData);
	//	SOIL_free_image_data(image);
	//}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);

	//unbind texture 2d
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	MyTexture = Texture;
	return Texture;
}
// 2x expensive of loading a picture
u8vec4 * ImageLoader::GetImageData(string Filename, int & Width, int & Height)
{
	u8vec4* ImageData;
	// "Loading Screen/UI.jpg"
	ImageData = reinterpret_cast<u8vec4*>(SOIL_load_image(Filename.c_str(), &Width, &Height, 0, SOIL_LOAD_AUTO));
	this->TrueSize = vec2(Width, Height);

	return ImageData;
}

void ImageLoader::ReloadTexture(u8vec4* ColorData, int Width, int Height)
{
	this->TrueSize = vec2(Width, Height);

	glBindTexture(GL_TEXTURE_2D, MyTexture);
	glTexSubImage2D(GL_TEXTURE_2D,
		0,
		0,
		0,
		Width,
		Height,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		ColorData);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void ImageLoader::ReloadTexture(string Filename)
{
	glBindTexture(GL_TEXTURE_2D, MyTexture);
	int Width, Height;
	unsigned char* image;
	image = SOIL_load_image(Filename.c_str(), &Width, &Height, 0, SOIL_LOAD_AUTO);
	this->TrueSize = vec2(Width, Height);

	glTexSubImage2D(GL_TEXTURE_2D,
		0,
		0,
		0,
		Width,
		Height,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		image);
	SOIL_free_image_data(image);;

	glBindTexture(GL_TEXTURE_2D, 0);
}

void ImageLoader::Draw(vec2 TopLeft, vec2 BotRight)
{
	Mouse mouse;
	vec2 OpenGLCoords(((BotRight.x - TopLeft.x) / mouse.GetWindowSize().x) * 2 - 1,
		-(((BotRight.y - TopLeft.y) / mouse.GetWindowSize().y) * 2 - 1));
	vec2 Offset((TopLeft.x / mouse.GetWindowSize().x) * 2, -(TopLeft.y / mouse.GetWindowSize().y) * 2);
	OpenGLCoords += Offset;
	vec3 InterfaceWindowSize((BotRight.x - TopLeft.x) / (mouse.GetWindowSize().x / 2),
		(BotRight.y - TopLeft.y) / (mouse.GetWindowSize().y / 2), 1.0f);
	mat4 Model;
	Model = translate(Model, vec3(OpenGLCoords, 0.0f));
	Model = scale(Model, InterfaceWindowSize);

	ShaderBuilder::LoadShader(Shader::At("Image"))->Add_mat4("model", Model)
		.Add_texture("ourTexture", MyTexture);
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, Vertices_Amount);
	glBindVertexArray(0);
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);

}
void ImageLoader::DrawImagePart(vec2 TopLeft, vec2 BotRight, vec2 ImageTrueSize, vec2 CropTopLeft, vec2 CropBotRight)
{
	Mouse mouse;
	vec2 OpenGLCoords(((BotRight.x - TopLeft.x) / mouse.GetWindowSize().x) * 2 - 1,
		-(((BotRight.y - TopLeft.y) / mouse.GetWindowSize().y) * 2 - 1));
	vec2 Offset((TopLeft.x / mouse.GetWindowSize().x) * 2, -(TopLeft.y / mouse.GetWindowSize().y) * 2);
	OpenGLCoords += Offset;
	vec3 InterfaceWindowSize((BotRight.x - TopLeft.x) / (mouse.GetWindowSize().x / 2),
		(BotRight.y - TopLeft.y) / (mouse.GetWindowSize().y / 2), 1.0f);
	mat4 Model;
	Model = translate(Model, vec3(OpenGLCoords, 0.0f));
	Model = scale(Model, InterfaceWindowSize);


	/*glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	*/	ShaderBuilder::LoadShader(Shader::At("Crop"))->
		Add_texture("ourTexture", MyTexture).
		Add_mat4("model", Model).
		Add_vec2("truesize", ImageTrueSize).
		Add_vec2("topleft", CropTopLeft).
		Add_vec2("botright", CropBotRight);

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, Vertices_Amount);
	glBindVertexArray(0);
	//glEnable(GL_DEPTH_TEST);

}
