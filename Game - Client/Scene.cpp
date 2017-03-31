#include "Scene.h"



Scene::Scene(GlobalDataObject& Data,UserInterface& UI,FBO* Index, GlobalDataObject& InputToScene)
	:Data(Data), UI(UI), InputToScene(InputToScene)
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
	//ShowCursor(false);
	cursor.Initialize();

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
	mFBO["LakeReflectionBlur"].Initialize(1, 1, Shader());
	mFBO["LakeReflection"].Initialize(1, 1, Shader::At("PostProcessing"));
	//mFBO["Index"].Initialize(1, 1, Shader::At("PostProcessing"));
	IndexFBO->InitializeBig(1, 1, Shader::At("PostProcessing"));
	mAntiAliasing.InitializeMultiSample();
	championChat = new ChampionChat(Shader::At("Champion Chat"));
	championChat->CreateChatbox();
	//skyBox = new SkyBox;
	//skyBox->InitTexture();
	minimap.Initialize();
	//TODO: remove
	NPC npc;
	npc.Name = "House1";
	NPCs.push_back(npc);
	//OutlineObjects.push_back("House1");
#pragma region 2D Interface
	GenerateForm();


#pragma endregion 2D Interface


	loaded_Models.initialize_Models();
	minimap.UpdateMap();
//	Data.Map = &minimap;
	Data.Map.Map = minimap.GetMinimapData(Data.Map.Width, Data.Map.Height);
	grass.Initialize();
	//Players[Channel].push_back(Player(Unit_Data(vec3(0, 10, 0), "Katarina", 0, 0, 1),1));
	// remove next line
	//seaAnim.Initialize();
	//for (int i = 0; i < 8000; i++)
	//{
	//	vec3 ObstaclePos = loaded_Models["Land"]->meshes[0].mCollision->OnCollision(
	//		vec3(float(float(Stas::Maths::llrand() % 200000) - 100000) / 1000.0f, 0,
	//		float(float(Stas::Maths::llrand() % 200000) - 100000) / 1000.0f));
	//	vec3 ObstacleRotation(float(rand() % 200 - 100) / 100.0f,float(rand()%200 - 100)/100.0f, float(rand() % 200 - 100) / 100.0f);
	//	//Obstacles.push_back(ObstaclePos);
	//	//rotate
	//	//translate
	//	mat4 ModelMat = glm::translate(mat4(), ObstaclePos);
	//	ModelMat = glm::rotate(ModelMat, glm::radians(60.0f) ,ObstacleRotation);
	//	grass.ObstaclesMat.push_back(ModelMat);

	//}
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
	glStencilFunc(GL_ALWAYS, 1, 1);
	glStencilMask(1);
	glClearStencil(0);
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);

	glDepthMask(GL_TRUE);
	glEnable(GL_CLIP_DISTANCE0);


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
	vec2 Position;
	UI.root = new UIElement("Root", "");

	/*UIElement* GreyCover = new UIElement("GreyCover", "Interface/GreyCover.png",0);
	Position = vec2(0, 0);
	GreyCover->TopLeft = Position;
	GreyCover->SetByTrueSize(Position);
	GreyCover->innerText = "PAUSE";
	root->AppendChild(GreyCover);*/

	UIElement* UsernameElement = new UIElement("Username", "Interface/Textbox.png");
	Position = vec2(10, 80);
	UsernameElement->TopLeft = Position;
	UsernameElement->SetByTrueSize(Position);
	UsernameElement->AddHoverEvent([]
	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/TextboxHovered.png"); });
	UsernameElement->AddHoverDoneEvent([]
	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/Textbox.png"); });
	UsernameElement->AddReturnDefaultEvent([]
	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/Textbox.png"); });
	UsernameElement->AddClickEvent([]
	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/TextboxSelected.png"); });
	UsernameElement->AddTextChangedEvent([]
	(UIElement* Element)mutable-> void {
		if (Element->innerText.back() == '\r') 
		{
			TCP tcp; tcp.SendPacket(Element->innerText); Element->innerText.pop_back();
		}
	});
	UI.root->AppendChild(UsernameElement);

	UIElement* Element = new UIElement("Shop", "Interface/InventoryRow.png");
	Position = vec2(300, 160);
	Element->TopLeft = Position;
	Element->SetByTrueSize(Position);
	Element->Hide();
	UI.root->AppendChild(Element);

	Element = new UIElement("Shop-X", "Interface/X.png");
	Position = vec2(485, 165); // 5 padding
	Element->TopLeft = Position;
	Element->SetByTrueSize(Position);
	Element->AddClickEvent([]
	(UIElement* Element)mutable-> void { Element->Parent->Hide(); });
	UI.root->GetUIElement("Shop")->AppendChild(Element);

	Element = new UIElement("Shop-Gold", "Interface/Textbox.png");
	Position = vec2(300, 110); // 5 padding
	Element->TopLeft = Position;
	Element->SetByTrueSize(Position);
	UI.root->GetUIElement("Shop")->AppendChild(Element);

	//UIElement* StatsWindow = new UIElement("StatsWindow", "Interface/StatsWindow.png");
	//Position = vec2(710, 300);
	//StatsWindow->TopLeft = Position;
	//StatsWindow->SetByTrueSize(Position);
	//root->AppendChild(StatsWindow);

	//for (int i = 0; i < 4; i++)
	//{
	//	UIElement* StatsField = new UIElement("StatsField"+i, "Interface/StatsField.png");
	//	Position = vec2(710, 300 + (i * 50));
	//	StatsField->TopLeft = Position;
	//	StatsField->SetByTrueSize(Position);
	//	StatsField->AddHoverEvent([]
	//	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/StatsFieldHovered.png"); });
	//	StatsField->AddHoverDoneEvent([]
	//	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/StatsField.png"); });
	//	StatsField->AddReturnDefaultEvent([]
	//	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/StatsField.png"); });
	//	StatsField->AddClickEvent([]
	//	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/StatsFieldSelected.png"); });
	//	StatsWindow->AppendChild(StatsField);
	//}
	// load up for later use
	UIElement* EmptyHPBar = new UIElement("EmptyHPBar", "Interface/EmptyHPBar.png");
	UIElement* FullHPBar = new UIElement("FullHPBar", "Interface/FullHPBar.png");
}

void Scene::Draw_Units()
{

	// Draw To Depth Buffer
	DrawScene_Depth();
	// Draw Water
	/*DrawScene_Refraction();
	DrawScene_Reflection();*/
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
	DrawColladaShadow();
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
	mFBO["LakeReflection"].BindFrameBuffer();
	{
		SetCameraView();
		camera.SetCameraPosition(vec3(camera.CameraPositionCalculated.x, -camera.CameraPositionCalculated.y, camera.CameraPositionCalculated.z));
		camera.InvertPitch();
		SetCameraView();
		DrawSky();
		DrawCollada();
		//DrawGround(mSea.sReflection_Ground);
		//Draw_All_Units();
		//DrawEntities();
		//	Soldier->Draw(Shader("Basic Vertex Shader.glsl", "Basic Fragment Shader.glsl"));
		camera.SetCameraPosition(vec3(camera.CameraPositionCalculated.x, -camera.CameraPositionCalculated.y, camera.CameraPositionCalculated.z));
		camera.InvertPitch();
		SetCameraView();
	}

	mFBO["HBlurS"].BindFrameBuffer();//1
	mFBO["LakeReflection"].DrawFrameBuffer();//0
	mFBO["VBlurS"].BindFrameBuffer();//2 b
	mFBO["HBlurS"].DrawFrameBuffer();//1 d 
	mFBO["HBlur"].BindFrameBuffer();//3 b
	mFBO["VBlurS"].DrawFrameBuffer();//2 d
	mFBO["VBlur"].BindFrameBuffer();//4 b 
	mFBO["HBlur"].DrawFrameBuffer();//3 d
	mFBO["HBlurS"].BindFrameBuffer();//1 b
	mFBO["VBlur"].DrawFrameBuffer();//4 d
	mFBO["VBlurS"].BindFrameBuffer();//2 b
	mFBO["HBlurS"].DrawFrameBuffer();//1 d
	mFBO["LakeReflection"].BindFrameBuffer();//5 b
	mFBO["VBlurS"].DrawFrameBuffer();//2 d

}
void Scene::DrawScene_NoEffect()
{
	mAntiAliasing.BindFrameBuffer();
#pragma region 3D Elements
	SetCameraView();
	DrawSky();
	//DrawGround(Shader::At("Ground"));
	DrawCollada();
	//DrawEntities();
	//DrawSea();
	DrawSeaAnimated();
	DrawUI();
#pragma endregion 3D Elements
	mAntiAliasing.CopyBuffer(mFBO["Post Processing"].PostProcessingFBO);
	FBO::UnbindFrameBuffer();
	mFBO["Post Processing"].DrawFrameBuffer();

}
void Scene::DrawScene_PostProcessing()
{
	mAntiAliasing.BindFrameBuffer();
#pragma region 3D Elements
	glEnable(GL_CLIP_DISTANCE0);

	SetCameraView();
	DrawSky();
	//DrawGround(Shader::At("Ground"));
	DrawOutlineObjects();
	Outline();
	DrawCollada();
	//DrawWater();
	DrawUI();

	//DrawEntities();
	//DrawSea();
	DrawSeaAnimated();
	
#pragma endregion 3D Elements

	mAntiAliasing.CopyBuffer(mFBO["Post Processing"].PostProcessingFBO);
	mFBO["HBlurS"].BindFrameBuffer();//1
	mFBO["Post Processing"].DrawFrameBuffer();//0
	mFBO["VBlurS"].BindFrameBuffer();//2 b
	mFBO["HBlurS"].DrawFrameBuffer();//1 d 
	mFBO["HBlur"].BindFrameBuffer();//3 b
	mFBO["VBlurS"].DrawFrameBuffer();//2 d
	mFBO["VBlur"].BindFrameBuffer();//4 b 
	mFBO["HBlur"].DrawFrameBuffer();//3 d
	mFBO["HBlurS"].BindFrameBuffer();//1 b
	mFBO["VBlur"].DrawFrameBuffer();//4 d
	mFBO["VBlurS"].BindFrameBuffer();//2 b
	mFBO["HBlurS"].DrawFrameBuffer();//1 d
	mFBO["Basic"].BindFrameBuffer();//5 b
	mFBO["VBlurS"].DrawFrameBuffer();//2 d


	//mBright.BindFrameBuffer();
	//mPostProcessing.DrawFrameBuffer();
	// Draw Shine
	//DrawGaussicEffect();

	//LastLayer.BindFrameBuffer();
	//mVBlurS.DrawFrameBuffer();
	// uniform textures
	FBO::UnbindFrameBuffer();

	vector<GLuint> Textures = { mFBO["Basic"].texture,mFBO["Post Processing"].texture};
	vector<string> ShaderNames = { "ourShine","ourTexture" };
	mFBO["Combine"].DrawDirectly(Textures,ShaderNames);
	
	mFBO["Combine"].DrawFrameBuffer();
	// draw ui after postprocessing effect
	DrawUI();
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

void Scene::DrawIndexColor()
{
	// Draws All Entities with Color
	IndexFBO->BindFrameBuffer();
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	mat4 WVM = ProjectionMatrix*ViewMatrix;
	/*ShaderBuilder::LoadShader(Shader::At("Index"))->
		Add_mat4("WVM",WVM);
	loaded_Models["Land"]->Draw();
*/	
	ShaderBuilder::LoadShader(Shader::At("Index"))->
		Add_bool("indexType",true).
		Add_mat4("WVM", WVM);
	loaded_Models["Land"]->Draw();
	for(auto npc : NPCs)
	{
		WVM = ProjectionMatrix * ViewMatrix * Default::GetInstance().BlenderConversion;
		ShaderBuilder::LoadShader(Shader::At("Index"))->
			Add_bool("indexType", false).
			Add_float("Index", npc.npcID).
			Add_mat4("WVM", WVM);
		loaded_Models[npc.Name]->Draw();
	}

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
	/*{
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
	}*/
#pragma endregion Grass

}

void Scene::SetCameraView()
{
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

	for (auto p : Data.GetPlayerInformation())
	{
		p.second->DrawUI(ProjectionMatrix, ViewMatrix);
		vec3 pos = p.second->GetUnitData().GetPosition();
		mat4 ModelMatrix;
		ModelMatrix = translate(ModelMatrix, pos);
		championChat->Draw2D(p.second->CharacterName, ProjectionMatrix, ViewMatrix, ModelMatrix);
	}
	championChat->Draw("OpenGL", ProjectionMatrix, ViewMatrix, mat4());
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
	Text& text = Text::getInstance();
	text.RenderText(UI.Chat, 100.0f, 200.0f, 200.0f, 40.0f);

	color = vec3(1, 0, 0);
	SetCameraView();
	mat4 projectionMatrix = glm::perspective(radians(120.0f),
		float(mouse.GetWindowSize().x / mouse.GetWindowSize().y), 1.0f, 1000.0f);
	ShaderBuilder::LoadShader(Shader::At("2D Text"))->Add_vec3("textColor", color);
	fps.CountFrame(Shader::At("2D Text"));
	cursor.Draw();
}

void Scene::DrawThreaded()
{
	cursor.Draw();

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
void Scene::DrawColladaShadow()
{
	mat4 WVM;
	vec3 NewLightPos = LightPosition + vec3(50.0 * sin(float(++counter) / 90.0f), 0, 0);
	// Light Source
	mat4 LightViewMatrix = glm::lookAt(NewLightPos, vec3(0.0f), vec3(0.0f, 1.0f, 0.0f));
	LightViewMatrix = ProjectionMatrix * LightViewMatrix;
	////for each (Player P in Data.GetPlayerInformation())
	//for (auto i = Data.GetPlayerInformation().begin(); i != Data.GetPlayerInformation().end(); i++)
	//{
	//	i->second->Draw(ProjectionMatrix, ViewMatrix);
	//}
	// default unit, internet connection independent
	vec3 position;
	mat4 ModelMatrix;
	ModelMatrix = glm::translate(ModelMatrix, position);
	vec3 color;
	mat4 CharMat;
	WVM = ProjectionMatrix * ViewMatrix * CharMat;

	float time = float(GetTickCount());
	float SlowTime = time / 40.0f;
	mat4 landmat;
	WVM = ProjectionMatrix * ViewMatrix * landmat;

	// light source
	mat4 LightModel = translate(mat4(), NewLightPos + vec3(0, -10, 0));
	WVM = ProjectionMatrix * ViewMatrix * LightModel;
	ShaderBuilder::LoadShader(Shader::At("AnimationShadow"))->
		Add_mat4("WVM", WVM).
		Add_bool("isAnimated", true).
		Add_float("Texelation", 1.0f).
		Add_textures(loaded_Models["Collada"]->Textures);
	loaded_Models["Collada"]->Draw();
	WVM = ProjectionMatrix * ViewMatrix;
	//
	/*uniform vec3 lightPos;
	uniform vec3 cameraPos;
	uniform Material Wood;*/
	// Initialize Shader
	ShaderBuilder::LoadShader(Shader::At("AnimationShadow"))->
		Add_bool("isAnimated", false).
		Add_float("Texelation", 10.0f).
		Add_vec3("lightPos", NewLightPos).
		Add_vec3("cameraPos", -camera.GetCameraPosition()).
		Add_Material("Wood", Materials::GetInstance()["chrome"]).
		Add_textures(loaded_Models["House"]->Textures);
	// Draw NPC
	for (auto npc : NPCs)
	{
		WVM = ProjectionMatrix * ViewMatrix * Default::GetInstance().BlenderConversion;
		ShaderBuilder::LoadShader(Shader::At("AnimationShadow"))->
			Add_mat4("WVM", LightViewMatrix);
		loaded_Models[npc.Name]->Draw();
	}
	// Draw Players
	for (auto i = Data.GetPlayerInformation().begin(); i != Data.GetPlayerInformation().end(); i++)
	{
		i->second->DrawShadow(LightViewMatrix, mat4());
	}


}
void Scene::DrawCollada()
{
	mat4 WVM;
	// Light Source
	vec3 NewLightPos = LightPosition + vec3(50.0 * sin(float(++counter) / 90.0f), 0, 0);
	mat4 LightViewMatrix = glm::lookAt(NewLightPos, vec3(0.0f), vec3(0.0f, 1.0f, 0.0f));
	LightViewMatrix = ProjectionMatrix * LightViewMatrix;
	////for each (Player P in Data.GetPlayerInformation())
	//for (auto i = Data.GetPlayerInformation().begin(); i != Data.GetPlayerInformation().end(); i++)
	//{
	//	i->second->Draw(ProjectionMatrix, ViewMatrix);
	//}
	// default unit, internet connection independent
	vec3 position;
	mat4 ModelMatrix;
	ModelMatrix = glm::translate(ModelMatrix, position);
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
	/*LightPosition = vec3(rand()%50-25, rand() % 50 - 25, rand() % 50 - 25);
	LightPosition = -camera.GetCameraPosition();
	LightPosition = vec3(30, 50, 30);*/
	//LightPosition.y *= -1;
	//LightPosition.y *= -1;
	ShaderBuilder::LoadShader(Shader::At("Ground"))->
		Add_mat4("WVM", WVM).
		Add_mat4("Model", landmat).
		Add_float("Texelation", 25.0f).
		Add_vec3("lightPos", NewLightPos).
		Add_vec3("cameraPos", -camera.GetCameraPosition()).
		Add_textures(loaded_Models["Land"]->Textures).
		Add_texture("shadowMap", shadow->depthMap).
		Add_mat4("LightViewMatrix", LightViewMatrix).
		Add_bool("clip", true).
		Add_Material("Brick", Materials::GetInstance()["chrome"]).
		Add_Material("Grass", Materials::GetInstance()["emerald"]).
		Add_bool("isAnimated", false);
	loaded_Models["Land"]->Draw();

	/*landmat = translate(mat4(), vec3(0,0,0));
	WVM = ProjectionMatrix * ViewMatrix * landmat;
	ShaderBuilder::LoadShader(Shader::At("Water"))->
		Add_mat4("WVM", WVM).
		Add_mat4("Model", landmat).
		Add_float("Texelation", 25.0f).
		Add_vec3("lightPos", NewLightPos).
		Add_vec3("cameraPos", -camera.GetCameraPosition()).
		Add_textures(loaded_Models["Water"]->Textures).
		Add_texture("shadowMap", shadow->depthMap).
		Add_mat4("LightViewMatrix", LightViewMatrix).
		Add_Material("Brick", Materials::GetInstance()["chrome"]).
		Add_Material("Grass", Materials::GetInstance()["chrome"]).
		Add_float("time", fmod(GetTickCount(),100000000)).
		Add_texture("reflection",mFBO["LakeReflection"].texture).
		Add_bool("isAnimated", false);
	loaded_Models["Water"]->Draw();
*/
	

	// light source
	mat4 LightModel = translate(mat4(), NewLightPos + vec3(0, -10, 0));
	WVM = ProjectionMatrix * ViewMatrix * LightModel;
	ShaderBuilder::LoadShader(Shader::At("Animation"))->
		Add_mat4("WVM", WVM).
		Add_bool("isAnimated", false).
		Add_float("Texelation", 1.0f).
		Add_textures(loaded_Models["Sphere"]->Textures);
	loaded_Models["Sphere"]->Draw();
	WVM = ProjectionMatrix * ViewMatrix;
	//
	/*uniform vec3 lightPos;
	uniform vec3 cameraPos;
	uniform Material Wood;*/
	
#pragma region Houses


	//ShaderBuilder::LoadShader(Shader::At("Animation"))->
	//	Add_mat4("WVM", WVM).
	//	Add_bool("isAnimated", false).
	//	Add_float("Texelation", 10.0f).
	//	Add_vec3("lightPos", NewLightPos).
	//	Add_vec3("cameraPos", -camera.GetCameraPosition()).
	//	Add_Material("Wood", Materials::GetInstance()["chrome"]).
	//	Add_textures(loaded_Models["House"]->Textures);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//for (int i = -8; i < 8; i++)
	//{
	//	vec3 housePosition(i * 12, 0, 20);
	//	housePosition = loaded_Models["Land"]->meshes[0].mCollision->OnCollision(housePosition);

	//	mat4 ModelMat = translate(mat4(), housePosition);
	//	ModelMat = rotate(ModelMat, radians(180.0f), vec3(0, 1, 0));

	//	WVM = ProjectionMatrix * ViewMatrix * ModelMat;
	//	ShaderBuilder::LoadShader(Shader::At("Animation"))->
	//		Add_mat4("Model", ModelMat).
	//		Add_mat4("WVM", WVM);
	//	loaded_Models["House"]->Draw();
	//}
	//for (int i = -8; i < 8; i++)
	//{
	//	vec3 housePosition(i * 12, 0, -20);
	//	housePosition = loaded_Models["Land"]->meshes[0].mCollision->OnCollision(housePosition);
	//	mat4 ModelMat = translate(mat4(), housePosition);

	//	WVM = ProjectionMatrix * ViewMatrix * ModelMat;
	//	ShaderBuilder::LoadShader(Shader::At("Animation"))->
	//		Add_mat4("Model", ModelMat).
	//		Add_mat4("WVM", WVM);
	//	loaded_Models["House"]->Draw();
	//}
#pragma endregion

	//glEnable(GL_BLEND);
	//for (int j = 3; j < 4; j++)
	//{
	//	for (int i = -4; i < 4; i++)
	//	{
	//		mat4 ModelMat = translate(mat4(), vec3(i * 1, 0, j * 1));
	//		ModelMat = rotate(ModelMat, degrees(float((i+j) * 13)), vec3(0, 1, 0));
	//		WVM = ProjectionMatrix * ViewMatrix * ModelMat;
	//		ShaderBuilder::LoadShader(Shader::At("Animation"))->
	//			Add_textures(loaded_Models["Grass"]->Textures).
	//			Add_bool("isAnimated", true).
	//			Add_float("Texelation", 1.0f).
	//			Add_mat4("Model", ModelMat).
	//			Add_mat4("WVM", WVM);
	//		loaded_Models["Grass"]->Draw();
	//	}
	//}
	//glDisable(GL_BLEND);
	Core & core = Core::GetInstance();
	vector<Effect>* effects;
	if (core.Online)
	{
		effects = &Data.Effects;
	}
	else
	{
		effects = &OfflineDataObject::GetInstance().Effects;
	}
	for (auto e : *effects)
	{
		WVM = ProjectionMatrix * ViewMatrix * e.ModelMatrix;
		ShaderBuilder::LoadShader(Shader::At("Animation"))->
			Add_mat4("WVM", WVM).
			Add_bool("isAnimated", true).
			Add_float("Texelation", 1.0f).
			Add_textures(e.EffectModel->Textures);
		e.Draw();
	}
	for (auto npc : NPCs)
	{
		WVM = ProjectionMatrix * ViewMatrix * Default::GetInstance().BlenderConversion;
		ShaderBuilder::LoadShader(Shader::At("Animation"))->
			Add_mat4("WVM", WVM).
			Add_bool("isAnimated", false).
			Add_Material("Wood",Materials::GetInstance()["chrome"]).
			Add_float("Texelation", 1.0f).
			Add_textures(loaded_Models[npc.Name]->Textures);
		loaded_Models[npc.Name]->Draw();
	}
	//ShaderBuilder::LoadShader(Shader::At("Index"))->
	//	Add_mat4("WVM", WVM);
	//loaded_Models["Land"]->Draw();

	//loaded_Models["Collada"]->Draw();

#pragma region Grass
	/*{
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
		vec3 cameraPos = camera.GetCameraPosition();
		ShaderBuilder::LoadShader(Shader::At("Instanced"))->
			Add_mat4("WVM", WVM).
			Add_float("time", 0).
			Add_vec3("cameraPos", camera.GetCameraPosition()).
			Add_vec2("mousePos", mouse.GetMouseCoords()).
			Add_textures(grass.model.Textures).
			Add_bool("isAnimated", false);
		grass.Draw(grass.ObstaclesMat);
	}*/
#pragma endregion Grass


}


void Scene::DrawWater()
{
	glDisable(GL_CLIP_DISTANCE0);

	mat4 WVM = ProjectionMatrix * ViewMatrix;
	mat4 landmat;
	vec3 NewLightPos = LightPosition + vec3(50.0 * sin(float(counter) / 90.0f), 0, 0);

	ShaderBuilder::LoadShader(Shader::At("Water"))->
		Add_mat4("WVM", WVM).
		Add_bool("isAnimated", false).
		Add_float("Texelation", 10.0f).
		Add_vec3("lightPos", NewLightPos).
		Add_mat4("Model", landmat).
		Add_float("time", fmod(GetTickCount(), 100000000)).
		Add_vec3("cameraPos", -camera.GetCameraPosition()).
		Add_Material("Water", Materials::GetInstance()["water"]).
		Add_bool("clip", false).
		Add_texture("Texture3", mFBO["LakeReflection"].texture).
		Add_textures(loaded_Models["Water"]->Textures);
	loaded_Models["Water"]->Draw();
}
void Scene::Outline()
{
	// set stencil mode to only draw those not previous drawn
	glStencilFunc(GL_EQUAL, 0, 1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glStencilMask(0x00);

	// Hover NPC
	mat4 ModelMatrix = glm::scale(mat4(), vec3(1.02f));
	mat4 WVM = ProjectionMatrix * ViewMatrix* Default::GetInstance().BlenderConversion * ModelMatrix;
	for (auto o : InputToScene.Highlight)
	{
		ShaderBuilder::LoadShader(Shader::At("Color"))->
			Add_mat4("WVM", WVM).
			Add_bool("isAnimated", false).
			Add_vec3("Color", vec3(0, 0.8, 0.9));
		loaded_Models[o]->Draw();
	}

	Core & core = Core::GetInstance();
	if (core.Online)
	{
		// All Units get a base outline
		for (auto i = Data.GetPlayerInformation().begin(); i != Data.GetPlayerInformation().end(); i++)
		{
			i->second->DrawOutline(ProjectionMatrix, ViewMatrix, vec3(0.9));
		}
	}
	else
	{
		OfflineDataObject& offlineData = OfflineDataObject::GetInstance();
		offlineData.player.DrawOutline(ProjectionMatrix, ViewMatrix, vec3(0.9));
	}
	glDisable(GL_STENCIL_TEST);
}
void Scene::DrawOutlineObjects()
{
	mat4 WVM;
	for (auto npc : NPCs)
	{
		WVM = ProjectionMatrix * ViewMatrix * Default::GetInstance().BlenderConversion;
		ShaderBuilder::LoadShader(Shader::At("Animation"))->
			Add_mat4("WVM", WVM).
			Add_bool("isAnimated", false).
			Add_float("Texelation", 1.0f).
			Add_textures(loaded_Models[npc.Name]->Textures);
		loaded_Models[npc.Name]->Draw();
	}
	Core & core = Core::GetInstance();
	if (core.Online)
	{
		for (auto i = Data.GetPlayerInformation().begin(); i != Data.GetPlayerInformation().end(); i++)
		{
			i->second->Draw(ProjectionMatrix, ViewMatrix);
		}
	}
	else
	{
		OfflineDataObject& offlineData = OfflineDataObject::GetInstance();
		offlineData.player.Draw(ProjectionMatrix, ViewMatrix);
	}
}