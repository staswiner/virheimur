#include "Shader.h"

map<string, Shader*> Shader::mapShader;

bool Shader::LoadShaders()
{
	mapShader["Basic"]			= new Shader("Basic Vertex Shader.glsl", "Basic Fragment Shader.glsl");
	mapShader["Ground"]			= new Shader("Ground Vertex Shader.glsl","Ground Fragment Shader.glsl");
	mapShader["Katarina"]		= new Shader("Champion VertexShader.glsl", "Champion Geometry Shader.glsl", "Champion FragmentShader.glsl");
	mapShader["Grass"]			= new Shader("Grass Vertex Shader.glsl", "Champion Geometry Shader.glsl", "Grass Fragment Shader.glsl");
	mapShader["Gaussic"]		= new Shader("Gaussic Vertex Shader.glsl", "Gaussic Geometry Shader.glsl", "Gaussic Fragment Shader.glsl");
	mapShader["2D Text"]		= new Shader("Text Vertex Shader.glsl", "Text Fragment Shader.glsl");
	mapShader["Champion Chat"]  = new Shader("3D Text Vertex Shader.glsl", "Text Fragment Shader.glsl");
	mapShader["HBlur"]			= new Shader("HBlur Vertex Shader.glsl", "HBlur Fragment Shader.glsl");
	mapShader["VBlur"]			= new Shader("VBlur Vertex Shader.glsl", "VBlur Fragment Shader.glsl");
	mapShader["FBO"]			= new Shader("PostProcessing Vertex Shader.glsl", "PostProcessing Fragment Shader.glsl");
	mapShader["Skybox"]			= new Shader("SkyBox Vertex Shader.glsl","SkyBox Fragment Shader.glsl");
	mapShader["PostProcessing"] = new Shader("PostProcessing Vertex Shader.glsl","PostProcessing Fragment Shader.glsl");
	mapShader["Bright"]			= new Shader("PostProcessing Vertex Shader.glsl", "Bright Fragment Shader.glsl");
	mapShader["Combine"]		= new Shader("PostProcessing Vertex Shader.glsl", "Combine Fragment Shader.glsl");
	mapShader["Crop"]			= new Shader("InterfaceCrop Vertex Shader.glsl", "Interface Fragment Shader.glsl");
	mapShader["Image"]			= new Shader("Interface Vertex Shader.glsl", "Interface Fragment Shader.glsl");
	//mapShader["Animation"]		= new Shader("Animation Vertex Shader.glsl", "Animation Fragment Shader.glsl");
	mapShader["Animation"]		= new Shader("Animation Vertex Shader.glsl", "Ground Geometry Shader.glsl", "Animation Fragment Shader.glsl");
	mapShader["Instanced"]		= new Shader("Instanced Vertex Shader.glsl", "Instanced Geometry Shader.glsl", "Instanced Fragment Shader.glsl");
	mapShader["AnimationDistance"]= new Shader("Animation Vertex Shader.glsl", "Distance Fragment Shader.glsl");
	mapShader["AnimationShadow"]= new Shader("Animation Vertex Shader.glsl", "AnimationShadow Fragment Shader.glsl");
	mapShader["Ground"]			= new Shader("Animation Vertex Shader.glsl", "Ground Geometry Shader.glsl", "Ground Fragment Shader.glsl");
	mapShader["Water"]			= new Shader("Animation Vertex Shader.glsl","Ground Geometry Shader.glsl" ,"Water Fragment Shader.glsl");
	mapShader["InstancedDistance"]		= new Shader("Instanced Vertex Shader.glsl", "Instanced Geometry Shader.glsl", "Distance Fragment Shader.glsl");
	mapShader["SeaAnimated"]	= new Shader("SeaAnimated Vertex Shader.glsl","SeaAnimated Geometry Shader.glsl","SeaAnimated Fragment Shader.glsl");
	mapShader["Index"]			= new Shader("Index1 Vertex Shader.glsl","Index1 Geometry Shader.glsl", "Index1 Fragment Shader.glsl");
	mapShader["Text"] = new Shader("Text Vertex Shader.glsl", "Text Fragment Shader.glsl");
	mapShader["Color"]			= new Shader("Color Vertex Shader.glsl", "Color Fragment Shader.glsl");
	//	new Shader("Index Vertex Shader.glsl", "Index Geometry Shader.glsl", "Index Fragment Shader.glsl");
	return true;
}
Shader::~Shader()
{
	glDeleteProgram(ProgramID);
}


void Shader::InitializeShaderProgram(string Path, GLuint shaderID)
{
	string VertexShaderCode;
	ifstream VertexShaderStream(Path, std::ios::in);
	if (VertexShaderStream.is_open())
	{
		string Line = "";
		while (getline(VertexShaderStream, Line))
			VertexShaderCode += "\n" + Line;
		VertexShaderStream.close();
	}
	else
	{
//		cout<<"Impossible to open "<< Path <<". Are you in the right directory ? Don't forget to read the FAQ !\n";
	}
	GLint Result = GL_FALSE;
	int InfoLogLength;
	// Compile Vertex Shader
	const GLchar* VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(shaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(shaderID);

	// Check Vertex Shader
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0)
	{
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(shaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		string error;
		for (unsigned int i = 0; i < VertexShaderErrorMessage.size(); ++i)
		{
			error += VertexShaderErrorMessage[i];
		}
		//MessageBoxA(0, error.c_str() ,"",MB_OK);
	}

}
Shader::Shader(string vertexPath, string fragmentPath)
{
	string Folder = "Shaders/";
	vertexPath = Folder + vertexPath;
	fragmentPath = Folder + fragmentPath;
	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	string VertexShaderCode;
	ifstream VertexShaderStream(vertexPath, std::ios::in);
	if (VertexShaderStream.is_open())
	{
		string Line = "";
		while (getline(VertexShaderStream, Line))
			VertexShaderCode += "\n" + Line;
		VertexShaderStream.close();
	}
	else
	{
//		printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertexPath);
	}

	// Read the Fragment Shader code from the file
	string FragmentShaderCode;
	ifstream FragmentShaderStream(fragmentPath, std::ios::in);
	if (FragmentShaderStream.is_open())
	{
		string Line = "";
		while (getline(FragmentShaderStream, Line))
			FragmentShaderCode += "\n" + Line;
		FragmentShaderStream.close();
	}
	GLint Result = GL_FALSE;
	int InfoLogLength;
	// Compile Vertex Shader
	const GLchar* VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0)
	{
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		string error;
		for (unsigned int i = 0; i < VertexShaderErrorMessage.size(); ++i)
		{
			error += VertexShaderErrorMessage[i];
		}
		//MessageBoxA(0, error.c_str() ,"",MB_OK);
	}

	// Compile Fragment Shader
	const GLchar* FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0)
	{
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		string error;
		for (unsigned int i = 0; i < FragmentShaderErrorMessage.size(); ++i)
		{
			error += FragmentShaderErrorMessage[i];
		}
		//	MessageBoxA(0, error.c_str(), "", MB_OK);
	}
	// Link the program
	ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0)
	{
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		string error;
		for (unsigned int i = 0; i < ProgramErrorMessage.size(); ++i)
		{
			error += ProgramErrorMessage[i];
		}
		//MessageBoxA(0, error.c_str(), "", MB_OK);
	}


	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

}
Shader::Shader(string vertexPath, string geometryPath, string fragmentPath)
{
	string Folder = "Shaders/";
	vertexPath = Folder + vertexPath;
	geometryPath = Folder + geometryPath;
	fragmentPath = Folder + fragmentPath;
	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	GLuint GeometryShaderID = glCreateShader(GL_GEOMETRY_SHADER);
	// Read the Vertex Shader code from the file
	string VertexShaderCode;
	ifstream VertexShaderStream(vertexPath, std::ios::in);
	if (VertexShaderStream.is_open())
	{
		string Line = "";
		while (getline(VertexShaderStream, Line))
			VertexShaderCode += "\n" + Line;
		VertexShaderStream.close();
	}
	else
	{
//		printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertexPath);
	}
	// Read the Geometry Shader code from the file
	string GeometryShaderCode;
	ifstream GeometryShaderStream(geometryPath, std::ios::in);
	if (GeometryShaderStream.is_open())
	{
		string Line = "";
		while (getline(GeometryShaderStream, Line))
			GeometryShaderCode += "\n" + Line;
		GeometryShaderStream.close();
	}

	// Read the Fragment Shader code from the file
	string FragmentShaderCode;
	ifstream FragmentShaderStream(fragmentPath, std::ios::in);
	if (FragmentShaderStream.is_open())
	{
		string Line = "";
		while (getline(FragmentShaderStream, Line))
			FragmentShaderCode += "\n" + Line;
		FragmentShaderStream.close();
	}
	GLint Result = GL_FALSE;
	int InfoLogLength;
	// Compile Vertex Shader
	const GLchar* VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0)
	{
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		string error;
		for (unsigned int i = 0; i < VertexShaderErrorMessage.size(); ++i)
		{
			error += VertexShaderErrorMessage[i];
		}
	}
	//Compile Geometry Shader
	const GLchar* GeometrySourcePointer = GeometryShaderCode.c_str();
	glShaderSource(GeometryShaderID, 1, &GeometrySourcePointer, NULL);
	glCompileShader(GeometryShaderID);

	// Check Geometry Shader
	glGetShaderiv(GeometryShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(GeometryShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0)
	{
		std::vector<char> GeometryShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(GeometryShaderID, InfoLogLength, NULL, &GeometryShaderErrorMessage[0]);
		string error;
		for (unsigned int i = 0; i < GeometryShaderErrorMessage.size(); ++i)
		{
			error += GeometryShaderErrorMessage[i];
		}
	}
	// Compile Fragment Shader
	const GLchar* FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0)
	{
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		string error;
		for (unsigned int i = 0; i < FragmentShaderErrorMessage.size(); ++i)
		{
			error += FragmentShaderErrorMessage[i];
		}
		//	MessageBoxA(0, error.c_str(), "", MB_OK);
	}
	// Link the program
	ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, GeometryShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0)
	{
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		string error;
		for (unsigned int i = 0; i < ProgramErrorMessage.size(); ++i)
		{
			error += ProgramErrorMessage[i];
		}
		//MessageBoxA(0, error.c_str(), "", MB_OK);
	}


	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, GeometryShaderID);
	glDetachShader(ProgramID, FragmentShaderID);

	glDeleteShader(VertexShaderID);
	glDeleteShader(GeometryShaderID);
	glDeleteShader(FragmentShaderID);

}
Shader::Shader(string vertexShader, string geometryShader, string fragmentShader, bool)
{
	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	GLuint GeometryShaderID = glCreateShader(GL_GEOMETRY_SHADER);

	GLint Result = GL_FALSE;
	int InfoLogLength;
	// Compile Vertex Shader
	const GLchar* VertexSourcePointer = vertexShader.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0)
	{
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		string error;
		for (unsigned int i = 0; i < VertexShaderErrorMessage.size(); ++i)
		{
			error += VertexShaderErrorMessage[i];
		}
	}
	//Compile Geometry Shader
	const GLchar* GeometrySourcePointer = geometryShader.c_str();
	glShaderSource(GeometryShaderID, 1, &GeometrySourcePointer, NULL);
	glCompileShader(GeometryShaderID);

	// Check Geometry Shader
	glGetShaderiv(GeometryShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(GeometryShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0)
	{
		std::vector<char> GeometryShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(GeometryShaderID, InfoLogLength, NULL, &GeometryShaderErrorMessage[0]);
		string error;
		for (unsigned int i = 0; i < GeometryShaderErrorMessage.size(); ++i)
		{
			error += GeometryShaderErrorMessage[i];
		}
	}
	// Compile Fragment Shader
	const GLchar* FragmentSourcePointer = fragmentShader.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0)
	{
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		string error;
		for (unsigned int i = 0; i < FragmentShaderErrorMessage.size(); ++i)
		{
			error += FragmentShaderErrorMessage[i];
		}
		//	MessageBoxA(0, error.c_str(), "", MB_OK);
	}
	// Link the program
	ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, GeometryShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0)
	{
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		string error;
		for (unsigned int i = 0; i < ProgramErrorMessage.size(); ++i)
		{
			error += ProgramErrorMessage[i];
		}
		//MessageBoxA(0, error.c_str(), "", MB_OK);
	}


	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, GeometryShaderID);
	glDetachShader(ProgramID, FragmentShaderID);

	glDeleteShader(VertexShaderID);
	glDeleteShader(GeometryShaderID);
	glDeleteShader(FragmentShaderID);
}
Shader* Shader::ConstructShader(ShaderInfo shaderInfo)
{
	Shader * shader = new Shader();
	shader->ConstructShaderNS(shaderInfo);
	return shader;
}
Shader* Shader::ConstructShaderNS(ShaderInfo shaderInfo)
{
	this->shaderInfo = shaderInfo;
	GLuint VertexShaderID = CompileVertexShader();
	GLuint GeometryShaderID = CompileGeometryShader();
	GLuint FragmentShaderID = CompileFragmentShader();
	GLint Result = GL_FALSE;
	int InfoLogLength;

	// Link the program
	ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, GeometryShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0)
	{
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		string error;
		for (unsigned int i = 0; i < ProgramErrorMessage.size(); ++i)
		{
			error += ProgramErrorMessage[i];
		}
	}


	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, GeometryShaderID);
	glDetachShader(ProgramID, FragmentShaderID);

	glDeleteShader(VertexShaderID);
	glDeleteShader(GeometryShaderID);
	glDeleteShader(FragmentShaderID);
	return this;
	/*int numMaterials;
	MODEL->Scene->Materials;
	MODEL->Scene->Mesh->Indexes;
	MODEL -> shader = the following :
	
	"uniform Material Material[20];";

	"color = total * Material[index];";*/
}
GLuint Shader::CompileVertexShader()
{
	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);

	GLint Result = GL_FALSE;
	int InfoLogLength;
	// Compile Vertex Shader
	string text = ConstructVertexShader();
	const GLchar* VertexSourcePointer = text.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0)
	{
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		string error;
		for (unsigned int i = 0; i < VertexShaderErrorMessage.size(); ++i)
		{
			error += VertexShaderErrorMessage[i];
		}
	}

	return VertexShaderID;
}
GLuint Shader::CompileGeometryShader()
{
	// Create the shaders
	GLuint GeometryShaderID = glCreateShader(GL_GEOMETRY_SHADER);

	GLint Result = GL_FALSE;
	int InfoLogLength;

	//Compile Geometry Shader
	string text = ConstructGeometryShader();
	const GLchar* GeometrySourcePointer = text.c_str();
	glShaderSource(GeometryShaderID, 1, &GeometrySourcePointer, NULL);
	glCompileShader(GeometryShaderID);

	// Check Geometry Shader
	glGetShaderiv(GeometryShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(GeometryShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0)
	{
		std::vector<char> GeometryShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(GeometryShaderID, InfoLogLength, NULL, &GeometryShaderErrorMessage[0]);
		string error;
		for (unsigned int i = 0; i < GeometryShaderErrorMessage.size(); ++i)
		{
			error += GeometryShaderErrorMessage[i];
		}
	}
	
	return GeometryShaderID;
}
GLuint Shader::CompileFragmentShader()
{
	// Create the shaders
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	GLint Result = GL_FALSE;
	int InfoLogLength;
	
	// Compile Fragment Shader
	string text = ConstructFragmentShader();
	const GLchar* FragmentSourcePointer = text.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0)
	{
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		string error;
		for (unsigned int i = 0; i < FragmentShaderErrorMessage.size(); ++i)
		{
			error += FragmentShaderErrorMessage[i];
		}
		//	MessageBoxA(0, error.c_str(), "", MB_OK);
	}
	
	return FragmentShaderID;
}
string Shader::ConstructVertexShader()
{
	string s1 =
		R"(#version 400 compatibility 
		layout(location = 0) in vec3 position;
		layout(location = 1) in vec3 normals;
		layout(location = 2) in vec2 uvs;
		layout(location = 3) in ivec4 bonesID;
		layout(location = 4) in vec4 Weights;
		
		out float gl_ClipDistance[1];
		out VS_OUT{
		vec2 UVs;
		vec3 Normals;
		vec3 FragPos;
		vec3 LightFragPos;
		vec4 clipSpace;
		}vs_out;
		
		uniform bool isAnimated;
		uniform mat4 WVM;
		uniform mat4 LightMatrix;
		uniform mat4 Model;
		
		uniform int BoneNum;
		uniform mat4 Bones[100];
		
	
		void main()
		{
			vec4 objectpos = vec4(position, 1.0);
			if (isAnimated == true)
			{
				mat4 BoneTransform = mat4(0);
				//BoneTransform += Bones[bonesID[0]] * Weights[0];
				for (int i = 0; i < 4; i++)
				{
					BoneTransform += Bones[bonesID[i]] * Weights[i];
				}
		
				objectpos = BoneTransform * vec4(position, 1.0);
			}
			vs_out.FragPos = vec3(Model * objectpos);
		
			vs_out.clipSpace = WVM * objectpos;
		
			gl_Position = vs_out.clipSpace;
			vs_out.UVs = vec2(uvs.x, 1.0 - uvs.y);
			vs_out.Normals = normals;
			vec4 lFragPos = LightMatrix * vec4(vs_out.FragPos, 1);
			vs_out.LightFragPos = vec3(lFragPos.xyz) / lFragPos.w;
		

		})";
	return s1;
}
string Shader::ConstructGeometryShader()
{
	string s1 =
		R"(#version 400 compatibility
		layout(triangles) in;
		layout(triangle_strip, max_vertices = 3) out;

		in VS_OUT{
		vec2 UVs;
		vec3 Normals;
		vec3 FragPos;
		vec3 LightFragPos;
		vec4 clipSpace;
		}vs_in[];

		out GS_OUT{
		vec2 UVs;
		vec3 Normals;
		vec3 FragPos;
		vec4 clipSpace;
		vec3 LightFragPos;
		vec3 T;
		vec3 B;
		}gs_out;
		//varying out vec3 a;
		uniform mat4 WVM;
		//varying in vec3 varNormal[];
		//varying vec3 varNormalf;

		void TransferData(in int i)
		{
			gl_Position = gl_in[i].gl_Position;
			//gl_ClipDistance[0] = gl_in[i].gl_ClipDistance[0];
			gs_out.UVs = vs_in[i].UVs;
			gs_out.Normals = vs_in[i].Normals;
			gs_out.FragPos = vs_in[i].FragPos;
			gs_out.LightFragPos = vs_in[i].LightFragPos;
			gs_out.clipSpace = vs_in[i].clipSpace;
			//varNormalf = varNormal[i];
		}
		void CalculateTangent()
		{
			// MBT::
			vec3 Edge1 = vs_in[1].FragPos - vs_in[0].FragPos;
			vec3 Edge2 = vs_in[2].FragPos - vs_in[0].FragPos;

			vec2 DeltaUV1 = vs_in[1].UVs - vs_in[0].UVs;
			vec2 DeltaUV2 = vs_in[2].UVs - vs_in[0].UVs;

			float f = 1.0f / (DeltaUV1.x * DeltaUV2.y - DeltaUV2.x * DeltaUV1.y);

			vec3 Tangent, Bitangent;

			Tangent.x = f * (DeltaUV2.y * Edge1.x - DeltaUV1.y * Edge2.x);
			Tangent.y = f * (DeltaUV2.y * Edge1.y - DeltaUV1.y * Edge2.y);
			Tangent.z = f * (DeltaUV2.y * Edge1.z - DeltaUV1.y * Edge2.z);

			Bitangent.x = f * (-DeltaUV2.x * Edge1.x - DeltaUV1.x * Edge2.x);
			Bitangent.y = f * (-DeltaUV2.x * Edge1.y - DeltaUV1.x * Edge2.y);
			Bitangent.z = f * (-DeltaUV2.x * Edge1.z - DeltaUV1.x * Edge2.z);

			Tangent = normalize(Tangent);
			Bitangent = normalize(Bitangent);
			gs_out.T = Tangent; // WVM * vector
			gs_out.B = Bitangent;

		}
		void main()
		{
			for (int i = 0; i < 3; i++)
			{
				TransferData(i);
				CalculateTangent();
				EmitVertex();
			}
			EndPrimitive();
		})";
	return s1;
}
string Shader::ConstructFragmentShader()
{

	string header = 
		R"(	#version 400 compatibility
			in GS_OUT{
			vec2 UVs;
			vec3 Normals;
			vec3 FragPos;
			vec4 clipSpace;
			vec3 LightFragPos;
			vec3 T;
			vec3 B;
			}fs_in;
			struct Material {
				vec3 ambient;
				vec3 diffuse;
				vec3 specular;
				float shininess;
			};
			uniform sampler2D Texture[5];
			uniform sampler2D NormalMap[5];
			uniform sampler2D Dispose;
			uniform vec3 lightPos;
			uniform vec3 cameraPos;
			uniform Material material;
			out vec4 color;)";
	string Normalfunc =
		R"(vec3 CalcNormal()
		{
			vec3 Normal = normalize(fs_in.Normals);
			return Normal;
		})";
	string NormalMapfunc =
		R"(vec3 CalcBumpedNormal(sampler2D normalTexture)
		{
		vec3 Normal = CalcNormal();
		vec3 T = fs_in.T;
		T = normalize(T - dot(T, Normal) * Normal);
		vec3 B = cross(T, Normal);
		//B = fs_in.B;

		vec4 TexturedNormal = texture2D(normalTexture, fs_in.UVs * Texelation);
		TexturedNormal = (TexturedNormal*2.0 - vec4(1.0));
		vec3 BumpMapNormal = vec3(TexturedNormal.xyz);// vec3(TexturedNormal.x, TexturedNormal.z, TexturedNormal.y);

		vec3 NewNormal;
		//mat3 TBN = mat3(vec3(1, 0, 0), vec3(0, 0, 1), Normal);
		mat3 TBN = mat3(T, B, Normal);
		NewNormal = TBN * BumpMapNormal;
		//NewNormal.x *= -1.0;
		//NewNormal.z *= -1.0;
		NewNormal = normalize(NewNormal);
		return NewNormal;
		})";
	string materialfunc1 =
		"vec3 AddLight(Material material, vec3 LightColor, vec3 LightDir";
	string materialfunc1NormalMap =
		", sampler2D normalTexture)";
	string materialfunc1NoNormalMap =
		")";
	string materialfunc2 =
		R"({
			// Mathematics
			vec3 toCameraVector = normalize(fs_in.FragPos - cameraPos);

			// Light
			vec3 ambient = LightColor * material.ambient;)";
	string materialfunc2NormalMap =
		"	vec3 norm = CalcBumpedNormal(normalTexture);";
	string materialfunc2NoNormalMap =
		"	vec3 norm = CalcNormal();";
	string materialfunc3 =
		R"(	vec3 textnorm = normalize(norm);
			float diff = max(dot(textnorm, LightDir), 0.0);
			vec3 diffuse = diff * material.diffuse * LightColor;

			//  specular
			////vec3 reflectedLight = reflect(normalize(lightDir), norm);//phong
			vec3 reflectedLight = normalize(LightDir - normalize(toCameraVector));//blinn-phong
			////float spec = pow(max(dot(normalize(toCameraVector.xz), reflectedLight.xz), 0.0), shineDamper);//phong
			float spec = pow(max(dot(norm, reflectedLight), 0.0), int(material.specular * 128.0));//blinn-phong
			vec3 specular = spec * LightColor;
			//	float shadow = ShadowCalculation(fs_in.LightFragPos,LightDir, textnorm);    "
			// Enable Shadows
			//	shadow = 0;
			vec3 Light = (diffuse + (1.0) * (4.0 * specular + ambient));
			return Light;
		})";
	string mainfunc1 =
		R"(void main()
		{
			vec3 LightColor = vec3(1.0, 0.9, 0.7);
			vec3 lightDir = normalize(lightPos - fs_in.FragPos);)";
	string mainfunc1Diffuse =
		R"(	vec4 color0 = texture2D(Texture[0], fs_in.UVs);
			vec3 TotalColor = vec3(color0) * AddLight(material, LightColor, lightDir)";
	string mainfunc1NoDiffuse =
		"vec3 TotalColor = AddLight(material, LightColor, lightDir";
	string mainfunc1NormalMap =
		", NormalMap[0]);"; 
	string mainfunc1NoNormalMap =
		");";
	string mainfunc2 =
		R"(	float near = 0.1f;
			float far = 1000.0f;
			float depth = gl_FragCoord.z;
			float Distance = 2.0 * near * far / (far + near - (2.0 * depth - 1.0) * (far - near));

			color = vec4(TotalColor, 1);
		})";

	
	string FragmentShader = header + Normalfunc;
	FragmentShader += (this->shaderInfo.NumNormalMap) ? NormalMapfunc : "";

	FragmentShader += materialfunc1;
	FragmentShader += (this->shaderInfo.NumNormalMap) ? materialfunc1NormalMap : materialfunc1NoNormalMap;
	FragmentShader += materialfunc2;
	FragmentShader += (this->shaderInfo.NumNormalMap) ? materialfunc2NormalMap : materialfunc2NoNormalMap;
	FragmentShader += materialfunc3;

	FragmentShader += mainfunc1;
	FragmentShader += (this->shaderInfo.NumDiffuse) ? mainfunc1Diffuse : mainfunc1NoDiffuse;
	FragmentShader += (this->shaderInfo.NumNormalMap) ? mainfunc1NormalMap : mainfunc1NoNormalMap;
	FragmentShader += mainfunc2;

	return FragmentShader;
}
void Shader::Use()
{
	glUseProgram(this->ProgramID);
}
Shader & Shader::At(string ID)
{
	return *Shader::mapShader[ID];
}
Shader::Shader()
{
}

