#include "ChampionChat.h"



ChampionChat::ChampionChat(Shader& shader)
	:shader(shader)
{
}


ChampionChat::~ChampionChat()
{
}

void ChampionChat::CreateChatbox()
{
	/*ChatFrames.push_back(new ImageLoader());
	ChatFrames.back()->Initialize("Interface/Chat.png");*/
}

void ChampionChat::Draw(string a_Text, mat4& projection, mat4& view, mat4& model)
{
	mat4 WorldPos;
	Mouse mouse;
	vec3 color(0);
	glm::mat4 projectionOrtho = glm::ortho(0.0f, mouse.GetWindowSize().x,
		mouse.GetWindowSize().y, 0.0f);
	//ShaderBuilder::LoadShader(shader)->Add_mat4("projection", projection).
	//	Add_mat4("view", view);// .Add_mat4("model", model);// .Add_mat4("worldPos", WorldPos);

	//ChatFrames[0]->DrawImage(vec2(0, 0), vec2(300, 300));

	ShaderBuilder::LoadShader(shader)->Add_mat4("projection", projection).Add_mat4("view", view).
		Add_mat4("model", model).Add_vec3("textColor", color).Add_texture("text", 0);
	Text& text = Text::getInstance();
	text.RenderTextReverse(a_Text, 0.0f, 0.0f, 200.0f, 10.0f);
}

void ChampionChat::Draw2D(string a_Text, mat4 & projection, mat4 & view, mat4 & model)
{

	mat4 WorldPos;
	Mouse mouse;
	vec3 color(0);
	glm::mat4 projectionOrtho = glm::ortho(0.0f, mouse.GetWindowSize().x,
		mouse.GetWindowSize().y, 0.0f);
	vec4 TextPosition = projection * view * model * vec4(0,0,0,1);
	TextPosition /= TextPosition.w;
	if (TextPosition.z > 1) return;
	float x = mouse.GetWindowSize().x / 2.0f;
	float y = mouse.GetWindowSize().y / 2.0f;
	
	vec2 TextCoords = vec2(TextPosition.x * x + x, -TextPosition.y * y + y);
	//ShaderBuilder::LoadShader(shader)->Add_mat4("projection", projection).
	//	Add_mat4("view", view);// .Add_mat4("model", model);// .Add_mat4("worldPos", WorldPos);

	/*Frame*/
	int Rows = count(a_Text.begin(), a_Text.end(), '\r') + 1;
	// TODO
	//
	//
	ShaderBuilder::LoadShader(Shader::At("Crop"))->
		Add_mat4("projection", projectionOrtho)
		.Add_mat4("view", mat4());
	//ChatFrames[0]->DrawImagePart(vec2(0, 0), vec2(300, 300), vec2(300, 300),
	//	vec2(0, 0), vec2(300, 300));
	
	/*Text*/
	ShaderBuilder::LoadShader(shader)->Add_mat4("projection", projectionOrtho).Add_mat4("view", mat4()).
		Add_mat4("model", mat4()).Add_vec3("textColor", color).Add_texture("text", 0);
	Text& text = Text::getInstance();
	text.RenderText(a_Text, TextCoords.x, TextCoords.y, 200.0f, 40.0f);
}
