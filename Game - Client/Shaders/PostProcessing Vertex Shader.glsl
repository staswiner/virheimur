#version 400 core
layout (location = 0) in vec2 position;
layout (location = 1) in vec2 UVs;
out vec2 TexCoords;

uniform vec4 ScreenCoordinates; // left, top, right, bot
uniform vec4 FBO_Coordinates; // left, top, right, bot

void main()
{
	// Size
	vec2 ScreenDimension = vec2(ScreenCoordinates.z - ScreenCoordinates.x, ScreenCoordinates.w - ScreenCoordinates.y);  // 4,4
	vec2 FBO_Dimension = vec2(FBO_Coordinates.z - FBO_Coordinates.x, FBO_Coordinates.w - FBO_Coordinates.y);  // 2,2
	
	// Offset from top left
	vec2 FBO_From_Screen_Offset = (((FBO_Coordinates.xy - ScreenCoordinates.xy) / ScreenDimension)) * 2.0f - 1.0f;
	FBO_From_Screen_Offset = FBO_From_Screen_Offset * vec2(1.0f,-1.0f); 
	
	// Combining both
	vec2 FBO_Screen_Mapping = FBO_Dimension / ScreenDimension * 2.0f;
	
	vec2 OpenGL_Coordinates = FBO_Screen_Mapping * position + FBO_From_Screen_Offset;
	
	gl_Position = vec4(OpenGL_Coordinates.x, OpenGL_Coordinates.y, 0.0, 1.0);


	//gl_Position = vec4(position.x, position.y, 0.0, 1.0);
	
    TexCoords = vec2(UVs.x, UVs.y);
}  