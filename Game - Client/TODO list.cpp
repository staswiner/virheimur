/*

0. Drawing objects assigned to layers before drawn, and sorted by layer asc
1. Add Edge Clippers for all shaders
2. Create a launcher/updater
3. implement simple combat
4. implement server sided AI monsters
5. switch to binary instead of json
6. fix website 
9. Deffered shading
10. shadow mapping
11. order transparent objects
12. construct DLLs
14. shader condition file format
15. shader condition view and edit application
16. physical collision
17. implement algorithms, and pseudo sensors

*/
//#version 400 core
//layout (location = 0) in vec2 position;
//layout (location = 1) in vec2 uvs;
//out vec2 TexCoords;
//
////uniform mat4 projection;
////uniform mat4 view;
//uniform mat4 model;
//uniform vec2 uvoffset;
//
//void main()
//{
//	gl_Position = model * vec4(position.x, position.y, 0.0, 1.0);
//	float x1,y1,x2,y2;
//	vec2 UVs;
//	x1 = (1.0 / 16.0 ) * uvoffset.x;
//	y1 = (1.0 / 16.0 ) * uvoffset.y;
//	x2 = (1.0 / 16.0 ) * uvoffset.x + (1.0 / 16.0 );
//	y2 = (1.0 / 16.0 ) * uvoffset.y - (1.0 / 16.0 );
//	if (uvs.x == 0)
//		UVs.x = x1;
//	if (uvs.x == 1)
//		UVs.x = x2;
//	if (uvs.y == 0)
//		UVs.y = y1;
//	if (uvs.y == 1)
//		UVs.y = y2;
//    TexCoords = vec2(UVs.x, UVs.y);
//	TexCoords = uvs;
//}  