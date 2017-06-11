#include "Scene.h"



Scene::Scene(UserInterface& UI,FBO* Index)
	:UI(UI)
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



	mFBO["Post Processing"].Initialize(1, 1, &Shader::At("PostProcessing"));
	mFBO["HBlur"].Initialize(2, 2, &Shader::At("HBlur"));
	mFBO["VBlur"].Initialize(2, 2, &Shader::At("VBlur"));
	mFBO["HBlurS"].Initialize(1, 1, &Shader::At("HBlur"));
	mFBO["VBlurS"].Initialize(1, 1, &Shader::At("VBlur"));
	mFBO["Bright"].Initialize(1, 1, &Shader::At("Bright"));
	mFBO["Combine"].Initialize(1, 1, &Shader::At("Combine"));
	mFBO["Gaussic Effect"].Initialize(1, 1, &Shader::At("Combine"));
	mFBO["RadialBlur"].Initialize(1, 1, new Shader("RadialBlur Vertex Shader.glsl", "RadialBlur Fragment Shader.glsl"));
	mFBO["Basic"].Initialize(1, 1, new Shader());
	mFBO["LakeReflectionBlur"].Initialize(1, 1, &Shader());
	mFBO["LakeReflection"].Initialize(1, 1, &Shader::At("PostProcessing"));
	//mFBO["Index"].Initialize(1, 1, Shader::At("PostProcessing"));
	IndexFBO->InitializeBig(1, 1, &Shader::At("PostProcessing"));
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
	XML xml = XMLReader().Read(R"(..\UserInterface\SceneUI.xml)");
	UI.root = new UIElement("Root", "");
	LoadForm(xml.Root, UI.root);
//	GenerateForm();


#pragma endregion 2D Interface


	minimap.UpdateMap();
//	Data.Map = &minimap;
	//Data.Map.Map = minimap.GetMinimapData(Data.Map.Width, Data.Map.Height);
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
	FrameData::Instance().Light_Pos = vec3(100, 50, 100);

	OfflineDataObject::Instance().level.LoadLevel();
	music = new Music("Soundtracks/Perion.wav");
	//music->PlayLoop();

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

	//music.Play();
	Camera::GetCamera(Camera::eCamera::Main).ProjectionMatrix =
		glm::perspective(0.77f, Mouse::Instanace().GetWindowSize().x / Mouse::Instanace().GetWindowSize().y,
			1.0f, 1000.0f);
	Camera& camera = Camera::GetCamera(Camera::eCamera::Current);

	//DrawIndexColor();
	Draw_Scene();
	//Draw_Units();

	glFlush();
	SwapBuffers(m_HDC);
}


void Scene::SetWindowHDC(HDC & hdc)
{
	this->m_HDC = hdc;
}

//void Scene::GenerateForm()
//{
//	
//	vec2 Position;
//	UI.root = new UIElement("Root", "");
//
//	/*UIElement* GreyCover = new UIElement("GreyCover", "Interface/GreyCover.png",0);
//	Position = vec2(0, 0);
//	GreyCover->TopLeft = Position;
//	GreyCover->SetByTrueSize(Position);
//	GreyCover->innerText = "PAUSE";
//	root->AppendChild(GreyCover);*/
//
//	UIElement* UsernameElement = new UIElement("Username", "Interface/Textbox.png");
//	Position = vec2(10, 80);
//	UsernameElement->Top = Position.y;
//	UsernameElement->Left = Position.x;
//	UsernameElement->SetByTrueSize(Position);
//	UsernameElement->AddHoverEvent([]
//	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/TextboxHovered.png"); });
//	UsernameElement->AddHoverDoneEvent([]
//	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/Textbox.png"); });
//	UsernameElement->AddReturnDefaultEvent([]
//	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/Textbox.png"); });
//	UsernameElement->AddClickEvent([]
//	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/TextboxSelected.png"); });
//	UsernameElement->AddTextChangedEvent([]
//	(UIElement* Element)mutable-> void {
//		if (Element->innerText.back() == '\r') 
//		{
//			TCP tcp; tcp.SendPacket(Element->innerText); Element->innerText.pop_back();
//		}
//	});
//	UI.root->AppendChild(UsernameElement);
//
//	UIElement* Element = new UIElement("Shop", "Interface/InventoryRow.png");
//	Position = vec2(300, 160);
//	Element->Top = Position.y;
//	Element->Left = Position.x;
//	Element->SetByTrueSize(Position);
//	Element->Hide();
//	UI.root->AppendChild(Element);
//
//	Element = new UIElement("Shop-X", "Interface/X.png");
//	Position = vec2(485, 165); // 5 padding
//	Element->Top = Position.y;
//	Element->Left = Position.x;
//	Element->Hide();
//	Element->SetByTrueSize(Position);
//	Element->AddClickEvent([]
//	(UIElement* Element)mutable-> void { Element->Parent->Hide(); });
//	UI.root->GetUIElement("Shop")->AppendChild(Element);
//
//	Element = new UIElement("Shop-Gold", "Interface/Textbox.png");
//	Position = vec2(300, 110); // 5 padding
//	Element->Top = Position.y;
//	Element->Left = Position.x;
//	Element->Hide();
//	Element->SetByTrueSize(Position);
//	UI.root->GetUIElement("Shop")->AppendChild(Element);
//
//	Element = new UIElement("Command Line", "Interface/Textbox.png");
//	Position = vec2(200, 400);
//	Element->writable = true;
//	Element->Top = Position.y;
//	Element->Left = Position.x;
//	Element->Bottom = 500;
//	Element->Right = 400;
//	//Element->SetByTrueSize(Position);
//	Element->AddHoverEvent([]
//	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/TextboxHovered.png"); });
//	Element->AddHoverDoneEvent([]
//	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/Textbox.png"); });
//	Element->AddReturnDefaultEvent([]
//	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/Textbox.png"); });
//	Element->AddClickEvent([]
//	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/TextboxSelected.png"); });
//	Element->AddTextChangedEvent([&]
//	(UIElement* Element)mutable-> void {
//		if (Element->innerText.back() == '\r')
//		{
//			Element->innerText.pop_back();
//			std::transform(Element->innerText.begin(),
//				Element->innerText.end(), Element->innerText.begin(), ::tolower);
//			if (Element->innerText == "wire")
//			{
//				OfflineDataObject& offlineData = OfflineDataObject::Instance();
//				offlineData.level.ReloadShaders(Shader::ImageType::Wire);
//			}
//			if (Element->innerText == "triangle")
//			{
//				OfflineDataObject& offlineData = OfflineDataObject::Instance();
//				offlineData.level.ReloadShaders(Shader::ImageType::Triangle);
//			}
//			Element->innerText.clear();
//		}
//	});
//	UI.root->AppendChild(Element);
//
//	Element = new UIElement("Other Camera", "Interface/Textbox.png");
//	Position = vec2(724, 400);
//	Element->writable = false;
//	Element->Top = Position.y;
//	Element->Left = Position.x;
//	Element->Bottom = 600;
//	Element->Right = 1024;
//	//Element->SetByTrueSize(Position);
//	Element->AddHoverEvent([]
//	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/TextboxHovered.png"); });
//	Element->AddHoverDoneEvent([]
//	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/Textbox.png"); });
//	Element->AddReturnDefaultEvent([]
//	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/Textbox.png"); });
//	Element->AddClickEvent([]
//	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/TextboxSelected.png"); });
//	Element->AddTextChangedEvent([&]
//	(UIElement* Element)mutable-> void {
//		if (Element->innerText.back() == '\r')
//		{
//			Element->innerText.pop_back();
//			std::transform(Element->innerText.begin(),
//				Element->innerText.end(), Element->innerText.begin(), ::tolower);
//			if (Element->innerText == "wire")
//			{
//				OfflineDataObject& offlineData = OfflineDataObject::Instance();
//				offlineData.level.ReloadShaders(Shader::ImageType::Wire);
//			}
//			if (Element->innerText == "triangle")
//			{
//				OfflineDataObject& offlineData = OfflineDataObject::Instance();
//				offlineData.level.ReloadShaders(Shader::ImageType::Triangle);
//			}
//			Element->innerText.clear();
//		}
//	});
//	FBO fbo;
//	Element->PicturePadding = 2;
//	Element->InitFramebuffer(fbo);
//	UI.root->AppendChild(Element);
//
//	// sound buttons
//	Element = new UIElement("Sound+", "Interface/Textbox.png");
//	Position = vec2(500, 20);
//	Element->writable = false;
//	Element->innerText = "+";
//	Element->Top = Position.y;
//	Element->Left = Position.x;
//	Element->Bottom = Position.y + 20;
//	Element->Right = Position.x + 20;
//	Element->AddHoverEvent([]
//	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/TextboxHovered.png"); });
//	Element->AddHoverDoneEvent([]
//	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/Textbox.png"); });
//	Element->AddReturnDefaultEvent([]
//	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/Textbox.png"); });
//	Element->AddClickEvent([&]
//	(UIElement* Element)mutable-> void { 
//		Element->ChangePicture("Interface/TextboxSelected.png");
//		this->music->AddVolume(0.1f);
//	});
//	UI.root->AppendChild(Element);
//
//	Element = new UIElement("Sound-", "Interface/Textbox.png");
//	Position = vec2(500, 40);
//	Element->writable = false;
//	Element->innerText = "-";
//	Element->Top = Position.y;
//	Element->Left = Position.x;
//	Element->Bottom = Position.y + 20;
//	Element->Right = Position.x + 20;
//	Element->AddHoverEvent([]
//	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/TextboxHovered.png"); });
//	Element->AddHoverDoneEvent([]
//	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/Textbox.png"); });
//	Element->AddReturnDefaultEvent([]
//	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/Textbox.png"); });
//	Element->AddClickEvent([&]
//	(UIElement* Element)mutable-> void { 
//		Element->ChangePicture("Interface/TextboxSelected.png"); 
//		this->music->AddVolume(-0.1f);
//	});
//	UI.root->AppendChild(Element);
//
//	//UIElement* StatsWindow = new UIElement("StatsWindow", "Interface/StatsWindow.png");
//	//Position = vec2(710, 300);
//	//StatsWindow->TopLeft = Position;
//	//StatsWindow->SetByTrueSize(Position);
//	//root->AppendChild(StatsWindow);
//
//	//for (int i = 0; i < 4; i++)
//	//{
//	//	UIElement* StatsField = new UIElement("StatsField"+i, "Interface/StatsField.png");
//	//	Position = vec2(710, 300 + (i * 50));
//	//	StatsField->TopLeft = Position;
//	//	StatsField->SetByTrueSize(Position);
//	//	StatsField->AddHoverEvent([]
//	//	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/StatsFieldHovered.png"); });
//	//	StatsField->AddHoverDoneEvent([]
//	//	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/StatsField.png"); });
//	//	StatsField->AddReturnDefaultEvent([]
//	//	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/StatsField.png"); });
//	//	StatsField->AddClickEvent([]
//	//	(UIElement* Element)mutable-> void { Element->ChangePicture("Interface/StatsFieldSelected.png"); });
//	//	StatsWindow->AppendChild(StatsField);
//	//}
//	// load up for later use
//	UIElement* EmptyHPBar = new UIElement("EmptyHPBar", "Interface/EmptyHPBar.png");
//	UIElement* FullHPBar = new UIElement("FullHPBar", "Interface/FullHPBar.png");
//
//}

void Scene::LoadForm(XML::Element & XML_Element, UIElement * uiElement)
{
	for (auto c : XML_Element.Children)
	{
		UIElement* Element = nullptr;
		if (c.Tag == "label")
		{
			Element = new UI::Textbox(c.GetAttribute("name"));
		}
		if (c.Tag == "textbox")
		{
			Element = new UI::Textbox(c.GetAttribute("name"));
		}
		if (c.Tag == "drawingarea")
		{
			Element = new UI::DrawingArea(c.GetAttribute("name"));
		}
		if (c.Tag == "button")
		{
			Element = new UI::Button(c.GetAttribute("name"));
		}
		//if (Element == nullptr) Element = new UIElement(c.GetAttribute("name"));
		if (c.GetAttribute("text") != "") Element->innerText = c.GetAttribute("text");
		if (c.GetAttribute("top") != "") Element->Set_Top(stoi(c.GetAttribute("top")));
		if (c.GetAttribute("left") != "") Element->Set_Left(stoi(c.GetAttribute("left")));
		if (c.GetAttribute("bottom") != "") Element->Set_Bottom(stoi(c.GetAttribute("bottom")));
		if (c.GetAttribute("right") != "") Element->Set_Right(stoi(c.GetAttribute("right")));
		if (c.GetAttribute("position") != "") Element->Set_Position(c.GetAttribute("position"));
		if (c.GetAttribute("width") != "") Element->Set_Width(stoi(c.GetAttribute("width")));
		if (c.GetAttribute("height") != "") Element->Set_Height(stoi(c.GetAttribute("height")));
		//if (c.GetAttribute("onclick") != "") Element->style.font = UIElement::Font();
		if (c.Tag == "drawingarea")
		{
			dynamic_cast<UI::DrawingArea*>(Element)->Resize();
		}
		UI.root->AppendChild(Element);
		LoadForm(c, Element);
	}
}

void Scene::Draw_Units()
{

	// Draw To Depth Buffer
	DrawScene_Depth();
	// Draw Water
	/*DrawScene_Refraction();
	DrawScene_Reflection();*/
	// Draw postprocesser
}
void Scene::Draw_Scene()
{

	FBO::UnbindFrameBuffer();
	mAntiAliasing.BindFrameBuffer();

	glEnable(GL_CLIP_DISTANCE0);
	Camera::GetCamera(Camera::eCamera::Current) = std::move(Camera::GetCamera(Camera::eCamera::Main));
	
	OfflineDataObject::Instance().level.Draw();

	ShaderBuilder::LoadShader(*mFBO["Post Processing"].shader)->
		Add_vec4("ScreenCoordinates", vec4(0, 0, 400, 400)).
		Add_vec4("FBO_Coordinates", vec4(0, 0, 400, 400));
	ShaderBuilder::LoadShader(*mFBO["Bright"].shader)->
		Add_vec4("ScreenCoordinates", vec4(0, 0, 400, 400)).
		Add_vec4("FBO_Coordinates", vec4(0, 0, 400, 400));
	
	mAntiAliasing.CopyBuffer(mFBO["Post Processing"].ID);
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

	// uniform textures
	FBO::UnbindFrameBuffer();
	glDisable(GL_DEPTH_TEST);
	vector<GLuint> Textures = { mFBO["Basic"].texture,mFBO["Post Processing"].texture };
	vector<string> ShaderNames = { "ourShine","ourTexture" };

	ShaderBuilder::LoadShader(*mFBO["Combine"].shader)->
		Add_vec4("FBO_Coordinates", vec4(0, 0, 400, 400)).
		Add_vec4("ScreenCoordinates", vec4(0, 0, 400, 400));
	mFBO["Combine"].DrawMultipleTextures(Textures, ShaderNames);
	glEnable(GL_DEPTH_TEST);
	// Set Draw Target to Element
	UIElement* element = UI.root->GetUIElement("Other Camera");
	UIElement::SetDrawTarget(element);
	
	// Change to new camera
	Camera::GetCamera(Camera::eCamera::Custom).SetCustomCameraValues(vec3(0, -100, 0), vec3(85, 65, 0));
	Camera::GetCamera(Camera::eCamera::Custom).ProjectionMatrix = Camera::GetCamera(Camera::eCamera::Main).ProjectionMatrix;
	Camera::GetCamera(Camera::eCamera::Current) = std::move(Camera::GetCamera(Camera::eCamera::Custom));

	// Draw Scene From Different Camera
	OfflineDataObject::Instance().level.Draw();
	// Change Back to main camera
	Camera::GetCamera(Camera::eCamera::Current) = std::move(Camera::GetCamera(Camera::eCamera::Main));

	FBO::UnbindFrameBuffer();
	glDisable(GL_DEPTH_TEST);
	// Draw UI
	DrawUI();
	glEnable(GL_DEPTH_TEST);


}
void Scene::DrawScene_Depth()
{
	Mouse& mouse = Mouse::Instanace();

	shadow->BindFrameBuffer();
	//Shadow_DrawGround(shadow->shader);
	//DrawColladaDistance();
	//DrawColladaShadow();
	// back to default framebuffer
	mFBO["Post Processing"].BindFrameBuffer();
	//glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, (int)mouse.GetWindowSize().x, (int)mouse.GetWindowSize().y);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}
void Scene::DrawScene_Refraction()
{
	mSea.BindRefraction();
	//DrawGround(mSea.sRefraction_Ground);
	//Draw_All_Units();
	//DrawEntities();
	//	Soldier->Draw(Shader("Basic Vertex Shader.glsl", "Basic Fragment Shader.glsl"));

}
void Scene::DrawScene_Reflection()
{
	Camera& camera = Camera::GetCamera(Camera::eCamera::Current);
	mFBO["LakeReflection"].BindFrameBuffer();
	{
		camera.Position = vec3(camera.Position.x, -camera.Position.y, camera.Position.z);
		camera.InvertPitch();
		//DrawGround(mSea.sReflection_Ground);
		//Draw_All_Units();
		//DrawEntities();
		//	Soldier->Draw(Shader("Basic Vertex Shader.glsl", "Basic Fragment Shader.glsl"));
		camera.Position = vec3(camera.Position.x, -camera.Position.y, camera.Position.z);
		camera.InvertPitch();
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
	//DrawGround(Shader::At("Ground"));
	//DrawEntities();
	//DrawSea();
	DrawUI();
#pragma endregion 3D Elements
	mAntiAliasing.CopyBuffer(mFBO["Post Processing"].ID);
	FBO::UnbindFrameBuffer();
	mFBO["Post Processing"].DrawFrameBuffer();

}
void Scene::Shadow_DrawGround(Shader& shader)
{

	//loaded_Models["Ground"]->DrawModel(l_ProjectionMatrix, l_ViewMatrix, ModelMatrix, shader); // TODO remove mat arguements
}

void Scene::DrawIndexColor()
{
	//// Draws All Entities with Color
	//IndexFBO->BindFrameBuffer();
	////glEnable(GL_BLEND);
	////glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//
	//
	//mat4 WVM = ProjectionMatrix*ViewMatrix;
	///*ShaderBuilder::LoadShader(Shader::At("Index"))->
	//	Add_mat4("WVM",WVM);
	//loaded_Models["Land"]->Draw();
	//*/
	//ShaderBuilder::LoadShader(Shader::At("Index"))->
	//	Add_bool("indexType",true).
	//	Add_mat4("WVM", WVM);
	//ModelsCollection::Instance()["Land"]->Draw();
	//for(auto npc : NPCs)
	//{
	//	WVM = ProjectionMatrix * ViewMatrix * Default::Instance().BlenderConversion;
	//	ShaderBuilder::LoadShader(Shader::At("Index"))->
	//		Add_bool("indexType", false).
	//		Add_float("Index", (float)npc.npcID).
	//		Add_mat4("WVM", WVM);
	//	ModelsCollection::Instance()[npc.Name]->Draw();
	//}
	//Core& core = Core::Instance();
	//if (!core.Online)
	//{
	//	OfflineDataObject& offlineData = OfflineDataObject::Instance();
	//	WVM = ProjectionMatrix * ViewMatrix * offlineData.player.unit_Data.GetModelMatrix();
	//	ShaderBuilder::LoadShader(Shader::At("Index"))->
	//		Add_bool("indexType", false).
	//		Add_float("Index", 5).
	//		Add_mat4("WVM", WVM);
	//	offlineData.player.unit_Data.Model_Data->Draw();
	//}
}

void Scene::DrawUI()
{
	Mouse& mouse = Mouse::Instanace();

	glm::mat4 projection = glm::ortho(0.0f, mouse.GetWindowSize().x,
		mouse.GetWindowSize().y, 0.0f);
	mat4 view, model;
	vec3 color = vec3(0, 1, 1);
	vec2 Center(mouse.GetWindowSize().x / 2, mouse.GetWindowSize().y / 2);
	// Official UI
	UI.root->Draw();
	//minimap.Change();
	
	
	
	
	//minimap.DrawMinimap(Data);
	////minimap.Draw(vec2(100, 100), vec2(400, 400));

	//for (auto p : Data.GetPlayerInformation())
	//{
	//	p.second->DrawUI(ProjectionMatrix, ViewMatrix);
	//	vec3 pos = p.second->GetUnitData().Position;
	//	mat4 ModelMatrix;
	//	ModelMatrix = translate(ModelMatrix, pos);
	//	//championChat->Draw2D(p.second->CharacterName, ProjectionMatrix, ViewMatrix, ModelMatrix);
	//}
	//championChat->Draw("OpenGL", ProjectionMatrix, ViewMatrix, mat4());
	///*else
	//{

	//	ShaderBuilder::LoadShader(Shader::At("2D Text"))->Add_mat4("projection", projection).
	//		Add_mat4("view", view).Add_mat4("model", model).
	//		Add_vec3("textColor", color).Add_texture("text", 0);
	//	text.RenderText("Loading . . .", 350.0f, 200.0f, 500.0f, 40.0f);
	//	UI.AcceptInput();
	//}*/

	//ShaderBuilder::LoadShader(Shader::At("2D Text"))->Add_mat4("projection", projection).
	//	Add_mat4("view", view).Add_mat4("model", model).
	//	Add_vec3("textColor", color).Add_texture("text", 0);
	//Text& text = Text::getInstance();
	//text.RenderText(UI.Chat, 100.0f, 200.0f, 200.0f, 40.0f);

	//color = vec3(1, 0, 0);
	//SetCameraView();
	//mat4 projectionMatrix = glm::perspective(radians(120.0f),
	//	float(mouse.GetWindowSize().x / mouse.GetWindowSize().y), 1.0f, 1000.0f);
	ShaderBuilder::LoadShader(Shader::At("2D Text"))->Add_vec3("textColor", color);
	fps.CountFrame(Shader::At("2D Text"));
	//cursor.Draw();
}
void Scene::Outline()
{
	//// set stencil mode to only draw those not previous drawn
	//glStencilFunc(GL_EQUAL, 0, 1);
	//glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	//glStencilMask(0x00);

	//// Hover NPC
	//mat4 ModelMatrix = glm::scale(mat4(), vec3(1.02f));
	//mat4 WVM = ProjectionMatrix * ViewMatrix* Default::Instance().BlenderConversion * ModelMatrix;
	//for (auto o : InputToScene.Highlight)
	//{
	//	ShaderBuilder::LoadShader(Shader::At("Color"))->
	//		Add_mat4("WVM", WVM).
	//		Add_bool("isAnimated", false).
	//		Add_vec3("Color", vec3(0, 0.8, 0.9));
	//	ModelsCollection::Instance()[o]->Draw();
	//}

	//Core & core = Core::Instance();
	//if (core.Online)
	//{
	//	// All Units get a base outline
	//	/*for (auto i = Data.GetPlayerInformation().begin(); i != Data.GetPlayerInformation().end(); i++)
	//	{
	//		i->second->DrawOutline(ProjectionMatrix, ViewMatrix, vec3(0.9f));
	//	}*/
	//}
	//else
	//{
	//	OfflineDataObject& offlineData = OfflineDataObject::Instance();
	//	//offlineData.player.DrawOutline(ProjectionMatrix, ViewMatrix, vec3(0.9));
	///*	if (InputToScene.Highlight)*/
	//}
	//glDisable(GL_STENCIL_TEST);
}
void Scene::DrawOutlineObjects()
{
	/*mat4 WVM;
	for (auto npc : NPCs)
	{
		WVM = ProjectionMatrix * ViewMatrix * Default::Instance().BlenderConversion;
		ShaderBuilder::LoadShader(Shader::At("Animation"))->
			Add_mat4("WVM", WVM).
	Add_bool("isAnimated", false).
	Add_float("Texelation", 1.0f).
	Add_textures(ModelsCollection::Instance()[npc.Name]->Textures);
	ModelsCollection::Instance()[npc.Name]->Draw();
	}
	Core & core = Core::Instance();
	if (core.Online)
	{
		for (auto i = Data.GetPlayerInformation().begin(); i != Data.GetPlayerInformation().end(); i++)
		{
			i->second->Draw();
		}
	}
	else
	{
		OfflineDataObject& offlineData = OfflineDataObject::Instance();
		offlineData.player.Draw();
	}*/
}