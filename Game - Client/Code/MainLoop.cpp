//#include "MainLoop.h"
//#define _OBJECT_SIZE OBJECT_SIZE 
//
//HDC MainLoop::m_hDC;
//bool MainLoop::IsLoaded = false;
//Camera MainLoop::camera;
//mat4 MainLoop::ProjectionMatrix;
//mat4 MainLoop::ViewMatrix;
//unsigned int MainLoop::ClientID = 0;
//MainLoop::MainLoop()
//{
//	LightPosition = vec3(0, 40, 0);
//}
///*
//``Releases Data, Joins Threads``
//*/
//MainLoop::~MainLoop()
//{
//	client._CloseConnection(ClientID);
//	if (Bar != NULL)
//		delete Bar;
//	if (shadow != NULL)
//		delete shadow;
//}
///*
//``Sets up Connection To Server, Starts OpenGL engines``
//*/
//void MainLoop::Initalize()
//{
//	// Connect the Client to Server
//	if (Offline_Flag)
//	{
//
//	}
//	else
//	{
//		future<bool> ClientConnectionAttemp = std::async(&Client::_Initialize, &client);
//	}
//	// Generate OpenGL engines
//	glewExperimental = TRUE;
//	GLenum err = glewInit();
//	// Reset OpenGL Buffed Mathematics
//	//Bar = new _2D_Interface();
//
//	inventory = new Inventory();
//	glLoadIdentity();
//	tLoading_Screen = Loading_Screen(mouse.GetWindowSize(), m_hDC);
//	text.Initialize();
//
//	Shader::LoadShaders();
//	shadow = new Shadow_Mapping();
//	mSea.Initialize();
//	mPreEffect.Initialize();
//	mPostProcessing.Initialize(1,1, Shader::At("PostProcessing"));
//	mHBlur.Initialize(2, 2, Shader::At("HBlur"));
//	mVBlur.Initialize(2, 2, Shader::At("VBlur"));
//	mHBlurS.Initialize(1, 1, Shader::At("HBlur"));
//	mVBlurS.Initialize(1, 1, Shader::At("VBlur"));
//	mBright.Initialize(1, 1, Shader::At("Bright"));
//	mGaussicEffect.Initialize(1,1, Shader("PostProcessing Vertex Shader.glsl", "Combine Fragment Shader.glsl"));
//	mCombine.Initialize(1 ,1, Shader::At("Combine"));
//	mRadialBlur.Initialize(1 ,1, Shader("RadialBlur Vertex Shader.glsl", "RadialBlur Fragment Shader.glsl"));
//	mGammaCorrection.Initialize(1, 1, Shader("PostProcessing Vertex Shader.glsl", "Gamma Correction Fragment Shader.glsl"));
//	mAntiAliasing.InitializeMultiSample();
//	LastLayer.Initialize(1, 1, Shader());
//	mMGrass = new MathGrass();
//	championChat = new ChampionChat(Shader::At("Champion Chat"));
//	for (int i = 0; i < 1; i++)
//	{
//		m_GrassObjects.push_back(new GrassObjects);
//	}
//	if (Offline_Flag)
//	{
//
//	}
//	else
//	{
//		SocketLoop = std::async(&MainLoop::ServerClient_DataLoop, this);
//		SocketLoop.wait(); // Set SocketLoop ready for execution
//	}
//
//	// Retreieve Data From Server/DataBase // MUST BE EXECUTED AFTER ALL MODELS ARE LOADED
////	Connect = thread(&MainLoop::GenerateConnection, this, "Receive ClientID"); // GenerateConnection("Receive ClientID")
//}
//void MainLoop::Initialize()
//{
//	game.Initialize();
//}
///*
//Load Models mostly
//*/
///*
//``Bind Objects to Graphic Card``
//*/
//void MainLoop::BindGame()
//{
//	m_Loaded_Models.Bind_Texture_To_Models();
//	// assign Model Data to local class Variables ( Pointers ) 
//	//mSkyBox = m_Loaded_Models["Sky"];//Loaded_Models::e_SkyBox];
//	//mGround = m_Loaded_Models["Ground"];
//	//mGrass = m_Loaded_Models["Grass"];
//
//	mGround_Collision = &Ground_Collision::Instance();
//	mGround_Collision->SetGround(mGround->MappedVertices);
//	mMGrass->Init();
//	//Soldier = new Model("Collada/ArmyPilot.dae");
//	Soldier = new Model("Katarina/Katarina.obj");
//
//	//Katarina = new Model("Katarina/Katarina.obj");
//}
///*
//``Compiles Scene and Draws it``
//*/
//void MainLoop::Draw_Scene() // general function
//{
//	if (!IsLoaded)
//	{
//		test();
//		glBindFramebuffer(GL_FRAMEBUFFER, 0);
//	//	glEnable(GL_DEPTH_TEST);
//		glEnable(GL_STENCIL_TEST);
//
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
//		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
//
//		glDepthMask(GL_TRUE);
//		glClearColor(0, 0, 0, 0);
//		mRadialBlur.BindFrameBuffer();
//		Draw_Loading_Screen();
//		
//		FBO::UnbindFrameBuffer();
//		mRadialBlur.DrawFrameBuffer();
//		DrawUI();
//		mMGrass->Draw(mat4());
//		glFlush();
//		SwapBuffers(m_hDC);
//		return;
//	}
//	glBindFramebuffer(GL_FRAMEBUFFER, 0);
//	glEnable(GL_DEPTH_TEST);
//	glEnable(GL_STENCIL_TEST);
//	
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
//	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
//
//	glDepthMask(GL_TRUE);
//
//#pragma region Explosion
//	// TODO:
//	if (keyboard.isKeyPressed(SPACE))
//	{
//		/*for each(Unit_Data Unit in m_Unit_Data[Channel])
//		{
//			Unit.GetModelData()->Explode();
//		}*/
//		Channel++;
//		if (Channel > 1)
//		{
//			Channel = 0;
//		}
//	}
//	//if (keyboard.isKeyPressed(A_Key))
//	//{
//	//	for each(Unit_Data Unit in m_Unit_Data[Channel])
//	//	{
//	//		Unit.GetModelData()->Recover_Explosion();
//	//	}
//	//}
//#pragma endregion
//	UserInput();
//	Draw_All_Static_Objects_And_Units();
//	// draw to screen
//	
//	//glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);
//
//	
//	//mPostProcessing.DrawFrameBuffer();
//	//mVBlur.DrawFrameBuffer();
//
//	glFlush();
//	SwapBuffers(m_hDC);
//}
//void MainLoop::Loop()
//{
//	//if (IsLoaded)
//		game.Loop();
//}
///*
//``Sends Input to Server to receive Updated Unit Locations``
//*/
//void MainLoop::ServerClient_DataLoop()
//{
//	SendData();
//	Counter++;
//	DataUpdateRequest = std::async(&TransferedData::UpdateData, &UpdatedData, client._AsyncReceiveMessage(), Counter);
//	if (DataUpdateRequest.get())
//	{
//		UpdatedData.Unit = UpdatedData.GetUnitData();
//	}
//}
///*
//``Draws the background and Game Units``
//*/
//void MainLoop::Draw_All_Static_Objects_And_Units()
//{
//
//	// Adjust framerate to Real Time
//	Camera::CalculateTimeDelta(); // should be placed in the dataloop as the server parameter
//
//	// Socket Data Loop
//	if (Offline_Flag)
//	{
//		OfflineDataLoop();
//	}
//	else
//	{
//		if (SocketLoop._Is_ready())
//		{
//			Set_Unit_Data();
//			// Get Data from Server to Draw
//			SocketLoop = std::async(&MainLoop::ServerClient_DataLoop, this);
//		}
//	}
//
//	// Get Camera Matrix
//	camera.GetUpdatedCamera();
//	// Draw To Depth Buffer
//	DrawScene_Depth();
//	// Draw Water
//	DrawScene_Refraction();
//	DrawScene_Reflection();
//	// Draw postprocesser
//	DrawScene_PostProcessing();
//}
//void MainLoop::DrawScene_Depth()
//{
//	Draw_To_Depth_Buffer();
//	{
//		SetCameraView();
//		//Shadow_DrawGround(shadow->shader);
//		//Draw_All_Units(m_Unit_Data[Channel], shadow->shader);
//	}
//}
//void MainLoop::Draw_To_Depth_Buffer()
//{
//	shadow->BindFrameBuffer();
//	Shadow_DrawGround(shadow->shader);
//	Draw_All_Units(shadow->shader);
//
//	// back to default framebuffer
//	mPostProcessing.BindFrameBuffer();
//	//glBindFramebuffer(GL_FRAMEBUFFER, 0);
//	glViewport(0, 0, (int)mouse.GetWindowSize().x, (int)mouse.GetWindowSize().y);
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//}
//void MainLoop::Draw_All_Units(Shader& shader)
//{
//	//mat4 l_ProjectionMatrix = glm::perspective(radians(120.0f),
//	//	float(mouse.GetWindowSize().x / mouse.GetWindowSize().y), 1.0f,1000.0f);
//	//mat4 l_ViewMatrix = glm::lookAt(LightPosition, vec3(), vec3(1.0f,1.0f,1.0f));
//	//mat4 l_LightView = l_ProjectionMatrix * l_ViewMatrix;
//	//for each (Unit_Data i in m_Unit_Data[Channel])
//	//{
//	//	if (i.GetClientID() == 0)
//	//		continue;
//	//	//vec3 UnitPosition = Calculate_Ground_Collision(i);
//	//	vec3 UnitPosition = i.GetPosition();
//	//	ModelMatrix = mat4();
//	//	ModelMatrix = glm::translate(ModelMatrix, UnitPosition);
//	//	ModelMatrix = glm::rotate(ModelMatrix, 0.0f, vec3(1, 0, 0));
//	////	ModelMatrix = glm::rotate(ModelMatrix, radians((float)Counter), vec3(0, 1, 0));
//	//	ModelMatrix = glm::rotate(ModelMatrix, 0.0f, vec3(0, 0, 1));
//	//	i.GetModelData()->DrawModel(l_ProjectionMatrix, l_ViewMatrix, ModelMatrix, shader);
//
//	//}
//}
//void MainLoop::Shadow_DrawGround(Shader& shader)
//{
//	mat4 l_ProjectionMatrix = glm::perspective(radians(120.0f),
//		float(mouse.GetWindowSize().x / mouse.GetWindowSize().y), 1.0f, 1000.0f);
//	mat4 l_ViewMatrix = glm::lookAt(LightPosition, vec3(0.0f), vec3(1.0f, 1.0f, 1.0f));
//	ModelMatrix = mat4(); // for now				
//	mGround->DrawModel(l_ProjectionMatrix, l_ViewMatrix, ModelMatrix, shader); // TODO remove mat arguements
//}
//void MainLoop::DrawScene_Refraction()
//{
//	mSea.BindRefraction();
//
//	SetCameraView();
//	DrawSky();
//	DrawGround(mSea.sRefraction_Ground);
//	//Draw_All_Units();
//	DrawEntities();
////	Soldier->Draw(Shader("Basic Vertex Shader.glsl", "Basic Fragment Shader.glsl"));
//
//}
//void MainLoop::DrawScene_Reflection()
//{
//	mSea.BindReflection();
//	{
//		SetCameraView();
//		camera.SetCameraPosition(vec3(camera.CameraPositionCalculated.x, -camera.CameraPositionCalculated.y, camera.CameraPositionCalculated.z));
//		camera.InvertPitch();
//		SetCameraView();
//		DrawSky();
//		DrawGround(mSea.sReflection_Ground);
//		//Draw_All_Units();
//		DrawEntities();
//	//	Soldier->Draw(Shader("Basic Vertex Shader.glsl", "Basic Fragment Shader.glsl"));
//		camera.SetCameraPosition(vec3(camera.CameraPositionCalculated.x, -camera.CameraPositionCalculated.y, camera.CameraPositionCalculated.z));
//		camera.InvertPitch();
//		SetCameraView();
//	}
//}
//void MainLoop::DrawScene_PostProcessing()
//{
//	mAntiAliasing.BindFrameBuffer();
//
//	SetCameraView();
//
//	DrawSky();
//	DrawGround(Shader::At("Ground"));
//	Draw_All_Units();
//	DrawEntities();
//	DrawSea();
//	DrawUI();
//
//	mAntiAliasing.CopyBuffer(mPostProcessing.PostProcessingFBO);
//
//	mBright.BindFrameBuffer();
//	mPostProcessing.DrawFrameBuffer();
//	// Draw Shine
//	DrawGaussicEffect();
//
//	LastLayer.BindFrameBuffer();
//	mVBlurS.DrawFrameBuffer();
//	// uniform textures
//	mGammaCorrection.BindFrameBuffer();
//
//	vector<GLuint> Textures = { LastLayer.texture,mPostProcessing.texture};
//	vector<string> ShaderNames = {"ourShine","ourTexture"};
//	mCombine.DrawDirectly(Textures,ShaderNames);
//	//LastLayer.DrawFrameBuffer();
//	FBO::UnbindFrameBuffer();
//	mGammaCorrection.DrawFrameBuffer();
//	//shadow->Draw();
//	//mPostProcessing.DrawFrameBuffer();
//}
//void MainLoop::DrawPreBuffer()
//{
//	mPreEffect.DrawFrameBuffer();
//}
//void MainLoop::DrawGaussicEffect()
//{
//	// Bright Scene
//	LastLayer.BindFrameBuffer();
//	mBright.DrawFrameBuffer();
//
//	// Bright Model
//	mGaussicEffect.BindFrameBuffer();
//	Draw_All_Units_Gaussic();
//
//	// Combine
//	vector<GLuint> Textures = { LastLayer.texture,mGaussicEffect.texture };
//	vector<string> ShaderNames = { "ourShine","ourTexture" };
//
//	mHBlur.BindFrameBuffer();
//	mCombine.DrawDirectly(Textures,ShaderNames);
//	mVBlur.BindFrameBuffer();
//	mHBlur.DrawFrameBuffer();
//	for (int i = 0; i < 4; i++)
//	{
//		mHBlur.BindFrameBuffer();
//		mVBlur.DrawFrameBuffer();
//		mVBlur.BindFrameBuffer();
//		mHBlur.DrawFrameBuffer();
//	}
//	mHBlurS.BindFrameBuffer();
//	mVBlur.DrawFrameBuffer();
//	mVBlurS.BindFrameBuffer();
//	mHBlurS.DrawFrameBuffer();
//
//}
//void MainLoop::Draw_All_Units_Gaussic()
//{
//	mat4 l_ProjectionMatrix = glm::perspective(radians(120.0f),
//		float(mouse.GetWindowSize().x / mouse.GetWindowSize().y), 1.0f, 1000.0f);
//	mat4 l_ViewMatrix = glm::lookAt(LightPosition, vec3(0.0f), vec3(1.0f, 1.0f, 1.0f));
//	mat4 l_LightView = l_ProjectionMatrix * l_ViewMatrix;
//	for each (Unit_Data i in m_Unit_Data[Channel])
//	{
//		if (i.GetClientID() == 0)
//			continue;
//		//vec3 UnitPosition = Calculate_Ground_Collision(i);
//		vec3 UnitPosition = i.GetPosition();
//		ModelMatrix = mat4();
//		ModelMatrix = glm::translate(ModelMatrix, UnitPosition);
//		ModelMatrix = glm::rotate(ModelMatrix, 0.0f, vec3(1, 0, 0));
//			ModelMatrix = glm::rotate(ModelMatrix, radians((float)Counter), vec3(0, 1, 0));
//		ModelMatrix = glm::rotate(ModelMatrix, 0.0f, vec3(0, 0, 1));
//		mat4 WorldSpace = ProjectionMatrix * ViewMatrix * ModelMatrix;
//		Loader* u = i.GetModelData();
//		float AmbientStrenth = 1.0f;
//		float zeroVar = 0.0f;
//		ShaderBuilder::LoadShader(Shader::At("Gaussic"))->
//			Add_mat4("projection", ProjectionMatrix).Add_mat4("view", ViewMatrix).Add_mat4("model", ModelMatrix).
//			Add_mat4("worldSpace", WorldSpace).Add_mat4("lightSpaceMatrix", l_LightView).
//			Add_vec3("lightPos", vec3(0, 20, 0)).Add_vec3("cameraPos", camera.GetCameraPosition()).
//			Add_float("GravityHeight", zeroVar).Add_float("time", zeroVar).Add_float("AmbientStrength", AmbientStrenth).
//			Add_texture("ourTexture", u->texture).Add_texture("ourShadow", shadow->depthMap).Add_texture("ourShine", u->Shine);
//
//		i.GetModelData()->DrawModel();
//
//
//	}
//}
//
///*
//``Draws All Dynamic Units Stored And Passed from the DataBase``
//*/
//void MainLoop::Draw_All_Units()
//{
//	mat4 l_ProjectionMatrix = glm::perspective(radians(120.0f),
//		float(mouse.GetWindowSize().x / mouse.GetWindowSize().y), 1.0f, 1000.0f);
//	mat4 l_ViewMatrix = glm::lookAt(LightPosition, vec3(0.0f), vec3(1.0f, 1.0f, 1.0f));
//	mat4 l_LightView = l_ProjectionMatrix * l_ViewMatrix;
//	//for each (Player p in Players[Channel])
//	//{
//	//	if (i.GetClientID() == 0)
//	//		continue;
//	//	//vec3 UnitPosition = Calculate_Ground_Collision(i);
//	//	vec3 UnitPosition = i.GetPosition();
//	//	//UnitPosition = mGround_Collision.Calculate_Ground_Collision(UnitPosition);
//	//	ModelMatrix = mat4();
//	//	ModelMatrix = glm::translate(ModelMatrix, UnitPosition);
//	//	ModelMatrix = glm::rotate(ModelMatrix, 0.0f, vec3(1, 0, 0));
//	////	ModelMatrix = glm::rotate(ModelMatrix, radians((float)Counter), vec3(0, 1, 0));
//	//	ModelMatrix = glm::rotate(ModelMatrix, 0.0f, vec3(0, 0, 1));
//	//	mat4 WorldSpace = ProjectionMatrix * ViewMatrix * ModelMatrix;
//	//	//i.GetModelData()->DrawModel(ProjectionMatrix, ViewMatrix, ModelMatrix
//	//	//	, shadow->depthMap, l_LightView, NULL, 0);
//	//
//	//	Loader* u = i.GetModelData();
//	//	float AmbientStrenth = 1.0f;
//	//	float zeroVar = 0.0f;
//
//	//	ShaderBuilder::LoadShader(Shader::At("Katarina"))->
//	//		Add_mat4("projection", ProjectionMatrix).Add_mat4("view", ViewMatrix).Add_mat4("model", ModelMatrix).
//	//		Add_mat4("worldSpace", WorldSpace).Add_mat4("lightSpaceMatrix", l_LightView).
//	//		Add_vec3("lightPos", vec3(0, 20, 0)).Add_vec3("cameraPos", camera.GetCameraPosition()).
//	//		Add_float("GravityHeight", zeroVar).Add_float("time", zeroVar).Add_float("AmbientStrength", AmbientStrenth).
//	//		Add_texture("ourTexture",u->texture).Add_texture("ourShadow",shadow->depthMap).Add_texture("ourShine",u->Shine);
//	//	//i.GetModelData()->DrawModel();
//	//	Soldier->Draw();
//	//}
//}
///*
//``full data Ground Draw``
//*/
//void MainLoop::DrawGround(Shader& shader)
//{
//	mat4 l_ProjectionMatrix = glm::perspective(radians(120.0f),
//		float(mouse.GetWindowSize().x / mouse.GetWindowSize().y), 1.0f, 1000.0f);
//	mat4 l_ViewMatrix = glm::lookAt(LightPosition, vec3(0.0f), vec3(1.0f, 1.0f, 1.0f));
//	mat4 l_LightView = l_ProjectionMatrix * l_ViewMatrix;
//	ModelMatrix = mat4(); // for now
//
//	float time = 0.0f;
//	float zeroval = 0;
//	mat4 WorldSpace = ProjectionMatrix * ViewMatrix * ModelMatrix;
//
//	ShaderBuilder::LoadShader(shader)->
//		Add_texture("GrassTexture", dynamic_cast<Ground*>(mGround)->GrassTexture).
//		Add_texture("MountainTexture", dynamic_cast<Ground*>(mGround)->MountainTexture).
//		Add_texture("shadowMap",shadow->depthMap).
//		Add_mat4("projection", ProjectionMatrix).
//		Add_mat4("view", ViewMatrix).
//		Add_mat4("worldSpace", WorldSpace).
//		Add_mat4("model", ModelMatrix).
//		Add_mat4("lightSpaceMatrix", l_LightView).
//		Add_float("time", time).Add_float("AmbientStrength", zeroval).
//		Add_vec3("lightPos", vec3(0.0f, 100.0f, 0.0f)).
//		Add_vec3("cameraPos", camera.GetCameraPosition()).
//		Add_float("GravityHeight", zeroval);
//	mGround->DrawModel();
//}
///*
//``Shadow Mapping Ground``
//*/
///*
//``Draws SkyBox``
//*/
//void MainLoop::DrawSky()
//{
//	ModelMatrix = mat4();
//	ModelMatrix = glm::rotate(ModelMatrix, radians(float(Counter) / 10.0f),vec3(0,1,0));
//	mSkyBox->DrawModel(ProjectionMatrix, ViewMatrix, ModelMatrix, 0, mat4(), NULL,0);
//}
///*
//``[Static] Sets Projection Matrix``
//*/
//void MainLoop::SetProjectionMatrix(mat4& ProjectionMatrix)
//{
//	MainLoop::ProjectionMatrix = ProjectionMatrix;
//	camera.SetProjectionMatrix(ProjectionMatrix);
//}
///*
//``Initialize 1 Champion in offline mode``
//*/
//void MainLoop::OfflineInitialize()
//{
//	vector<Unit_Data*> Unit;
//	Unit.push_back(new Unit_Data(vec3(0,10,0),"Katarina",0,0,1));
//	//Unit[Unit_Count]->Update_Unit_Data(Position, ModelType, Action, Counter);
//
//	UpdatedData.Unit = Unit;
//	for each (Unit_Data* unit in UpdatedData.Unit)
//	{
//		m_Unit_Data[Channel].push_back(*unit);
//	}
//	//m_Unit_Data = Unit;
//}
///*
//``Replaces Online system``
//*/
//void MainLoop::test()
//{
//	//tinyxml2::XMLDocument xml;
//	//tinyxml2::XMLElement * element;
//	//tinyxml2::XMLElement * elementNext;
//	//vec3 Position;
//	//tinyxml2::XMLError err;
//	//xml.NewText("<scene><map>1</map><units></units></scene");
//	//string error = xml.GetErrorStr1();
//	////xml.geter
//	//tinyxml2::XMLText* test = xml.ToText();
//	//element = xml.FirstChildElement("scene");
//	//element->SetAttribute("type", "katarina");
//	//elementNext = xml.NewElement("x");
//	//elementNext->SetValue(to_string(Position.x).c_str());
//	//element->InsertEndChild(elementNext);
//	//elementNext = xml.NewElement("y");
//	//elementNext->SetValue(to_string(Position.y).c_str());
//	//element->InsertEndChild(elementNext);
//	//elementNext = xml.NewElement("z");
//	//elementNext->SetValue(to_string(Position.z).c_str());
//	//element->InsertEndChild(elementNext);
//}
//void MainLoop::OfflineDataLoop()
//{
//	//UpdatedData.Unit
//	if (mouse.RightIsPressed())
//	{
//
//		vec3 WorldRay = RayCast(ProjectionMatrix, ViewMatrix).GetWorldRay();
//		vec3 Destination = Collision(WorldRay);
//		vec3 GroundDestination = mGround_Collision->Calculate_Ground_Collision(Destination);
//		m_Unit_Data[Channel][0].SetPosition(GroundDestination);
//	}
//	else if (keyboard.isKeyPressed(RIGHT) || keyboard.isKeyPressed(LEFT) || keyboard.isKeyPressed(UP) || keyboard.isKeyPressed(DOWN))
//	{
//		vec3 Destination;
//		//Destination = Calculate_Ground_Collision(Units[this->ClientID - 1]);
//		float movementSpeed = 0.1f * Camera::Delta;
//		Destination = m_Unit_Data[Channel][this->ClientID].GetPosition();
//		if (keyboard.isKeyPressed(RIGHT))
//		{
//			Destination.x -= movementSpeed;
//		}
//		if (keyboard.isKeyPressed(LEFT))
//		{
//			Destination.x += movementSpeed;
//		}
//		if (keyboard.isKeyPressed(UP))
//		{
//			Destination.z += movementSpeed;
//		}
//		if (keyboard.isKeyPressed(DOWN))
//		{
//			Destination.z -= movementSpeed;
//		}
//		vec3 GroundDestination = mGround_Collision->Calculate_Ground_Collision(Destination);
//		m_Unit_Data[Channel][0].SetPosition(GroundDestination);
//	}
//}
//void MainLoop::UserInput()
//{
//}
//void MainLoop::DrawUI()
//{
//	glm::mat4 projection = glm::ortho(0.0f, mouse.GetWindowSize().x,
//		mouse.GetWindowSize().y, 0.0f);
//	mat4 view, model;
//	vec3 color = vec3(0, 1, 1);
//
//	if (m_Unit_Data[0].size() > 0)
//	{
//		vec3 pos = m_Unit_Data[0][0].GetPosition();
//		mat4 ModelMatrix;
//		ModelMatrix = translate(ModelMatrix, pos);
//		championChat->Draw(text, "OpenGL", ProjectionMatrix, ViewMatrix, mat4());
//		championChat->Draw2D(text, "OpenGL", ProjectionMatrix, ViewMatrix, ModelMatrix);
//	}
//	else
//	{
//
//		ShaderBuilder::LoadShader(Shader::At("2D Text"))->Add_mat4("projection", projection).
//			Add_mat4("view", view).Add_mat4("model", model).
//			Add_vec3("textColor", color).Add_texture("text", 0);
//		text.RenderText("Loading . . .", 350.0f, 200.0f, 500.0f, 40.0f);
//		UI.AcceptInput();
//	}
//	ShaderBuilder::LoadShader(Shader::At("2D Text"))->Add_mat4("projection", projection).
//		Add_mat4("view", view).Add_mat4("model", model).
//		Add_vec3("textColor", color).Add_texture("text", 0);
//	text.RenderText(UI.Chat, 100.0f, 200.0f, 200.0f, 40.0f);
//	
//	color = vec3(1,0,0);
//	SetCameraView();
//	mat4 projectionMatrix = glm::perspective(radians(120.0f),
//		float(mouse.GetWindowSize().x / mouse.GetWindowSize().y), 1.0f, 1000.0f);
//	ShaderBuilder::LoadShader(Shader::At("2D Text"))->Add_vec3("textColor", color);
//	fps.CountFrame(Shader::At("2D Text"));
//
//
//
//}
///*
//``Sends Player Input Data to Server``
//*/

//vec3 MainLoop::Collision(vec3 WorldRay)
//{
//	///*----------Camera---------*/	
//	/// intercaction
//	WorldRay = RayCast(ProjectionMatrix, ViewMatrix).GetWorldRay();
//	vec3 mapUp(0, 0, 1);
//	vec3 mapRight(1, 0, 0);
//	vec3 mapProduct = glm::cross(mapUp, mapRight);
//	/* get camera position in worldspace (goes under projection and camera matrices )*/
//	vec3 CameraPositionInWorldSpace = GetCameraPosition(ProjectionMatrix, ViewMatrix);
//	/* gets interaction between worldray and y = 0 surface */
//	float scaler = CameraPositionInWorldSpace.y / WorldRay.y;
//	return (CameraPositionInWorldSpace - WorldRay * scaler);
//}
//vec3 MainLoop::GetCameraPosition(mat4& projectionMat, mat4& cameraMat)
//{
//	vec3 CameraPosition = camera.GetCameraPosition();
//	vec3 CameraRotation = camera.GetCameraRotation();
//	/*********/
//	vec4 CameraPositionTransformed = inverse(cameraMat) * inverse(projectionMat) * vec4(CameraPosition, 1.0f);
//	CameraPositionTransformed /= CameraPositionTransformed.w;
//	CameraPosition = vec3(CameraPositionTransformed);
//	return CameraPosition;
//}
//
//
//
//
//void MainLoop::DrawSea()
//{
//	mat4 ModelMat;
//	ModelMat = scale(ModelMat, vec3(1000, 1000, 1000));
//	mSea.Draw(ProjectionMatrix, ViewMatrix, ModelMat);
//}
//
//void MainLoop::SetCameraView()
//{
//	/*if (m_Unit_Data[Channel].size() <= ClientID)
//		return;*/
//	if (IsLoaded)
//	camera.ZoomInto(vec3(), m_Unit_Data[Channel][0].GetPosition() );
//	ViewMatrix = mat4();
//	ViewMatrix = camera.GetCameraMatrix();
//}
//
//

//Draws Loading Screen While Game Is Loading
//*/
//void MainLoop::Draw_Loading_Screen()
//{
//	// Present Loading Screen
//	tLoading_Screen.Draw_Loading_Screen();
//}
//
//
//


///*
//"Receive ClientID" to Generate the client with a new ID
//"Receive Data" to Receive lost data
//*/
//void MainLoop::GenerateConnection(string Request)
//{
//	//while (!LoadModels._Is_ready());
//	client._SendMessage(Request);
//	if (UpdatedData.UpdateData(client._AsyncReceiveMessage(), Counter))
//	{
//		UpdatedData.Unit = UpdatedData.GetUnitData(); // gotta recheck logic, it might be a really stupid loop
//		ClientID = UpdatedData.ClientID;
//	}
//}
//void MainLoop::DrawEntities()
//{
//	mat4 l_ProjectionMatrix = glm::perspective(radians(120.0f),
//		float(mouse.GetWindowSize().x / mouse.GetWindowSize().y), 1.0f, 1000.0f);
//	mat4 l_ViewMatrix = glm::lookAt(LightPosition, vec3(0.0f), vec3(1.0f, 1.0f, 1.0f));
//	mat4 l_LightView = l_ProjectionMatrix * l_ViewMatrix;
//	for each (GrassObjects* grass in m_GrassObjects)
//	{
//		mat4 ModelMatrix;
//		vec3 newPosition = mGround_Collision->Calculate_Ground_Collision(grass->m_Position); //todo: add return value
//		ModelMatrix = translate(ModelMatrix, newPosition);
//		ModelMatrix = scale(ModelMatrix, vec3(1));
//		
//		float time = float(grass->m_StartTime++) / 20.0f;
//		float zeroval = 0;
//		mat4 WorldSpace = ProjectionMatrix * ViewMatrix * ModelMatrix;
//		ShaderBuilder::LoadShader(Shader::At("Grass"))->
//			Add_texture("ourTexture", mGrass->texture).
//			Add_texture("shadowMap", shadow->depthMap).
//			Add_mat4("projection", ProjectionMatrix).
//			Add_mat4("view", ViewMatrix).
//			Add_mat4("worldSpace", WorldSpace).
//			Add_mat4("model", ModelMatrix).
//			Add_mat4("lightSpaceMatrix", l_LightView).
//			Add_float("time", time).Add_float("AmbientStrength", zeroval).
//			Add_vec3("lightPos", vec3(0.0f, 100.0f, 0.0f)).
//			Add_vec3("cameraPos", camera.GetCameraPosition()).
//			Add_float("GravityHeight", zeroval);
//		mGrass->DrawModel();
//
//	}
//
//}
//
