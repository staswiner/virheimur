//#include "Grass.h"
//
//
//
//Grass::Grass(const unsigned int Number_Of_Instances)
//	:
//	//Obj_Bmp_Loader("Katarina/Katarina.obj", "Katarina/Katarina Glowing.bmp", "Champion VertexShader.glsl", "Champion Geometry Shader.glsl","Champion FragmentShader.glsl")
//	Obj_Bmp_Loader("Grass pack/Grass_02.obj", "Map/Grass Tile.jpg")
//
//{
//	this->m_Number_Of_Instances = Number_Of_Instances;;
//	Recover_Explosion();
//	//InitializeInstances(Number_Of_Instances);
//}
//Grass::~Grass()
//{
//
//}
//
//void Grass::InitializeInstances(const unsigned int Number_Of_Instances)
//{
//	vector<GrassObjects*> GrassInstances;
//	vector<vec3> PosOffsets;
//	for (int i = 0; i < Number_Of_Instances; i++)
//	{
//		GrassInstances.push_back(new GrassObjects);
//		PosOffsets.push_back(GrassInstances.back()->m_Position);
//	}
//	GLuint instanceVBO;
//	glGenBuffers(1, &instanceVBO);
//	glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * Number_Of_Instances, &PosOffsets[0], GL_STATIC_DRAW);
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//
//
//	glEnableVertexAttribArray(3);
//	glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
//	glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(vec3), (GLvoid*)0);
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	glVertexAttribDivisor(3, 1);
//}
//void Grass::Explode()
//{
//	m_Time++;
//	m_GSpeed += 0.1f;
//	m_GPosition += m_GSpeed;
//}
//void Grass::Recover_Explosion()
//{
//	m_Time = 0.0f;
//	m_GSpeed = 0.0f;
//	m_GPosition = 0.0f;
//}
//void Grass::LoadVAO()
//{
//	vector<GrassObjects*> GrassInstances;
//	vector<vec3> GrassPosition;
//	vector<float> GrassTimes;
//	for (int i = 0; i <m_Number_Of_Instances; i++)
//	{
//		GrassInstances.push_back(new GrassObjects);
//		mat4 t_ModelMat;
//		t_ModelMat = translate(t_ModelMat, GrassInstances.back()->m_Position);
//		t_ModelMat = translate(t_ModelMat, vec3(0,30,0));
//		GrassPosition.push_back(GrassInstances[i]->m_Position);
//		GrassTimes.push_back((float)GrassInstances[i]->m_StartTime / 1000.0f);
//	}
//	GLuint GrassPositionVBO;
//	VAO; VBO;
//	// generate buffers
//	glGenVertexArrays(1, &VAO);
//	glGenBuffers(1, &VBO);
//	// bind arrays
//	glBindVertexArray(VAO);
//	// bind vertices
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Stas::Vertex), &vertices.front(), GL_STATIC_DRAW);
//	// vertices
//	GLuint Vertexs;
//	glGenBuffers(1, &Vertexs);
//	glBindBuffer(GL_ARRAY_BUFFER, Vertexs);
//	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec3), &vertices.front(), GL_STATIC_DRAW);
//	/// Position attribute
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Stas::Vertex) , BUFFER_OFFSET(0));
//	glEnableVertexAttribArray(0);
//	/// Normals attribute
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Stas::Vertex) , BUFFER_OFFSET(sizeof(vec3)));
//	glEnableVertexAttribArray(1);
//	/// texture coordinates attribute
//	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Stas::Vertex), BUFFER_OFFSET(sizeof(vec3) * 2));
//	glEnableVertexAttribArray(2);
//	
//	glGenBuffers(1, &GrassPositionVBO);;
//	glBindBuffer(GL_ARRAY_BUFFER, GrassPositionVBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * m_Number_Of_Instances, &GrassPosition[0], GL_STATIC_DRAW);
//
//	// Grass Positions
//	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), (GLvoid*)0);
//	glEnableVertexAttribArray(3);
//	glVertexAttribDivisor(3, 1);
//
//	GLuint TimeVBO;
//	glGenBuffers(1, &TimeVBO);
//	glBindBuffer(GL_ARRAY_BUFFER, TimeVBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_Number_Of_Instances, &GrassTimes[0], GL_STATIC_DRAW);
//
//	// Grass Times
//	glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, sizeof(float), (GLvoid*)0);
//	glEnableVertexAttribArray(4);
//	glVertexAttribDivisor(4, 1);
//
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	// Unbind VAO
//	glBindVertexArray(0);
//
//	// free memory
//	Vertices_Amount = vertices.size();
//	Indices_Amount = indices.size();
//	//vertices.clear();
//	indices.clear();
//}