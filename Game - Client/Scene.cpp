#include "Scene.h"



Scene::Scene(GlobalDataObject& Data,UserInterface& UI,FBO* Index)
	:Data(Data), UI(UI)
{
	IndexFBO = Index;
	int i = 0;
}

Scene::~Scene()
{
}

void Scene::Initialize()
{
	glewExperimental = TRUE;
	GLuint Err = glewInit();
	glLoadIdentity();
	Shader::LoadShaders();
	
	mSea.Initialize();
	text.Initialize();

	shadow = new Shadow_Mapping();

	mFBO["Post Processing"].Initialize(1, 1, Shader::At("PostProcessing"));
	mFBO["HBlur"].Initialize(2, 2, Shader::At("HBlur"));
	mFBO["VBlur"].Initialize(2, 2, Shader::At("VBlur"));
	mFBO["HBlurS"].Initialize(1, 1, Shader::At("HBlur"));
	mFBO["VBlurS"].Initialize(1, 1, Shader::At("VBlur"));
	mFBO["Bright"].Initialize(1, 1, Shader::At("Bright"));
	mFBO["Combine"].Initialize(1, 1, Shader::At("Combine"));
	mFBO["Gaussic Effect"].Initialize(1, 1, Shader::At("Combine"));
	mFBO["RadialBlur"].Initialize(1, 1, Shader("RadialBlur Vertex Shader.glsl", "RadialBlur Fragment Shader.glsl"));
	mFBO["Basic"].Initialize(1, 1, Shader());
	//mFBO["Index"].Initialize(1, 1, Shader::At("PostProcessing"));
	IndexFBO->InitializeBig(1, 1, Shader::At("PostProcessing"));
	mAntiAliasing.InitializeMultiSample();
	championChat = new ChampionChat(Shader::At("Champion Chat"));
	championChat->CreateChatbox();
	//skyBox = new SkyBox;
	//skyBox->InitTexture();
	minimap.Initialize();

#pragma region 2D Interface
	GenerateForm();


#pragma endregion 2D Interface


	loaded_Models.initialize_Models();
	grass.Initialize();
	//Players[Channel].push_back(Player(Unit_Data(vec3(0, 10, 0), "Katarina", 0, 0, 1),1));
	// remove next line
	//seaAnim.Initialize();
	for (int i = 0; i < 1600; i++)
	{
		vec3 ObstaclePos = loaded_Models["Land"]->meshes[0].mCollision->OnCollision(
			vec3(float(float(Stas::Maths::llrand() % 200000) - 100000) / 1000.0f, 0,
			float(float(Stas::Maths::llrand() % 200000) - 100000) / 1000.0f));
		vec3 ObstacleRotation(float(rand() % 200 - 100) / 100.0f,float(rand()%200 - 100)/100.0f, float(rand() % 200 - 100) / 100.0f);
		//Obstacles.push_back(ObstaclePos);
		//rotate
		//translate
		mat4 ModelMat = glm::translate(mat4(), ObstaclePos);
		ModelMat = glm::rotate(ModelMat, glm::radians(60.0f) ,ObstacleRotation);
		grass.ObstaclesMat.push_back(ModelMat);

	}
	//for (int i = -100; i < 100; i++)
	//{
	//	for (int j = -100; j < 100; j++)
	//	{
	//		vec3 ObstaclePos = vec3(i,0,j);
	//		//Obstacles.push_back(ObstaclePos);
	//		//rotate
	//		//translate
	//		mat4 ModelMat = glm::translate(mat4(), ObstaclePos);
	//		seaAnim.ObstaclesMat.push_back(ModelMat);
	//	}
	//}
}

void Scene::Frame()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glClearColor(255, 255, 255, 255);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);
	glDepthMask(GL_TRUE);

	ViewMatrix = camera.GetCameraMatrix();
	SetProjectionMatrix(camera.GetProjectionMatrix());

	DrawIndexColor();
	//Draw_Scene();
	Draw_Units();

	glFlush();
	SwapBuffers(m_HDC);
}


void Scene::SetProjectionMatrix(mat4 & projection)
{
	this->ProjectionMatrix = projection;
}

void Scene::SetWindowHDC(HDC & hdc)
{
	this->m_HDC = hdc;
}

void Scene::GenerateForm()
{
	UI.GenerateForm();
}

void Scene::Draw_Units()
{

	// Draw To Depth Buffer
	DrawScene_Depth();
	// Draw Water
	DrawScene_Refraction();
	DrawScene_Reflection();
	// Draw postprocesser
	DrawScene_PostProcessing();
}
void Scene::Draw_Scene()
{
	DrawGround(Shader::At("Ground"));
}
void Scene::DrawScene_Depth()
{
	shadow->BindFrameBuffer();
	//Shadow_DrawGround(shadow->shader);
	//DrawColladaDistance();
	// back to default framebuffer
	mFBO["Post Processing"].BindFrameBuffer();
	//glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, (int)mouse.GetWindowSize().x, (int)mouse.GetWindowSize().y);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}
void Scene::DrawScene_Refraction()
{
	mSea.BindRefraction();

	SetCameraView();
	DrawSky();
	//DrawGround(mSea.sRefraction_Ground);
	//Draw_All_Units();
	//DrawEntities();
	//	Soldier->Draw(Shader("Basic Vertex Shader.glsl", "Basic Fragment Shader.glsl"));

}
void Scene::DrawScene_Reflection()
{
	mSea.BindReflection();
	{
		SetCameraView();
		camera.SetCameraPosition(vec3(camera.CameraPositionCalculated.x, -camera.CameraPositionCalculated.y, camera.CameraPositionCalculated.z));
		camera.InvertPitch();
		SetCameraView();
		DrawSky();
		//DrawGround(mSea.sReflection_Ground);
		//Draw_All_Units();
		//DrawEntities();
		//	Soldier->Draw(Shader("Basic Vertex Shader.glsl", "Basic Fragment Shader.glsl"));
		camera.SetCameraPosition(vec3(camera.CameraPositionCalculated.x, -camera.CameraPositionCalculated.y, camera.CameraPositionCalculated.z));
		camera.InvertPitch();
		SetCameraView();
	}
}
void Scene::DrawScene_PostProcessing()
{
	mAntiAliasing.BindFrameBuffer();

	SetCameraView();

	DrawSky();
	//DrawGround(Shader::At("Ground"));
	DrawCollada();
	//DrawEntities();
	//DrawSea();
	DrawSeaAnimated();
	DrawUI();

	mAntiAliasing.CopyBuffer(mFBO["Post Processing"].PostProcessingFBO);
	//mFBO["HBlurS"].BindFrameBuffer();
	//mFBO["Post Processing"].DrawFrameBuffer();
	//mFBO["VBlurS"].BindFrameBuffer();
	//mFBO["HBlurS"].DrawFrameBuffer();
	//mFBO["Basic"].BindFrameBuffer();
	//mFBO["VBlurS"].DrawFrameBuffer();

	//mBright.BindFrameBuffer();
	//mPostProcessing.DrawFrameBuffer();
	// Draw Shine
	//DrawGaussicEffect();

	//LastLayer.BindFrameBuffer();
	//mVBlurS.DrawFrameBuffer();
	// uniform textures
	FBO::UnbindFrameBuffer();

	//vector<GLuint> Textures = { mFBO["Basic"].texture,mFBO["Post Processing"].texture,shadow->depthMap };
	//vector<string> ShaderNames = { "ourShine","ourTexture","DepthMap" };
	//mFBO["Combine"].DrawDirectly(Textures,ShaderNames);
	////shadow->Draw();
	////mFBO["Basic"].DrawDirectly(Textures,ShaderNames);
	//mFBO["Combine"].DrawFrameBuffer();
	mFBO["Post Processing"].DrawFrameBuffer();
	//IndexFBO->DrawFrameBuffer();
	//shadow->Draw();
}
void Scene::Shadow_DrawGround(Shader& shader)
{
	mat4 l_ProjectionMatrix = glm::perspective(radians(120.0f),
		float(mouse.GetWindowSize().x / mouse.GetWindowSize().y), 1.0f, 1000.0f);
	mat4 l_ViewMatrix = glm::lookAt(LightPosition, vec3(0.0f), vec3(1.0f, 1.0f, 1.0f));
	mat4 ModelMatrix;
	//loaded_Models["Ground"]->DrawModel(l_ProjectionMatrix, l_ViewMatrix, ModelMatrix, shader); // TODO remove mat arguements
}
void Scene::DrawGround(Shader& shader)
{
	vec3 LightPos = vec3(0,10,10);
	mat4 l_ProjectionMatrix = glm::perspective(radians(120.0f),
		float(mouse.GetWindowSize().x / mouse.GetWindowSize().y), 1.0f, 1000.0f);
	mat4 l_ViewMatrix = glm::lookAt(LightPos, vec3(0.0f), vec3(1.0f, 1.0f, 1.0f));
	mat4 l_LightView = l_ProjectionMatrix * l_ViewMatrix;
	mat4 ModelMatrix; // for now

	float time = 0.0f;
	float zeroval = 0;
	mat4 WorldSpace = ProjectionMatrix * ViewMatrix * ModelMatrix;

	ShaderBuilder::LoadShader(shader)->
	/*	Add_texture("GrassTexture", dynamic_cast<Ground*>(loaded_Models["Ground"])->GrassTexture).
		Add_texture("MountainTexture", dynamic_cast<Ground*>(loaded_Models["Ground"])->MountainTexture).*/
		Add_texture("shadowMap", shadow->depthMap).
		Add_mat4("projection", ProjectionMatrix).
		Add_mat4("view", ViewMatrix).
		Add_mat4("worldSpace", WorldSpace).
		Add_mat4("model", ModelMatrix).
		Add_mat4("lightSpaceMatrix", l_LightView).
		Add_float("time", time).Add_float("AmbientStrength", zeroval).
		Add_vec3("lightPos", vec3(0.0f, 100.0f, 0.0f)).
		Add_vec3("cameraPos", camera.GetCameraPosition()).
		Add_float("GravityHeight", zeroval);
	loaded_Models["Ground"]->Draw();
}
void Scene::DrawEntities()
{
	mat4 l_ProjectionMatrix = glm::perspective(radians(120.0f),
		float(mouse.GetWindowSize().x / mouse.GetWindowSize().y), 1.0f, 1000.0f);
	mat4 l_ViewMatrix = glm::lookAt(LightPosition, vec3(0.0f), vec3(1.0f, 1.0f, 1.0f));
	mat4 l_LightView = l_ProjectionMatrix * l_ViewMatrix;
}
void Scene::DrawSea()
{
	mat4 ModelMat;
	ModelMat = scale(ModelMat, vec3(100, 100, 100));
	mSea.Draw(ProjectionMatrix, ViewMatrix, ModelMat);
}
char ToLower(char a)
{
	if (a <= 'Z')
		return (a - 'A' + 'a');
	else return a;
}

void Scene::DrawIndexColor()
{
	// Draws All Entities with Color
	IndexFBO->BindFrameBuffer();

	mat4 WVM = ProjectionMatrix*ViewMatrix;
	/*ShaderBuilder::LoadShader(Shader::At("Index"))->
		Add_mat4("WVM",WVM);
	loaded_Models["Land"]->Draw();
*/
	WVM = ProjectionMatrix * ViewMatrix;
	ShaderBuilder::LoadShader(Shader::At("Index"))->
		Add_mat4("WVM", WVM);
	loaded_Models["Land"]->Draw();

	
	FBO::UnbindFrameBuffer();
}
void Scene::DrawColladaDistance()
{
	mat4 WVM;
	vec3 position;

#pragma region Mathematics
	mat4 ModelMatrix;
	ModelMatrix = glm::translate(ModelMatrix, position);
#pragma endregion Mathematics
	vec3 color;
	mat4 CharMat;
	WVM = ProjectionMatrix * ViewMatrix * CharMat;
	//ShaderBuilder::LoadShader(Shader::At("Animation"))->
	//	Add_mat4("WVM", WVM).
	//	Add_bool("isAnimated", true).
	//	Add_textures(loaded_Models["Collada"]->Textures);
	//loaded_Models["Collada"]->Draw();
	//position = vec3(50, 0, 0);
	//ModelMatrix = glm::translate(ModelMatrix, position);
	//ShaderBuilder::LoadShader(Shader::At("Animation"))->
	//	Add_mat4("model", ModelMatrix);
	float time = float(GetTickCount());
	float SlowTime = time / 40.0f;
	mat4 landmat;
	WVM = ProjectionMatrix * ViewMatrix * landmat;
	ShaderBuilder::LoadShader(Shader::At("AnimationDistance"))->
		Add_mat4("WVM", WVM).
		Add_bool("isAnimated", false);
	loaded_Models["Land"]->Draw();
	//loaded_Models["Collada"]->Draw();

#pragma region Grass
	{
		vector<vec4> ModelMatrixs;
		mat4 Animation;
		ShaderBuilder shader = *ShaderBuilder::LoadShader(Shader::At("InstancedDistance"));
		for (int i = 0; i < 25; i++)
		{
			Animation = glm::rotate(mat4(),
				radians(
					cos(
						radians(
							fmod(SlowTime, 360.0f) + i * 10.0f
						)
					)
					*80.0f)
				, vec3(1, 0, 1));
			shader.Add_mat4("Animation[" + to_string(i) + "]", Animation);
		}

		mat4 WVM = ProjectionMatrix * ViewMatrix;

		ShaderBuilder::LoadShader(Shader::At("InstancedDistance"))->
			Add_mat4("WVM", WVM).
			Add_float("time", time).
			Add_vec3("cameraPos", camera.GetCameraPosition()).
			Add_bool("isAnimated", false);
		grass.Draw(grass.ObstaclesMat);
	}
#pragma endregion Grass

}

void Scene::SetCameraView()
{
	/*if (m_Unit_Data[Channel].size() <= ClientID)
	return;*/
	ViewMatrix = camera.GetCameraMatrix();
}
void Scene::DrawUI()
{
	glm::mat4 projection = glm::ortho(0.0f, mouse.GetWindowSize().x,
		mouse.GetWindowSize().y, 0.0f);
	mat4 view, model;
	vec3 color = vec3(0, 1, 1);
	vec2 Center(mouse.GetWindowSize().x / 2, mouse.GetWindowSize().y / 2);
	// Official UI
	UI.root->Draw();
	//minimap.Change();
	minimap.DrawMinimap(Data);
	//minimap.Draw(vec2(100, 100), vec2(400, 400));
	for(auto it = Data.GetPlayerInformation().begin(); it != Data.GetPlayerInformation().end(); it++)
	{
		vec3 pos = it->second.GetUnitData().GetPosition();
		mat4 ModelMatrix;
		ModelMatrix = translate(ModelMatrix, pos);
		championChat->Draw(text, "OpenGL", ProjectionMatrix, ViewMatrix, mat4());
		championChat->Draw2D(text, it->second.GetUsername(), ProjectionMatrix, ViewMatrix, ModelMatrix);
	}
	/*else
	{

		ShaderBuilder::LoadShader(Shader::At("2D Text"))->Add_mat4("projection", projection).
			Add_mat4("view", view).Add_mat4("model", model).
			Add_vec3("textColor", color).Add_texture("text", 0);
		text.RenderText("Loading . . .", 350.0f, 200.0f, 500.0f, 40.0f);
		UI.AcceptInput();
	}*/

	ShaderBuilder::LoadShader(Shader::At("2D Text"))->Add_mat4("projection", projection).
		Add_mat4("view", view).Add_mat4("model", model).
		Add_vec3("textColor", color).Add_texture("text", 0);
	text.RenderText(UI.Chat, 100.0f, 200.0f, 200.0f, 40.0f);

	color = vec3(1, 0, 0);
	SetCameraView();
	mat4 projectionMatrix = glm::perspective(radians(120.0f),
		float(mouse.GetWindowSize().x / mouse.GetWindowSize().y), 1.0f, 1000.0f);
	ShaderBuilder::LoadShader(Shader::At("2D Text"))->Add_vec3("textColor", color);
	fps.CountFrame(Shader::At("2D Text"));
}

void Scene::DrawSky()
{
	mat4 ModelMatrix;
	float Counter = 0;
	ModelMatrix = glm::rotate(ModelMatrix, radians(float(Counter) / 10.0f), vec3(0, 1, 0));
	//skyBox->DrawModel(ProjectionMatrix, ViewMatrix, ModelMatrix, 0, mat4(), NULL, 0);
	//loaded_Models["Sky"]->DrawModel(ProjectionMatrix, ViewMatrix, ModelMatrix, 0, mat4(), NULL, 0);
}
void Scene::DrawSeaAnimated()
{

}

void Scene::DrawCollada()
{
	mat4 WVM;
	//for each (Player P in Data.GetPlayerInformation())
	for (auto i = Data.GetPlayerInformation().begin(); i != Data.GetPlayerInformation().end(); i++)
	{
		Unit_Data ud = i->second.GetUnitData();
		vec3 position = ud.GetPosition();

#pragma region Mathematics
		mat4 ModelMatrix;
		ModelMatrix = glm::translate(ModelMatrix, position);
		WVM = ProjectionMatrix * ViewMatrix * ModelMatrix;
#pragma endregion Mathematics
		string ip = i->second.GetIP();
		/*	string UserColor = i->second.GetUsername().substr(0,3);

		float r = ((ToLower(UserColor[0]) - 'a')*10.0f) / 255.f;
		float g = ((ToLower(UserColor[1]) - 'a')*10.0f) / 255.f;
		float b = ((ToLower(UserColor[2]) - 'a')*10.0f) / 255.f;*/
		//float value = ((char(UserColor[0])- char(UserColor[1])) * 20.0f) / 255.0f;
		//ShaderBuilder::LoadShader(Shader::At("Animation"))->
		//	Add_mat4("projection", ProjectionMatrix).
		//	Add_mat4("view", ViewMatrix).
		//	Add_mat4("model", ModelMatrix).
		//	Add_vec3("ucolor",vec3(r,g,b));
		//loaded_Models["Collada"]->Draw();
		ShaderBuilder::LoadShader(Shader::At("Animation"))->
			Add_mat4("WVM", WVM).
			Add_bool("isAnimated", true).
			Add_textures(loaded_Models["Collada"]->Textures);
		loaded_Models["Collada"]->Draw();

	}
	// default unit, internet connection independent
	vec3 position;

#pragma region Mathematics
	mat4 ModelMatrix;
	ModelMatrix = glm::translate(ModelMatrix, position);
#pragma endregion Mathematics
	vec3 color;
	mat4 CharMat;
	WVM = ProjectionMatrix * ViewMatrix * CharMat;
	//ShaderBuilder::LoadShader(Shader::At("Animation"))->
	//	Add_mat4("WVM", WVM).
	//	Add_bool("isAnimated", true).
	//	Add_textures(loaded_Models["Collada"]->Textures);
	//loaded_Models["Collada"]->Draw();
	//position = vec3(50, 0, 0);
	//ModelMatrix = glm::translate(ModelMatrix, position);
	//ShaderBuilder::LoadShader(Shader::At("Animation"))->
	//	Add_mat4("model", ModelMatrix);
	float time = float(GetTickCount());
	float SlowTime = time / 40.0f;
	mat4 landmat;
	WVM = ProjectionMatrix * ViewMatrix * landmat;
	ShaderBuilder::LoadShader(Shader::At("Animation"))->
		Add_mat4("WVM", WVM).
		Add_float("Texelation",100.0f).
		Add_textures(loaded_Models["Land"]->Textures).
		Add_bool("isAnimated", false);
	loaded_Models["Land"]->Draw();

	//loaded_Models["Collada"]->Draw();

#pragma region Grass
	{
		vector<vec4> ModelMatrixs;
		mat4 Animation;
		ShaderBuilder shader = *ShaderBuilder::LoadShader(Shader::At("Instanced"));
		for (int i = 0; i < 25; i++)
		{
			Animation = glm::rotate(mat4(),
				radians(
					cos(
						radians(
							fmod(SlowTime, 360.0f) + i * 10.0f
						)
					)
					*80.0f)
				, vec3(1, 0, 1));
			shader.Add_mat4("Animation[" + to_string(i) + "]", Animation);
		}

		mat4 WVM = ProjectionMatrix * ViewMatrix;

		ShaderBuilder::LoadShader(Shader::At("Instanced"))->
			Add_mat4("WVM", WVM).
			Add_float("time", time).
			Add_vec3("cameraPos", camera.GetCameraPosition()).
			Add_textures(grass.model.Textures).
			Add_bool("isAnimated", false);
		grass.Draw(grass.ObstaclesMat);
	}
#pragma endregion Grass
	//#pragma region Sea
	//	{
	//		vector<vec4> ModelMatrixs;
	//
	//		float time = float(GetTickCount());
	//		float SlowTime = time / 40.0f;
	//		mat4 Animation;
	//		ShaderBuilder shader = *ShaderBuilder::LoadShader(Shader::At("SeaAnimated"));
	//
	//		for (int i = 0; i < 8; i++)
	//		{
	//			Animation = glm::rotate(mat4(),
	//				radians(
	//					sin(
	//						radians(
	//							fmod(SlowTime, 360.0f)/* + i * 20.0f*/
	//						)
	//					)
	//					*40.0f)
	//				, vec3(1, 0, 1));// = glm::scale(mat4(), vec3(0, fmod(time, 1.0f) + 1.0f, 0));
	//			shader.Add_mat4("Animation[" + to_string(i) + "]", Animation);
	//		}
	//		//Animation = glm::scale(Animation, vec3(1, fmod(time, 1.0f) + 1.0f, 1));
	//
	//		mat4 WVM = ProjectionMatrix * ViewMatrix;
	//
	//		ShaderBuilder::LoadShader(Shader::At("SeaAnimated"))->
	//			Add_mat4("WVM", WVM).
	//			Add_float("time", time).
	//			Add_float("SlowTime", SlowTime).
	//			Add_vec3("cameraPos", camera.GetCameraPosition()).
	//			Add_bool("isAnimated", false);
	//		seaAnim.Draw(seaAnim.ObstaclesMat);
	//	}
	//#pragma endregion Sea

}