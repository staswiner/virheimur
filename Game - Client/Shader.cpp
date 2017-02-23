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
		printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", Path);
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
		printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertexPath);
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
		printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertexPath);
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

