#include "GrassObjects.h"



GrassObjects::GrassObjects()
{
	m_StartTime = (rand() % 10000); ;
	m_Position = vec3((rand() % 100) - 50.0f, 0, (rand() % 100) - 50.0f);
}


GrassObjects::~GrassObjects()
{
}
