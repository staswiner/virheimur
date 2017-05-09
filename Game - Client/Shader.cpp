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
	mapShader["3D Image"]		= new Shader("3D Text Vertex Shader.glsl", "Interface Fragment Shader.glsl");
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
	mapShader["Color"] = new Shader("Color Vertex Shader.glsl", "Color Fragment Shader.glsl");
	mapShader["Normals"]			= new Shader("NormalsV.glsl","NormalsF.glsl");
	//	new Shader("Index Vertex Shader.glsl", "Index Geometry Shader.glsl", "Index Fragment Shader.glsl");
	return true;
}
void Shader::Reload()
{
	glDeleteProgram(ProgramID);
	if (GeometryShaderPath == "")
		*this = *new Shader(VertexShaderPath,FragmentShaderPath);
	else
		*this = *new Shader(VertexShaderPath,GeometryShaderPath ,FragmentShaderPath);
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
	this->VertexShaderPath = vertexPath;
	this->FragmentShaderPath = fragmentPath;
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
	string error;

	if (InfoLogLength > 0)
	{
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
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
	error.clear();
	if (InfoLogLength > 0)
	{
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
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
	this->VertexShaderPath = vertexPath;
	this->GeometryShaderPath = geometryPath;
	this->FragmentShaderPath = fragmentPath;
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
	string s1 = FileToText("ShaderBuilder/Vertex-vertex1.glsl");

	OutputFinalShader(s1, "ShaderBuilder/Vertex-FULL.glsl");

	return s1;
}
string Shader::ConstructGeometryShader()
{

	string Triangle = FileToText("ShaderBuilder/Geometry1-triangles.glsl");
	string Wire = FileToText("ShaderBuilder/Geometry1-wire.glsl");
	string Body = FileToText("ShaderBuilder/Geometry2-geometry1.glsl");
	
	string GeometryShader;
	GeometryShader += (shaderInfo.imageType == Shader::ImageType::Wire) ? Wire : Triangle;
	GeometryShader += Body;

	OutputFinalShader(GeometryShader, "ShaderBuilder/Geometry-FULL.glsl");

	 
	return GeometryShader;
}
string Shader::ConstructFragmentShader()
{

	string header = FileToText("ShaderBuilder/Fragment1-header.glsl");
		
	string Normalfunc = FileToText("ShaderBuilder/Fragment2-Normalfunc.glsl");

	string NormalMapfunc = FileToText("ShaderBuilder/Fragment2-NormalMapfunc.glsl");
		
	string materialfunc1 = FileToText("ShaderBuilder/Fragment3-materialfunc1.glsl");
	
	string materialfunc1NormalMap = FileToText("ShaderBuilder/Fragment3-materialfunc1NormalMap.glsl");
	
	string materialfunc1NoNormalMap = FileToText("ShaderBuilder/Fragment3-materialfunc1NoNormalMap.glsl");
	
	string materialfunc2 = FileToText("ShaderBuilder/Fragment3-materialfunc2.glsl");
		
	string materialfunc2NormalMap = FileToText("ShaderBuilder/Fragment3-materialfunc2NormalMap.glsl");

	string materialfunc2NoNormalMap = FileToText("ShaderBuilder/Fragment3-materialfunc2NoNormalMap.glsl");
	
	string materialfunc3 = FileToText("ShaderBuilder/Fragment3-materialfunc3.glsl");
		
	string mainfunc1 = FileToText("ShaderBuilder/Fragment-mainfunc1.glsl");
		
	string mainfunc1Diffuse = FileToText("ShaderBuilder/Fragment-mainfunc1Diffuse.glsl");
		
	string mainfunc1NoDiffuse = FileToText("ShaderBuilder/Fragment-mainfunc1NoDiffuse.glsl");
	
	string mainfunc1NormalMap = FileToText("ShaderBuilder/Fragment-mainfunc1NormalMap.glsl");
	
	string mainfunc1NoNormalMap = FileToText("ShaderBuilder/Fragment-mainfunc1NoNormalMap.glsl");
	
	string mainfunc2 = FileToText("ShaderBuilder/Fragment-mainfunc2.glsl");
	
	
	string FragmentShader = header;
	FragmentShader += (this->shaderInfo.NumNormalMap) ? NormalMapfunc : Normalfunc;

	FragmentShader += materialfunc1;
	FragmentShader += (this->shaderInfo.NumNormalMap) ? materialfunc1NormalMap : materialfunc1NoNormalMap;
	FragmentShader += materialfunc2;
	FragmentShader += (this->shaderInfo.NumNormalMap) ? materialfunc2NormalMap : materialfunc2NoNormalMap;
	FragmentShader += materialfunc3;

	FragmentShader += mainfunc1;
	FragmentShader += (this->shaderInfo.NumDiffuse) ? mainfunc1Diffuse : mainfunc1NoDiffuse;
	FragmentShader += (this->shaderInfo.NumNormalMap) ? mainfunc1NormalMap : mainfunc1NoNormalMap;
	FragmentShader += mainfunc2;

	OutputFinalShader(FragmentShader,"ShaderBuilder/Fragment-FULL.glsl");

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
void Shader::TextToFile(string Text, string Path)
{
	string line;
	ofstream myfile(Path);
	if (myfile.is_open())
	{
		myfile << Text;
		myfile.close();
	}
	else
	{
		throw exception("unable to open file");
	}
}
void Shader::OutputFinalShader(string Text, string Path)
{
	TextToFile(Text, Path);
}
void Shader::Use()
{
	glUseProgram(this->ProgramID);
}
Shader & Shader::At(string ID)
{
	return *Shader::mapShader[ID];
}
void Shader::ReloadAll()
{
	for (auto s : mapShader)
	{
		s.second->Reload();
	}
}
Shader::Shader()
{
}

