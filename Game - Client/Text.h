#pragma once
#include <string>
#include <map>
#include <utility>
#include "Graphics_Header.h"
#include "ImageLoader.h"
#include "ft2build.h"
#include "Mouse.h"

#include FT_FREETYPE_H  
#include "freetype\freetype.h"
using namespace std;
using namespace glm;
class Text // singleton
{
public:
	static Text& getInstance()
	{
		static Text Instance;
		return Instance;
	}
	Text(Text const&) = delete;
	void operator=(Text const&) = delete;
	~Text();
	void Initialize();
	//void Draw(char charCode);
	void RenderText(std::string text,
		GLfloat x, GLfloat y, GLfloat xMax, GLfloat scale, vec3 color = vec3(0));
	void RenderTextReverse(std::string text,
		GLfloat x, GLfloat y, GLfloat xMax, GLfloat scale);
	static void LoadTextShader(vec3 color);
	Text();
private:
	Text(string font);
	static Text Instance;
	void AddFont(string font, float scale);
	void LoadCharacters(float scale);
	void ReserveVBO();
	//void Text::Draw_Interface(int top, int bot, int left, int right, vec2 offset);
	GLuint Texture, VAO, VBO;
	Shader shader;
	ImageLoader* m_Font;
	string m_OurFont;
	struct Vertices {
		vec2 vertices;
		vec2 uvs;
	};

	struct Character {
		GLuint     TextureID;  // ID handle of the glyph texture
		glm::ivec2 Size;       // Size of glyph
		glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
		GLuint     Advance;    // Offset to advance to next glyph
	};

	static std::map<GLchar, Character> Characters;
	map<float, map<GLchar, Character>> Fonts;

	static vector<Vertices> vertices;
	static unsigned int Vertices_Amount;
	int Resolution;
	FT_Library library;
	FT_Face face;
	Mouse mouse;
};

