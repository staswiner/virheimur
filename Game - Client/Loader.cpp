//#include "Loader.h"
//
//
//
////vector<bool>   Loader::isFileLoaded(4, false);
//
//
//
///*
//Loads AABB ( axis aligned boundry box )
//*/
//void Loader::LoadModelBox()
//{
//	vec3 Max(0, 0, 0);
//	vec3 Min(0, 0, 0);
//	for (uint i = 0; i < vertices.size(); i++)
//	{
//		if (vertices[i].Position.x > vertices[(uint)Max.x].Position.x)
//			Max.x = (float)i;
//
//		if (vertices[i].Position.y > vertices[(uint)Max.y].Position.y)
//			Max.y = (float)i;
//
//		if (vertices[i].Position.z > vertices[(uint)Max.z].Position.z)
//			Max.z = (float)i;
//
//		if (vertices[i].Position.x < vertices[(uint)Min.x].Position.x)
//			Min.x = (float)i;
//
//		if (vertices[i].Position.y < vertices[(uint)Min.y].Position.y)
//			Min.y = (float)i;
//
//		if (vertices[i].Position.z < vertices[(uint)Min.z].Position.z)
//			Min.z = (float)i;
//	}
//	verticesSimplified.push_back(vertices[(uint)Max.x]);
//	verticesSimplified.push_back(vertices[(uint)Max.y]);
//	verticesSimplified.push_back(vertices[(uint)Max.z]);
//	verticesSimplified.push_back(vertices[(uint)Min.x]);
//	verticesSimplified.push_back(vertices[(uint)Min.y]);
//	verticesSimplified.push_back(vertices[(uint)Min.z]);
//
//	verticesBox.push_back(vec3(vertices[(uint)Max.x].Position.x, vertices[(uint)Max.y].Position.y, vertices[(uint)Max.z].Position.z));
//	verticesBox.push_back(vec3(vertices[(uint)Max.x].Position.x, vertices[(uint)Max.y].Position.y, vertices[(uint)Min.z].Position.z));
//	verticesBox.push_back(vec3(vertices[(uint)Max.x].Position.x, vertices[(uint)Min.y].Position.y, vertices[(uint)Max.z].Position.z));
//	verticesBox.push_back(vec3(vertices[(uint)Max.x].Position.x, vertices[(uint)Min.y].Position.y, vertices[(uint)Min.z].Position.z));
//
//	verticesBox.push_back(vec3(vertices[(uint)Min.x].Position.x, vertices[(uint)Max.y].Position.y, vertices[(uint)Max.z].Position.z));
//	verticesBox.push_back(vec3(vertices[(uint)Min.x].Position.x, vertices[(uint)Max.y].Position.y, vertices[(uint)Min.z].Position.z));
//	verticesBox.push_back(vec3(vertices[(uint)Min.x].Position.x, vertices[(uint)Min.y].Position.y, vertices[(uint)Max.z].Position.z));
//	verticesBox.push_back(vec3(vertices[(uint)Min.x].Position.x, vertices[(uint)Min.y].Position.y, vertices[(uint)Min.z].Position.z));
//
//	verticesBox.push_back(vec3(vertices[(uint)Max.x].Position.x, vertices[(uint)Max.y].Position.y, vertices[(uint)Max.z].Position.z));
//	verticesBox.push_back(vec3(vertices[(uint)Max.x].Position.x, vertices[(uint)Min.y].Position.y, vertices[(uint)Max.z].Position.z));
//	verticesBox.push_back(vec3(vertices[(uint)Max.x].Position.x, vertices[(uint)Max.y].Position.y, vertices[(uint)Min.z].Position.z));
//	verticesBox.push_back(vec3(vertices[(uint)Max.x].Position.x, vertices[(uint)Min.y].Position.y, vertices[(uint)Min.z].Position.z));
//								
//	verticesBox.push_back(vec3(vertices[(uint)Min.x].Position.x, vertices[(uint)Max.y].Position.y, vertices[(uint)Max.z].Position.z));
//	verticesBox.push_back(vec3(vertices[(uint)Min.x].Position.x, vertices[(uint)Min.y].Position.y, vertices[(uint)Max.z].Position.z));
//	verticesBox.push_back(vec3(vertices[(uint)Min.x].Position.x, vertices[(uint)Max.y].Position.y, vertices[(uint)Min.z].Position.z));
//	verticesBox.push_back(vec3(vertices[(uint)Min.x].Position.x, vertices[(uint)Min.y].Position.y, vertices[(uint)Min.z].Position.z));
//
//	verticesBox.push_back(vec3(vertices[(uint)Max.x].Position.x, vertices[(uint)Max.y].Position.y, vertices[(uint)Max.z].Position.z));
//	verticesBox.push_back(vec3(vertices[(uint)Min.x].Position.x, vertices[(uint)Max.y].Position.y, vertices[(uint)Max.z].Position.z));
//	verticesBox.push_back(vec3(vertices[(uint)Max.x].Position.x, vertices[(uint)Min.y].Position.y, vertices[(uint)Max.z].Position.z));
//	verticesBox.push_back(vec3(vertices[(uint)Min.x].Position.x, vertices[(uint)Min.y].Position.y, vertices[(uint)Max.z].Position.z));
//							
//	verticesBox.push_back(vec3(vertices[(uint)Max.x].Position.x, vertices[(uint)Max.y].Position.y, vertices[(uint)Min.z].Position.z));
//	verticesBox.push_back(vec3(vertices[(uint)Min.x].Position.x, vertices[(uint)Max.y].Position.y, vertices[(uint)Min.z].Position.z));
//	verticesBox.push_back(vec3(vertices[(uint)Max.x].Position.x, vertices[(uint)Min.y].Position.y, vertices[(uint)Min.z].Position.z));
//	verticesBox.push_back(vec3(vertices[(uint)Min.x].Position.x, vertices[(uint)Min.y].Position.y, vertices[(uint)Min.z].Position.z));
//	//vertices.clear();
//	//vertices = verticesSimplified;
//}
//void Loader::InitTexture()
//{
//	// texture
//	glGenTextures(1, &texture);
//	//bind as 2d texture
//	glBindTexture(GL_TEXTURE_2D, texture);
//	// Set our texture parameters
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	//// Set texture filtering
//	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	//// 
//	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//	// Load, create texture and generate mipmaps
//	int width, height;
//	unsigned char* image = SOIL_load_image(BMP_NAME.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//	glGenerateMipmap(GL_TEXTURE_2D);
//	//glGenerateTextureMipmap(texture);
//	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//	//glGenerateMipmap(GL_TEXTURE_2D);
//	SOIL_free_image_data(image);
//	glEnable(GL_TEXTURE_2D);
//	//unbind texture 2d
//	glBindTexture(GL_TEXTURE_2D, 0);
//
//	if (SHINE_NAME != "")
//	{
//		// texture
//		glGenTextures(1, &Shine);
//		//bind as 2d texture
//		glBindTexture(GL_TEXTURE_2D, Shine);
//		// Set our texture parameters
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//
//		int width, height;
//
//		unsigned char* image = SOIL_load_image(SHINE_NAME.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
//		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//		glGenerateMipmap(GL_TEXTURE_2D);
//
//		SOIL_free_image_data(image);
//		glEnable(GL_TEXTURE_2D);
//		//unbind texture 2d
//		glBindTexture(GL_TEXTURE_2D, 0);
//	}
//
//
//	LoadVAO();
//
//}
//
//
//
//void Obj_Bmp_Loader::DrawModel(mat4& PerspectiveMat, mat4& ViewMat, mat4& ModelMat, Shader& shader)
//{
//																		
//	shader.Use();																
//	//apply shaders
//	GLint modelID = glGetUniformLocation(shader.ProgramID, "model");
//	GLint viewID = glGetUniformLocation(shader.ProgramID, "view");
//	GLint projectionID = glGetUniformLocation(shader.ProgramID, "projection");
//	glUniformMatrix4fv(modelID, 1, GL_FALSE, value_ptr(ModelMat));
//	glUniformMatrix4fv(viewID, 1, GL_FALSE, value_ptr(ViewMat));
//	glUniformMatrix4fv(projectionID, 1, GL_FALSE, value_ptr(PerspectiveMat));
//
//	// Draw container
//	glBindVertexArray(VAO);
//	glDrawArrays(GL_TRIANGLES, 0, Vertices_Amount);
//	glBindVertexArray(0);
//
//}
//void Loader::DrawModel()
//{
//	glBindVertexArray(VAO);
//	glDrawArrays(GL_TRIANGLES, 0, Vertices_Amount);
//	glBindVertexArray(0);
//}
//
//void Loader::DrawModelGaussic(mat4& PerspectiveMat, mat4& ViewMat, mat4& ModelMat, Shader& shader)
//{
//	shader.Use();
//	//apply shaders
//	GLint modelID = glGetUniformLocation(shader.ProgramID, "model");
//	GLint viewID = glGetUniformLocation(shader.ProgramID, "view");
//	GLint projectionID = glGetUniformLocation(shader.ProgramID, "projection");
//	glUniformMatrix4fv(modelID, 1, GL_FALSE, value_ptr(ModelMat));
//	glUniformMatrix4fv(viewID, 1, GL_FALSE, value_ptr(ViewMat));
//	glUniformMatrix4fv(projectionID, 1, GL_FALSE, value_ptr(PerspectiveMat));
//
//	// Draw container
//	glBindVertexArray(VAO);
//	glDrawArrays(GL_TRIANGLES, 0, Vertices_Amount);
//	glBindVertexArray(0);
//}