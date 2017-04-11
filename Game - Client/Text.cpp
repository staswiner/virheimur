#include "Text.h"
#define RESOLUTION 32.0f

std::map<GLchar, Text::Character> Text::Characters;
vector<Text::Vertices> Text::vertices;
unsigned int Text::Vertices_Amount;


Text::Text(string font)
{
//	m_Font = new _2D_Interface(font);
	m_OurFont = font;
	//this->m_LoadBitmap();
}
Text::Text()
{
	this->Initialize();
}

Text::~Text()
{
}



void Text::Initialize()
{
	///*glEnable(GL_CULL_FACE);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);*/
	//
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//shader = Shader("Text Vertex Shader.glsl", "Text Fragment Shader.glsl");

	//GLuint error = FT_Init_FreeType(&library);
	//error = FT_New_Face(library,"C://Windows/Fonts/arial.ttf",
	//	0,&face);
	//FT_Set_Pixel_Sizes(face, 0, RESOLUTION);
	////error = FT_Set_Char_Size(
	////	face,    /* handle to face object           */
	////	16 * 64,       /* char_width in 1/64th of points  */
	////	16 * 64,   /* char_height in 1/64th of points */
	////	800,     /* horizontal device resolution    */
	////	600);   /* vertical device resolution      */
	ReserveVBO();
	shader = Shader("Text Vertex Shader.glsl", "Text Fragment Shader.glsl");

	//LoadCharacters();
}


void Text::AddFont(string font, float scale)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	GLuint error = FT_Init_FreeType(&library);
	error = FT_New_Face(library, "C://Windows/Fonts/arial.ttf",
		0, &face);
	FT_Set_Pixel_Sizes(face, 0, (FT_UInt)scale);
	LoadCharacters(scale);
}

void Text::LoadCharacters(float scale)
{
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction

	for (GLubyte c = 0; c < 255; c++)
	{
		// Load character glyph 
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
			continue;
		}
		// Generate texture
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D,0,GL_RED,face->glyph->bitmap.width,
		face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);
		// Set texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// Now store character for later use
		Character character = {
			texture,
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			(GLuint)face->glyph->advance.x
		};
		Fonts[scale][c] = character;
		Characters.insert(std::pair<GLchar, Character>(c, character));
	}
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	// Destroy FreeType once we're finished
	FT_Done_Face(face);
	FT_Done_FreeType(library);
}

void Text::ReserveVBO()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

void Text::RenderText(std::string text, GLfloat x, GLfloat y, GLfloat xMax, GLfloat scale, vec3 color)
{
	float FontScale = scale;
	if (Fonts.find(FontScale) == Fonts.end())
	{
		// TODO : add font specification
		AddFont("", FontScale);
	}
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// Activate corresponding render state	
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(VAO);
	glEnableVertexAttribArray(0);
	
	Text::LoadTextShader(color);

	scale /= FontScale;
	vec2 start(x, y);
	// Iterate through all characters
	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++)
	{
		//Character ch = Characters[*c];
		Character ch = Fonts[FontScale][*c];
		if (*c == '\r' || (x-start.x > xMax && xMax != 0.0f))
		{
			y += scale * FontScale;
			x = start.x;
			if (*c == '\r')
				continue;
		}

		GLfloat xpos = x + ch.Bearing.x * scale;
		GLfloat ypos = y + (ch.Size.y - ch.Bearing.y) * scale;

		GLfloat w = ch.Size.x * scale;
		GLfloat h = ch.Size.y * scale;
		// Update VBO for each character
		vec4 vertices[6] = {
			{ xpos,     ypos - h,   0.0, 0.0 },
			{ xpos,     ypos,       0.0, 1.0 },
			{ xpos + w, ypos,       1.0, 1.0 },
							 
			{ xpos,     ypos - h,   0.0, 0.0 },
			{ xpos + w, ypos,       1.0, 1.0 },
			{ xpos + w, ypos - h,   1.0, 0.0 }
		};
		// Render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.TextureID);

		// Update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		// Render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		x += (ch.Advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64)
	}

	//glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_BLEND);
}
void Text::RenderTextReverse(std::string text, GLfloat x, GLfloat y, GLfloat xMax, GLfloat scale)
{
	float FontScale = scale;
	if (Fonts.find(FontScale) == Fonts.end())
	{
		// TODO : add font specification
		AddFont("", FontScale);
	}
	//glClear(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_BLEND);
	//glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	GLuint kataVAO = 16;
	// Activate corresponding render state	
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(VAO);
	glEnableVertexAttribArray(0);

	scale /= FontScale;
	vec2 start(x, y);
	// Iterate through all characters
	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++)
	{
		Character ch = Characters[*c];
		if (*c == '\r' || (x - start.x > xMax && xMax != 0.0f))
		{
			y -= ((ch.Advance >> 6) + FontScale) * scale;
			x = start.x;
			continue;
		}

		GLfloat xpos = x + ch.Bearing.x * scale;
		GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

		GLfloat w = ch.Size.x * scale;
		GLfloat h = ch.Size.y * scale;
		// Update VBO for each character
		GLfloat vertices[6][4] = {
			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos,     ypos,       0.0, 1.0 },
			{ xpos + w, ypos,       1.0, 1.0 },

			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos + w, ypos,       1.0, 1.0 },
			{ xpos + w, ypos + h,   1.0, 0.0 }
		};
		// Render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.TextureID);

		// Update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		/*vec4* dest = static_cast<vec4*>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));

		for (int i = 0; i < 6; i++) {
			*(vec4*)dest = vec4(vertices[i][0], vertices[i][1], vertices[i][2], vertices[i][3]);
			dest += sizeof(vec4);
		}
		GLboolean success = glUnmapBuffer(GL_ARRAY_BUFFER);*/
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		// Render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		x += (ch.Advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64)
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	//glDisable(GL_CULL_FACE);
	glDisable(GL_BLEND);
}
void Text::LoadTextShader(vec3 color)
{
	Mouse mouse;
	glm::mat4 projection = glm::ortho(0.0f, mouse.GetWindowSize().x,
		mouse.GetWindowSize().y, 0.0f);
	mat4 view, model;
	ShaderBuilder::LoadShader(Shader::At("2D Text"))->Add_mat4("projection", projection).
		Add_mat4("view", view).Add_mat4("model", model).
		Add_vec3("textColor", color).Add_texture("text", 0);
}
//void Text::Draw(char charCode)
//{
//	GLuint glyph_index;
//	GLuint error;
//	error = FT_Load_Char(face, charCode, FT_LOAD_RENDER);
//	//glyph_index = FT_Get_Char_Index(face, charCode);
//	//error = FT_Load_Glyph(
//	//	face,          /* handle to face object */
//	//	glyph_index,   /* glyph index           */
//	//	FT_LOAD_DEFAULT);  /* load flags, see below */
//	error = FT_Render_Glyph(face->glyph,   /* glyph slot  */
//		FT_RENDER_MODE_NORMAL); /* render mode */
//	FT_GlyphSlot slot = face->glyph; /* a small shortcut */
//	Draw_Character(slot->bitmap, vec2(300, 300));
//}
//void Text::LoadVAO()
//{
//	vertices.push_back({ vec2(-1, 0), vec2(0, 0) });//|34-|
//	vertices.push_back({ vec2(0, 0),vec2(1, 0) });		//|12-|
//	vertices.push_back({ vec2(-1, 1),vec2(0, 1) });	//|---|
//
//	vertices.push_back({ vec2(0, 1),vec2(1, 1) });
//	vertices.push_back({ vec2(0, 0),vec2(1, 0) }); // 2
//	vertices.push_back({ vec2(-1, 1),vec2(0, 1) }); // 3
//
//
//	VAO; VBO;
//	// generate buffers
//	glGenVertexArrays(1, &VAO);
//	glGenBuffers(1, &VBO);
//	// bind arrays
//	glBindVertexArray(VAO);
//	// bind vertices
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertices), &vertices.front(), GL_STATIC_DRAW);
//
//	// vertices
//	/// Position attribute
//	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertices), BUFFER_OFFSET(0));
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertices), BUFFER_OFFSET(sizeof(vec2)));
//	glEnableVertexAttribArray(1);
//
//	// Unbind VAO
//	glBindVertexArray(0);
//
//	// free memory
//	Vertices_Amount = vertices.size() * 3;
//	vertices.clear();
//}
//void Text::m_LoadBitmap()
//{
//	// texture
//	glBindFramebuffer(GL_FRAMEBUFFER, 0);
//	glBindRenderbuffer(GL_RENDERBUFFER, 0);
//	glGenTextures(1, &Texture);
//	for (int i = 0; i < 1; i++)
//	{
//		//bind as 2d texture
//		glActiveTexture(GL_TEXTURE0);
//		glBindTexture(GL_TEXTURE_2D, Texture);
//		// Set our texture parameters
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//		// Set texture filtering
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//		// Load, create texture and generate mipmaps
//		int width, height;
//		unsigned char* image;
//		ostringstream oss;
//		oss << i;
//		// "Loading Screen/UI.jpg"
//		image = SOIL_load_image(m_OurFont.c_str(), &width, &height, 0, SOIL_LOAD_AUTO);
//		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
//		//	SOIL_free_image_data(image);
//		//}
//
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//		glGenerateMipmap(GL_TEXTURE_2D);
//
//		SOIL_free_image_data(image);
//		//glEnable(GL_TEXTURE_2D);
//		//unbind texture 2d
//		glBindTexture(GL_TEXTURE_2D, 0);
//	}
//	LoadVAO();
//	shader = Shader("Text Vertex Shader.glsl", "Text Fragment Shader.glsl");
//}
//void Text::Draw(string Text, float size, vec2 Position)
//{
//	for (int i = 0; i < Text.size(); i++)
//	{
//		Draw_Character(Text[i], size, vec2(Position.x + size * i, Position.y));
//	}
//}
//void Text::Draw_Character(char Char,float size ,vec2 Position)
//{
//	this->Draw_Interface(Position.y, Position.y + size, Position.x, Position.x + size, vec2(Char % 16, Char / 16 - 1));
//
//}
//void Text::Draw_Character(FT_Bitmap& bitmap, vec2 Position)
//{
//	Mouse mouse;
//	int right = Position.x + bitmap.width;
//	int left = Position.x;
//	int bot = Position.y + bitmap.rows;
//	int top = Position.y;
//	vec2 OpenGLCoords(((right - left) / mouse.GetWindowSize().x) * 2 - 1, -(((bot - top) / mouse.GetWindowSize().y) * 2 - 1));
//	vec2 Offset((left / mouse.GetWindowSize().x) * 2, -(top / mouse.GetWindowSize().y) * 2);
//	OpenGLCoords += Offset;
//	vec3 InterfaceWindowSize((right - left) / (mouse.GetWindowSize().x / 2), (bot - top) / (mouse.GetWindowSize().y / 2), 1.0f);
//	mat4 Model;
//	Model = translate(Model, vec3(OpenGLCoords, 0.0f));
//	Model = scale(Model, InterfaceWindowSize);
//	static bool loaded = false;
//	//if (loaded == false)
//	//{
//	//	//m_LoadBitmap(bitmap);
//	//	loaded = true;
//	//}
//	glDisable(GL_DEPTH_TEST);
//	glEnable(GL_BLEND);
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//
//	glActiveTexture(GL_TEXTURE0);
//	glBindTexture(GL_TEXTURE_2D, Texture);
//	glUseProgram(shader.ProgramID);
//	glUniform1i(glGetUniformLocation(shader.ProgramID, "ourTexture"), 0);
//	glUniformMatrix4fv(glGetUniformLocation(shader.ProgramID, "model"), 1, GL_FALSE, value_ptr(Model));
//	glBindVertexArray(VAO);
//	glDrawArrays(GL_TRIANGLES, 0, Vertices_Amount);
//	glBindVertexArray(0);
//
//	glEnable(GL_DEPTH_TEST);
//}
//void Text::Draw_Interface(int top, int bot, int left, int right, vec2 offset)
//{
//	Mouse mouse;
//	vec2 OpenGLCoords(((right - left) / mouse.GetWindowSize().x) * 2 - 1, -(((bot - top) / mouse.GetWindowSize().y) * 2 - 1));
//	vec2 Offset((left / mouse.GetWindowSize().x) * 2, -(top / mouse.GetWindowSize().y) * 2);
//	OpenGLCoords += Offset;
//	vec3 InterfaceWindowSize((right - left) / (mouse.GetWindowSize().x / 2), (bot - top) / (mouse.GetWindowSize().y / 2), 1.0f);
//	mat4 Model;
//	Model = translate(Model, vec3(OpenGLCoords, 0.0f));
//	Model = scale(Model, InterfaceWindowSize);
//
//
//	glDisable(GL_DEPTH_TEST);
//	glEnable(GL_BLEND);
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//
//	glActiveTexture(GL_TEXTURE0);
//	glBindTexture(GL_TEXTURE_2D, Texture);
//	glUseProgram(shader.ProgramID);
//	glUniform1i(glGetUniformLocation(shader.ProgramID, "ourTexture"), 0);
//	glUniformMatrix4fv(glGetUniformLocation(shader.ProgramID, "model"), 1, GL_FALSE, value_ptr(Model));
//	glUniform2f(glGetUniformLocation(shader.ProgramID, "uvoffset"), offset.x, offset.y);
//	glBindVertexArray(VAO);
//	glDrawArrays(GL_TRIANGLES, 0, Vertices_Amount);
//	glBindVertexArray(0);
//
//	glEnable(GL_DEPTH_TEST);
//}