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

	string header = FileToText("ShaderBuilder/Fragment-header.glsl");
		
	string Normalfunc = FileToText("ShaderBuilder/Fragment-Normalfunc.glsl");

	string NormalMapfunc = FileToText("ShaderBuilder/Fragment-NormalMapfunc.glsl");
		
	string materialfunc1 = FileToText("ShaderBuilder/Fragment-materialfunc1.glsl");
	
	string materialfunc1NormalMap = FileToText("ShaderBuilder/Fragment-materialfunc1NormalMap.glsl");
	
	string materialfunc1NoNormalMap = FileToText("ShaderBuilder/Fragment-materialfunc1NoNormalMap.glsl");
	
	string materialfunc2 = FileToText("ShaderBuilder/Fragment-materialfunc2.glsl");
		
	string materialfunc2NormalMap = FileToText("ShaderBuilder/Fragment-materialfunc2NormalMap.glsl");

	string materialfunc2NoNormalMap = FileToText("ShaderBuilder/Fragment-materialfunc2NoNormalMap.glsl");
	
	string materialfunc3 = FileToText("ShaderBuilder/Fragment-materialfunc3.glsl");
		
	string mainfunc1 = FileToText("ShaderBuilder/Fragment-mainfunc1.glsl");
		
	string mainfunc1Diffuse = FileToText("ShaderBuilder/Fragment-mainfunc1Diffuse.glsl");
		
	string mainfunc1NoDiffuse = FileToText("ShaderBuilder/Fragment-mainfunc1NoDiffuse.glsl");
	
	string mainfunc1NormalMap = FileToText("ShaderBuilder/Fragment-mainfunc1NormalMap.glsl");
	
	string mainfunc1NoNormalMap = FileToText("ShaderBuilder/Fragment-mainfunc1NoNormalMap.glsl");
	
	string mainfunc2 = FileToText("ShaderBuilder/Fragment-mainfunc2.glsl");
	
	
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
string Shader::FileToText(string Path)
{
	string line;
	string Text;
	ifstream myfile(Path);
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			Text += line + '\n';
		}
		myfile.close();
	}
	else
	{
		throw exception("unable to open file");
	}
	return Text;
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

